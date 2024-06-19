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

  uint8_t task_led_on();

  uint8_t task_led_off();
};

#endif /* BOARD_BRIDGE_HPP */
