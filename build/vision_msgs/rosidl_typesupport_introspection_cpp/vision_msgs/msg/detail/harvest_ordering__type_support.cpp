// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vision_msgs/msg/detail/harvest_ordering__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vision_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void HarvestOrdering_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vision_msgs::msg::HarvestOrdering(_init);
}

void HarvestOrdering_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vision_msgs::msg::HarvestOrdering *>(message_memory);
  typed_message->~HarvestOrdering();
}

size_t size_function__HarvestOrdering__crop_ids(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__HarvestOrdering__crop_ids(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__HarvestOrdering__crop_ids(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__HarvestOrdering__crop_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uint32_t *>(
    get_const_function__HarvestOrdering__crop_ids(untyped_member, index));
  auto & value = *reinterpret_cast<uint32_t *>(untyped_value);
  value = item;
}

void assign_function__HarvestOrdering__crop_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uint32_t *>(
    get_function__HarvestOrdering__crop_ids(untyped_member, index));
  const auto & value = *reinterpret_cast<const uint32_t *>(untyped_value);
  item = value;
}

void resize_function__HarvestOrdering__crop_ids(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint32_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__HarvestOrdering__objects(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<vision_msgs::msg::DetectedCrop> *>(untyped_member);
  return member->size();
}

const void * get_const_function__HarvestOrdering__objects(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<vision_msgs::msg::DetectedCrop> *>(untyped_member);
  return &member[index];
}

void * get_function__HarvestOrdering__objects(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<vision_msgs::msg::DetectedCrop> *>(untyped_member);
  return &member[index];
}

void fetch_function__HarvestOrdering__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const vision_msgs::msg::DetectedCrop *>(
    get_const_function__HarvestOrdering__objects(untyped_member, index));
  auto & value = *reinterpret_cast<vision_msgs::msg::DetectedCrop *>(untyped_value);
  value = item;
}

void assign_function__HarvestOrdering__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<vision_msgs::msg::DetectedCrop *>(
    get_function__HarvestOrdering__objects(untyped_member, index));
  const auto & value = *reinterpret_cast<const vision_msgs::msg::DetectedCrop *>(untyped_value);
  item = value;
}

void resize_function__HarvestOrdering__objects(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<vision_msgs::msg::DetectedCrop> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember HarvestOrdering_message_member_array[4] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs::msg::HarvestOrdering, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "crop_ids",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs::msg::HarvestOrdering, crop_ids),  // bytes offset in struct
    nullptr,  // default value
    size_function__HarvestOrdering__crop_ids,  // size() function pointer
    get_const_function__HarvestOrdering__crop_ids,  // get_const(index) function pointer
    get_function__HarvestOrdering__crop_ids,  // get(index) function pointer
    fetch_function__HarvestOrdering__crop_ids,  // fetch(index, &value) function pointer
    assign_function__HarvestOrdering__crop_ids,  // assign(index, value) function pointer
    resize_function__HarvestOrdering__crop_ids  // resize(index) function pointer
  },
  {
    "objects",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<vision_msgs::msg::DetectedCrop>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs::msg::HarvestOrdering, objects),  // bytes offset in struct
    nullptr,  // default value
    size_function__HarvestOrdering__objects,  // size() function pointer
    get_const_function__HarvestOrdering__objects,  // get_const(index) function pointer
    get_function__HarvestOrdering__objects,  // get(index) function pointer
    fetch_function__HarvestOrdering__objects,  // fetch(index, &value) function pointer
    assign_function__HarvestOrdering__objects,  // assign(index, value) function pointer
    resize_function__HarvestOrdering__objects  // resize(index) function pointer
  },
  {
    "total_objects",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs::msg::HarvestOrdering, total_objects),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers HarvestOrdering_message_members = {
  "vision_msgs::msg",  // message namespace
  "HarvestOrdering",  // message name
  4,  // number of fields
  sizeof(vision_msgs::msg::HarvestOrdering),
  HarvestOrdering_message_member_array,  // message members
  HarvestOrdering_init_function,  // function to initialize message memory (memory has to be allocated)
  HarvestOrdering_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t HarvestOrdering_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &HarvestOrdering_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace vision_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vision_msgs::msg::HarvestOrdering>()
{
  return &::vision_msgs::msg::rosidl_typesupport_introspection_cpp::HarvestOrdering_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vision_msgs, msg, HarvestOrdering)() {
  return &::vision_msgs::msg::rosidl_typesupport_introspection_cpp::HarvestOrdering_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
