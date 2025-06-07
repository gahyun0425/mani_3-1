// #include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/float64_multi_array.hpp"
// #include "std_msgs/msg/float64.hpp"
// #include "serial/serial.h"
// #include "dynamixel_sdk/dynamixel_sdk.h"
// #include <cmath>
// #include <array>
// #include <vector>

// #define PROTOCOL_VERSION 2.0
// #define DXL_ID_1 4
// #define DXL_ID_2 5
// #define DXL_ID_3 6

// #define ADDR_TORQUE_ENABLE 64
// #define ADDR_OPERATING_MODE 11
// #define ADDR_GOAL_VELOCITY 104
// #define ADDR_PRESENT_VELOCITY 128  
// #define ADDR_GOAL_POSITION 116 // 추가

// class MotorControlNode : public rclcpp::Node {
// public:
//     MotorControlNode() : Node("motorcontrol_node") {
//         portHandler_ = dynamixel::PortHandler::getPortHandler("/dev/ttyUSB11");// U2D2 연결 포트
//         packetHandler_ = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

//         if (!portHandler_->openPort()) {
//             RCLCPP_ERROR(this->get_logger(), "Failed to open Dynamixel port");
//             return;
//         }
//         if (!portHandler_->setBaudRate(115200)) {
//             RCLCPP_ERROR(this->get_logger(), "Failed to set Dynamixel baudrate");
//             return;
//         }

//         // Enable Torque 1, 2
//         uint8_t dxl_error = 0;

//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_OPERATING_MODE, 1, &dxl_error);
//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_OPERATING_MODE, 1, &dxl_error);
//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_3, ADDR_OPERATING_MODE, 3, &dxl_error); // Gripper: Position mode

//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_TORQUE_ENABLE, 1, &dxl_error);
//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_TORQUE_ENABLE, 1, &dxl_error);
//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_3, ADDR_TORQUE_ENABLE, 1, &dxl_error);

//         try {
//             serial_.setPort("/dev/ttyUSB10");// STM 연결 포트
//             serial_.setBaudrate(115200);
//             serial::Timeout timeout = serial::Timeout::simpleTimeout(1000);
//             serial_.setTimeout(timeout);
//             serial_.open();
//         } catch (serial::IOException &e) {
//             RCLCPP_ERROR(this->get_logger(), "Unable to open STM32 serial port");
//             return;
//         }
//         if (!serial_.isOpen()) {
//             RCLCPP_ERROR(this->get_logger(), "STM32 serial port not open");
//             return;
//         }

//         dq_sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>("/joint_velocity", 10,
//             std::bind(&MotorControlNode::dq_callback, this, std::placeholders::_1));
//             //Float64MultiArray 메시지를 수신하면 this->dq_callback(msg) 실행
//         gripper_sub_ = this->create_subscription<std_msgs::msg::Float64>("/gripper_command", 10,
//             std::bind(&MotorControlNode::gripper_callback, this, std::placeholders::_1));

//         timer_ = this->create_wall_timer(std::chrono::milliseconds(1),
//             std::bind(&MotorControlNode::readFromSTM32, this));

//         current_qdot_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
//             "/current_qdot", 10
//         );


//         RCLCPP_INFO(this->get_logger(), "MotorControlNode initialized");
//     }

//     ~MotorControlNode() {
//         uint8_t dxl_error = 0;
//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_TORQUE_ENABLE, 0, &dxl_error);
//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_TORQUE_ENABLE, 0, &dxl_error);
//         packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_3, ADDR_TORQUE_ENABLE, 0, &dxl_error);
//         portHandler_->closePort();
//         if (serial_.isOpen()) serial_.close();
//     }

// private:
//     void dq_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
//     {
//         if (msg->data.size() != 6) {
//             RCLCPP_WARN(this->get_logger(), "Expected 6 joint velocities, but got %zu", msg->data.size());
//             return;
//         }

//         RCLCPP_INFO(this->get_logger(),
//         "[/joint_velocity] Received: [%.3f %.3f %.3f %.3f %.3f %.3f]",
//         msg->data[0], msg->data[1], msg->data[2],
//         msg->data[3], msg->data[4], msg->data[5]);

//         std::vector<double> dc_vals(msg->data.begin(), msg->data.begin() + 4); // STM32에 4개 전달
//         sendToSTM32(dc_vals);

