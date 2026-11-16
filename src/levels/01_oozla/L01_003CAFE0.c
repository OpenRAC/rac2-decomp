#include "include_asm.h"
#include "common.h"


/* Quadword copies and clears, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

extern int math_fast_float_d(void *a0);

extern int FastDecTimer(void *a0);

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

/* func_L01_003CEDA0: scalar `sda` declarations under -G0 give retail's absolute accesses and
   its $gp loads in delay slots. */
extern u8 g_swamp_cutscene_flag __attribute__((sda));
extern u8 g_subtitle_history[];
extern u8 g_cutscene_vars[];
extern u8 *g_swamp_patrol_positions __attribute__((sda));
extern int g_hero_l01_control_mode __attribute__((sda));
extern int g_cutscene_flag __attribute__((sda));
extern float g_hero_l01_reach_timer_b __attribute__((sda));
extern u32 g_frame_counter __attribute__((sda));
extern float FastAddRotations(float, float);
extern int IsPointInCuboid(void *, int);
extern int req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern void part_spawn_sparkles_and_glow_rings(void *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void help_unlock_entry(int);
extern int moby_handle_request_slot_state(int);
extern void value_set_entry_by_index(int, int);
extern int MemcardSave(int, int);
extern void cam_lock_entry(int);
extern int subtitle_request_voice_line(int, int);

/* func_L01_003CAFE0 is in L01_003CAFE0-ctx-g16.c. */


/* func_L01_003CB668 is in L01_003CB668-g16.c. */

/* func_L01_003CBCD8 is in L01_003CBCD8-qcopy.c. */

/* Frees the object at 0xD8 of the object at 0x68 and clears its 0xDC flag. */
/* Gives back the shared attack slot this monster was holding, if any. */
void swamp_monster_release_attack_slot(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (moby[0x21] != 0xFF && *(u8 *)(vars + 0xDC) != 0)
        math_fast_float_d(*(void **)(vars + 0xD8));
    *(u8 *)(vars + 0xDC) = 0;
}

/* func_L01_003CBFF0 is defined in a sibling -g8.c unit. */

/* Releases the sub-objects at 0xC0, 0xBC, 0xC4 and 0x26, first bumping the counter at 0x96. */
/* Cleans up the swamp monster arm timers when it is removed. */
void swamp_monster_release_arm_timers(u8 *moby)
{
    u8 *moby_alias = moby;
    u8 *vars = *(u8 **)(moby_alias + 0x68);

    if (*(s32 *)(vars + 0x74) == 0)
        math_fast_float_d(vars + 0xC0);
    if (*(u16 *)(moby_alias + 0x96) < 0xFFFE)
        *(u16 *)(moby_alias + 0x96) = *(u16 *)(moby_alias + 0x96) + 1;
    math_fast_float_d(vars + 0xBC);
    math_fast_float_d(vars + 0xC4);
    FastDecTimer(vars + 0x26);
}

/* func_L01_003CC280 is defined in L01_003CC280-g8.c. */

/* Registers the object with the 0x04000009 descriptor and arms its 0x00 flag once. */
/* Tests a swing between two points against the hero and plays a hit sound the first time. */
void swamp_monster_test_attack_segment_hits_hero(u8 *moby, u32 segment_start, u32 segment_end, u8 width, u8 *sound_played)
{
    u8 *attacker = moby;
    u8 *sound_flag = sound_played;

    if (func_3120A8(attacker, segment_start, segment_end, 0x04000009, 0, 1, 1, (f32)width, 1.0f) == 0)
        return;
    if (g_hit_l01_result[0] != g_pHeroMoby[0])
        return;
    if (*sound_flag == 0)
        return;
    func_355780(3, 0, attacker);
    *sound_flag = 1;
}


extern void script_queue_keyed_request(s32 a0, s32 a1);
extern void anim_start_blended(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 math_closest_point_on_polygon_edge(void *a0, void *a1, void *a2, s32 a3);

/* While the owner's kind (+0x95) is 6, serves the two entities whose ids lie at +0xA0 and +0xA4. */
/* Shares health between this body and its two linked parts. When it runs out, both play their death moves. */
s32 swamp_monster_sync_linked_parts_health(u8 *moby)
{
    u8 *vars;
    u8 *part;
    u8 *part_vars;
    s32 *part_ids;
    s32 i;
    u8 *path_table;
    s32 shared_value;

    vars = *(u8 **)(moby + 0x68);
    if (moby[0x95] == 6)
        return 0;
    part_ids = (s32 *)(vars + 0xA0);
    for (i = 0; i < 2; i++) {
        if (part_ids[i] == -1)
            continue;
        part = D_L01_001B255C_sda[0] + (part_ids[i] << 8);
        part_vars = *(u8 **)(part + 0x68);
        if (moby[0x95] == 4 && *(s32 *)(part_vars + 0x74) == 1)
            script_queue_keyed_request(*(s32 *)(vars + 0xD0), *(s32 *)(vars + 0xD8));
        if (part[0x95] == 8)
            continue;
        shared_value = *(s32 *)(part_vars + 0xC0);
        if (shared_value < *(s32 *)(vars + 0xBC))
            shared_value = *(s32 *)(vars + 0xBC);
        *(s32 *)(vars + 0xBC) = shared_value;
        *(s32 *)(part_vars + 0xC0) = shared_value;
        if (*(f32 *)(vars + 0x20) <= 0.0f) {
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 10);
            *(f32 *)(vars + 0x20) = 0.0f;
            *(f32 *)(part_vars + 0x20) = 0.0f;
            if (part[0x43] != 4 && part[0x42] != 4)
                anim_start_blended(part, 4, 0, 10);
            part[0x95] = 8;
            moby_set_state(moby, 0, 6);
        }
        qcopy(vars + 0x80, part_vars + 0x60);
        path_table = g_path_l01_table[*(s32 *)(vars + 0xA8)];
        math_closest_point_on_polygon_edge(vars + 0x70, part_vars + 0x60, path_table + 0x10, *(s32 *)path_table);
    }
    return *(s32 *)(vars + 0xBC);
}

/* Sends the timer string and steps the 0x2E/0x28/0x2A state fields of the owner. */
extern s32 FloatToInt(f32 a0);
extern float path_l01_compute_segment_lengths(void *a0);
extern void anim_start_immediate(void *a0, s32 a1, s32 a2);

/* Seeds the state block (random timers, the saved position, its mode bytes), lets the table
   entry it names inherit the object's float at +0x18, then starts either the flagged (0xAC)
   or the plain animation. */
/* Sets up a body part when it appears, picks random timers and starts its first animation. */
void swamp_monster_init_linked_body_part(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    *(u8 *)(vars + 0x48) = FloatToInt(30.0f);
    *(u8 *)(vars + 0x4A) = FloatToInt(24.0f);
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24);
    qcopy(vars + 0x60, moby + 0x10);
    *(u8 *)(vars + 0x28) = 3;
    *(u8 *)(vars + 0x2E) = 3;
    *(f32 *)(vars + 0x30) = 3.0f;
    *(u32 *)(vars + 0xB4) = 0;
    *(s32 *)(vars + 0xC0) = -1;
    *(u8 *)(vars + 0x2A) = 8;
    if (*(s32 *)(vars + 0xCC) != -1) {
        u8 *linked_part = (u8 *)((*(s32 *)(vars + 0xCC) << 8) + (s32)D_L01_001B255C_sda[0]);

        if (*(u8 *)(linked_part + 0x20) != 0xFE) {
            if (*(u8 *)(linked_part + 0x20) != 0xFD)
                *(f32 *)(linked_part + 0x18) = *(f32 *)(moby + 0x18);
        }
    }
    if (*(s32 *)(vars + 0xA8) != -1)
        path_l01_compute_segment_lengths(g_path_l01_table[*(s32 *)(vars + 0xA8)]);
    if (*(u32 *)(vars + 0xAC) != 0) {
        *(u16 *)(moby + 0x34) &= 0xEFFF;
        anim_start_immediate(moby, 0, 0);
        *(u32 *)(moby + 0x48) = 0;
        moby_set_state(moby, 0, 4);
        return;
    }
    *(u16 *)(moby + 0x34) |= 0x1000;
    anim_start_immediate(moby, 1, 0);
    moby_set_state(moby, 0, 1);
}

