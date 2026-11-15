#include "common.h"
extern u8 *D_L11_001B359C[] __attribute__((sda));
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B2E8[][16];
extern u8 D_L11_00188660[];
extern s32 func_002E5CF8(s32,s32,u8 *);
extern void func_002E59F8(s32);
extern void func_00282F20(void *,void *,f32);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(f32 *,const f32 *,const f32 *);
extern s32 func_002ACBC8(void *, s32);
extern f32 func_00283CE0(s32);
extern s32 func_00282948(void *);
/* Slides the object one way while its trigger object is active, then back the other way when it stops, playing a sound while it moves. */
void func_L11_003F8150(u8 *mobyArg) {
    f32 step[4];
    f32 duration;
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *triggerMoby = gMobyTable_L11[0] + *(s32 *)(vars + 0x6C) * 256;
    if (D_0019B2E8[gCurrentMapIndex[0]][*(u8 *)(moby + 0xB0)] & 0x80) return;
    if (*(u8 *)(moby + 0x20) == 0) {
        if (*(s16 *)(moby + 0xAA) == 0xB71 /* moby class 2929 */) *(u32 *)(vars + 0x5C) |= 1;
        *(u8 *)(moby + 0x20) = 1;
    }
    if (*(u8 *)(moby + 0x20) == 1) {
        if (IsPointInCuboid(triggerMoby + 0x10, *(s32 *)(vars + 0x60))) {
            u8 *soundSlot;
            *(u8 *)(moby + 0x20) = 2;
            soundSlot = D_L11_00188660 + *(s32 *)(vars + 0x70) * 0x70;
            if (*(u8 **)(soundSlot + 0x88) != moby || *(u8 *)(soundSlot + 0x74) == 0)
                *(s32 *)(vars + 0x70) = PlayMobySound(0, 4, moby);
            *(s32 *)(vars + 0x64) = 45;
        }
    }
    if (*(u8 *)(moby + 0x20) == 2) {
        qcopy(step, moby + 0xC0);
        duration = IntToFloat(45);
        duration = *(f32 *)(vars + 0x68) / duration;
        vec_scale_to_length(step, step, duration);
        FastVecAdd(moby + 0x10, moby + 0x10, step);
        if (FastFloatHelperD(vars + 0x64)) {
            s32 sound = *(s32 *)(vars + 0x70);
            if (sound != -1) {
                u8 *soundSlot = D_L11_00188660 + sound * 0x70;
                if (*(u8 **)(soundSlot + 0x88) == moby && *(u8 *)(soundSlot + 0x74)) StopSoundVoice(sound);
            }
            *(s32 *)(vars + 0x70) = -1;
            *(u8 *)(moby + 0x20) = 3;
        }
    }
    if (*(u8 *)(moby + 0x20) == 3) {
        if (!IsPointInCuboid(triggerMoby + 0x10, *(s32 *)(vars + 0x60))) {
            u8 *soundSlot = D_L11_00188660 + *(s32 *)(vars + 0x70) * 0x70;
            if (*(u8 **)(soundSlot + 0x88) != moby || *(u8 *)(soundSlot + 0x74) == 0)
                *(s32 *)(vars + 0x70) = PlayMobySound(0, 4, moby);
            *(u8 *)(moby + 0x20) = 4;
            *(s32 *)(vars + 0x64) = 45;
        }
    }
    if (*(u8 *)(moby + 0x20) == 4) {
        qcopy(step, moby + 0xC0);
        duration = IntToFloat(45);
        duration = *(f32 *)(vars + 0x68) / duration;
        vec_scale_to_length(step, step, duration);
        FastVecSub((f32 *)(moby + 0x10), (f32 *)(moby + 0x10), step);
        if (FastFloatHelperD(vars + 0x64)) {
            s32 sound = *(s32 *)(vars + 0x70);
            if (sound != -1) {
                u8 *soundSlot = D_L11_00188660 + sound * 0x70;
                if (*(u8 **)(soundSlot + 0x88) == moby && *(u8 *)(soundSlot + 0x74)) StopSoundVoice(sound);
            }
            *(s32 *)(vars + 0x70) = -1;
            *(u8 *)(moby + 0x20) = 1;
        }
    }
}
