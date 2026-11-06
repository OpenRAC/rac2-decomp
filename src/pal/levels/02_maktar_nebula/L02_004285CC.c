#include "include_asm.h"

typedef unsigned char u8;

extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern float func_002A7878(float, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int D_L02_001B2050[2] __attribute__((sda));
extern int D_L02_001B2058[2] __attribute__((sda));

/* func_PAL_L02_004288E8, the PAL copy of func_L02_00423838: the same C, where the three frame counts are
   scaled to 50 Hz and the downward pull per frame becomes 0.002f. */
void func_PAL_L02_004288E8(u8 *a0, float lo, float hi) {
    float v10[4];
    float v20[4];
    float v30[4];
    float v40[4];
    float v50[4];
    float v60[4];
    int i;
    float r;
    int a, b, c;
    int c0, c1;
    float k = 0.002f;

    func_00282D30(v10, a0 + 0xE0, 1.75f);
    func_00282CC0(v20, v10, a0 + 0x10);
    func_00282D30(v10, a0 + 0xC0, -0.5f);
    func_00282CC0(v20, v10, v20);
    i = 19;
    do {
        func_00282F20(v40, a0 + 0xD0, func_002A7878(-1.0f, 1.0f));
        func_00282F20(v30, a0 + 0xE0, func_002A7878(-0.15f, 1.0f));
        func_00282CC0(v50, a0 + 0xC0, v40);
        func_00282CC0(v50, v50, v30);
        func_00282F20(v50, v50, func_002A7878(lo, hi));
        r = func_002A7878(0.5f, 1.5f);
        a = func_00283CF0((r * 50.0f + 2.0f) * 0.16666667f);
        b = func_00283CF0((r * 150.0f + 2.0f) * 0.16666667f);
        c = func_00283CF0((r * 35.0f + 2.0f) * 0.16666667f);
        v50[3] = func_002A7878(0.2f, 0.6f);
        func_00282C88(v60);
        v60[2] = -k * (float)(a + b + c);
        func_00282CC0(v60, v60, v50);
        v60[3] = 0.01f;
        c0 = func_00283D38(D_L02_001B2050[0], D_L02_001B2050[1], func_002A7878(0.0f, 1.0f));
        c1 = func_00283D38(D_L02_001B2058[0], D_L02_001B2058[1], func_002A7878(0.0f, 1.0f));
        func_002BAA28(v20, v50, v60, c0, c1, a, b, c, 0x1003C);
    } while (--i >= 0);
}
