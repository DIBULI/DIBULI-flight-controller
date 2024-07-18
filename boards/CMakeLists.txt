enable_language(C ASM)

if (BOARD STREQUAL "stm32f103")
  set(FREERTOS_PORT "GCC_ARM_CM3" CACHE STRING "")
  set(FREERTOS_CONFIG_FILE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${BOARD}/Core/Inc" CACHE STRING "")

  set(BOARD_NAME_MACRO "STM32F103" CACHE STRING "")
  set(BOARD_FREERTOS_NEEDED_INCLUDE_DIRS 
    "${CMAKE_CURRENT_LIST_DIR}/${BOARD}/Drivers/CMSIS/Device/ST/STM32F1xx/Include" 
    "${CMAKE_CURRENT_LIST_DIR}/${BOARD}/Drivers/CMSIS/Include" CACHE STRING "")
  set(BOARD_SYSTEM_NEEDED_INCLUDE_DIRS 
    "${CMAKE_CURRENT_LIST_DIR}/${BOARD}/Drivers/CMSIS/Device/ST/STM32F1xx/Include" CACHE STRING "")
  
  add_subdirectory(${BOARD}/cmake/stm32cubemx)
  set(BOARD_LIB stm32cubemx)
  set(BOARD_BRIDGE_IMPL "${CMAKE_CURRENT_LIST_DIR}/src/stm32f103_board_bridge.cpp")
endif()

add_library(board_bridge_lib STATIC)

target_include_directories(board_bridge_lib PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(board_bridge_lib PUBLIC
  ${BOARD_BRIDGE_IMPL}
  src/common/circular_byte_array.cpp
)

add_subdirectory(../FreeRTOS-Kernel ${CMAKE_BINARY_DIR}/FreeRTOS-Kernel)

target_link_libraries(board_bridge_lib
  ${BOARD_LIB}
  freertos_kernel
)