#include "include_asm.h"

/* func_PAL_L02_00433B90, the PAL copy of func_L02_0042E680: the same C, where each count runs through
   the 50 Hz scale (x * 5 + 2) / 6 and k becomes 0.0036000002f. A unit of its own for the template's
   opt-in quadword-copy profile and scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier,
   config/cflags.txt). */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern void func_002ACB48(void *, float);
extern int D_L02_001B2410[2] __attribute__((sda));
extern int D_L02_001B2418[2] __attribute__((sda));

void func_PAL_L02_00433B90(u8 *a0, float lo, float hi) {
    float v10[4];
    float v20[4];
    float v30[4];
    float v40[4];
    float v50[4];
    float v60[4];
    float v70[4];
    int i;
    float r;
    int a, b, c;
    int c0, c1;
    float k = 0.0036000002f;

    v10[0] = 0.0f;
    v10[1] = 0.0f;
    v10[2] = 4.0f;
    v10[3] = 1.0f;
    func_00282CC0(v20, v10, a0 + 0x10);
    i = 29;
    do {
        func_00282F20(v40, a0 + 0xC0, func_002A7878(-0.8f, 0.8f));
        func_00282F20(v30, a0 + 0xE0, func_002A7878(0.25f, 1.0f));
        func_00282CC0(v50, a0 + 0xD0, v40);
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
        c0 = func_00283D38(D_L02_001B2410[0], D_L02_001B2410[1], func_002A7878(0.0f, 1.0f));
        c1 = func_00283D38(D_L02_001B2418[0], D_L02_001B2418[1], func_002A7878(0.0f, 1.0f));
        *(TI128 *)v70 = *(TI128 *)v20;
        func_002ACB48(v70, 0.25f);
        func_002BAA28(v70, v50, v60, c0, c1, a, b, c, 0x1003C);
    } while (--i >= 0);
}
