#include <rclcpp/rclcpp.hpp>
#include <vector> // STL 벡터 사용 -> 크기를 자동으로 늘릴 수 있는 배열
#include <Eigen/Dense>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <chrono> // 시간 관련 (타이머 설정용)

using namespace std::chrono_literals;

// Spline 보간을 수행하는 클래스 정의
class SplineInterpolationNode : public rclcpp::Node {
public:

    SplineInterpolationNode() : Node("spline_interpolation_node") {
        // RViz로 보내는 pub
        marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("visualization_marker_array", 10);

        // 20개의 제어점 정의: 위치(Eigen::Vector3d) + 쿼터니언(Eigen::Quaterniond) -> (마지막 경유점 (0.8, 0.9, 0.5)로 조정)
        std::vector<std::pair<Eigen::Vector3d, Eigen::Quaterniond>> controlPoints = {
            {{0.00, 0.00, 0.00}, Eigen::Quaterniond::Identity()},
            {{0.04, 0.08, 0.04}, Eigen::Quaterniond(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()))},
            {{0.08, 0.16, 0.08}, Eigen::Quaterniond(Eigen::AngleAxisd(0.2, Eigen::Vector3d::UnitZ()))},
            {{0.12, 0.24, 0.04}, Eigen::Quaterniond(Eigen::AngleAxisd(0.3, Eigen::Vector3d::UnitZ()))},
            {{0.16, 0.28, 0.12}, Eigen::Quaterniond(Eigen::AngleAxisd(0.4, Eigen::Vector3d::UnitZ()))},
            {{0.20, 0.20, 0.10}, Eigen::Quaterniond(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ()))},
            {{0.24, 0.16, 0.08}, Eigen::Quaterniond(Eigen::AngleAxisd(0.6, Eigen::Vector3d::UnitZ()))},
            {{0.28, 0.12, 0.10}, Eigen::Quaterniond(Eigen::AngleAxisd(0.7, Eigen::Vector3d::UnitZ()))},
            {{0.32, 0.08, 0.12}, Eigen::Quaterniond(Eigen::AngleAxisd(0.8, Eigen::Vector3d::UnitZ()))},
            {{0.36, 0.04, 0.14}, Eigen::Quaterniond(Eigen::AngleAxisd(0.9, Eigen::Vector3d::UnitZ()))},
            {{0.40, 0.00, 0.16}, Eigen::Quaterniond(Eigen::AngleAxisd(1.0, Eigen::Vector3d::UnitZ()))},
            {{0.44, 0.04, 0.18}, Eigen::Quaterniond(Eigen::AngleAxisd(1.1, Eigen::Vector3d::UnitZ()))},
            {{0.48, 0.08, 0.20}, Eigen::Quaterniond(Eigen::AngleAxisd(1.2, Eigen::Vector3d::UnitZ()))},
            {{0.52, 0.12, 0.22}, Eigen::Quaterniond(Eigen::AngleAxisd(1.3, Eigen::Vector3d::UnitZ()))},
            {{0.56, 0.16, 0.24}, Eigen::Quaterniond(Eigen::AngleAxisd(1.4, Eigen::Vector3d::UnitZ()))},
            {{0.60, 0.20, 0.26}, Eigen::Quaterniond(Eigen::AngleAxisd(1.5, Eigen::Vector3d::UnitZ()))},
            {{0.64, 0.24, 0.28}, Eigen::Quaterniond(Eigen::AngleAxisd(1.6, Eigen::Vector3d::UnitZ()))},
            {{0.68, 0.28, 0.30}, Eigen::Quaterniond(Eigen::AngleAxisd(1.7, Eigen::Vector3d::UnitZ()))},
            {{0.72, 0.32, 0.32}, Eigen::Quaterniond(Eigen::AngleAxisd(1.8, Eigen::Vector3d::UnitZ()))},
            {{0.80, 0.90, 0.50}, Eigen::Quaterniond(Eigen::AngleAxisd(2.0, Eigen::Vector3d::UnitZ()))}
        };

        // B-spline 보간의 차수 설정 (3차 -> cubic)
        int degree = 3;

        // Knot 벡터 생성: B-spline 계산에 사용되는 노드
        std::vector<double> knots(controlPoints.size() + degree + 1);

        // 시작 부분은 0으로 반복 -> 곡선이 첫번째 제어점을 정확히 지나도록 보장하기 위해
        for (size_t i = 0; i <= static_cast<size_t>(degree); ++i) knots[i] = 0.0;

        // 중간 구간은 균일한 간격
        for (size_t i = degree + 1; i < controlPoints.size(); ++i) knots[i] = i - degree;

        // 마지막 부분은 최대값으로 반복 -> 곡선이 마지막 제어점을 정확히 지나도록 보장하는 장치
        for (size_t i = controlPoints.size(); i < knots.size(); ++i) knots[i] = controlPoints.size() - degree;

        // 경로와 장애물 마커 생성
        marker_array_ = createPathMarkers(controlPoints, knots, degree);

        // 0.5초 간격으로 마커 퍼블리시하는 타이머 설정
        timer_ = this->create_wall_timer(500ms, [this]() {
            marker_pub_->publish(marker_array_);
        });

        // 터미널에 보간된 경로 출력
        printPath(controlPoints, knots, degree);
    }

