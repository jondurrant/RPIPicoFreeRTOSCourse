/*
 * BlinkWorker.h
 *
 * Blink worker, to blink LED on a GPIO pad but do a random amount of work
 * between blinks
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#ifndef BLINKWORKER_H_
#define BLINKWORKER_H_

#include "pico/stdlib.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

#include "BlinkAgent.h"


class BlinkWorker: public BlinkAgent  {
public:
	/***
	 * Constructor
	 * @param gp = GPIO pad number
	 */
	BlinkWorker(uint8_t gp);

	/***
	 * Destructor
	 */
	virtual ~BlinkWorker();

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
};


#endif /* BLINKWORKER_H_ */
