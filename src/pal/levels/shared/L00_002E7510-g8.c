#include "include_asm.h"
#include "names.h"
extern void RenderFrame(void);
extern unsigned int g_screen_overlay_color;

/* Sets the screen overlay color and renders a frame. */
void gfx_set_draw_mode_and_render_pal(void) {
 g_screen_overlay_color = 0x100FF;
 RenderFrame();
}

extern void gfx_append_draw_list_buffer_tag(int);
extern void gfx_set_clear_color_packet(int, int, int, int);

/* Clears the screen to a color and renders a frame. */
void gfx_clear_screen_and_render_pal(void) {
 gfx_append_draw_list_buffer_tag(0);
 gfx_set_clear_color_packet(0, 0, 0, 0x80);
 g_screen_overlay_color = 0xF0;
 RenderFrame();
}
