#include "include_asm.h"
#include "names.h"

extern volatile int D_001AD520 __attribute__((sda));
extern int D_001B22B8 __attribute__((sda));
extern int D_001B22B4_1 __attribute__((sda));
extern int D_001B22B4;
extern int D_001B22B0;
extern int D_001B22A0[];
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

    flags = D_001AD520 | 0x1F;
    used = g_dma_packet_cursor - D_001B22A0[D_001B22B4];
    D_001AD520 = flags;
    if (used > D_001B22B0) {
        if (used < D_001B22B8)
            D_001B22B8 = used;
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
        func_00127220(packet, D_001B22A0[D_001B22B4]);
        if (ready) {
            gfx_wait_for_dma_status_bits(1);
            gfx_swap_packet_buffer();
        }
    } else {
        D_001AD520 = 0;
        gfx_reset_record_list();
    }
}
