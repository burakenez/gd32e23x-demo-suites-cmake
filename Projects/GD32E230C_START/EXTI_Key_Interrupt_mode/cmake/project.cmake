function(project_add_target_properties TARGET_NAME)

target_compile_definitions(${TARGET_NAME} PRIVATE
    "$<$<CONFIG:Debug>:DEBUG>"
    "$<$<NOT:$<CONFIG:Debug>>:RELEASE>"
    GD32E23x
    GD32E230
)

target_compile_options(${TARGET_NAME} PRIVATE
    "$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:ASM>>:-g3>"
    "$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g3>"
    "$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g3>"
    "$<$<AND:$<NOT:$<CONFIG:Debug>>,$<COMPILE_LANGUAGE:ASM>>:-g0>"
    "$<$<AND:$<NOT:$<CONFIG:Debug>>,$<COMPILE_LANGUAGE:C>>:-g0>"
    "$<$<AND:$<NOT:$<CONFIG:Debug>>,$<COMPILE_LANGUAGE:CXX>>:-g0>"

    "$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-O0>"
    "$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-O0>"
    "$<$<AND:$<NOT:$<CONFIG:Debug>>,$<COMPILE_LANGUAGE:C>>:-Os>"
    "$<$<AND:$<NOT:$<CONFIG:Debug>>,$<COMPILE_LANGUAGE:CXX>>:-Os>"

    -mcpu=cortex-m23
    )

target_link_options(${TARGET_NAME} PRIVATE 
    -mcpu=cortex-m23
    -mthumb
    -u _printf_float
    -static
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--gc-sections
    -Wl,--start-group -lc -lm -Wl,--end-group
    )

# target_link_libraries(${TARGET_NAME} PRIVATE 
#     m # to us C math library. -lm should be end of the linker script. In order to achieve that, target_link_libraries is used.
#     )

# target_link_libraries(${TARGET_NAME} PRIVATE
#     :libarm_cortexM4lf_math.a
#     )

# target_link_directories(${TARGET_NAME} PRIVATE
#     ${DRIVERS_DIR}/CMSIS/DSP/Lib/GCC
#     )

endfunction()
