#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L16_00411710);

#include "common.h"
extern s32 func_313EA0(s32);
extern void func_002A7750(void *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern float func_00282E48(void *, void *);
extern u8 *D_L16_001B2C0C[] __attribute__((sda));
extern u8 D_0013963B;
extern s32 func_00282948(void *);
extern u8 *D_L16_001FE7C0[];
extern void func_002B60B0(void *, float, float, float, float);
extern s32 func_00283CF0(float);
extern void func_002A93B0(void *);
extern s32 func_PAL_002B1A50(void *, void *, s32);
extern void func_L16_0040D188(u8 *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern float D_L16_001B9B00[];
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern s32 D_L16_001B2B38[] __attribute__((sda));
extern s32 func_002A9640(void *, s32, s32);
extern s32 func_00277258(void *, s32, void *, float);

/* Object update: on the first frame (+0x20 still zero) sets the state's defaults and
   rates; then, with +0x31 set and the object within 32 units of D_L16_001B9B00, runs
   func_002A93B0 and sets +0x6F to 30; marks the group when func_PAL_002B1A50 reports, and
   runs func_002B3BA8 on the state's two slots, keeping the object's +0x18 across them. */
void func_PAL_L16_00411C78(u8 *arg)
{
    u8 *state;

    state = *(u8 **)(arg + 0x68);
    if (arg[0x20] == 0) {
        *(s32 *)(state + 0x54) = 0;
        *(s32 *)(state + 0x7C) = 0;
        state[0x150] = 5;
        *(s32 *)(state + 0x188) = 3;
        *(float *)(state + 0x17C) = 0.15f;
        *(float *)(state + 0x50) = 1.868f;
        *(float *)(state + 0x170) = 0.5f;
        *(float *)(state + 0x174) = 0.5f;
        *(float *)(state + 0x58) = 0.5f;
        *(float *)(state + 0x5C) = 0.5f;
        *(float *)(state + 0x60) = 3.141593f;
        *(float *)(state + 0x80) = 0.52359885f;
        func_002B60B0(arg, 0.0032000002f, 0.080000006f, 0.00062831864f, 0.04188791f);
        *(s32 *)(state + 0x88) |= 2;
        if (*(s16 *)(state + 0x24) == 0) {
            *(s16 *)(state + 0x24) = 1;
            *(float *)(state + 0x20) = 1.0f;
        }
        func_002A7750(arg, 1, 0);
        if (arg[0x43])
            func_PAL_002A7E68(arg, 0, 0, 0);
        state[0x48] = func_00283CF0(18.0f);
        state[0x4A] = func_00283CF0(16.0f);
        *(float *)(state + 0x358) = *(float *)(arg + 0x18);
    }
    if (arg[0x31] && func_00282E48(arg + 0x10, D_L16_001B9B00) < 32.0f) {
        func_002A93B0(arg);
        arg[0x6F] = 30;
    }
    if (func_PAL_002B1A50(arg, state + 0x140, 0))
        func_L16_0040D188(arg);
    *(s32 *)(state + 0x240) = func_002B3BA8(arg, *(s32 *)(state + 0x230), *(float *)(state + 0x234), 0.0f, 0, 0);
    *(s32 *)(state + 0x354) = func_002B3BA8(arg, *(s32 *)(state + 0x350), 0.0f, 0.0f, 0, 0);
    *(float *)(arg + 0x18) = *(float *)(state + 0x358);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L16_00411E88);
