// src/path_test_node.cpp

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>

class PathTestNode : public rclcpp::Node {
public:
    PathTestNode()
    : Node("path_test_node") {
        // 퍼블리셔 생성
        start_goal_pub_ = this->create_publisher<geometry_msgs::msg::Point>("start_goal", 10);

        // 메시지를 한 번만 보내도록 설정
        publishStartGoal();  // 노드가 시작할 때 한 번만 호출
    }
private:
    void publishStartGoal() {
        geometry_msgs::msg::Point start, goal;
        
        // 예시: start_와 goal_ 점의 값을 설정
        start.x = 0.14; start.y = 0.0; start.z = 1.005;
        goal.x = 0.6; goal.y = 0.0; goal.z = 0.57;

        // 시작점 퍼블리시
        start_goal_pub_->publish(start);

        // 목표점 퍼블리시 (주기적으로)
        start_goal_pub_->publish(goal);

        RCLCPP_INFO(this->get_logger(), "start: [%.2f, %.2f, %.2f], goal: [%.2f, %.2f, %.2f]",
                    start.x, start.y, start.z, goal.x, goal.y, goal.z);
    }

    rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr start_goal_pub_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PathTestNode>());
    rclcpp::shutdown();
    return 0;
}
