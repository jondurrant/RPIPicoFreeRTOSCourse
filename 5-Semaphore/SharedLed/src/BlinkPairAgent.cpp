/*
 * BlinkPairAgent.cpp
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#include "BlinkPairAgent.h"
#include <stdio.h>

#define DELAY 500

BlinkPairAgent::BlinkPairAgent(uint8_t gp, SharedLed *shared): BlinkAgent(gp) {
	pSharedLed = shared;
}

BlinkPairAgent::~BlinkPairAgent() {
	// NOP
}

/***
* Main Run Task for agent
*/
void BlinkPairAgent::run(){

	printf("Blink Started\n");

	gpio_init(xLedPad);

	gpio_set_dir(xLedPad, GPIO_OUT);

	while (true) { // Loop forever
		gpio_put(xLedPad, 1);
		if (pSharedLed != NULL){
			while (pSharedLed->blink(DELAY) == false){
				//Keep checking
			}
		}
		gpio_put(xLedPad, 0);
		vTaskDelay(DELAY);
	}

}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE BlinkPairAgent::getMaxStackSize(){
	return 150;
}
