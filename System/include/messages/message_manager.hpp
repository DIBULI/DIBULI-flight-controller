#ifndef MESSAGE_MANAGER_HPP
#define MESSAGE_MANAGER_HPP

#include "board_bridge.hpp"
#include "sensors/sensor_manager.hpp"
#include "dprotocol/d_protocol.hpp"
#include "dprotocol/circular_byte_array.hpp"
#include "dprotocol/d_protocol_message.hpp"

class MessageManager {
public:
  MessageManager(BoardBridge *board_bridge, CircularByteArray *cba, SensorManager* sensor_manager);
  ~MessageManager();

  void handle_message_task();

  void process_message(DProtocolMessage msg);

  BoardBridge *board_bridge;
  CircularByteArray *cba;
  SensorManager* sensor_manager;
  DProtocal dprotocol;
};

#endif /* MESSAGE_MANAGER_HPP */
