#include "include_asm.h"
#include "names.h"

extern void RenderFrame(void);

extern unsigned int D_L00_001B18D4;

/* Sets a draw setting to a fixed value and renders the frame. */
void gfx_set_draw_mode_and_render(void) {
 D_L00_001B18D4 = 0x100FF;
 RenderFrame();
}

extern void gfx_append_draw_list_buffer_tag(int);

extern void gfx_set_clear_color_packet(int, int, int, int);

/* Clears the screen to black, sets a draw setting and renders the frame. */
void gfx_clear_screen_and_render(void) {
 gfx_append_draw_list_buffer_tag(0);
 gfx_set_clear_color_packet(0, 0, 0, 0x80);
 D_L00_001B18D4 = 0xF0;
 RenderFrame();
}

extern int D_L00_001B19A8;

/* Turns a draw flag on. */
void gfx_enable_draw_flag(void) {
    D_L00_001B19A8 = 1;
}

/* Turns a draw flag off. */
void gfx_disable_draw_flag(void) {
    D_L00_001B19A8 = 0;
}

/* ---- 0x002E73E0: a counter bump around three measured callees. ---- */

extern int D_L00_001B18D8;
extern int D_001A72DC;
extern int g_screen_height;

extern void ref_L00_002E73E0_00(int);
extern int ref_L00_002E73E0_01(void);
extern void ref_L00_002E73E0_02(void *, int, int);

extern int sceGsSyncV(int);

/* Starts a draw pass, bumps a frame counter and draws the given item. */
void gfx_draw_item_with_pass(void *item) {
    ref_L00_002E73E0_00(1);
    sceGsSyncV(0);
    D_L00_001B18D8 = D_L00_001B18D8 + 1;
    ref_L00_002E73E0_01();
    ref_L00_002E73E0_02(item, D_001A72DC, g_screen_height << 11);
}
