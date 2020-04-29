/*
 * FPadder_core.h
 *
 *  Created on: Apr 27, 2020
 *      Author: Dominic
 */

#ifndef _FPADDR_H_INCLUDED
#define _FPADDR_H_INCLUDED

#include "chu_io_rw.h"
#include "chu_io_map.h"  // to use SYS_CLK_FREQ

/**
 * adder core driver:
 *  - add two unsigned 32-bit integer.

 */
class FPAdderCore {
public:
   /**
    * register map
    */
   enum {
      Value1_REG = 0x00001,     /**< addend 1 */
      Value2_REG = 0x00002,       /**< addend 2 */

   };

   FPAdderCore(uint32_t adsr_base_addr);
   ~FPAdderCore();                  // not used


   uint32_t Add(uint32_t Value1, uint32_t Value2);

private:
   /* variable to keep track of current status */
   uint32_t base_addr;
   /* current envelope parameters  */
};

#endif //_FPADDR_H_INCLUDED



