#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_VEC_F6BF9CE42
#define RAC2_T_VEC_F6BF9CE42
typedef struct { float x; float y; } VEC_F6bf9ce42;
#endif

extern int g_menu_panel_frame_left __attribute__((sda));

extern int g_menu_panel_frame_top;

extern int g_menu_panel_frame_right;

extern int g_menu_panel_frame_bottom;

extern int g_menu_panel_frame_margin_x __attribute__((sda));

extern int g_menu_panel_frame_margin_y;

extern int g_screen_width;

extern int g_screen_height;

extern int math_ping_pong_blend_values(int a, int b, int c, int d, int e);

extern void DrawFramebufferRect(int a, int b, int c, int d, int e, int f, int g);

/* Draws the coloured frame around a menu panel at its current position. */
void menu_panel_draw_frame(VEC_F6bf9ce42 **positionPtr)
{
    int left, top, bottom, right;
    int colour;


    VEC_F6bf9ce42 *position;
    position = *positionPtr;
    left = (int)((float)g_menu_panel_frame_left + position->x - (float)g_menu_panel_frame_margin_x);
    top = (int)((float)g_menu_panel_frame_top + position->y - (float)g_menu_panel_frame_margin_y);
    right = (int)((float)g_menu_panel_frame_right + position->x + (float)g_menu_panel_frame_margin_x);
    bottom = (int)((float)g_menu_panel_frame_bottom + position->y + (float)g_menu_panel_frame_margin_y);

    colour = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 20, 0, 0);
    DrawFramebufferRect(left, top, right, bottom, g_screen_width, g_screen_height, colour);

    position = *positionPtr;
    DrawFramebufferRect((int)((float)g_menu_panel_frame_left + position->x), (int)((float)g_menu_panel_frame_top + position->y),
            (int)((float)g_menu_panel_frame_right + position->x), (int)((float)g_menu_panel_frame_bottom + position->y),
            g_screen_width, g_screen_height, 0x60241700);

}
