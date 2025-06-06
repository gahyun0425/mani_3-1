// src/path_node.cpp

#include <rclcpp/rclcpp.hpp>
#include "my_vision_msgs/msg/harvest_ordering.hpp"  // 커스텀 메시지 타입
#include "std_msgs/msg/float64_multi_array.hpp"    // 위치·방위 전송용 메시지
#include <geometry_msgs/msg/point.hpp>
#include <visualization_msgs/msg/marker_array.hpp> // MarkerArray 정의
#include <Eigen/Dense>
#include <chrono>
#include <vector>
#include <limits>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std::chrono_literals;

// RRT* 트리용 노드 구조체: 3차원 좌표, 부모 인덱스, 누적 비용
struct TreeNode {
    geometry_msgs::msg::Point point;
    int parent;
    double cost;
};

class RSNode : public rclcpp::Node {
public:
    RSNode()
    : Node("rrt_spline_node"),
      gen_(42),
      first_plan_done_(false)
    {
        // 1) HarvestOrdering 메시지 구독자 생성 (latched)
        rclcpp::QoS qos(1);
        qos.transient_local();
        obstacle_sub_ = this->create_subscription<my_vision_msgs::msg::HarvestOrdering>(
            "/harvest_order", qos,
            std::bind(&RSNode::obstacleCallback, this, std::placeholders::_1)
        );

        // 2) RViz 시각화를 위한 MarkerArray 퍼블리셔 생성
        marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
            "/rrt_spline/markers", 10
        );
        RCLCPP_INFO(this->get_logger(), "[RSNode] MarkerArray 퍼블리셔 생성 완료: /rrt_spline/markers");

        // 3) 주기적으로 마커 퍼블리시할 타이머 (1Hz)
        timer_ = this->create_wall_timer(
            1000ms, std::bind(&RSNode::publishMarkers, this)
        );

        // 시작점과 목표점 설정 (예시)
        start_ = makePoint(0.1435, 0.0, 0.976);
        goal_  = makePoint(0.6,    0.0, 0.57);

        // 4) 위치·방위 퍼블리셔 생성
        orientation_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "path_to_inverse_kinematics", 10
        );
    }

