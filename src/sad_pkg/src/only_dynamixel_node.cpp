#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace dynamixel;

//----------------------------------------------------------------
// Control table addresses and conversion factors
//----------------------------------------------------------------
#define H_ADDR_TORQUE_ENABLE        512   // H54
#define H_ADDR_GOAL_POSITION        564   // H54
#define H_ADDR_PRESENT_POSITION     580   // H54
#define H_ADDR_PROFILE_ACCELERATION 556
#define H54_RAD2POS                 159767.053
#define H54_POS2RAD                 0.000006259

#define P_ADDR_TORQUE_ENABLE        512   // PH42
#define P_ADDR_GOAL_POSITION        564   // PH42
#define P_ADDR_PRESENT_POSITION     580   // PH42
#define P_ADDR_PROFILE_ACCELERATION 556
#define PH42_RAD2POS                96686.6279
#define PH42_POS2RAD                0.000010343

#define L_ADDR_TORQUE_ENABLE        562   // L42
#define L_ADDR_GOAL_POSITION        596   // L42
#define L_ADDR_PRESENT_POSITION     611   // L42
#define L_ADDR_PROFILE_ACCELERATION 604
#define L42_RAD2POS                 651.898646904
#define L42_POS2RAD                 0.00153398078

//----------------------------------------------------------------
// Other settings
//----------------------------------------------------------------
#define PROTOCOL_VERSION    2.0
#define NUM_MOTORS          6
#define BAUDRATE            2000000
#define DEVICE_NAME         "/dev/ttyUSB0"

// Fixed model type per ID
static const uint16_t fixed_model_types[NUM_MOTORS]
  = {54025, 54025, 54025, 2000, 2000, 35072};

