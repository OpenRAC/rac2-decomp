#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L16_003F9F10);

INCLUDE_ASM("asm/pal/levels", func_PAL_L16_00408420);


#include "common.h"
extern s32 func_313EA0(s32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_L07_00321D68(void *, void *);
extern u8 *D_L16_001B2C0C[] __attribute__((sda));
extern u8 D_0013963B;
extern s32 func_00282948(void *);
extern u8 *D_L16_001FE7C0[];
extern s32 func_00283CF0(float);
extern s32 func_002B0ED8(void *, void *, s32);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern s32 D_L16_001B2B38[] __attribute__((sda));
extern s32 func_002A9640(void *, s32, s32);
extern s32 func_00277258(void *, s32, void *, float);

/* Steers the object toward the next point of its path (the state's table and cursor at
   0x294/0x2A4); advances the cursor once within half a unit, and returns 1 when the path is done. */
s32 func_PAL_L16_004099C0(u8 *moby)
{
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = D_L16_001FE7C0[*(s32 *)(state + 0x294)];

    if (*(s32 *)(state + 0x2A4) >= *(s32 *)path)
        return 1;
    qcopy(point, path + 16 + *(s32 *)(state + 0x2A4) * 16);
    func_00282CF0(step, point, moby + 0x10);
    func_00282F20(step, step, 0.24000001f);
    func_L07_00321D68(moby, step);
    if (*(s32 *)(state + 0x2AC) != 0) {
        if (func_00282E48(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    } else {
        if (func_00282E80(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    }
    return 0;
}


