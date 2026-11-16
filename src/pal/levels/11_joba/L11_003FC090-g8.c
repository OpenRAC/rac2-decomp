#include "include_asm.h"

#include "common.h"
extern s32 FloatToInt(f32 a0);
extern u8 *g_moby_l11_table;
extern u8 g_sound_l11_slot_table[];
extern void *g_group_id_lists[];
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern s32 PlayMobySound(s32, s32, u8 *);
extern void snd_stop_voice(s32);
extern s32 g_pulsing_platform_trigger_counter __attribute__((sda));

/* Once the linked object is in state 2 and the shared step counter is in phase, moves the object
   through one cycle along its vector from its start position, keeping its sound playing; when its
   trigger value is set, flags the objects of the two listed groups (0xCF5, 0xCF6, 0xD07) and sets
   its own state to 4.
   The two sound lookups are separate values, and the early exits return without stepping the
   shared counter, as retail does. */
void func_PAL_L11_003FC090(u8 *arg0) {
    f32 tmp[4];
    u8 *base = g_moby_l11_table;
    u8 *self = arg0;
    u8 *vars = *(u8 **)(self+0x68);
    u8 *target = base + *(s32 *)(vars+8)*256;
    u8 *entry;
    s16 *list;
    s16 *start;
    u8 *obj;
    switch (*(u8 *)(self+0x20)) {
    case 0:
        *(u8 *)(self+0x20) = 1;
        *(f32 *)(vars+0xC) = 3.1415927410125732f;
        *(s32 *)(vars+0x10) = 0;
        g_pulsing_platform_trigger_counter = 0;
        qcopy(vars+0x20,self+0x10);
        *(s32 *)(vars+0x1C) = 0;
        /* fall through */
    case 1:
        if (*(s32 *)vars && *(u8 *)(target+0x20) == 2 &&
            g_pulsing_platform_trigger_counter == FloatToInt(*(f32 *)(vars+4)*15.0f)) {
            *(u8 *)(self+0x20) = 2;
            *(f32 *)(vars+0xC) = 3.1415927410125732f;
            *(s32 *)(vars+0x10) = 0;
        }
        break;
    case 2: {
        s32 handle;
        *(f32 *)(vars+0x10) += 0.062831864f;
        *(f32 *)(vars+0xC) = FastAddRotations(*(f32 *)(vars+0xC),0.062831864f);
        handle = *(s32 *)(vars+0x30);
        entry = g_sound_l11_slot_table + handle * 0x70;
        if (*(u8 **)(entry+0x88) != self || !*(u8 *)(entry+0x74))
            *(s32 *)(vars+0x30) = PlayMobySound(0,4,self);
        if (*(f32 *)(vars+0x10) >= 6.2831854820251465f) {
            if (*(u8 *)(target+0x20) != 2) {
                *(u8 *)(self+0x20) = 1;
                if (*(s32 *)(vars+0x30) != -1) {
                    u8 *sound = g_sound_l11_slot_table + *(s32 *)(vars+0x30)*0x70;
                    if (*(u8 **)(sound+0x88) == self && *(u8 *)(sound+0x74))
                        snd_stop_voice(*(s32 *)(vars+0x30));
                }
                *(s32 *)(vars+0x30) = -1;
            }
            *(s32 *)(vars+0x10) = 0;
            *(f32 *)(vars+0xC) = 3.1415927410125732f;
            qcopy(self+0x10,vars+0x20);
        } else {
            vec_scale_to_length(tmp,self+0xD0,-(math_fast_sin_or_cos_a(*(f32 *)(vars+0xC))+1.0f)*2.2f);
            FastVecAdd(self+0x10,tmp,vars+0x20);
        }
        break;
    }
    }
    if (*(f32 *)(vars+4) == 1337.0f) {
        if (*(u8 *)(target+0x20) == 2) {
            if (*(s32 *)(vars+0x1C) == 0) {
                *(s32 *)(vars+0x1C) = 1;
                if (*(s32 *)(vars+0x14) == 255 || (start = g_group_id_lists[*(s32 *)(vars+0x14)]) == 0) {
                    *(u8 *)(self+0x20) = 4;
                    return;
                }
                list = start;
                do {
                    obj = g_moby_l11_table + ((*list & 0x7FFF) << 8);
                    if (*(s8 *)(obj+0x20) >= 0) {
                        s32 kind = *(s16 *)(obj+0xAA);
                        if (kind == 0xCF5) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xCF6) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xD07) *(u8 *)(obj+0x95) = 1;
                    }
                } while (*list++ >= 0);
                if (*(s32 *)(vars+0x18) == 255 || (start = g_group_id_lists[*(s32 *)(vars+0x18)]) == 0) {
                    *(u8 *)(self+0x20) = 4;
                    return;
                }
                list = start;
                do {
                    obj = g_moby_l11_table + ((*list & 0x7FFF) << 8);
                    if (*(s8 *)(obj+0x20) >= 0) {
                        s32 kind = *(s16 *)(obj+0xAA);
                        if (kind == 0xD07) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xCF6) *(u8 *)(obj+0x95) = 1;
                        else if (kind == 0xCF5) *(u8 *)(obj+0x95) = 1;
                    }
                } while (*list++ >= 0);
                *(u8 *)(self+0x20) = 4;
            }
            if (++g_pulsing_platform_trigger_counter > 104) g_pulsing_platform_trigger_counter = 0;
        } else g_pulsing_platform_trigger_counter = 0;
    }
}

extern void func_PAL_L01_002EBFB8(s32, s32, s32, s32, s32);
extern s32 IsPointInCuboid(void *, s32);
extern s32 math_fast_float_d(void *);
extern s32 func_PAL_00289730(s32, s32);
extern u16 g_level_id_word NOT_SDA;
extern u16 g_level_flag_word NOT_SDA;
extern u16 g_arena_flag_word NOT_SDA;
extern s32 g_arena_progress_level __attribute__((sda));
extern u8 g_hero_position[];
extern u8 g_inventory_have_flags[0x38] __attribute__((sda));
extern s32 g_arena_l11_active_flag[] __attribute__((sda));

/* Queues Joba subtitles when inventory and cuboid gates permit, with retry timers. */
void func_PAL_L11_00417778(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);

    if (*(u8 *)(object + 0x20) == 0) {
        *(u8 *)(object + 0x20) = 1;
        *(u8 *)(object + 0x30) = 0xFF;
        *(s32 *)(state + 0x8) = 0x15E;
        *(s32 *)(state + 0x10) = 0xFA;
    }
    if (*(u8 *)(object + 0x20) != 1) {
        return;
    }
    if (g_inventory_have_flags[0]) {
        func_PAL_L01_002EBFB8(0x9FF, 0x56, 3, *(s32 *)(state + 0x4), -1);
    }
    if (g_arena_l11_active_flag[0] != 0 && g_arena_progress_level >= 3) {
        g_level_id_word = 0xFFFF;
    }
    if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 0x0)) != 0) {
        if (math_fast_float_d(state + 0x8) != 0) {
            if (g_level_flag_word == 0) {
                func_PAL_00289730(0xA00, 0x57);
                *(s32 *)(state + 0x8) = 0x15E;
            }
        }
    }
    if (g_inventory_have_flags[0x2E]) {
        func_PAL_L01_002EBFB8(0xA03, 0x5A, 0, *(s32 *)(state + 0xC), -1);
    }
    if (g_inventory_have_flags[0xB]) {
        if (g_arena_flag_word == 0) {
            if (math_fast_float_d(state + 0x10) != 0) {
                func_PAL_00289730(0xA3D, 0x94);
            }
        }
    }
}
