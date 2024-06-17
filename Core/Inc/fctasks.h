#ifndef FCTASKS_H
#define FCTASKS_H

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f1xx_hal.h"

void task_led_blink(void *pvParameters);

#endif /* FCTASKS_H */
