#include "include_asm.h"
#include "names.h"

/* A -G0 unit of its own: retail loads D_001B22A8 absolutely (lui/lw) everywhere except the
   store in the call's delay slot, which the assembler turns into the one-instruction $gp form
   for a bare small-data symbol. 002FC3C0.c is -G8 and would load it through $gp too. */
extern unsigned char *D_001B22A8 __attribute__((sda));

/* func_00282B50 is a quadword copy: (destination, source, byte count). */
extern void func_00282B50(void *destination, void *source, int bytes);

/* Appends a four-word packet header to the buffer at D_001B22A8 (a tag with the quadword count,
   a zero word, a fixed word, and a word built from a0 and the count), then copies count
   quadwords from source behind it and advances the buffer. */
void func_002FC468(unsigned int unpackAddress, void *source, unsigned int count)
{
    *(unsigned int *)(gDmaPacketCursor + 0) = 0x10000000u | count;
    *(unsigned int *)(gDmaPacketCursor + 4) = 0;
    *(unsigned int *)(gDmaPacketCursor + 8) = 0x01000404u;
    *(unsigned int *)(gDmaPacketCursor + 12) = unpackAddress | (count << 16) | 0x6C000000u;
    gDmaPacketCursor += 16;
    FastMemoryHelperC(gDmaPacketCursor, source, count << 4);
    gDmaPacketCursor += count << 4;
}
