/*
 * DumbSDKHeap.h
 *
 * Class forces allocation from the Pico SDK Heap
 *
 *  Created on: 1 Feb 2024
 *      Author: jondurrant
 */

#ifndef V11_EXTRA_CXXMEM_SRC_DUMBSDKHEAP_H_
#define V11_EXTRA_CXXMEM_SRC_DUMBSDKHEAP_H_

#include "Dumb.h"
#include "pico/stdlib.h"

class DumbSDKHeap : public Dumb{
public:
	DumbSDKHeap();
	virtual ~DumbSDKHeap();

	void * operator new(size_t size);

	 void operator delete(void * p);
};

#endif /* V11_EXTRA_CXXMEM_SRC_DUMBSDKHEAP_H_ */
