/*
 * CounterAgent.cpp
 *
 *  Created on: 22 Aug 2022
 *      Author: jondurrant
 */

#include "CounterAgent.h"
#include "stdio.h"

//Local enumerator of the actions to be queued
enum CounterAction {CounterOff, CounterOn, CounterBlink};

//Queue cmd structure
struct CounterCmd {
	CounterAction 	action;
	uint8_t 		count;
};

//Type def for the queue command
typedef struct CounterCmd CounterCmdT;

/***
 * Contructor
 * @param gp1 GPIO PAD for 1st LED - units
 * @param gp2 GPIO PAD for 1st LED - 2
 * @param gp3 GPIO PAD for 1st LED - 4
 * @param gp4 GPIO PAD for 1st LED - 8
 */
CounterAgent::CounterAgent(uint8_t gp1, uint8_t gp2, uint8_t gp3, uint8_t gp4) {

	pLedPads[0] = gp1;
	pLedPads[1] = gp2;
	pLedPads[2] = gp3;
	pLedPads[3] = gp4;

	xCmdQ = xQueueCreate( COUNT_QUEUE_LEN, sizeof(CounterCmd));
	if (xCmdQ == NULL){
		printf("ERROR: Unable to create Queue\n");
	}
}


/***
 * Destructor
 */
CounterAgent::~CounterAgent() {
	if (xCmdQ != NULL){
		vQueueDelete(xCmdQ);
	}
}

/***
 * Initialise the LEDs
 */
void CounterAgent::init(){
	for (int i = 0 ; i < COUNT_LEDS; i++){
		gpio_init(pLedPads[i]);
		gpio_set_dir(pLedPads[i], GPIO_OUT);
		gpio_put(pLedPads[i], 0);
	}
}


/***
  * Main Run Task for agent
  */
 void CounterAgent::run(){
	BaseType_t res;
	printf("Count Started\n");
	init();

	CounterAction action = CounterOff;
	uint8_t count = 0;
	bool blinkOn = false;
	CounterCmdT cmd;
	bool change;

	if (xCmdQ == NULL){
		return;
	}

	while (true) { // Loop forever
		printf("%s on Core %d\n",pName, getCore());
		res = xQueueReceive(xCmdQ, (void *)&cmd, COUNT_BLINK_DELAY);
		if (res == pdTRUE){
			action = cmd.action;
			count =  cmd.count;
			change = true;
		} else {
			change = false;
		}

		switch(action){
		case CounterOff:
			if (change){
				setLeds(0);
			}
			break;
		case CounterOn:
			if (change){
				setLeds(count);
			}
			break;
		case CounterBlink:
			blinkOn = ! blinkOn;
			if (blinkOn){
				setLeds(count);
			} else {
				setLeds(0);
			}
		}
	}

}

/***
 * Get the static depth required in words
 * @return - words
 */
configSTACK_DEPTH_TYPE CounterAgent::getMaxStackSize(){
	return 150;
}


/***
 * Set the LEDs to the mask in count
 * @param count
 */
void CounterAgent::setLeds(uint8_t count){
	for (int i = 0; i < COUNT_LEDS; i ++){
		uint8_t m = 1 << i;
		if ( (count & m) > 0){
			gpio_put(pLedPads[i], 1);
		} else {
			gpio_put(pLedPads[i], 0);
		}
	}
}

/***
 * Turn LEDs on and display count
 * @param count - between 0 and 0xF
 */
void CounterAgent::on(uint8_t count){
	BaseType_t res;

	CounterCmdT cmd;
	cmd.action = CounterOn;
	cmd.count = count;

	if (xCmdQ != NULL){
		res = xQueueSendToBack(xCmdQ, (void *)&cmd, 0);
		if (res != pdTRUE){
			printf("WARNING: Queue is full\n");
		}
	}
}

/***
 * Turn LEDs off
 */
void CounterAgent::off(){
	BaseType_t res;

	CounterCmdT cmd;
	cmd.action = CounterOff;
	cmd.count = 0;

	if (xCmdQ != NULL){
		res = xQueueSendToBack(xCmdQ, (void *)&cmd, 0);
		if (res != pdTRUE){
			printf("WARNING: Queue is full\n");
		}
	}

}

/***
 * Blink LEDs with displayed count
 * @param count - between 0 and 0x0F
 */
void CounterAgent::blink(uint8_t count){
	BaseType_t res;

	CounterCmdT cmd;
	cmd.action = CounterBlink;
	cmd.count = count;

	if (xCmdQ != NULL){
		res = xQueueSendToBack(xCmdQ, (void *)&cmd, 0);
		if (res != pdTRUE){
			printf("WARNING: Queue is full\n");
		}
	}
}


