// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vision_msgs:msg/CropPose.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__CROP_POSE__STRUCT_H_
#define VISION_MSGS__MSG__DETAIL__CROP_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/CropPose in the package vision_msgs.
/**
  * vision_msgs/msg/CropPose.msg
 */
typedef struct vision_msgs__msg__CropPose
{
  double x;
  double y;
  double z;
} vision_msgs__msg__CropPose;

// Struct for a sequence of vision_msgs__msg__CropPose.
typedef struct vision_msgs__msg__CropPose__Sequence
{
  vision_msgs__msg__CropPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vision_msgs__msg__CropPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VISION_MSGS__MSG__DETAIL__CROP_POSE__STRUCT_H_
