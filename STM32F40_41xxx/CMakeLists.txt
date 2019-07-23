cmake_minimum_required(VERSION 3.1)

enable_language(ASM)

#skip compiler features test
#set(CMAKE_C_COMPILER_WORK ON)
#set(CMAKE_CXX_COMPILER_WORK ON)

add_definitions(-DSTM32F40_41xxx)
add_definitions(-DSTM32F407xx)
add_definitions(-DCMAKE_SYSTEM_NAME=Generic)
add_definitions(-DUSE_STDPERIPH_DRIVER)
add_definitions(-DUSE_FULL_ASSERT)
add_definitions(-DHSE_VALUE=8000000)
add_definitions(-DUSE_STM324xG_EVAL)

include_directories(
		STM32F40_41xxx/stdperiphlib/include
		STM32F40_41xxx/CMSIS/system/include
		STM32F40_41xxx/CMSIS/include
		tools
)

aux_source_directory(
		STM32F40_41xxx/stdperiphlib/source
		STD_PERIPH_LIB_SOURCE
)

aux_source_directory(
		STM32F40_41xxx/CMSIS/system/source
		SYSTEM_SOURCE
)

set(
		STARTUP_ASM
		STM32F40_41xxx/startup/startup_stm32f40_41xxx.s
)

set(
		LINKER_SCRIPT
		D:/toolchain/STM32F40_41xxx/STM32F417IG_FLASH.ld
)

set(
		CMAKE_EXE_LINKER_FLAGS
		"${CMAKE_EXE_LINKER_FLAGS} -T${LINKER_SCRIPT}"
)

add_executable(
		main
		main.cpp
		exception_handlers.cpp
		${STD_PERIPH_LIB_SOURCE}
		${SYSTEM_SOURCE}
		${STARTUP_ASM}
)
add_custom_command(TARGET main POST_BUILD
		COMMAND copy main main.elf
		COMMAND arm-none-eabi-objcopy -O ihex main main.hex
		COMMAND arm-none-eabi-objcopy -O binary main main.bin
		COMMAND arm-none-eabi-objdump -D -S main > main.s)