#ifndef CIRCULAR_BYTE_ARRAY_HPP
#define CIRCULAR_BYTE_ARRAY_HPP

#include "stdint.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "string.h"

class CircularByteArray {
public:
  CircularByteArray(uint32_t size);
  ~CircularByteArray();

  uint8_t append(const uint8_t* data, uint32_t size);
  uint8_t peek(uint8_t* data, uint32_t size, uint32_t offset);
  uint8_t remove(uint32_t size);
  uint32_t remain();
  uint32_t size();
  bool isFull();
  uint32_t totalSize();
  void clean();

private:
  uint32_t headerIndex;
  uint32_t tailIndex;
  uint8_t* byteArray;
  uint32_t arraySize;
  uint32_t length;
  SemaphoreHandle_t xMutex;
};

#endif /* CIRCULAR_BYTE_ARRAY_HPP */
