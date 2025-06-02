// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__STRUCT_H_
#define VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__STRUCT_H_

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
// Member 'crop_ids'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'objects'
#include "vision_msgs/msg/detail/detected_crop__struct.h"

/// Struct defined in msg/HarvestOrdering in the package vision_msgs.
/**
  * 수확 순서 정보
 */
typedef struct vision_msgs__msg__HarvestOrdering
{
  std_msgs__msg__Header header;
  /// 수확할 작물 ID 순서
  /// 우선순위만 넘어옴
  rosidl_runtime_c__uint32__Sequence crop_ids;
  /// 작물 객체 정보
  /// 1번 xyz, 2번 xyz 이런 식으로 순서 맞춰서 좌표값 넘어옴
  vision_msgs__msg__DetectedCrop__Sequence objects;
  /// 총 작물 수
  uint32_t total_objects;
} vision_msgs__msg__HarvestOrdering;

// Struct for a sequence of vision_msgs__msg__HarvestOrdering.
typedef struct vision_msgs__msg__HarvestOrdering__Sequence
{
  vision_msgs__msg__HarvestOrdering * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vision_msgs__msg__HarvestOrdering__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__STRUCT_H_
