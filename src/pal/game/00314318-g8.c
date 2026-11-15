#include "include_asm.h"
#include "names.h"

extern char g_camera_eye_state[];
extern int math_random_int_below(int);
extern float D_001AF1A4 __attribute__((sda));
extern float D_001AF1A8 __attribute__((sda));
extern unsigned char D_001AF1AC __attribute__((sda));
extern void *D_001AF1B0 __attribute__((sda));
extern void *D_001AF1B4 __attribute__((sda));
extern void *D_001AF1B8 __attribute__((sda));
extern float D_001AF1BC __attribute__((sda));
extern float D_001AF1C0 __attribute__((sda));
extern char D_0018A0E0[];
extern void FastVecSub(void *, void *, void *);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void part_spawn_hero_relative(void *, void *, void *, int, int, int, float);

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
    basis = D_0018A0E0;
    FastVecScale(second, basis,
                  math_random_float_range(D_001AF1A4 * 0.020000001f,
                               D_001AF1A8 * 0.020000001f));
    math_apply_axis_rotation_to_quat(third, second, first, math_random_angle());

    effect = state[0x57] != 0 ? D_001AF1B8 : D_001AF1B0;
    kind = D_001AF1AC;
    random = (unsigned char)math_random_int_below(255);
    part_spawn_hero_relative(object + 0x10, third, effect, kind, random, 1, D_001AF1BC);

    kind = D_001AF1AC;
    random = (unsigned char)math_random_int_below(255);
    part_spawn_hero_relative(object + 0x10, third, D_001AF1B4, kind, random, 1, D_001AF1C0);
}
