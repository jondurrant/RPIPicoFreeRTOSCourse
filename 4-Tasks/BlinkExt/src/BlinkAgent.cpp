/*
 * BlinkAgent.cpp
 *
 *  Created on: 15 Aug 2022
 *      Author: jondurrant
 */

#include "BlinkAgent.h"

#include "stdio.h"

//Blink Delay
#define DELAY			500

/***
 * Constructor
 * @param gp - GPIO Pad number for LED
 */
BlinkAgent::BlinkAgent(uint8_t gp) {
	xLedPad = gp;

}

/***
 * Destructor
 */
BlinkAgent::~BlinkAgent() {
	stop();
}

/***
 * Stop task
 */
void BlinkAgent::stop(){
	if (xHandle != NULL){
		vTaskDelete(  xHandle );
		xHandle = NULL;
	}
}


/***
* Get high water for stack
* @return close to zero means overflow risk
*/
unsigned int BlinkAgent::getStakHighWater(){
	if (xHandle != NULL)
		return uxTaskGetStackHighWaterMark(xHandle);
	else
		return 0;
}


/***
* Get the FreeRTOS task being used
* @return
*/
TaskHandle_t BlinkAgent::getTask(){
	return xHandle;
}


/***
 * Start the task
 * @param priority - Priority to apply to process
 * @return true if ok
 */
bool BlinkAgent::start(UBaseType_t priority){
	BaseType_t res;
	res = xTaskCreate(
			BlinkAgent::vTask,       /* Function that implements the task. */
		"Blink",   /* Text name for the task. */
		150,             /* Stack size in words, not bytes. */
		( void * ) this,    /* Parameter passed into the task. */
		priority,/* Priority at which the task is created. */
		&xHandle
	);
	return (res == pdPASS);
}



/***
 * Internal function used by FreeRTOS to run the task
 * @param pvParameters
 */
 void BlinkAgent::vTask( void * pvParameters ){
	 BlinkAgent *task = (BlinkAgent *) pvParameters;
	 if (task != NULL){
		 task->run();
	 }
 }

 /***
  * Main Run Task for agent
  */
 void BlinkAgent::run(){

	printf("Blink Started\n");

	gpio_init(xLedPad);

	gpio_set_dir(xLedPad, GPIO_OUT);

	while (true) { // Loop forever
		gpio_put(xLedPad, 1);
		vTaskDelay(DELAY);
		gpio_put(xLedPad, 0);
		vTaskDelay(DELAY);
	}

 }
