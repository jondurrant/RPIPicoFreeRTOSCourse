/*
 * BlinkPairAgent.h
 *
 * Blink an LED this class owns and a shared one together
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#ifndef BLINKPAIRAGENT_H_
#define BLINKPAIRAGENT_H_

#include "BlinkAgent.h"
#include "SharedLed.h"

class BlinkPairAgent : public BlinkAgent{
public:
	/***
	 * Constructor
	 * @param gp - GPIO Pad number for LED
	 */
	BlinkPairAgent(uint8_t gp=0, SharedLed *shared=NULL);

	/***
	 * Destructor
	 */
	virtual ~BlinkPairAgent();


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

	SharedLed *pSharedLed = NULL;

};


#endif /* BLINKPAIRAGENT_H_ */
