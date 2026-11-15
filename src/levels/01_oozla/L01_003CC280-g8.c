#include "common.h"

extern void swamp_monster_release_attack_slot(u8 *);
extern s32 FloatToInt(f32);
extern void moby_set_state(u8 *, s32, s32);
extern u8 *g_moby_l01_table;
extern s32 D_L01_001B2578[] __attribute__((sda));
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern u16 *D_L01_001FB020[];
extern u8 g_hero_position[], D_L01_001B94C0[];
extern u8 D_L01_001AFE18[] __attribute__((sda));
extern f32 D_L01_001B2F40;
extern u8 *part_find_owned_effect_slot(void *, s32, s32);
extern f32 moby_update_aim_target_strength(void *, void *);
extern u8 *moby_get_private_value_0(void *);
extern void gfx_start_color_fade(void *, void *);
extern void gfx_update_color_fade(void *, void *);
extern void anim_start_blended(void *, s32, s32, s32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern s32 math_random_int_below(s32);
extern void vec_add_random_offset(void *, f32);
extern f32 level_get_water_height(void);
extern f32 math_random_float_range(f32, f32);
extern void part_spawn_drifting(void *, void *, u32, f32, f32);
extern void weapon_select_aim_target(void *, s32, s32, s32, f32, f32);
extern f32 fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);

/* Applies incoming damage to the linked group or this object's timer, updates its
   animation and effects, and adjusts the nearby-object reaction and height.
   The isolated profile retains the timer branch's state + 0x50 calculation and
   keeps the shared floating-point branch labels on their hazard nops. */
/* Handles damage to the swamp monster parts and reacts with hit animations, pushes and bubbles. */
void UpdateOozlaLinkedGroupDamage(u8 *moby)
{
    u8 pos[16] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *attacker, *group_member, *hit_record, *linked;
    u16 *member_list;
    f32 damage, push_strength;
    s32 hit_duration, other_state, ignores_hit;
    s32 particle_color;
    u16 class_id;

    if (moby[0x95] == 1 || ((moby[0x95] >= 5 && moby[0x95] <= 6) && 0.0f < *(f32 *)(state + 0x20))) {
        attacker = part_find_owned_effect_slot(moby, 0x10000, 0);
        if (*(short *)(state + 0x26) >= 1)
            attacker = 0;
        damage = moby_update_aim_target_strength(moby, attacker);
        if (attacker && 0.0f < damage && moby[0x95] >= 5) {
            if (*(s32 *)(state + 0xB0) != -1) {
                *(s32 *)(state + 0xC0) = 240;
                if (moby[0x21] != 0xFF) {
                    class_id = *(u16 *)(*(u8 **)(attacker + 0x20) + 0xAA);
                    hit_duration = (class_id == 0xCE4 /* moby class 3300 */ || class_id == 0xCE5 /* moby class 3301 */) ? 60 : 0;
                    for (member_list = D_L01_001FB020[moby[0x21]];
                         moby[0x21] != 0xFF && moby[0x21] <= D_L01_001B2578[0] && member_list &&
                         ((member_list != 0 && (short)member_list[-1] >= 0) || member_list == D_L01_001FB020[moby[0x21]]); member_list++) {
                        group_member = g_moby_l01_table + ((*member_list & 0x7FFF) << 8);
                        if (!group_member)
                            break;
                        hit_record = moby_get_private_value_0(group_member);
                        if (hit_record) {
                            *(u16 *)(hit_record + 6) = hit_duration;
                            *(f32 *)hit_record -= damage;
                            hit_record[0x17] = state[0x37];
                            *(s32 *)(hit_record + 0x18) = *(s32 *)(state + 0x38);
                            *(u16 *)(hit_record + 0x1C) = *(u16 *)(state + 0x3C);
                        }
                        group_member[0xA8] = 0xFF;
                    }
                }
            } else {
                *(f32 *)(state + 0x20) -= damage;
            }
        }
        moby[0xA8] = 0xFF;

        if (0.0f < damage) {
            state[0x57] = FloatToInt(damage * 20.0f) + 100;
            gfx_start_color_fade(moby, state + 0x50);
        }
        if (moby[0x95] == 1 && attacker) {
            *(s32 *)(state + 0xBC) = 0;
            if (moby[0x20] == 0)
                moby_set_state(moby, 1, -1);
        } else {
            if (*(f32 *)(state + 0x20) < 0.0f ||
                (*(s32 *)(state + 0xB0) != -1 && (!(linked = D_L01_001B255C_base[0] + (*(s32 *)(state + 0xB0) << 8)) || (other_state = linked[0x20]) == 0xFE || other_state == 0xFD))) {
                swamp_monster_release_attack_slot(moby);
                if (moby[0x43] != 4)
                    anim_start_blended(moby, 4, 0, 10);
                *(u32 *)(state + 0x20) = 0;
                *(u16 *)(moby + 0x34) &= 0xEFFF;
                moby_set_state(moby, 0, 7);
            } else {
                ignores_hit = 0;
                if (attacker && *(u8 **)(attacker + 0x20))
                    ignores_hit = *(short *)(*(u8 **)(attacker + 0x20) + 0xAA) == 0x47 /* moby class 71 */;
                if (!ignores_hit) {
                    if (1.0f <= damage) {
                        swamp_monster_release_attack_slot(moby);
                        if (moby[0x42] == 1) {
                            if (moby[0x43] != 3)
                                anim_start_blended(moby, 3, 5, 5);
                        } else if (moby[0x42] == 2) {
                            if (moby[0x43] != 3)
                                anim_start_blended(moby, 3, 0, 20);
                        } else if (moby[0x43] != 3) {
                            anim_start_blended(moby, 3, 2, 10);
                        }
                        *(u16 *)(moby + 0x34) &= 0xEFFF;
                        moby_set_state(moby, 0, 7);
                    }
                    if (0.1f < damage) {
                        FastVecSub(state + 0xA0, moby + 0x10, g_hero_position);
                        push_strength = (damage + damage + 3.0f) * 0.016666668f;
                        if (0.20000002f < push_strength)
                            push_strength = 0.20000002f;
                        vec_scale_to_length(state + 0xA0, state + 0xA0, push_strength);
                        *(s32 *)(state + 0xA8) = 0;
                    }
                }
            }
        }
    } else {
        moby[0xA8] = 0xFF;
    }
    gfx_update_color_fade(moby, state + 0x50);
    if (0.0f < *(f32 *)(moby + 0x48) && moby[0x95] != 2 && moby[0x31] && math_random_int_below(9) == 0) {
        qcopy(pos, moby + 0x10);
        vec_add_random_offset(&pos, 0.15f);
        ((f32 *)pos)[2] = level_get_water_height();
        damage = math_random_float_range(0.5f, 3.0f);
        particle_color = ((math_random_int_below(6) + 20) << 24) | 0x5060;
        part_spawn_drifting(&pos, D_L01_001AFE18, particle_color, damage, 12000.0f);
    }
    weapon_select_aim_target(moby, *(s32 *)(state + 0xF0), 0, moby[0x95] < 5, 0.0f, 0.0f);
    other_state = moby[0x31];
    if (other_state && fast_vec_dist(moby + 0x10, D_L01_001B94C0) < 48.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 45;
    }
    *(f32 *)(moby + 0x74) = 1.0f;
    *(f32 *)(moby + 0x70) = 109.0f - *(f32 *)(moby + 0x18);
    if (moby[0x95] >= 3 && moby[0x95] <= 7)
        D_L01_001B2F40 = 0.20943953f;
}
