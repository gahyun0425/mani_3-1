// NOLINT: This file starts with a BOM since it contain non-ASCII characters
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

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'cutting_point'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/CropPose in the package vision_msgs.
/**
  * 작물의 3D 포즈 정보
 */
typedef struct vision_msgs__msg__CropPose
{
  std_msgs__msg__Header header;
  /// 작물 ID (감지된 작물과 매칭)
  uint32_t crop_id;
  /// 3D 위치
  geometry_msgs__msg__Point cutting_point;
  /// 신뢰도
  float confidence;
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
