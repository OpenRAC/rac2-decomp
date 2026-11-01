#include "include_asm.h"

typedef float f32;
extern void func_0029F338(char *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(float, int, int);
extern float func_00283CE0(int);
extern void func_L00_002E6CF0(void *, void *);
extern void func_PAL_L20_003A21A0(char *);
extern int D_L20_001AEDA8 __attribute__((sda));
extern int D_L20_001AED90 __attribute__((sda));
extern int D_L20_001AED94;
extern int D_L20_001AED98;
extern int D_L20_001AED9C;

void func_PAL_L20_003A1CE8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (func_00282948(state) != 0) {
        func_0029F338(arg0);
    } else {
        f32 x = *(f32 *)(state + 0x8);
        f32 r, s;
        int v, w, lo, hi;

        if (*(int *)(state + 0xC) != 0) {
            r = func_00283B98(x, (f32)D_L20_001AEDA8 * 0.0003490659f);
            *(f32 *)(state + 0x8) = r;
            s = func_00283198(r);
            v = func_00283D38(s * 0.5f + 0.5f, D_L20_001AED90, D_L20_001AED94);
        } else {
            r = func_00283B98(x, (f32)D_L20_001AEDA8 * 0.0003490659f);
            *(f32 *)(state + 0x8) = r;
            s = func_00283198(r);
            v = func_00283D38(s * s * 0.5f + 0.5f, D_L20_001AED98, D_L20_001AED9C);
        }
        w = func_00283D38(0.15f, *(int *)(state + 0x10) | *(int *)(state + 0x4), v);
        lo = w & 0xFFFFFF;
        hi = w & 0xFF000000;
        *(int *)(state + 0x10) = hi;
        *(int *)(state + 0x4) = lo;
        *(f32 *)(state + 0x14) = func_00283CE0(hi >> 24) * 0.00390625f;
        func_L00_002E6CF0(func_PAL_L20_003A21A0, arg0);
    }
}
