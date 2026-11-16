#include "common.h"

/* Fade sequence follows rac1-decomp src/game/draw.c (GPL-3.0). */
typedef union { int *words; char *bytes; int address; } PacketCursor;

extern void gfx_wait_for_dma_status_bits(int);
extern void gfx_reset_packet_buffer(void);
extern void SubmitBufferedDmaChain(void);
extern void gfx_swap_packet_buffer(void);
extern int sceGsSyncV(int);
extern void gfx_append_draw_list_header(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern void PutDrawBufferSmall(void);
extern void VU1_addGSregister(unsigned int, unsigned long);
extern int g_frame_counter_3;
extern int D_001B1598_GP SDATA(D_001B1598);
extern PacketCursor ref_0027D330_00;
extern char g_gfx_clear_packet_b[];

/* Fades the screen to black over the given number of frames. */
void FadeToBlack(int frames)
{
    int i;

    gfx_wait_for_dma_status_bits(1);
    sceGsSyncV(0);
    D_001B1598_GP = g_frame_counter_3 + 1;
    gfx_reset_packet_buffer();
    i = frames - 1;
    if (i >= 0) {
        do {
            int q;

            gfx_append_draw_list_header();
            gfx_append_draw_list_buffer_tag(1);
            PutDrawBufferSmall();
            VU1_addGSregister(0x42, 0x8000000044UL);
            q = (i << 7) / (i + 1);
            i--;
            VU1_addGSregister(1, (unsigned long)(128 - q) << 24);
            ref_0027D330_00.words[0] = 0x30000014;
            ref_0027D330_00.words[1] = (int)g_gfx_clear_packet_b;
            ref_0027D330_00.words[2] = 0;
            ref_0027D330_00.words[3] = 0x50000014;
            ref_0027D330_00.words += 4;
            gfx_wait_for_dma_status_bits(1);
            sceGsSyncV(0);
            D_001B1598_GP = g_frame_counter_3 + 1;
            SubmitBufferedDmaChain();
            gfx_swap_packet_buffer();
        } while (i >= 0);
    }
    gfx_wait_for_dma_status_bits(1);
    sceGsSyncV(0);
    D_001B1598_GP = g_frame_counter_3 + 1;
    gfx_reset_packet_buffer();
    gfx_append_draw_list_header();
    gfx_append_draw_list_buffer_tag(1);
}
