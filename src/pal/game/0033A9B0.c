#include "include_asm.h"
#include "common.h"

/* func_PAL_0033A9B0, the PAL copy of func_00338AD8: the same panel, where the text lines are drawn
   in every mode (USA only in mode 1), at the offsets of the panel's mode, with the scaled text call
   and the scale of func_PAL_0033A598.
   Bordered text panel: background box, six border pieces, then the text lines.
   The border offsets are per-program records (ref_ names); 0x1D0 is a float field.
   Retail reaches the offset table's x column through $gp and its y column as an absolute address,
   so the table has two names, as in other mixed GP/absolute accesses (docs/build/compiler-notes.md). */
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
extern float text_panel_mode_scale_pal(void *, int);
extern void text_draw_small_scaled(float, float, long, signed char *, int, float);

/* Draws the bordered text panel: background box, border pieces, then the text lines (PAL version). */
void text_panel_draw_pal(char *object)
{
    unsigned int colors[4];
    BorderOffset_00338AD8 corner;
    BorderOffset_00338AD8 edge;
    float x, y;
    int i = 0, text_x, text_y;
    char *top = object + 0x10;
    char *side = object + 0x5c;
    colors[0] = **(unsigned int **)(object + 8);
    colors[1] = colors[0];
    colors[2] = colors[0];
    colors[3] = colors[0];
    gfx_draw_screen_rectangle((int)((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)),
                 (int)((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)),
                 (int)((*(float **)object)[0] + (float)*(int *)(object + 0x1a8)),
                 (int)((*(float **)object)[1] + (float)*(int *)(object + 0x1ac)), 0xfffff0, colors);
    corner = ref_00338AD8_00;
    edge = ref_00338AD8_01;
    object_set_first_float4(top, ((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - corner.x,
                      ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - corner.y, 0.0f, 0.0f);
    object_set_second_float4(top, -1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(top);
    object_set_first_float4(top, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + corner.x + 1.0f,
                      ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - corner.y, 0.0f, 0.0f);
    object_set_second_float4(top, 1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(top);
    object_set_first_float4(side, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + edge.x,
                       ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y, 0.0f, 0.0f);
    object_set_second_float4(side, 1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(side);
    object_set_first_float4(side, ((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - edge.x + 1.0f,
                       ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y, 0.0f, 0.0f);
    object_set_second_float4(side, -1.0f, 1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(side);
    object_set_first_float4(side, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + edge.x,
                       (((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y) + *(float *)(object + 0x1d0), 0.0f, 0.0f);
    object_set_second_float4(side, 1.0f, -1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(side);
    object_set_first_float4(side, (((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - edge.x) + 1.0f,
                       (((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y) + *(float *)(object + 0x1d0), 0.0f, 0.0f);
    object_set_second_float4(side, -1.0f, -1.0f, 0.0f, 0.0f);
    gfx_draw_screen_element_stored(side);
    x = (*(float **)object)[0];
    y = (*(float **)object)[1];
    text_x = (int)((x - (float)*(int *)(object + 0x1a8)) + (float)*(int *)(object + 0x1bc));
    text_y = (int)(y - (float)*(int *)(object + 0x1ac));
    if (*(int *)(object + 0x1d8)) {
        for (; i < *(int *)(object + 0x1b0); i++) {
            int mode = *(int *)(object + 0x1c4);
            text_draw_small_scaled((float)(text_x + ref_00338AD8_02_gp[mode].x),
                              (float)(text_y + ref_00338AD8_02[mode].y + i * 16),
                              **(unsigned int **)(object + 12), ((signed char **)(object + 0x1d8))[i], -1,
                              text_panel_mode_scale_pal(object, mode));
        }
    }
}
