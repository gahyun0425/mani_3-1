// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from my_vision_msgs:msg/DetectedCropArray.idl
// generated code does not contain a copyright notice

#ifndef MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__FUNCTIONS_H_
#define MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "my_vision_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "my_vision_msgs/msg/detail/detected_crop_array__struct.h"

/// Initialize msg/DetectedCropArray message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * my_vision_msgs__msg__DetectedCropArray
 * )) before or use
 * my_vision_msgs__msg__DetectedCropArray__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
bool
my_vision_msgs__msg__DetectedCropArray__init(my_vision_msgs__msg__DetectedCropArray * msg);

/// Finalize msg/DetectedCropArray message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
void
my_vision_msgs__msg__DetectedCropArray__fini(my_vision_msgs__msg__DetectedCropArray * msg);

/// Create msg/DetectedCropArray message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * my_vision_msgs__msg__DetectedCropArray__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
my_vision_msgs__msg__DetectedCropArray *
my_vision_msgs__msg__DetectedCropArray__create();

/// Destroy msg/DetectedCropArray message.
/**
 * It calls
 * my_vision_msgs__msg__DetectedCropArray__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
void
my_vision_msgs__msg__DetectedCropArray__destroy(my_vision_msgs__msg__DetectedCropArray * msg);

/// Check for msg/DetectedCropArray message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
bool
my_vision_msgs__msg__DetectedCropArray__are_equal(const my_vision_msgs__msg__DetectedCropArray * lhs, const my_vision_msgs__msg__DetectedCropArray * rhs);

/// Copy a msg/DetectedCropArray message.
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
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
bool
my_vision_msgs__msg__DetectedCropArray__copy(
  const my_vision_msgs__msg__DetectedCropArray * input,
  my_vision_msgs__msg__DetectedCropArray * output);

/// Initialize array of msg/DetectedCropArray messages.
/**
 * It allocates the memory for the number of elements and calls
 * my_vision_msgs__msg__DetectedCropArray__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
bool
my_vision_msgs__msg__DetectedCropArray__Sequence__init(my_vision_msgs__msg__DetectedCropArray__Sequence * array, size_t size);

/// Finalize array of msg/DetectedCropArray messages.
/**
 * It calls
 * my_vision_msgs__msg__DetectedCropArray__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
void
my_vision_msgs__msg__DetectedCropArray__Sequence__fini(my_vision_msgs__msg__DetectedCropArray__Sequence * array);

/// Create array of msg/DetectedCropArray messages.
/**
 * It allocates the memory for the array and calls
 * my_vision_msgs__msg__DetectedCropArray__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
my_vision_msgs__msg__DetectedCropArray__Sequence *
my_vision_msgs__msg__DetectedCropArray__Sequence__create(size_t size);

/// Destroy array of msg/DetectedCropArray messages.
/**
 * It calls
 * my_vision_msgs__msg__DetectedCropArray__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
void
my_vision_msgs__msg__DetectedCropArray__Sequence__destroy(my_vision_msgs__msg__DetectedCropArray__Sequence * array);

/// Check for msg/DetectedCropArray message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
bool
my_vision_msgs__msg__DetectedCropArray__Sequence__are_equal(const my_vision_msgs__msg__DetectedCropArray__Sequence * lhs, const my_vision_msgs__msg__DetectedCropArray__Sequence * rhs);

/// Copy an array of msg/DetectedCropArray messages.
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
ROSIDL_GENERATOR_C_PUBLIC_my_vision_msgs
bool
my_vision_msgs__msg__DetectedCropArray__Sequence__copy(
  const my_vision_msgs__msg__DetectedCropArray__Sequence * input,
  my_vision_msgs__msg__DetectedCropArray__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // MY_VISION_MSGS__MSG__DETAIL__DETECTED_CROP_ARRAY__FUNCTIONS_H_
