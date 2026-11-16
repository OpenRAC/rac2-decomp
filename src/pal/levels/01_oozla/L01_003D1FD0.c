#include "include_asm.h"

#include "common.h"
extern void moby_mark_spawned(void *a0);
extern u32 g_hit_l01_result[];
extern u32 g_pHeroMoby[];
extern s32 func_3120A8(void *a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5,
                      u32 a6, f32 f12, f32 f13);
extern s32 func_355780(u32 a0, u32 a1, void *a2);
extern void moby_set_state(void *a0, s32 a1, s32 a2);
extern u8 *D_L01_001B255C_sda[] __attribute__((sda));
extern u8 *g_path_l01_table[];
extern u8 *g_moby_l01_table __attribute__((sda));
extern u32 g_level_l01_word_table[];
extern u8 g_swamp_cutscene_flag __attribute__((sda));
extern u8 g_subtitle_history[];
extern u8 g_cutscene_vars[];
extern u8 *g_swamp_patrol_positions __attribute__((sda));
extern u32 g_frame_counter __attribute__((sda));
extern void anim_start_blended_pal(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 math_closest_point_on_polygon_edge(void *a0, void *a1, void *a2, s32 a3);
extern s32 FloatToInt(f32 a0);
extern s32 g_swamp_monster_thresholds[] __attribute__((sda));
extern u16 *g_group_list_table[];
extern u8 g_hero_position[];
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern f32 moby_update_aim_target_strength_pal(void *, void *);
extern u8 *moby_get_private_value_0(u8 *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern f32 IntToFloat(s32);
extern void hud_start_overlay(s32, s32, f32);

/* While the owner's kind (+0x95) is 5 or 6 and its timer (+0x20) is positive, finds the entity
   func_002A9640 names (only when the state's halfword at +0x26 is below 1) and its distance
   f20 from func_PAL_002AA108; when that is positive, walks the id list of the owner's group and
   sets the effect record each entity hands out (func_002AB1F0: class-dependent 60 or 0 at +6,
   the distance taken off its float at +0), otherwise takes the distance off the timer. Then
   it runs the timer out (releasing the entity at +0xCC and switching to state 5), or, below it,
   enters state 4 for a distance of 1.0 or more and scales the vector at +0x90. At the end the
   shared update runs and the timer ratio is handed to func_L01_002F14E8. The function keeps
   the second `p != 0` guard of the walk; func_L01_003CDB40 returns a word, and the retail
   copy of the 0.2 limit holds one ulp more than 0.2f. */
void swamp_monster_apply_damage_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *owned_effect;
    u8 *target_effect;
    u8 *entity;
    u8 *record;
    u16 *group_entry;
    f32 strength;
    f32 push_speed;
    s32 effect_value;
    u16 cls;

    if (moby[0x95] >= 5 && moby[0x95] <= 6 && 0.0f < *(f32 *)(vars + 0x20)) {
        owned_effect = part_find_owned_effect_slot(moby, 0x10000, 0);
        target_effect = owned_effect;
        if (*(short *)(vars + 0x26) >= 1)
            target_effect = 0;
        strength = moby_update_aim_target_strength_pal(moby, target_effect);
        if (target_effect != 0 && 0.0f < strength) {
            if (moby[0x21] != 0xFF && *(s32 *)(vars + 0xA0) != -1) {
                cls = *(u16 *)(*(u8 **)(target_effect + 0x20) + 0xAA);
                effect_value = (cls == 0xCE4 || cls == 0xCE5) ? 50 : 0;
                for (group_entry = g_group_list_table[moby[0x21]];
                     moby[0x21] != 0xFF && moby[0x21] <= g_swamp_monster_thresholds[0] && group_entry != 0 &&
                     ((group_entry != 0 && (short)group_entry[-1] >= 0) || group_entry == g_group_list_table[moby[0x21]]);
                     group_entry++) {
                    entity = D_L01_001B255C_sda[0] + ((*group_entry & 0x7FFF) << 8);
                    if (entity == 0)
                        break;
                    record = moby_get_private_value_0(entity);
                    if (record != 0) {
                        *(u16 *)(record + 6) = effect_value;
                        *(f32 *)record = *(f32 *)record - strength;
                        record[0x17] = vars[0x37];
                        *(s32 *)(record + 0x18) = *(s32 *)(vars + 0x38);
                        *(u16 *)(record + 0x1C) = *(u16 *)(vars + 0x3C);
                    }
                    entity[0xA8] = 0xFF;
                }
            } else {
                *(f32 *)(vars + 0x20) = *(f32 *)(vars + 0x20) - strength;
            }
        }
        moby[0xA8] = 0xFF;
        if (*(f32 *)(vars + 0x20) < 0.0f) {
            if (*(s32 *)(vars + 0xCC) != -1)
                moby_mark_spawned(D_L01_001B255C_sda[0] + (*(s32 *)(vars + 0xCC) << 8));
            *(s32 *)(vars + 0xCC) = -1;
            if (moby[0x43] != 5)
                anim_start_blended_pal(moby, 5, 0, 10);
            *(f32 *)(vars + 0x20) = 0.0f;
            moby_set_state(moby, 0, 6);
            *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) & 0xEFFF;
        } else {
            if (1.0f <= strength) {
                *(s32 *)(vars + 0xBC) = 0xC8;
                if (moby[0x43] != 4)
                    anim_start_blended_pal(moby, 4, 0, 3);
                *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) & 0xEFFF;
                moby_set_state(moby, 0, 6);
            }
            if (0.1f < strength) {
                FastVecSub(vars + 0x90, moby + 0x10, g_hero_position);
                push_speed = (strength + strength + 3.0f) * 0.020000001f;
                if (0.24000001f < push_speed)
                    push_speed = 0.24000001f;
                vec_scale_to_length(vars + 0x90, vars + 0x90, push_speed);
                *(s32 *)(vars + 0x98) = 0;
            }
        }
    } else {
        moby[0xA8] = 0xFF;
    }
    swamp_monster_sync_linked_parts_health(moby);
    if (moby[0x95] >= 5 && moby[0x95] <= 6)
        hud_start_overlay(1, 0, *(f32 *)(vars + 0x20) / IntToFloat(*(short *)(vars + 0x24)));
}




