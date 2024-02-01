/**
 * Calculate the value of PI using 4 Worker threads across 2 cores
 * Jon Durrant - 2024
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <FreeRTOS.h>
#include "Counter.h"
#include "Worker.h"


#define DELAY_SHORT 200 // in microseconds
#define DELAY_LONG  1000 // in microseconds

#define TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )



int64_t alarmCB (alarm_id_t id, void *user_data){
	Counter::getInstance()->report();
	return 0;
}



void main_task(void* params){
  Worker worker1(0);
  Worker worker2(1);
  Worker worker3(2);
  Worker worker4(3);

  printf("Main task started\n");

  alarm_id_t alarm = add_alarm_in_ms(
  			60 * 1000,
  			alarmCB, NULL, false);

	Counter::getInstance()->start();
	worker1.start("Worker 1", TASK_PRIORITY );
	worker2.start("Worker 2", TASK_PRIORITY);
	worker3.start("Worker 3", TASK_PRIORITY );
	worker4.start("Worker 4", TASK_PRIORITY);

  for (;;){
	  vTaskDelay(3000);
  }
}




int main() {


	//Initialise IO as we are using printf for debug
	stdio_init_all();
	sleep_ms(2000);
	printf("Start\n");

	TaskHandle_t task;

   xTaskCreate(main_task, "MainThread", 2048, NULL, TASK_PRIORITY, &task);

  /* Start the tasks and timer running. */
	vTaskStartScheduler();

	for (;;){

	}
}
