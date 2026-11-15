#include "common.h"

extern u8 D_00188660[];
extern u8 *D_L01_001B255C MACRO_ADDR;
extern u8 *D_L01_001FE180[];
extern f32 D_L01_001B0540 __attribute__((sda));

extern s32 func_L01_00337888(u8 *object, u8 *entry, void *out, s32 current, s32 direction, f32 step);
extern s32 func_002E5CF8(s32 a0, s32 a1, void *a2);
extern void func_0029F338(void *a0);
extern void func_00282CF0(void *a0, void *a1, void *a2);
extern void func_002AD6F0(void *a0, void *a1, void *a2, void *a3);

/* Moves a launched object along its path and removes it at the end. */
void func_L01_003D26C0(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *launcherVars = *(u8 **)(*(u8 **)(vars + 0x70) + 0x68);
    u8 *pathTable;
    u8 *soundHandle;
    f32 moveDelta[4];

    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * D_L01_001B0540;
    qcopy(vars + 0x60, moby + 0x10);
    pathTable = D_L01_001FE180[*(s32 *)(vars + 0x74)];
    *(s32 *)(vars + 0x78) =
        AdvancePointAlongPolyline(moby, pathTable, moby + 0x10, *(s32 *)(vars + 0x78), 1,
                          *(f32 *)(launcherVars + 0x20) * 0.016666668f);
    if (*(f32 *)(moby + 0x18) < *(f32 *)(vars + 0x68)) {
        if (!(*(u16 *)(vars + 0x7C) & 0x80)) {
            PlayMobySound(1, 0, moby);
            *(u16 *)(vars + 0x7C) = *(u16 *)(vars + 0x7C) | 0x80;
        }
        gMobyTable_L01[(*(s32 *)(*(u8 **)(*(u8 **)(vars + 0x70) + 0x68) + 0xC) << 8) + 0xBC] = 1;
    }
    soundHandle = gSoundState + *(s16 *)(vars + 0x7E) * 0x70;
    if (*(u8 **)(soundHandle + 0x88) != moby || soundHandle[0x74] == 0)
        *(s16 *)(vars + 0x7E) = PlayMobySound(0, 4, moby);
    if (*(s32 *)(vars + 0x78) == *(s32 *)pathTable - 1) {
        gMobyTable_L01[(*(s32 *)(*(u8 **)(*(u8 **)(vars + 0x70) + 0x68) + 0xC) << 8) + 0xBC] = 0;
        MarkMobySpawned(moby);
    } else {
        FastVecSub(moveDelta, moby + 0x10, vars + 0x60);
        CombineTransformsAndStore(vars + 0x20, moveDelta, moby + 0xF0, moby + 0xF0);
        qcopy(vars + 0x60, moby + 0x10);
    }
}
