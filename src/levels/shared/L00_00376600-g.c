#include "common.h"

extern char g_purchase_menu_model[];
extern float D_L00_001B25E0[] __attribute__((sda));
extern int g_is_pal_video[] __attribute__((sda));
extern int g_screen_width[] __attribute__((sda)), g_screen_height[] __attribute__((sda));
extern void gfx_set_scissor_clamped(int, int, int, int);
extern int subtract_integer_with_clamp(int);
extern void DrawFramebufferRect(int, int, int, int, int, int, unsigned int);
extern int GetIconFrame(int, int);
extern double __extendsfdf2(float);
extern int __cmpdf2(double, double);
extern double __subdf3(double, double);
extern int __fixdfsi(double);
extern void hud_draw_sprite_gradient(int, int, int, int, int, unsigned int *);

/* Draws the row of item icons with a pulsing highlight box around the selected one, fading them at the edges. */
void shop_draw_item_icon_strip(void) {
    unsigned int colors[4];
    char *model;
    int top;
    int bottom;
    int outer_top, outer_bottom, inner_top, inner_bottom;
    char *loop_model;
    int y;
    int start;
    int initial_y;
    char *scroll;
    int pulse;
    int relative;
    int x;
    int slot;
    int handle;
    int first_alpha;
    int second_alpha;
    unsigned int shade;
    double distance;
    unsigned int tint;
    initial_y = (int)(D_L00_001B25E0[0] * 185.0f + 0.5f);
    initial_y += g_is_pal_video[0] ? 4 : 0;
    gfx_set_scissor_clamped(48, 298, (int)(D_L00_001B25E0[0] * 120.0f + 0.5f), initial_y);
    scroll = g_purchase_menu_model;
    if (*(int *)(scroll + 0x6C) < 0) *(int *)(scroll + 0x6C) += 4;
    else if (*(int *)(scroll + 0x6C) > 0) *(int *)(scroll + 0x6C) -= 4;
    model = g_purchase_menu_model;
    pulse = subtract_integer_with_clamp(((*(int *)(model + 4) * 4) & 63) - 32) + 64;
    if (*(int *)(model + 0x144 + *(int *)(model + 0x80) * 12) > 0) {
        shade = pulse * 0x10202;
        outer_top = (int)(D_L00_001B25E0[0] * 123.0f + 0.5f);
        outer_bottom = (int)(D_L00_001B25E0[0] * 179.0f + 0.5f);
        outer_top += g_is_pal_video[0] ? 4 : 0; outer_bottom += g_is_pal_video[0] ? 4 : 0;
        DrawFramebufferRect(101, outer_top, 157, outer_bottom, g_screen_width[0], g_screen_height[0],
                      shade | 0x80000000u);
        inner_top = (int)(D_L00_001B25E0[0] * 125.0f + 0.5f);
        inner_bottom = (int)(D_L00_001B25E0[0] * 177.0f + 0.5f);
        inner_top += g_is_pal_video[0] ? 4 : 0; inner_bottom += g_is_pal_video[0] ? 4 : 0;
        DrawFramebufferRect(103, inner_top, 155, inner_bottom, g_screen_width[0], g_screen_height[0], 0x80442D00);
    }
    x = *(int *)(model + 0x6C) - 63;
    for (relative = -3; relative < 5; relative++, x += 56) {
        loop_model = g_purchase_menu_model;
        slot = relative + *(int *)(loop_model + 0x80);
        if (slot < 0) continue;
        if (slot >= *(int *)(loop_model + 0x740)) continue;
        tint = 0xF0F0B0;
        handle = GetIconFrame(*(int *)(g_purchase_menu_model + 0x140 + slot * 12), 0);
        distance = __extendsfdf2(150.0f - (float)(x + 2));
        if (__cmpdf2(distance, 0.0) < 0) distance = __subdf3(0.0, distance);
        first_alpha = 128 - __fixdfsi(distance);
        distance = __extendsfdf2(150.0f - (float)(x + 40));
        if (__cmpdf2(distance, 0.0) < 0) distance = __subdf3(0.0, distance);
        second_alpha = 128 - __fixdfsi(distance);
        if (first_alpha < 0) first_alpha = 0;
        if (second_alpha < 0) second_alpha = 0;
        first_alpha <<= 24;
        second_alpha <<= 24;
        colors[1] = second_alpha | tint;
        colors[0] = first_alpha | tint;
        colors[3] = second_alpha | tint;
        colors[2] = first_alpha | tint;
        y = (int)(D_L00_001B25E0[0] * 129.0f + 0.5f);
        y += g_is_pal_video[0] ? 4 : 0;
        hud_draw_sprite_gradient(handle, x + 2, y, 40, (int)(D_L00_001B25E0[0] * 40.0f + 0.5f), colors);
    }
}
