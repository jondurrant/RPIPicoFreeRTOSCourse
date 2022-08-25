/*
 * SharedLed.cpp
 * Shared LED that can only be blinked by one client at a time
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#include "SharedLed.h"
#include <stdio.h>

/***
 * Constructor
 * @param gp - GPIO Pad number for LED
 */
SharedLed::SharedLed(uint8_t gp) {
	xLedPad = gp;
	xSem = xSemaphoreCreateBinary( );
	if (xSem == NULL){
		printf("ERROR could not create semaphore\n");
	} else {
		xSemaphoreGive(xSem);
	}

	gpio_init(xLedPad);

	gpio_set_dir(xLedPad, GPIO_OUT);
}

/***
 * Destructor
 */
SharedLed::~SharedLed() {
	if (xSem != NULL){
		vSemaphoreDelete(xSem);
	}
}

/***
 * Blink LED once for desired time
 * @param time
 * @return - true if ok
 */
bool SharedLed::blink(uint time){

	if (xSemaphoreTake(xSem, 0) == pdTRUE){
		gpio_put(xLedPad, 1);
		vTaskDelay(time);
		gpio_put(xLedPad, 0);
		vTaskDelay(time);

		xSemaphoreGive(xSem);

		return true;
	}

	return false;
}

