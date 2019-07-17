set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(TOOLCHAIN_DIR
		"D:/gccarm/8 2019-q3-update")
set(TOOLCHAIN_INCLUDE_DIR
		"${TOOLCHAIN_DIR}/arm-none-eabi/include"
		"${TOOLCHAIN_DIR}/lib/gcc/arm-none-eabi/8.3.1/include")
set(TOOLCHAIN_LIB_DIR
		"${TOOLCHAIN_DIR}/arm-none-eabi/lib"
		"${TOOLCHAIN_DIR}/lib/gcc/arm-none-eabi/8.3.1/thumb/v7/nofp")

set(CMAKE_ARM_FLAGS "-mcpu=cortex-m4 -mthumb -specs=nosys.specs")

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_ARM_FLAGS}")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_ARM_FLAGS} -Os -std=c++11 -ffreestanding")

#skip compiler features test
set(CMAKE_C_COMPILER_WORKS ON)
set(CMAKE_CXX_COMPILER_WORKS ON)

set(CMAKE_FIND_ROOT_PATH "${TOOLCHAIN_DIR}/arm-none-eabi")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

include_directories(${TOOLCHAIN_INCLUDE_DIR})

set(CMAKE_INCLUDE_PATH ${TOOLCHAIN_INCLUDE_DIR})

set(CMAKE_LIBRARY_PATH ${TOOLCHAIN_LIB_DIR})