#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <random>
#include <vector>
#include <tuple>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std::chrono_literals;

// RRT* 트리용 노드 구조체
struct TreeNode {
  geometry_msgs::msg::Point point;
  int parent;
  double cost;
};

class RRTStarPlanner : public rclcpp::Node {
public:
  RRTStarPlanner()
  : Node("rrt_star_planner"),
    gen_(42),               // 난수 생성기 시드 고정
    first_plan_done_(false) // 최초 실행 여부
  {
    // 1) transient_local QoS 로 latched 구독
    rclcpp::QoS qos(1); // 메세지 하나만 버퍼에 저장해둠
    qos.transient_local(); // 가장 최신 것 하나만 받아옴
    obstacle_sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/obstacle_positions", qos,
      std::bind(&RRTStarPlanner::obstacleCallback, this, std::placeholders::_1)
    );

    // 2) MarkerArray 퍼블리셔
    marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
      "/rrt_star/markers", 10
    );

    // 3) 시작 & 목표 설정
    start_ = createPoint(0.1435, 0.0, 0.976);
    goal_  = createPoint(0.6,    0.0, 0.57);

    // 4) 1 Hz 로 MarkerArray 퍼블리시
    timer_ = this->create_wall_timer(
      1000ms, std::bind(&RRTStarPlanner::publishMarkers, this)
    );
  }

