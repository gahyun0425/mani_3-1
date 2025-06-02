// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vision_msgs:msg/HarvestOrdering.idl
// generated code does not contain a copyright notice

#ifndef VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__STRUCT_HPP_
#define VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__STRUCT_HPP_

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
// Member 'objects'
#include "vision_msgs/msg/detail/detected_crop__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vision_msgs__msg__HarvestOrdering __attribute__((deprecated))
#else
# define DEPRECATED__vision_msgs__msg__HarvestOrdering __declspec(deprecated)
#endif

namespace vision_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HarvestOrdering_
{
  using Type = HarvestOrdering_<ContainerAllocator>;

  explicit HarvestOrdering_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->total_objects = 0ul;
    }
  }

  explicit HarvestOrdering_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->total_objects = 0ul;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _crop_ids_type =
    std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>>;
  _crop_ids_type crop_ids;
  using _objects_type =
    std::vector<vision_msgs::msg::DetectedCrop_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vision_msgs::msg::DetectedCrop_<ContainerAllocator>>>;
  _objects_type objects;
  using _total_objects_type =
    uint32_t;
  _total_objects_type total_objects;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__crop_ids(
    const std::vector<uint32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint32_t>> & _arg)
  {
    this->crop_ids = _arg;
    return *this;
  }
  Type & set__objects(
    const std::vector<vision_msgs::msg::DetectedCrop_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<vision_msgs::msg::DetectedCrop_<ContainerAllocator>>> & _arg)
  {
    this->objects = _arg;
    return *this;
  }
  Type & set__total_objects(
    const uint32_t & _arg)
  {
    this->total_objects = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vision_msgs::msg::HarvestOrdering_<ContainerAllocator> *;
  using ConstRawPtr =
    const vision_msgs::msg::HarvestOrdering_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vision_msgs::msg::HarvestOrdering_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vision_msgs::msg::HarvestOrdering_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vision_msgs__msg__HarvestOrdering
    std::shared_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vision_msgs__msg__HarvestOrdering
    std::shared_ptr<vision_msgs::msg::HarvestOrdering_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HarvestOrdering_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->crop_ids != other.crop_ids) {
      return false;
    }
    if (this->objects != other.objects) {
      return false;
    }
    if (this->total_objects != other.total_objects) {
      return false;
    }
    return true;
  }
  bool operator!=(const HarvestOrdering_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HarvestOrdering_

// alias to use template instance with default allocator
using HarvestOrdering =
  vision_msgs::msg::HarvestOrdering_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vision_msgs

#endif  // VISION_MSGS__MSG__DETAIL__HARVEST_ORDERING__STRUCT_HPP_
