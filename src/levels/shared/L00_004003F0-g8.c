#include "common.h"
extern int D_L00_001B0CA0 __attribute__((sda));
extern int D_001A904C[] __attribute__((sda));
extern float D_L00_001B2704[] __attribute__((sda));
extern int D_L00_001B2C10[] __attribute__((sda));
extern char D_L00_001B0CB8[];
extern void *table_find_by_id(int, int);
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern int math_split_time_into_parts(int, int *, int *, int *);
extern int sprintf(char *, char *, ...);
extern int FloatToInt(float);
extern void text_draw_medium(int, int, unsigned long, char *, int);

/* The display mode word beside the HUD scale. */
extern int D_L00_001B2700[] __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real: its load and compare go at flow2,
   after allocation, which leaves the saved but unused register (as func_L11_004456A0). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L00_001B2700[0] == active)
        scaled = 1.0f;
    return result;
}

/* Draws the HUD timer: two labels from the text table, then the time split into three
   fields, formatted and drawn centred, scaled by the HUD scale. */
/* Draws the Turret Spider Bot countdown timer on the screen. */
int spider_bot_draw_timer(void)
{
    char text[64];
    int a, b, c;
    int id, y, one, entry;
    float half;
    float ox, sc, z, w;

    if (D_L00_001B0CA0 == 0)
        return 1;
    w = 380.0f;
    half = 0.5f;
    one = 1;
    entry = 0x8710;
    id = table_find_by_id(D_001A904C[0] + entry, 0xC1);
    y = hud_coord(w, D_L00_001B2704[0], half, one);
    ox = -0.5f;
    sc = 1.0f;
    gfx_draw_scaled_object_two_axes(id, 0x60442D00, 454.0f, (float)y, ox, sc, z = 0.0f);
    id = table_find_by_id(D_001A904C[0] + entry, 0xC2);
    y = hud_coord(w, D_L00_001B2704[0], half, one);
    gfx_draw_scaled_object_two_axes(id, 0x55F0C070, 454.0f, (float)y, ox, sc, z);
    math_split_time_into_parts(D_L00_001B2C10[0], &a, &b, &c);
    sprintf(text, D_L00_001B0CB8, a, b, c);
    text_draw_medium(FloatToInt(405.0f), hud_coord(372.0f, D_L00_001B2704[0], half, one),
                  0x80808080UL, text, 128);
    return 1;
}