private:
  // ── 콜백: 장애물 좌표 수신 시
  void obstacleCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    const auto& d = msg->data;
    if (d.size() % 3 != 0) {
      RCLCPP_WARN(get_logger(),
        "Obstacle data size (%zu) not multiple of 3, ignoring", d.size());
      return;
    }
    obstacles_.clear();
    for (size_t i = 0; i < d.size(); i += 3) {
      auto pt = createPoint(d[i], d[i+1], d[i+2]);
      obstacles_.emplace_back(pt, 0.045, 0.045, 0.0575);
    }
    RCLCPP_INFO(get_logger(), "Received %zu obstacles", obstacles_.size());

    if (!first_plan_done_) {
      RCLCPP_INFO(get_logger(), "Running initial RRT* planning...");
      plan();
      first_plan_done_ = true;
    }
  }

  // 3D Point 생성
  geometry_msgs::msg::Point createPoint(double x, double y, double z) {
    geometry_msgs::msg::Point p; p.x = x; p.y = y; p.z = z; return p;
  }

  // ── RRT* 알고리즘
  void plan() {
    const double x_min=-0.5, x_max=1.0,
                 y_min=-0.5, y_max=1.0,
                 z_min= 0.0, z_max=1.0;
    const double step_size=0.05, search_r=0.3, goal_bias=0.05;
    const int    max_iters=1000;

    std::uniform_real_distribution<> dx(x_min,x_max),
                                  dy(y_min,y_max),
                                  dz(z_min,z_max),
                                  db(0.0,1.0);

    nodes_.clear();
    nodes_.push_back({ start_, -1, 0.0 });

    for (int iter = 0; iter < max_iters; ++iter) {
      // 샘플링
      geometry_msgs::msg::Point rnd = 
        (db(gen_) < goal_bias) ? goal_ : createPoint(dx(gen_), dy(gen_), dz(gen_));
      int nearest = nearestNode(rnd);
      auto new_pt = steer(nodes_[nearest].point, rnd, step_size);
      if (collision(nodes_[nearest].point, new_pt)) continue;

      TreeNode new_node{ new_pt, nearest,
        nodes_[nearest].cost + distance(nodes_[nearest].point, new_pt) };

      auto nbrs = nearNodes(new_pt, search_r);
      for (auto idx : nbrs) {
        double c = nodes_[idx].cost + distance(nodes_[idx].point, new_pt);
        if (!collision(nodes_[idx].point, new_pt) && c < new_node.cost) {
          new_node.parent = idx;
          new_node.cost   = c;
        }
      }

      int id = nodes_.size();
      nodes_.push_back(new_node);
      for (auto idx : nbrs) {
        double c2 = new_node.cost + distance(new_pt, nodes_[idx].point);
        if (!collision(new_pt, nodes_[idx].point) && c2 < nodes_[idx].cost) {
          nodes_[idx].parent = id;
          nodes_[idx].cost   = c2;
        }
      }
    }

    int gp = nearestNode(goal_);
    if (!collision(nodes_[gp].point, goal_)) {
      TreeNode g{ goal_, gp,
        nodes_[gp].cost + distance(nodes_[gp].point, goal_) };
      nodes_.push_back(g);
      reconstructPath(nodes_.size()-1);
    } else {
      reconstructPath(nearestNode(goal_));
      RCLCPP_INFO(get_logger(), "Obstacle blocking goal connection");
    }
  }

  // 거리 계산
  double distance(const geometry_msgs::msg::Point &a,
                  const geometry_msgs::msg::Point &b) {
    return std::hypot(a.x-b.x, a.y-b.y, a.z-b.z);
  }

  // 최근접 노드 찾기
  int nearestNode(const geometry_msgs::msg::Point &pt) {
    double mind = std::numeric_limits<double>::infinity();
    int    idx = 0;
    for (size_t i=0;i<nodes_.size();++i) {
      double d = distance(nodes_[i].point, pt);
      if (d < mind) { mind=d; idx=i; }
    }
    return idx;
  }

  // 반경 내 노드 목록
  std::vector<int> nearNodes(const geometry_msgs::msg::Point &pt, double r) {
    std::vector<int> out;
    for (size_t i=0;i<nodes_.size();++i)
      if (distance(nodes_[i].point, pt) <= r) out.push_back(i);
    return out;
  }

  // steer
  geometry_msgs::msg::Point steer(const geometry_msgs::msg::Point &from,
                                  const geometry_msgs::msg::Point &to,
                                  double eps) {
    double dx=to.x-from.x, dy=to.y-from.y, dz=to.z-from.z;
    double d = std::sqrt(dx*dx+dy*dy+dz*dz);
    if (d<1e-6) return from;
    double t = std::min(eps, d);
    return createPoint(from.x+t*dx/d, from.y+t*dy/d, from.z+t*dz/d);
  }

  // 충돌 검사 (ellipsoid)
  bool collision(const geometry_msgs::msg::Point &a,
                 const geometry_msgs::msg::Point &b) {
    for (auto &obs : obstacles_) {
      auto &[c, rx, ry, rz] = obs;
      double dx=b.x-a.x, dy=b.y-a.y, dz=b.z-a.z;
      double A = dx*dx/(rx*rx)+dy*dy/(ry*ry)+dz*dz/(rz*rz);
      double B = 2*((a.x-c.x)*dx/(rx*rx)
                  +(a.y-c.y)*dy/(ry*ry)
                  +(a.z-c.z)*dz/(rz*rz));
      double C = (a.x-c.x)*(a.x-c.x)/(rx*rx)
               +(a.y-c.y)*(a.y-c.y)/(ry*ry)
               +(a.z-c.z)*(a.z-c.z)/(rz*rz)-1.0;
      double disc=B*B-4*A*C;
      if (disc<0) continue;
      double t1=(-B+std::sqrt(disc))/(2*A), t2=(-B-std::sqrt(disc))/(2*A);
      if ((t1>=0&&t1<=1)||(t2>=0&&t2<=1)) return true;
    }
    return false;
  }

  // 경로 재구성
  void reconstructPath(int idx) {
    best_path_.clear();
    for (int cur=idx; cur>=0; cur=nodes_[cur].parent)
      best_path_.push_back(nodes_[cur].point);
    std::reverse(best_path_.begin(), best_path_.end());
  }

  // ── RViz용 MarkerArray 퍼블리시 & 로그
  void publishMarkers() {
    visualization_msgs::msg::MarkerArray m_array;
    
    // 트리 마커
    visualization_msgs::msg::Marker tree;
    tree.header.frame_id = "world";
    tree.header.stamp    = now();
    tree.ns              = "rrt_tree";
    tree.id              = 0;
    tree.type            = visualization_msgs::msg::Marker::LINE_LIST;
    tree.action          = visualization_msgs::msg::Marker::ADD;
    tree.scale.x = 0.001;
    tree.color.g = 1.0; tree.color.a = 0.3;
    for (size_t i=1;i<nodes_.size();++i) {
      tree.points.push_back(nodes_[i].point);
      tree.points.push_back(nodes_[nodes_[i].parent].point);
    }
    m_array.markers.push_back(tree);
    // 최적 경로 마커
    visualization_msgs::msg::Marker path;
    path.header.frame_id = "world";
    path.header.stamp    = now();
    path.ns              = "rrt_path";
    path.id              = 0;
    path.type            = visualization_msgs::msg::Marker::LINE_STRIP;
    path.action          = visualization_msgs::msg::Marker::ADD;
    path.scale.x = 0.005;
    path.color.r = 1.0; path.color.a = 1.0;
    for (auto &p : best_path_) path.points.push_back(p);
    m_array.markers.push_back(path);

    marker_pub_->publish(m_array);
  }

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr obstacle_sub_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  geometry_msgs::msg::Point start_, goal_;
  std::vector<std::tuple<geometry_msgs::msg::Point,double,double,double>> obstacles_;
  std::vector<TreeNode> nodes_;
  std::vector<geometry_msgs::msg::Point> best_path_;
  std::mt19937 gen_;
  bool first_plan_done_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RRTStarPlanner>());
  rclcpp::shutdown();
  return 0;
}
