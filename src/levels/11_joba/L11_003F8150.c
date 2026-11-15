#include "common.h"
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 D_0019B2E8[][16];
extern u8 D_L11_00188660[];
extern s32 PlayMobySound(s32,s32,u8 *);
extern void snd_stop_voice(s32);
extern void vec_scale_to_length(void *,void *,f32);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(f32 *,const f32 *,const f32 *);
extern s32 IsPointInCuboid(void *, s32);
extern f32 IntToFloat(s32);
extern s32 math_fast_float_d(void *);
/* Slides the object one way while its trigger object is active, then back the other way when it stops, playing a sound while it moves. */
void joba_sliding_door_update(u8 *moby_arg) {
    f32 step[4];
    f32 duration;
    u8 *moby = moby_arg;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *trigger_moby = g_moby_l11_table[0] + *(s32 *)(vars + 0x6C) * 256;
    if (D_0019B2E8[g_current_map_index[0]][*(u8 *)(moby + 0xB0)] & 0x80) return;
    if (*(u8 *)(moby + 0x20) == 0) {
        if (*(s16 *)(moby + 0xAA) == 0xB71 /* moby class 2929 */) *(u32 *)(vars + 0x5C) |= 1;
        *(u8 *)(moby + 0x20) = 1;
    }
    if (*(u8 *)(moby + 0x20) == 1) {
        if (IsPointInCuboid(trigger_moby + 0x10, *(s32 *)(vars + 0x60))) {
            u8 *sound_slot;
            *(u8 *)(moby + 0x20) = 2;
            sound_slot = D_L11_00188660 + *(s32 *)(vars + 0x70) * 0x70;
            if (*(u8 **)(sound_slot + 0x88) != moby || *(u8 *)(sound_slot + 0x74) == 0)
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
        if (math_fast_float_d(vars + 0x64)) {
            s32 sound = *(s32 *)(vars + 0x70);
            if (sound != -1) {
                u8 *sound_slot = D_L11_00188660 + sound * 0x70;
                if (*(u8 **)(sound_slot + 0x88) == moby && *(u8 *)(sound_slot + 0x74)) snd_stop_voice(sound);
            }
            *(s32 *)(vars + 0x70) = -1;
            *(u8 *)(moby + 0x20) = 3;
        }
    }
    if (*(u8 *)(moby + 0x20) == 3) {
        if (!IsPointInCuboid(trigger_moby + 0x10, *(s32 *)(vars + 0x60))) {
            u8 *sound_slot = D_L11_00188660 + *(s32 *)(vars + 0x70) * 0x70;
            if (*(u8 **)(sound_slot + 0x88) != moby || *(u8 *)(sound_slot + 0x74) == 0)
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
        if (math_fast_float_d(vars + 0x64)) {
            s32 sound = *(s32 *)(vars + 0x70);
            if (sound != -1) {
                u8 *sound_slot = D_L11_00188660 + sound * 0x70;
                if (*(u8 **)(sound_slot + 0x88) == moby && *(u8 *)(sound_slot + 0x74)) snd_stop_voice(sound);
            }
            *(s32 *)(vars + 0x70) = -1;
            *(u8 *)(moby + 0x20) = 1;
        }
    }
}
