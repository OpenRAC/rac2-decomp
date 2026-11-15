#include "include_asm.h"
#include "names.h"

extern int D_001A72D0 __attribute__((sda));
extern int D_001A72D4;
extern unsigned char *g_dma_packet_cursor __attribute__((nosda));
extern char D_001ACA60[];

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
    D_001A72D0 = D_001A72D4;
    FlushCache(0);
    func_002F1010();
    gfx_run_level_render_step();
    FlushCache(0);
    func_002F35B0();
    func_002F1E88();
    func_002F2A38();
    mem_fast_helper_c(g_dma_packet_cursor, D_001ACA60, 0x20);
    g_dma_packet_cursor += 0x20;
}
