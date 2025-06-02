// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice
#include "my_vision_msgs/msg/detail/harvest_ordering__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `crop_ids`
#include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `objects`
#include "my_vision_msgs/msg/detail/detected_crop__functions.h"

bool
my_vision_msgs__msg__HarvestOrdering__init(my_vision_msgs__msg__HarvestOrdering * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    my_vision_msgs__msg__HarvestOrdering__fini(msg);
    return false;
  }
  // crop_ids
  if (!rosidl_runtime_c__uint32__Sequence__init(&msg->crop_ids, 0)) {
    my_vision_msgs__msg__HarvestOrdering__fini(msg);
    return false;
  }
  // objects
  if (!my_vision_msgs__msg__DetectedCrop__Sequence__init(&msg->objects, 0)) {
    my_vision_msgs__msg__HarvestOrdering__fini(msg);
    return false;
  }
  // total_objects
  return true;
}

void
my_vision_msgs__msg__HarvestOrdering__fini(my_vision_msgs__msg__HarvestOrdering * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // crop_ids
  rosidl_runtime_c__uint32__Sequence__fini(&msg->crop_ids);
  // objects
  my_vision_msgs__msg__DetectedCrop__Sequence__fini(&msg->objects);
  // total_objects
}

bool
my_vision_msgs__msg__HarvestOrdering__are_equal(const my_vision_msgs__msg__HarvestOrdering * lhs, const my_vision_msgs__msg__HarvestOrdering * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // crop_ids
  if (!rosidl_runtime_c__uint32__Sequence__are_equal(
      &(lhs->crop_ids), &(rhs->crop_ids)))
  {
    return false;
  }
  // objects
  if (!my_vision_msgs__msg__DetectedCrop__Sequence__are_equal(
      &(lhs->objects), &(rhs->objects)))
  {
    return false;
  }
  // total_objects
  if (lhs->total_objects != rhs->total_objects) {
    return false;
  }
  return true;
}

bool
my_vision_msgs__msg__HarvestOrdering__copy(
  const my_vision_msgs__msg__HarvestOrdering * input,
  my_vision_msgs__msg__HarvestOrdering * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // crop_ids
  if (!rosidl_runtime_c__uint32__Sequence__copy(
      &(input->crop_ids), &(output->crop_ids)))
  {
    return false;
  }
  // objects
  if (!my_vision_msgs__msg__DetectedCrop__Sequence__copy(
      &(input->objects), &(output->objects)))
  {
    return false;
  }
  // total_objects
  output->total_objects = input->total_objects;
  return true;
}

my_vision_msgs__msg__HarvestOrdering *
my_vision_msgs__msg__HarvestOrdering__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_vision_msgs__msg__HarvestOrdering * msg = (my_vision_msgs__msg__HarvestOrdering *)allocator.allocate(sizeof(my_vision_msgs__msg__HarvestOrdering), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_vision_msgs__msg__HarvestOrdering));
  bool success = my_vision_msgs__msg__HarvestOrdering__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_vision_msgs__msg__HarvestOrdering__destroy(my_vision_msgs__msg__HarvestOrdering * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_vision_msgs__msg__HarvestOrdering__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_vision_msgs__msg__HarvestOrdering__Sequence__init(my_vision_msgs__msg__HarvestOrdering__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_vision_msgs__msg__HarvestOrdering * data = NULL;

  if (size) {
    data = (my_vision_msgs__msg__HarvestOrdering *)allocator.zero_allocate(size, sizeof(my_vision_msgs__msg__HarvestOrdering), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_vision_msgs__msg__HarvestOrdering__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_vision_msgs__msg__HarvestOrdering__fini(&data[i - 1]);
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
my_vision_msgs__msg__HarvestOrdering__Sequence__fini(my_vision_msgs__msg__HarvestOrdering__Sequence * array)
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
      my_vision_msgs__msg__HarvestOrdering__fini(&array->data[i]);
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

my_vision_msgs__msg__HarvestOrdering__Sequence *
my_vision_msgs__msg__HarvestOrdering__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_vision_msgs__msg__HarvestOrdering__Sequence * array = (my_vision_msgs__msg__HarvestOrdering__Sequence *)allocator.allocate(sizeof(my_vision_msgs__msg__HarvestOrdering__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_vision_msgs__msg__HarvestOrdering__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_vision_msgs__msg__HarvestOrdering__Sequence__destroy(my_vision_msgs__msg__HarvestOrdering__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_vision_msgs__msg__HarvestOrdering__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_vision_msgs__msg__HarvestOrdering__Sequence__are_equal(const my_vision_msgs__msg__HarvestOrdering__Sequence * lhs, const my_vision_msgs__msg__HarvestOrdering__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_vision_msgs__msg__HarvestOrdering__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_vision_msgs__msg__HarvestOrdering__Sequence__copy(
  const my_vision_msgs__msg__HarvestOrdering__Sequence * input,
  my_vision_msgs__msg__HarvestOrdering__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_vision_msgs__msg__HarvestOrdering);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_vision_msgs__msg__HarvestOrdering * data =
      (my_vision_msgs__msg__HarvestOrdering *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_vision_msgs__msg__HarvestOrdering__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_vision_msgs__msg__HarvestOrdering__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_vision_msgs__msg__HarvestOrdering__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
