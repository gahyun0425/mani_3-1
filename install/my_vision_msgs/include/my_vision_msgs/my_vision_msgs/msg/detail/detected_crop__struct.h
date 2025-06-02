// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_vision_msgs:msg/DetectedCrop.idl
// generated code does not contain a copyright notice

#ifndef MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP__STRUCT_H_
#define MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/DetectedCrop in the package my_vision_msgs.
/**
  * 개별 감지 객체
 */
typedef struct my_vision_msgs__msg__DetectedCrop
{
  /// 객체 번호 (예: 1, 2, 3 ...)
  uint32_t id;
  /// Calibration된 X 좌표
  double x;
  /// Calibration된 Y 좌표
  double y;
  /// Calibration된 Z 좌표
  double z;
} my_vision_msgs__msg__DetectedCrop;

// Struct for a sequence of my_vision_msgs__msg__DetectedCrop.
typedef struct my_vision_msgs__msg__DetectedCrop__Sequence
{
  my_vision_msgs__msg__DetectedCrop * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_vision_msgs__msg__DetectedCrop__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP__STRUCT_H_
