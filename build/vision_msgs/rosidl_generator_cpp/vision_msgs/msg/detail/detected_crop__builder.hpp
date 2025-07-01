// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vision_msgs:msg/DetectedCrop.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__DETECTED_CROP__BUILDER_HPP_
#define VISION_MSGS__MSG__DETAIL__DETECTED_CROP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vision_msgs/msg/detail/detected_crop__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vision_msgs
{

namespace msg
{

namespace builder
{

class Init_DetectedCrop_z
{
public:
  explicit Init_DetectedCrop_z(::vision_msgs::msg::DetectedCrop & msg)
  : msg_(msg)
  {}
  ::vision_msgs::msg::DetectedCrop z(::vision_msgs::msg::DetectedCrop::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vision_msgs::msg::DetectedCrop msg_;
};

class Init_DetectedCrop_y
{
public:
  explicit Init_DetectedCrop_y(::vision_msgs::msg::DetectedCrop & msg)
  : msg_(msg)
  {}
  Init_DetectedCrop_z y(::vision_msgs::msg::DetectedCrop::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_DetectedCrop_z(msg_);
  }

private:
  ::vision_msgs::msg::DetectedCrop msg_;
};

class Init_DetectedCrop_x
{
public:
  explicit Init_DetectedCrop_x(::vision_msgs::msg::DetectedCrop & msg)
  : msg_(msg)
  {}
  Init_DetectedCrop_y x(::vision_msgs::msg::DetectedCrop::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_DetectedCrop_y(msg_);
  }

private:
  ::vision_msgs::msg::DetectedCrop msg_;
};

class Init_DetectedCrop_id
{
public:
  Init_DetectedCrop_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectedCrop_x id(::vision_msgs::msg::DetectedCrop::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_DetectedCrop_x(msg_);
  }

private:
  ::vision_msgs::msg::DetectedCrop msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vision_msgs::msg::DetectedCrop>()
{
  return vision_msgs::msg::builder::Init_DetectedCrop_id();
}

}  // namespace vision_msgs

#endif  // VISION_MSGS__MSG__DETAIL__DETECTED_CROP__BUILDER_HPP_
