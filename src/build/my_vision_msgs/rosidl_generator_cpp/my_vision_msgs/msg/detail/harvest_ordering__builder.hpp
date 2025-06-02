// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#ifndef MY_VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__BUILDER_HPP_
#define MY_VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_vision_msgs/msg/detail/harvest_ordering__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_vision_msgs
{

namespace msg
{

namespace builder
{

class Init_HarvestOrdering_total_objects
{
public:
  explicit Init_HarvestOrdering_total_objects(::my_vision_msgs::msg::HarvestOrdering & msg)
  : msg_(msg)
  {}
  ::my_vision_msgs::msg::HarvestOrdering total_objects(::my_vision_msgs::msg::HarvestOrdering::_total_objects_type arg)
  {
    msg_.total_objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_vision_msgs::msg::HarvestOrdering msg_;
};

class Init_HarvestOrdering_objects
{
public:
  explicit Init_HarvestOrdering_objects(::my_vision_msgs::msg::HarvestOrdering & msg)
  : msg_(msg)
  {}
  Init_HarvestOrdering_total_objects objects(::my_vision_msgs::msg::HarvestOrdering::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return Init_HarvestOrdering_total_objects(msg_);
  }

private:
  ::my_vision_msgs::msg::HarvestOrdering msg_;
};

class Init_HarvestOrdering_crop_ids
{
public:
  explicit Init_HarvestOrdering_crop_ids(::my_vision_msgs::msg::HarvestOrdering & msg)
  : msg_(msg)
  {}
  Init_HarvestOrdering_objects crop_ids(::my_vision_msgs::msg::HarvestOrdering::_crop_ids_type arg)
  {
    msg_.crop_ids = std::move(arg);
    return Init_HarvestOrdering_objects(msg_);
  }

private:
  ::my_vision_msgs::msg::HarvestOrdering msg_;
};

class Init_HarvestOrdering_header
{
public:
  Init_HarvestOrdering_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HarvestOrdering_crop_ids header(::my_vision_msgs::msg::HarvestOrdering::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HarvestOrdering_crop_ids(msg_);
  }

private:
  ::my_vision_msgs::msg::HarvestOrdering msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_vision_msgs::msg::HarvestOrdering>()
{
  return my_vision_msgs::msg::builder::Init_HarvestOrdering_header();
}

}  // namespace my_vision_msgs

#endif  // MY_VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__BUILDER_HPP_
