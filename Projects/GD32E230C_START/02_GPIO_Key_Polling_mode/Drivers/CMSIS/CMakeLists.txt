project(CMSIS LANGUAGES C CXX ASM)

add_library(CMSIS INTERFACE)

target_include_directories(CMSIS INTERFACE
    ${DRIVERS_DIR}/CMSIS/
    ${DRIVERS_DIR}/CMSIS/GD/GD32E23x/Include

    # Add "gd32e23x_libopt.h" path.
    ${CMAKE_SOURCE_DIR}/Application/Core/Inc
    )
