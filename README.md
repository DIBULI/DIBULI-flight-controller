# DIBULI Flight Controller

This repo contains the source codes used for self-designed flight controller.

## Dependecy required

1. st-link utils
2. arm gnu toolchain
3. cmake tools

## supported MCU

1. stm32f103cx

## Modules

1. Board Bridge - Taking charge of the communication between the flight controlling system and the hardwares
2. State estimation - TBD


## How to build

```
git clone git@github.com:DIBULI/Dibuli-flight-controller.git
cd Dibuli-flight-controller
BUILD_CMAKE_PRESET=stm32f103-Release
mkdir build && cd build
cmake --preset=$BUILD_CMAKE_PRESET ..
cd $BUILD_CMAKE_PRESET 
cmake --build .
```

## How to upload the firmware

```
BUILD_CMAKE_PRESET=stm32f103-Release
cd build/$BUILD_CMAKE_PRESET
cmake --build . --target flash-firmware
```