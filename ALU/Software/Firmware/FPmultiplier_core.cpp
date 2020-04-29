/*
 * FPmultiplier_core.cpp
 *
 *  Created on: Apr 28, 2020
 *      Author: Dominic
 */

#include "FPmultiplier_core.h"

FPMultCore::FPMultCore(uint32_t core_base_addr) {
   base_addr = core_base_addr;
}

FPMultCore::~FPMultCore() {
}

uint32_t FPMultCore::FPMult(uint32_t Value1, uint32_t Value2){
	io_write(base_addr, Value1_REG, Value1);
	io_write(base_addr, Value2_REG, Value2);
	return io_read(base_addr, 0);
}




