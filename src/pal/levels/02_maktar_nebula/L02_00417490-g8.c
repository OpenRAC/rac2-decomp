#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float D_L02_001B1C74 __attribute__((sda));
extern float D_L02_001B1C78 __attribute__((sda));
extern float D_L02_001B1C7C __attribute__((sda));
extern float D_L02_001B1C80 __attribute__((sda));
extern float D_L02_001B1C84 __attribute__((sda));
extern float D_L02_001B1C88 __attribute__((sda));

/* Restore the base pose, then advance its three independent oscillations. */
void func_PAL_L02_00418428(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float step;
    float next;
    float wave;

    *(TI128 *)(object + 0x10) = *(TI128 *)(state + 0x90);
    *(TI128 *)(object + 0xF0) = *(TI128 *)(state + 0xA0);
    step = 0.0003490659f;
    *(float *)(state + 0xB8) = func_00283B98(*(float *)(state + 0xB8), D_L02_001B1C74 * step);
    wave = func_00283198(*(float *)(state + 0xB8));
    next = D_L02_001B1C7C * step;
    *(float *)(object + 0xF0) += D_L02_001B1C78 * wave;
    *(float *)(state + 0xB4) = func_00283B98(*(float *)(state + 0xB4), next);
    wave = func_00283198(*(float *)(state + 0xB4));
    next = D_L02_001B1C84 * step;
    *(float *)(object + 0xF4) += D_L02_001B1C80 * wave;
    *(float *)(state + 0xB0) = func_00283B98(*(float *)(state + 0xB0), next);
    *(float *)(object + 0x18) += D_L02_001B1C88 * func_00283198(*(float *)(state + 0xB0));
}
