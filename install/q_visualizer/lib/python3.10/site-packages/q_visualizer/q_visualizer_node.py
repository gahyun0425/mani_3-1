def main():
    import rclpy
    from rclpy.node import Node
    import matplotlib.pyplot as plt
    from std_msgs.msg import Float64MultiArray
    import numpy as np
    import time

    class QVisualizerNode(Node):
        def __init__(self):
            super().__init__('q_visualizer_node')

            self.sub_current = self.create_subscription(
                Float64MultiArray, '/current_q', self.current_callback, 10)
            self.sub_target = self.create_subscription(
                Float64MultiArray, '/target_q', self.target_callback, 10)
            self.sub_current_dot = self.create_subscription(
                Float64MultiArray, '/current_qdot', self.current_dot_callback, 10)
            self.sub_target_dot = self.create_subscription(
                Float64MultiArray, '/joint_velocity', self.target_dot_callback, 10)

            self.current_q = [0.0] * 6
            self.target_q = [0.0] * 6
            self.current_q_dot = [0.0] * 6
            self.target_q_dot = [0.0] * 6
            self.integrated_current_q = [0.0] * 6
            self.integrated_target_q = [0.0] * 6
            self.last_time = time.time()

            self.timer = self.create_timer(0.01, self.timer_callback)  # 20Hz

        def current_callback(self, msg):
            if len(msg.data) == 6:
                self.current_q = msg.data

        def target_callback(self, msg):
            if len(msg.data) == 6:
                self.target_q = msg.data

        def current_dot_callback(self, msg):
            if len(msg.data) == 6:
                self.current_q_dot = msg.data

        def target_dot_callback(self, msg):
            if len(msg.data) == 6:
                self.target_q_dot = msg.data

        def timer_callback(self):
            now = time.time()
            dt = now - self.last_time
            self.last_time = now

            # q_dot 적분 (Euler 방식)
            for i in range(6):
                self.integrated_current_q[i] += self.current_q_dot[i] * dt
                self.integrated_target_q[i] += self.target_q_dot[i] * dt

            plt.clf()
            joint_ids = range(6)

            plt.bar([x - 0.3 for x in joint_ids], self.current_q, width=0.15, label='Current q', color='blue')
            plt.bar([x - 0.15 for x in joint_ids], self.target_q, width=0.15, label='Target q', color='orange')
            plt.bar([x + 0.05 for x in joint_ids], self.integrated_current_q, width=0.15, label='∫Current q̇', color='green')
            plt.bar([x + 0.20 for x in joint_ids], self.integrated_target_q, width=0.15, label='∫Target q̇', color='red')

            plt.xticks(joint_ids, [f'J{i+1}' for i in joint_ids])
            plt.ylim(-4, 4)
            plt.ylabel('Joint angle (rad)')
            plt.title('Joint Angle Comparison')
            plt.legend()
            plt.pause(0.001)

    rclpy.init()
    node = QVisualizerNode()
    plt.ion()
    plt.figure(figsize=(10, 5))
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    plt.ioff()
    plt.close()
    node.destroy_node()
    rclpy.shutdown()
