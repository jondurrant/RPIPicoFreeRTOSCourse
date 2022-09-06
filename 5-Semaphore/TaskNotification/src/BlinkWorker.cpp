/*
 * BlinkWorker.cpp
 *
 * Blink worker, to blink LED on a GPIO pad but do a random amount of work
 * between blinks
 *
 *  Created on: 17 Aug 2022
 *      Author: jondurrant
 */

#include "BlinkWorker.h"
#include "math.h"
#include <cstdio>

//Blink Delay
#define DELAY			500

/***
 * Constructor
 * @param gp = GPIO pad number
 */
BlinkWorker::BlinkWorker(uint8_t gp):BlinkAgent(gp) {
	//NOP

}

/***
 * Destructor
 */
BlinkWorker::~BlinkWorker() {
	// NOP
}

/***
* Main Run Task for agent
*/
void BlinkWorker::run(){

	printf("Blink Started\n");

	gpio_init(xLedPad);

	gpio_set_dir(xLedPad, GPIO_OUT);

	while (true) { // Loop forever
		gpio_put(xLedPad, 1);
		vTaskDelay(DELAY);
		gpio_put(xLedPad, 0);

		int n = rand() % 5000;
		for (int i=0; i < n; i++ ){
			double d = asin(sin(sqrt((double)n)));
			d = acos(cos(d));
		}
		vTaskDelay(DELAY);
		if (pPeer != NULL){
			xTaskNotifyGive(pPeer->getTask());
		}
		uint32_t r = ulTaskNotifyTake(pdTRUE, DELAY);
	}

}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE BlinkWorker::getMaxStackSize(){
	return 150;
}


/***
 * Set Peer Worker
 * @param peer - peer BlinkWorker that we will sync blink with
 */
void BlinkWorker::setPeer(BlinkWorker *peer){
	pPeer = peer;
}

