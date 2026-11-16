#include "include_asm.h"
#include "names.h"

extern volatile int g_packet_flags __attribute__((sda));
extern int g_packet_min_free __attribute__((sda));
extern int D_001B22B4_1 __attribute__((sda));
extern int g_packet_buffer_index;
extern int g_packet_buffer_size;
extern int g_packet_buffer_table[];
extern int g_dma_packet_cursor;
extern int sceDmaGetChan(unsigned int);
extern void FlushCache(int);
extern void func_00127220(void *, int);
extern void gfx_wait_for_dma_status_bits(unsigned long);
extern void gfx_swap_packet_buffer(void);
extern void gfx_reset_record_list(void);

/* Terminates and submits the DMA chain, advancing the buffer when full. */
void SubmitBufferedDmaChain(void)
{
    int flags;
    int used;
    int ready = 0;
    char *packet;

    flags = g_packet_flags | 0x1F;
    used = g_dma_packet_cursor - g_packet_buffer_table[g_packet_buffer_index];
    g_packet_flags = flags;
    if (used > g_packet_buffer_size) {
        if (used < g_packet_min_free)
            g_packet_min_free = used;
        ready = 1;
    }
    if (!ready || D_001B22B4_1 == 0) {
        *(int *)(g_dma_packet_cursor + 0) = 0x70000000;
        *(int *)(g_dma_packet_cursor + 4) = 0;
        *(int *)(g_dma_packet_cursor + 8) = 0;
        *(int *)(g_dma_packet_cursor + 12) = 0;
        packet = (char *)sceDmaGetChan(1);
        *(int *)packet |= 0xC0;
        FlushCache(0);
        func_00127220(packet, g_packet_buffer_table[g_packet_buffer_index]);
        if (ready) {
            gfx_wait_for_dma_status_bits(1);
            gfx_swap_packet_buffer();
        }
    } else {
        g_packet_flags = 0;
        gfx_reset_record_list();
    }
}
