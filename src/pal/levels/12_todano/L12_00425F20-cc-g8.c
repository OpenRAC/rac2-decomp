#include "names.h"
/* func_PAL_L12_00425F20, the PAL copy of func_L12_00420B78: the same C, where wrap data[5] (({e}) * 8.0f); lit 8.0f becomes 9.6f. */
#include "common.h"

extern float g_quad_random_min __attribute__((sda));
extern float g_quad_random_max __attribute__((sda));
extern int g_water_wave_state_id;
extern float g_water_wave_position[4] __attribute__((aligned(16), sda));
extern int g_frame_l12_counter[] __attribute__((sda));
extern u8 g_hero_position[];

/* 294 vertices, in strips of 21. */
extern float g_barrier_vertex_table[][4];
typedef struct {
    short vertex;
    short uv;
    short pad;
} L12Corner;

/* 223 quads. */
extern L12Corner g_barrier_corner_table[][4];

/* The 144-byte packet func_00281DE8 starts and func_00280B90 submits. */
extern int coll_point_inside_region(void *point, int index);
extern void gfx_add_draw_callback_first(void (*callback)(u8 *), void *object);
extern void gfx_add_draw_callback_third(void (*callback)(u8 *), void *object);
extern float math_fast_sin_or_cos_b(float angle);
extern float math_random_float_range(float low, float high);
extern float vec_distance_xy(void *a, void *b);

void DrawScrollingTwoPassQuadMesh(u8 *object);

void func_PAL_L12_00425F20(u8 *object)
{
    float *data = *(float **)(object + 0x68);
    int i;
    float angle;
    float a, b, c, d, e, f, g, h;

    switch (object[0x20]) {
    case 0:
        data[0] = 0.0f;
        data[1] = 0.25f;
        data[2] = 0.5f;
        data[3] = 0.75f;
        data[8] = 1.0f;
        data[9] = 1.25f;
        data[10] = 1.5f;
        data[11] = 1.75f;
        object[0x20] = 1;
        object[0x30] = 255;
        if (g_barrier_vertex_table[0][0] > 1000.0f) {
            for (i = 0; i < 294; i++) {
                g_barrier_vertex_table[i][0] *= 0.01f;
                g_barrier_vertex_table[i][1] *= 0.01f;
                g_barrier_vertex_table[i][2] *= 0.01f;
            }
        }
        break;
    case 1:
        if (coll_point_inside_region(g_hero_position, *(int *)(data + 6)))
            return;
        gfx_add_draw_callback_first(DrawScrollingTwoPassQuadMesh, object);
        g_water_wave_state_id = 1;
        qcopy(g_water_wave_position, g_hero_position);
        g_water_wave_position[3] = 48.0f;
        *(short *)(g_hero_position + 0x17e) = 5;
        angle = (float)(g_frame_l12_counter[0] % 360) * 0.017444444820284843f - 3.140000104904175f;
        g_water_wave_position[2] = math_fast_sin_or_cos_b(angle) * 0.25f + 59.5f;
        data[4] += ((data[5]) * 1.2f);
        if (data[4] >= 8.0f)
            data[4] -= 8.0f;
        a = math_fast_sin_or_cos_b(data[0] * 3.141590118408203f) * 0.001f;
        b = math_fast_sin_or_cos_b(data[1] * 3.141590118408203f) * 0.001f;
        c = math_fast_sin_or_cos_b(data[2] * 3.141590118408203f) * 0.001f;
        d = math_fast_sin_or_cos_b(data[3] * 3.141590118408203f) * 0.001f;
        e = math_fast_sin_or_cos_b(data[0] * 3.141590118408203f) * 0.001f;
        f = math_fast_sin_or_cos_b(data[1] * 3.141590118408203f) * 0.001f;
        g = math_fast_sin_or_cos_b(data[2] * 3.141590118408203f) * 0.001f;
        h = math_fast_sin_or_cos_b(data[3] * 3.141590118408203f) * 0.001f;
        for (i = 0; i < 21; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += a;
        }
        for (i = 21; i < 42; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += b;
        }
        for (i = 42; i < 63; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += c;
        }
        for (i = 63; i < 84; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += d;
        }
        for (i = 84; i < 105; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += e;
        }
        for (i = 105; i < 126; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += f;
        }
        for (i = 126; i < 147; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += g;
        }
        for (i = 147; i < 168; i++) {
            float *p = g_barrier_vertex_table[i];

            p[2] += h;
        }
        data[0] += 0.01f;
        data[1] += 0.01f;
        data[2] += 0.01f;
        data[3] += 0.01f;
        data[8] += 0.01f;
        data[9] += 0.01f;
        data[10] += 0.01f;
        data[11] += 0.01f;
        if (data[0] > 2.0f) data[0] = 0;
        if (data[1] > 2.0f) data[1] = 0;
        if (data[2] > 2.0f) data[2] = 0;
        if (data[3] > 2.0f) data[3] = 0;
        data[5] = math_random_float_range(g_quad_random_min, g_quad_random_max);
        break;
    case 2:
        if (vec_distance_xy(object + 0x10, g_hero_position) < 64.0f)
            gfx_add_draw_callback_third(DrawScrollingTwoPassQuadMesh, object);
        break;
    }
}
