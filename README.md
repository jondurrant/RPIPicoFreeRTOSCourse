# RPIPicoFreeRTOSCourse
Course Repository for Udemy Course: [FreeRTOS on Raspberry PI PICO](https://www.udemy.com/course/draft/4868484/?referralCode=C5A9A19C93919A9DA294)

16 Examples of which 15 demonstrate FreeRTOS features on the Raspberry PI Pico or RP2040 board. One of which that focuses on the SDK multicore API functions.

## 2 Pico Setup

+ BlinkLEDExt: Blink an external LED on GPIO using a function approach.

## 4 Tasks

+ Blink Ext: Blink an external LED on GPIO 0, encapsulating the task within a Class.
+ MultiBlink: Blink multiple LEDs using different task priority
+ BlinkPriority: Use priority with tasks that create CPU workload
+ BlinkAssignment: Explore priority


## 5 Semaphore

+ SharedLED: Defined shared LED which will be used by two blink LED pair objects. Creating a contention scenario that requires semaphores. 
+ LimitWorkers: Use count semaphore to limit the number of active tasks using a resource
+ AssignmentLimitWorkers: Explore counting semaphores in assignment
+ BlinkWorker: Create a scenario of workers that will blink out of sync
+ TaskNotification: Use task notification as two semaphores to synchronize the two tasks


## 6 Queue

+ CountLed: Display a binary value on four LEDs (0 to 15) that is being sent to the task via a queue
+ AssignmentQueue: Assignment question to use queues

## 7 MessageBuf

+ JsonCmds: Use of message buffer to send a JSON strong to a task. Decode the JSON and display the contained value on four LEDs
+ SerialCmds: Two Pico communicating together over UART to display the same value on four LEDs in sync

## 8 Multicore

+ sdKMulticore: Use both cores and send a random number from core 0 to core 1 using the SDK FIFO queue
+ FreeRTOSSMP: Use SMP to run tasks across both cores and some associated with single core

