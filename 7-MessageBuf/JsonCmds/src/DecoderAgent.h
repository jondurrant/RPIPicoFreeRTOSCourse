/*
 * DecoderAgent.h
 *
 * Decode JSON Messages and pass on count instruction to CounterAgent
 *
 *  Created on: 22 Aug 2022
 *      Author: jondurrant
 */

#ifndef DECODERAGENT_H_
#define DECODERAGENT_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include "tiny-json.h"

#include "CounterAgent.h"
#include "Agent.h"


#define DECODE_BUFFER_LEN 1024
#define DECODE_LINE_LEN 80
#define DECODE_WAIT_TIME 3000
#define DECODE_JSON_POOL 12

class DecoderAgent : public Agent {
public:
	/***
	 * Constructor
	 * @param agent - CounterAgent to control with decoded json messages
	 */
	DecoderAgent(CounterAgent *agent);

	/***
	 * Destructor
	 */
	virtual ~DecoderAgent();

	/***
	 * Add text to the decoding buffer
	 * @param txt, C string is copied to the buffer
	 */
	virtual void add(char *txt);

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
	 * Parse the json in the given c string
	 * @param line - line of string
	 */
	void parseLine(char *line);

	// Buffer handle
	MessageBufferHandle_t xBuffer = NULL;

	// pointer to the Counter Agent to use
	CounterAgent *pAgent = NULL;

	// Json decoding buffer
	json_t pJsonPool[ DECODE_JSON_POOL ];

};


#endif /* 7_MESSAGEBUF_JSONCMDS_SRC_DECODERAGENT_H_ */
