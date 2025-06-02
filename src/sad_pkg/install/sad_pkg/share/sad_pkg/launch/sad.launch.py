import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, RegisterEventHandler
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch import LaunchDescription
from launch.actions import ExecuteProcess
import xacro

def generate_launch_description():
    pkg_name = 'sad_pkg' 
    sad_pkg_path = get_package_share_directory(pkg_name)
    file_subpath = '/home/ga/sad_ws/src/sad_pkg/urdf/description/test.xacro'

    xacro_file = os.path.join(sad_pkg_path, file_subpath)
    robot_description_config = xacro.process_file(xacro_file)
    robot_description = {'robot_description': robot_description_config.toxml()}

    gui_arg = DeclareLaunchArgument(
        'gui', default_value='true', description='Set to "false" to disable gzclient (GUI).'
    )
    use_gui = LaunchConfiguration('gui')

    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description, {'use_sim_time': True}]
    )


    gazebo_server = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(get_package_share_directory("gazebo_ros"), "launch", "gzserver.launch.py")
        ]),
        launch_arguments=[('verbose', 'true')]
    )

    gazebo_client = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('gazebo_ros'), 'launch', 'gzclient.launch.py')]),
        condition=IfCondition(use_gui)
    )

    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic', 'robot_description', '-entity', 'test_robot'],
        output='screen'
    )


    activate_joint_state_broadcaster = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'joint_state_broadcaster'],
        output='screen'
    )

    activate_joint_trajectory_controller = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'joint_trajectory_controller'],
        output='screen'
    )

    return LaunchDescription([
        gui_arg,
        gazebo_server,
        gazebo_client,
        node_robot_state_publisher,
        spawn_entity,
        activate_joint_state_broadcaster,
        activate_joint_trajectory_controller,
    ])
