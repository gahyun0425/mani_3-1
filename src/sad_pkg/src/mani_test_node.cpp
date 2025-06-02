#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "rclcpp/rclcpp.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp" 

using Eigen::Matrix4d;
using Eigen::MatrixXd;
using Eigen::Vector3d;
using Eigen::VectorXd;

double a1 = 0.0, a2 = -61.27, a3 = -57.155, a4 = 0.0, a5 = 0.0, a6 = 0.0;
double d1 = 18.07, d2 = 0.0, d3 = 0.0, d4 = 17.415, d5 = 11.985, d6 = 11.655;
double alpha1 = M_PI / 2, alpha2 = 0.0, alpha3 = 0.0, alpha4 = M_PI / 2, alpha5 = -M_PI / 2, alpha6 = 0.0;
double theta_offset1 = 0.0, theta_offset2 = 0.0, theta_offset3 = 0.0, theta_offset4 = 0.0, theta_offset5 = 0.0, theta_offset6 = 0.0;
double K_p_position = 0.9;
double K_p_orientation = 0.4;
double K_d = 0.0;

// Function prototypes
MatrixXd computeJacobian(VectorXd& theta);
VectorXd inverseKinematics(const Vector3d& position, const Vector3d& angular_velocity);
Matrix4d forwardKinematics(VectorXd& theta);

std::vector<std::array<double,7>> points;

// Convert degrees to radians
double degToRad(double degree) {
    return degree * M_PI / 180.0;
}


// 각 관절의 제한 범위 (단위: 라디안)
const double joint_limits[6][2] = {
    {-M_PI, M_PI},               // 관절 1: ±360°
    {-M_PI, M_PI},               // 관절 2: -180° ~ +180°
    {-M_PI, M_PI},               // 관절 3: -180° ~ +180°
    {-M_PI, M_PI},               // 관절 4: ±360°
    {-M_PI, M_PI},               // 관절 5: ±360°
    {-M_PI, M_PI}                // 관절 6: ±360°
};


// Quaternion 구조체 정의
struct Quaternion {
    double w, x, y, z;

    // 정규화
    void normalize() {
        double norm = std::sqrt(w*w + x*x + y*y + z*z);
        w /= norm;
        x /= norm;
        y /= norm;
        z /= norm;
    }

    // 역수 계산
    Quaternion inverse() const {
        return {w, -x, -y, -z};
    }

    // 곱셈 연산자 오버로딩
    Quaternion operator*(const Quaternion& q) const {
        return {
            w*q.w - x*q.x - y*q.y - z*q.z,
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w
        };
    }
};

// Rotation Matrix에서 Quaternion으로 변환
Quaternion rotationMatrixToQuaternion(const Eigen::Matrix3d& R) {
    Quaternion q;
    double trace = R.trace();
    if (trace > 0) {
        double s = 0.5 / std::sqrt(trace + 1.0);
        q.w = 0.25 / s;
        q.x = (R(2,1) - R(1,2)) * s;
        q.y = (R(0,2) - R(2,0)) * s;
        q.z = (R(1,0) - R(0,1)) * s;
    } else {
        if (R(0,0) > R(1,1) && R(0,0) > R(2,2)) {
            double s = 2.0 * std::sqrt(1.0 + R(0,0) - R(1,1) - R(2,2));
            q.w = (R(2,1) - R(1,2)) / s;
            q.x = 0.25 * s;
            q.y = (R(0,1) + R(1,0)) / s;
            q.z = (R(0,2) + R(2,0)) / s;
        } else if (R(1,1) > R(2,2)) {
            double s = 2.0 * std::sqrt(1.0 + R(1,1) - R(0,0) - R(2,2));
            q.w = (R(0,2) - R(2,0)) / s;
            q.x = (R(0,1) + R(1,0)) / s;
            q.y = 0.25 * s;
            q.z = (R(1,2) + R(2,1)) / s;
        } else {
            double s = 2.0 * std::sqrt(1.0 + R(2,2) - R(0,0) - R(1,1));
            q.w = (R(1,0) - R(0,1)) / s;
            q.x = (R(0,2) + R(2,0)) / s;
            q.y = (R(1,2) + R(2,1)) / s;
            q.z = 0.25 * s;
        }
    }
    q.normalize();
    return q;
}