class ArmControllerNode : public rclcpp::Node
{
public:
  ArmControllerNode()
  : Node("arm_controller_node"),
    port_handler_( PortHandler::getPortHandler(DEVICE_NAME) ),
    packet_handler_( PacketHandler::getPacketHandler(PROTOCOL_VERSION) ),
    group_bulk_read_( port_handler_, packet_handler_ ),
    group_bulk_write_( port_handler_, packet_handler_ ),
    g_cmd_received_(false),
    init_bulk_read_(false)
  {
    // 1) 포트 열기 & Baudrate 설정
    if (!port_handler_->openPort() ||
        !port_handler_->setBaudRate(BAUDRATE))
    {
      RCLCPP_FATAL(get_logger(), "Failed to open port or set baudrate");
      rclcpp::shutdown();
      return;
    }

    // 2) 모든 모터 토크 Enable & Profile Acc 설정 (반복 재시도)
    bool all_ok = false;
    while (rclcpp::ok() && !all_ok) {
      all_ok = true;
      for (int id = 0; id < NUM_MOTORS; ++id) {
        uint16_t model = fixed_model_types[id];
        uint16_t torque_addr, accel_addr;
        if      (model == 2000) { torque_addr=P_ADDR_TORQUE_ENABLE;      accel_addr=P_ADDR_PROFILE_ACCELERATION; }
        else if (model == 35072){ torque_addr=L_ADDR_TORQUE_ENABLE;      accel_addr=L_ADDR_PROFILE_ACCELERATION; }
        else                   { torque_addr=H_ADDR_TORQUE_ENABLE;      accel_addr=H_ADDR_PROFILE_ACCELERATION; }

        uint8_t err = 0;
        int res = packet_handler_->write1ByteTxRx(
          port_handler_, id, torque_addr, 1, &err);
        if (res != COMM_SUCCESS) {
          RCLCPP_ERROR(get_logger(),
            "Enable torque failed for ID %d (%d)", id, res);
          all_ok = false;
          continue;
        }
        // H54, PH42 만 Acceleration 설정
        if (model != 35072) {
          res = packet_handler_->write4ByteTxRx(
            port_handler_, id, accel_addr, 800, &err);
          if (res != COMM_SUCCESS) {
            RCLCPP_ERROR(get_logger(),
              "Set accel failed for ID %d (%d)", id, res);
            all_ok = false;
          }
        }
      }
      if (!all_ok) {
        RCLCPP_WARN(get_logger(),
          "Some motors failed to init. Retrying in 0.5s...");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    }
    RCLCPP_INFO(get_logger(), "All motors initialized");

    // 3) Subscription & Publisher (Float64MultiArray)
    cmd_sub_ = create_subscription<std_msgs::msg::Float64MultiArray>(
      "/target_q", 10,
      std::bind(&ArmControllerNode::commandCallback, this, std::placeholders::_1));

    array_pub_ = create_publisher<std_msgs::msg::Float64MultiArray>(
      "/dynamixel_q", 10);

    // 4) Timers: 쓰기 20Hz, 읽기 50Hz
    write_timer_ = create_wall_timer(
      std::chrono::milliseconds(50),
      std::bind(&ArmControllerNode::writeCommand, this));

    read_timer_ = create_wall_timer(
      std::chrono::milliseconds(20),
      std::bind(&ArmControllerNode::publishJointArray, this));
  }

  ~ArmControllerNode() override
  {
    // 종료 시 토크 끄고 포트 닫기
    for (int id = 0; id < NUM_MOTORS; ++id) {
      uint16_t addr = (fixed_model_types[id]==2000?P_ADDR_TORQUE_ENABLE:
                       fixed_model_types[id]==35072?L_ADDR_TORQUE_ENABLE:
                       H_ADDR_TORQUE_ENABLE);
      uint8_t err = 0;
      packet_handler_->write1ByteTxRx(port_handler_, id, addr, 0, &err);
    }
    port_handler_->closePort();
  }

private:
  void commandCallback(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
  {
    if (msg->data.size() >= 7) {
      g_cmd_ = msg->data;
      g_cmd_received_ = true;
    } else {
      RCLCPP_WARN(get_logger(),
        "Expected ≥7 elems, got %zu", msg->data.size());
    }
  }

  void writeCommand()
  {
    if (!g_cmd_received_) return;

    double cmd[NUM_MOTORS];
    cmd[0]=g_cmd_[0]; cmd[1]=g_cmd_[1]; cmd[2]=g_cmd_[2];
    cmd[3]=g_cmd_[3]; cmd[4]=g_cmd_[5]; cmd[5]=g_cmd_[6];

    uint32_t goal[NUM_MOTORS];
    group_bulk_write_.clearParam();

    for (int id=0; id<NUM_MOTORS; ++id) {
      uint16_t model = fixed_model_types[id];
      uint16_t addr;
      double r2p;
      if      (model==2000){ addr=P_ADDR_GOAL_POSITION;      r2p=PH42_RAD2POS; }
      else if (model==35072){addr=L_ADDR_GOAL_POSITION;      r2p=L42_RAD2POS; }
      else                 { addr=H_ADDR_GOAL_POSITION;      r2p=H54_RAD2POS; }

      goal[id] = static_cast<uint32_t>(cmd[id]*r2p);
      group_bulk_write_.addParam(
        id, addr, 4, (uint8_t*)&goal[id]);
    }
    int res = group_bulk_write_.txPacket();
    if (res!=COMM_SUCCESS) {
      RCLCPP_ERROR(get_logger(),
        "BulkWrite failed: %d", res);
    }
    group_bulk_write_.clearParam();
    g_cmd_received_ = false;
  }

  void publishJointArray()
  {
    if (!init_bulk_read_) {
      group_bulk_read_.clearParam();
      for (int id=0; id<NUM_MOTORS; ++id){
        uint16_t model = fixed_model_types[id];
        uint16_t addr = (model==2000?P_ADDR_PRESENT_POSITION:
                         model==35072?L_ADDR_PRESENT_POSITION:
                         H_ADDR_PRESENT_POSITION);
        bool addparam_result = group_bulk_read_.addParam(id, addr, 4);
        if (!addparam_result) {
                RCLCPP_ERROR(get_logger(),"Failed to add param for ID %d (position)", id);
                continue;
            }
      }
      init_bulk_read_ = true;
    }

    int res = group_bulk_read_.txRxPacket();
    std::vector<double> pos(NUM_MOTORS,0.0);
    if (res==COMM_SUCCESS) {
      for (int id=0; id<NUM_MOTORS; ++id){
        uint16_t model = fixed_model_types[id];
        double p2r = (model==2000?PH42_POS2RAD:
                      model==35072?L42_POS2RAD:
                      H54_POS2RAD);
        int32_t raw = group_bulk_read_.getData(id,
          (model==2000?P_ADDR_PRESENT_POSITION:
           model==35072?L_ADDR_PRESENT_POSITION:
           H_ADDR_PRESENT_POSITION), 4);
        pos[id] = raw * p2r;
      }
      last_pos_ = pos;
    } else {
      RCLCPP_ERROR(get_logger(),
        "BulkRead failed: %d", res);
      pos = last_pos_;
    }

    // Publish as Float64MultiArray
    std_msgs::msg::Float64MultiArray msg;
    msg.data.resize(NUM_MOTORS);
    for (size_t i = 0; i < NUM_MOTORS; ++i) {
      msg.data[i] = pos[i];
    }
    array_pub_->publish(msg);
  }

  // members
  PortHandler    *port_handler_;
  PacketHandler  *packet_handler_;
  GroupBulkRead   group_bulk_read_;
  GroupBulkWrite  group_bulk_write_;

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr cmd_sub_;
  rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr array_pub_;
  rclcpp::TimerBase::SharedPtr write_timer_;
  rclcpp::TimerBase::SharedPtr read_timer_;

  std::vector<double>       g_cmd_;
  bool                      g_cmd_received_;
  bool                      init_bulk_read_;
  std::vector<double>       last_pos_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmControllerNode>());
  rclcpp::shutdown();
  return 0;
}
