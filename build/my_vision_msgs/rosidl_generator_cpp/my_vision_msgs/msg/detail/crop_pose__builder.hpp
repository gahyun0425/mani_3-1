// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_vision_msgs:msg/CropPose.idl
// generated code does not contain a copyright notice

#ifndef MY_VISION_MSGS__MSG__DETAIL__CROP_POSE__BUILDER_HPP_
#define MY_VISION_MSGS__MSG__DETAIL__CROP_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_vision_msgs/msg/detail/crop_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_vision_msgs
{

namespace msg
{

namespace builder
{

class Init_CropPose_confidence
{
public:
  explicit Init_CropPose_confidence(::my_vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  ::my_vision_msgs::msg::CropPose confidence(::my_vision_msgs::msg::CropPose::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_cutting_point
{
public:
  explicit Init_CropPose_cutting_point(::my_vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  Init_CropPose_confidence cutting_point(::my_vision_msgs::msg::CropPose::_cutting_point_type arg)
  {
    msg_.cutting_point = std::move(arg);
    return Init_CropPose_confidence(msg_);
  }

private:
  ::my_vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_crop_id
{
public:
  explicit Init_CropPose_crop_id(::my_vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  Init_CropPose_cutting_point crop_id(::my_vision_msgs::msg::CropPose::_crop_id_type arg)
  {
    msg_.crop_id = std::move(arg);
    return Init_CropPose_cutting_point(msg_);
  }

private:
  ::my_vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_header
{
public:
  Init_CropPose_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CropPose_crop_id header(::my_vision_msgs::msg::CropPose::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CropPose_crop_id(msg_);
  }

private:
  ::my_vision_msgs::msg::CropPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_vision_msgs::msg::CropPose>()
{
  return my_vision_msgs::msg::builder::Init_CropPose_header();
}

}  // namespace my_vision_msgs

#endif  // MY_VISION_MSGS__MSG__DETAIL__CROP_POSE__BUILDER_HPP_
