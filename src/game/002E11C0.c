#include "names.h"
/* Advance the resident table pointer and hand the engine the table start. Every global
   carries the sda attribute: under -G0 that gives the assembler macro form (lui + access
   sharing one register), and the one store inside the jal delay slot takes the single $gp
   form, so one name serves both of the retail's address forms. */
extern void *g_dma_packet_cursor __attribute__((sda));
extern void *g_dma_list_tail __attribute__((sda));
extern int g_vram_cursor __attribute__((sda));
extern int g_vram_frame_base __attribute__((sda));
extern char g_gfx_register_block_a[];
extern void FlushCache(int);
extern void gfx_init_render_setup_state(void);
extern void gfx_write_register_with_sync(void *first, int second, int third);
extern void gfx_link_display_lists_track_size(void);

/* Moves the buffer cursor ahead and starts a new render setup pass. */
void gfx_begin_render_setup(void)
{
    char *cursor = (char *)g_dma_packet_cursor;
    int savedMark = g_vram_frame_base;

    g_dma_list_tail = cursor;
    cursor += 0x10;
    g_vram_cursor = savedMark;
    g_dma_packet_cursor = cursor;
    FlushCache(0);
    gfx_init_render_setup_state();
    gfx_write_register_with_sync(g_gfx_register_block_a, 0x3200, 0x40);
    gfx_link_display_lists_track_size();
}
