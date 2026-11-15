#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_VEC_F6BF9CE42
#define RAC2_T_VEC_F6BF9CE42
typedef struct { float x; float y; } VEC_F6bf9ce42;
#endif

extern int D_L04_001AE478 __attribute__((sda));

extern int D_L04_001AE47C;

extern int D_L04_001AE480;

extern int D_L04_001AE484;

extern int D_L04_001AE488 __attribute__((sda));

extern int D_L04_001AE48C;

extern int g_screen_width;

extern int g_screen_height;

extern int math_ping_pong_blend_values(int a, int b, int c, int d, int e);

extern int DrawFramebufferRect(int a, int b, int c, int d, int e, int f, int g);

/* Draws the coloured frame around a menu panel at its current position. */
void menu_panel_draw_frame(VEC_F6bf9ce42 **positionPtr)
{
    int left, top, bottom, right;
    int colour;


    VEC_F6bf9ce42 *position;
    position = *positionPtr;
    left = (int)((float)D_L04_001AE478 + position->x - (float)D_L04_001AE488);
    top = (int)((float)D_L04_001AE47C + position->y - (float)D_L04_001AE48C);
    right = (int)((float)D_L04_001AE480 + position->x + (float)D_L04_001AE488);
    bottom = (int)((float)D_L04_001AE484 + position->y + (float)D_L04_001AE48C);

    colour = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 20, 0, 0);
    DrawFramebufferRect(left, top, right, bottom, g_screen_width, g_screen_height, colour);

    position = *positionPtr;
    DrawFramebufferRect((int)((float)D_L04_001AE478 + position->x), (int)((float)D_L04_001AE47C + position->y),
            (int)((float)D_L04_001AE480 + position->x), (int)((float)D_L04_001AE484 + position->y),
            g_screen_width, g_screen_height, 0x60241700);

}
