cmake_minimum_required(VERSION 3.8)
project(sad_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_runtime REQUIRED)
find_package(rosidl_typesupport_c REQUIRED)  
find_package(Eigen3 REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(trajectory_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(xacro REQUIRED)
find_package(ros2_control REQUIRED)
find_package(gazebo_ros2_control REQUIRED)
find_package(my_vision_msgs REQUIRED) 
find_package(rosidl_typesupport_cpp REQUIRED)   
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(control_msgs REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIRS}
    ${rclcpp_INCLUDE_DIRS}
    ${std_msgs_INCLUDE_DIRS}
    ${sensor_msgs_INCLUDE_DIRS}
    ${geometry_msgs_INCLUDE_DIRS}
    ${trajectory_msgs_INCLUDE_DIRS}
    ${my_vision_msgs_INCLUDE_DIRS}
    /opt/ros/humble/include
    )

add_executable(forward_node src/forward_node.cpp)
add_executable(rrt_node src/rrt_node.cpp)
add_executable(spline_node src/spline_node.cpp)
add_executable(obstacle_node src/obstacle_node.cpp)
add_executable(map_node src/map_node.cpp)
add_executable(path_node src/path_node.cpp)
add_executable(Inverse_node src/Inverse_node.cpp)
add_executable(motor_node src/motor_node.cpp)

ament_target_dependencies(forward_node rclcpp trajectory_msgs Eigen3 sensor_msgs)
ament_target_dependencies(rrt_node rclcpp geometry_msgs std_msgs visualization_msgs Eigen3 sensor_msgs)
ament_target_dependencies(spline_node rclcpp geometry_msgs visualization_msgs Eigen3 sensor_msgs)
ament_target_dependencies(obstacle_node rclcpp std_msgs rosidl_typesupport_cpp my_vision_msgs)
ament_target_dependencies(map_node rclcpp geometry_msgs std_msgs visualization_msgs Eigen3 sensor_msgs my_vision_msgs)
ament_target_dependencies(path_node rclcpp geometry_msgs std_msgs visualization_msgs Eigen3 sensor_msgs my_vision_msgs tf2
  tf2_geometry_msgs)
ament_target_dependencies(Inverse_node rclcpp rclcpp_action control_msgs geometry_msgs std_msgs visualization_msgs Eigen3 sensor_msgs trajectory_msgs my_vision_msgs rosidl_default_runtime tf2
  tf2_geometry_msgs)
ament_target_dependencies(motor_node rclcpp rclcpp_action control_msgs geometry_msgs std_msgs visualization_msgs Eigen3 sensor_msgs trajectory_msgs my_vision_msgs rosidl_default_runtime tf2
  tf2_geometry_msgs)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


# Launch 파일 설치
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

# Xacro 파일 설치
install(DIRECTORY
  urdf
  DESTINATION share/${PROJECT_NAME}
)

# Mesh 파일 설치 (STL, DAE 등)
install(DIRECTORY
  meshes
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
)

install(TARGETS 
  forward_node
  rrt_node
  obstacle_node
  spline_node
  map_node
  path_node
  Inverse_node
  motor_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
