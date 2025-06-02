// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_vision_msgs:msg/CropPose.idl
// generated code does not contain a copyright notice

#ifndef MY_VISION_MSGS__MSG__DETAIL__CROP_POSE__STRUCT_HPP_
#define MY_VISION_MSGS__MSG__DETAIL__CROP_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'cutting_point'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__my_vision_msgs__msg__CropPose __attribute__((deprecated))
#else
# define DEPRECATED__my_vision_msgs__msg__CropPose __declspec(deprecated)
#endif

namespace my_vision_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CropPose_
{
  using Type = CropPose_<ContainerAllocator>;

  explicit CropPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    cutting_point(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->crop_id = 0ul;
      this->confidence = 0.0f;
    }
  }

  explicit CropPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    cutting_point(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->crop_id = 0ul;
      this->confidence = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _crop_id_type =
    uint32_t;
  _crop_id_type crop_id;
  using _cutting_point_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _cutting_point_type cutting_point;
  using _confidence_type =
    float;
  _confidence_type confidence;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__crop_id(
    const uint32_t & _arg)
  {
    this->crop_id = _arg;
    return *this;
  }
  Type & set__cutting_point(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->cutting_point = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_vision_msgs::msg::CropPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_vision_msgs::msg::CropPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_vision_msgs::msg::CropPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_vision_msgs::msg::CropPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_vision_msgs__msg__CropPose
    std::shared_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_vision_msgs__msg__CropPose
    std::shared_ptr<my_vision_msgs::msg::CropPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CropPose_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->crop_id != other.crop_id) {
      return false;
    }
    if (this->cutting_point != other.cutting_point) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    return true;
  }
  bool operator!=(const CropPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CropPose_

// alias to use template instance with default allocator
using CropPose =
  my_vision_msgs::msg::CropPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_vision_msgs

#endif  // MY_VISION_MSGS__MSG__DETAIL__CROP_POSE__STRUCT_HPP_
