#include "FreeRTOS.h"
#include "task.h"

#include "board_bridge.hpp"

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

int main(void) {

  board_bridge->initialize();
  
  vTaskStartScheduler();

  while (1) {}

  return 0;
}