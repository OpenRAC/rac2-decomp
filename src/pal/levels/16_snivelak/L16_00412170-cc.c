/* func_PAL_L16_00412170, the PAL copy of func_L16_0040D258: the same C, where scale func_002A7820(18, 22); wrap func_002A7820(10, 15) (((int)({e}) * 5 + 2) / 6); wrap func_002A7820(10, 15) (((int)({e}) * 5 + 2) / 6); wrap func_002A7820(18, 22) (((int)({e}) * 5 + 2) / 6); wrap func_002A7820(20, 24) (((int)({e}) * 5 + 2) / 6); wrap func_002A7820(20, 24) (((int)({e}) * 5 + 2) / 6). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern unsigned int D_L16_001B2648 MACRO_ADDR;
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void *func_002BAE50(void *, void *, int, int, int, int, int, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282F20(void *, void *, float);

/* Emits two particle layers from five bones, with velocity chosen by bone group. */
void func_PAL_L16_00412170(u8 *moby)
{
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float clear[4] __attribute__((aligned(16)));
    int bone, lifetime, size;
    for (bone = 5; bone < 8; bone++) {
        *(TI128 *)clear = 0;
        clear[2] = -(func_002A7878(4.5f, 5.5f) * 0.020000001f);
        *(TI128 *)velocity = *(TI128 *)clear;
        func_0029FCC0(moby, bone, position);
        if (D_L16_001B2648 & 1) {
            size = (((int)(func_002A7820(18, 22)) * 5 + 2) / 6);
            func_002BAE50(position, velocity, 0xcf0000ff, 0xcf, size, 180, -10, 1);
        } else {
            size = (((int)(func_002A7820(20, 24)) * 5 + 2) / 6);
            func_002BAE50(position, velocity, 0x6000ffff, 0x80, size, 350, -10, 1);
        }
        lifetime = func_002A7820(20, 90);
        size = (((int)(func_002A7820(10, 15)) * 5 + 2) / 6);
        func_002BAE50(position, velocity, 0xefff7f4f, 0xff0000, size, lifetime, -lifetime, 1);
    }
    for (bone = 3; bone < 5; bone++) {
        func_00282F20(velocity, moby + 0xc0, -(func_002A7878(4.5f, 5.5f) * 0.020000001f));
        func_0029FCC0(moby, bone, position);
        if (D_L16_001B2648 & 1) {
            size = (((int)(func_002A7820(18, 22)) * 5 + 2) / 6);
            func_002BAE50(position, velocity, 0xcf0000ff, 0xcf, size, 50, -10, 1);
        } else {
            size = (((int)(func_002A7820(20, 24)) * 5 + 2) / 6);
            func_002BAE50(position, velocity, 0x6000ffff, 0x80, size, 100, -10, 1);
        }
        lifetime = func_002A7820(10, 25);
        size = (((int)(func_002A7820(10, 15)) * 5 + 2) / 6);
        func_002BAE50(position, velocity, 0xefff7f4f, 0xff0000, size, lifetime, -lifetime, 1);
    }
}
