// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vision_msgs/msg/detail/harvest_ordering__rosidl_typesupport_introspection_c.h"
#include "vision_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vision_msgs/msg/detail/harvest_ordering__functions.h"
#include "vision_msgs/msg/detail/harvest_ordering__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `crop_ids`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `objects`
#include "vision_msgs/msg/detected_crop.h"
// Member `objects`
#include "vision_msgs/msg/detail/detected_crop__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vision_msgs__msg__HarvestOrdering__init(message_memory);
}

void vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_fini_function(void * message_memory)
{
  vision_msgs__msg__HarvestOrdering__fini(message_memory);
}

size_t vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__crop_ids(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return member->size;
}

const void * vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__crop_ids(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__crop_ids(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__crop_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__crop_ids(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__crop_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__crop_ids(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

bool vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__crop_ids(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  rosidl_runtime_c__uint32__Sequence__fini(member);
  return rosidl_runtime_c__uint32__Sequence__init(member, size);
}

size_t vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__objects(
  const void * untyped_member)
{
  const vision_msgs__msg__DetectedCrop__Sequence * member =
    (const vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return member->size;
}

const void * vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__objects(
  const void * untyped_member, size_t index)
{
  const vision_msgs__msg__DetectedCrop__Sequence * member =
    (const vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__objects(
  void * untyped_member, size_t index)
{
  vision_msgs__msg__DetectedCrop__Sequence * member =
    (vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return &member->data[index];
}

void vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vision_msgs__msg__DetectedCrop * item =
    ((const vision_msgs__msg__DetectedCrop *)
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__objects(untyped_member, index));
  vision_msgs__msg__DetectedCrop * value =
    (vision_msgs__msg__DetectedCrop *)(untyped_value);
  *value = *item;
}

void vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vision_msgs__msg__DetectedCrop * item =
    ((vision_msgs__msg__DetectedCrop *)
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__objects(untyped_member, index));
  const vision_msgs__msg__DetectedCrop * value =
    (const vision_msgs__msg__DetectedCrop *)(untyped_value);
  *item = *value;
}

bool vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__objects(
  void * untyped_member, size_t size)
{
  vision_msgs__msg__DetectedCrop__Sequence * member =
    (vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  vision_msgs__msg__DetectedCrop__Sequence__fini(member);
  return vision_msgs__msg__DetectedCrop__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs__msg__HarvestOrdering, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "crop_ids",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs__msg__HarvestOrdering, crop_ids),  // bytes offset in struct
    NULL,  // default value
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__crop_ids,  // size() function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__crop_ids,  // get_const(index) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__crop_ids,  // get(index) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__crop_ids,  // fetch(index, &value) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__crop_ids,  // assign(index, value) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__crop_ids  // resize(index) function pointer
  },
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs__msg__HarvestOrdering, objects),  // bytes offset in struct
    NULL,  // default value
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__objects,  // size() function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__objects,  // get_const(index) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__objects,  // get(index) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__objects,  // fetch(index, &value) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__objects,  // assign(index, value) function pointer
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__objects  // resize(index) function pointer
  },
  {
    "total_objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vision_msgs__msg__HarvestOrdering, total_objects),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_members = {
  "vision_msgs__msg",  // message namespace
  "HarvestOrdering",  // message name
  4,  // number of fields
  sizeof(vision_msgs__msg__HarvestOrdering),
  vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array,  // message members
  vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_init_function,  // function to initialize message memory (memory has to be allocated)
  vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle = {
  0,
  &vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vision_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vision_msgs, msg, HarvestOrdering)() {
  vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vision_msgs, msg, DetectedCrop)();
  if (!vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle.typesupport_identifier) {
    vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
