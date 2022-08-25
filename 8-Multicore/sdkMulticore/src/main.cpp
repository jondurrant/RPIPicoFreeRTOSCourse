/***
 * Demo program to
 *
 * Jon Durrant
 * 15-Aug-2022
 */


#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/multicore.h"
#include "hardware/structs/sio.h"
#include <math.h>

#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )

//LED PAD to use
#define LED_PAD			0
#define LED5_PAD	   15

//Blink Delay
#define DELAY			500


/***
 * Function to run on Core1
 */
void core1Main(void){

	printf("Main Core 1 task started %ld\n", sio_hw->cpuid);

	const uint ledPad = LED5_PAD;
	gpio_init(ledPad);

	gpio_set_dir(ledPad, GPIO_OUT);

	while (true) { // Loop forever
		gpio_put(ledPad, 1);
		sleep_ms(DELAY);
		gpio_put(ledPad, 0);
		sleep_ms(DELAY);

		uint32_t r;
		if (multicore_fifo_pop_timeout_us(0, &r)){
			printf("Received %ld\n", r);
		}
	}
}

/***
 * Function to run on Core 0
 */
void core0Main(void){

	printf("Main Core 0 task started %ld\n", sio_hw->cpuid);

	const uint ledPad = LED_PAD;
	gpio_init(ledPad);

	gpio_set_dir(ledPad, GPIO_OUT);

	while (true) { // Loop forever
		gpio_put(ledPad, 1);
		sleep_ms(DELAY);
		gpio_put(ledPad, 0);
		sleep_ms(DELAY);

		uint32_t r = rand();
		if (multicore_fifo_push_timeout_us	(r, 0)){
			printf("Sent %ld\n", r);
		}
	}
}


/***
 * Main
 * @return
 */
int main( void )
{
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    multicore_launch_core1(core1Main);

    core0Main();



    return 0;
}
