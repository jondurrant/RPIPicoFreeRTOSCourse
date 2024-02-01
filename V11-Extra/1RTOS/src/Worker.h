/*
 * Worker.h
 *
 *  Created on: 17 Jan 2024
 *      Author: jondurrant
 */

#ifndef SRC_WORKER_H_
#define SRC_WORKER_H_

#include "Agent.h"
#include "pico/stdlib.h"



class Worker : public Agent {
public:
	Worker(uint8_t id);
	virtual ~Worker();

protected:
	/***
	 * Task main run loop
	 */
	virtual void run();

	/***
	 * Get the static depth required in words
	 * @return - words
	 */
	virtual configSTACK_DEPTH_TYPE getMaxStackSize();

private:
	bool doWork();

	uint8_t xId;

};


#endif /* SRC_WORKER_H_ */
