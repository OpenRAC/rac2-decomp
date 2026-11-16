#include "include_asm.h"
#include "names.h"





extern short g_transition_mode;
extern int g_render_layer_flags __attribute__((sda));
extern void gfx_render_frame_all_layers(void);
extern void RenderFrame(void);
extern void transition_render_scene(void);

void transition_draw_background_pal(void)
{
    switch (g_transition_mode) {
    case 0:
    case 3:
        gfx_render_frame_all_layers();
        break;
    case 1:
        g_render_layer_flags = 127;
        RenderFrame();
        break;
    case 2:
        transition_render_scene();
        break;
    }
}

