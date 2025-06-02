// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__BUILDER_HPP_
#define VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vision_msgs/msg/detail/harvest_ordering__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vision_msgs
{

namespace msg
{

namespace builder
{

class Init_HarvestOrdering_total_objects
{
public:
  explicit Init_HarvestOrdering_total_objects(::vision_msgs::msg::HarvestOrdering & msg)
  : msg_(msg)
  {}
  ::vision_msgs::msg::HarvestOrdering total_objects(::vision_msgs::msg::HarvestOrdering::_total_objects_type arg)
  {
    msg_.total_objects = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vision_msgs::msg::HarvestOrdering msg_;
};

class Init_HarvestOrdering_objects
{
public:
  explicit Init_HarvestOrdering_objects(::vision_msgs::msg::HarvestOrdering & msg)
  : msg_(msg)
  {}
  Init_HarvestOrdering_total_objects objects(::vision_msgs::msg::HarvestOrdering::_objects_type arg)
  {
    msg_.objects = std::move(arg);
    return Init_HarvestOrdering_total_objects(msg_);
  }

private:
  ::vision_msgs::msg::HarvestOrdering msg_;
};

class Init_HarvestOrdering_crop_ids
{
public:
  explicit Init_HarvestOrdering_crop_ids(::vision_msgs::msg::HarvestOrdering & msg)
  : msg_(msg)
  {}
  Init_HarvestOrdering_objects crop_ids(::vision_msgs::msg::HarvestOrdering::_crop_ids_type arg)
  {
    msg_.crop_ids = std::move(arg);
    return Init_HarvestOrdering_objects(msg_);
  }

private:
  ::vision_msgs::msg::HarvestOrdering msg_;
};

class Init_HarvestOrdering_header
{
public:
  Init_HarvestOrdering_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HarvestOrdering_crop_ids header(::vision_msgs::msg::HarvestOrdering::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HarvestOrdering_crop_ids(msg_);
  }

private:
  ::vision_msgs::msg::HarvestOrdering msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vision_msgs::msg::HarvestOrdering>()
{
  return vision_msgs::msg::builder::Init_HarvestOrdering_header();
}

}  // namespace vision_msgs

#endif  // VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__BUILDER_HPP_
