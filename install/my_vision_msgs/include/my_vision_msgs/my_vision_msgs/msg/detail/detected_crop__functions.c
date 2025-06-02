// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_vision_msgs:msg/DetectedCrop.idl
// generated code does not contain a copyright notice
#include "my_vision_msgs/msg/detail/detected_crop__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
my_vision_msgs__msg__DetectedCrop__init(my_vision_msgs__msg__DetectedCrop * msg)
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
my_vision_msgs__msg__DetectedCrop__fini(my_vision_msgs__msg__DetectedCrop * msg)
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
my_vision_msgs__msg__DetectedCrop__are_equal(const my_vision_msgs__msg__DetectedCrop * lhs, const my_vision_msgs__msg__DetectedCrop * rhs)
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
my_vision_msgs__msg__DetectedCrop__copy(
  const my_vision_msgs__msg__DetectedCrop * input,
  my_vision_msgs__msg__DetectedCrop * output)
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

my_vision_msgs__msg__DetectedCrop *
my_vision_msgs__msg__DetectedCrop__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_vision_msgs__msg__DetectedCrop * msg = (my_vision_msgs__msg__DetectedCrop *)allocator.allocate(sizeof(my_vision_msgs__msg__DetectedCrop), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_vision_msgs__msg__DetectedCrop));
  bool success = my_vision_msgs__msg__DetectedCrop__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_vision_msgs__msg__DetectedCrop__destroy(my_vision_msgs__msg__DetectedCrop * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_vision_msgs__msg__DetectedCrop__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_vision_msgs__msg__DetectedCrop__Sequence__init(my_vision_msgs__msg__DetectedCrop__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_vision_msgs__msg__DetectedCrop * data = NULL;

  if (size) {
    data = (my_vision_msgs__msg__DetectedCrop *)allocator.zero_allocate(size, sizeof(my_vision_msgs__msg__DetectedCrop), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_vision_msgs__msg__DetectedCrop__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_vision_msgs__msg__DetectedCrop__fini(&data[i - 1]);
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
my_vision_msgs__msg__DetectedCrop__Sequence__fini(my_vision_msgs__msg__DetectedCrop__Sequence * array)
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
      my_vision_msgs__msg__DetectedCrop__fini(&array->data[i]);
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

my_vision_msgs__msg__DetectedCrop__Sequence *
my_vision_msgs__msg__DetectedCrop__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_vision_msgs__msg__DetectedCrop__Sequence * array = (my_vision_msgs__msg__DetectedCrop__Sequence *)allocator.allocate(sizeof(my_vision_msgs__msg__DetectedCrop__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_vision_msgs__msg__DetectedCrop__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_vision_msgs__msg__DetectedCrop__Sequence__destroy(my_vision_msgs__msg__DetectedCrop__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_vision_msgs__msg__DetectedCrop__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_vision_msgs__msg__DetectedCrop__Sequence__are_equal(const my_vision_msgs__msg__DetectedCrop__Sequence * lhs, const my_vision_msgs__msg__DetectedCrop__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_vision_msgs__msg__DetectedCrop__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_vision_msgs__msg__DetectedCrop__Sequence__copy(
  const my_vision_msgs__msg__DetectedCrop__Sequence * input,
  my_vision_msgs__msg__DetectedCrop__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_vision_msgs__msg__DetectedCrop);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_vision_msgs__msg__DetectedCrop * data =
      (my_vision_msgs__msg__DetectedCrop *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_vision_msgs__msg__DetectedCrop__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_vision_msgs__msg__DetectedCrop__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_vision_msgs__msg__DetectedCrop__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
