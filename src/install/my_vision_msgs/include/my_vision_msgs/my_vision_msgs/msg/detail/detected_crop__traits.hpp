// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_vision_msgs:msg/DetectedCrop.idl
// generated code does not contain a copyright notice

#ifndef MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP__TRAITS_HPP_
#define MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_vision_msgs/msg/detail/detected_crop__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace my_vision_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const DetectedCrop & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DetectedCrop & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DetectedCrop & msg, bool use_flow_style = false)
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

}  // namespace my_vision_msgs

namespace rosidl_generator_traits
{

[[deprecated("use my_vision_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_vision_msgs::msg::DetectedCrop & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_vision_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_vision_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_vision_msgs::msg::DetectedCrop & msg)
{
  return my_vision_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_vision_msgs::msg::DetectedCrop>()
{
  return "my_vision_msgs::msg::DetectedCrop";
}

template<>
inline const char * name<my_vision_msgs::msg::DetectedCrop>()
{
  return "my_vision_msgs/msg/DetectedCrop";
}

template<>
struct has_fixed_size<my_vision_msgs::msg::DetectedCrop>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_vision_msgs::msg::DetectedCrop>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_vision_msgs::msg::DetectedCrop>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP__TRAITS_HPP_
