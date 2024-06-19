#ifndef SYSTEM_TASKS_HPP
#define SYSTEM_TASKS_HPP

#include "board_bridge.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"

extern BoardBridge* board_bridge;

void create_system_tasks();

void system_task_led_blink(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_TASKS_HPP */
