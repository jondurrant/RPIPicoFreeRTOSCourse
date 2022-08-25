/*
 * RainbowAgent.cpp
 *
 * A Rainbow display agent.
 * Walks through colours of the rainbow
 * Doing a random amount of work inbetween steps
 *
 *  Created on: 16 Aug 2022
 *      Author: jondurrant
 */

#include "RainbowAgent.h"
#include "hardware/pwm.h"
#include <math.h>
#include <stdio.h>

//Blink Delay
#define DELAY			1000

/****
 * Constructor
 * @param gpRed = GPIO pin for Red
 * @param gpGreen - GPIO pin for Green
 * @param gpBlue - GPIO pin for Blue
 */
RainbowAgent::RainbowAgent(uint8_t gpRed, uint8_t gpGreen, uint8_t gpBlue) {
	xRGBPads[0] = gpRed;
	xRGBPads[1] = gpGreen;
	xRGBPads[2] = gpBlue;
}

/***
 * Destructor
 */
RainbowAgent::~RainbowAgent() {
	// Nop
}

/***
 * Initialise the GPIO Pins
 */
void RainbowAgent::init(){
	uint8_t gp;

	for (uint8_t i = 0; i < 3; i++){
		gp = xRGBPads[i];

		gpio_init(gp);
		gpio_set_function(gp, GPIO_FUNC_PWM);
		uint slice_num = pwm_gpio_to_slice_num(gp);
		pwm_set_enabled(slice_num, true);
		pwm_set_gpio_level(gp, 0);
	}
}

/***
 * Set the RGB LED to a colour
 * @param rgb - array of three bytes for Red, Green and Blue components
 */
void RainbowAgent::setRGB(const uint8_t* rgb){
	for (uint8_t i=0; i < 3; i++){
		int lvl = rgb[i]* rgb[i];
		pwm_set_gpio_level(xRGBPads[i], lvl);
	}
}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE RainbowAgent::getMaxStackSize(){
	return 200;
}

/***
 * Run loop for the agent.
 */
void RainbowAgent::run(){
	int n;
	double d;


	init();
	xStep = 0;


	for(;;){
		setRGB(pRainbow[xStep]);
		printf("%s: %d\n", pName, xStep);
		n = rand();
		for (int i=1; i < n; i++){
			d = cbrt(i);
			d= cbrt(n*n);

		}

		vTaskDelay(n%300);

		vTaskDelay(DELAY);
		xStep++;
		if (xStep > 7){
			xStep = 0;

			if (pPeer != NULL){
				xTaskNotifyGive(pPeer->getTask());
				uint32_t r = ulTaskNotifyTake(pdTRUE, DELAY);
				printf("%s %d %d", pName, xStep, r);
			}
		}
	}

}

/***
 * Set peer. Will notify each time return to begin of sequence
 * @param peer
 */
void RainbowAgent::setPeer(RainbowAgent *peer){
	pPeer = peer;
}
