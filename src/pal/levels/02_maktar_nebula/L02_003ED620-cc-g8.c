#include "names.h"
/* func_PAL_L02_003ED620, the PAL copy of func_L02_003E91F0: the same C, where wrap D_L02_001B0CAC (({e}) * 1.2f). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float g_tether_strand_length __attribute__((sda));
extern float g_tether_height_phase_spacing __attribute__((sda)), g_tether_height_min __attribute__((sda)), g_tether_height_max __attribute__((sda));
extern float g_tether_l02_height_phase __attribute__((sda)), g_tether_l02_height_phase_speed __attribute__((sda));
extern float g_tether_lateral_phase __attribute__((sda)), g_tether_lateral_phase_speed __attribute__((sda));
extern float g_tether_lateral_phase_spacing __attribute__((sda)), g_tether_height_amplitude __attribute__((sda)), g_tether_lateral_amplitude __attribute__((sda));
extern float g_tether_l02_wave_phase_2 __attribute__((sda)), g_tether_l02_wave_phase_speed __attribute__((sda)), g_tether_wave_phase_spacing __attribute__((sda));
extern float g_tether_height_noise_min __attribute__((sda)), g_tether_height_noise_max __attribute__((sda));
extern float g_tether_toward_scale __attribute__((sda));
extern int g_tether_l02_ground_effect_color __attribute__((sda));
extern float g_tether_strand_points[2][20][4];
extern float g_tether_strand_prev_heights[20], g_tether_strand_sideways[20][4], g_tether_strand_heights[20];
typedef union { char b[0x2600]; float f[0x980]; Quad q[0x260]; } Hero;
extern char g_hero_state[];
extern char g_zero_l02_vector[] __attribute__((sda));
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern char *moby_get_private_value_0(void *);
extern float fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float IntToFloat(int), math_wrap_angle_to_pi(float), math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float), math_random_signed_float_range(float, float);
extern void lerp_vector(void *, void *, void *, float);
extern float FastVecLength(void *);
extern void FastVecAdd(void *, void *, void *);
extern float mat_fast_helper_a(float, float), math_random_float_range(float, float);
extern int math_random_int_range(int, int), math_random_int_below(int);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
typedef struct {
    char pad[0x20];
    float start[4];
    float end[4];
    char gap[0x0C];
    char *target;
    int count;
} TetherState;
/* Relaxes and animates a pair of twenty-point tether strands, then emits sparks. */
void tether_animate_strands_pal(char *moby) {
    TetherState *state = *(TetherState **)(moby + 0x68);
    float endpoint[4], direction[4], delta[4], blended[4], tangent[4], sideways[4], toward[4];
    float length = g_tether_strand_length * 0.05f;
    float phase, span, distance, oscillation, lateral, radius;
    int spin;
    g_tether_l02_height_phase = FastAddRotations(g_tether_l02_height_phase, g_tether_l02_height_phase_speed);
    g_tether_lateral_phase = fast_subtract_rotations(g_tether_lateral_phase, g_tether_lateral_phase_speed);
    g_tether_l02_wave_phase_2 = FastAddRotations(g_tether_l02_wave_phase_2, g_tether_l02_wave_phase_speed);
    if (state->target) {
        char *settings = (char *)moby_get_private_value_0(state->target);
        qcopy(endpoint, state->target + 0x10);
        endpoint[2] += *(float *)(settings + 0x10);
        length = fast_vec_dist(state->start, endpoint) * 0.05f;
    }
    state->count = 20;
    FastVecSub(direction, state->end, state->start);
    vec_scale_to_length(direction, direction, 1.0f);
    if (state->target) {
        FastVecCross(delta, direction, &((Hero *)g_hero_state)->q[0x2C0 / 16]);
        math_apply_axis_rotation_to_quat(direction, direction, delta, 0.17453295f);
    }
    FastVecScale(tangent, direction, length);
    qcopy(g_tether_strand_points[0][0], state->start);
    qcopy(g_tether_strand_points[1][0], state->start);
    {
    /* i is declared here, after the setup code: its later pseudo number sets the gcse order of the spilled state->start/state->end/i*4 copies. */
    int i;
    for (i = 1; i < 20; i++) {
        float lateral_angle, height, zero;
        float *strand_point;
        height = IntToFloat(i);
        height = g_tether_height_min + (g_tether_height_max - g_tether_height_min) * (height * 0.05f);
        height *= math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l02_height_phase + (float)i * g_tether_height_phase_spacing));
        height += math_random_signed_float_range(g_tether_height_noise_min, g_tether_height_noise_max);
        g_tether_strand_points[0][i][2] -= g_tether_strand_prev_heights[i];
        g_tether_strand_prev_heights[i] = height;
        FastVecSub(delta, g_tether_strand_points[0][i], g_tether_strand_points[0][i - 1]);
        lerp_vector(blended, delta, tangent, 0.85f);
        span = FastVecLength(blended);
        zero = 0.0f;
        if (span == zero) qcopy(g_tether_strand_points[0][i], g_tether_strand_points[0][i - 1]);
        else {
            FastVecScale(blended, blended, length / span);
            FastVecAdd(g_tether_strand_points[0][i], g_tether_strand_points[0][i - 1], blended);
            qcopy(tangent, blended);
        }
        g_tether_strand_points[0][i][2] += height;
        FastVecSub(delta, g_tether_strand_points[0][i], g_tether_strand_points[0][i - 1]);
        if (state->target) {
            FastVecSub(toward, endpoint, g_tether_strand_points[0][i]);
            distance = FastVecLength(toward);
            if (distance != zero) {
                if (i == 19) { length = distance; height = 0.5f; }
                else if (i >= 16) {
                    float remaining = IntToFloat(19 - i);
                    height = 0.5f;
                    length = distance / remaining;
                }
                else height = 0.1f;
                FastVecScale(toward, toward, length / distance);
                lerp_vector(tangent, tangent, toward, height);
            }
        }
        lateral_angle = math_wrap_angle_to_pi(g_tether_lateral_phase + (float)i * g_tether_lateral_phase_spacing);
        oscillation = math_wrap_angle_to_pi(g_tether_l02_wave_phase_2 + (float)i * g_tether_wave_phase_spacing);
        height = g_tether_height_amplitude * math_fast_sin_or_cos_b(oscillation);
        qcopy(g_tether_strand_points[1][i], g_tether_strand_points[0][i]);
        height *= math_fast_sin_or_cos_b(lateral_angle);
        g_tether_strand_heights[i] = height;
        strand_point = g_tether_strand_points[0][i];
        strand_point[82] += height;
        height = FastAddRotations(mat_fast_helper_a(delta[0], delta[1]), 1.5707965f);
        lateral = g_tether_lateral_amplitude * math_fast_sin_or_cos_a(lateral_angle);
        sideways[0] = math_fast_sin_or_cos_a(height) * lateral;
        sideways[1] = math_fast_sin_or_cos_b(height) * lateral;
        sideways[2] = 0;
        qcopy(g_tether_strand_sideways[i], sideways);
        FastVecAdd(g_tether_strand_points[1][i], g_tether_strand_points[1][i], sideways);
    }
    }
    qcopy(state->end, g_tether_strand_points[0][19]);
    oscillation = math_random_signed_float_range(0.52359885f, 1.0471977f);
    phase = math_random_float_range(-0.52359885f, 1.0471977f);
    FastVecScale(toward, direction, ((g_tether_toward_scale) * 1.2f));
    math_apply_axis_rotation_to_quat(toward, toward, &((Hero *)g_hero_state)->q[0x740 / 16], phase);
    math_apply_axis_rotation_to_quat(toward, toward, &((Hero *)g_hero_state)->q[0x750 / 16], oscillation);
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2)) spin = -spin;
    radius = math_random_float_range(0.2f, 0.6f);
    part_spawn_ground_effect(state->start, 12, radius * 0.3f, radius, g_tether_l02_ground_effect_color | 0x7F000000, 0, spin, toward, 0, 0.0f);
    part_spawn_ground_effect(state->start, 12, radius * 0.15f, radius * 0.5f, 0x307F7F7F, 0, -spin, toward, 0, 0.0f);
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2)) spin = -spin;
    radius = math_random_float_range(0.15f, 3.0f);
    part_spawn_ground_effect(state->end, 10, radius * 0.1f, radius, g_tether_l02_ground_effect_color | 0x7F000000, 0, spin, g_zero_l02_vector, 0, 0.0f);
}
