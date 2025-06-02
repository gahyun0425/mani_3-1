cmake_minimum_required(VERSION 3.8)
project(my_vision_msgs)

# --- C99 / C++17 ---
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# --- 컴파일 옵션 ---
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- find packages ---
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)                  # <- node 코드 때문에 필요
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)      # <- Header::Time 때문에 필요
find_package(rosidl_default_generators REQUIRED)

# --- 메시지 목록 ---
set(MY_VISION_MSGS
  "msg/CropPose.msg"
  "msg/DetectedCrop.msg"
  "msg/DetectedCropArray.msg"
  "msg/HarvestOrdering.msg"
)

# --- 메시지 생성 (interface only) ---
rosidl_generate_interfaces(${PROJECT_NAME}
  ${MY_VISION_MSGS}
  DEPENDENCIES
    std_msgs
    geometry_msgs
    builtin_interfaces                    # <- rclcpp는 여기서 빼야 합니다!
)

# --- (필요하다면) node executable 추가 ---
# add_executable(obstacle_node src/obstacle_node.cpp)
# ament_target_dependencies(obstacle_node rclcpp my_vision_msgs)
# … map_node 도 동일

ament_package()
