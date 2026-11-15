#include "include_asm.h"

/* Finds the address of a bit position in the ring buffer, wrapping around at the end. */
unsigned int func_0012EA70(unsigned int *stream, int bitPos)
{
  unsigned int addr;
  
  addr = *(stream + 2) + (bitPos >> 3);
  if (*(stream + 9) <= addr) {
    addr = addr - *(stream + 10);
  }
  return addr;
}

