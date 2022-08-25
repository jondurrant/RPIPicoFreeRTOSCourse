/*
 * IOAgent.h
 *
 * Serial IO Agent. To read from UART0 on GPIO 16 and 17
 *
 *  Created on: 22 Aug 2022
 *      Author: jondurrant
 */

#ifndef IOAGENT_H_
#define IOAGENT_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

#include "Agent.h"
#include "DecoderAgent.h"

#define IO_AGENT_BAUD   9600

#define IO_AGENT_RX_PAD 16
#define IO_AGENT_TX_PAD 17

#define IO_AGENT_LINE_LEN 80
#define IO_MSG_WAIT 3000


class IOAgent : public Agent{
public:
	/***
	 * Constructor
	 * @param agent - DecoderAgent to pass input string to
	 * @param gp - GPIO Pad to use as an LED, turn on when we are in
	 * conductor mode
	 */
	IOAgent(DecoderAgent *agent, uint8_t gp);

	/***
	 * Destructor
	 */
	virtual ~IOAgent();

	/***
	 * Write the string out through the UART
	 * @param line - c string
	 */
	void write(char *line);

protected:

	/***
	 * Run loop for the agent.
	 */
	virtual void run();


	/***
	 * Get the static depth required in words
	 * @return - words
	 */
	virtual configSTACK_DEPTH_TYPE getMaxStackSize();

	/***
	 * Initislise the UART0 and LED
	 */
	void init();

	/***
	 * Set if conductor or not. If conductor will turn on LED
	 * @param isConductor - boolean true if conductor
	 */
	void setConductor(bool isConductor);

	// Decoder Agent to pass messages to
	DecoderAgent *pAgent = NULL;

	// Line buffer for reading for the UART
	char pLine[IO_AGENT_LINE_LEN];

	// Index possition of where we are up to in the pLine buffer
	int xLineIdx = 0;

	// GPIO Pad number for the LED
	uint8_t xLedPad = 0;

};


#endif /* 7_MESSAGEBUF_JSONCMDS_SRC_IOAGENT_H_ */
