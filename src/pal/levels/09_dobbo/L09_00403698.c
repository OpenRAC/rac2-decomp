#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L09_00403698);

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern float func_00283CE0(int a0);
extern int func_00283DB8(float *a0, float f12);
extern float func_002A7878(float lo, float hi);
extern void func_0029FCC0(char *a0, int a1, float *a2);
extern char *func_002BAE50(float *a0, float *a1, int a2, int a3, int t0, int t1, int t2, int t3);
extern int func_00283CF0(float a);

/* func_L09_003FEA48 is defined in L09_003FEA48-g8.c (this unit has no $gp access for it). */

/* func_L09_003FEAE8 is defined in L09_003FEAE8-g8.c. */

void func_PAL_L09_00403900(char *a0) {
    EffectVector a;
    EffectVector b;
    EffectVector c;
    EffectVector w;
    int i;
    int j;
    char *p;

    qcopy(a.value, a0 + 0x10);
    a.value[3] = 6.0f;
    if (func_00283DB8(a.value, func_00283CE0(*(s16 *)(a0 + 0x32))) == -1)
        return;
    for (i = 12; i < 14; i++) {
        w.bits = 0;
        w.value[2] = -(func_002A7878(3.5f, 4.5f) * 0.020000001f);
        c.bits = w.bits;
        for (j = 0; j < 2; j++) {
            func_0029FCC0(a0, i, b.value);
            b.value[2] += func_00283CE0(j) * 0.015f + 0.5f;
            if (j & 1)
                p = func_002BAE50(b.value, c.value, 0x77FF0000, 0x00FF0060, 0x10, 200, -100, 1);
            else
                p = func_002BAE50(b.value, c.value, 0x77FF0060, 0x00FF0000, 0x11, 300, -100, 1);
            if (p)
                p[9] = ((*(s16 *)(a0 + 0x32) >> 5) << 4) + func_00283CF0(0.0f);
            p = func_002BAE50(b.value, c.value, 0x77FFFFFF, 0x00FF0000, 0xA, 100, -100, 1);
            if (p)
                p[9] = ((*(s16 *)(a0 + 0x32) >> 5) << 4) + func_00283CF0(0.0f);
        }
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L09_00403B10);

