#include "include_asm.h"

/* Advances a ring buffer position by param_2 / 8 bytes, wrapping around when the limit at
   offset 0x24 is reached by subtracting the size at offset 0x28. */
unsigned int func_0012EA70(unsigned int *param_1, int param_2)
{
  unsigned int uVar1;
  
  uVar1 = *(param_1 + 2) + (param_2 >> 3);
  if (*(param_1 + 9) <= uVar1) {
    uVar1 = uVar1 - *(param_1 + 10);
  }
  return uVar1;
}

