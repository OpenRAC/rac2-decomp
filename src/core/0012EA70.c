#include "include_asm.h"
#include "names.h"

/* Finds the address of a bit position in the ring buffer, wrapping around at the end. */
unsigned int mpeg_get_bit_stream_byte_pointer(unsigned int *stream, int bitPos)
{
  unsigned int addr;
  
  addr = *(stream + 2) + (bitPos >> 3);
  if (*(stream + 9) <= addr) {
    addr = addr - *(stream + 10);
  }
  return addr;
}

