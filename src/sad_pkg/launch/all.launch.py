import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, LogInfo, IncludeLaunchDescription, ExecuteProcess
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
import xacro
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    # URDF와 관련된 설정
    pkg_name = 'sad_pkg'
    sad_pkg_path = get_package_share_directory(pkg_name)
    file_subpath = 'urdf/description/test.xacro'
    xacro_file = os.path.join(sad_pkg_path, file_subpath)

    robot_description_config = xacro.process_file(xacro_file)
    robot_description = {'robot_description': robot_description_config.toxml()}

    # Inverse_node 실행에 필요한 인자 선언
    gui_arg = DeclareLaunchArgument(
        'gui', default_value='false', description='Set to "true" to enable gzclient (GUI).'
    )
    use_gui = LaunchConfiguration('gui')

    # RViz 실행
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen'
    )

    # obstacle_node 실행
    obstacle_node = Node(
        package='sad_pkg',  # 실제 패키지 이름으로 변경
        executable='obstacle_node',
        name='obstacle_node',
        output='screen'
    )

    # map_node 실행
    map_node = Node(
        package='sad_pkg',  # 실제 패키지 이름으로 변경
        executable='map_node',
        name='map_node',
        output='screen'
    )

    # path_node 실행
    path_node = Node(
        package='sad_pkg',  # 실제 패키지 이름으로 변경
        executable='path_node',
        name='path_node',
        output='screen'
    )

    # Inverse_node 실행
    inverse_node = Node(
        package='sad_pkg',  # 실제 패키지 이름으로 변경
        executable='Inverse_node',
        name='Inverse_node',
        output='screen'
    )

    return LaunchDescription([
        # GUI 설정
        gui_arg,
        
        # RViz, 장애물, 경로, 역기구학 노드 실행
        rviz_node,
        obstacle_node,
        map_node,
        path_node,
        inverse_node,
    ])
