/*
 * multiplier_core.h
 *
 *  Created on: Apr 27, 2020
 *      Author: Dominic
 */

#ifndef _MULT_H_INCLUDED
#define _MULT_H_INCLUDED

#include "chu_io_rw.h"
#include "chu_io_map.h"  // to use SYS_CLK_FREQ

/**
 * adder core driver:
 *  - add two unsigned 32-bit integer.

 */
class MultCore {
public:
   /**
    * register map
    */
   enum {
      Value1_REG = 0x00001,     /**< addend 1 */
      Value2_REG = 0x00002,     /**< addend 2 */
	  Upper_REG = 0x00004,		/**< upper reg */
	  Lower_REG = 0x00000		/**< lower reg */
   };

   MultCore(uint32_t adsr_base_addr);
   ~MultCore();                  // not used


   uint32_t Mult(uint32_t Value1, uint32_t Value2);

//   unsigned int MultUpper(unsigned int Value1, unsigned int Value2);

private:
   /* variable to keep track of current status */
   uint32_t base_addr;
   /* current envelope parameters  */
};

#endif //_MULT_H_INCLUDED
