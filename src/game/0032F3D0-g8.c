#include "common.h"
extern int D_001B0960 __attribute__((sda));
extern int D_001A8CFC[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
extern int D_001B2840[] __attribute__((sda));
extern char D_001B0978[];
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
int hud_draw_timer_b(void)
{
    char text[64];
    int field0, field1, field2;
    int labelId, labelY, one, tableOffset;
    float half;
    float ox, sc, z, labelBaseY;

    if (D_001B0960 == 0)
        return 1;
    labelBaseY = 380.0f;
    half = 0.5f;
    one = 1;
    tableOffset = 0x8710;
    labelId = table_find_by_id(D_001A8CFC[0] + tableOffset, 0xC1);
    labelY = hud_coord(labelBaseY, D_001B23A4[0], half, one);
    ox = -0.5f;
    sc = 1.0f;
    gfx_draw_scaled_object_two_axes(labelId, 0x60442D00, 454.0f, (float)labelY, ox, sc, z = 0.0f);
    labelId = table_find_by_id(D_001A8CFC[0] + tableOffset, 0xC2);
    labelY = hud_coord(labelBaseY, D_001B23A4[0], half, one);
    gfx_draw_scaled_object_two_axes(labelId, 0x55F0C070, 454.0f, (float)labelY, ox, sc, z);
    math_split_time_into_parts(D_001B2840[0], &field0, &field1, &field2);
    sprintf(text, D_001B0978, field0, field1, field2);
    text_draw_medium(FloatToInt(405.0f), hud_coord(372.0f, D_001B23A4[0], half, one),
                  0x80808080UL, text, 128);
    return 1;
}
