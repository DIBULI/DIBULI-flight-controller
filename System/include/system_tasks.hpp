#ifndef SYSTEM_TASKS_HPP
#define SYSTEM_TASKS_HPP

#include "board_bridge.hpp"
#include "sensors/sensor_manager.hpp"
#include "messages/message_manager.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"

extern BoardBridge* board_bridge;

extern SensorManager* sensor_manager;

extern MessageManager* message_manager;

void create_system_tasks();

void system_task_led_blink(void *pvParameters);

void system_task_read_imu(void *pvParameters);

void system_task_uart_helloworld(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_TASKS_HPP */
