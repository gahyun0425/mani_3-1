#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "std_msgs/msg/float64.hpp"
#include "serial/serial.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <cmath>
#include <array>
#include <vector>
#include <thread>
#include "std_srvs/srv/trigger.hpp"

#define PROTOCOL_VERSION 2.0
#define DXL_ID_1 4
#define DXL_ID_2 5

#define ADDR_TORQUE_ENABLE 64
#define ADDR_OPERATING_MODE 11
#define ADDR_GOAL_VELOCITY 104
#define ADDR_PRESENT_VELOCITY 128

class MotorControlNode : public rclcpp::Node {
public:
    MotorControlNode() : Node("motorcontrol_node") {
        portHandler_ = dynamixel::PortHandler::getPortHandler("/dev/ttyU2D2");// U2D2 연결 포트
        packetHandler_ = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

        if (!portHandler_->openPort()) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open Dynamixel port");
            return;
        }
        if (!portHandler_->setBaudRate(115200)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to set Dynamixel baudrate");
            return;
        }

        // Enable Torque 1, 2
        uint8_t dxl_error = 0;

        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_OPERATING_MODE, 1, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_OPERATING_MODE, 1, &dxl_error);

        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_TORQUE_ENABLE, 1, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_TORQUE_ENABLE, 1, &dxl_error);

        try {
            serial_.setPort("/dev/ttyUART");// STM 연결 포트
            serial_.setBaudrate(115200);
            serial::Timeout timeout = serial::Timeout::simpleTimeout(1000);
            serial_.setTimeout(timeout);
            serial_.open();
        } catch (serial::IOException &e) {
            RCLCPP_ERROR(this->get_logger(), "Unable to open STM32 serial port");
            return;
        }
        if (!serial_.isOpen()) {
            RCLCPP_ERROR(this->get_logger(), "STM32 serial port not open");
            return;
        }

        dq_sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>("/joint_velocity", 10,
            std::bind(&MotorControlNode::dq_callback, this, std::placeholders::_1));
            
        std::thread([this]() {
            rclcpp::WallRate rate(std::chrono::milliseconds(2));
            while (rclcpp::ok()) {
                this->readFromSTM32();
                rate.sleep();  // 정확히 2ms 주기 유지
            }
        }).detach();

        current_qdot_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/current_qdot", 10);

        RCLCPP_INFO(this->get_logger(), "MotorControlNode initialized");
    }

    ~MotorControlNode() {
        uint8_t dxl_error = 0;
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_TORQUE_ENABLE, 0, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_TORQUE_ENABLE, 0, &dxl_error);
        portHandler_->closePort();
        if (serial_.isOpen()) serial_.close();
    }

