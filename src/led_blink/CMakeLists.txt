add_executable(led_blink
    main.c
    init.c
)

target_link_libraries(led_blink PRIVATE led)

target_include_directories(led_blink PRIVATE
    ${EXTERNAL_LIB_PATH}/src/rp2_common/cmsis/stub/CMSIS/Device/RP2350/Include/
    ${EXTERNAL_LIB_PATH}/src/rp2_common/cmsis/stub/CMSIS/Core/Include/
    ${EXTERNAL_LIB_PATH}/src/rp2350/hardware_regs/include/
)

target_link_options(led_blink PRIVATE
    "-T${CMAKE_CURRENT_SOURCE_DIR}/flash.ld"
)

add_custom_command(TARGET led_blink POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:led_blink> ${CMAKE_CURRENT_BINARY_DIR}/led_blink.bin
    COMMENT "Generating binary image"
)

add_custom_command(TARGET led_blink POST_BUILD
    COMMAND picotool uf2 convert ${CMAKE_CURRENT_BINARY_DIR}/led_blink.bin ${CMAKE_CURRENT_BINARY_DIR}/led_blink.uf2 --family rp2350-arm-s --abs-block
    COMMENT "Generating UF2"
)
