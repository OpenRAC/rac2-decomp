#include "include_asm.h"

#include "common.h"
typedef union {
    char b[0x400];
    int i[0x100];
    char *ptr[0x100];
} L04_003EC140_Player;
extern L04_003EC140_Player g_hero_state;
extern void *memset(void *, int, int);
extern float math_fabs(float);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_from_basis_rows(void *, void *);
extern float FastAddRotations(float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern float g_hover_phase_rate_a __attribute__((sda));
extern float g_hover_phase_rate_b[] __attribute__((sda));
extern float g_hover_phase_rate_c[] __attribute__((sda));
extern float g_hover_sway_amp_x __attribute__((sda));
extern float g_hover_sway_amp_y[] __attribute__((sda));
extern float g_hover_bob_amp_z[] __attribute__((sda));
extern float g_hover_input_speed_scale[2] __attribute__((sda));
extern float g_hover_desired_z_speed[] __attribute__((sda));
extern float g_hover_base_speed_scale[2] __attribute__((sda));
extern float g_hover_base_z_speed[] __attribute__((sda));
extern float g_hover_motion_scale __attribute__((sda));

void hovering_object_update_motion_pal(char *o)
{
    float rate[4], base[4], desired[4], input[4], matrix[16], delta[4];
    float scale, angle;
    int active, i;
    char *p = *(char **)(o + 0x68);

    qcopy(o + 0x10, p + 0x1b0);
    memset(input, 0, 12);
    scale = 1.0f;
    active = 0;
    if (g_hero_state.ptr[0x33c / 4] == o && g_hero_state.i[0x340 / 4]) {
        active = 1;
        if (g_hero_state.i[0x340 / 4] == 1) {
            scale = g_hover_motion_scale;
            *(int *)(p + 0x1d0) = 0;
            *(int *)(p + 0x1d4) = 0;
            *(int *)(p + 0x1d8) = 0;
        }
        matrix_from_basis_rows(matrix, o + 0xc0);
        FastVecSub(delta, g_hero_state.b + 0x80, o + 0x10);
        matrix_mul_vec3(delta, delta, matrix);
        input[0] += -delta[1] * 0.333f;
        input[1] += delta[0] * 1.5f;
    }
    for (i = 0; i < 2; i++) {
        base[i] = g_hover_base_speed_scale[i] * ((math_fabs(input[i]) + 1.0f) * 0.00040000002f);
        rate[i] = base[i] * scale;
        desired[i] = active ? g_hover_input_speed_scale[i] * input[i] : 0;
        math_step_value_toward_target(p + 0x1c4 + i * 4, p + 0x1d0 + i * 4, desired[i], rate[i], base[i], 0.1f);
    }
    base[2] = g_hover_base_z_speed[0] * 0.00040000002f;
    rate[2] = base[2] * scale;
    desired[2] = active ? g_hover_desired_z_speed[0] : 0;
    math_step_value_toward_target(p + 0x1cc, p + 0x1d8, desired[2], rate[2], base[2], 0.1f);
    *(float *)(o + 0xf0) = *(float *)(p + 0x1c4);
    *(float *)(o + 0xf4) = *(float *)(p + 0x1c8);
    *(float *)(o + 0x18) += *(float *)(p + 0x1cc);
    angle = FastAddRotations(*(float *)(p + 0x1a8), g_hover_phase_rate_a * 0.0003490659f);
    *(float *)(p + 0x1a8) = angle;
    *(float *)(o + 0xf0) += g_hover_sway_amp_x * (math_fast_sin_or_cos_b(angle) * 0.017453294f);
    angle = FastAddRotations(*(float *)(p + 0x1ac), g_hover_phase_rate_b[0] * 0.0003490659f);
    *(float *)(p + 0x1ac) = angle;
    *(float *)(o + 0xf4) += g_hover_sway_amp_y[0] * (math_fast_sin_or_cos_b(angle) * 0.017453294f);
    angle = FastAddRotations(*(float *)(p + 0x1c0), g_hover_phase_rate_c[0] * 0.0003490659f);
    *(float *)(p + 0x1c0) = angle;
    *(float *)(o + 0x18) += g_hover_bob_amp_z[0] * math_fast_sin_or_cos_b(angle);
}
