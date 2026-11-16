#include "include_asm.h"
#include "names.h"

extern int g_vram_cursor __attribute__((sda));
extern int g_vram_frame_base;
extern unsigned char *g_dma_packet_cursor __attribute__((nosda));
extern char g_level_render_pass_packet[];

extern void VU1_addGSregister(unsigned int reg, unsigned long long value);
extern void FlushCache(int);
extern void func_002F1010(void);
extern void gfx_run_level_render_step(void);
extern void func_002F35B0(void);
extern void func_002F1E88(void);
extern void func_002F2A38(void);
extern void mem_fast_helper_c(void *, void *, int);

/* Starts the display list for the level, moves the resident chain cursor and
   appends the 0x20-byte packet at D_001ACA60. */
/* Draws one frame of the level: sets up the render state, runs each render pass in order, then adds the frame's final packet. */
void gfx_draw_level_render_passes(void)
{
    VU1_addGSregister(0x47, 0x5180B);
    g_vram_cursor = g_vram_frame_base;
    FlushCache(0);
    func_002F1010();
    gfx_run_level_render_step();
    FlushCache(0);
    func_002F35B0();
    func_002F1E88();
    func_002F2A38();
    mem_fast_helper_c(g_dma_packet_cursor, g_level_render_pass_packet, 0x20);
    g_dma_packet_cursor += 0x20;
}
