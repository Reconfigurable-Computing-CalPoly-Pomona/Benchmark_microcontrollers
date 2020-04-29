/*
 * RAM_core.h
 *
 *  Created on: Apr 27, 2020
 *      Author: Dominic
 */

#include "RAM_core.h"

RAMCore::RAMCore(uint32_t core_base_addr) {
   base_addr = core_base_addr;
}

RAMCore::~RAMCore() {
}

void RAMCore::Store(uint32_t Address, uint32_t Value){
	io_write(base_addr, Address, Value);
}

void RAMCore::FPStore(uint32_t Address, uint32_t Value){
	io_write(base_addr, Address, Value);
}


uint32_t RAMCore::Load(uint32_t Address){
	return io_read(base_addr, Address);
}


uint32_t RAMCore::FPLoad(uint32_t Address){
	return io_read(base_addr, Address);
}
