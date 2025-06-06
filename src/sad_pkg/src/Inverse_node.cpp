// src/ModifiedManipulatorNode.cpp

#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <limits>
#include <stdexcept> // 표준 예외 클래스
#include "rclcpp/rclcpp.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"  // <-- 여기로 바뀌었습니다.
#include "sensor_msgs/msg/joint_state.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

using Eigen::Matrix4d;
using Eigen::MatrixXd;
using Eigen::Matrix3d;
using Eigen::Vector3d;
using Eigen::VectorXd;

// DH 파라미터 정의
double a0 = 0.0, a1 = 0.0, a2 = 0.0, a3 = 0.0, a4 = 0.0, a5 = 0.0, a6 = 0.1435;
double alpha0 = 0.0, alpha1 = M_PI / 2, alpha2 = -M_PI / 2, alpha3 = M_PI / 2, alpha4 = -M_PI / 2, alpha5 = M_PI / 2, alpha6 = -M_PI / 2;
double d1 = 0.402, d2 = 0.0, d3 = 0.278, d4 = 0.0, d5 = 0.2505, d6 = 0.0, d7 = 0.0455;
bool moved_once_ = false;

// 각 관절의 제한 범위 (단위: 라디안)
const double joint_limits[6][2] = {
    {-M_PI, M_PI},           
    {-1.745, 1.745},       
    {-M_PI, M_PI},         
    {-2.09, 2.09},  
    {-M_PI, M_PI},          
    {-1.0472, M_PI/2}     
};

// Quaternion 구조체
struct Quaternion {
    double w, x, y, z;
    void normalize() {
        double norm = std::sqrt(w*w + x*x + y*y + z*z);
        w /= norm; x /= norm; y /= norm; z /= norm;
    }
    Quaternion inverse() const {
        return {w, -x, -y, -z};
    }
    Quaternion operator*(const Quaternion& q) const {
        return {
            w*q.w - x*q.x - y*q.y - z*q.z,
            w*q.x + x*q.w + y*q.z - z*q.y,
            w*q.y - x*q.z + y*q.w + z*q.x,
            w*q.z + x*q.y - y*q.x + z*q.w
        };
    }
};

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

void quaternionToAngleAxis(const Quaternion& q, Vector3d& axis, double& angle) {
    angle = 2.0 * acos(q.w);
    double s = sqrt(1 - q.w * q.w);
    if (s < 1e-6) {
        axis = Vector3d(q.x, q.y, q.z);
    } else {
        axis = Vector3d(q.x / s, q.y / s, q.z / s);
    }
}

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

// DH 파라미터 → 변환 행렬
Matrix4d DHMatrix(double a, double alpha, double d, double theta) {
    Matrix4d T;
    T << cos(theta), -sin(theta), 0, a,
         sin(theta) * cos(alpha), cos(theta) * cos(alpha), -sin(alpha), -d * sin(alpha),
         sin(theta) * sin(alpha), cos(theta) * sin(alpha),  cos(alpha),  d * cos(alpha),
         0, 0, 0, 1;
    return T;
}

// forward kinematics
Matrix4d forwardKinematics(const VectorXd& theta) {
    Matrix4d T = DHMatrix(a0, alpha0, d1, theta(0))
               * DHMatrix(a1, alpha1, d2, theta(1))
               * DHMatrix(a2, alpha2, d3, theta(2))
               * DHMatrix(a3, alpha3, d4, theta(3))
               * DHMatrix(a4, alpha4, d5, theta(4))
               * DHMatrix(a5, alpha5, d6, theta(5))
               * DHMatrix(a6, alpha6, d7, 0);
    return T;
}

class ManipulatorNode : public rclcpp::Node {
public:
    ManipulatorNode()
    : Node(
        "manipulator_node",
        rclcpp::NodeOptions()
          .parameter_overrides({
            rclcpp::Parameter("use_sim_time", true)
          })
      ),
      current_index_(0),
      have_joint_state_(false)
    {
        // 1) path_node에서 보내온 Float64MultiArray 구독
        path_sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/path_to_inverse_kinematics", 10,
            std::bind(&ManipulatorNode::pathCallback, this, std::placeholders::_1)
        );