//         int32_t dxl_vel_1 = static_cast<int32_t>(msg->data[4] * 41.8879); // Dynamixel 2개 전달
//         int32_t dxl_vel_2 = static_cast<int32_t>(msg->data[5] * 41.8879);
//         setDynamixelVelocity(DXL_ID_1, dxl_vel_1);
//         setDynamixelVelocity(DXL_ID_2, dxl_vel_2);
//     }
//     void gripper_callback(const std_msgs::msg::Float64::SharedPtr msg) {
//         int32_t gripper_goal = static_cast<int32_t>(msg->data);
//         uint8_t dxl_error = 0;
//         packetHandler_->write4ByteTxRx(portHandler_, DXL_ID_3, ADDR_GOAL_POSITION, static_cast<uint32_t>(gripper_goal), &dxl_error);
//     }
//     void setDynamixelVelocity(uint8_t id, int32_t vel) {
//         uint8_t dxl_error = 0;
//         packetHandler_->write4ByteTxRx(portHandler_, id, ADDR_GOAL_VELOCITY, static_cast<uint32_t>(vel), &dxl_error);
//     }

// void sendToSTM32(const std::vector<double>& velocities) {
//     if (velocities.size() < 4) return;

//     uint8_t packet[18]; // 0xAA, 16, float*4 = 17바이트
//     packet[0] = 0xAA; // 시작 바이트
//     packet[1] = 17;   // 데이터 길이

//     float vals[4] = {
//         static_cast<float>(velocities[0]),
//         static_cast<float>(velocities[1]),
//         static_cast<float>(velocities[2]),
//         static_cast<float>(velocities[3])
//     };
//     memcpy(&packet[2], reinterpret_cast<uint8_t*>(vals), sizeof(float) * 4);

//     serial_.write(packet, 18);  // 체크섬 제거 → 17바이트 전송
//     rclcpp::sleep_for(std::chrono::milliseconds(1)); 
// }


//     // void readFromSTM32() {
//     //     uint8_t rx_buf[19];
//     //     if (serial_.available() >= 19) {
//     //         serial_.read(rx_buf, 19);
//     //         if (rx_buf[0] == 0xAA && rx_buf[1] == 16) {
//     //             float dc_values[4];
//     //             memcpy(dc_values, &rx_buf[2], sizeof(float) * 4);
//     //             int sum = 0;
//     //             for (int i = 2; i < 18; ++i) sum += rx_buf[i];
//     //             if ((sum & 0xFF) == rx_buf[18]) {
//     //                 std_msgs::msg::Float64MultiArray msg;
//     //                 msg.data.resize(6);

//     //                 for (int i = 0; i < 4; ++i) // DC 모터 속도값 (msg[0]~msg[3])
//     //                     msg.data[i] = static_cast<double>(dc_values[i]); 

//     //                 for (int i = 0; i < 2; ++i) { // Dynamixel 속도값 추가 (msg[4]~msg[5])
//     //                     int32_t signed_vel = 0;
//     //                     uint8_t dxl_error = 0;
//     //                     packetHandler_->read4ByteTxRx(portHandler_, DXL_ID_1 + i, ADDR_PRESENT_VELOCITY,
//     //                                     reinterpret_cast<uint32_t*>(&signed_vel), &dxl_error);
//     //                     double radps = signed_vel * 0.229 * 2 * M_PI / 60.0;
//     //                     msg.data[4 + i] = radps;
//     //                 }
//     //                 RCLCPP_INFO(this->get_logger(), "Current joint velocities %f %f %f %f %f %f ", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
//     //                 current_qdot_pub_->publish(msg);
//     //             }
//     //         }
//     //     }
//     // }
    
// void readFromSTM32() {
//     const size_t PACKET_SIZE = 18; // 0xAA, 0x10, float*4 (16바이트)
//     const uint8_t PACKET_HEADER = 0xAA;
//     const uint8_t PACKET_TYPE = 0x10;

//     while (serial_.available() >= PACKET_SIZE) {
//         uint8_t temp;
//         if (serial_.read(&temp, 1) != 1) return;

//         if (temp != PACKET_HEADER) continue;

//         uint8_t maybe_packet[17];  // 남은 16바이트 (type + data)
//         size_t bytes_read = serial_.read(maybe_packet, 17);
//         if (bytes_read != 17) return;

//         if (maybe_packet[0] != PACKET_TYPE) continue;

//         float dc_values[4];
//         memcpy(dc_values, &maybe_packet[1], sizeof(float) * 4); // [1]부터가 float

