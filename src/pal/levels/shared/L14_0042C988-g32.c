/* func_PAL_L14_0042C988, the PAL copy of func_L14_004272D8: the same C, where the particle count
   n gets the 50 Hz scale. Built with -g: the line label before the div.s gives retail's two nops. */
#include "include_asm.h"
#include "common.h"

extern f32 D_L14_001B1820[2] __attribute__((sda));
extern s32 D_L14_001B1828[2] __attribute__((sda));
extern s32 D_L14_001B1830[4] __attribute__((sda));
extern f32 D_L14_001B1840 __attribute__((sda));
extern f32 D_L14_001B1850[2][4] __attribute__((sda));

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float IntToFloat(int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);

void func_PAL_L14_0042C988(u8 *self) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 step[4] __attribute__((aligned(16)));
    s32 side;
    s32 kind;
    s32 n;

    side = math_random_int_below(2);
    kind = 1;
    if (!(math_random_float_range(0.0f, 1.0f) < D_L14_001B1840)) {
        kind = 0;
    }
    n = (math_random_int_range(D_L14_001B1830[kind * 2], D_L14_001B1830[kind * 2 + 1]) * 5 + 2) / 6;
    matrix_mul_vec3(pos, D_L14_001B1850[side], self + 0xC0);
    FastVecAdd(pos, pos, self + 0x10);
    FastVecSub(step, D_L14_001B1850[(side + 1) & 1], D_L14_001B1850[side]);
    matrix_mul_vec3(step, step, self + 0xC0);
    FastVecScale(step, step, 1.0f / IntToFloat(n));
    {
        s32 *cp = &D_L14_001B1828[kind];
        f32 *fp = &D_L14_001B1820[kind];
        part_spawn_hero_relative(pos, step, *cp, n & 0xFF, math_random_int_below(0xFF) & 0xFF, 0, *fp);
    }
}
