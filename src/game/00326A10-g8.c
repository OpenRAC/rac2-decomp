#include "common.h"
extern int D_001B00FC __attribute__((sda));
extern int D_001A8CFC[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
extern int D_001B27C0[] __attribute__((sda));
extern char D_001B0110[];
extern int table_find_by_id(int, int);
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern void math_split_time_into_parts(int, int *, int *, int *);
extern int sprintf(char *, char *, ...);
extern int FloatToInt(float);
extern void text_draw_medium(int, int, unsigned long, char *, int);

/* The display mode word beside the HUD scale. */
extern int D_001B23A0[] __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real: its load and compare go at flow2,
   after allocation, which leaves the saved but unused register (as func_L11_004456A0). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_001B23A0[0] == active)
        scaled = 1.0f;
    return result;
}

/* Draws the HUD timer: two labels from the text table, then the time split into three
   fields, formatted and drawn centred, scaled by the HUD scale. */
int hud_draw_timer_a(void)
{
    char text[64];
    int hours, minutes, seconds;
    int id, y, one, textOffset;
    float half;
    float ox, sc, z, baseY;

    if (D_001B00FC == 0)
        return 1;
    baseY = 380.0f;
    half = 0.5f;
    one = 1;
    textOffset = 0x8710;
    id = table_find_by_id(D_001A8CFC[0] + textOffset, 0xC1);
    y = hud_coord(baseY, D_001B23A4[0], half, one);
    ox = -0.5f;
    sc = 1.0f;
    gfx_draw_scaled_object_two_axes(id, 0x60442D00, 454.0f, (float)y, ox, sc, z = 0.0f);
    id = table_find_by_id(D_001A8CFC[0] + textOffset, 0xC2);
    y = hud_coord(baseY, D_001B23A4[0], half, one);
    gfx_draw_scaled_object_two_axes(id, 0x55F0C070, 454.0f, (float)y, ox, sc, z);
    math_split_time_into_parts(D_001B27C0[0], &hours, &minutes, &seconds);
    sprintf(text, D_001B0110, hours, minutes, seconds);
    text_draw_medium(FloatToInt(405.0f), hud_coord(372.0f, D_001B23A4[0], half, one),
                  0x80808080UL, text, 128);
    return 1;
}
