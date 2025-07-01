#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "vision_msgs/msg/harvest_ordering.hpp"

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace std;
using namespace Eigen;

struct DHParam {
    double theta;
    double a;
    double d;
    double alpha;
};

Matrix4d dhToMatrix(const DHParam& dh) {
    Matrix4d T;
    double ct = cos(dh.theta);
    double st = sin(dh.theta);
    double ca = cos(dh.alpha);
    double sa = sin(dh.alpha);

    T << ct, -st, 0, dh.a,
         st * ca, ct * ca, -sa, -dh.d * sa,
         st * sa, ct * sa, ca, dh.d * ca,
         0, 0, 0, 1;

    return T;
}

Matrix4d forwardKinematics(const vector<DHParam>& dh_params) {
    Matrix4d T = Matrix4d::Identity();
    for (const auto& dh : dh_params) {
        T *= dhToMatrix(dh);
    }
    return T;
}

class RSNode : public rclcpp::Node {
public:
    RSNode() : Node("rs_node_joint_state"),
               goal_received_(false), goal_processed_(false), initial_goal_sent_(false) {
        joint_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10,
            std::bind(&RSNode::jointCallback, this, std::placeholders::_1)
        );

        goal_sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/goal_command", 10,
            std::bind(&RSNode::goalCallback, this, std::placeholders::_1)
        );

        goal_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/transformed_goal", 10);

        auto qos = rclcpp::QoS(10).transient_local();

        obstacle_sub_ = this->create_subscription<vision_msgs::msg::HarvestOrdering>(
            "/harvest_order", qos,
            std::bind(&RSNode::obstacleCallback, this, std::placeholders::_1)
        );

        auto pub_qos = rclcpp::QoS(10).transient_local();
        obstacle_pub_ = this->create_publisher<vision_msgs::msg::HarvestOrdering>(
            "/transformed_obstacles", pub_qos);
        
        vision_msgs::msg::HarvestOrdering::SharedPtr pending_obstacle_msg_;

        }

