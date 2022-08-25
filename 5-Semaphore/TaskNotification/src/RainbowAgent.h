/*
 * RainbowAgent.h
 *
 * A Rainbow display agent.
 * Walks through colours of the rainbow
 * Doing a random amount of work inbetween steps
 *
 *  Created on: 16 Aug 2022
 *      Author: jondurrant
 */

#ifndef SRC_RAINBOWAGENT_H_
#define SRC_RAINBOWAGENT_H_

#include "pico/stdlib.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

#include "Agent.h"

class RainbowAgent : public Agent {
public:
	/****
	 * Constructor
	 * @param gpRed = GPIO pin for Red
	 * @param gpGreen - GPIO pin for Green
	 * @param gpBlue - GPIO pin for Blue
	 */
	RainbowAgent(uint8_t gpRed, uint8_t gpGreen, uint8_t gpBlue);

	/***
	 * Destructor
	 */
	virtual ~RainbowAgent();

	/***
	 * Set peer. Will notify each time return to begin of sequence
	 * @param peer
	 */
	void setPeer(RainbowAgent *peer);
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

private:

	/***
	 * Initialise the GPIO Pins
	 */
	void init();

	/***
	 * Set the RGB LED to a colour
	 * @param rgb - array of three bytes for Red, Green and Blue components
	 */
	void setRGB(const uint8_t* rgb);

	//GPIO PAD for LED
	uint8_t xRGBPads[3];

	uint8_t xStep = 0;

	//Peer for sync notification
	RainbowAgent *pPeer = NULL;

	//Rainbow sequence as Red, Green, Blue tuples
	const uint8_t pRainbow[7][3]= {
		{0x94, 0x00, 0xD3},
		{0x4B, 0x00, 0x82},
		{0x00, 0x00, 0xFF},
		{0x00, 0xFF, 0x00},
		{0xFF, 0xFF, 0x00},
		{0xFF, 0x7F, 0x00},
		{0xFF, 0x00, 0x00}
	};

};


#endif /* SRC_RAINBOWAGENT_H_ */
