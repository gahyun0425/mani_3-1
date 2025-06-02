// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vision_msgs:msg/DetectedCropArray.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__STRUCT_H_
#define VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__STRUCT_H_

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
// Member 'objects'
#include "vision_msgs/msg/detail/detected_crop__struct.h"

/// Struct defined in msg/DetectedCropArray in the package vision_msgs.
/**
  * 감지된 객체들의 리스트
 */
typedef struct vision_msgs__msg__DetectedCropArray
{
  std_msgs__msg__Header header;
  vision_msgs__msg__DetectedCrop__Sequence objects;
  uint32_t total_objects;
} vision_msgs__msg__DetectedCropArray;

// Struct for a sequence of vision_msgs__msg__DetectedCropArray.
typedef struct vision_msgs__msg__DetectedCropArray__Sequence
{
  vision_msgs__msg__DetectedCropArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vision_msgs__msg__DetectedCropArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__STRUCT_H_
