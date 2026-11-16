#include "include_asm.h"
#include "names.h"


extern void gfx_append_draw_list_buffer_tag(int);
extern int g_render_layer_flags __attribute__((sda));
extern void RenderFrame(void);

/* Renders a frame with every layer enabled. */
void gfx_render_frame_all_layers_us2(void) {
    extern void gfx_append_draw_list_buffer_tag(int);
    extern void RenderFrame(void);
    extern int g_render_layer_flags __attribute__((sda));
    gfx_append_draw_list_buffer_tag(0);
    g_render_layer_flags = 0x7F;
    RenderFrame();
}

void menu_draw_pause_panels(int);
extern unsigned int menu_get_second_value(void);
extern void menu_draw_pause_panels(int);
extern void menu_draw_message_panel(void);

/* Renders the extra-layer frame when the menu value is 1, or draws the pause panels when it is 0, then draws the message panel. */
void gfx_render_frame_extra_layers_us2(void)
{
    if (menu_get_second_value() == 1) {
        gfx_append_draw_list_buffer_tag(0);
        g_render_layer_flags = 0x100FF;
        RenderFrame();
    } else if (menu_get_second_value() == 0) {
        menu_draw_pause_panels(1);
    }
    menu_draw_message_panel();
}

/* Draws the pause panels with argument 0. */
void gfx_call_frame_helper_zero_us2(void)
{
  menu_draw_pause_panels(0);
  return;
}