//         std_msgs::msg::Float64MultiArray msg;
//         msg.data.resize(6);
//         for (int i = 0; i < 4; ++i)
//             msg.data[i] = static_cast<double>(dc_values[i]);

//         for (int i = 0; i < 2; ++i) {
//             int32_t signed_vel = 0;
//             uint8_t dxl_error = 0;
//             int dxl_comm_result = packetHandler_->read4ByteTxRx(
//                 portHandler_, DXL_ID_1 + i, ADDR_PRESENT_VELOCITY,
//                 reinterpret_cast<uint32_t*>(&signed_vel), &dxl_error);
//             if (dxl_comm_result == COMM_SUCCESS && dxl_error == 0) {
//                 double radps = signed_vel * 0.229 * 2 * M_PI / 60.0;
//                 msg.data[4 + i] = radps;
//             }
//         }

//         RCLCPP_INFO(this->get_logger(),
//             "Current joint velocities %.6f %.6f %.6f %.6f %.6f %.6f",
//             msg.data[0], msg.data[1], msg.data[2],
//             msg.data[3], msg.data[4], msg.data[5]);

//         current_qdot_pub_->publish(msg);
//         return;
//     }
// }
//     rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr dq_sub_;
//     rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr gripper_sub_;
//     rclcpp::TimerBase::SharedPtr timer_;
//     rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr current_qdot_pub_;

//     serial::Serial serial_;
//     dynamixel::PortHandler *portHandler_;
//     dynamixel::PacketHandler *packetHandler_;
// };
// int main(int argc, char * argv[]) {
//     rclcpp::init(argc, argv);
//     auto node = std::make_shared<MotorControlNode>();
//     rclcpp::spin(node);
//     rclcpp::shutdown();
//     return 0;
// }



#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "std_msgs/msg/float64.hpp"
#include "serial/serial.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <cmath>
#include <array>
#include <vector>
#include <thread>
#include <mutex>
#include <optional>

#define PROTOCOL_VERSION 2.0
#define DXL_ID_1 4
#define DXL_ID_2 5
#define DXL_ID_3 6

#define ADDR_TORQUE_ENABLE 64
#define ADDR_OPERATING_MODE 11
#define ADDR_GOAL_VELOCITY 104
#define ADDR_PRESENT_VELOCITY 128
#define ADDR_GOAL_POSITION 116

class MotorControlNode : public rclcpp::Node {
public:
    MotorControlNode() : Node("motorcontrol_node"), running_(true) {
        portHandler_ = dynamixel::PortHandler::getPortHandler("/dev/ttyUSB1");
        packetHandler_ = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

        if (!portHandler_->openPort() || !portHandler_->setBaudRate(115200)) {
            RCLCPP_ERROR(this->get_logger(), "Failed to open/set Dynamixel port");
            return;
        }

        uint8_t dxl_error = 0;
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_OPERATING_MODE, 1, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_OPERATING_MODE, 1, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_3, ADDR_OPERATING_MODE, 3, &dxl_error);

        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_TORQUE_ENABLE, 1, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_TORQUE_ENABLE, 1, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_3, ADDR_TORQUE_ENABLE, 1, &dxl_error);

        try {
            serial_.setPort("/dev/ttyUSB0");
            serial_.setBaudrate(115200);
            // serial_.setTimeout(serial::Timeout::simpleTimeout(1000));
            serial::Timeout timeout = serial::Timeout::simpleTimeout(1000); // ✅
            serial_.setTimeout(timeout);
            serial_.open();
        } catch (serial::IOException &e) {
            RCLCPP_ERROR(this->get_logger(), "Unable to open STM32 serial port");
            return;
        }

        dq_sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/joint_velocity", 10,
            std::bind(&MotorControlNode::dq_callback, this, std::placeholders::_1));
        gripper_sub_ = this->create_subscription<std_msgs::msg::Float64>(
            "/gripper_command", 10,
            std::bind(&MotorControlNode::gripper_callback, this, std::placeholders::_1));
        current_qdot_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/current_qdot", 10);

        serial_thread_ = std::thread(&MotorControlNode::serialReadingLoop, this);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(1),
            std::bind(&MotorControlNode::publishLatestMsg, this));

        RCLCPP_INFO(this->get_logger(), "MotorControlNode initialized");
    }

    ~MotorControlNode() {
        running_ = false;
        if (serial_thread_.joinable()) serial_thread_.join();

        uint8_t dxl_error = 0;
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_1, ADDR_TORQUE_ENABLE, 0, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_2, ADDR_TORQUE_ENABLE, 0, &dxl_error);
        packetHandler_->write1ByteTxRx(portHandler_, DXL_ID_3, ADDR_TORQUE_ENABLE, 0, &dxl_error);
        portHandler_->closePort();
        if (serial_.isOpen()) serial_.close();
    }

