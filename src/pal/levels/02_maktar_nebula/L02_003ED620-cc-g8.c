/* func_PAL_L02_003ED620, the PAL copy of func_L02_003E91F0: the same C, where wrap D_L02_001B0CAC (({e}) * 1.2f). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float D_L02_001B0BA8 __attribute__((sda));
extern float D_L02_001B0C1C __attribute__((sda)), D_L02_001B0C20 __attribute__((sda)), D_L02_001B0C24 __attribute__((sda));
extern float D_L02_001B0C28 __attribute__((sda)), D_L02_001B0C2C __attribute__((sda));
extern float D_L02_001B0C30 __attribute__((sda)), D_L02_001B0C34 __attribute__((sda));
extern float D_L02_001B0C38 __attribute__((sda)), D_L02_001B0C3C __attribute__((sda)), D_L02_001B0C40 __attribute__((sda));
extern float D_L02_001B0C44 __attribute__((sda)), D_L02_001B0C48 __attribute__((sda)), D_L02_001B0C4C __attribute__((sda));
extern float D_L02_001B0C60 __attribute__((sda)), D_L02_001B0C64 __attribute__((sda));
extern float D_L02_001B0CAC __attribute__((sda));
extern int D_L02_001B0C7C __attribute__((sda));
extern float D_L02_00249090[2][20][4];
extern float D_L02_00249310[20], D_L02_00249360[20][4], D_L02_002494A0[20];
typedef union { char b[0x2600]; float f[0x980]; Quad q[0x260]; } Hero;
extern char g_hero_state[];
extern char D_L02_001A8F20[] __attribute__((sda));
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
void func_PAL_L02_003ED620(char *actor) {
    TetherState *state = *(TetherState **)(actor + 0x68);
    float endpoint[4], direction[4], delta[4], blended[4], tangent[4], sideways[4], toward[4];
    float length = D_L02_001B0BA8 * 0.05f;
    float phase, span, distance, oscillation, lateral, radius;
    int spin;
    D_L02_001B0C28 = FastAddRotations(D_L02_001B0C28, D_L02_001B0C2C);
    D_L02_001B0C30 = fast_subtract_rotations(D_L02_001B0C30, D_L02_001B0C34);
    D_L02_001B0C44 = FastAddRotations(D_L02_001B0C44, D_L02_001B0C48);
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
    qcopy(D_L02_00249090[0][0], state->start);
    qcopy(D_L02_00249090[1][0], state->start);
    {
    /* i is declared here, after the setup code: its later pseudo number sets the gcse order of the spilled state->start/state->end/i*4 copies. */
    int i;
    for (i = 1; i < 20; i++) {
        float value, height, zero;
        float *point;
        height = IntToFloat(i);
        height = D_L02_001B0C20 + (D_L02_001B0C24 - D_L02_001B0C20) * (height * 0.05f);
        height *= math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L02_001B0C28 + (float)i * D_L02_001B0C1C));
        height += math_random_signed_float_range(D_L02_001B0C60, D_L02_001B0C64);
        D_L02_00249090[0][i][2] -= D_L02_00249310[i];
        D_L02_00249310[i] = height;
        FastVecSub(delta, D_L02_00249090[0][i], D_L02_00249090[0][i - 1]);
        lerp_vector(blended, delta, tangent, 0.85f);
        span = FastVecLength(blended);
        zero = 0.0f;
        if (span == zero) qcopy(D_L02_00249090[0][i], D_L02_00249090[0][i - 1]);
        else {
            FastVecScale(blended, blended, length / span);
            FastVecAdd(D_L02_00249090[0][i], D_L02_00249090[0][i - 1], blended);
            qcopy(tangent, blended);
        }
        D_L02_00249090[0][i][2] += height;
        FastVecSub(delta, D_L02_00249090[0][i], D_L02_00249090[0][i - 1]);
        if (state->target) {
            FastVecSub(toward, endpoint, D_L02_00249090[0][i]);
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
        value = math_wrap_angle_to_pi(D_L02_001B0C30 + (float)i * D_L02_001B0C38);
        oscillation = math_wrap_angle_to_pi(D_L02_001B0C44 + (float)i * D_L02_001B0C4C);
        height = D_L02_001B0C3C * math_fast_sin_or_cos_b(oscillation);
        qcopy(D_L02_00249090[1][i], D_L02_00249090[0][i]);
        height *= math_fast_sin_or_cos_b(value);
        D_L02_002494A0[i] = height;
        point = D_L02_00249090[0][i];
        point[82] += height;
        height = FastAddRotations(mat_fast_helper_a(delta[0], delta[1]), 1.5707965f);
        lateral = D_L02_001B0C40 * math_fast_sin_or_cos_a(value);
        sideways[0] = math_fast_sin_or_cos_a(height) * lateral;
        sideways[1] = math_fast_sin_or_cos_b(height) * lateral;
        sideways[2] = 0;
        qcopy(D_L02_00249360[i], sideways);
        FastVecAdd(D_L02_00249090[1][i], D_L02_00249090[1][i], sideways);
    }
    }
    qcopy(state->end, D_L02_00249090[0][19]);
    oscillation = math_random_signed_float_range(0.52359885f, 1.0471977f);
    phase = math_random_float_range(-0.52359885f, 1.0471977f);
    FastVecScale(toward, direction, ((D_L02_001B0CAC) * 1.2f));
    math_apply_axis_rotation_to_quat(toward, toward, &((Hero *)g_hero_state)->q[0x740 / 16], phase);
    math_apply_axis_rotation_to_quat(toward, toward, &((Hero *)g_hero_state)->q[0x750 / 16], oscillation);
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2)) spin = -spin;
    radius = math_random_float_range(0.2f, 0.6f);
    part_spawn_ground_effect(state->start, 12, radius * 0.3f, radius, D_L02_001B0C7C | 0x7F000000, 0, spin, toward, 0, 0.0f);
    part_spawn_ground_effect(state->start, 12, radius * 0.15f, radius * 0.5f, 0x307F7F7F, 0, -spin, toward, 0, 0.0f);
    spin = math_random_int_range(1, 8);
    if (math_random_int_below(2)) spin = -spin;
    radius = math_random_float_range(0.15f, 3.0f);
    part_spawn_ground_effect(state->end, 10, radius * 0.1f, radius, D_L02_001B0C7C | 0x7F000000, 0, spin, D_L02_001A8F20, 0, 0.0f);
}
