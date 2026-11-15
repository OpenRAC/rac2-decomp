#include "common.h"

extern s32 D_L13_001B1618 __attribute__((sda));
extern s32 D_L13_001B1630 __attribute__((sda));
extern s32 D_L13_001B1628 __attribute__((sda));
extern s32 D_L13_001B1634 __attribute__((sda));
extern s32 func_00283DB8(void *a0, f32 f12);
extern s32 func_00282978(void *a0);
extern void func_L13_0041A550(u8 *a0);
extern void func_L13_0041AB30(u8 *a0);
extern void func_L00_002E6EF8(void *a0, u8 *a1);
extern u8 func_L13_0041AD00[];

typedef struct {
    f32 f[4];
} __attribute__((aligned(16))) L13_Quad;

/* Runs the beam machine: while on screen it makes a new lightning beam, ticks it, and plays its sound. */
void func_L13_0041A398(u8 *moby)
{
    u8 *vars;
    s32 one;
    L13_Quad checkPos;

    vars = *(u8 **)(moby + 0x68);
    if (moby[0x20] != 0) {
        qcopy(&checkPos, moby + 0x10);
        checkPos.f[3] = *(f32 *)(vars + 0x624);
        if (FastMathHelperA(&checkPos, 52.0f) < 0)
            return;
    }
    if (*(s32 *)(vars + 0x628) == 0)
        return;
    one = 1;
    switch (moby[0x20]) {
    case 0:
        BuildLightningBeam(moby);
        *(u16 *)(vars + 0x10) = *(u16 *)(vars + 0xC);
        moby[0x20] = 2;
        *(f32 *)(vars + 0x624) = 2.5f;
        *(s16 *)(vars + 8) = one;
        *(s16 *)(vars + 0xA) = one;
        break;
    case 1:
        if (D_L13_001B1618 != 0 && *(s16 *)(vars + 0x12) == 0) {
            D_L13_001B1618 = D_L13_001B1618 - 1;
            BuildLightningBeam(moby);
        }
        break;
    case 2:
        if (FastDecTimer(vars + 0x10) != 0) {
            moby[0x20] = 3;
            *(u16 *)(vars + 0x10) = *(u16 *)(vars + 4);
            BuildLightningBeam(moby);
        }
        break;
    case 3:
        if (FastDecTimer(vars + 0x10) != 0) {
            if (*(s16 *)(vars + 6) != 0)
                moby[0x20] = 2;
            *(s16 *)(vars + 0x10) = 5;
        } else if (*(s16 *)(vars + 0x12) == 0) {
            BuildLightningBeam(moby);
        }
        break;
    }
    if (*(s16 *)(vars + 0x12) != 0) {
        if (D_L13_001B1630 == 0)
            UpdateStreakEffect_L13(moby);
        if (D_L13_001B1628 < *(s16 *)(vars + 0x12) && D_L13_001B1634 == 0)
            AddDrawCallbackToList3(DrawElectricBeam, moby);
    }
}
