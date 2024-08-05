#include "messages/message_manager.hpp"

MessageManager::MessageManager(BoardBridge *board_bridge, CircularByteArray *cba, SensorManager* sensor_manager) {
  this->board_bridge = board_bridge;
  this->cba = cba;
  this->sensor_manager = sensor_manager;
}

MessageManager::~MessageManager() {}

void MessageManager::handle_message_task() {
  DProtocolMessage msg;
  uint8_t ret = this->dprotocol.retrieveMessage(cba, &msg);

  if (ret == 0) {
    this->process_message(msg);
    msg.clean();
  } else if (ret == 10) {
    cba->remove(1);
    dprotocol.cleanCBA(cba);
  }
}

uint8_t tx_buf[] = "HeartBeat received!\r\n";
uint8_t tx_buf1[] = "echoechoechoe\r\n";


// 辅助函数，用于将整数转换为字符串
std::string intToString(int num) {
    if (num == 0) return "0";
    std::string str;
    bool isNegative = num < 0;
    if (isNegative) num = -num;

    while (num > 0) {
        str.insert(str.begin(), '0' + (num % 10));
        num /= 10;
    }

    if (isNegative) str.insert(str.begin(), '-');
    return str;
}

// 辅助函数，用于将浮点数转换为字符串
std::string floatToString(float num, int precision = 2) {
    int integerPart = static_cast<int>(num);
    float fractionalPart = num - integerPart;

    std::string result = intToString(integerPart) + ".";

    for (int i = 0; i < precision; ++i) {
        fractionalPart *= 10;
        int digit = static_cast<int>(fractionalPart);
        result += '0' + digit;
        fractionalPart -= digit;
    }

    return result;
}

// 主函数，将 vector<float> 转换为字符串
std::string vectorToString(const std::vector<float>& vec) {
    std::string result;

    for (size_t i = 0; i < vec.size(); ++i) {
        result += floatToString(vec[i]);
        if (i != vec.size() - 1) {
            result += " "; // 添加空格分隔符
        }
    }

    result += "\r\n";

    return result;
}

void MessageManager::process_message(DProtocolMessage msg) {
  if (msg.type == 0) { // heartbeat message  
    board_bridge->uart_send_message(tx_buf, sizeof(tx_buf));
  } if (msg.type == 1) { // echo message  
    board_bridge->uart_send_message(tx_buf1, sizeof(tx_buf1));
  } if (msg.type == 2) { // imu message  
    std::string result = vectorToString(sensor_manager->imuReadings);
    board_bridge->uart_send_message((uint8_t *) result.c_str(), result.size());
  }
}