private:
    void dq_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
    {
        if (msg->data.size() != 6) {
            RCLCPP_WARN(this->get_logger(), "Expected 6 joint velocities, but got %zu", msg->data.size());
            return;
        }
        
        RCLCPP_INFO(this->get_logger(),
            "[/joint_velocity] Received: [%.3f %.3f %.3f %.3f %.3f %.3f]",
            msg->data[0], msg->data[1], msg->data[2],
            msg->data[3], msg->data[4], msg->data[5]);

        std::vector<double> dc_vals(msg->data.begin(), msg->data.begin() + 4); // STM32에 4개 전달
        sendToSTM32(dc_vals);

         // === LPF 적용 ===
        double raw_vel_1 = msg->data[4];
        double raw_vel_2 = msg->data[5];

        double filtered_vel_1 = alpha_ * raw_vel_1 + (1.0 - alpha_) * prev_dxl_vel_1_;
        double filtered_vel_2 = alpha_ * raw_vel_2 + (1.0 - alpha_) * prev_dxl_vel_2_;

        prev_dxl_vel_1_ = filtered_vel_1;
        prev_dxl_vel_2_ = filtered_vel_2;

        // === rad/s → Dynamixel internal unit (약 41.89) ===
        int32_t dxl_vel_1 = static_cast<int32_t>(filtered_vel_1 * 41.8879);
        int32_t dxl_vel_2 = static_cast<int32_t>(filtered_vel_2 * 41.8879);

        setDynamixelVelocity(DXL_ID_1, dxl_vel_1);
        setDynamixelVelocity(DXL_ID_2, dxl_vel_2);
    }
    void setDynamixelVelocity(uint8_t id, int32_t vel) {
        uint8_t param[4];
        param[0] = vel & 0xFF;
        param[1] = (vel >> 8) & 0xFF;
        param[2] = (vel >> 16) & 0xFF;
        param[3] = (vel >> 24) & 0xFF;

        uint8_t dxl_error = 0;
        packetHandler_->writeTxRx(portHandler_, id, ADDR_GOAL_VELOCITY, 4, param, &dxl_error);
    }
    void sendToSTM32(const std::vector<double>& velocities) {
        if (velocities.size() < 4) return;
        uint8_t packet[19]; //시작, length, float*4, 체크섬
        packet[0] = 0xAA; // 시작 바이트
        packet[1] = 16; // data 크기

        float vals[4] = {
            static_cast<float>(velocities[0]),
            static_cast<float>(velocities[1]),
            static_cast<float>(velocities[2]),
            static_cast<float>(velocities[3])
        };
        memcpy(&packet[2], reinterpret_cast<uint8_t*>(vals), sizeof(float) * 4);

        int sum = 0;
        for (int i = 2; i < 18; i++) {
            sum += packet[i];
        }
        packet[18] = sum & 0xFF;

        serial_.write(packet, 19);
        serial_.flush();
    }
    void readFromSTM32() {
        constexpr size_t FRAME_SIZE = 18;
        uint8_t frame[FRAME_SIZE];
        size_t bytes_read = 0;

        while (bytes_read < FRAME_SIZE && rclcpp::ok()) {
            size_t n = serial_.read(frame + bytes_read, FRAME_SIZE - bytes_read);
            if (n == 0) {
                continue;
            }
            bytes_read += n;
        }
        if (bytes_read != FRAME_SIZE) {
            return;
        }

        if (frame[0] != 0xAA || frame[1] != 16) {
            return;
        }

        float dc_values[4];
        memcpy(dc_values, &frame[2], sizeof(dc_values));

        RCLCPP_INFO(get_logger(),
            "BLOCKING_DC [%.6f, %.6f, %.6f, %.6f]",
            dc_values[0], dc_values[1], dc_values[2], dc_values[3]
        );

        std_msgs::msg::Float64MultiArray msg;
        msg.data.resize(6);
        for (int i = 0; i < 4; ++i) {
            msg.data[i] = static_cast<double>(dc_values[i]);
        }
        for (int i = 0; i < 2; ++i) {
            uint8_t velocity_bytes[4];
            uint8_t dxl_err = 0;
            packetHandler_->readTxRx(
                portHandler_, DXL_ID_1 + i,
                ADDR_PRESENT_VELOCITY,
                4,
                velocity_bytes,
                &dxl_err
            );

            int32_t signed_vel = (velocity_bytes[3] << 24) |
                                (velocity_bytes[2] << 16) |
                                (velocity_bytes[1] << 8)  |
                                (velocity_bytes[0]);

            msg.data[4 + i] = signed_vel * 0.229 * 2 * M_PI / 60.0;
        }
        current_qdot_pub_->publish(msg);
    }

    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr dq_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr current_qdot_pub_;

    serial::Serial serial_;
    dynamixel::PortHandler *portHandler_;
    dynamixel::PacketHandler *packetHandler_;
    std::vector<uint8_t> _rx_buffer;

    double prev_dxl_vel_1_ = 0.0;
    double prev_dxl_vel_2_ = 0.0;
    const double alpha_ = 0.2;  // 필터 계수 (0.0 ~ 1.0)

};
int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MotorControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}