#include "names.h"


extern int D_L04_001ADC6C __attribute__((sda));

extern int D_L04_001ADC70 __attribute__((sda));

extern int GetIconFrame(int a, int b);

extern int hud_draw_sprite_gradient(int a, int b, int c, int d, int e, int *p);

/* Draws a coloured quad for a UI element if it is visible, using the element's colour and corner points. */
void hud_draw_colored_quad_widget(int *widget)
{
    int colors[4];
    float visibility;

    visibility = *(float *)widget[4];
    if (visibility == 0.0f)
        return;
    if (D_L04_001ADC6C != 0)
        *(int *)widget[3] = (*(int *)widget[3] & 0xff000000) | (D_L04_001ADC70 & 0x00ffffff);
    colors[0] = *(int *)widget[3];
    colors[1] = *(int *)widget[3];
    colors[2] = *(int *)widget[3];
    colors[3] = *(int *)widget[3];
    hud_draw_sprite_gradient(GetIconFrame((int)((float *)widget[13])[0], (int)((float *)widget[13])[1]),
             (int)((float *)widget[0])[0], (int)((float *)widget[0])[1],
             (int)((float *)widget[1])[0], (int)((float *)widget[1])[1], colors);
}
