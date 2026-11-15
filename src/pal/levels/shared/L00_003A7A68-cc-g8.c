/* func_PAL_L00_003A7A68, the PAL copy of func_L00_003A4480: the same C, where expr 0.016666668f becomes 0.020000001f; scale D_L00_001AF63C; rename func_002C16C0 becomes func_PAL_002C23B8. */
#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern Hero g_hero_state;
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

extern float D_L00_001AF62C __attribute__((sda));
extern float D_L00_001AF630 __attribute__((sda));
extern int D_L00_001AF634 __attribute__((sda));
extern int D_L00_001AF638 __attribute__((sda));
extern unsigned int D_L00_001AF63C __attribute__((sda));
extern float D_L00_001AF640 __attribute__((sda));
extern float D_L00_001AF644 __attribute__((sda));
extern float D_L00_001AF648 __attribute__((sda));
extern float D_L00_001AF64C __attribute__((sda));
extern float D_L00_001AF650 __attribute__((sda));
extern float D_L00_001AF654 __attribute__((sda));
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
extern char *func_PAL_002C23B8(void *, void *, unsigned int, int, int, int, float, float, float, float, float);

/* Emit a rotating fan of fragments followed by smoke particles. */
void func_PAL_L00_003A7A68(char *moby)
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
    *(unsigned char *)(moby + 0xBC) = 5;
    math_apply_axis_rotation_to_quat(base, &g_hero_state.f[460], &g_hero_state.f[464], 0.34906590f);
    qcopy(direction, base);
    for (count = 0; count < 20; count++) {
        char *fragment;
        angle = FastAddRotations(angle, math_random_float_range(0.0f, 0.6283186078f));
        FastVecScale(velocity, direction, math_random_float_range(0.120000005f, 0.36f));
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
    math_apply_axis_rotation_to_quat(base, &g_hero_state.f[460], &g_hero_state.f[464], D_L00_001AF62C * 0.017453294f);
    qcopy(direction, base);
    qzero_nc(drift);
    if (g_hero_state.i[208])
        FastVecScale(drift, &g_hero_state.f[68], 1.7f);
    for (count = 0; count < 20; count++) {
        unsigned int color;
        int spin;
        float size;
        angle = FastAddRotations(angle, math_random_float_range(0.0f, 0.6283186078f));
        FastVecScale(velocity, direction, math_random_float_range(D_L00_001AF644 * (0.020000001f),
                                                       D_L00_001AF648 * (0.020000001f)));
        FastVecAdd(velocity, velocity, drift);
        color = (((int)(D_L00_001AF63C) * 5 + 2) / 6);
        spin = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        jitter[0] = origin[0] + math_random_signed_float_range(0.0f, D_L00_001AF630);
        jitter[1] = origin[1] + math_random_signed_float_range(0.0f, D_L00_001AF630);
        jitter[2] = origin[2] + math_random_signed_float_range(0.0f, D_L00_001AF630);
        size = math_random_float_range(D_L00_001AF64C, D_L00_001AF650) * 210000.0f;
        FastVecSub(jitter, jitter, velocity);
        func_PAL_002C23B8(jitter, velocity, color, D_L00_001AF634, D_L00_001AF638, spin,
                      size, D_L00_001AF654, D_L00_001AF640, 0.0f, 0.0f);
        if (math_fabs(angle) > 0.00001f) {
            math_build_axis_angle_quat(rotation, &g_hero_state.f[460], angle);
            vec_rotate_by_quaternion(direction, base, rotation);
        }
    }
}
