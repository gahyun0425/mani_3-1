// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from my_vision_msgs:msg/DetectedCropArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "my_vision_msgs/msg/detail/detected_crop_array__rosidl_typesupport_introspection_c.h"
#include "my_vision_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "my_vision_msgs/msg/detail/detected_crop_array__functions.h"
#include "my_vision_msgs/msg/detail/detected_crop_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `objects`
#include "my_vision_msgs/msg/detected_crop.h"
// Member `objects`
#include "my_vision_msgs/msg/detail/detected_crop__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  my_vision_msgs__msg__DetectedCropArray__init(message_memory);
}

void my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_fini_function(void * message_memory)
{
  my_vision_msgs__msg__DetectedCropArray__fini(message_memory);
}

size_t my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__size_function__DetectedCropArray__objects(
  const void * untyped_member)
{
  const my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (const my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return member->size;
}

const void * my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__get_const_function__DetectedCropArray__objects(
  const void * untyped_member, size_t index)
{
  const my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (const my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return &member->data[index];
}

void * my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__get_function__DetectedCropArray__objects(
  void * untyped_member, size_t index)
{
  my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  return &member->data[index];
}

void my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__fetch_function__DetectedCropArray__objects(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const my_vision_msgs__msg__DetectedCrop * item =
    ((const my_vision_msgs__msg__DetectedCrop *)
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__get_const_function__DetectedCropArray__objects(untyped_member, index));
  my_vision_msgs__msg__DetectedCrop * value =
    (my_vision_msgs__msg__DetectedCrop *)(untyped_value);
  *value = *item;
}

void my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__assign_function__DetectedCropArray__objects(
  void * untyped_member, size_t index, const void * untyped_value)
{
  my_vision_msgs__msg__DetectedCrop * item =
    ((my_vision_msgs__msg__DetectedCrop *)
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__get_function__DetectedCropArray__objects(untyped_member, index));
  const my_vision_msgs__msg__DetectedCrop * value =
    (const my_vision_msgs__msg__DetectedCrop *)(untyped_value);
  *item = *value;
}

bool my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__resize_function__DetectedCropArray__objects(
  void * untyped_member, size_t size)
{
  my_vision_msgs__msg__DetectedCrop__Sequence * member =
    (my_vision_msgs__msg__DetectedCrop__Sequence *)(untyped_member);
  my_vision_msgs__msg__DetectedCrop__Sequence__fini(member);
  return my_vision_msgs__msg__DetectedCrop__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_vision_msgs__msg__DetectedCropArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_vision_msgs__msg__DetectedCropArray, objects),  // bytes offset in struct
    NULL,  // default value
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__size_function__DetectedCropArray__objects,  // size() function pointer
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__get_const_function__DetectedCropArray__objects,  // get_const(index) function pointer
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__get_function__DetectedCropArray__objects,  // get(index) function pointer
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__fetch_function__DetectedCropArray__objects,  // fetch(index, &value) function pointer
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__assign_function__DetectedCropArray__objects,  // assign(index, value) function pointer
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__resize_function__DetectedCropArray__objects  // resize(index) function pointer
  },
  {
    "total_objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(my_vision_msgs__msg__DetectedCropArray, total_objects),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_members = {
  "my_vision_msgs__msg",  // message namespace
  "DetectedCropArray",  // message name
  3,  // number of fields
  sizeof(my_vision_msgs__msg__DetectedCropArray),
  my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_member_array,  // message members
  my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_init_function,  // function to initialize message memory (memory has to be allocated)
  my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_type_support_handle = {
  0,
  &my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_my_vision_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_vision_msgs, msg, DetectedCropArray)() {
  my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, my_vision_msgs, msg, DetectedCrop)();
  if (!my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_type_support_handle.typesupport_identifier) {
    my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &my_vision_msgs__msg__DetectedCropArray__rosidl_typesupport_introspection_c__DetectedCropArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
