/*
 * BlinkHeavy.h
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#ifndef BLINKHEAVY_H_
#define BLINKHEAVY_H_

#include "pico/stdlib.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

#include "BlinkAgent.h"


class BlinkHeavy : public BlinkAgent{
public:
	/***
	 * Constructor
	 * @param gp = GPIO pad number
	 */
	BlinkHeavy(uint8_t gp);

	/***
	 * Destructor
	 */
	virtual ~BlinkHeavy();

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


#endif /* BLINKHEAVY_H_ */
