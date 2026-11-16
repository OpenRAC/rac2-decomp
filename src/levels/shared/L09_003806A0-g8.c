#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { float u, v; } ScrollLayer;
#define I32(p, o) (*(int *)((p) + (o)))
#define F32(p, o) (*(float *)((p) + (o)))
#define S16(p, o) (*(short *)((p) + (o)))

extern u8 g_hero_state[], g_hero_position[];
extern float g_frame_delta_scale;
extern int g_dobbo_limits[];
extern Quad g_water_sheet_prev_pos SDATA(D_L09_001B3100);
extern u8 g_camera_l09_position[];
extern u8 *g_dobbo_point_table;
extern ScrollLayer g_water_layer_uv_offsets[] MACRO_ADDR;
extern float g_water_sheet_uv_scales[] SDATA(D_L09_001AEC38);
extern float g_water_sheet_u_speeds[] SDATA(D_L09_001AEC48);
extern float g_water_sheet_v_speeds[] MACRO_ADDR;
extern float g_water_sheet_z MACRO_ADDR;
extern float g_water_sheet_base_z MACRO_ADDR;
extern int g_frame_l09_counter;

extern int IsPointInCuboid(void *, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int FloatToInt(float);
extern float IntToFloat(int), math_fast_sin_or_cos_b(float);
extern void water_sheet_draw(void *);
extern void gfx_add_draw_callback_second(void (*)(void *), void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);

/* Per-frame update of the water sheet object: scrolls the water textures with the hero movement, bobs the water height with a wave, and queues the water draw. */
void water_sheet_update(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float delta[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    int i, index;
    int found;
    int *scan;

    if (g_dobbo_limits[0] != I32(state, 0x30))
        return;
    if (object[0x20] == 0) {
        object[0x20] = 1;
        object[0x30] = 255;
        {
            for (i = 0; i < 2; i++) {
                g_water_layer_uv_offsets[i].u = 0.0f;
                g_water_layer_uv_offsets[i].v = 0.0f;
            }
        }
        qcopy(&g_water_sheet_prev_pos, g_camera_l09_position);
        g_water_sheet_base_z = F32(state, 0x14);
        return;
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (I32(state, 0x40 + i * 4) == -1)
            continue;
        if (IsPointInCuboid(g_hero_position, I32(state, 0x40 + i * 4))) {
            { u8 *h = g_hero_state; S16(h, 0x1FE) = 0; }
            found = 1;
            break;
        }
    }
    if (found)
        return;
    g_water_sheet_base_z = F32(state, 0x14);
    scan = (int *)(state + 0x50);
    for (i = 0; i < 4; i++) {
        if (scan[i] == -1)
            continue;
        if (IsPointInCuboid(g_hero_position, scan[i])) {
            g_water_sheet_base_z = F32(g_dobbo_point_table + scan[i] * 128, 0x38) + 0.15f;
            break;
        }
    }
    { u8 *h = g_hero_state; S16(h, 0x1FE) = 2; }
    FastVecSub(delta, g_camera_l09_position, &g_water_sheet_prev_pos);
    qcopy(&g_water_sheet_prev_pos, g_camera_l09_position);
    if (!(F32(state, 0x20) < F32(g_camera_l09_position, 8)))
        return;

    for (i = 0; i < 2; i++) {
        float numerator = g_water_sheet_uv_scales[i] + g_water_sheet_uv_scales[i];
        float denominator = F32(state, 0x18) * 5.0f;
        float scale = numerator / denominator;
        FastVecScale(scaled, delta, scale);
        /* Preserve the ordered comparisons, including the exact-1 and NaN paths. */
        if (1.0f < scaled[0] || scaled[0] < 1.0f)
            scaled[0] -= IntToFloat(FloatToInt(scaled[0]));
        if (1.0f < scaled[1] || scaled[1] < 1.0f)
            scaled[1] -= IntToFloat(FloatToInt(scaled[1]));
        g_water_layer_uv_offsets[i].u += scaled[0];
        g_water_layer_uv_offsets[i].v += scaled[1];
        if (1.0f < g_water_layer_uv_offsets[i].u)
            g_water_layer_uv_offsets[i].u -= 1.0f;
        if (g_water_layer_uv_offsets[i].u < -1.0f)
            g_water_layer_uv_offsets[i].u += 1.0f;
        if (1.0f < g_water_layer_uv_offsets[i].v)
            g_water_layer_uv_offsets[i].v -= 1.0f;
        if (g_water_layer_uv_offsets[i].v < -1.0f)
            g_water_layer_uv_offsets[i].v += 1.0f;
    }
    g_water_sheet_z = g_water_sheet_base_z +
        math_fast_sin_or_cos_b(IntToFloat(g_frame_l09_counter % 360) *
                     0.017444444820284843f - 3.140000104904175f) * F32(state, 0x34);
    for (i = 0; i < 2; i++) {
        g_water_layer_uv_offsets[i].u += g_water_sheet_u_speeds[i * 2] * g_frame_delta_scale;
        if (1.0f < g_water_layer_uv_offsets[i].u)
            g_water_layer_uv_offsets[i].u -= 1.0f;
        if (g_water_layer_uv_offsets[i].u < -1.0f)
            g_water_layer_uv_offsets[i].u += 1.0f;
        g_water_layer_uv_offsets[i].v += g_water_sheet_v_speeds[i * 2] * g_frame_delta_scale;
        if (1.0f < g_water_layer_uv_offsets[i].v)
            g_water_layer_uv_offsets[i].v -= 1.0f;
        if (g_water_layer_uv_offsets[i].v < -1.0f)
            g_water_layer_uv_offsets[i].v += 1.0f;
    }
    if (I32(state, 0x38))
        gfx_add_draw_callback_second(water_sheet_draw, object);
    else
        gfx_add_draw_callback_first(water_sheet_draw, object);
}
