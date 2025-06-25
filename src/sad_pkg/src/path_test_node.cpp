// src/path_test_node.cpp

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;

class PathTestNode : public rclcpp::Node {
public:
    PathTestNode()
    : Node("path_test_node") {
        start_goal_pub_ = this->create_publisher<geometry_msgs::msg::PointStamped>("start_goal", 10);
        publishStartGoal();
    }

private:
    void publishStartGoal() {
        geometry_msgs::msg::PointStamped start, goal;

        start.header.frame_id = "start";
        start.header.stamp = this->now();
        start.point.x = 0.14;
        start.point.y = 0.0;
        start.point.z = 1.005;

        goal.header.frame_id = "goal";
        goal.header.stamp = this->now();
        goal.point.x = 0.5;
        goal.point.y = 0.0;
        goal.point.z = 0.7;

        start_goal_pub_->publish(start);
        RCLCPP_INFO(this->get_logger(), "✅ Start sent");

        // 👇 수정된 부분
        std::function<void()> timer_cb = [this, goal]() mutable {
            start_goal_pub_->publish(goal);
            RCLCPP_INFO(this->get_logger(), "✅ Goal sent");
            timer_->cancel();
        };

        timer_ = this->create_wall_timer(1s, timer_cb);
    }

    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr start_goal_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PathTestNode>());
    rclcpp::shutdown();
    return 0;
}
