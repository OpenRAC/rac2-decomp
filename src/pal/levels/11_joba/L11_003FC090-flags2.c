#include "include_asm.h"

#include "common.h"
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 g_moby_group_flags[][16];
extern u8 g_sound_l11_slot_table[];
extern s32 PlayMobySound(s32,s32,u8 *);
extern void snd_stop_voice(s32);
extern void vec_scale_to_length(void *,void *,f32);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(f32 *,const f32 *,const f32 *);
extern s32 IsPointInCuboid(void *, s32);
extern f32 IntToFloat(s32);
extern s32 math_fast_float_d(void *);

void func_PAL_L11_003FC670(u8 *arg0) {
    f32 tmp[4];
    f32 duration;
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    u8 *s2 = g_moby_l11_table[0] + *(s32 *)(s1 + 0x6C) * 256;
    if (g_moby_group_flags[g_current_map_index[0]][*(u8 *)(s0 + 0xB0)] & 0x80) return;
    if (*(u8 *)(s0 + 0x20) == 0) {
        if (*(s16 *)(s0 + 0xAA) == 0xB71) *(u32 *)(s1 + 0x5C) |= 1;
        *(u8 *)(s0 + 0x20) = 1;
    }
    if (*(u8 *)(s0 + 0x20) == 1) {
        if (IsPointInCuboid(s2 + 0x10, *(s32 *)(s1 + 0x60))) {
            u8 *v;
            *(u8 *)(s0 + 0x20) = 2;
            v = g_sound_l11_slot_table + *(s32 *)(s1 + 0x70) * 0x70;
            if (*(u8 **)(v + 0x88) != s0 || *(u8 *)(v + 0x74) == 0)
                *(s32 *)(s1 + 0x70) = PlayMobySound(0, 4, s0);
            *(s32 *)(s1 + 0x64) = 37;
        }
    }
    if (*(u8 *)(s0 + 0x20) == 2) {
        qcopy(tmp, s0 + 0xC0);
        duration = IntToFloat(37);
        duration = *(f32 *)(s1 + 0x68) / duration;
        vec_scale_to_length(tmp, tmp, duration);
        FastVecAdd(s0 + 0x10, s0 + 0x10, tmp);
        if (math_fast_float_d(s1 + 0x64)) {
            s32 sound = *(s32 *)(s1 + 0x70);
            if (sound != -1) {
                u8 *v = g_sound_l11_slot_table + sound * 0x70;
                if (*(u8 **)(v + 0x88) == s0 && *(u8 *)(v + 0x74)) snd_stop_voice(sound);
            }
            *(s32 *)(s1 + 0x70) = -1;
            *(u8 *)(s0 + 0x20) = 3;
        }
    }
    if (*(u8 *)(s0 + 0x20) == 3) {
        if (!IsPointInCuboid(s2 + 0x10, *(s32 *)(s1 + 0x60))) {
            u8 *v = g_sound_l11_slot_table + *(s32 *)(s1 + 0x70) * 0x70;
            if (*(u8 **)(v + 0x88) != s0 || *(u8 *)(v + 0x74) == 0)
                *(s32 *)(s1 + 0x70) = PlayMobySound(0, 4, s0);
            *(u8 *)(s0 + 0x20) = 4;
            *(s32 *)(s1 + 0x64) = 37;
        }
    }
    if (*(u8 *)(s0 + 0x20) == 4) {
        qcopy(tmp, s0 + 0xC0);
        duration = IntToFloat(37);
        duration = *(f32 *)(s1 + 0x68) / duration;
        vec_scale_to_length(tmp, tmp, duration);
        FastVecSub((f32 *)(s0 + 0x10), (f32 *)(s0 + 0x10), tmp);
        if (math_fast_float_d(s1 + 0x64)) {
            s32 sound = *(s32 *)(s1 + 0x70);
            if (sound != -1) {
                u8 *v = g_sound_l11_slot_table + sound * 0x70;
                if (*(u8 **)(v + 0x88) == s0 && *(u8 *)(v + 0x74)) snd_stop_voice(sound);
            }
            *(s32 *)(s1 + 0x70) = -1;
            *(u8 *)(s0 + 0x20) = 1;
        }
    }
}
