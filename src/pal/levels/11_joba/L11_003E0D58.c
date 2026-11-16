#include "include_asm.h"



#include "common.h"
extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);
extern s32 snd_is_voice_playing_for_owner(u8 *arg0, s32 arg1);
extern s32 PlayMobySound(s32 arg0, s32 arg1, u8 *arg2);
extern s32 FloatToInt(f32 arg0);
extern void moby_update_ground_check(u8 *arg0);
extern f32 fast_vec_dist(u8 *arg0, u8 *arg1);
extern void joba_enemy_init();
extern void joba_enemy_apply_damage(u8 *arg0);
extern void joba_enemy_update_state_machine(u8 *arg0);
extern void joba_enemy_update_orbit(u8 *arg0);
extern void joba_enemy_update_effects(u8 *arg0);
extern s32 joba_enemy_is_active(u8 *arg0);
extern u8 g_sound_l11_slot_table[];
extern u8 g_hero_l11_position[];
extern s32 g_hero_control_locked __attribute__((sda));
extern s32 g_hero_l11_input_blocked __attribute__((sda));
extern f32 vec_get_heading_angle(u8 *a0, f32 *a1, s32 a2);
extern f32 vec_distance_xy(u8 *a0, u8 *a1);
extern u8 g_hero_l11_state_data[];

void arachnoid_update_pal(u8 *arg0) {
    u8 *s0 = arg0;
    if (*(u8 *)(s0 + 0x20) == 0) {
        joba_enemy_init();
    } else {
        if (joba_enemy_is_active(s0) != 0)
            return;
        if (*(u8 *)(s0 + 0x31) != 0
            && fast_vec_dist(s0 + 0x10, g_hero_l11_position) < 48.0f) {
            moby_update_ground_check(s0);
            *(u8 *)(s0 + 0x6F) = 0x2D;
        }
        joba_enemy_apply_damage(s0);
        joba_enemy_update_state_machine(s0);
        joba_enemy_update_orbit(s0);
        joba_enemy_update_effects(s0);
    }
}

