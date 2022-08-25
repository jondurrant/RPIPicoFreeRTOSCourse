/*
 * BlinkAgent.h
 *
 * Active agent to run as task and blink and LED on the given GPIO pad
 *
 *  Created on: 15 Aug 2022
 *      Author: jondurrant
 */

#ifndef BLINKAGENT_H_
#define BLINKAGENT_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"


class BlinkAgent {
public:
	/***
	 * Constructor
	 * @param gp - GPIO Pad number for LED
	 */
	BlinkAgent(uint8_t gp=0);

	/***
	 * Destructor
	 */
	virtual ~BlinkAgent();

	/***
	 * Start task
	 * @param priority - priority
	 * @return return true of ok
	 */
	virtual  bool start(UBaseType_t priority = tskIDLE_PRIORITY);

	/***
	 * Stop task
	 * @return
	 */
	virtual void stop();


	/***
	 * Get high water for stack
	 * @return close to zero means overflow risk
	 */
	virtual unsigned int getStakHighWater();

	/***
	 * Get the FreeRTOS task being used
	 * @return task handle
	 */
	virtual TaskHandle_t getTask();

protected:
	/***
	 * Static function used to start a task
	 * @param pvParameters - should point to the object of this class
	 */
	static void vTask( void * pvParameters );

	/***
	 * Run loop for the agent.
	 */
	virtual void run();


	//The task
	TaskHandle_t xHandle = NULL;



private:

	uint8_t xLedPad = 0;

};


#endif /* BLINKAGENT_H_ */
