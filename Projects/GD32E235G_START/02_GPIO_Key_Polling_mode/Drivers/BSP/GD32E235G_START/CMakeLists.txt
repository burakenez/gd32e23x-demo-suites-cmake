project(GD32E235G_START LANGUAGES C CXX ASM)

add_library(GD32E235G_START OBJECT 
    ${DRIVERS_DIR}/BSP/GD32E235G_START/gd32e235g_start.c
    )

target_include_directories(GD32E235G_START PUBLIC
    ${DRIVERS_DIR}/BSP/GD32E235G_START
    )

target_link_libraries(GD32E235G_START PUBLIC GD32E23x_standard_peripheral)
