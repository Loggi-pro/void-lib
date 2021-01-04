add_avr_executable(void_mcu_example ${MCU} main.cpp)
configure_void_library(MCU ${MCU} F_CPU 16000000UL)
target_link_libraries(void_mcu_example.elf
        PUBLIC void-${MCU}
        PRIVATE project_options project_warnings)