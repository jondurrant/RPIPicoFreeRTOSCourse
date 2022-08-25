/*
 * IOAgent.cpp
 *
 * Serial IO Agent. To read from UART0 on GPIO 16 and 17
 *
 *  Created on: 22 Aug 2022
 *      Author: jondurrant
 */

#include "IOAgent.h"
#include <stdio.h>
#include "hardware/uart.h"


/***
 * Constructor
 * @param agent - DecoderAgent to pass input string to
 * @param gp - GPIO Pad to use as an LED, turn on when we are in
 * conductor mode
 */
IOAgent::IOAgent(DecoderAgent *agent, uint8_t gp) {
	pAgent = agent;
	xLedPad = gp;

}

/***
 * Destructor
 */
IOAgent::~IOAgent() {
	//NOP
}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE IOAgent::getMaxStackSize(){
	return 300;
}


/***
  * Main Run Task for agent
  */
 void IOAgent::run(){
	 uint32_t lastMsg, now;
	 char line[IO_AGENT_LINE_LEN];

	 init();

	 printf("IO Agent started\n");

	 lastMsg = to_ms_since_boot (get_absolute_time ());

	 while(true){
		 if (uart_is_readable_within_us(uart0, 10)){
			 char c = uart_getc	(uart0);
			 if ((c == '\n') || (c == '\r') || (c == 0)){
				 if (xLineIdx > 0){
					 pLine[xLineIdx] = 0;

					 printf("LINE READ:%s \n", pLine);
					 xLineIdx = 0;
					 lastMsg = to_ms_since_boot (get_absolute_time ());
					 if (pAgent != NULL){
						 pAgent->add(pLine);
					 }
					 setConductor(false);
				 }
			 } else {
				 //printf("Read %x %c\n", c, c);
				 pLine[xLineIdx++] = c;

				 if (xLineIdx > IO_AGENT_LINE_LEN){
					 printf("ERROR: line length exceed %d\n", IO_AGENT_LINE_LEN);
					 xLineIdx = 0;
				 }
			 }
	 	 } else {
			 vTaskDelay(10);
		 }

		 now = to_ms_since_boot (get_absolute_time ());
		 if ((now - lastMsg ) > IO_MSG_WAIT){
			 //Become conductor
			 uint8_t r = rand() & 0x0F;
			 sprintf(line, "{\"count\": %d}\r\n", r);
			 printf("I am conductor 0x%X\n", r);
			 write(line);
			 if (pAgent != NULL){
				 pAgent->add(line);
			 }

			 lastMsg = now;
			 setConductor(true);
		 }
	 }
}


/***
 * Initislise the UART0 and LED
 */
void IOAgent::init(){
	// Initialise UART 0
	uart_init(uart0, IO_AGENT_BAUD);
	uart_set_format	(uart0, 8, 1, UART_PARITY_NONE);
	uart_set_hw_flow(uart0, false, false);
	uart_set_fifo_enabled(uart0, true);
	gpio_set_function(IO_AGENT_TX_PAD, GPIO_FUNC_UART);
	gpio_set_function(IO_AGENT_RX_PAD, GPIO_FUNC_UART);

	// Init the LED
	gpio_init(xLedPad);
	gpio_set_dir(xLedPad, GPIO_OUT);
	gpio_put(xLedPad, 0);
}

/***
 * Write the string out through the UART
 * @param line - c string
 */
void IOAgent::write(char *line){
	uart_puts (uart0, line);
}


/***
 * Set if conductor or not. If conductor will turn on LED
 * @param isConductor - boolean true if conductor
 */
void IOAgent::setConductor(bool isConductor){
	gpio_put(xLedPad, isConductor);
}
