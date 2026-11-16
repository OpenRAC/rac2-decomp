#include "common.h"

/* func_US2_00339B00, the USA v2.00 copy of func_00338AD8: the same bordered panel, where the
   text offset comes from a table indexed by the panel's mode (0x1C4), and the text is drawn
   with the float wrapper at the scale func_US2_003396E8 gives that mode.
   Retail builds the table's base through $gp and the address of its y field through lui/addiu,
   so the one table has two names: the SDATA view for x, the absolute name for y. */
typedef struct { float x, y; } BorderOffset_00338AD8;
typedef struct { int x, y; } TextOffset_00338AD8;
extern BorderOffset_00338AD8 ref_00338AD8_00;
extern BorderOffset_00338AD8 ref_00338AD8_01;
extern TextOffset_00338AD8 ref_00338AD8_02[] __attribute__((sda));
extern TextOffset_00338AD8 ref_00338AD8_02_gp[] SDATA(ref_00338AD8_02);
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_second_float4(void *, float, float, float, float);
extern void gfx_draw_screen_element_stored(void *);
extern void text_draw_small_scaled_us2(float, float, u64, u8 *, int, float);
extern float text_panel_get_scale_us2(void *, int);

void text_panel_draw_us2(char *object)
{
    unsigned int colours[4];
    BorderOffset_00338AD8 corner_offset;
    BorderOffset_00338AD8 edge_offset;
    float x, y;
    int i = 0, text_x, text_y;
    char *corner_widget = object + 0x10;
    char *edge_widget = object + 0x5c;
    colours[0] = **(unsigned int **)(object + 8);
    colours[1] = colours[0];
    colours[2] = colours[0];
    colours[3] = colours[0];
    gfx_draw_screen_rectangle((int)((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)),
                 (int)((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)),
                 (int)((*(float **)object)[0] + (float)*(int *)(object + 0x1a8)),
                 (int)((*(float **)object)[1] + (float)*(int *)(object + 0x1ac)), 0xfffff0, colours);
    corner_offset = ref_00338AD8_00;
    edge_offset = ref_00338AD8_01;
    object_set_first_float4(corner_widget, ((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - corner_offset.x,
                      ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - corner_offset.y, 0.0f, 0.0f);
    object_set_second_float4(corner_widget, -1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(corner_widget);
    object_set_first_float4(corner_widget, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + corner_offset.x + 1.0f,
                      ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - corner_offset.y, 0.0f, 0.0f);
    object_set_second_float4(corner_widget, 1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(corner_widget);
    object_set_first_float4(edge_widget, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + edge_offset.x,
                       ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge_offset.y, 0.0f, 0.0f);
    object_set_second_float4(edge_widget, 1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edge_widget);
    object_set_first_float4(edge_widget, ((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - edge_offset.x + 1.0f,
                       ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge_offset.y, 0.0f, 0.0f);
    object_set_second_float4(edge_widget, -1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edge_widget);
    object_set_first_float4(edge_widget, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + edge_offset.x,
                       (((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge_offset.y) + *(float *)(object + 0x1d0), 0.0f, 0.0f);
    object_set_second_float4(edge_widget, 1.0f, -1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edge_widget);
    object_set_first_float4(edge_widget, (((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - edge_offset.x) + 1.0f,
                       (((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge_offset.y) + *(float *)(object + 0x1d0), 0.0f, 0.0f);
    object_set_second_float4(edge_widget, -1.0f, -1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(edge_widget);
    x = (*(float **)object)[0];
    y = (*(float **)object)[1];
    text_x = (int)((x - (float)*(int *)(object + 0x1a8)) + (float)*(int *)(object + 0x1bc));
    text_y = (int)(y - (float)*(int *)(object + 0x1ac));
    if (*(int *)(object + 0x1d8)) {
        for (; i < *(int *)(object + 0x1b0); i++) {
            int text_mode = *(int *)(object + 0x1c4);
            text_draw_small_scaled_us2((float)(text_x + ref_00338AD8_02_gp[text_mode].x),
                              (float)(text_y + ref_00338AD8_02[text_mode].y + i * 16),
                              **(unsigned int **)(object + 12), ((u8 **)(object + 0x1d8))[i], -1,
                              text_panel_get_scale_us2(object, text_mode));
        }
    }
}
