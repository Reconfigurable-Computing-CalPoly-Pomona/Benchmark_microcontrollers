#ifndef _SHFT_H_INCLUDED
#define _SHFT_H_INCLUDED

#include "chu_io_rw.h"
#include "chu_io_map.h"  // to use SYS_CLK_FREQ

/**
 * adder core driver:
 *  - add two unsigned 32-bit integer.

 */
class ShifterCore {
public:
   /**
    * register map
    */
   enum {
      Shift_REG = 0x00001,     /**< addend 1 */
      Value_REG = 0x00002,       /**< addend 2 */

   };

   ShifterCore(uint32_t adsr_base_addr);
   ~ShifterCore();                  // not used


   uint32_t Shift(uint32_t Value, uint32_t Shift);

private:
   /* variable to keep track of current status */
   uint32_t base_addr;
   /* current envelope parameters  */
};
#endif  // _SHFT_H_INCLUDED
