/*
 * RAM_core.h
 *
 *  Created on: Apr 27, 2020
 *      Author: Dominic
 */

//does not function. The HDL test bench works but this does not. Requires more work.

#ifndef _RAM_H_INCLUDED
#define _RAM_H_INCLUDED

#include "chu_io_rw.h"
#include "chu_io_map.h"  // to use SYS_CLK_FREQ

/**
 * RAM core driver:
 *  - store a unsigned 32-bit integer.
 *  - load a unsigned 32-bit integer.
 */
class RAMCore {
public:

   RAMCore(uint32_t adsr_base_addr);
   ~RAMCore();                  // not used


void Store(uint32_t Address, uint32_t Value);
void FPStore(uint32_t Address, uint32_t Value);

uint32_t Load(uint32_t Address);
uint32_t FPLoad(uint32_t Address);

private:
   /* variable to keep track of current status */
   uint32_t base_addr;
   /* current envelope parameters  */
};
#endif  // _ADDR_H_INCLUDED
