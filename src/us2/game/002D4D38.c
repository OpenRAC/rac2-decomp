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
    int value, display_choice, selection_mask, required_bits, icon;
} PreviewChoice;
extern PreviewChoice g_preview_choices[];

/* Draws the icon of one preview choice as a 40x40 sprite that fades out away from the screen centre.
   (USA v2.00 copy of func_002D3D88: the same C, without the display scaling.)
   Original note: func_US2_002D4D38, the USA v2.00 copy of func_002D3D88: the same C, without the display scaling. */
void preview_choice_icon_draw_us2(int index, int x)
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

/* func_US2_002D4ED8 lives in 002D4ED8-g8.c. */

