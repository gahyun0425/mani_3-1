// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__FUNCTIONS_H_
#define VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vision_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "vision_msgs/msg/detail/harvest_ordering__struct.h"

/// Initialize msg/HarvestOrdering message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vision_msgs__msg__HarvestOrdering
 * )) before or use
 * vision_msgs__msg__HarvestOrdering__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
bool
vision_msgs__msg__HarvestOrdering__init(vision_msgs__msg__HarvestOrdering * msg);

/// Finalize msg/HarvestOrdering message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
void
vision_msgs__msg__HarvestOrdering__fini(vision_msgs__msg__HarvestOrdering * msg);

/// Create msg/HarvestOrdering message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vision_msgs__msg__HarvestOrdering__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
vision_msgs__msg__HarvestOrdering *
vision_msgs__msg__HarvestOrdering__create();

/// Destroy msg/HarvestOrdering message.
/**
 * It calls
 * vision_msgs__msg__HarvestOrdering__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
void
vision_msgs__msg__HarvestOrdering__destroy(vision_msgs__msg__HarvestOrdering * msg);

/// Check for msg/HarvestOrdering message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
bool
vision_msgs__msg__HarvestOrdering__are_equal(const vision_msgs__msg__HarvestOrdering * lhs, const vision_msgs__msg__HarvestOrdering * rhs);

/// Copy a msg/HarvestOrdering message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
bool
vision_msgs__msg__HarvestOrdering__copy(
  const vision_msgs__msg__HarvestOrdering * input,
  vision_msgs__msg__HarvestOrdering * output);

/// Initialize array of msg/HarvestOrdering messages.
/**
 * It allocates the memory for the number of elements and calls
 * vision_msgs__msg__HarvestOrdering__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
bool
vision_msgs__msg__HarvestOrdering__Sequence__init(vision_msgs__msg__HarvestOrdering__Sequence * array, size_t size);

/// Finalize array of msg/HarvestOrdering messages.
/**
 * It calls
 * vision_msgs__msg__HarvestOrdering__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
void
vision_msgs__msg__HarvestOrdering__Sequence__fini(vision_msgs__msg__HarvestOrdering__Sequence * array);

/// Create array of msg/HarvestOrdering messages.
/**
 * It allocates the memory for the array and calls
 * vision_msgs__msg__HarvestOrdering__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
vision_msgs__msg__HarvestOrdering__Sequence *
vision_msgs__msg__HarvestOrdering__Sequence__create(size_t size);

/// Destroy array of msg/HarvestOrdering messages.
/**
 * It calls
 * vision_msgs__msg__HarvestOrdering__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
void
vision_msgs__msg__HarvestOrdering__Sequence__destroy(vision_msgs__msg__HarvestOrdering__Sequence * array);

/// Check for msg/HarvestOrdering message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
bool
vision_msgs__msg__HarvestOrdering__Sequence__are_equal(const vision_msgs__msg__HarvestOrdering__Sequence * lhs, const vision_msgs__msg__HarvestOrdering__Sequence * rhs);

/// Copy an array of msg/HarvestOrdering messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vision_msgs
bool
vision_msgs__msg__HarvestOrdering__Sequence__copy(
  const vision_msgs__msg__HarvestOrdering__Sequence * input,
  vision_msgs__msg__HarvestOrdering__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__FUNCTIONS_H_
