#include "common.h"
extern int g_hud_timer_b_state __attribute__((sda));
extern int g_resident_data_base[] __attribute__((sda));
extern float g_hud_scale[] __attribute__((sda));
extern int g_hud_timer_b[] __attribute__((sda));
extern char g_str_hud_timer_b_format[];
extern void *table_find_by_id(int, int);
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern int math_split_time_into_parts(int, int *, int *, int *);
extern int sprintf(char *, char *, ...);
extern int FloatToInt(float);
extern void text_draw_medium(int, int, unsigned long, char *, int);

/* The display mode word beside the HUD scale. */
extern int g_hud_mode[] __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel. The display-mode
   test has no effect on the result, but it is real: its load and compare go at flow2,
   after allocation, which leaves the saved but unused register (as func_L11_004456A0). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && g_hud_mode[0] == active)
        scaled = 1.0f;
    return result;
}

/* Draws the HUD timer: two labels from the text table, then the time split into three
   fields, formatted and drawn centred, scaled by the HUD scale. */
int hud_draw_timer_b(void)
{
    char text[64];
    int field0, field1, field2;
    int label_id, label_y, one, table_offset;
    float half;
    float ox, sc, z, label_base_y;

    if (g_hud_timer_b_state == 0)
        return 1;
    label_base_y = 380.0f;
    half = 0.5f;
    one = 1;
    table_offset = 0x8710;
    label_id = table_find_by_id(g_resident_data_base[0] + table_offset, 0xC1);
    label_y = hud_coord(label_base_y, g_hud_scale[0], half, one);
    ox = -0.5f;
    sc = 1.0f;
    gfx_draw_scaled_object_two_axes(label_id, 0x60442D00, 454.0f, (float)label_y, ox, sc, z = 0.0f);
    label_id = table_find_by_id(g_resident_data_base[0] + table_offset, 0xC2);
    label_y = hud_coord(label_base_y, g_hud_scale[0], half, one);
    gfx_draw_scaled_object_two_axes(label_id, 0x55F0C070, 454.0f, (float)label_y, ox, sc, z);
    math_split_time_into_parts(g_hud_timer_b[0], &field0, &field1, &field2);
    sprintf(text, g_str_hud_timer_b_format, field0, field1, field2);
    text_draw_medium(FloatToInt(405.0f), hud_coord(372.0f, g_hud_scale[0], half, one),
                  0x80808080UL, text, 128);
    return 1;
}
