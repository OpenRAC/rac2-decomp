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

/* Moves a hovering object: eases its speed toward the hero-driven input and adds swaying and bobbing (PAL). */
void hovering_object_update_motion_pal(char *moby)
{
    float step_rate[4], base_speed[4], target_speed[4], input_vec[4], basis_matrix[16], hero_delta[4];
    float speed_scale, angle;
    int active, i;
    char *state = *(char **)(moby + 0x68);

    qcopy(moby + 0x10, state + 0x1b0);
    memset(input_vec, 0, 12);
    speed_scale = 1.0f;
    active = 0;
    if (g_hero_state.ptr[0x33c / 4] == moby && g_hero_state.i[0x340 / 4]) {
        active = 1;
        if (g_hero_state.i[0x340 / 4] == 1) {
            speed_scale = g_hover_motion_scale;
            *(int *)(state + 0x1d0) = 0;
            *(int *)(state + 0x1d4) = 0;
            *(int *)(state + 0x1d8) = 0;
        }
        matrix_from_basis_rows(basis_matrix, moby + 0xc0);
        FastVecSub(hero_delta, g_hero_state.b + 0x80, moby + 0x10);
        matrix_mul_vec3(hero_delta, hero_delta, basis_matrix);
        input_vec[0] += -hero_delta[1] * 0.333f;
        input_vec[1] += hero_delta[0] * 1.5f;
    }
    for (i = 0; i < 2; i++) {
        base_speed[i] = g_hover_base_speed_scale[i] * ((math_fabs(input_vec[i]) + 1.0f) * 0.00040000002f);
        step_rate[i] = base_speed[i] * speed_scale;
        target_speed[i] = active ? g_hover_input_speed_scale[i] * input_vec[i] : 0;
        math_step_value_toward_target(state + 0x1c4 + i * 4, state + 0x1d0 + i * 4, target_speed[i], step_rate[i], base_speed[i], 0.1f);
    }
    base_speed[2] = g_hover_base_z_speed[0] * 0.00040000002f;
    step_rate[2] = base_speed[2] * speed_scale;
    target_speed[2] = active ? g_hover_desired_z_speed[0] : 0;
    math_step_value_toward_target(state + 0x1cc, state + 0x1d8, target_speed[2], step_rate[2], base_speed[2], 0.1f);
    *(float *)(moby + 0xf0) = *(float *)(state + 0x1c4);
    *(float *)(moby + 0xf4) = *(float *)(state + 0x1c8);
    *(float *)(moby + 0x18) += *(float *)(state + 0x1cc);
    angle = FastAddRotations(*(float *)(state + 0x1a8), g_hover_phase_rate_a * 0.0003490659f);
    *(float *)(state + 0x1a8) = angle;
    *(float *)(moby + 0xf0) += g_hover_sway_amp_x * (math_fast_sin_or_cos_b(angle) * 0.017453294f);
    angle = FastAddRotations(*(float *)(state + 0x1ac), g_hover_phase_rate_b[0] * 0.0003490659f);
    *(float *)(state + 0x1ac) = angle;
    *(float *)(moby + 0xf4) += g_hover_sway_amp_y[0] * (math_fast_sin_or_cos_b(angle) * 0.017453294f);
    angle = FastAddRotations(*(float *)(state + 0x1c0), g_hover_phase_rate_c[0] * 0.0003490659f);
    *(float *)(state + 0x1c0) = angle;
    *(float *)(moby + 0x18) += g_hover_bob_amp_z[0] * math_fast_sin_or_cos_b(angle);
}
