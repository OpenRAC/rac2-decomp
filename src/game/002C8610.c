#include "common.h"

extern float D_001B5348;
extern int D_001B1DD4[] __attribute__((sda));
extern int D_001B1DD4_sda __attribute__((sda));
extern int D_001B1688[] __attribute__((sda));
extern char D_001B1DF0[] __attribute__((sda));
extern char D_001B5580[];

extern int func_00282978(void *);
extern void func_002B9180(void *);
extern float func_00283198(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_002C8610(char *obj)
{
    float v[4];
    char *p = obj + 0x20;
    char *q;
    int n;
    int top;

    if (*(float *)(obj + 0x18) - D_001B5348 < -7.0f ||
        (*(int *)(p + 0x14) != 0 && FastDecTimer(obj + 0xA) != 0)) {
        n = *(int *)(p + 0x10) - 1;
        *(int *)(p + 0x10) = n;
        if (n <= 0) {
            func_002B9180(obj);
            D_001B1DD4_sda = D_001B1DD4[0] - 1;
            return;
        }
        *(int *)(obj + 4) = (*(int *)(obj + 4) & 0xFFFFFF) + (n << 24);
    } else {
        top = *(int *)(obj + 4);
        if ((top >> 24) < *(int *)(p + 0x10))
            *(int *)(obj + 4) = top + 0x1000000;
    }
    if (((int)obj & 0x80) == 0)
        *(unsigned char *)(obj + 8) += 2;
    else
        *(unsigned char *)(obj + 8) -= 2;
    q = obj + 0x10;
    FastVecAdd(q, q, p);
    FastVecAdd(q, q, D_001B1DF0);
    if (*(int *)(p + 0x14) == 0) {
        short h = *(short *)(obj + 0xA);
        float f = func_00283198((float)(D_001B1688[0] & (h - 1)) / (float)h * 6.2831855f);
        FastVecScale(v, D_001B5580, f * 0.016666668f);
        FastVecAdd(q, v, q);
    }
}
