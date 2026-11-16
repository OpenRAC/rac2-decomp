#include "include_asm.h"

#include "common.h"
extern u8 *g_moby_pool_base __attribute__((sda));
extern u8 g_effect_l10_record_table[];
extern void *state_get_stored_pointer_value(u8 *arg0);
extern void hrugis_init_flying_piece_pal(u8 *arg0);
extern void vec_clear_128(u8 *a0);
extern void level_append_object(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern u8 *moby_get_motion_data(u8 *arg0);
extern void follower_l05_update_pal(u8 *a0);
extern s32 moby_process_collision_hit(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern void snd_stop_voice(s32 a0);
extern s32 snd_play_from_class_bank(s32 a, s32 b, u8 *c, s32 d);
extern void moby_check_player_in_view_and_range(u8 *a0, s32 a1, f32 f12);
extern void hrugis_start_timed_effect_pal(u8 *arg0);
extern s32 moby_can_take_next_step(u8 *a0);
extern void follower_start_wander_pal(u8 *a0);
extern int math_fast_float_d(u8 *a0);
extern void part_spawn_small_tail_trail_pal(u8 *arg0);
extern void snd_stop_moby_effect(u8 *arg0);

/* Updates the mission target ship: sets it up in state 0, then handles hits, the tail trail, the timed effect and its engine sound (PAL copy of mission_target_ship_update). */
void mission_target_ship_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *motion;
    u8 *sound;
    s32 voice;
    s32 zero[4];
    s32 one;

    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        if (state_get_stored_pointer_value(moby) == 0)
            return;
        hrugis_init_flying_piece_pal(moby);
        vec_clear_128((u8 *)zero);
        if (*(s32 *)(vars + 0x264) != 0)
            level_append_object(moby, (s32)snd_stop_moby_effect, 0, 0);
        return;
    }
    motion = moby_get_motion_data(moby);
    if (*(s32 *)(motion + 0x110) == 0)
        return;
    follower_l05_update_pal(moby);
    one = 1;
    if (moby_process_collision_hit(moby, 0, 0, 0) == one) {
        voice = *(s32 *)(vars + 0x26C);
        if (voice != -1) {
            sound = g_effect_l10_record_table + voice * 0x70;
            if (*(u8 **)(sound + 0x88) == moby && sound[0x74] != 0)
                snd_stop_voice(voice);
        }
        *(s32 *)(vars + 0x26C) = -1;
        snd_play_from_class_bank(2, 0, moby, 0xF8E);
    }
    moby_check_player_in_view_and_range(moby, 0, 176.0f);
    if (*(s32 *)(motion + 0x110) == 1) {
        if (*(s32 *)(vars + 0x260) != -1) {
            *(s32 *)(motion + 0x11C) = *(s32 *)(motion + 0x110);
            *(u8 **)(motion + 0x120) = g_moby_pool_base + (*(s32 *)(vars + 0x260) << 8);
        }
        if (*(s32 *)(motion + 0x104) != 0)
            hrugis_start_timed_effect_pal(moby);
        if (moby_can_take_next_step(moby) != 0)
            follower_start_wander_pal(moby);
        math_fast_float_d(vars + 0x268);
        part_spawn_small_tail_trail_pal(moby);
    }
    sound = g_effect_l10_record_table + *(s32 *)(vars + 0x26C) * 0x70;
    if (*(u8 **)(sound + 0x88) != moby || sound[0x74] == 0)
        *(s32 *)(vars + 0x26C) = snd_play_from_class_bank(0, 6, moby, 0xF8E);
}