private:
    void dq_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
        if (msg->data.size() != 6) {
            RCLCPP_WARN(this->get_logger(), "Expected 6 joint velocities, got %zu", msg->data.size());
            return;
        }

        std::vector<double> dc_vals(msg->data.begin(), msg->data.begin() + 4);
        sendToSTM32(dc_vals);

        int32_t dxl_vel_1 = static_cast<int32_t>(msg->data[4] * 41.8879);
        int32_t dxl_vel_2 = static_cast<int32_t>(msg->data[5] * 41.8879);
        setDynamixelVelocity(DXL_ID_1, dxl_vel_1);
        setDynamixelVelocity(DXL_ID_2, dxl_vel_2);
    }

    void gripper_callback(const std_msgs::msg::Float64::SharedPtr msg) {
        int32_t gripper_goal = static_cast<int32_t>(msg->data);
        uint8_t dxl_error = 0;
        packetHandler_->write4ByteTxRx(portHandler_, DXL_ID_3, ADDR_GOAL_POSITION, static_cast<uint32_t>(gripper_goal), &dxl_error);
    }

    void setDynamixelVelocity(uint8_t id, int32_t vel) {
        uint8_t dxl_error = 0;
        packetHandler_->write4ByteTxRx(portHandler_, id, ADDR_GOAL_VELOCITY, static_cast<uint32_t>(vel), &dxl_error);
    }

    void sendToSTM32(const std::vector<double>& velocities) {
        if (velocities.size() < 4) return;

        uint8_t packet[18];
        packet[0] = 0xAA;
        packet[1] = 17;

        float vals[4] = {
            static_cast<float>(velocities[0]),
            static_cast<float>(velocities[1]),
            static_cast<float>(velocities[2]),
            static_cast<float>(velocities[3])
        };
        memcpy(&packet[2], reinterpret_cast<uint8_t*>(vals), sizeof(float) * 4);

        serial_.write(packet, 18);
    }

    void serialReadingLoop() {
        const size_t PACKET_SIZE = 18;
        const uint8_t PACKET_HEADER = 0xAA;
        const uint8_t PACKET_TYPE = 0x10;

        while (running_) {
            if (serial_.available() < PACKET_SIZE) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }

            uint8_t temp;
            if (serial_.read(&temp, 1) != 1 || temp != PACKET_HEADER) continue;

            uint8_t maybe_packet[17];
            if (serial_.read(maybe_packet, 17) != 17 || maybe_packet[0] != PACKET_TYPE) continue;

            float dc_values[4];
            memcpy(dc_values, &maybe_packet[1], sizeof(float) * 4);

            std::array<double, 6> data;
            for (int i = 0; i < 4; ++i)
                data[i] = static_cast<double>(dc_values[i]);

            for (int i = 0; i < 2; ++i) {
                int32_t signed_vel = 0;
                uint8_t dxl_error = 0;
                int dxl_comm_result = packetHandler_->read4ByteTxRx(
                    portHandler_, DXL_ID_1 + i, ADDR_PRESENT_VELOCITY,
                    reinterpret_cast<uint32_t*>(&signed_vel), &dxl_error);
                if (dxl_comm_result == COMM_SUCCESS && dxl_error == 0) {
                    data[4 + i] = signed_vel * 0.229 * 2 * M_PI / 60.0;
                }
            }

            {
                std::lock_guard<std::mutex> lock(data_mutex_);
                latest_msg_ = data;
            }
        }
    }

    void publishLatestMsg() {
        std::lock_guard<std::mutex> lock(data_mutex_);
        if (!latest_msg_) return;

        std_msgs::msg::Float64MultiArray msg;
        msg.data.resize(6);
        for (size_t i = 0; i < 6; ++i)
            msg.data[i] = (*latest_msg_)[i];

        current_qdot_pub_->publish(msg);
    }

    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr dq_sub_;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr gripper_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr current_qdot_pub_;

    serial::Serial serial_;
    dynamixel::PortHandler *portHandler_;
    dynamixel::PacketHandler *packetHandler_;

    std::thread serial_thread_;
    std::mutex data_mutex_;
    std::optional<std::array<double, 6>> latest_msg_;
    bool running_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MotorControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
