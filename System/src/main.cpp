#include "FreeRTOS.h"
#include "task.h"

#include "board_bridge.hpp"
#include "system_tasks.hpp"

void *operator new(size_t size) {
  return pvPortMalloc(size);
}

void *operator new[](size_t size){
	return pvPortMalloc(size); 
}

void operator delete(void *ptr) {
  vPortFree(ptr);
}

void operator delete[](void *p){
	vPortFree(p); 
}

BoardBridge* board_bridge = new BoardBridge();

SensorManager* sensor_manager = new SensorManager();

int main(void) {

  board_bridge->initialize();


  board_bridge->configure_sensors();

  create_system_tasks();
  
  vTaskStartScheduler();

  while (1) {}

  return 0;
}