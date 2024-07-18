#include "common/circular_byte_array.hpp"



CircularByteArray::CircularByteArray(uint32_t size) {
  byteArray = (uint8_t *) pvPortMalloc(sizeof(uint8_t) * size);
  arraySize = size;
  headerIndex = 0;
  tailIndex = 0;
  // length = headerIndex < tailIndex ? headerIndex + size - tailIndex : headerIndex - tailIndex;
  length = 0;
  xMutex = xSemaphoreCreateBinary();
  xSemaphoreGive(xMutex);
}

CircularByteArray::~CircularByteArray() {
  vPortFree(byteArray);
}

uint8_t CircularByteArray::append(const uint8_t* data, uint32_t size) {
  if (xSemaphoreTake(xMutex, ( TickType_t ) 10) == pdTRUE) {
    if (size > remain()) {
      return 1;
    } else {
      uint32_t lengthToTheEnd = arraySize - headerIndex;
      
      if (lengthToTheEnd > size) {  // if the remaining array (to the end) capacity can store all the request data
        memcpy(this->byteArray + headerIndex, data, size);
        headerIndex += size;
        headerIndex %= arraySize;
      } else {  // if the remaining array (to the end) capacity can  not store all the request data
        memcpy(this->byteArray + headerIndex, data, lengthToTheEnd);
        memcpy(this->byteArray, data + lengthToTheEnd, size - lengthToTheEnd);
        headerIndex = size - lengthToTheEnd;
      }
      length += size;

      xSemaphoreGive(xMutex);
      return 0;
    }
  } else {
    return 100;
  }
}

uint8_t CircularByteArray::peek(uint8_t* data, uint32_t size, uint32_t offset) {
  if (xSemaphoreTake(xMutex, ( TickType_t ) 10) == pdTRUE) {
    uint32_t lengthToTheEnd = arraySize - tailIndex - offset;

    if (lengthToTheEnd > size) { // if the remaining array (to the end) capacity can retrieve all the request data
      memcpy(data, this->byteArray + this->tailIndex + offset, size);
    } else { // if the remaining array (to the end) capacity can not retrieve all the request data
      memcpy(data, this->byteArray + this->tailIndex + offset, lengthToTheEnd);
      memcpy(data + lengthToTheEnd, this->byteArray, size - lengthToTheEnd);
    }

    xSemaphoreGive(xMutex);
    return 0;
  } else {
    return 100;
  }
}

uint8_t CircularByteArray::remove(uint32_t size) {
  if (xSemaphoreTake(xMutex, ( TickType_t ) 10) == pdTRUE) {
    uint32_t lengthToTheEnd = arraySize - tailIndex;

    if (lengthToTheEnd > size) { // if the remaining array (to the end) capacity can delete the requested data size
      tailIndex += size;
      tailIndex %= arraySize;
    } else { // if the remaining array (to the end) capacity can not delete the requested data size
      tailIndex = size - lengthToTheEnd;
    }

    length -= size;

    xSemaphoreGive(xMutex);
    return 0;
  } else {
    return 100;
  }
}

uint32_t CircularByteArray::remain() {
  return arraySize - length;
}

uint32_t CircularByteArray::size() {
  return length;
}

uint32_t CircularByteArray::totalSize() {
  return arraySize;
}

void CircularByteArray::clean() {
  if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
    headerIndex = 0;
    tailIndex = 0;
    length = 0;
  }
}

bool CircularByteArray::isFull() {
  return this->length == this->arraySize;
}