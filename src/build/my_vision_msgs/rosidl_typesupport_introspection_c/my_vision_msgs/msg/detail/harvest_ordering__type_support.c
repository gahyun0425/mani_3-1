// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from my_vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "my_vision_msgs/msg/detail/harvest_ordering__rosidl_typesupport_introspection_c.h"
#include "my_vision_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "my_vision_msgs/msg/detail/harvest_ordering__functions.h"
#include "my_vision_msgs/msg/detail/harvest_ordering__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `crop_ids`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `objects`
#include "my_vision_msgs/msg/detected_crop.h"
// Member `objects`
#include "my_vision_msgs/msg/detail/detected_crop__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  my_vision_msgs__msg__HarvestOrdering__init(message_memory);
}

void my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_fini_function(void * message_memory)
{
  my_vision_msgs__msg__HarvestOrdering__fini(message_memory);
}

size_t my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__crop_ids(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return member->size;
}

const void * my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__crop_ids(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint32__Sequence * member =
    (const rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__crop_ids(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  return &member->data[index];
}

void my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__crop_ids(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint32_t * item =
    ((const uint32_t *)
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__crop_ids(untyped_member, index));
  uint32_t * value =
    (uint32_t *)(untyped_value);
  *value = *item;
}

void my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__crop_ids(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint32_t * item =
    ((uint32_t *)
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__crop_ids(untyped_member, index));
  const uint32_t * value =
    (const uint32_t *)(untyped_value);
  *item = *value;
}

bool my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__crop_ids(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint32__Sequence * member =
    (rosidl_runtime_c__uint32__Sequence *)(untyped_member);
  rosidl_runtime_c__uint32__Sequence__fini(member);
  return rosidl_runtime_c__uint32__Sequence__init(member, size);
}

size_t my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__objects(
  const void * untyped_member)
{
  const my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (const my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return member->size;
}

const void * my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__objects(
  const void * untyped_member, size_t index)
{
  const my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (const my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return &member->data[index];
}

void * my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__objects(
  void * untyped_member, size_t index)
{
  my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return &member->data[index];
}

void my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const my_vision_msgs__msg__DetectedCrop * item =
    ((const my_vision_msgs__msg__DetectedCrop *)
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__objects(untyped_member, index));
  my_vision_msgs__msg__DetectedCrop * value =
    (my_vision_msgs__msg__DetectedCrop *)(untyped_value);
  *value = *item;
}

void my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  my_vision_msgs__msg__DetectedCrop * item =
    ((my_vision_msgs__msg__DetectedCrop *)
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__objects(untyped_member, index));
  const my_vision_msgs__msg__DetectedCrop * value =
    (const my_vision_msgs__msg__DetectedCrop *)(untyped_value);
  *item = *value;
}

bool my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__objects(
  void * untyped_member, size_t size)
{
  my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  my_vision_msgs__msg__DetectedCrop__Sequence__fini(member);
  return my_vision_msgs__msg__DetectedCrop__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_vision_msgs__msg__HarvestOrdering, header),  // bytes offset in struct
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
    offsetof(my_vision_msgs__msg__HarvestOrdering, crop_ids),  // bytes offset in struct
    NULL,  // default value
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__crop_ids,  // size() function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__crop_ids,  // get_const(index) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__crop_ids,  // get(index) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__crop_ids,  // fetch(index, &value) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__crop_ids,  // assign(index, value) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__crop_ids  // resize(index) function pointer
  },
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_vision_msgs__msg__HarvestOrdering, objects),  // bytes offset in struct
    NULL,  // default value
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__size_function__HarvestOrdering__objects,  // size() function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_const_function__HarvestOrdering__objects,  // get_const(index) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__get_function__HarvestOrdering__objects,  // get(index) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__fetch_function__HarvestOrdering__objects,  // fetch(index, &value) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__assign_function__HarvestOrdering__objects,  // assign(index, value) function pointer
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__resize_function__HarvestOrdering__objects  // resize(index) function pointer
  },
  {
    "total_objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_vision_msgs__msg__HarvestOrdering, total_objects),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_members = {
  "my_vision_msgs__msg",  // message namespace
  "HarvestOrdering",  // message name
  4,  // number of fields
  sizeof(my_vision_msgs__msg__HarvestOrdering),
  my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array,  // message members
  my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_init_function,  // function to initialize message memory (memory has to be allocated)
  my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle = {
  0,
  &my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_my_vision_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_vision_msgs, msg, HarvestOrdering)() {
  my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_vision_msgs, msg, DetectedCrop)();
  if (!my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle.typesupport_identifier) {
    my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &my_vision_msgs__msg__HarvestOrdering__rosidl_typesupport_introspection_c__HarvestOrdering_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
