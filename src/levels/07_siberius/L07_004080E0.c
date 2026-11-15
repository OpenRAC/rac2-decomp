#include "common.h"
extern void func_002A7750(void *, s32, s32);
extern u8 *func_002A9640(void *, s32, s32);
extern f32 func_00282E48(void *, void *);
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern void func_002E5CF8(s32, s32, void *);
extern void func_L00_0032A258(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L07_00408338(void *);
extern void func_002E5E58(s32, s32, s32);
extern void func_002B0A18(s32, s32);
extern s32 func_00282948(void *);
extern void func_0029F338(void *);
extern u8 D_L07_001B1540[16] __attribute__((sda));
extern u8 D_L07_001B1538[8] __attribute__((sda));
extern u8 D_L07_001B1530[8] __attribute__((sda));
extern s32 D_L07_001B1560 __attribute__((sda));
/* The byte is read through an absolute macro and written through a split address. */
extern u8 D_001A7A70 __attribute__((nosda));
extern u8 D_001A7A70_read[] __asm__("D_001A7A70") __attribute__((sda));
extern s32 D_L07_001A903C[] __attribute__((sda));
extern f32 D_L07_001B3198 __attribute__((sda));
extern f32 D_L07_001AA698 __attribute__((sda));

/* Updates a Siberius trigger object (moby class 3943): waits for a touch, plays an effect and sound once, then removes itself after a timer. */
void func_L07_004080E0(u8 *moby)
{
    f32 myPos[4], targetPos[4];
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *target;
    s32 blocked;
    switch (moby[0x20]) {
    case 0:
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (!*(s32 *)vars) {
            target = FindOwnedEffectSlot(moby, 0x4010000, 0);
            if (target) {
                qcopy(myPos, moby + 0x10);
                myPos[2] += 0.5f;
                blocked = 1;
                if (*(u8 **)(target + 0x20)) {
                    qcopy(targetPos, *(u8 **)(target + 0x20) + 0x10);
                    targetPos[2] += 0.5f;
                    if (fast_vec_dist(targetPos, myPos) < 64.0f) {
                        blocked = 0;
                        if (!CollLine(targetPos, myPos, 2, moby, 0)) blocked = 1;
                    }
                }
                if (blocked) SetMobyState(moby, 2, -1);
            }
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        PlayMobySound(0, 0, moby);
        ExplodeObjectIntoPieces(moby, D_L07_001B1540, D_L07_001B1538, D_L07_001B1530, 0xFFF, -1, D_L07_001B1560, 16, 0xFFFF, 0xFF, 0);
        SpawnSparkBurst_L07(moby);
        *(s32 *)(vars + 4) = 480;
        if (!D_001A7A70_read[0]) {
            D_001A7A70 = 1;
            PlaySoundFromGlobalBank(1, 0, 0);
            SetEntryValueByIndex(0x1233, -1);
            D_L07_001A903C[0] = 1;
        }
        if (D_L07_001B1560 >= 0) *(u16 *)(moby + 0x7C) = (1 << D_L07_001B1560) | 0x8000;
        else *(u16 *)(moby + 0x34) |= 0x41;
        SetMobyState(moby, 3, -1);
        break;
    case 3:
        if (FastFloatHelperD(vars + 4)) {
            D_L07_001AA698 = D_L07_001B3198;
            MarkMobySpawned(moby);
        }
        break;
    }
}
