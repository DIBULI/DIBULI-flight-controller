#include "FreeRTOS.h"
#include "task.h"

#include "board_bridge.hpp"
#include "system_tasks.hpp"

#include "dprotocol/circular_byte_array.hpp"

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

CircularByteArray* cba = new CircularByteArray(256);

MessageManager* message_manager = new MessageManager(board_bridge, cba, sensor_manager);

bool freeRTOS_started;

int main(void) {

  board_bridge->initialize();

  create_system_tasks();
  
  // indicate that freeRTOS has been started and now can use semphr
  freeRTOS_started = true;

  cba->clean();
  
  vTaskStartScheduler();

  while (1) {}

  return 0;
}