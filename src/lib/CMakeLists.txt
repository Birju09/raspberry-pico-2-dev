add_library(led STATIC led.c)

target_include_directories(led PRIVATE
    ${EXTERNAL_LIB_PATH}/src/rp2_common/cmsis/stub/CMSIS/Device/RP2350/Include/
    ${EXTERNAL_LIB_PATH}/src/rp2_common/cmsis/stub/CMSIS/Core/Include/
    ${EXTERNAL_LIB_PATH}/src/rp2350/hardware_regs/include/
)

# For targets depending on this library
target_include_directories(led PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
