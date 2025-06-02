// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vision_msgs:msg/CropPose.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__CROP_POSE__BUILDER_HPP_
#define VISION_MSGS__MSG__DETAIL__CROP_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vision_msgs/msg/detail/crop_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vision_msgs
{

namespace msg
{

namespace builder
{

class Init_CropPose_confidence
{
public:
  explicit Init_CropPose_confidence(::vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  ::vision_msgs::msg::CropPose confidence(::vision_msgs::msg::CropPose::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_cutting_point
{
public:
  explicit Init_CropPose_cutting_point(::vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  Init_CropPose_confidence cutting_point(::vision_msgs::msg::CropPose::_cutting_point_type arg)
  {
    msg_.cutting_point = std::move(arg);
    return Init_CropPose_confidence(msg_);
  }

private:
  ::vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_crop_id
{
public:
  explicit Init_CropPose_crop_id(::vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  Init_CropPose_cutting_point crop_id(::vision_msgs::msg::CropPose::_crop_id_type arg)
  {
    msg_.crop_id = std::move(arg);
    return Init_CropPose_cutting_point(msg_);
  }

private:
  ::vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_header
{
public:
  Init_CropPose_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CropPose_crop_id header(::vision_msgs::msg::CropPose::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CropPose_crop_id(msg_);
  }

private:
  ::vision_msgs::msg::CropPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vision_msgs::msg::CropPose>()
{
  return vision_msgs::msg::builder::Init_CropPose_header();
}

}  // namespace vision_msgs

#endif  // VISION_MSGS__MSG__DETAIL__CROP_POSE__BUILDER_HPP_
