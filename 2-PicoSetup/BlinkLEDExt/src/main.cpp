/***
 * Demo program to flash an LED attached to GPIO PAD 0.
 * Uses FreeRTOS Task
 * Jon Durrant
 * 15-Aug-2022
 */


#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>


//Standard Task priority
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

//LED PAD to use
#define LED_PAD				0

//Blink Delay
#define DELAY				500



/***
 * Main task to blink external LED
 * @param params - unused
 */
void mainTask(void *params){

	printf("Main task started\n");

	const uint ledPad = LED_PAD;
	gpio_init(ledPad);

	gpio_set_dir(ledPad, GPIO_OUT);

	while (true) { // Loop forever
		gpio_put(ledPad, 1);
		vTaskDelay(DELAY);
		gpio_put(ledPad, 0);
		vTaskDelay(DELAY);
	}
}




/***
 * Launch the tasks and scheduler
 */
void vLaunch( void) {

	//Start blink task
    TaskHandle_t task;
    xTaskCreate(mainTask, "MainThread", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, &task);

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

/***
 * Main
 * @return
 */
int main( void )
{
	//Setup serial over USB and give a few seconds to settle before we start
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    //Start tasks and scheduler
    const char *rtos_name = "FreeRTOS";
    printf("Starting %s on core 0:\n", rtos_name);
    vLaunch();


    return 0;
}