private:
    // 퍼블리셔, 타이머, 마커 데이터 저장
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    visualization_msgs::msg::MarkerArray marker_array_;

    // B-spline Basis Function 재귀 정의 (De Boor 방식)
    double basisFunction(int i, int k, double t, const std::vector<double>& knots) {
        if (k == 0) {
            return (t >= knots[i] && t < knots[i + 1]) ? 1.0 : 0.0;
        } else {
            double denom1 = knots[i + k] - knots[i];
            double denom2 = knots[i + k + 1] - knots[i + 1];
            double term1 = (denom1 == 0) ? 0 : (t - knots[i]) / denom1 * basisFunction(i, k - 1, t, knots);
            double term2 = (denom2 == 0) ? 0 : (knots[i + k + 1] - t) / denom2 * basisFunction(i + 1, k - 1, t, knots);
            return term1 + term2;
        }
    }

    // 위치 + 자세 (Quaternion) 보간을 위한 함수
    std::pair<Eigen::Vector3d, Eigen::Quaterniond> cubicBSplineInterpolation(
        double t, const std::vector<std::pair<Eigen::Vector3d, Eigen::Quaterniond>>& controlPoints,
        const std::vector<double>& knots, int degree) 
    {
        Eigen::Vector3d position(0.0, 0.0, 0.0);            // 누적 위치값
        Eigen::Quaterniond orientation = Eigen::Quaterniond::Identity();  // 초기 쿼터니언
        int n = controlPoints.size() - 1;

        // 위치 보간 (벡터 덧셈 기반)
        for (int i = 0; i <= n; ++i) {
            double B = basisFunction(i, degree, t, knots);
            position += B * controlPoints[i].first;
        }

        // 자세 보간 (slerp는 연쇄적으로 적용되므로 완전 정확하진 않음)
        for (int i = 0; i < n; ++i) {
            double B = basisFunction(i, degree, t, knots);
            orientation = orientation.slerp(B, controlPoints[i].second);
        }

        return {position, orientation};
    }

    // 경로 마커(ARROW)를 생성해서 배열로 반환
    visualization_msgs::msg::MarkerArray createPathMarkers(
        const std::vector<std::pair<Eigen::Vector3d, Eigen::Quaterniond>>& controlPoints,
        const std::vector<double>& knots, int degree) 
    {
        visualization_msgs::msg::MarkerArray marker_array;
        double t_min = knots[degree];
        double t_max = knots[controlPoints.size()];  // 마지막 유효 구간
        int id = 0;

        // t를 일정 간격으로 샘플링해서 위치+자세 보간 결과를 마커로 생성
        for (double t = t_min; t <= t_max; t += 0.1) {
            auto [position, orientation] = cubicBSplineInterpolation(t, controlPoints, knots, degree);

            visualization_msgs::msg::Marker marker;
            marker.header.frame_id = "world";
            marker.header.stamp = this->now();
            marker.ns = "spline_path";
            marker.id = id++;
            marker.type = visualization_msgs::msg::Marker::ARROW;
            marker.action = visualization_msgs::msg::Marker::ADD;
            marker.pose.position.x = position.x();
            marker.pose.position.y = position.y();
            marker.pose.position.z = position.z();
            marker.pose.orientation.x = orientation.x();
            marker.pose.orientation.y = orientation.y();
            marker.pose.orientation.z = orientation.z();
            marker.pose.orientation.w = orientation.w();
            marker.scale.x = 0.05;  // 화살표 길이
            marker.scale.y = 0.05;  // 화살표 너비
            marker.scale.z = 0.05;  // 화살표 높이
            marker.color.r = 1.0;
            marker.color.g = 0.0;
            marker.color.b = 0.0;
            marker.color.a = 1.0;
            marker.lifetime = rclcpp::Duration(0, 0);  // 영구 표시

            marker_array.markers.push_back(marker);
        }
        return marker_array;
    }

    // 경로상의 보간 좌표들을 터미널에 출력
    void printPath(const std::vector<std::pair<Eigen::Vector3d, Eigen::Quaterniond>>& controlPoints,
                   const std::vector<double>& knots, int degree) 
    {
        double t_min = knots[degree];
        double t_max = knots[controlPoints.size()];

        RCLCPP_INFO(this->get_logger(), "Spline Interpolation Path with Orientation:");
        for (double t = t_min; t <= t_max; t += 0.1) {
            auto [position, orientation] = cubicBSplineInterpolation(t, controlPoints, knots, degree);
            RCLCPP_INFO(this->get_logger(), "t=%.2f -> (x=%.2f, y=%.2f, z=%.2f, qx=%.2f, qy=%.2f, qz=%.2f, qw=%.2f)", 
                        t, position.x(), position.y(), position.z(), orientation.x(), orientation.y(), orientation.z(), orientation.w());
        }
    }
};

// 메인 함수: 노드 실행
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SplineInterpolationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
