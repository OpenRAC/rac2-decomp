#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern void moby_set_state(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int IsPointInCuboid(void *, int);
extern char g_hero_position[];
extern char D_L12_001B9E00[];
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void FastVecScale(float, void *, void *);

void func_PAL_L12_00424110(u8 *a0)
{
    s32 *s = *(s32 **)(a0 + 0x68);
    int state = a0[0x20];
    f32 v[4];

    switch (state) {
    case 0:
        qcopy((u8 *)s + 0x10, a0 + 0x10);
        moby_set_state(a0, 1, -1);
        a0[0x30] = 0x7F;
        break;
    case 1:
        if (vec_distance_xy(a0 + 0x10, D_L12_001B2E9C + (s[0] << 8) + 0x10) < 5.0f) {
            s[0xB] = state;
            s[8] = 0x32;
        } else if ((IsPointInCuboid(g_hero_position, s[1]) && s[0xB] != 0) ||
                   (IsPointInCuboid(D_L12_001B9E00, s[1]) && s[0xB] != 0)) {
            s[8] = 0x32;
        }
        if (math_fast_float_d((u8 *)s + 0x20))
            math_step_value_toward_target((u8 *)s + 0x24, (u8 *)s + 0x28, 0.0f, 0.00080000004f, 0.00080000004f, 0.080000006f);
        else
            math_step_value_toward_target((u8 *)s + 0x24, (u8 *)s + 0x28, 1.0f, 0.00080000004f, 0.00080000004f, 0.080000006f);
        if (*(f32 *)((u8 *)s + 0x28) != 0.0f) {
            *(TI128 *)v = 0;
            v[0] = 1.0f;
            v[2] = 3.0f;
            matrix_mul_vec3(v, v, a0 + 0xC0);
            FastVecScale(*(f32 *)((u8 *)s + 0x24), v, v);
            FastVecAdd(a0 + 0x10, (u8 *)s + 0x10, v);
            if (s[0xC] % 120 == 0)
                PlayMobySound(0, 0, (s32)a0);
            s[0xC]++;
        } else {
            s[0xC] = 0;
        }
        break;
    }
}
