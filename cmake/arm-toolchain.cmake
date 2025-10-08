set(CMAKE_C_COMPILER "$ENV{ARM_GCC}/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "$ENV{ARM_GCC}/arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "$ENV{ARM_GCC}/arm-none-eabi-gcc")
set(CMAKE_OBJCOPY "$ENV{ARM_GCC}/arm-none-eabi-objcopy")

SET(CMAKE_CROSSCOMPILING 1)
SET(CMAKE_SYSTEM_NAME RaspberryPico)

set(CPU_TYPE "-mcpu=cortex-m33")
set(ARCH "-march=armv8-m.main")

set(CMAKE_C_FLAGS "${CPU_TYPE} ${ARCH} -mthumb -ffunction-sections -nostartfiles --specs=nosys.specs -fdata-sections -Os -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable")
set(CMAKE_CXX_FLAGS "${CPU_TYPE} ${ARCH} -mthumb -ffunction-sections -nostartfiles --specs=nosys.specs -fdata-sections -Os -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -fno-exceptions -fno-rtti")
set(CMAKE_ASM_FLAGS "${CPU_TYPE} ${ARCH} -mthumb -ffunction-sections -nostartfiles --specs=nosys.specs -fdata-sections -Os -Wall -Wextra")

set(CMAKE_EXE_LINKER_FLAGS "${CPU_TYPE} ${ARCH} -mthumb -Wl,--gc-sections -Wl,--print-memory-usage")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
