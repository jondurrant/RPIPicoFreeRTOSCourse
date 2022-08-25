/*
 * CounterAgent.h
 *
 * Show binary view of count on LEDs
 *
 *  Created on: 22 Aug 2022
 *      Author: jondurrant
 */

#ifndef COUNTERAGENT_H_
#define COUNTERAGENT_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Agent.h"

#define COUNT_LEDS 			4
#define COUNT_QUEUE_LEN 	10
#define COUNT_BLINK_DELAY 	500

class CounterAgent : public Agent {
public:

	/***
	 * Contructor
	 * @param gp1 GPIO PAD for 1st LED - units
	 * @param gp2 GPIO PAD for 1st LED - 2
	 * @param gp3 GPIO PAD for 1st LED - 4
	 * @param gp4 GPIO PAD for 1st LED - 8
	 */
	CounterAgent(uint8_t gp1=0, uint8_t gp2=0, uint8_t gp3=0, uint8_t gp4=0);

	/***
	 * Destructor
	 */
	virtual ~CounterAgent();

	/***
	 * Turn LEDs on and display count
	 * @param count - between 0 and 0xF
	 */
	virtual void on(uint8_t count);

	/***
	 * Turn LEDs off
	 */
	virtual void off();

	/***
	 * Blink LEDs with displayed count
	 * @param count - between 0 and 0x0F
	 */
	virtual void blink(uint8_t count);

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
	 * Initialise the LEDs
	 */
	virtual void init();


	/***
	 * Set the LEDs to the mask in count
	 * @param count
	 */
	virtual void setLeds(uint8_t count);

	//GPIO PAD for LED
	uint8_t pLedPads[COUNT_LEDS];

	//Queue of commands
	QueueHandle_t xCmdQ;

};

#endif /* COUNTERAGENT_H_ */
