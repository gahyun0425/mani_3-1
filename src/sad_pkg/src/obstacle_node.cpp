// src/harvest_order_publisher.cpp

#include <rclcpp/rclcpp.hpp>
#include "my_vision_msgs/msg/harvest_ordering.hpp"
#include "my_vision_msgs/msg/detected_crop.hpp"
#include <chrono>

using namespace std::chrono_literals;

class HarvestOrderPublisher : public rclcpp::Node
{
public:
  HarvestOrderPublisher()
  : Node("harvest_order_publisher")
  {
    // 1) transient_local QoS 로 latched 퍼블리셔 생성
    rclcpp::QoS qos(1);
    qos.transient_local();
    pub_ = this->create_publisher<my_vision_msgs::msg::HarvestOrdering>(
      "/harvest_order", qos);

    // 2) 예시 우선순위 및 장애물(작물) 좌표 초기화
    crop_ids_ = { 3, 1, 2, 4, 6, 5};
    positions_ = {
       0.6,  0.0,  0.5,
       0.6,  0.1,  0.5,
       0.6, -0.1,  0.5,
       0.6,  0.2,  0.5,
       0.6, -0.2,  0.5,
       0.6,  0.0,  0.7,
       0.6,  0.1,  0.7,
       0.6, -0.1,  0.7
    };

    // 3) 1초 뒤 한 번만 publish
    timer_ = this->create_wall_timer(
      2000ms, std::bind(&HarvestOrderPublisher::on_timer, this));
  }

private:
  void on_timer()
  {
    auto msg = my_vision_msgs::msg::HarvestOrdering();

    // Header timestamp
    msg.header.stamp = this->now();
    msg.header.frame_id = "world";

    // 우선순위 ID
    msg.crop_ids = crop_ids_;

    // DetectedCrop 객체 채우기
    size_t n = positions_.size() / 3;
    msg.objects.reserve(n);
    for (size_t i = 0; i < n; ++i) {
      my_vision_msgs::msg::DetectedCrop obj;
      obj.x = positions_[3*i + 0];
      obj.y = positions_[3*i + 1];
      obj.z = positions_[3*i + 2];
      msg.objects.push_back(obj);
    }

    // 총 개수
    msg.total_objects = static_cast<uint32_t>(n);

    // 퍼블리시
    pub_->publish(msg);
    RCLCPP_INFO(this->get_logger(),
      "★ Published HarvestOrder: %u items (latched)", msg.total_objects);

    // 타이머 해제 (한 번만)
    timer_->cancel();
  }

  rclcpp::Publisher<my_vision_msgs::msg::HarvestOrdering>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::vector<uint32_t> crop_ids_;
  std::vector<double> positions_;
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<HarvestOrderPublisher>());
  rclcpp::shutdown();
  return 0;
}
