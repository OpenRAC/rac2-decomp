#include "include_asm.h"

#include "common.h"
typedef union {
    char b[0x400];
    int i[0x100];
    char *ptr[0x100];
} L04_003EC140_Player;
extern L04_003EC140_Player D_00189E20;
extern void *func_00115484(void *, int, int);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283198(float);
extern void func_00283698(void *, void *);
extern float func_00283B98(float, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float D_L04_001B00E8 __attribute__((sda));
extern float D_L04_001B00EC[] __attribute__((sda));
extern float D_L04_001B00F0[] __attribute__((sda));
extern float D_L04_001B00F8 __attribute__((sda));
extern float D_L04_001B00FC[] __attribute__((sda));
extern float D_L04_001B0100[] __attribute__((sda));
extern float D_L04_001B0108[2] __attribute__((sda));
extern float D_L04_001B0110[] __attribute__((sda));
extern float D_L04_001B0118[2] __attribute__((sda));
extern float D_L04_001B0120[] __attribute__((sda));
extern float D_L04_001B0124 __attribute__((sda));

void func_PAL_L04_003F00D8(char *o)
{
    float rate[4], base[4], desired[4], input[4], matrix[16], delta[4];
    float scale, angle;
    int active, i;
    char *p = *(char **)(o + 0x68);

    qcopy(o + 0x10, p + 0x1b0);
    func_00115484(input, 0, 12);
    scale = 1.0f;
    active = 0;
    if (D_00189E20.ptr[0x33c / 4] == o && D_00189E20.i[0x340 / 4]) {
        active = 1;
        if (D_00189E20.i[0x340 / 4] == 1) {
            scale = D_L04_001B0124;
            *(int *)(p + 0x1d0) = 0;
            *(int *)(p + 0x1d4) = 0;
            *(int *)(p + 0x1d8) = 0;
        }
        func_00283698(matrix, o + 0xc0);
        func_00282CF0(delta, D_00189E20.b + 0x80, o + 0x10);
        func_00283098(delta, delta, matrix);
        input[0] += -delta[1] * 0.333f;
        input[1] += delta[0] * 1.5f;
    }
    for (i = 0; i < 2; i++) {
        base[i] = D_L04_001B0118[i] * ((func_00282C48(input[i]) + 1.0f) * 0.00040000002f);
        rate[i] = base[i] * scale;
        desired[i] = active ? D_L04_001B0108[i] * input[i] : 0;
        func_002AA548(p + 0x1c4 + i * 4, p + 0x1d0 + i * 4, desired[i], rate[i], base[i], 0.1f);
    }
    base[2] = D_L04_001B0120[0] * 0.00040000002f;
    rate[2] = base[2] * scale;
    desired[2] = active ? D_L04_001B0110[0] : 0;
    func_002AA548(p + 0x1cc, p + 0x1d8, desired[2], rate[2], base[2], 0.1f);
    *(float *)(o + 0xf0) = *(float *)(p + 0x1c4);
    *(float *)(o + 0xf4) = *(float *)(p + 0x1c8);
    *(float *)(o + 0x18) += *(float *)(p + 0x1cc);
    angle = func_00283B98(*(float *)(p + 0x1a8), D_L04_001B00E8 * 0.0003490659f);
    *(float *)(p + 0x1a8) = angle;
    *(float *)(o + 0xf0) += D_L04_001B00F8 * (func_00283198(angle) * 0.017453294f);
    angle = func_00283B98(*(float *)(p + 0x1ac), D_L04_001B00EC[0] * 0.0003490659f);
    *(float *)(p + 0x1ac) = angle;
    *(float *)(o + 0xf4) += D_L04_001B00FC[0] * (func_00283198(angle) * 0.017453294f);
    angle = func_00283B98(*(float *)(p + 0x1c0), D_L04_001B00F0[0] * 0.0003490659f);
    *(float *)(p + 0x1c0) = angle;
    *(float *)(o + 0x18) += D_L04_001B0100[0] * func_00283198(angle);
}
