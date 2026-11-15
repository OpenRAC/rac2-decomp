#include "include_asm.h"
#include "names.h"

/* A -G0 unit of its own: retail loads D_001B22A8 absolutely (lui/lw) everywhere except the
   store in the call's delay slot, which the assembler turns into the one-instruction $gp form
   for a bare small-data symbol. 002FC3C0.c is -G8 and would load it through $gp too. */
extern unsigned char *g_dma_packet_cursor __attribute__((sda));

/* func_00282B50 is a quadword copy: (destination, source, byte count). */
extern void mem_fast_helper_c(void *destination, void *source, int bytes);

/* Appends a four-word packet header to the buffer at D_001B22A8 (a tag with the quadword count,
   a zero word, a fixed word, and a word built from a0 and the count), then copies count
   quadwords from source behind it and advances the buffer. */
void gfx_append_vif_unpack_data(unsigned int unpackAddress, void *source, unsigned int count)
{
    *(unsigned int *)(g_dma_packet_cursor + 0) = 0x10000000u | count;
    *(unsigned int *)(g_dma_packet_cursor + 4) = 0;
    *(unsigned int *)(g_dma_packet_cursor + 8) = 0x01000404u;
    *(unsigned int *)(g_dma_packet_cursor + 12) = unpackAddress | (count << 16) | 0x6C000000u;
    g_dma_packet_cursor += 16;
    mem_fast_helper_c(g_dma_packet_cursor, source, count << 4);
    g_dma_packet_cursor += count << 4;
}