/* Releases the three sub-objects at 0xBC, 0xB4 and 0x26, first bumping the counter at 0x96. */
/* Cleans up the part timers when it is removed. */
void swamp_monster_release_timers(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u16 *)(moby + 0x96) < 0xFFFE)
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
    math_fast_float_d(vars + 0xBC);
    math_fast_float_d(vars + 0xB4);
    FastDecTimer(vars + 0x26);
}

/* The group count and the entity base, read as bare symbols (`sda` arrays of unknown size: the
   assembler makes the loads $gp ones in a branch delay slot); the base takes a second name
   because D_L01_001B255C is declared above with its pointer type. */
extern s32 g_swamp_monster_thresholds[] __attribute__((sda));
extern u16 *g_group_list_table[];
extern u8 g_hero_position[];

extern void *part_find_owned_effect_slot(void *, s32, s32);
extern f32 moby_update_aim_target_strength(void *, void *);
extern u8 *moby_get_private_value_0(u8 *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern f32 IntToFloat(s32);
extern void hud_start_overlay(s32, s32, f32);

/* While the owner's kind (+0x95) is 5 or 6 and its timer (+0x20) is positive, finds the entity
   func_002A9640 names (only when the state's halfword at +0x26 is below 1) and its distance
   f20 from func_002A96A0; when that is positive, walks the id list of the owner's group and
   sets the effect record each entity hands out (func_002AB1F0: class-dependent 60 or 0 at +6,
   the distance taken off its float at +0), otherwise takes the distance off the timer. Then
   it runs the timer out (releasing the entity at +0xCC and switching to state 5), or, below it,
   enters state 4 for a distance of 1.0 or more and scales the vector at +0x90. At the end the
   shared update runs and the timer ratio is handed to func_L01_002F14E8. The function keeps
   the second `p != 0` guard of the walk; func_L01_003CDB40 returns a word, and the retail
   copy of the 0.2 limit holds one ulp more than 0.2f. */
/* Handles damage to a body part, then switches it to a hit or death animation and pushes it away. */
void swamp_monster_apply_damage(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *attacker;
    u8 *hit_source;
    u8 *group_member;
    u8 *hit_record;
    u16 *member_list;
    f32 damage;
    f32 push_strength;
    s32 hit_duration;
    u16 class_id;

    if (moby[0x95] >= 5 && moby[0x95] <= 6 && 0.0f < *(f32 *)(state + 0x20)) {
        attacker = part_find_owned_effect_slot(moby, 0x10000, 0);
        hit_source = attacker;
        if (*(short *)(state + 0x26) >= 1)
            hit_source = 0;
        damage = moby_update_aim_target_strength(moby, hit_source);
        if (hit_source != 0 && 0.0f < damage) {
            if (moby[0x21] != 0xFF && *(s32 *)(state + 0xA0) != -1) {
                class_id = *(u16 *)(*(u8 **)(hit_source + 0x20) + 0xAA);
                hit_duration = (class_id == 0xCE4 /* moby class 3300 */ || class_id == 0xCE5 /* moby class 3301 */) ? 60 : 0;
                for (member_list = g_group_list_table[moby[0x21]];
                     moby[0x21] != 0xFF && moby[0x21] <= g_swamp_monster_thresholds[0] && member_list != 0 &&
                     ((member_list != 0 && (short)member_list[-1] >= 0) || member_list == g_group_list_table[moby[0x21]]);
                     member_list++) {
                    group_member = D_L01_001B255C_sda[0] + ((*member_list & 0x7FFF) << 8);
                    if (group_member == 0)
                        break;
                    hit_record = moby_get_private_value_0(group_member);
                    if (hit_record != 0) {
                        *(u16 *)(hit_record + 6) = hit_duration;
                        *(f32 *)hit_record = *(f32 *)hit_record - damage;
                        hit_record[0x17] = state[0x37];
                        *(s32 *)(hit_record + 0x18) = *(s32 *)(state + 0x38);
                        *(u16 *)(hit_record + 0x1C) = *(u16 *)(state + 0x3C);
                    }
                    group_member[0xA8] = 0xFF;
                }
            } else {
                *(f32 *)(state + 0x20) = *(f32 *)(state + 0x20) - damage;
            }
        }
        moby[0xA8] = 0xFF;
        if (*(f32 *)(state + 0x20) < 0.0f) {
            if (*(s32 *)(state + 0xCC) != -1)
                moby_mark_spawned(D_L01_001B255C_sda[0] + (*(s32 *)(state + 0xCC) << 8));
            *(s32 *)(state + 0xCC) = -1;
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 10);
            *(f32 *)(state + 0x20) = 0.0f;
            moby_set_state(moby, 0, 6);
            *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) & 0xEFFF;
        } else {
            if (1.0f <= damage) {
                *(s32 *)(state + 0xBC) = 0xF0;
                if (moby[0x43] != 4)
                    anim_start_blended(moby, 4, 0, 3);
                *(u16 *)(moby + 0x34) = *(u16 *)(moby + 0x34) & 0xEFFF;
                moby_set_state(moby, 0, 6);
            }
            if (0.1f < damage) {
                FastVecSub(state + 0x90, moby + 0x10, g_hero_position);
                push_strength = (damage + damage + 3.0f) * 0.016666668f;
                if (0.20000002f < push_strength)
                    push_strength = 0.20000002f;
                vec_scale_to_length(state + 0x90, state + 0x90, push_strength);
                *(s32 *)(state + 0x98) = 0;
            }
        }
    } else {
        moby[0xA8] = 0xFF;
    }
    swamp_monster_sync_linked_parts_health(moby);
    if (moby[0x95] >= 5 && moby[0x95] <= 6)
        hud_start_overlay(1, 0, *(f32 *)(state + 0x20) / IntToFloat(*(short *)(state + 0x24)));
}


