#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern short D_L05_00221D50;
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern int func_00282948(char *);
extern float func_00283B98(float, float);
extern void func_L04_0040DCA8(char *, int, int, int, float, float, float, float);

void func_PAL_L05_0041DB88(char *arg0)
{
    char *st = *(char **)(arg0 + 0x68);
    TI128 v;
    char *q;
    int c1;
    int c2;

    *(float *)(st + 0x60) = func_00283B98(*(float *)(st + 0x60), 0.01f);
    *(float *)(st + 0x64) = func_00283B98(*(float *)(st + 0x64), -0.007f);
    *(float *)(st + 0x68) = func_00283B98(*(float *)(st + 0x68), 0.007f);
    *(float *)(st + 0x6C) = func_00283B98(*(float *)(st + 0x6C), *(float *)(st + 0x38) * 0.02f);
    q = arg0 + 0xE0;
    qcopy(&v, q);
    c1 = 0;
    func_00282F20((char *)&v, (char *)&v, 0.05f);
    c2 = 0;
    func_00282CC0((char *)&v, arg0 + 0x10, (char *)&v);
    if (D_L05_00221D50 != 0) {
        *(int *)(st + 0xA0) = 6;
    } else {
        c1 = 0x0FC85A5A;
        c2 = 0x28FF3232;
    }
    if (func_00282948(st + 0xA0) == 0) {
        int k = *(int *)(st + 0xA0) * 5;
        int lo = (0x6E - k) | 0x1E000000;

        c1 = ((k + 0x6E) << 16) | lo;
        c2 = ((k + 0x96) << 16) | lo;
    }
    func_L04_0040DCA8((char *)&v, *(int *)(st + 0x58), c1, 1, 0.27f, 0.35f, *(float *)(st + 0x60), 0.0f);
    func_L04_0040DCA8((char *)&v, *(int *)(st + 0x58), c1, 1, 0.27f, 0.35f, *(float *)(st + 0x64), 0.0f);
    func_L04_0040DCA8((char *)&v, 0x36, c2, 1, 0.22f, 0.35f, *(float *)(st + 0x68), 0.0f);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L05_0041E068);

INCLUDE_ASM("asm/pal/levels", func_PAL_L05_0041E5C8);

INCLUDE_ASM("asm/pal/levels", func_PAL_L05_0041EA08);

INCLUDE_ASM("asm/pal/levels", func_PAL_L05_0041EC50);

/* func_L05_00419F10 is defined in L05_00419F10-g8.c. */

void func_PAL_L05_0041EF70(void)
{
    char buf[0x20];
}

