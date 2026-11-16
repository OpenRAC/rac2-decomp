#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern Hero g_hero_state;
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

extern float g_fragment_fan_angle __attribute__((sda));
extern float g_fragment_jitter_range __attribute__((sda));
extern int g_fragment_burst_param_a __attribute__((sda));
extern int g_fragment_burst_param_b __attribute__((sda));
extern unsigned int g_fragment_color __attribute__((sda));
extern float g_fragment_spawn_param_b __attribute__((sda));
extern float g_fragment_speed_min __attribute__((sda));
extern float g_fragment_speed_max __attribute__((sda));
extern float g_fragment_size_min __attribute__((sda));
extern float g_fragment_size_max __attribute__((sda));
extern float g_fragment_spawn_param_a __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void FastVecScale(void *, void *, float);
extern char *part_spawn_streak_effect(void *, void *);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void FastVecSub(void *, void *, void *);
extern char *part_spawn_burst(void *, void *, unsigned int, int, int, int, float, float, float, float, float);

/* Emit a rotating fan of fragments followed by smoke particles. */
void part_spawn_fragment_fan_and_smoke(char *moby)
{
    Vector rotation, direction, base, origin, velocity, jitter, drift;
    float angle = 0.0f;
    int count;
    *(VectorBits *)base = 0;
    base[0] = 0.3f;
    base[1] = -1.0f;
    base[3] = 1.0f;
    matrix_mul_vec3(base, base, moby + 0xC0);
    FastVecAdd(origin, moby + 0x10, base);
    *(unsigned char *)(moby + 0xBC) = 6;
    math_apply_axis_rotation_to_quat(base, &g_hero_state.f[460], &g_hero_state.f[464], 0.34906590f);
    qcopy(direction, base);
    for (count = 0; count < 20; count++) {
        char *fragment;
        angle = FastAddRotations(angle, math_random_float_range(0.0f, 0.6283186078f));
        FastVecScale(velocity, direction, math_random_float_range(0.1000000089f, 0.3f));
        fragment = part_spawn_streak_effect(origin, velocity);
        if (fragment) {
            char *tail = fragment + 0x30;
            float duration = 2.0f;
            float rate = 0.05f;
            float scale = 0.5f;
            FastVecScale(velocity, direction, 0.75f);
            FastVecAdd(fragment + 0x10, origin, velocity);
            qcopy(fragment + 0x20, origin);
            *(float *)(tail + 0xC) = duration;
            *(float *)(fragment + 0x1C) = rate;
            *(float *)(fragment + 0x2C) = scale;
            *(int *)(fragment + 4) = 0x307F7F7F;
            *(int *)(fragment + 0xC) = 0x307F7F7F;
        }
        if (math_fabs(angle) > 0.00001f) {
            math_build_axis_angle_quat(rotation, &g_hero_state.f[460], angle);
            vec_rotate_by_quaternion(direction, base, rotation);
        }
    }
    angle = 0.0f;
    math_apply_axis_rotation_to_quat(base, &g_hero_state.f[460], &g_hero_state.f[464], g_fragment_fan_angle * 0.017453294f);
    qcopy(direction, base);
    qzero_nc(drift);
    if (g_hero_state.i[208])
        FastVecScale(drift, &g_hero_state.f[68], 1.7f);
    for (count = 0; count < 20; count++) {
        unsigned int color;
        int spin;
        float size;
        angle = FastAddRotations(angle, math_random_float_range(0.0f, 0.6283186078f));
        FastVecScale(velocity, direction, math_random_float_range(g_fragment_speed_min * (1.0f / 60.0f),
                                                       g_fragment_speed_max * (1.0f / 60.0f)));
        FastVecAdd(velocity, velocity, drift);
        color = g_fragment_color;
        spin = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        jitter[0] = origin[0] + math_random_signed_float_range(0.0f, g_fragment_jitter_range);
        jitter[1] = origin[1] + math_random_signed_float_range(0.0f, g_fragment_jitter_range);
        jitter[2] = origin[2] + math_random_signed_float_range(0.0f, g_fragment_jitter_range);
        size = math_random_float_range(g_fragment_size_min, g_fragment_size_max) * 210000.0f;
        FastVecSub(jitter, jitter, velocity);
        part_spawn_burst(jitter, velocity, color, g_fragment_burst_param_a, g_fragment_burst_param_b, spin,
                      size, g_fragment_spawn_param_a, g_fragment_spawn_param_b, 0.0f, 0.0f);
        if (math_fabs(angle) > 0.00001f) {
            math_build_axis_angle_quat(rotation, &g_hero_state.f[460], angle);
            vec_rotate_by_quaternion(direction, base, rotation);
        }
    }
}