// Euler 각도에서 Quaternion으로 변환 (ZYX 순서)
Quaternion eulerToQuaternion(double roll, double pitch, double yaw) {
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;
    q.normalize();
    return q;
}

// Quaternion에서 Angle-Axis로 변환
void quaternionToAngleAxis(const Quaternion& q, Vector3d& axis, double& angle) {
    angle = 2.0 * acos(q.w);
    double s = sqrt(1 - q.w * q.w);
    if (s < 1e-6) {
        // 근사 처리
        axis = Vector3d(q.x, q.y, q.z);
    } else {
        axis = Vector3d(q.x / s, q.y / s, q.z / s);
    }
}

Matrix4d DHMatrix(double a, double alpha, double d, double theta) {
    Matrix4d T;
    T << cos(theta), -sin(theta) * cos(alpha), sin(theta)* sin(alpha), a* cos(theta),
        sin(theta), cos(theta)* cos(alpha), -cos(theta) * sin(alpha), a* sin(theta),
        0, sin(alpha), cos(alpha), d,
        0, 0, 0, 1;
    return T;
}

Matrix4d forwardKinematics(VectorXd& theta) {
    Matrix4d T1 = DHMatrix(a1, alpha1, d1, theta(0) + theta_offset1);
    Matrix4d T2 = T1 * DHMatrix(a2, alpha2, d2, theta(1) + theta_offset2);
    Matrix4d T3 = T2 * DHMatrix(a3, alpha3, d3, theta(2) + theta_offset3);
    Matrix4d T4 = T3 * DHMatrix(a4, alpha4, d4, theta(3) + theta_offset4);
    Matrix4d T5 = T4 * DHMatrix(a5, alpha5, d5, theta(4) + theta_offset5);
    Matrix4d T6 = T5 * DHMatrix(a6, alpha6, d6, theta(5) + theta_offset6);
    return T6;
}

class ManipulatorNode : public rclcpp::Node {
public:
    ManipulatorNode() : Node("manipulator_node") {

        joint_trajectory_pub_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>("/joint_trajectory_controller/joint_trajectory", 10);
        spline_path_sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/spline_path_pose", 10, std::bind(&ManipulatorNode::splinePathCallback, this, std::placeholders::_1));
        joint_state_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
                    "/joint_states", 10, std::bind(&ManipulatorNode::jointStateCallback, this, std::placeholders::_1));
        
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&ManipulatorNode::processPoints, this));

        current_joint_angles_= VectorXd::Zero(6);
        desired_joint_angles_ = VectorXd::Zero(6);
        RCLCPP_INFO(this->get_logger(), "ManipulatorNode initialized.");
    }

