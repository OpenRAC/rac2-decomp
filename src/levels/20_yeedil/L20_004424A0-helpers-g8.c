#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B212C __attribute__((sda));
extern float D_L20_001B2130 __attribute__((sda));
extern float D_L20_001B2138 __attribute__((sda));
extern float D_L20_001B2128 __attribute__((sda));


extern void func_002B60B0(unsigned char *, float, float, float, float);
extern float func_002A89A8(void *, int, float);
extern float func_00282C10(float);

void func_L20_004424A0(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    func_002B60B0((unsigned char *)actor, 0.0f, 0.0f,
                 D_L20_001B212C * 4.84813745e-06f,
                 D_L20_001B2130 * 0.000290888245f);
    *(float *)(state + 0x7C) = D_L20_001B2138 * 0.000277777785f;
    *(float *)(state + 0xE0) = func_002A89A8(actor + 0x10, 0, 0.5f);
    qzero(state + 0xF0);
    *(float *)(state + 0xF8) = func_00282C10(*(float *)(state + 0x7C) * 2.0f * D_L20_001B2128);
}
