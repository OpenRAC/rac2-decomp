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
extern void func_PAL_002A7E68(void *a0, s32 a1, s32 a2, s32 a3);
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
void func_PAL_L01_003D1FD0(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *ent;
    u8 *s0;
    u8 *e;
    u8 *r;
    u16 *p;
    f32 f20;
    f32 w;
    s32 s4;
    u16 cls;

    if (a0[0x95] >= 5 && a0[0x95] <= 6 && 0.0f < *(f32 *)(state + 0x20)) {
        ent = part_find_owned_effect_slot(a0, 0x10000, 0);
        s0 = ent;
        if (*(short *)(state + 0x26) >= 1)
            s0 = 0;
        f20 = moby_update_aim_target_strength_pal(a0, s0);
        if (s0 != 0 && 0.0f < f20) {
            if (a0[0x21] != 0xFF && *(s32 *)(state + 0xA0) != -1) {
                cls = *(u16 *)(*(u8 **)(s0 + 0x20) + 0xAA);
                s4 = (cls == 0xCE4 || cls == 0xCE5) ? 50 : 0;
                for (p = g_group_list_table[a0[0x21]];
                     a0[0x21] != 0xFF && a0[0x21] <= g_swamp_monster_thresholds[0] && p != 0 &&
                     ((p != 0 && (short)p[-1] >= 0) || p == g_group_list_table[a0[0x21]]);
                     p++) {
                    e = D_L01_001B255C_sda[0] + ((*p & 0x7FFF) << 8);
                    if (e == 0)
                        break;
                    r = moby_get_private_value_0(e);
                    if (r != 0) {
                        *(u16 *)(r + 6) = s4;
                        *(f32 *)r = *(f32 *)r - f20;
                        r[0x17] = state[0x37];
                        *(s32 *)(r + 0x18) = *(s32 *)(state + 0x38);
                        *(u16 *)(r + 0x1C) = *(u16 *)(state + 0x3C);
                    }
                    e[0xA8] = 0xFF;
                }
            } else {
                *(f32 *)(state + 0x20) = *(f32 *)(state + 0x20) - f20;
            }
        }
        a0[0xA8] = 0xFF;
        if (*(f32 *)(state + 0x20) < 0.0f) {
            if (*(s32 *)(state + 0xCC) != -1)
                moby_mark_spawned(D_L01_001B255C_sda[0] + (*(s32 *)(state + 0xCC) << 8));
            *(s32 *)(state + 0xCC) = -1;
            if (a0[0x43] != 5)
                func_PAL_002A7E68(a0, 5, 0, 10);
            *(f32 *)(state + 0x20) = 0.0f;
            moby_set_state(a0, 0, 6);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) & 0xEFFF;
        } else {
            if (1.0f <= f20) {
                *(s32 *)(state + 0xBC) = 0xC8;
                if (a0[0x43] != 4)
                    func_PAL_002A7E68(a0, 4, 0, 3);
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) & 0xEFFF;
                moby_set_state(a0, 0, 6);
            }
            if (0.1f < f20) {
                FastVecSub(state + 0x90, a0 + 0x10, g_hero_position);
                w = (f20 + f20 + 3.0f) * 0.020000001f;
                if (0.24000001f < w)
                    w = 0.24000001f;
                vec_scale_to_length(state + 0x90, state + 0x90, w);
                *(s32 *)(state + 0x98) = 0;
            }
        }
    } else {
        a0[0xA8] = 0xFF;
    }
    swamp_monster_sync_linked_parts_health(a0);
    if (a0[0x95] >= 5 && a0[0x95] <= 6)
        hud_start_overlay(1, 0, *(f32 *)(state + 0x20) / IntToFloat(*(short *)(state + 0x24)));
}




