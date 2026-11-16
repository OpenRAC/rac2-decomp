#include "include_asm.h"
#include "names.h"


extern void gfx_append_draw_list_buffer_tag(int);
extern int g_render_layer_flags __attribute__((sda));
extern void RenderFrame(void);

void gfx_render_frame_all_layers_pal(void) {
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

void gfx_render_frame_extra_layers_pal(void)
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

void gfx_call_frame_helper_zero_pal(void)
{
  menu_draw_pause_panels(0);
  return;
}

