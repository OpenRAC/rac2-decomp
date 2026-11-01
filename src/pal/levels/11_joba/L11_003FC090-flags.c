#include "include_asm.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern void func_0029F338(void *);
extern int func_002E5CF8(int, int, char *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);

void func_PAL_L11_003FC478(u8 *object) {
    float movement[4];
    u8 *vars = *(u8 **)(object + 0x68);
    if (vars == 0) {
        func_0029F338(object);
        return;
    }
    switch (object[0x20]) {
    case 0:
        func_002E5CF8(0, 0, (char *)object);
        object[0x20] = 2;
        *(float *)(vars + 0xC) = 3.1415927f;
        *(float *)(vars + 0x10) = 0;
        *(Quadword *)(vars + 0x20) = *(Quadword *)(object + 0x10);
        /* Continue the first half of the oscillation immediately. */
    case 2:
        *(float *)(vars + 0x10) += 0.059341207f;
        *(float *)(vars + 0xC) = func_00283B98(*(float *)(vars + 0xC), 0.059341207f);
        if (*(float *)(vars + 0x10) >= 3.1415927f) {
            object[0x20] = 4;
        } else {
            func_00282F20(movement, (float *)(object + 0xC0), func_00283180(*(float *)(vars + 0xC)) + 1.0f);
            func_00282CC0((float *)(object + 0x10), movement, (float *)(vars + 0x20));
        }
        break;
    case 4:
        *(float *)(vars + 0x10) += 0.031415932f;
        *(float *)(vars + 0xC) = func_00283B98(*(float *)(vars + 0xC), 0.031415932f);
        if (*(float *)(vars + 0x10) >= 6.2831855f) {
            func_002E5CF8(0, 0, (char *)object);
            object[0x20] = 2;
            *(float *)(vars + 0xC) = 3.1415927f;
            *(float *)(vars + 0x10) = 0;
            *(Quadword *)(object + 0x10) = *(Quadword *)(vars + 0x20);
        } else {
            func_00282F20(movement, (float *)(object + 0xC0), func_00283180(*(float *)(vars + 0xC)) + 1.0f);
            func_00282CC0((float *)(object + 0x10), movement, (float *)(vars + 0x20));
        }
        break;
    }
}
