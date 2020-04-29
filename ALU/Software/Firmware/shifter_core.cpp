/*
 * shifter_core.cpp
 *
 *  Created on: Apr 28, 2020
 *      Author: Dominic
 */

#include "shifter_core.h"

ShifterCore::ShifterCore(uint32_t core_base_addr) {
   base_addr = core_base_addr;
}

ShifterCore::~ShifterCore() {
}

uint32_t ShifterCore::Shift(uint32_t Value, uint32_t Shift){
	io_write(base_addr, Shift, Value);
//	io_write(base_addr, Shift_REG, Shift);
	return io_read(base_addr, Shift);
}



