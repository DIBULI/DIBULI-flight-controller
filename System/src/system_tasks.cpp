#include "system_tasks.hpp"

void system_task_led_blink(void *pvParameters) {
  while(1)
  {
    board_bridge->task_led_on();
    vTaskDelay(pdMS_TO_TICKS(500));
    board_bridge->task_led_off();
    vTaskDelay(pdMS_TO_TICKS(500));
  }

  /* Tasks must not attempt to return from their implementing
  function or otherwise exit.  In newer FreeRTOS port
  attempting to do so will result in an configASSERT() being
  called if it is defined.  If it is necessary for a task to
  exit then have the task call vTaskDelete( NULL ) to ensure
  its exit is clean. */
  vTaskDelete( NULL );
}

void create_system_tasks() {
  xTaskCreate(
    system_task_led_blink,
    "task_led_blink",
    configMINIMAL_STACK_SIZE,
    NULL,
    configMAX_PRIORITIES - 1, 
    NULL
  );
}