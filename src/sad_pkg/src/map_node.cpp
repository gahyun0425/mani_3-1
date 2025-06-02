// map_node.cpp

#include <rclcpp/rclcpp.hpp>
#include "my_vision_msgs/msg/harvest_ordering.hpp"
#include "my_vision_msgs/msg/detected_crop.hpp"
#include <visualization_msgs/msg/marker_array.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <sstream>

using namespace std::chrono_literals;

// 장애물(작물) 정보 구조체
struct Obstacle {
  geometry_msgs::msg::Point center;
  double rx, ry, rz;
};

class MapNode : public rclcpp::Node
{
public:
  MapNode()
  : Node("map_node")
  {
    // 1) HarvestOrder 토픽 구독 (latched: transient_local)
    rclcpp::QoS qos(1);
    qos.transient_local();
    order_sub_ = this->create_subscription<my_vision_msgs::msg::HarvestOrdering>(
      "/harvest_order", qos,
      std::bind(&MapNode::orderCallback, this, std::placeholders::_1)
    );

    // 2) MarkerArray 퍼블리셔 (RViz용)
    marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>(
      "/obstacle_markers", 10
    );

    // 3) 2Hz 주기로 MarkerArray 발행
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MapNode::publishMarkers, this)
    );
  }

private:
  // 콜백: HarvestOrder 수신
  void orderCallback(const my_vision_msgs::msg::HarvestOrdering::SharedPtr msg)
  {
    // 1) 우선순위 출력
    std::ostringstream oss;
    oss << "★ Received harvest priorities:";
    for (auto id : msg->crop_ids) {
      oss << " " << id;
    }
    RCLCPP_INFO(this->get_logger(), "%s", oss.str().c_str());

    // 2) 객체(좌표) 목록 갱신
    obstacles_.clear();
    for (const auto &obj : msg->objects) {
      geometry_msgs::msg::Point p;
      p.x = obj.x;
      p.y = obj.y;
      p.z = obj.z;
      // 반지름 예시: x=0.045, y=0.045, z=0.0575
      obstacles_.push_back({p, 0.045, 0.045, 0.0575});
    }

    RCLCPP_INFO(this->get_logger(),
      "★ Stored %u objects for visualization",
      msg->total_objects);
  }

  // 주기적 MarkerArray 발행
  void publishMarkers()
  {
    visualization_msgs::msg::MarkerArray marker_array;

    for (size_t i = 0; i < obstacles_.size(); ++i) {
      const auto &obs = obstacles_[i];
      visualization_msgs::msg::Marker m;
      m.header.frame_id    = "world";
      m.header.stamp       = this->now();
      m.ns                 = "obstacles";
      m.id                 = static_cast<int>(i);
      m.type               = visualization_msgs::msg::Marker::SPHERE;
      m.action             = visualization_msgs::msg::Marker::ADD;
      m.pose.position      = obs.center;
      m.pose.orientation.w = 1.0;
      // 스케일 = 반지름 * 2
      m.scale.x = obs.rx * 2;
      m.scale.y = obs.ry * 2;
      m.scale.z = obs.rz * 2;
      // 색상 (예시)
      m.color.r = 0.98;
      m.color.g = 0.84;
      m.color.a = 0.8;

      marker_array.markers.push_back(m);
    }

    marker_pub_->publish(marker_array);
  }

  rclcpp::Subscription<my_vision_msgs::msg::HarvestOrdering>::SharedPtr order_sub_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::vector<Obstacle> obstacles_;
};

 int main(int argc, char **argv)
 {
   rclcpp::init(argc, argv);
   rclcpp::spin(std::make_shared<MapNode>());
   rclcpp::shutdown();
   return 0;
 }