/* func_L01_003CE868 is defined in L01_003CE868-g8.c. */

/* Three states on the byte at +0x20: 0 raises the moby by 0.75 and sets its scale to 1.5 times
   the class value (or frees it while D_001A7B1C is set); 1 turns it (+0xF8) and, once the point
   D_00189EA0 lies in the cuboid its vars name at +4, queues movie 0x26 (QueueMovie) and enters
   state 2; 2 bumps the counter at +0x96, waits for func_002F5D10, then runs the level calls for
   the entry its vars name at +8, flags the object named at +0xC once, steps the subtitle history
   timer of entry 16 (TryQueueSubtitleSelection 0x9B9 after 180 frames) and frees the moby.
   The timer's three loads keep their retail order only when the frame counter is read last. */
/* Cutscene trigger. When the hero walks into its zone it plays a movie, runs the level event and removes itself. */
void cutscene_trigger_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68), *anchor;
    int screen_mode;

    switch (moby[0x20]) {
    case 0:
        if (g_swamp_cutscene_flag) {
            moby_mark_spawned(moby);
            break;
        }
        *(float *)(moby + 0x18) += 0.75f;
        *(float *)(moby + 0x2C) = *(float *)(*(u8 **)(moby + 0x24) + 0x24) * 1.5f;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), 0.078539826f);
        if (IsPointInCuboid(g_hero_position, *(int *)(vars + 4))) {
            vars = g_cutscene_vars;
            if (req_push_queue(vars, 0x26)) {
                req_launch_queued(vars);
                moby_set_state(moby, 2, -1);
            }
        }
        if (moby[0x31])
            part_spawn_sparkles_and_glow_rings(moby);
        break;
    case 2:
        screen_mode = g_hero_l01_control_mode;
        (*(u16 *)(moby + 0x96))++;
        if (screen_mode == 2) {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        anchor = g_swamp_patrol_positions + (*(int *)(vars + 8) << 7);
        g_cutscene_flag = 0;
        g_hero_l01_reach_timer_b = 0;
        hero_reset_position_and_direction(anchor + 0x30, anchor + 0x70, 0x6F, 1);
        help_unlock_entry(0x24);
        moby_handle_request_slot_state(0x24);
        value_set_entry_by_index(0x1225, -1);
        MemcardSave(0, -1);
        if (*(int *)(vars + 12) != -1) {
            vars = *(u8 **)(g_moby_l01_table + (*(int *)(vars + 12) << 8) + 0x68);
            if (!*(int *)(vars + 0x3C)) {
                cam_lock_entry(*(int *)(vars + 0x38));
                *(int *)(vars + 0x3C) = 1;
            }
            vars = g_subtitle_history;
            if (!*(u16 *)(vars + 0xC0)) {
                u16 elapsed = *(u16 *)(vars + 0xC2);
                u32 start = *(u32 *)(vars + 0xC4);
                u32 now = g_frame_counter;

                if (start + elapsed >= now - 2) {
                    *(u16 *)(vars + 0xC2) = ++elapsed;
                    if (elapsed >= 180) {
                        subtitle_request_voice_line(0x9B9, 0x10);
                        *(u16 *)(vars + 0xC2) = 0;
                    }
                } else {
                    if (start < now)
                        *(u32 *)(vars + 0xC4) = now;
                    *(u16 *)(vars + 0xC2) = 0;
                }
            }
        }
        moby_mark_spawned(moby);
        break;
    }
}

/* func_L01_003D1A48 lives in L01_003D1A48-g8.c. */

/* func_L01_003D1F40 is defined in L01_003D1F40-g8.c. */

/* func_L01_003D25B8 is defined in a sibling -g8.c unit. */

/* func_L01_003D26C0 is in L01_003D26C0-g8.c. */

/* func_L01_003D2890 is in L01_003CAFE0-launch.c. */

/* func_L01_003D2E50 is in L01_003D2E50.c. */

/* func_L01_003D68C0 is defined in a sibling -g8.c unit. */

/* func_L01_003D8358 lives in L01_003D8358-g8.c. */

/* func_L01_003D8830 is in L01_003CAFE0-burst.c. */

/* func_L01_003D8AD0 is defined in a sibling -g8.c unit. */

/* func_L01_003D8C00 is defined in L01_003D8C00-qcopy-barrier.c. */

/* func_L01_003D8E80 is defined in L01_003CAFE0-g8.c. */


/* func_L01_003D98E0 is defined in L01_003D98E0-g8.c. */

/* func_L01_003DA300 is in L01_003DA300-g8.c. */

/* func_L01_003DA3F0 is defined in L01_003DA3F0-g8.c. */
