#include "include_asm.h"
#include "names.h"

extern char g_camera_eye_state[];
extern int math_random_int_below(int);
extern float g_sparkle_time_min __attribute__((sda));
extern float g_sparkle_time_max __attribute__((sda));
extern unsigned char g_sparkle_kind __attribute__((sda));
extern void *g_sparkle_effect_default __attribute__((sda));
extern void *g_sparkle_effect_third __attribute__((sda));
extern void *g_sparkle_effect_alt __attribute__((sda));
extern float g_sparkle_scale __attribute__((sda));
extern float g_sparkle_scale_third __attribute__((sda));
extern char g_hero_state_block[];
extern void FastVecSub(void *, void *, void *);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void *part_spawn_hero_relative(void *, void *, void *, int, int, int, float);

void func_PAL_00314558(unsigned char *object)
{
    char first[16];
    char second[16];
    char third[16];
    unsigned char *state;
    char *basis;
    void *effect;
    unsigned char kind;
    unsigned char random;

    state = *(unsigned char **)(object + 0x68);
    FastVecSub(first, g_camera_eye_state, object + 0x10);
    basis = g_hero_state_block;
    FastVecScale(second, basis,
                  math_random_float_range(g_sparkle_time_min * 0.020000001f,
                               g_sparkle_time_max * 0.020000001f));
    math_apply_axis_rotation_to_quat(third, second, first, math_random_angle());

    effect = state[0x57] != 0 ? g_sparkle_effect_alt : g_sparkle_effect_default;
    kind = g_sparkle_kind;
    random = (unsigned char)math_random_int_below(255);
    part_spawn_hero_relative(object + 0x10, third, effect, kind, random, 1, g_sparkle_scale);

    kind = g_sparkle_kind;
    random = (unsigned char)math_random_int_below(255);
    part_spawn_hero_relative(object + 0x10, third, g_sparkle_effect_third, kind, random, 1, g_sparkle_scale_third);
}
