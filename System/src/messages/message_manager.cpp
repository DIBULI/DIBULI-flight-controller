#include "messages/message_manager.hpp"

MessageManager::MessageManager(BoardBridge *board_bridge, CircularByteArray *cba, SensorManager* sensor_manager) {
  this->board_bridge = board_bridge;
  this->cba = cba;
  this->sensor_manager = sensor_manager;
  this->messageBinary = new uint8_t[sizeof(float) * 7 + 8];
  for (int i=0; i < sizeof(float) * 7 + 8; i++) {
    messageBinary[i] = 0;
  }
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

void MessageManager::process_message(DProtocolMessage msg) {
  if (msg.type == 0) { // heartbeat message  
    board_bridge->uart_send_message(tx_buf, sizeof(tx_buf));
  } if (msg.type == 1) { // echo message  
    board_bridge->uart_send_message(tx_buf1, sizeof(tx_buf1));
  } if (msg.type == 2) { // imu message
    this->dprotocol.wrapMessage(messageBinary, 2, (uint8_t *)sensor_manager->imuReadings, sizeof(float) * 7);
    board_bridge->uart_send_message(messageBinary, sizeof(float) * 7 + 8);
  }
}