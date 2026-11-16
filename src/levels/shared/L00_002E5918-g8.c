#include "include_asm.h"
#include "names.h"

extern void RenderFrame(void);

extern unsigned int g_screen_overlay_color;

/* Sets a draw setting to a fixed value and renders the frame. */
void gfx_set_draw_mode_and_render(void) {
 g_screen_overlay_color = 0x100FF;
 RenderFrame();
}

extern void gfx_append_draw_list_buffer_tag(int);

extern void gfx_set_clear_color_packet(int, int, int, int);

/* Clears the screen to black, sets a draw setting and renders the frame. */
void gfx_clear_screen_and_render(void) {
 gfx_append_draw_list_buffer_tag(0);
 gfx_set_clear_color_packet(0, 0, 0, 0x80);
 g_screen_overlay_color = 0xF0;
 RenderFrame();
}

extern int g_draw_flag_enabled;

/* Turns a draw flag on. */
void gfx_enable_draw_flag(void) {
    g_draw_flag_enabled = 1;
}

/* Turns a draw flag off. */
void gfx_disable_draw_flag(void) {
    g_draw_flag_enabled = 0;
}

/* ---- 0x002E73E0: a counter bump around three measured callees. ---- */

extern int g_ring_animation_counter;
extern int g_vram_display_address;
extern int g_screen_height;

extern void ref_L00_002E73E0_00(int);
extern int ref_L00_002E73E0_01(void);
extern void ref_L00_002E73E0_02(void *, int, int);

extern int sceGsSyncV(int);

/* Starts a draw pass, bumps a frame counter and draws the given item. */
void gfx_draw_item_with_pass(void *item) {
    ref_L00_002E73E0_00(1);
    sceGsSyncV(0);
    g_ring_animation_counter = g_ring_animation_counter + 1;
    ref_L00_002E73E0_01();
    ref_L00_002E73E0_02(item, g_vram_display_address, g_screen_height << 11);
}