private:
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr joint_trajectory_pub_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr spline_path_sub_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
    VectorXd current_joint_angles_;
    VectorXd desired_joint_angles_;

     void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) {
        if (msg->position.size() >= 6) {
            for (int i = 0; i < 6; ++i) {
                current_joint_angles_[i] = msg->position[i];
            }

            // 현재 위치 계산 (Forward Kinematics 사용)
            Matrix4d T6 = forwardKinematics(current_joint_angles_);
            Vector3d current_position = T6.block<3, 1>(0, 3);

            // 현재 위치 출력
            RCLCPP_INFO(this->get_logger(), "Current End-Effector Position: x = %f, y = %f, z = %f",
                        current_position.x(), current_position.y(), current_position.z());
            
        } else {
            RCLCPP_WARN(this->get_logger(), "Received joint state message with insufficient data.");
        }
    }

    // splinePathCallback 함수
    void splinePathCallback(const std_msgs::msg::Float64MultiArray::SharedPtr result_msg) {
        if (result_msg->data.size() == 7) {
            std::array<double, 7> point;
            std::copy(result_msg->data.begin(), result_msg->data.end(), point.begin());
            points.push_back(point);
            RCLCPP_INFO(this->get_logger(), "Received and stored point: [%f, %f, %f, %f, %f, %f, %f]",
                        point[0], point[1], point[2], point[3], point[4], point[5], point[6]);
        
            processPoints(); // 새로운 포인트를 받으면 processPoints 호출
        } else {
            RCLCPP_WARN(this->get_logger(), "Received message with incorrect size: %zu", result_msg->data.size());
        }
    }
    
    // Function to process points by sending target position and orientation to `computeFeedbackVelocity`
    void processPoints() {
    for (const auto& point : points) {
        Vector3d target_position(point[0], point[1], point[2]);
        Quaternion target_orientation = { point[3], point[4], point[5], point[6] };

        double position_tolerance = 1e-3;  // 위치 허용 오차
        double orientation_tolerance = 1e-3;  // 방향 허용 오차
        double max_joint_velocity = 0.2;  // 관절 속도 제한
        int max_iterations = 50;  // 최대 반복 횟수

        for (int iteration = 0; iteration < max_iterations; ++iteration) {
            // 현재 상태에서 목표까지의 속도 계산
            VectorXd joint_velocities = computeFeedbackVelocity(target_position, target_orientation);

            // 속도 제한 적용
            for (int i = 0; i < joint_velocities.size(); ++i) {
                if (std::abs(joint_velocities[i]) > max_joint_velocity) {
                    joint_velocities[i] = (joint_velocities[i] > 0 ? max_joint_velocity : -max_joint_velocity);
                }
            }

            // 관절 각도 업데이트
            desired_joint_angles_ = current_joint_angles_ + joint_velocities * 0.1;

            // 관절 각도 제한 적용
            applyJointLimits(desired_joint_angles_);

            // Forward Kinematics로 실제 위치 계산
            Matrix4d T6 = forwardKinematics(desired_joint_angles_);
            Vector3d real_position = T6.block<3, 1>(0, 3);

            // 위치 및 방향 오차 계산
            Vector3d position_error = target_position - real_position;

            Eigen::Matrix3d R = T6.block<3, 3>(0, 0);
            Quaternion current_orientation = rotationMatrixToQuaternion(R);
            Quaternion error_quat = target_orientation * current_orientation.inverse();
            Vector3d orientation_error;
            double orientation_angle;
            quaternionToAngleAxis(error_quat, orientation_error, orientation_angle);
            orientation_error *= orientation_angle;
            // 오일러 각도랑 위치랑 다를게 없는디????
            // desired ori 오일러로 입력 받고 보간하고 오일러를 쿼터니언으로 변환
            // current ori 회전행렬을 쿼터니언을 변환하고
            // 

            // 위치와 방향 오차가 모두 허용 오차 내에 들어오면 종료
            if (position_error.norm() < position_tolerance && orientation_error.norm() < orientation_tolerance) {
                RCLCPP_INFO(this->get_logger(), "Target reached: x = %f, y = %f, z = %f",
                            real_position.x(), real_position.y(), real_position.z());
                // break;

                current_joint_angles_ = desired_joint_angles_;

                points.erase(points.begin());
            }

            // 현재 각도를 다음 반복을 위해 업데이트
            current_joint_angles_ = desired_joint_angles_;

            // 로봇의 상태를 확인하기 위해 현재 위치를 출력
            // RCLCPP_INFO(this->get_logger(), "Iteration %d: End-effector Position: x = %f, y = %f, z = %f",
            //             iteration, real_position.x(), real_position.y(), real_position.z());

            // 반복 간 대기 시간 추가 (필요시 조정 가능)
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        // 목표 위치로 이동 완료 후 명령 전달
        sendJointTrajectory(desired_joint_angles_);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        // Orientation 값을 Roll, Pitch, Yaw로 변환하여 출력
         Vector3d euler_orientation = quaternionToEulerManual(target_orientation);
        RCLCPP_INFO(this->get_logger(), "Moving to position: x = %f, y = %f, z = %f, roll = %f, pitch = %f, yaw = %f",
                    target_position.x(), target_position.y(), target_position.z(),
                    euler_orientation.x(), euler_orientation.y(), euler_orientation.z());
    }

    // 모든 포인트를 처리한 후, points 배열을 비움
    points.clear();
}







    VectorXd computeFeedbackVelocity(const Vector3d& target_position, const Quaternion& target_orientation) {
        VectorXd q_dot(6);
        Matrix4d T6 = forwardKinematics(current_joint_angles_);
        Vector3d current_position = T6.block<3, 1>(0, 3);

        Eigen::Matrix3d R = T6.block<3, 3>(0, 0);

        // Rotation Matrix에서 Quaternion으로 변환
        Quaternion current_orientation = rotationMatrixToQuaternion(R);

        Vector3d position_error = target_position - current_position;


        // Quaternion 오차 계산
        Quaternion error_quat = target_orientation * current_orientation.inverse();
        Vector3d orientation_error;
        double angle;
        quaternionToAngleAxis(error_quat, orientation_error, angle);
        orientation_error *= angle;

        double position_deadband = 1.5; // end-effector가 목표 지점에 어느 정도 가까워지면 움직임을 멈추게 하는 것.
        double orientation_deadband = 0.05; // target orientation과 current orientation 사이의 각도가 어느정도 작아지면 움직임을 멈추게 함.

        if (position_error.norm() < position_deadband && orientation_error.norm() < orientation_deadband) {
            q_dot.setZero();
            return q_dot;
        }

        VectorXd u_feedback(6);
        u_feedback.head<3>() = K_p_position * position_error;
        u_feedback.tail<3>() = K_p_orientation * orientation_error;

        MatrixXd J = computeJacobian(current_joint_angles_);
        MatrixXd J_pseudo_inv = dampedPseudoInverse(J);
        q_dot = J_pseudo_inv * u_feedback;

        double max_joint_velocity = 0.4;
        for (int i = 0; i < q_dot.size(); ++i) {
            if (std::abs(q_dot[i]) > max_joint_velocity) {
                q_dot[i] = (q_dot[i] > 0 ? max_joint_velocity : -max_joint_velocity);
            }
        }

        return q_dot;
    }

    // Function to apply joint limits to the current joint angles
    void applyJointLimits(VectorXd& joint_angles) {
        // const double joint_limits[6][2] = {
        //     {-M_PI, M_PI}, {-M_PI, M_PI}, {-M_PI, M_PI},
        //     {-M_PI, M_PI}, {-M_PI, M_PI}, {-M_PI, M_PI}
        // };

        for (int i = 0; i < 6; ++i) {
            if (joint_angles(i) < joint_limits[i][0]) {
                joint_angles(i) = joint_limits[i][0];
            } else if (joint_angles(i) > joint_limits[i][1]) {
                joint_angles(i) = joint_limits[i][1];
            }
        }
    }

    MatrixXd computeJacobian(VectorXd &theta) {
        MatrixXd J(6, 6);
        Matrix4d T1 = DHMatrix(a1, alpha1, d1, theta(0) + theta_offset1);
        Matrix4d T2 = T1 * DHMatrix(a2, alpha2, d2, theta(1) + theta_offset2);
        Matrix4d T3 = T2 * DHMatrix(a3, alpha3, d3, theta(2) + theta_offset3);
        Matrix4d T4 = T3 * DHMatrix(a4, alpha4, d4, theta(3) + theta_offset4);
        Matrix4d T5 = T4 * DHMatrix(a5, alpha5, d5, theta(4) + theta_offset5);
        Matrix4d T6 = T5 * DHMatrix(a6, alpha6, d6, theta(5) + theta_offset6);


        Vector3d Oe = T6.block<3, 1>(0, 3);

        Vector3d Z0(0, 0, 1);
        Vector3d Z1 = T1.block<3, 1>(0, 2);
        Vector3d Z2 = T2.block<3, 1>(0, 2);
        Vector3d Z3 = T3.block<3, 1>(0, 2);
        Vector3d Z4 = T4.block<3, 1>(0, 2);
        Vector3d Z5 = T5.block<3, 1>(0, 2);

        J.block<3, 1>(0, 0) = Z0.cross(Oe);
        J.block<3, 1>(0, 1) = Z1.cross(Oe - T1.block<3, 1>(0, 3));
        J.block<3, 1>(0, 2) = Z2.cross(Oe - T2.block<3, 1>(0, 3));
        J.block<3, 1>(0, 3) = Z3.cross(Oe - T3.block<3, 1>(0, 3));
        J.block<3, 1>(0, 4) = Z4.cross(Oe - T4.block<3, 1>(0, 3));
        J.block<3, 1>(0, 5) = Z5.cross(Oe - T5.block<3, 1>(0, 3));

        J.block<3, 1>(3, 0) = Z0;
        J.block<3, 1>(3, 1) = Z1;
        J.block<3, 1>(3, 2) = Z2;
        J.block<3, 1>(3, 3) = Z3;
        J.block<3, 1>(3, 4) = Z4;
        J.block<3, 1>(3, 5) = Z5;

        return J;
    }

    MatrixXd dampedPseudoInverse(const MatrixXd &J) {
        Eigen::JacobiSVD<MatrixXd> svd(J, Eigen::ComputeFullU | Eigen::ComputeFullV);
        VectorXd singular_values = svd.singularValues();
        MatrixXd U = svd.matrixU();
        MatrixXd V = svd.matrixV();

        double lambda2 = 0.03;

        // 감쇠를 적용하여 특이값 조정
        for (long i = 0; i < singular_values.size(); ++i) {
            if (singular_values(i) < std::numeric_limits<double>::epsilon()) {
                singular_values(i) = 0.0;
            }
            else {
                singular_values(i) = singular_values(i) / (singular_values(i) * singular_values(i) + lambda2);
            }
        }

        return V * singular_values.asDiagonal() * U.transpose();
    }

    // Quaternion에서 Euler 각도(Roll, Pitch, Yaw)로 변환
    Vector3d quaternionToEulerManual(const Quaternion& q) {
        Vector3d euler;

        // Roll 계산 (x축 회전)
        double sinr_cosp = 2.0 * (q.w * q.x + q.y * q.z);
        double cosr_cosp = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
        euler.x() = atan2(sinr_cosp, cosr_cosp); // atan2로 구체적 각도 계산

        // Pitch 계산 (y축 회전)
        double sinp = 2.0 * (q.w * q.y - q.z * q.x);
        if (std::abs(sinp) >= 1.0) {
            // 값이 ±1이면 Gimball Lock 상태 처리
            euler.y() = std::copysign(M_PI / 2, sinp);
        } else {
            euler.y() = asin(sinp); // arcsin으로 Pitch 계산
        }

        // Yaw 계산 (z축 회전)
        double siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
        double cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
        euler.z() = atan2(siny_cosp, cosy_cosp);

        return euler; // [Roll, Pitch, Yaw] 순서로 반환
    }


    // Function to publish joint angles to trajectory topic
    void sendJointTrajectory(const VectorXd& joint_angles) {
        auto message = trajectory_msgs::msg::JointTrajectory();
        message.joint_names = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};

        auto point = trajectory_msgs::msg::JointTrajectoryPoint();
        for (int i = 0; i < 6; ++i) {
            point.positions.push_back(joint_angles(i));
        }
        point.time_from_start = rclcpp::Duration::from_seconds(5.0);

        message.points.push_back(point);
        joint_trajectory_pub_->publish(message);
    }


};


// main 함수에서 사용자 입력을 통해 목표 위치와 방위값을 설정
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ManipulatorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}