private:
    void jointCallback(const sensor_msgs::msg::JointState::SharedPtr msg) {
        if (!goal_received_ || goal_processed_ || goal_count_ <= 1) return;

        if (msg->position.size() < 6) {
            RCLCPP_WARN(this->get_logger(), "Received joint state with insufficient positions.");
            return;
        }

        std::map<std::string, double> joint_map;

        // 이름과 값을 매핑
        for (size_t i = 0; i < msg->name.size(); ++i) {
            joint_map[msg->name[i]] = msg->position[i];
            RCLCPP_INFO(this->get_logger(), "Joint [%s] = %.3f rad", 
                        msg->name[i].c_str(), msg->position[i]);
        }

        // 원하는 순서로 안전하게 추출
        double theta1 = joint_map["joint1"];
        double theta2 = joint_map["joint2"];
        double theta3 = joint_map["joint3"];
        double theta4 = joint_map["joint4"];
        double theta5 = joint_map["joint5"];
        double theta6 = joint_map["joint6"];

    RCLCPP_INFO(this->get_logger(), "Ordered joints: %.3f, %.3f, %.3f, %.3f, %.3f, %.3f",
                theta1, theta2, theta3, theta4, theta5, theta6);

        vector<DHParam> dh_params = {
            {theta1, 0.0, 0.445, 0},
            {theta2, 0.0, 0.0, -M_PI/2},
            {theta3, 0.0, 0.27, M_PI/2},
            {theta4, 0.0, 0.0, -M_PI/2},
            {theta5, 0.0, 0.24, M_PI/2},
            {theta6, 0.0, 0.0, -M_PI/2},
            {0.0,    0.14, 0.05, M_PI/2}
                };

        Matrix4d T_06 = forwardKinematics(dh_params);
        T_60_ = T_06;

        Vector4d goal_in_world;
        goal_in_world << goal_position_(0), goal_position_(1), goal_position_(2), 1.0;

        Vector4d goal_in_base = T_60_ * goal_in_world;

        goal_in_base(0) -= 0.25;

        std_msgs::msg::Float64MultiArray transformed_msg;
        transformed_msg.data = {goal_in_base(0), goal_in_base(1), goal_in_base(2)};
        goal_pub_->publish(transformed_msg);

        goal_processed_ = true;

        RCLCPP_INFO(this->get_logger(), "Processed and published goal #%d: x=%.3f, y=%.3f, z=%.3f",
                    goal_count_, goal_in_base(0), goal_in_base(1), goal_in_base(2));

        // 🔽 FK 준비됐으면 보류했던 obstacle 처리
        if (pending_obstacle_msg_) {
            RCLCPP_INFO(this->get_logger(), "🟢 FK ready. Processing pending obstacle.");
            obstacleCallback(pending_obstacle_msg_);
            pending_obstacle_msg_.reset();  // clear
        }

    }


    void goalCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
        if (msg->data.size() >= 3) {
            goal_position_ << msg->data[0], msg->data[1], msg->data[2];
            goal_received_ = true;
            goal_processed_ = false;  // 매 goal마다 처리 가능하게

            goal_count_++;

            if (goal_count_ == 1) {
                // 첫 번째 goal은 수정 없이 바로 퍼블리시
                std_msgs::msg::Float64MultiArray initial_msg;
                initial_msg.data = {goal_position_(0), goal_position_(1), goal_position_(2)};
                goal_pub_->publish(initial_msg);
                initial_goal_sent_ = true;

                RCLCPP_INFO(this->get_logger(), "Initial goal published as-is: x=%.3f, y=%.3f, z=%.3f",
                            goal_position_(0), goal_position_(1), goal_position_(2));
            } else {
                RCLCPP_INFO(this->get_logger(), "Adjusted goal for FK: x=%.3f, y=%.3f, z=%.3f",
                            goal_position_(0), goal_position_(1), goal_position_(2));
            }
        }
    }


    void obstacleCallback(const vision_msgs::msg::HarvestOrdering::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "✅ obstacleCallback triggered!");

        // 상태 디버그 로그
        RCLCPP_INFO(this->get_logger(), "🟡 Status - goal_count_: %d, obstacle_count_: %d, goal_processed_: %s",
                    goal_count_, obstacle_count_, goal_processed_ ? "true" : "false");

        // 수신한 원본 obstacle 좌표 출력
        for (size_t i = 0; i < msg->objects.size(); ++i) {
            const auto& obj = msg->objects[i];
            RCLCPP_INFO(this->get_logger(), "Object #%zu: id=%d, x=%.3f, y=%.3f, z=%.3f",
                        i, obj.id, obj.x, obj.y, obj.z);
        }

        // obstacle 메시지가 비어있을 경우
        if (msg->objects.empty() || msg->crop_ids.empty()) {
            RCLCPP_WARN(this->get_logger(), "⚠️ HarvestOrdering message is empty.");
            return;
        }

        // 처음 한 번은 변환 없이 그대로 퍼블리시
        if (obstacle_count_ == 0) {
            obstacle_pub_->publish(*msg);
            RCLCPP_INFO(this->get_logger(), "🔁 First obstacle published as-is.");
            obstacle_count_++;
            return;
        }


        // FK가 아직 준비 안 됨
        if (!goal_processed_) {
            RCLCPP_WARN(this->get_logger(), "⚠️ FK not ready. Holding obstacle temporarily.");
            pending_obstacle_msg_ = msg;
            return;
        }

        // 변환된 메시지 생성
        vision_msgs::msg::HarvestOrdering transformed_msg;
        transformed_msg.header.stamp = this->get_clock()->now();
        transformed_msg.crop_ids = msg->crop_ids;
        transformed_msg.total_objects = msg->objects.size();

        RCLCPP_INFO(this->get_logger(), "🔧 Converting obstacle positions with FK...");

        for (size_t i = 0; i < msg->objects.size(); ++i) {
            const auto& obj = msg->objects[i];
            Vector4d obs_world(obj.x, obj.y, obj.z, 1.0);
            Vector4d obs_base = T_60_ * obs_world;

            vision_msgs::msg::DetectedCrop transformed_crop;
            transformed_crop.id = obj.id;
            transformed_crop.x = obs_base(0);
            transformed_crop.y = obs_base(1);
            transformed_crop.z = obs_base(2);

            transformed_msg.objects.push_back(transformed_crop);

            // 변환 결과 출력
            RCLCPP_INFO(this->get_logger(), "🔹 Transformed Obstacle #%zu (id=%d): x=%.3f, y=%.3f, z=%.3f",
                        i, transformed_crop.id, transformed_crop.x, transformed_crop.y, transformed_crop.z);
        }

        obstacle_pub_->publish(transformed_msg);
        RCLCPP_INFO(this->get_logger(), "✅ Published transformed obstacle positions.");
        obstacle_count_++;
    }






    // ROS 통신 관련
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_sub_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr goal_sub_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr goal_pub_;
    rclcpp::Subscription<vision_msgs::msg::HarvestOrdering>::SharedPtr obstacle_sub_;
    rclcpp::Publisher<vision_msgs::msg::HarvestOrdering>::SharedPtr obstacle_pub_;
    vision_msgs::msg::HarvestOrdering::SharedPtr pending_obstacle_msg_;  // 🔹 FK 준비 전 obstacle 저장


    // 상태 변수
    Eigen::Vector3d goal_position_;
    bool goal_received_;         // goal이 수신되었는가
    bool goal_processed_;        // FK 기반 변환이 완료되었는가
    bool initial_goal_sent_;     // 최초 goal을 즉시 보냈는가
    Matrix4d T_60_;
    int goal_count_ = 0;
    int obstacle_count_ = 0;


};


