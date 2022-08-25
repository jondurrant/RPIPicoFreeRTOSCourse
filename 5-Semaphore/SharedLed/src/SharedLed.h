/*
 * SharedLed.h
 *
 * Shared LED that can only be blinked by one client at a time
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#ifndef SHAREDLED_H_
#define SHAREDLED_H_

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


class SharedLed {
public:
	/***
	 * Constructor
	 * @param gp - GPIO Pad number for LED
	 */
	SharedLed(uint8_t gp);

	/***
	 * Destructor
	 */
	virtual ~SharedLed();


	/***
	 * Blink LED once over time
	 * @param time
	 * return true on sucessful
	 */
	bool blink(uint time);

private:



	//GPIO PAD for LED
	uint8_t xLedPad = 0;

	SemaphoreHandle_t xSem = NULL;

};


#endif /* SHAREDLED_H_ */
