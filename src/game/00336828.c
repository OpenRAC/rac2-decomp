#include "names.h"


extern int D_L04_001ADC6C __attribute__((sda));

extern int D_L04_001ADC70 __attribute__((sda));

extern int func_0028E588(int a, int b);

extern int func_0028EA58(int a, int b, int c, int d, int e, int *p);

/* Draws a coloured quad for a UI element if it is visible, using the element's colour and corner points. */
void func_00336828(int *widget)
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
    DrawHudSpriteGradient(GetIconFrame((int)((float *)widget[13])[0], (int)((float *)widget[13])[1]),
             (int)((float *)widget[0])[0], (int)((float *)widget[0])[1],
             (int)((float *)widget[1])[0], (int)((float *)widget[1])[1], colors);
}
