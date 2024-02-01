include(files.cmake)
add_executable(${NAME}
        main.cpp
        ${SRC_FILES}
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${NAME} 
	pico_stdlib
	pi_spigot
	FreeRTOS-Kernel-Heap4 # FreeRTOS kernel and dynamic heap
	freertos_config #FREERTOS_PORT
	)

# enable usb output, disable uart output
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 1)
target_compile_definitions(${NAME} PRIVATE
    PICO_DEFAULT_UART_RX_PIN=16
    PICO_DEFAULT_UART_TX_PIN=17
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})