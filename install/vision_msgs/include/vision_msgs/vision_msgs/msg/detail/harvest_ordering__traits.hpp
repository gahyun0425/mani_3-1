// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__TRAITS_HPP_
#define VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vision_msgs/msg/detail/harvest_ordering__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'objects'
#include "vision_msgs/msg/detail/detected_crop__traits.hpp"

namespace vision_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const HarvestOrdering & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: crop_ids
  {
    if (msg.crop_ids.size() == 0) {
      out << "crop_ids: []";
    } else {
      out << "crop_ids: [";
      size_t pending_items = msg.crop_ids.size();
      for (auto item : msg.crop_ids) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: objects
  {
    if (msg.objects.size() == 0) {
      out << "objects: []";
    } else {
      out << "objects: [";
      size_t pending_items = msg.objects.size();
      for (auto item : msg.objects) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: total_objects
  {
    out << "total_objects: ";
    rosidl_generator_traits::value_to_yaml(msg.total_objects, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const HarvestOrdering & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: crop_ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.crop_ids.size() == 0) {
      out << "crop_ids: []\n";
    } else {
      out << "crop_ids:\n";
      for (auto item : msg.crop_ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: objects
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.objects.size() == 0) {
      out << "objects: []\n";
    } else {
      out << "objects:\n";
      for (auto item : msg.objects) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: total_objects
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_objects: ";
    rosidl_generator_traits::value_to_yaml(msg.total_objects, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HarvestOrdering & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace vision_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vision_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vision_msgs::msg::HarvestOrdering & msg,
  std::ostream & out, size_t indentation = 0)
{
  vision_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vision_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vision_msgs::msg::HarvestOrdering & msg)
{
  return vision_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vision_msgs::msg::HarvestOrdering>()
{
  return "vision_msgs::msg::HarvestOrdering";
}

template<>
inline const char * name<vision_msgs::msg::HarvestOrdering>()
{
  return "vision_msgs/msg/HarvestOrdering";
}

template<>
struct has_fixed_size<vision_msgs::msg::HarvestOrdering>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vision_msgs::msg::HarvestOrdering>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vision_msgs::msg::HarvestOrdering>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__TRAITS_HPP_
