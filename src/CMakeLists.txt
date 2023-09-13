cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(macropad C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(macropad)

pico_generate_pio_header(macropad 
    ${CMAKE_CURRENT_LIST_DIR}/Lighting/neopixel.pio)

target_sources(macropad PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/macropad.c
    ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
    ${CMAKE_CURRENT_LIST_DIR}/Keys/Keys.c
    ${CMAKE_CURRENT_LIST_DIR}/Encoder/Encoder.c
    ${CMAKE_CURRENT_LIST_DIR}/Lighting/Neopixel.c
    ${CMAKE_CURRENT_LIST_DIR}/Lighting/LampArray.c
    )

target_include_directories(macropad PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(macropad PUBLIC
    pico_stdlib
    pico_multicore
    hardware_pio
    tinyusb_device
    tinyusb_board
    )

pico_add_extra_outputs(macropad)
pico_enable_stdio_usb(macropad 1)