        // 2) joint_states 구독
        joint_state_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
        "/joint_states", 10,
        [this](const sensor_msgs::msg::JointState::SharedPtr js) {
            std::map<std::string, double> name_to_pos;
            for (size_t i = 0; i < js->name.size(); ++i) {
                name_to_pos[js->name[i]] = js->position[i];
            }

            for (int i = 0; i < 6; ++i) {
                std::string expected_name = "joint" + std::to_string(i + 1);
                if (name_to_pos.find(expected_name) != name_to_pos.end()) {
                    current_joint_angles_(i) = name_to_pos[expected_name];
                } else {
                    RCLCPP_WARN(this->get_logger(),
                        "Joint '%s' not found in /joint_states", expected_name.c_str());
                }
            }

            have_joint_state_ = true;
        }
    );


        // 3) JointTrajectory 퍼블리셔 생성
        joint_trajectory_pub_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
            "/joint_trajectory_controller/joint_trajectory", 10
        );

        // 4) 주기적으로 IK 계산할 타이머(100ms)
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&ManipulatorNode::timerCallback, this)
        );
    }

private:
    // --- 멤버 변수 ---
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr   joint_trajectory_pub_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr     path_sub_;
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr         joint_state_sub_;
    rclcpp::TimerBase::SharedPtr                                          timer_;

    std::vector<Eigen::Vector3d> target_velocities_; 
    // 총 경로를 따라가는 데 걸릴 총 시간을 결정 (초 단위)
    static constexpr double TOTAL_TIME = 10.0;  // 예: 10초 동안 모든 샘플을 순차적으로 실행

    // 경로가 처음 들어온 시점(ROS 시간)
    rclcpp::Time trajectory_start_time_;

    // 각 targets_[i] 를 실행해야 할 절대 ROS 시간(내부적으로 rclcpp::Time으로 저장)
    std::vector<rclcpp::Time> target_times_;
    VectorXd current_joint_angles_{6};  // 현재 joint angles
    size_t current_index_;
    bool have_joint_state_;
    bool moved_once_ = false;
    bool reached_current_{false};
    rclcpp::Time reached_time_;  // “도달 판정이 처음 나왔던 ROS 시간”을 저장

    
    // 들어온 경로 샘플을 저장할 벡터:
    // 각 샘플은 (t, position, orientation) 형태
    std::vector<std::tuple<double, Vector3d, Vector3d>> targets_;

    // (타이머 안에서 사용하는) 목표 EE 위치/회전
    Vector3d target_position_;
    Vector3d target_orientation_;

    // --- 함수 정의 ---

    // 1) pathCallback: Float64MultiArray를 받아서 7개씩 분할
    void pathCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
        const auto &arr = msg->data;
        if (arr.size() % 10 != 0 || arr.size() < 10) {
            RCLCPP_WARN(this->get_logger(),
                "[ManipulatorNode] 잘못된 메시지 크기: %zu (10의 배수가 아닙니다.)", arr.size());
            return;
        }

        // 1) targets_ 를 채우기 전에, 경로 시작 시각을 기록
        trajectory_start_time_ = this->now();

        targets_.clear();
        target_times_.clear();  // 이전 타이밍 데이터 초기화

        size_t sample_count = arr.size() / 10;
        targets_.reserve(sample_count);
        target_times_.reserve(sample_count);

        for (size_t i = 0; i < sample_count; ++i) {
            double t_norm = arr[10*i + 0];  // 정규화된 시간
            double x      = arr[10*i + 1];
            double y      = arr[10*i + 2];
            double z      = arr[10*i + 3];
            double roll   = arr[10*i + 4];
            double pitch  = arr[10*i + 5];
            double yaw    = arr[10*i + 6];
            double vx     = arr[10*i + 7];
            double vy     = arr[10*i + 8];
            double vz     = arr[10*i + 9];

            targets_.push_back({t_norm, Vector3d(x,y,z), Vector3d(roll,pitch,yaw)});
            target_velocities_.push_back(Vector3d(vx, vy, vz)); 

            // 3) t_norm을 TOTAL_TIME에 곱해서 “절대 실행 시간”을 만든 뒤 벡터에 저장
            double abs_offset = t_norm * TOTAL_TIME;  // 경로 시작 후 예: 0∼10초 사이
            rclcpp::Time abs_time = trajectory_start_time_ + rclcpp::Duration::from_seconds(abs_offset);
            target_times_.push_back(abs_time);
        }

        current_index_ = 0;
        moved_once_    = false;
        RCLCPP_INFO(this->get_logger(),
            "[ManipulatorNode] 총 %zu개의 목표 샘플 수신됨; 경로 시작 시각 = %.3f (secs)",
            targets_.size(),
            trajectory_start_time_.seconds()
        );
    }


    // 2) 타이머 콜백: 100ms마다 실행 → current_index_번째 목표로 IK 수행
    // ─────────────────────────────────────────────────────────────────────────
    void timerCallback() {
        if (!have_joint_state_ || targets_.empty()) {
            return;
        }

        // 1) “경과 시간” 계산
        double elapsed = (this->now() - trajectory_start_time_).seconds();
        double sample_interval = TOTAL_TIME / static_cast<double>(targets_.size());

        // 2) index 계산 (예: elapsed=6.4, sample_interval=0.25 → index= floor(6.4/0.25)=25)
        size_t idx = static_cast<size_t>(std::floor(elapsed / sample_interval));
        if (idx >= targets_.size()) {
            idx = targets_.size() - 1;
        }
        current_index_ = idx;

        // 4) 현재 인덱스 목표 꺼내서 IK 제어 준비
        auto &entry = targets_[current_index_];
        target_position_    = std::get<1>(entry);
        target_orientation_ = std::get<2>(entry);

        // --- (A) 현재 EE 위치·방위 계산 ---
        // 1) FK → 현재 EE 위치
        Eigen::Matrix4d T6          = forwardKinematics(current_joint_angles_);
        Eigen::Vector3d current_pos = T6.block<3,1>(0,3);

        // 2) 회전 행렬 → 현재 EE 방위 (roll, pitch, yaw)
        Eigen::Matrix3d R_mat = T6.block<3,3>(0,0);
        double roll_cur, pitch_cur, yaw_cur;
        {
            double sy = std::sqrt(R_mat(0,0)*R_mat(0,0) + R_mat(1,0)*R_mat(1,0));
            if (sy >= 1e-6) {
                roll_cur  = std::atan2(R_mat(2,1), R_mat(2,2));
                pitch_cur = std::atan2(-R_mat(2,0), sy);
                yaw_cur   = std::atan2(R_mat(1,0), R_mat(0,0));
            } else {
                // gimbal lock 근처
                roll_cur  = std::atan2(-R_mat(1,2), R_mat(1,1));
                pitch_cur = std::atan2(-R_mat(2,0), sy);
                yaw_cur   = 0.0;
            }
        }

        // --- (B) 위치 오차 계산 ---
        Eigen::Vector3d position_error = target_position_ - current_pos;
        double pos_err_norm = position_error.norm();  // 위치 오차 크기 (m)

        // --- (C) 방위 오차 계산 (quaternion → axis-angle) ---
        Quaternion q_current = rotationMatrixToQuaternion(R_mat);
        Quaternion q_target  = eulerToQuaternion(
                                target_orientation_.x(),
                                target_orientation_.y(),
                                target_orientation_.z()
                            );
        Quaternion q_error   = q_target * q_current.inverse();
        Eigen::Vector3d axis;
        double angle_rad;
        quaternionToAngleAxis(q_error, axis, angle_rad);
        double ori_err_deg = angle_rad * (180.0 / M_PI);  // 방위 오차 (°)


        // --- (D) 콘솔로 출력 ---
        RCLCPP_INFO(this->get_logger(),
            "[Timer] 현재 목표 인덱스 = %zu", current_index_);

        RCLCPP_INFO(this->get_logger(),
            "[Timer] 현재 EE 위치 = (%.3f, %.3f, %.3f)  → 목표 위치 = (%.3f, %.3f, %.3f)",
            current_pos.x(), current_pos.y(), current_pos.z(),
            target_position_.x(), target_position_.y(), target_position_.z());

        RCLCPP_INFO(this->get_logger(),
            "[Timer] 현재 EE 방위 = (roll=%.3f°, pitch=%.3f°, yaw=%.3f°)  → 목표 방위 = (roll=%.3f°, pitch=%.3f°, yaw=%.3f°)",
            roll_cur * 180.0/M_PI, pitch_cur * 180.0/M_PI, yaw_cur * 180.0/M_PI,
            target_orientation_.x() * 180.0/M_PI,
            target_orientation_.y() * 180.0/M_PI,
            target_orientation_.z() * 180.0/M_PI);

        RCLCPP_INFO(this->get_logger(),
            "[Timer] 위치 오차 크기 = %.3f m, 방위 오차 크기 = %.3f°",
            pos_err_norm, ori_err_deg);

        // --- (E) Deadband 검사: 이미 목표점 근처라면 제어 없이 패스 ---
        double position_deadband    = 0.05;   // 5cm
        double orientation_deadband = 0.1;    // 약 5.7°
        if (pos_err_norm < position_deadband &&
            angle_rad < orientation_deadband) 
        {
            // deadband 안에 있으면 IK 제어 없이 리턴
            return;
        }

        double dt = 0.01;

        // --- (F) desired_velocity 계산 ---
        // 목표 속도 계산 (위치 및 회전 속도)
        Eigen::Vector3d desired_velocity_position = position_error / dt;
        // Eigen::Vector3d desired_velocity_orientation = axis * angle_rad / dt;

        // --- (G) CLIK 제어 수행 (dt = 0.001) ---
        VectorXd q_dot = computeFeedbackVelocity(position_error, axis * angle_rad, desired_velocity_position);
        
        VectorXd next_q = current_joint_angles_ + q_dot * dt;

        for (int i = 0; i < 6; ++i) {
            double min_limit = joint_limits[i][0];  // 최소 제한
            double max_limit = joint_limits[i][1];  // 최대 제한

            // 속도가 제한 범위를 벗어나지 않도록 클램핑
            q_dot(i) = std::max(min_limit, std::min(max_limit, q_dot(i)));
        }

        // 1) JointTrajectory 퍼블리시
        sendJointTrajectory(next_q, current_joint_angles_, dt);
        // 2) 내부 상태 업데이트
        current_joint_angles_ = next_q;
    }

    // 3) computeJacobian: 현재 관절각 theta로부터 6×6 자코비안 계산
    MatrixXd computeJacobian(const VectorXd &theta) {
        Matrix4d T0 = DHMatrix(a0, alpha0, d1, theta(0));
        Matrix4d T1 = T0 * DHMatrix(a1, alpha1, d2, theta(1));
        Matrix4d T2 = T1 * DHMatrix(a2, alpha2, d3, theta(2));
        Matrix4d T3 = T2 * DHMatrix(a3, alpha3, d4, theta(3));
        Matrix4d T4 = T3 * DHMatrix(a4, alpha4, d5, theta(4));
        Matrix4d T5 = T4 * DHMatrix(a5, alpha5, d6, theta(5));
        Matrix4d T6 = T5 * DHMatrix(a6, alpha6, d7, 0);

        Vector3d Oe = T6.block<3,1>(0,3);

        Vector3d Z0(0,0,1);
        Vector3d Z1 = T1.block<3,1>(0,2);
        Vector3d Z2 = T2.block<3,1>(0,2);
        Vector3d Z3 = T3.block<3,1>(0,2);
        Vector3d Z4 = T4.block<3,1>(0,2);
        Vector3d Z5 = T5.block<3,1>(0,2);

        MatrixXd J = MatrixXd::Zero(6,6);
        J.block<3,1>(0,0) = Z0.cross(Oe - Vector3d::Zero());
        J.block<3,1>(0,1) = Z1.cross(Oe - T1.block<3,1>(0,3));
        J.block<3,1>(0,2) = Z2.cross(Oe - T2.block<3,1>(0,3));
        J.block<3,1>(0,3) = Z3.cross(Oe - T3.block<3,1>(0,3));
        J.block<3,1>(0,4) = Z4.cross(Oe - T4.block<3,1>(0,3));
        J.block<3,1>(0,5) = Z5.cross(Oe - T5.block<3,1>(0,3));

        J.block<3,1>(3,0) = Z0;
        J.block<3,1>(3,1) = Z1;
        J.block<3,1>(3,2) = Z2;
        J.block<3,1>(3,3) = Z3;
        J.block<3,1>(3,4) = Z4;
        J.block<3,1>(3,5) = Z5;

        return J;
    }

    // 4) computeFeedbackVelocity: position_error, orientation_error로부터 q_dot 계산
    VectorXd computeFeedbackVelocity(const Vector3d &position_error,const Vector3d &orientation_error,const Vector3d &desired_linear_velocity)
    {
        // (1) Kp와 Kd 설정
        double Kp_pos = 2.0;
        double Kp_ori = 0.5;

        // (2) 목표 속도 벡터 구성
        VectorXd u_d_with_error(6);
        u_d_with_error.head<3>() = desired_linear_velocity + Kp_pos * position_error;
        u_d_with_error.tail<3>() = Kp_ori * orientation_error;

        // (3) 자코비안 기반 관절 속도 계산
        MatrixXd J = computeJacobian(current_joint_angles_);
        MatrixXd J_pinv = dampedPseudoInverse(J);
        VectorXd q_dot = J_pinv * u_d_with_error;

        return q_dot;
    }



    // 5) dampedPseudoInverse
    MatrixXd dampedPseudoInverse(const MatrixXd &J) {
        Eigen::JacobiSVD<MatrixXd> svd(J, Eigen::ComputeFullU | Eigen::ComputeFullV);
        VectorXd s = svd.singularValues();
        MatrixXd U = svd.matrixU();
        MatrixXd V = svd.matrixV();

        double lambda2 = 0.1;
        for (long i = 0; i < s.size(); ++i) {
            if (s(i) < std::numeric_limits<double>::epsilon()) {
                s(i) = 0.0;
            } else {
                s(i) = s(i) / (s(i)*s(i) + lambda2);
            }
        }
        return V * s.asDiagonal() * U.transpose();
    }

    // 6) JointTrajectory 퍼블리시
    // ================================================
// 수정된 sendJointTrajectory 함수
// ================================================
void sendJointTrajectory(
    const VectorXd &target_q,
    const VectorXd &current_q,
    double dt)
{
    trajectory_msgs::msg::JointTrajectory msg;
    // 헤더 스탬프는 “지금 시각”으로
    msg.header.stamp = this->now();

    // 관절 이름들
    msg.joint_names = {"joint1","joint2","joint3","joint4","joint5","joint6"};

    // 1) 첫 번째 포인트: 현재 관절각, time_from_start = 0
    trajectory_msgs::msg::JointTrajectoryPoint p0;
    p0.positions = std::vector<double>(current_q.data(),
                                       current_q.data() + current_q.size());
    p0.time_from_start = rclcpp::Duration::from_seconds(0.0);
    msg.points.push_back(p0);

    // 2) 두 번째 포인트: 목표 관절각, time_from_start = dt(예: 0.01s)
    trajectory_msgs::msg::JointTrajectoryPoint p1;
    p1.positions = std::vector<double>(target_q.data(),
                                       target_q.data() + target_q.size());
    p1.time_from_start = rclcpp::Duration::from_seconds(dt);
    msg.points.push_back(p1);

    joint_trajectory_pub_->publish(msg);
}

};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ManipulatorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}