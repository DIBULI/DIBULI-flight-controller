#include "system_tasks.hpp"

void system_task_led_blink(void *pvParameters) {
  while(1) {
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

void system_task_read_imu(void *pvParameters) {
  float* imuData  = (float*) pvParameters;
  while(1) {
    board_bridge->read_imu_data(imuData, imuData[6]);
    vTaskDelay(pdMS_TO_TICKS(1000 / 200));
  }

  vTaskDelete( NULL );
}

void system_task_uart_helloworld(void *pvParameters) {
  uint8_t tx_buf[] = "Hello World";
  while(1) {
    board_bridge->uart_send_message(tx_buf, sizeof(tx_buf));
    vTaskDelay(pdMS_TO_TICKS(1000 / 200));
  }
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

  xTaskCreate(
    system_task_read_imu,
    "task_read_imu",
    configMINIMAL_STACK_SIZE,
    sensor_manager->imuReadings.data(),
    configMAX_PRIORITIES - 2, 
    NULL
  );

  xTaskCreate(
    system_task_uart_helloworld,
    "task_uart_helloworld",
    configMINIMAL_STACK_SIZE,
    NULL,
    configMAX_PRIORITIES - 2, 
    NULL
  );
}