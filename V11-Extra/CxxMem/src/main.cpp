/***
 * Demo program to show Heap Usage in C++
 * Uses FreeRTOS Task
 * Jon Durrant
 * 1-Jan-2024
 */


#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#include "Dumb.h"
#include "DumbSDKHeap.h"


//Standard Task priority
#define TASK_PRIORITY		( tskIDLE_PRIORITY + 1UL )


void runTimeStats(   ){
	TaskStatus_t *pxTaskStatusArray;
	volatile UBaseType_t uxArraySize, x;
	unsigned long ulTotalRunTime;


   // Get number of takss
   uxArraySize = uxTaskGetNumberOfTasks();
   printf("Number of tasks %d\n", uxArraySize);

   //Allocate a TaskStatus_t structure for each task.
   pxTaskStatusArray = (TaskStatus_t *)pvPortMalloc( uxArraySize * sizeof( TaskStatus_t ) );

   if( pxTaskStatusArray != NULL ){
      // Generate raw status information about each task.
      uxArraySize = uxTaskGetSystemState( pxTaskStatusArray,
                                 uxArraySize,
                                 &ulTotalRunTime );

	 // Print stats
	 for( x = 0; x < uxArraySize; x++ ){
		 printf("Task: %d \t cPri:%d \t bPri:%d \t hw:%d \t%s\n",
				pxTaskStatusArray[ x ].xTaskNumber ,
				pxTaskStatusArray[ x ].uxCurrentPriority ,
				pxTaskStatusArray[ x ].uxBasePriority ,
				pxTaskStatusArray[ x ].usStackHighWaterMark ,
				pxTaskStatusArray[ x ].pcTaskName
				);
	 }


      // Free array
      vPortFree( pxTaskStatusArray );
   } else {
	   printf("Failed to allocate space for stats\n");
   }

   //Get heap allocation information
   HeapStats_t heapStats;
   vPortGetHeapStats(&heapStats);
   printf("HEAP avl: %d, blocks %d, alloc: %d, free: %d\n",
		   heapStats.xAvailableHeapSpaceInBytes,
		   heapStats.xNumberOfFreeBlocks,
		   heapStats.xNumberOfSuccessfulAllocations,
		   heapStats.xNumberOfSuccessfulFrees
		   );
}


void heapStats(){
	 //Get heap allocation information
	   HeapStats_t heapStats;
	   vPortGetHeapStats(&heapStats);
	   printf("HEAP avl: %d, blocks %d, alloc: %d, free: %d\n",
			   heapStats.xAvailableHeapSpaceInBytes,
			   heapStats.xNumberOfFreeBlocks,
			   heapStats.xNumberOfSuccessfulAllocations,
			   heapStats.xNumberOfSuccessfulFrees
			   );
}


/***
 * Main task to blink external LED
 * @param params - unused
 */
void mainTask(void *params){
	printf("Main task started\n");
	Dumb * pDumbs[100];

	heapStats();

	printf("NEW FreeRTOS Heap:\n");
	for (int i=0; i < 100; i++){
		pDumbs[i] = new Dumb;
	}
	heapStats();

	vTaskDelay(1000);
	printf("DELETE FreeRTOS Heap:\n");
	for (int i=0; i < 100; i++){
		delete pDumbs[i];
		pDumbs[i] = NULL;
	}
	heapStats();

	printf("NEW SDK Heap:\n");
	for (int i=0; i < 100; i++){
		pDumbs[i] = new DumbSDKHeap;
	}
	heapStats();

	vTaskDelay(1000);
	printf("DELETE SDK Heap:\n");
	for (int i=0; i < 100; i++){
		delete pDumbs[i];
		pDumbs[i] = NULL;
	}
	heapStats();

	for(;;){

		vTaskDelay(3000);
	}
}




/***
 * Launch the tasks and scheduler
 */
void vLaunch( void) {

	//Start blink task
    TaskHandle_t task;
    xTaskCreate(mainTask, "MainThread", 500, NULL, TASK_PRIORITY, &task);

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
