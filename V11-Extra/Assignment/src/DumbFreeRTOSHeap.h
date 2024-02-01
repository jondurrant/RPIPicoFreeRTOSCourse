/*
 * DumbFreeRTOSHeap.h
 *
 * Class forces allocation from the FreeRTOS Heap
 *  Created on: 1 Feb 2024
 *      Author: jondurrant
 */

#ifndef V11_EXTRA_ASSIGNMENT_SRC_DUMBFREERTOSHEAP_H_
#define V11_EXTRA_ASSIGNMENT_SRC_DUMBFREERTOSHEAP_H_

#include "Dumb.h"
#include "pico/stdlib.h"

class DumbFreeRTOSHeap : public Dumb{
public:
	DumbFreeRTOSHeap();
	virtual ~DumbFreeRTOSHeap();

	void * operator new(size_t size);

	void operator delete(void * p);
};

#endif /* V11_EXTRA_ASSIGNMENT_SRC_DUMBFREERTOSHEAP_H_ */
