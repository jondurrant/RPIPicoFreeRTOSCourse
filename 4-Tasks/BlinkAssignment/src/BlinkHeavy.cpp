/*
 * BlinkHeavy.cpp
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#include "BlinkHeavy.h"
#include "math.h"
#include <cstdio>

//Blink Delay
#define DELAY			500

BlinkHeavy::BlinkHeavy(uint8_t gp):BlinkAgent(gp) {
	//NOP
}

BlinkHeavy::~BlinkHeavy() {
	// NOP
}

/***
* Main Run Task for agent
*/
void BlinkHeavy::run(){
	int n;
	double d;

	printf("Blink Started\n");

	gpio_init(xLedPad);

	gpio_set_dir(xLedPad, GPIO_OUT);

	while (true) { // Loop forever
		for (int j = 0; j < 3; j++){
			gpio_put(xLedPad, 1);

			n = rand() % 10000;
			for (int i=0; i < n; i++ ){
				d = asin(sin(sqrt((double)n)));
				d = acos(cos(d));
			}

			gpio_put(xLedPad, 0);

			n = rand() % 10000;
			for (int i=0; i < n; i++ ){
				d = asin(sin(sqrt((double)n)));
				d = acos(cos(d));
			}
		}
		vTaskDelay(DELAY);
	}

}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE BlinkHeavy::getMaxStackSize(){
	return 150;
}
