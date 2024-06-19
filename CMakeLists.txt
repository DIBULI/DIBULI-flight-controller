cmake_minimum_required(VERSION 3.22)

# Set the project name
set(CMAKE_PROJECT_NAME dibuli-flight-controller)
# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

enable_language(C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 11)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

set(BOARD "stm32f103" CACHE STRING "Set the board type")

# Include board related toolchain file and libraries
message(STATUS "Have chosen board: ${BOARD}")
add_subdirectory("boards")
# Add STM32CubeMX generated sources

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

FILE(GLOB_RECURSE FC_SOURCE_FILES 
  System/src/**.cpp
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${FC_SOURCE_FILES}
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    System/include
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    ${BOARD_LIB}
    board_bridge_lib
)

add_custom_command(
    TARGET  ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex
    COMMENT "Creating the hex file.")

add_custom_command(
    TARGET  ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Creating the bin file.")

add_custom_command(
    TARGET  ${CMAKE_PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf
)

add_custom_target(flash-firmware
    DEPENDS ${CMAKE_PROJECT_NAME}.bin
    COMMAND st-flash --reset write ${CMAKE_PROJECT_NAME}.bin 0x08000000
)