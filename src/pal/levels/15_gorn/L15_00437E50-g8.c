#include "include_asm.h"

#include "common.h"
typedef int GornQuad __attribute__((mode(TI)));
typedef union { GornQuad q; float f[4]; } GornVector;
extern short g_part_channel_timers[] MACRO_ADDR, g_part_channel_counters[] MACRO_ADDR, g_part_channel_reload_values[] MACRO_ADDR;
extern GornVector g_part_channel_points[4][10] NOT_SDA;
extern float g_gorn_effect_jitter_small __attribute__((sda)), g_gorn_effect_jitter_large __attribute__((sda)), g_gorn_effect_tangent_length __attribute__((sda));
extern int FastDecTimer(short *);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void math_l00_interpolate_cubic_vector(void *, void *, void *, void *, void *, float);

/* For each of four channels whose timer expired: rearms it and rebuilds its jittered ten-point curves. */
void gorn_channel_curves_rebuild_pal(void *moby)
{
    GornVector origin, tangent, point;
    char *state = *(char **)((char *)moby + 0x68);
    int channel;
    for (channel = 0; channel < 4; channel++) {
        if (!FastDecTimer(&g_part_channel_timers[channel]))
            continue;
        g_part_channel_counters[channel] = 0;
        g_part_channel_timers[channel] = ((s32)(g_part_channel_reload_values[channel]) * 5 + 2) / 6;
        qcopy(&origin, state + 0x10);
        origin.f[0] += math_random_float_range(-30, 30);
        origin.f[1] += math_random_float_range(-30, 30);
        origin.f[2] += math_random_float_range(-30, 30);
        qcopy(state + 0x20, state + 0x10);
        qcopy(state + 0x30, state + 0x10);
        qcopy(state + 0x40, state + 0x10);
        {
            float positive = 60.0f, negative = -60.0f;
            *(float *)(state + 0x20) += math_random_float_range(negative, positive);
            *(float *)(state + 0x24) += math_random_float_range(negative, positive);
            *(float *)(state + 0x28) += math_random_float_range(negative, positive);
            *(float *)(state + 0x30) += math_random_float_range(negative, positive);
            *(float *)(state + 0x34) += math_random_float_range(negative, positive);
            *(float *)(state + 0x38) += math_random_float_range(negative, positive);
            *(float *)(state + 0x40) += math_random_float_range(negative, positive);
            *(float *)(state + 0x44) += math_random_float_range(negative, positive);
            *(float *)(state + 0x48) += math_random_float_range(negative, positive);
        }
        FastVecSub(&tangent, &origin, state);
        vec_scale_to_length(&tangent, &tangent, g_gorn_effect_tangent_length);
        FastVecAdd(&tangent, &origin, &tangent);
        {
            int i;

            for (i = 0; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, &origin, &tangent, &tangent, t);
                qcopy(&g_part_channel_points[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &g_part_channel_points[0][i]);
                point.f[0] += math_random_signed_float_range(0, g_gorn_effect_jitter_small);
                point.f[1] += math_random_signed_float_range(0, g_gorn_effect_jitter_small);
                point.f[2] += math_random_signed_float_range(0, g_gorn_effect_jitter_small);
                qcopy(&g_part_channel_points[0][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &g_part_channel_points[0][i]);
                point.f[0] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                point.f[1] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                point.f[2] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                qcopy(&g_part_channel_points[1][i], &point);
            }
        }
        {
            int i;

            for (i = 3; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, state + 0x20, &tangent, &tangent, t);
                qcopy(&g_part_channel_points[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &g_part_channel_points[0][i]);
                point.f[0] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                point.f[1] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                point.f[2] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                qcopy(&g_part_channel_points[2][i], &point);
            }
        }
        {
            int i;

            for (i = 6; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, state + 0x30, &tangent, &tangent, t);
                qcopy(&g_part_channel_points[channel][i], &point);
            }
        }
        {
            int i;

            for (i = 1; i < 9; i++) {
                qcopy(&point, &g_part_channel_points[0][i]);
                point.f[0] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                point.f[1] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                point.f[2] += math_random_signed_float_range(0, g_gorn_effect_jitter_large);
                qcopy(&g_part_channel_points[3][i], &point);
            }
        }
        {
            int i;

            for (i = 8; i < 10; i++) {
                float t = i * 0.1f;
                if (i == 9) t = 1.0f;
                math_l00_interpolate_cubic_vector(&point, state, state + 0x40, &tangent, &tangent, t);
                qcopy(&g_part_channel_points[channel][i], &point);
            }
        }
    }
}
