#include "include_asm.h"

#include "common.h"
extern char D_001B5200[], D_001B5490[], D_00189E20[];
extern void func_00282F20(float *, float *, float);
extern void func_00270B58(float *, float *, float *, float *, float *, float *);
extern void func_002AB600(void *, void *);
extern void func_00270D50(void);
extern void func_00270E30(void);
extern void func_00270EA8(void);
extern float func_00283CE0(int);

void func_PAL_00270D50(char *from)
{
    unsigned char *r = (unsigned char *)D_001B5200 + 0x290;
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    unsigned char sub;

    if (*(short *)r == 1) {
        sub = r[3];
        if (sub == 0) {
            qcopy(r + 0x50, from + 0x30);
            func_002AB600(r + 0x60, from);
        } else if (sub == 2) {
            qcopy(r + 0xC0, from + 0x30);
            func_002AB600(r + 0xD0, from);
            func_00270D50();
        } else {
            char *g = D_00189E20;

            func_00282F20(a, (float *)(*(char **)(g + 0x2290) + 0xC0), 1.0f);
            func_00282F20(b, (float *)(*(char **)(g + 0x2290) + 0xD0), 1.0f);
            func_00282F20(c, (float *)(*(char **)(g + 0x2290) + 0xE0), 1.0f);
            func_00270B58((float *)(r + 0x70), (float *)(from + 0x30),
                          (float *)(*(char **)(r - 0x100) + 0x30), a, b, c);
            func_002AB600(r + 0xB0, from);
            qcopy(r + 0xD0, r + 0xB0);
        }
    } else {
        sub = r[3];
        if (sub == 2) {
            func_00270E30();
            func_00270D50();
        } else if (sub == 1) {
            func_00270E30();
            qcopy(r + 0xB0, r + 0xD0);
        } else if (sub == 0) {
            func_00270EA8();
        }
    }
    *(short *)D_001B5490 = 3;
    r[2] = r[3];
    if (r[2] == 0) {
        unsigned char *l = r + 0x10;

        *(float *)(l + 0x10) = *(float *)(l + 0x14);
        *(int *)(l + 0xC) = 0;
        qcopy(r + 0x40, r + 0x50);
        *(int *)(r + 0x10) = 0;
        *(float *)(l + 0x4) = *(float *)(l + 0x8);
        qcopy(r + 0x30, r + 0x60);
    } else {
        unsigned char *o = r + 0x70;
        int n = ((s32)(++*(int *)(o + 0x14)) * 5 + 2) / 6;

        *(int *)(o + 0xC) = n;
        *(float *)(o + 0x10) = 1.0f / func_00283CE0(n);
    }
}
