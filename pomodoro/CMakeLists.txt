# Minimum CMake version required by the Pico SDK
cmake_minimum_required(VERSION 3.13...3.27)

# Using pico2_w so the board has WiFi/BT support built in.
# Kept this as pico2_w instead of plain pico2 so I can expand to
# WiFi features later without having to redo the whole build setup.
set(PICO_BOARD pico2_w)

# Pull in the Pico SDK (path must be set in environment or toolchain file)
include(pico_sdk_import.cmake)

# Initialize the SDK after project() so all board/compiler settings are in place
project(pomodoro)
pico_sdk_init()

# Source files for the project
add_executable(pomodoro
    pomodoro.c
)

# pico_stdlib -- core GPIO, sleep, stdio functions
# pico_cyw43_arch_lwip_poll -- needed for the onboard WiFi chip on the pico2_w.
# Not actively used in this version but linked in so the WiFi stack is ready
# when I come back to add network features in a future project.
target_link_libraries(pomodoro pico_stdlib pico_cyw43_arch_lwip_poll)
target_include_directories(pomodoro PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Route stdio over USB so I can read printf output via serial monitor
pico_enable_stdio_usb(pomodoro 1)
pico_enable_stdio_uart(pomodoro 0)

# Generate .uf2, .bin, .map etc. alongside the ELF for easy flashing
pico_add_extra_outputs(pomodoro)
