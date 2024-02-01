/*
 * DumbFreeRTOSHeap.cpp
 *
 *  Created on: 1 Feb 2024
 *      Author: jondurrant
 */

#include "DumbFreeRTOSHeap.h"
#include "FreeRTOS.h"

DumbFreeRTOSHeap::DumbFreeRTOSHeap() {
	// NOP

}

DumbFreeRTOSHeap::~DumbFreeRTOSHeap() {
	// NOP
}

void * DumbFreeRTOSHeap::operator new(size_t size){
	return pvPortMalloc( size );
}

void DumbFreeRTOSHeap::operator delete(void * p){
	vPortFree ( p );
}

