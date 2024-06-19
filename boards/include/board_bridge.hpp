#ifndef BOARD_BRIDGE_HPP
#define BOARD_BRIDGE_HPP

#include "FreeRTOS.h"
#include "task.h"

class BoardBridge {
public:
  BoardBridge();
  ~BoardBridge();

  uint8_t initialize();

  uint8_t configure_sensors();

  uint8_t task_led_on();

  uint8_t task_led_off();

  uint8_t configure_imu();
  
  uint8_t read_imu_data(float* data, float &temp);
};

#endif /* BOARD_BRIDGE_HPP */
