project(GD32E23x_standard_peripheral LANGUAGES C CXX ASM)

# Comment-out unused source files.
add_library(GD32E23x_standard_peripheral OBJECT
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_adc.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_cmp.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_crc.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_dbg.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_dma.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_exti.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_fmc.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_fwdgt.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_gpio.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_i2c.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_misc.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_pmu.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_rcu.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_rtc.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_spi.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_syscfg.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_timer.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_usart.c
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Source/gd32e23x_wwdgt.c
    )

target_include_directories(GD32E23x_standard_peripheral PUBLIC
    ${DRIVERS_DIR}/GD32E23x_standard_peripheral/Include
    )

# CMSIS header only library is linked.
target_link_libraries(GD32E23x_standard_peripheral PUBLIC CMSIS)
