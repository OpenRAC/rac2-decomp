#include "include_asm.h"
#include "common.h"

extern f32 D_L14_001B1820[2] __attribute__((sda));
extern s32 D_L14_001B1828[2] __attribute__((sda));
extern s32 D_L14_001B1830[4] __attribute__((sda));
extern f32 D_L14_001B1840 __attribute__((sda));
extern f32 D_L14_001B1850[2][4] __attribute__((sda));

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern void *func_002C3150(void *, void *, int, int, int, int, float);

void func_L14_004272D8(u8 *self) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 step[4] __attribute__((aligned(16)));
    s32 side;
    s32 kind;
    s32 n;

    side = func_002A77E0(2);
    kind = 1;
    if (!(func_002A7878(0.0f, 1.0f) < D_L14_001B1840)) {
        kind = 0;
    }
    n = func_002A7820(D_L14_001B1830[kind * 2], D_L14_001B1830[kind * 2 + 1]);
    matrix_mul_vec3(pos, D_L14_001B1850[side], self + 0xC0);
    FastVecAdd(pos, pos, self + 0x10);
    FastVecSub(step, D_L14_001B1850[(side + 1) & 1], D_L14_001B1850[side]);
    matrix_mul_vec3(step, step, self + 0xC0);
    FastVecScale(step, step, 1.0f / IntToFloat(n));
    {
        s32 *cp = &D_L14_001B1828[kind];
        f32 *fp = &D_L14_001B1820[kind];
        func_002C3150(pos, step, *cp, n & 0xFF, func_002A77E0(0xFF) & 0xFF, 0, *fp);
    }
}
