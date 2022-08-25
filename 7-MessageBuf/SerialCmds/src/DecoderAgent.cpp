/*
 * DecoderAgent.cpp
 *
 * Decode JSON Messages and pass on count instruction to CounterAgent
 *
 *  Created on: 22 Aug 2022
 *      Author: jondurrant
 */

#include "DecoderAgent.h"

#include <stdio.h>
#include <string.h>


/***
 * Constructor
 * @param agent - CounterAgent to control with decoded json messages
 */
DecoderAgent::DecoderAgent(CounterAgent *agent) {
	pAgent = agent;

	xBuffer = xMessageBufferCreate(DECODE_BUFFER_LEN);
	if (xBuffer == NULL){
		printf("ERROR buffer could not be allocated\n");
	}
}

/***
 * Destructor
 */
DecoderAgent::~DecoderAgent() {
	if (xBuffer != NULL){
		vMessageBufferDelete(xBuffer);
	}
}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE DecoderAgent::getMaxStackSize(){
	return 300;
}


/***
  * Main Run Task for agent
  */
 void DecoderAgent::run(){
	 if (xBuffer == NULL){
		 return;
	 }


	 size_t readLen;
	 char line[DECODE_LINE_LEN];
	 while(true){
		 readLen = xMessageBufferReceive(
				 xBuffer,
		         line,
		         DECODE_LINE_LEN,
				 DECODE_WAIT_TIME
		    );
		 if (readLen > 0){
			 parseLine(line);
		 }

	 }
 }

/***
 * Parse the json in the given c string
 * @param line - line of string
 */
 void DecoderAgent::parseLine(char *line){
	 json_t const* json = json_create( line, pJsonPool, DECODE_JSON_POOL);
	 if ( !json ) {
		 puts("Error json create.");
		 return ;
	 }

	 json_t const* count = json_getProperty( json, "count" );
	 if ( !count || JSON_INTEGER != json_getType( count ) ) {
		 puts("Error, the age property is not found.");
		 return ;
	 }
	 int  c = (int)json_getInteger( count );
	 printf("JSON Count is 0x%X\n", c);

	 if (pAgent != NULL){
		 pAgent->on(c);
	 }
}


/***
 * Add text to the decoding buffer
 * @param txt, C string is copied to the buffer
 */
 void DecoderAgent::add(char *txt){
	 if (xBuffer != NULL){
		 size_t dataOut = strlen(txt) + 1;
		 size_t  res = xMessageBufferSend(
			 xBuffer,
			 (const void *)txt,
			 dataOut,
			 0);

		 if (res != dataOut){
			 printf("ERROR: failed to write whole message to buffer\n");
		 }

	 }
 }
