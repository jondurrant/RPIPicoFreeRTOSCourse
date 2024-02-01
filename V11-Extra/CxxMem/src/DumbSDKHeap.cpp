/*
 * DumbSDKHeap.cpp
 *
 *  Created on: 1 Feb 2024
 *      Author: jondurrant
 */

#include "DumbSDKHeap.h"
#include<stdlib.h>

DumbSDKHeap::DumbSDKHeap() {
	// NOP

}

DumbSDKHeap::~DumbSDKHeap() {
	// NOP
}

void * DumbSDKHeap::operator new(size_t size){
        void * p = malloc(size);
        return p;
}

void DumbSDKHeap::operator delete(void * p){
        free(p);
}
