#include "include_asm.h"
#include "names.h"

extern char *g_dma_packet_cursor __attribute__((sda));
extern char D_001AC950[];

/* Queues a block of preset graphics data (table 1) for the vector unit. */
void gfx_append_vu1_preset_a(void)
{
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 0) = 0x30000003;
    *(char **)(*(char * volatile *)&g_dma_packet_cursor + 4) = D_001AC950;
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 8) = 0;
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 12) = 0x50000003;
    g_dma_packet_cursor = *(char * volatile *)&g_dma_packet_cursor + 16;
}