private:
    // ───────────────────────────────────────────────────────────────────────
    // 1) /harvest_order 메시지 수신 콜백
    void obstacleCallback(const my_vision_msgs::msg::HarvestOrdering::SharedPtr msg) {
        RCLCPP_INFO(get_logger(), "[RSNode] HarvestOrdering 메시지 수신");

        // (기존) 우선순위, 장애물 처리
        RCLCPP_INFO(get_logger(), "===== 수확 우선순위 =====");
        for (size_t i = 0; i < msg->crop_ids.size(); ++i) {
            RCLCPP_INFO(get_logger(), "%2zu위: crop_id = %u", i+1, msg->crop_ids[i]);
        }
        obstacles_.clear();
        for (const auto &obj : msg->objects) {
            auto pt = makePoint(obj.x, obj.y, obj.z);
            obstacles_.emplace_back(pt, 0.045, 0.045, 0.0575);
        }
        RCLCPP_INFO(get_logger(), "장애물 개수: %zu", obstacles_.size());

        // 최초 한 번만 RRT* 플래닝 실행
        if (!first_plan_done_) {
            RCLCPP_INFO(get_logger(), "RRT* 플래닝 시작...");
            planRRTstar();
            buildKnots();
            first_plan_done_ = true;
        } else {
            RCLCPP_INFO(get_logger(), "이미 플래닝 완료, 재실행 생략");
        }

        // 2) 스플라인 보간 결과 전체를 퍼블리시
        publishPoseAndOrientation();
    }

    // 추가: B-Spline 1차 도함수 기저 함수 (basis function derivative)
    double basis_derivative(int i, int k, double t) {
        if (k == 0) return 0.0;
        double d1 = knots_[i + k] - knots_[i];
        double d2 = knots_[i + k + 1] - knots_[i + 1];
        double term1 = (d1 == 0 ? 0 : (1.0 / d1) * basis(i, k - 1, t));
        double term2 = (d2 == 0 ? 0 : (1.0 / d2) * basis(i + 1, k - 1, t));
        return k * (term1 - term2);
    }

    // 추가: B-Spline 속도 계산 함수
    Eigen::Vector3d interpolateVelocity(double t) {
        Eigen::Vector3d velocity(0, 0, 0);
        int n = static_cast<int>(splineCP_.size()) - 1;
        int k = splineDegree_;
        for (int i = 0; i <= n - 1; ++i) {  // 주의! i <= n-1까지만!
            double coef = basis_derivative(i, k, t);
            velocity += coef * splineCP_[i];
        }
        return velocity;
    }


    void publishPoseAndOrientation() {
        if (static_cast<int>(splineCP_.size()) < splineDegree_ + 1 ||
            static_cast<int>(orientationCP_.size()) < splineDegree_ + 1)
        {
            RCLCPP_WARN(this->get_logger(),
                "[RSNode] 스플라인 제어점/방위 제어점 부족: posCP=%zu, oriCP=%zu",
                splineCP_.size(), orientationCP_.size());
            return;
        }

        double t0 = knots_[splineDegree_];
        double t1 = knots_[splineCP_.size()];
        double dt = 0.01;


        std_msgs::msg::Float64MultiArray msg;
        msg.data.clear();

        size_t sample_count = static_cast<size_t>(std::floor((t1 - t0) / dt));

        size_t idx = 0;
        
        for (double t = t0; t < t1; t += dt) {
            double t_norm = (t - t0) / (t1 - t0);
            Eigen::Vector3d pi = interpolate(t);
            Eigen::Vector3d euler = interpolateOrientation(t);
            Eigen::Vector3d velocity = interpolateVelocity(t);  // ← 추가

            msg.data.push_back(t_norm);
            msg.data.push_back(pi.x());
            msg.data.push_back(pi.y());
            msg.data.push_back(pi.z());
            msg.data.push_back(euler.x());
            msg.data.push_back(euler.y());
            msg.data.push_back(euler.z());
            msg.data.push_back(velocity.x());  // ← 추가
            msg.data.push_back(velocity.y());  // ← 추가
            msg.data.push_back(velocity.z());  // ← 추가

            RCLCPP_INFO(this->get_logger(),
                "[RSNode] 샘플 %2zu: t=%.3f,  x=%.3f, y=%.3f, z=%.3f, roll=%.3f, pitch=%.3f, yaw=%.3f, vx=%.3f, vy=%.3f, vz=%.3f",
                idx,
                t_norm,
                pi.x(), pi.y(), pi.z(),
                euler.x(), euler.y(), euler.z(),
                velocity.x(), velocity.y(), velocity.z()
            );
            ++idx;
        }

        // 마지막 샘플 한 번 더 추가
        {
            double t = t1 - dt;  // 마지막 유효 t
            double t_norm = 1.0; // 정규화 t는 1로
            Eigen::Vector3d pi = interpolate(t);
            Eigen::Vector3d euler = interpolateOrientation(t);

            msg.data.push_back(t_norm);
            msg.data.push_back(pi.x());
            msg.data.push_back(pi.y());
            msg.data.push_back(pi.z());
            msg.data.push_back(euler.x()); // roll
            msg.data.push_back(euler.y()); // pitch
            msg.data.push_back(euler.z()); // yaw

            Eigen::Vector3d velocity = Eigen::Vector3d::Zero();
            msg.data.push_back(velocity.x());
            msg.data.push_back(velocity.y());
            msg.data.push_back(velocity.z());

            RCLCPP_INFO(this->get_logger(),
                "[RSNode] 샘플 %2zu: t=%.3f,  x=%.3f, y=%.3f, z=%.3f, roll=%.3f, pitch=%.3f, yaw=%.3f, vx=%.3f, vy=%.3f, vz=%.3f",
                idx,
                t_norm,
                pi.x(), pi.y(), pi.z(),
                euler.x(), euler.y(), euler.z(),
                0.0, 0.0, 0.0
            );
        }

        orientation_pub_->publish(msg);
        RCLCPP_INFO(this->get_logger(),
            "[RSNode] 스플라인 %zu개 샘플 퍼블리시 (t범위: 0 ~ 1)",
            sample_count);
    }




    // ───────────────────────────────────────────────────────────────────────
    // 3) RRT* 플래닝 함수 (기존 코드 유지)
    void planRRTstar() {
        // 샘플링 공간 경계 및 파라미터 설정
        const double xmin = -0.5, xmax = 1.0;
        const double ymin = -0.5, ymax = 1.0;
        const double zmin =  0.0, zmax = 1.0;
        const double step      = 0.05;
        const double radius    = 0.3;
        const double goal_bias = 0.05;
        const int    max_iter  = 1000;

        // 난수 분포 선언
        std::uniform_real_distribution<> ux(xmin, xmax);
        std::uniform_real_distribution<> uy(ymin, ymax);
        std::uniform_real_distribution<> uz(zmin, zmax);
        std::uniform_real_distribution<> ub(0.0, 1.0);

        // 트리 초기화
        nodes_.clear();
        nodes_.push_back({ start_, -1, 0.0 });

        // RRT* 메인 루프
        for (int it = 0; it < max_iter; ++it) {
            geometry_msgs::msg::Point rnd =
                (ub(gen_) < goal_bias) ? goal_ : makePoint(ux(gen_), uy(gen_), uz(gen_));
            int nid = nearestNode(rnd);
            auto new_pt = steer(nodes_[nid].point, rnd, step);
            if (collision(nodes_[nid].point, new_pt)) continue;

            TreeNode new_node{ new_pt, nid,
                nodes_[nid].cost + dist(nodes_[nid].point, new_pt) };

            auto nbrs = nearNodes(new_pt, radius);
            for (int j : nbrs) {
                double c = nodes_[j].cost + dist(nodes_[j].point, new_pt);
                if (!collision(nodes_[j].point, new_pt) && c < new_node.cost) {
                    new_node.parent = j;
                    new_node.cost   = c;
                }
            }

            int new_id = nodes_.size();
            nodes_.push_back(new_node);
            for (int j : nbrs) {
                double c2 = new_node.cost + dist(new_pt, nodes_[j].point);
                if (!collision(new_pt, nodes_[j].point) && c2 < nodes_[j].cost) {
                    nodes_[j].parent = new_id;
                    nodes_[j].cost   = c2;
                }
            }
        }

        // 목표 연결 시도 및 경로 재구성
        int gid = nearestNode(goal_);
        if (!collision(nodes_[gid].point, goal_)) {
            TreeNode g{ goal_, gid,
                nodes_[gid].cost + dist(nodes_[gid].point, goal_) };
            nodes_.push_back(g);
            reconstructPath(nodes_.size() - 1);
        } else {
            reconstructPath(nearestNode(goal_));
            RCLCPP_INFO(get_logger(), "목표점 연결 불가, 최근접 노드 사용");
        }

        // B-Spline 제어점(위치) 준비
        splineCP_.clear();
        for (const auto &p : best_path_) {
            splineCP_.push_back(Eigen::Vector3d(p.x, p.y, p.z));
        }

        // <<< 여기를 주목: 오일러 각 제어점도 초기화
        orientationCP_.clear();
        // 예시로는 모두 (0,0,0)으로만 채웠습니다.
        // 실제로는 best_path_의 각 지점에 대응하는 roll/pitch/yaw 값을 넣으면 됩니다.
        for (size_t i = 0; i < best_path_.size(); ++i) {
            orientationCP_.push_back(Eigen::Vector3d(0.0, 0.0, 0.0));
        }

        splineDegree_ = 3;
    }

    // ───────────────────────────────────────────────────────────────────────
    // 4) MarkerArray 시각화 함수 (1Hz)
    void publishMarkers() {
        visualization_msgs::msg::MarkerArray ma;

        // RRT* 트리 표시 (LINE_LIST)
        visualization_msgs::msg::Marker tree;
        tree.header.frame_id = "world";
        tree.header.stamp    = now();
        tree.ns              = "rrt_tree";
        tree.id              = 0;
        tree.type            = visualization_msgs::msg::Marker::LINE_LIST;
        tree.action          = visualization_msgs::msg::Marker::ADD;
        tree.scale.x         = 0.001;
        tree.color.g         = 1.0;
        tree.color.a         = 0.3;
        for (size_t i = 1; i < nodes_.size(); ++i) {
            tree.points.push_back(nodes_[i].point);
            tree.points.push_back(nodes_[nodes_[i].parent].point);
        }
        ma.markers.push_back(tree);

        // 최적 경로 표시 (LINE_STRIP)
        visualization_msgs::msg::Marker path;
        path.header.frame_id = "world";
        path.header.stamp    = now();
        path.ns              = "rrt_path";
        path.id              = 1;
        path.type            = visualization_msgs::msg::Marker::LINE_STRIP;
        path.action          = visualization_msgs::msg::Marker::ADD;
        path.scale.x         = 0.005;
        path.color.b         = 1.0;
        path.color.a         = 1.0;
        for (const auto &pt : best_path_) {
            path.points.push_back(pt);
        }
        ma.markers.push_back(path);

        // B-Spline 표시 (LINE_STRIP)
        if (static_cast<int>(splineCP_.size()) >= splineDegree_ + 1) {
            visualization_msgs::msg::Marker spline;
            spline.header.frame_id = "world";
            spline.header.stamp    = now();
            spline.ns              = "spline_path";
            spline.id              = 2;
            spline.type            = visualization_msgs::msg::Marker::LINE_STRIP;
            spline.action          = visualization_msgs::msg::Marker::ADD;
            spline.scale.x         = 0.005;
            spline.color.r         = 1.0;
            spline.color.a         = 1.0;
            double t0 = knots_[splineDegree_];
            double t1 = knots_[splineCP_.size()];
            for (double t = t0; t <= t1; t += 0.01) {
                Eigen::Vector3d pi = interpolate(t);
                geometry_msgs::msg::Point gp;
                gp.x = pi.x(); gp.y = pi.y(); gp.z = pi.z();
                spline.points.push_back(gp);
            }
            ma.markers.push_back(spline);
        }
        marker_pub_->publish(ma);
    }

    // ───────────────────────────────────────────────────────────────────────
    // 유틸리티 함수들

    // 거리 계산
    double dist(const geometry_msgs::msg::Point &a, const geometry_msgs::msg::Point &b) {
        return std::hypot(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    // 포인트 생성
    geometry_msgs::msg::Point makePoint(double x, double y, double z) {
        geometry_msgs::msg::Point p; p.x = x; p.y = y; p.z = z; return p;
    }
    // 최근접 노드 인덱스 구하기
    int nearestNode(const geometry_msgs::msg::Point &p) {
        double best = std::numeric_limits<double>::infinity();
        int idx = 0;
        for (size_t i = 0; i < nodes_.size(); ++i) {
            double d = dist(nodes_[i].point, p);
            if (d < best) { best = d; idx = (int)i; }
        }
        return idx;
    }
    // 반경 내 노드 인덱스 리스트 반환
    std::vector<int> nearNodes(const geometry_msgs::msg::Point &pt, double r) {
        std::vector<int> idxs;
        for (size_t i = 0; i < nodes_.size(); ++i) {
            if (dist(nodes_[i].point, pt) <= r) idxs.push_back((int)i);
        }
        return idxs;
    }
    // steer 함수
    geometry_msgs::msg::Point steer(
        const geometry_msgs::msg::Point &from,
        const geometry_msgs::msg::Point &to,
        double step
    ) {
        double dx = to.x - from.x;
        double dy = to.y - from.y;
        double dz = to.z - from.z;
        double d = std::sqrt(dx*dx + dy*dy + dz*dz);
        if (d < 1e-6) return from;
        double t = std::min(step, d);
        return makePoint(
            from.x + t*(dx/d),
            from.y + t*(dy/d),
            from.z + t*(dz/d)
        );
    }
    // 충돌 검사 (타원체)
    bool collision(
        const geometry_msgs::msg::Point &a,
        const geometry_msgs::msg::Point &b
    ) {
        for (auto &obs : obstacles_) {
            auto &[c, rx, ry, rz] = obs;
            double dx = b.x - a.x;
            double dy = b.y - a.y;
            double dz = b.z - a.z;
            double A = dx*dx/(rx*rx) + dy*dy/(ry*ry) + dz*dz/(rz*rz);
            double B = 2*((a.x-c.x)*dx/(rx*rx)
                      + (a.y-c.y)*dy/(ry*ry)
                      + (a.z-c.z)*dz/(rz*rz));
            double C = (a.x-c.x)*(a.x-c.x)/(rx*rx)
                     + (a.y-c.y)*(a.y-c.y)/(ry*ry)
                     + (a.z-c.z)*(a.z-c.z)/(rz*rz) - 1;
            double disc = B*B - 4*A*C;
            if (disc < 0) continue;
            double t1 = (-B + std::sqrt(disc)) / (2*A);
            double t2 = (-B - std::sqrt(disc)) / (2*A);
            if ((t1>=0 && t1<=1) || (t2>=0 && t2<=1)) return true;
        }
        return false;
    }
    // 경로 재구성
    void reconstructPath(int idx) {
        best_path_.clear();
        for (int i = idx; i >= 0; i = nodes_[i].parent) {
            best_path_.push_back(nodes_[i].point);
        }
        std::reverse(best_path_.begin(), best_path_.end());
    }

    // B-Spline 기저 함수
    double basis(int i, int k, double t) {
        if (k == 0) return (t >= knots_[i] && t < knots_[i+1]) ? 1.0 : 0.0;
        double d1 = knots_[i+k]   - knots_[i];
        double d2 = knots_[i+k+1] - knots_[i+1];
        double a = (d1 == 0 ? 0 : (t - knots_[i]) / d1 * basis(i, k-1, t));
        double b = (d2 == 0 ? 0 : (knots_[i+k+1] - t) / d2 * basis(i+1, k-1, t));
        return a + b;
    }
    // B-Spline 매듭 벡터 생성
    void buildKnots() {
        int n = static_cast<int>(splineCP_.size()), k = splineDegree_;
        knots_.resize(n + k + 1);
        for (int i = 0; i <= k; ++i)           knots_[i] = 0;
        for (int i = k + 1; i <= n - 1; ++i)   knots_[i] = i - k;
        for (int i = n; i <= n + k; ++i)       knots_[i] = n - k;
    }

    // B-Spline 위치 보간
    Eigen::Vector3d interpolate(double t) {
        Eigen::Vector3d p(0,0,0);
        int n = static_cast<int>(splineCP_.size()) - 1, k = splineDegree_;
        for (int i = 0; i <= n; ++i) {
            p += basis(i, k, t) * splineCP_[i];
        }
        return p;
    }

    // <<< 여기를 주목: 오일러 각 보간 함수 (쭉 1차원 보간) >>>
    Eigen::Vector3d interpolateOrientation(double t) {

        // 보간 결과 벡터
        double roll = 0.0, pitch = 0.0, yaw = 0.0;

        // B-Spline 기저 함수를 이용해 각 축 별로 1차원 보간
        int m = static_cast<int>(orientationCP_.size()) - 1;
        int k = splineDegree_;
        for (int i = 0; i <= m; ++i) {
            double coef = basis(i, k, t);
            roll  += coef * orientationCP_[i].x();
            pitch += coef * orientationCP_[i].y();
            yaw   += coef * orientationCP_[i].z();
        }
        return Eigen::Vector3d(roll, pitch, yaw);
    }

    // ───────────────────────────────────────────────────────────────────────
    // 멤버 변수들
    rclcpp::Subscription<my_vision_msgs::msg::HarvestOrdering>::SharedPtr obstacle_sub_;
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr orientation_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    geometry_msgs::msg::Point start_, goal_;
    std::vector<std::tuple<geometry_msgs::msg::Point,double,double,double>> obstacles_;
    std::vector<TreeNode> nodes_;
    std::vector<geometry_msgs::msg::Point> best_path_;
    std::vector<Eigen::Vector3d> splineCP_;        // 위치 제어점
    std::vector<Eigen::Vector3d> orientationCP_;   // 오일러 각 제어점 <<< 추가
    std::vector<double> knots_;
    int splineDegree_;
    std::mt19937 gen_;
    bool first_plan_done_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RSNode>());
    rclcpp::shutdown();
    return 0;
}
