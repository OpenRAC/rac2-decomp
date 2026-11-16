#include "include_asm.h"
#include "names.h"

extern char *g_dma_packet_cursor __attribute__((sda));
extern char g_dma_strip_packet_first[];
extern char g_dma_strip_packet_second[];

/* Queues a draw list that runs the first set of screen strip packets. */
void gfx_queue_first_strip_packet(void)
{
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 0) = 0x30000026;
    *(char **)(*(char * volatile *)&g_dma_packet_cursor + 4) = g_dma_strip_packet_first;
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 8) = 0;
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 12) = 0x50000026;
    g_dma_packet_cursor = *(char * volatile *)&g_dma_packet_cursor + 16;
}


/* Queues a draw list that runs the second set of screen strip packets. */
void gfx_queue_second_strip_packet(void)
{
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 0) = 0x30000029;
    *(char **)(*(char * volatile *)&g_dma_packet_cursor + 4) = g_dma_strip_packet_second;
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 8) = 0;
    *(int *)(*(char * volatile *)&g_dma_packet_cursor + 12) = 0x50000029;
    g_dma_packet_cursor = *(char * volatile *)&g_dma_packet_cursor + 16;
}
