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

class Init_CropPose_z
{
public:
  explicit Init_CropPose_z(::vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  ::vision_msgs::msg::CropPose z(::vision_msgs::msg::CropPose::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_y
{
public:
  explicit Init_CropPose_y(::vision_msgs::msg::CropPose & msg)
  : msg_(msg)
  {}
  Init_CropPose_z y(::vision_msgs::msg::CropPose::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_CropPose_z(msg_);
  }

private:
  ::vision_msgs::msg::CropPose msg_;
};

class Init_CropPose_x
{
public:
  Init_CropPose_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CropPose_y x(::vision_msgs::msg::CropPose::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_CropPose_y(msg_);
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
  return vision_msgs::msg::builder::Init_CropPose_x();
}

}  // namespace vision_msgs

#endif  // VISION_MSGS__MSG__DETAIL__CROP_POSE__BUILDER_HPP_
