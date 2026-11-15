#include "include_asm.h"
#include "names.h"


extern short D_00152C20;
extern int D_001B1594 __attribute__((sda));
extern void gfx_render_frame_all_layers(void);
extern void RenderFrame(void);
extern void transition_render_scene(void);

void func_US2_002EB740(void)
{
    switch (D_00152C20) {
    case 0:
    case 3:
        gfx_render_frame_all_layers();
        break;
    case 1:
        D_001B1594 = 127;
        RenderFrame();
        break;
    case 2:
        transition_render_scene();
        break;
    }
}