int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RSNode>());
    rclcpp::shutdown();
    return 0;
}

/*
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace std;
using namespace Eigen;

// DH 파라미터 구조체 정의
struct DHParam {
    double theta; 
    double a;
    double d;
    double alpha;
};

// DH 파라미터를 이용한 변환 행렬 계산 함수
Matrix4d dhToMatrix(const DHParam& dh) {
    Matrix4d T;
    double ct = cos(dh.theta);
    double st = sin(dh.theta);
    double ca = cos(dh.alpha);
    double sa = sin(dh.alpha);

    T << ct, -st, 0, dh.a,
         st * ca, ct * ca, -sa, -dh.d * sa,
         st * sa, ct * sa, ca, dh.d * ca,
         0, 0, 0, 1;

    return T;
}

// Forward Kinematics 계산 함수
Matrix4d forwardKinematics(const vector<DHParam>& dh_params) {
    Matrix4d T = Matrix4d::Identity();
    for (const auto& dh : dh_params) {
        T *= dhToMatrix(dh);
    }
    return T;
}

int main() {
    // 초기 DH 파라미터 설정 (관절각은 0으로 초기화)
    vector<DHParam> dh_params = {
        {0, 0.0, 0.445, 0}, // theta, a, d, alpha
        {0, 0.0, 0.0, -M_PI/2},
        {0, 0.0, 0.27, M_PI/2},
        {0, 0.0, 0.0, -M_PI/2},
        {0, 0.0, 0.24, M_PI/2},
        {0, 0.0, 0.0, -M_PI/2},
        {0, 0.14, 0.05, M_PI/2}
    };

    // 사용자로부터 각 관절의 관절각 입력 받기
    for (size_t i = 0; i < dh_params.size()-1; ++i) {  // size_t 타입으로 변경
        cout << "Enter joint angle (in degrees) for joint " << i + 1 << ": ";
        double angle_deg;
        cin >> angle_deg;
        dh_params[i].theta = angle_deg * M_PI / 180.0; // degrees to radians
    }

    // Forward Kinematics 계산
    Matrix4d T_06 = forwardKinematics(dh_params);

    // 위치 값 (cm 단위로 변환)
    double x = T_06(0, 3) * 100.0;
    double y = T_06(1, 3) * 100.0;
    double z = T_06(2, 3) * 100.0;

    // 결과 출력
    cout << "Position and Orientation:\n";
    cout << "Position (X, Y, Z) in cm: " << x << " " << y << " " << z << " " << endl;

    return 0;
}*/