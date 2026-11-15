#include "include_asm.h"

#include "common.h"
extern void moby_set_state(u8 *, int, int);
extern float D_L07_001B0F44 __attribute__((sda));
extern float D_L07_001B0F38 __attribute__((sda));
extern float D_L07_001B0F3C __attribute__((sda));
extern float D_L07_001B0F40 __attribute__((sda));
extern int D_L07_001B1E08 __attribute__((sda));
extern int D_L07_001B0F30 __attribute__((sda));
extern int D_L07_001B0F34;
extern void func_PAL_L01_0031C9C0(u8 *, float, u8 *, float, float, int);
extern void func_PAL_L07_003FA300(u8 *);
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

void func_PAL_L07_003FA170(u8 *o)
{
    float pos[4], old[4], delta[4];
    u8 *m = *(u8 **)(o + 0x68);
    float phase;
    qcopy(pos, o + 0x10);
    qcopy(old, o + 0xF0);
    *(float *)(o + 0x2C) = *(float *)(*(u8 **)(o + 0x24) + 0x24) * D_L07_001B0F44;
    switch (o[0x20]) {
    case 0:
        *(u16 *)(o + 0x34) |= 0x1000;
        *(float *)(m + 0x88) = 9.0f;
        *(int *)(m + 0xDC) |= 1;
        moby_set_state(o, 1, -1);
        break;
    case 1:
        func_PAL_L01_0031C9C0(o, D_L07_001B0F38, m + 0x50, D_L07_001B0F3C, D_L07_001B0F40, *(int *)(m + 0xE0));
        func_PAL_L07_003FA300(o);
        break;
    }
    if (o[0x31]) {
        phase = IntToFloat(D_L07_001B1E08 % 50);
        { float period = IntToFloat(50);
        phase *= 6.2831855f;
        phase /= period; }
        *(int *)(o + 0x78) = PulseColor(D_L07_001B0F30, D_L07_001B0F34, phase - 3.1415927f);
    }
    FastVecSub(delta, o + 0x10, pos);
    mat_combine_and_store(m + 0xA0, delta, old, o + 0xF0);
}
