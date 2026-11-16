#include "include_asm.h"
#include "names.h"

extern unsigned int g_dma_packet_cursor __attribute__((sda));
extern char *g_fs_aa_buffer_table __attribute__((section(".sdata")));
extern char g_loader_movie[];
extern void text_draw_pulsing_us2(void);
extern void DrawSubtitles(void);
extern char g_dma_screen_packet[];
extern int g_scene_playback_state[];
extern void iFlushCache(int);

/* Starts a DMA chain at packet: two ref tags sent through VIF DIRECT (9 quadwords from
   the screen context + 0xC0, 0x25 from D_001A6AF0), counts the frame at D_001B8840 + 0x34,
   lets one of two builders append, then ends the chain and hands it to func_0011AED0.
   The cursor is an integer address, so each word stored through it may alias it and it
   is read again before every store. */
void BuildFrameDmaChain_us2(unsigned int *packet)
{
    g_dma_packet_cursor = (unsigned int)packet;
    *(unsigned int *)(g_dma_packet_cursor + 0x00) = 0x30000009;
    *(unsigned int *)(g_dma_packet_cursor + 0x04) = (unsigned int)(g_fs_aa_buffer_table + 0xC0) & 0x0FFFFFFF;
    *(unsigned int *)(g_dma_packet_cursor + 0x08) = 0;
    *(unsigned int *)(g_dma_packet_cursor + 0x0C) = 0x50000009;
    *(unsigned int *)(g_dma_packet_cursor + 0x10) = 0x30000025;
    *(unsigned int *)(g_dma_packet_cursor + 0x14) = (unsigned int)g_dma_screen_packet;
    *(unsigned int *)(g_dma_packet_cursor + 0x18) = 0;
    *(unsigned int *)(g_dma_packet_cursor + 0x1C) = 0x50000025;
    g_dma_packet_cursor += 0x20;
    g_scene_playback_state[13]++;
    if (*(int *)g_loader_movie)
        text_draw_pulsing_us2();
    else
        DrawSubtitles();
    *(unsigned int *)(g_dma_packet_cursor + 0x00) = 0x70000000;
    *(unsigned int *)(g_dma_packet_cursor + 0x04) = 0;
    g_dma_packet_cursor += 0x10;
    iFlushCache(0);
}

