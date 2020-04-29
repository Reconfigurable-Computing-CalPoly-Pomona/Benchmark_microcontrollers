/*
 * multiplier_core.cpp
 *
 *  Created on: Apr 27, 2020
 *      Author: Dominic
 */


#include "multiplier_core.h"

MultCore::MultCore(uint32_t core_base_addr) {
   base_addr = core_base_addr;
}

MultCore::~MultCore() {
}

uint32_t MultCore::Mult(uint32_t Value1, uint32_t Value2){
	io_write(base_addr, Value1_REG, Value1);
	io_write(base_addr, Value2_REG, Value2);
	return io_read(base_addr, Lower_REG);
}
