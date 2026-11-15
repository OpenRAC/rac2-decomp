#include "include_asm.h"

#include "common.h"
extern u8 *D_001B251C __attribute__((sda));
extern u8 D_L10_00188660[];
extern void *state_get_stored_pointer_value(u8 *arg0);
extern void func_PAL_L10_0041D788(u8 *arg0);
extern void vec_clear_128(u8 *a0);
extern void level_append_object(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern u8 *moby_get_motion_data(u8 *arg0);
extern void func_PAL_L05_0037E8E0(u8 *a0);
extern s32 moby_process_collision_hit(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern void snd_stop_voice(s32 a0);
extern s32 snd_play_from_class_bank(s32 a, s32 b, u8 *c, s32 d);
extern void moby_check_player_in_view_and_range(u8 *a0, s32 a1, f32 f12);
extern void func_PAL_L10_0041D888(u8 *arg0);
extern s32 moby_can_take_next_step(u8 *a0);
extern void func_PAL_L05_0037DE20(u8 *a0);
extern int math_fast_float_d(u8 *a0);
extern void func_PAL_L10_0041D950(u8 *arg0);
extern void snd_stop_moby_effect(u8 *arg0);

void func_PAL_L10_0041D518(u8 *arg0) {
    u8 *s2 = *(u8 **)(arg0 + 0x68);
    u8 *s3;
    u8 *p;
    s32 id;
    s32 tmp[4];
    s32 one;

    if (arg0[0x20] == 0) {
        arg0[0x30] = 0xFF;
        if (state_get_stored_pointer_value(arg0) == 0)
            return;
        func_PAL_L10_0041D788(arg0);
        vec_clear_128((u8 *)tmp);
        if (*(s32 *)(s2 + 0x264) != 0)
            level_append_object(arg0, (s32)snd_stop_moby_effect, 0, 0);
        return;
    }
    s3 = moby_get_motion_data(arg0);
    if (*(s32 *)(s3 + 0x110) == 0)
        return;
    func_PAL_L05_0037E8E0(arg0);
    one = 1;
    if (moby_process_collision_hit(arg0, 0, 0, 0) == one) {
        id = *(s32 *)(s2 + 0x26C);
        if (id != -1) {
            p = D_L10_00188660 + id * 0x70;
            if (*(u8 **)(p + 0x88) == arg0 && p[0x74] != 0)
                snd_stop_voice(id);
        }
        *(s32 *)(s2 + 0x26C) = -1;
        snd_play_from_class_bank(2, 0, arg0, 0xF8E);
    }
    moby_check_player_in_view_and_range(arg0, 0, 176.0f);
    if (*(s32 *)(s3 + 0x110) == 1) {
        if (*(s32 *)(s2 + 0x260) != -1) {
            *(s32 *)(s3 + 0x11C) = *(s32 *)(s3 + 0x110);
            *(u8 **)(s3 + 0x120) = D_001B251C + (*(s32 *)(s2 + 0x260) << 8);
        }
        if (*(s32 *)(s3 + 0x104) != 0)
            func_PAL_L10_0041D888(arg0);
        if (moby_can_take_next_step(arg0) != 0)
            func_PAL_L05_0037DE20(arg0);
        math_fast_float_d(s2 + 0x268);
        func_PAL_L10_0041D950(arg0);
    }
    p = D_L10_00188660 + *(s32 *)(s2 + 0x26C) * 0x70;
    if (*(u8 **)(p + 0x88) != arg0 || p[0x74] == 0)
        *(s32 *)(s2 + 0x26C) = snd_play_from_class_bank(0, 6, arg0, 0xF8E);
}
