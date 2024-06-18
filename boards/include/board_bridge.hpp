#ifndef BOARD_BRIDGE_HPP
#define BOARD_BRIDGE_HPP

#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"

class BoardBridge {
public:
  BoardBridge();
  ~BoardBridge();

  uint8_t initialize();

  uint8_t task_led_blink(void *pvParameters);
};

extern BoardBridge* board_bridge;

extern "C" {
  void system_task_led_blink(void *pvParameters);
}

#endif /* BOARD_BRIDGE_HPP */
