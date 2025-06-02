// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_vision_msgs:msg/DetectedCropArray.idl
// generated code does not contain a copyright notice

#ifndef MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__BUILDER_HPP_
#define MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_vision_msgs/msg/detail/detected_crop_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_vision_msgs
{

namespace msg
{

namespace builder
{

class Init_DetectedCropArray_total_objects
{
public:
  explicit Init_DetectedCropArray_total_objects(::my_vision_msgs::msg::DetectedCropArray & msg)
  : msg_(msg)
  {}
  ::my_vision_msgs::msg::DetectedCropArray total_objects(::my_vision_msgs::msg::DetectedCropArray::_total_objects_type arg)
  {
    msg_.total_objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_vision_msgs::msg::DetectedCropArray msg_;
};

class Init_DetectedCropArray_objects
{
public:
  explicit Init_DetectedCropArray_objects(::my_vision_msgs::msg::DetectedCropArray & msg)
  : msg_(msg)
  {}
  Init_DetectedCropArray_total_objects objects(::my_vision_msgs::msg::DetectedCropArray::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return Init_DetectedCropArray_total_objects(msg_);
  }

private:
  ::my_vision_msgs::msg::DetectedCropArray msg_;
};

class Init_DetectedCropArray_header
{
public:
  Init_DetectedCropArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectedCropArray_objects header(::my_vision_msgs::msg::DetectedCropArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DetectedCropArray_objects(msg_);
  }

private:
  ::my_vision_msgs::msg::DetectedCropArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_vision_msgs::msg::DetectedCropArray>()
{
  return my_vision_msgs::msg::builder::Init_DetectedCropArray_header();
}

}  // namespace my_vision_msgs

#endif  // MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__BUILDER_HPP_
