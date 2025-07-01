// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vision_msgs:msg/DetectedCrop.idl
// generated code does not contain a copyright notice
#include "vision_msgs/msg/detail/detected_crop__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vision_msgs__msg__DetectedCrop__init(vision_msgs__msg__DetectedCrop * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // x
  // y
  // z
  return true;
}

void
vision_msgs__msg__DetectedCrop__fini(vision_msgs__msg__DetectedCrop * msg)
{
  if (!msg) {
    return;
  }
  // id
  // x
  // y
  // z
}

bool
vision_msgs__msg__DetectedCrop__are_equal(const vision_msgs__msg__DetectedCrop * lhs, const vision_msgs__msg__DetectedCrop * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  return true;
}

bool
vision_msgs__msg__DetectedCrop__copy(
  const vision_msgs__msg__DetectedCrop * input,
  vision_msgs__msg__DetectedCrop * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  return true;
}

vision_msgs__msg__DetectedCrop *
vision_msgs__msg__DetectedCrop__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vision_msgs__msg__DetectedCrop * msg = (vision_msgs__msg__DetectedCrop *)allocator.allocate(sizeof(vision_msgs__msg__DetectedCrop), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vision_msgs__msg__DetectedCrop));
  bool success = vision_msgs__msg__DetectedCrop__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vision_msgs__msg__DetectedCrop__destroy(vision_msgs__msg__DetectedCrop * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vision_msgs__msg__DetectedCrop__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vision_msgs__msg__DetectedCrop__Sequence__init(vision_msgs__msg__DetectedCrop__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vision_msgs__msg__DetectedCrop * data = NULL;

  if (size) {
    data = (vision_msgs__msg__DetectedCrop *)allocator.zero_allocate(size, sizeof(vision_msgs__msg__DetectedCrop), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vision_msgs__msg__DetectedCrop__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vision_msgs__msg__DetectedCrop__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vision_msgs__msg__DetectedCrop__Sequence__fini(vision_msgs__msg__DetectedCrop__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vision_msgs__msg__DetectedCrop__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vision_msgs__msg__DetectedCrop__Sequence *
vision_msgs__msg__DetectedCrop__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vision_msgs__msg__DetectedCrop__Sequence * array = (vision_msgs__msg__DetectedCrop__Sequence *)allocator.allocate(sizeof(vision_msgs__msg__DetectedCrop__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vision_msgs__msg__DetectedCrop__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vision_msgs__msg__DetectedCrop__Sequence__destroy(vision_msgs__msg__DetectedCrop__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vision_msgs__msg__DetectedCrop__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vision_msgs__msg__DetectedCrop__Sequence__are_equal(const vision_msgs__msg__DetectedCrop__Sequence * lhs, const vision_msgs__msg__DetectedCrop__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vision_msgs__msg__DetectedCrop__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vision_msgs__msg__DetectedCrop__Sequence__copy(
  const vision_msgs__msg__DetectedCrop__Sequence * input,
  vision_msgs__msg__DetectedCrop__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vision_msgs__msg__DetectedCrop);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vision_msgs__msg__DetectedCrop * data =
      (vision_msgs__msg__DetectedCrop *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vision_msgs__msg__DetectedCrop__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vision_msgs__msg__DetectedCrop__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vision_msgs__msg__DetectedCrop__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
