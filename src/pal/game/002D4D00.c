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
extern PreviewChoice g_preview_choices[];

/* func_PAL_002D4D00, the PAL copy of func_002D3D88: the same C, where the display-scaled y and height
   become the fixed 334 and 40. */
void draw_preview_choice_icon_pal(int index, int x)
{
    int colors[4];
    int left_alpha;
    int right_alpha;
    int right;
    int texture;
    int left = x + 2;
    int base_color = 0xf0f0b0;
    double distance;

    texture = GetIconFrame(0xea97, g_preview_choices[index].icon);
    distance = __extendsfdf2(256.0f - (float)left);
    if (__cmpdf2(distance, 0.0) < 0)
        distance = __subdf3(0.0, distance);
    left_alpha = 128 - __fixdfsi(__muldf3(distance, 0.75));
    distance = __extendsfdf2(256.0f - (float)(x + 40));
    if (__cmpdf2(distance, 0.0) < 0)
        distance = __subdf3(0.0, distance);
    right_alpha = 128 - __fixdfsi(__muldf3(distance, 0.75));
    if (left_alpha < 0)
        left_alpha = 0;
    if (right_alpha < 0)
        right = 0;
    else
        right = right_alpha;
    left_alpha <<= 24;
    right <<= 24;
    colors[2] = colors[0] = left_alpha | base_color;
    colors[3] = colors[1] = right | base_color;
    hud_draw_sprite_gradient(texture, left, 334, 40, 40, colors);
}

/* func_PAL_002D4EA0 lives in 002D4EA0-g8.c. */
