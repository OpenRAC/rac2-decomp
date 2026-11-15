#include "include_asm.h"
#include "names.h"

extern int GetIconFrame(int, int);
extern double __extendsfdf2(float);
extern int __cmpdf2(double, double);
extern double __subdf3(double, double);
extern double __muldf3(double, double);
extern int __fixdfsi(double);
extern void hud_draw_sprite_gradient(int, int, int, int, int, int *);
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];

/* func_US2_002D4D38, the USA v2.00 copy of func_002D3D88: the same C, without the display scaling. */
void func_US2_002D4D38(int index, int x)
{
    int colors[4];
    int leftAlpha;
    int rightAlpha;
    int right;
    int texture;
    int left = x + 2;
    int baseColor = 0xf0f0b0;
    double distance;

    texture = GetIconFrame(0xea97, D_0026CFD0[index].icon);
    distance = __extendsfdf2(256.0f - (float)left);
    if (__cmpdf2(distance, 0.0) < 0)
        distance = __subdf3(0.0, distance);
    leftAlpha = 128 - __fixdfsi(__muldf3(distance, 0.75));
    distance = __extendsfdf2(256.0f - (float)(x + 40));
    if (__cmpdf2(distance, 0.0) < 0)
        distance = __subdf3(0.0, distance);
    rightAlpha = 128 - __fixdfsi(__muldf3(distance, 0.75));
    if (leftAlpha < 0)
        leftAlpha = 0;
    if (rightAlpha < 0)
        right = 0;
    else
        right = rightAlpha;
    leftAlpha <<= 24;
    right <<= 24;
    colors[2] = colors[0] = leftAlpha | baseColor;
    colors[3] = colors[1] = right | baseColor;
    hud_draw_sprite_gradient(texture, left, 334, 40, 40, colors);
}

/* func_US2_002D4ED8 lives in 002D4ED8-g8.c. */

