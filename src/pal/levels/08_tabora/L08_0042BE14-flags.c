#include "names.h"
/* func_PAL_L08_0042BE14, the PAL copy of func_L08_00426730: the same C at 50 Hz. Both func_002A7820
 * results are scaled by ((s32)(x) * 5 + 2) / 6, with their arguments unchanged; 240 becomes 200,
 * 120 becomes 100, 115 becomes 96, 90 becomes 75, 38 becomes 32; floats 0.012f, 0.006f, 0.64000005f,
 * 0.020000001f, 0.024434613f. Callees renamed to their PAL rows. */
#include "common.h"
#define FIELD(p, type, off) (*(type *)((p) + (off)))
extern int g_moby_array __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern unsigned char g_moby_nibble_table[];
extern char g_hero_position_vec[];
extern struct { char pad[0x160]; float amount; int pad164; int timer; int phase; } g_hero_l08_extra_state;
extern struct { char pad[0x464]; u8 flags[0]; } g_moby_spawn_state_flags_a;
extern struct { char pad[0x464]; u8 flags[0]; } g_moby_spawn_state_flags_b;
extern int moby_is_in_selected_zone(void *);
extern void moby_mark_spawned(void *);
extern float vec_distance_xy(void *, void *);
extern void hover_init_defaults_pal(char *);
extern void creature_update_hit_reaction_pal(char *);
extern int math_random_int_below(int);
extern int SelectNearestListedMoby(char *, char *, float, float, int, int, int, int);
extern int vec_apply_scaled_value(char *, float);
extern int moby_handle_is_gone(int);
extern int moby_handle_is_past_early_state(int);
extern void anim_start_blended(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern int flag_set_first_pending(char *);
extern int PlayMobySound(int, int, char *);
extern float math_step_value_toward_target(void *, float, void *, float, float, float);
extern void part_spawn_dust_burst_motion_pal(char *, void *, int, float, float, float, float, float, float);
extern void creature_pick_random_target(char *);
extern int func_001163B0(void);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_range(int, int);
extern float mat_fast_helper_a(float, float);
extern int moby_move_to_target_braking_pal(char *, float, float, int, float, float, float);
extern void creature_compute_aim_point(char *);
extern int FastDecTimer(void *);
extern float FastVecLength(void *);
extern int ClaimTaboraSlot(char *, int, int);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);
extern void dune_monster_sweep_attack(char *);
extern void group_advance_turn(char *);
extern int slot_release_by_key(char *);
extern int moby_dispatch_action_by_kind(char *, void *);
extern char *CreateMoby(int);
extern void func_002A0F48(char *);
extern void hero_copy_field_to_moby(char *);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void group_remove_member(char *);
extern void SetDeathBits(char *, int, int);
extern void hover_update_follow_counters_pal(char *);
extern void UpdateNearestTarget(char *, void *);

/* Per-frame state machine of a level-08 moby: wait for its trigger, rise above and sink
   below the height at +0x1C4, patrol and attack, recover
   from a hit, and on death spawn a replacement moby and clear its saved flag bits.
   Case 0 of the patrol switch repeats case 4's attack check; jump2 cross-jumps them. */
void dune_monster_update_pal(char *moby) {
    char *vars;
    float local[4] __attribute__((aligned(16)));
    float local2[4] __attribute__((aligned(16)));
    int ready;
    int flags;
    float angle;
    if (!moby_is_in_selected_zone(moby + 0x10)) return;
    vars = FIELD(moby, char *, 0x68);
    if (FIELD(moby, u8, 0x20) == 0) {
        u16 id = FIELD(moby, u16, 0xB2);
        int bits = g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)];
        if ((id & 1) ? (((bits >> 4) & 7) != 0) : ((bits & 7) != 0)) {
            moby_mark_spawned(moby);
            return;
        }
        hover_init_defaults_pal(moby);
    }
    if (vec_distance_xy(moby + 0x10, g_hero_position_vec) > (float)FIELD(moby, u8, 0x30)) return;
    creature_update_hit_reaction_pal(moby);
    switch (FIELD(moby, u8, 0x20)) {
    case 0: break;
    case 1: {
        int condition;
        ready = 0;
        switch (FIELD(vars, u8, 0x20C)) {
        case 0:
        case 1:
            if (!math_random_int_below(7)) {
                SelectNearestListedMoby(moby, vars + 0x120, (float)FIELD(moby, s16, 0x32), 0.0f,
                    FIELD(vars, int, 0x1D0), -1, FIELD(vars, int, 0x1D4), -1);
                if (FIELD(vars, int, 0x164) != 2)
                    condition = ~vec_apply_scaled_value(moby, (float)FIELD(moby, s16, 0x32));
                else break;
                goto ready_nonzero;
            }
            break;
        case 2:
            if (FIELD(moby, u8, 0xBC)) {
                FIELD(moby, u8, 0xBC) = 0;
                ready = 1;
            }
            break;
        case 3: ready = moby_handle_is_gone(FIELD(vars, int, 0x1EC)) != 0; break;
        case 5:
            condition = moby_handle_is_past_early_state(FIELD(vars, int, 0x1E8));
ready_nonzero:
            ready = condition != 0;
            break;
        }
        if (FIELD(moby, u8, 0xBC) & 2) {
            FIELD(moby, u8, 0xBC) = 0;
            ready = 1;
        }
        if (ready && vec_apply_scaled_value(moby, (float)FIELD(moby, s16, 0x32)) != -1) {
            FIELD(moby, u8, 0x30) = FIELD(vars, u8, 0x20E);
            qzero(vars + 0x190);
            if (FIELD(moby, u8, 0x43) != 1) anim_start_blended(moby, 1, 0, 10);
            FIELD(moby, u8, 0x31) = 1;
            FIELD(moby, u16, 0x34) &= 0xFFFE;
            moby_set_state(moby, 2, -1);
            g_hero_l08_extra_state.amount = 0.25f;
            g_hero_l08_extra_state.timer = 32;
            g_hero_l08_extra_state.phase = 0;
            if (FIELD(vars, char *, 0x22C)) {
                FIELD(FIELD(vars, char *, 0x22C), u8, 0xBC) = 1;
                FIELD(vars, char *, 0x22C) = 0;
            }
        }
        break;
    }
    case 2: {
        float height;
        if (flag_set_first_pending(moby)) PlayMobySound(0, 0, moby);
        math_step_value_toward_target(moby + 0x18, FIELD(vars, float, 0x1C8), vars + 0x198,
            0.012f, 0.006f, 0.64000005f);
        height = FIELD(vars, float, 0x1C4);
        if (FIELD(moby, float, 0x18) < height + 1.5f) {
            qcopy(local, moby + 0x10);
            local[2] = height;
            part_spawn_dust_burst_motion_pal(moby, local, 8, 10.0f, 4.0f, 4.0f, 0.0f, 0.25f, 3.5f);
        }
        if (FIELD(moby, u8, 0x60) & 2) {
            FIELD(moby, int, 0x98) = FIELD(FIELD(moby, char *, 0x24), int, 0x10);
            FIELD(moby, u16, 0x34) |= 0x1000;
            creature_pick_random_target(moby);
            if (FIELD(moby, u8, 0x43) != (func_001163B0() & 1) + 4)
                anim_start_blended(moby, (func_001163B0() & 1) | 4, 0, 10);
            moby_set_state(moby, 4, 0);
        }
        break;
    }
    case 3: {
        float height;
        math_step_value_toward_target(moby + 0x18, FIELD(vars, float, 0x1C4) - 1.5f, vars + 0x198,
            0.012f, 0.006f, 0.64000005f);
        FastVecSub(local, vars + 0x170, moby + 0x10);
        FastVecScale(local, local, 0.025f);
        local[2] = 0.0f;
        FastVecAdd(moby + 0x10, moby + 0x10, local);
        height = FIELD(vars, float, 0x1C4);
        if (FIELD(moby, float, 0x18) < height + 1.5f) {
            qcopy(local2, moby + 0x10);
            local2[2] = height;
            part_spawn_dust_burst_motion_pal(moby, local2, 8, 10.0f, 4.0f, 4.0f, 0.0f, 0.25f, 3.5f);
        }
        if (FIELD(moby, float, 0x18) < FIELD(vars, float, 0x1C4) - 1.4f && !FIELD(moby, u8, 0x42)) {
            part_spawn_dust_burst_motion_pal(moby, moby + 0x10, 8, 10.0f, 4.0f, 2.0f, 0.0f, 0.25f, 3.5f);
            FIELD(moby, int, 0x98) = 0;
            FIELD(moby, u16, 0x34) &= 0xEFFF;
            FIELD(moby, float, 0x18) = FIELD(vars, float, 0x1C4);
            if (FIELD(moby, u8, 0x43)) anim_start_blended(moby, 0, 0, 2);
            moby_set_state(moby, 1, -1);
            FIELD(moby, u8, 0x30) = FIELD(vars, u8, 0x20F);
        }
        break;
    }
    case 4:
        if (!math_random_int_below(7))
            SelectNearestListedMoby(moby, vars + 0x120, (float)FIELD(moby, s16, 0x32), 60.0f,
                FIELD(vars, int, 0x1D8), FIELD(vars, int, 0x1E0), FIELD(vars, int, 0x1DC), -1);
        if (vec_distance_xy(moby + 0x10, vars + 0x120) < 8.0f) FIELD(vars, s16, 0x1B8) = 100;
        switch (FIELD(moby, u8, 0x95)) {
        case 1:
            if (!FIELD(vars, s16, 0x1B0)) {
                u16 timer;
                FIELD(vars, s16, 0x1B0) = ((s32)math_random_int_range(240, 480) * 5 + 2) / 6;
                if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, math_random_int_range(15, 30));
                timer = FIELD(moby, u16, 0x96);
                moby_set_state(moby, 4, 0);
                FIELD(moby, u16, 0x96) = timer;
            }
            if (FIELD(vars, int, 0x164) != 2 && !FIELD(vars, s16, 0x1BC)) {
                if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, math_random_int_range(15, 30));
                FIELD(moby, u8, 0x30) = 255;
                moby_set_state(moby, 4, 2);
            }
            break;
        case 0:
            if (moby_move_to_target_braking_pal(moby, 5.5f, 5.5f, 1,
                mat_fast_helper_a(FIELD(vars, float, 0x120) - FIELD(moby, float, 0x10),
                             FIELD(vars, float, 0x124) - FIELD(moby, float, 0x14)), 0.0f, 0.0f)) FIELD(vars, s16, 0x1B0) = 0;
            if (!FIELD(vars, s16, 0x1B0)) {
                if (FIELD(moby, u16, 0x96) < 60) {
                    u16 timer;
                    creature_pick_random_target(moby);
                    FIELD(vars, s16, 0x1B0) = ((s32)math_random_int_range(90, 180) * 5 + 2) / 6;
                    if (FIELD(moby, u8, 0x43) != (func_001163B0() & 1) + 2)
                        anim_start_blended(moby, (func_001163B0() & 1) | 2, 0, 30);
                    timer = FIELD(moby, u16, 0x96);
                    moby_set_state(moby, 4, 1);
                    FIELD(moby, u16, 0x96) = timer;
                } else {
                    FIELD(vars, s16, 0x1B0) = 32767;
                    qcopy(vars + 0x180, vars + 0x170);
                    FIELD(vars, float, 0x188) = FIELD(moby, float, 0x18);
                    moby_set_state(moby, 4, 4);
                }
            }
            /* Same check as case 4; jump2 cross-jumps the two, sharing the call above. */
            if (FIELD(vars, int, 0x164) != 2 && !FIELD(vars, s16, 0x1BC)) {
                if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, math_random_int_range(15, 30));
                FIELD(moby, u8, 0x30) = 255;
                moby_set_state(moby, 4, 2);
            }
            goto patrol_heading;
        case 4:
            if (moby_move_to_target_braking_pal(moby, 5.5f, 5.5f, 1,
                mat_fast_helper_a(FIELD(vars, float, 0x120) - FIELD(moby, float, 0x10),
                             FIELD(vars, float, 0x124) - FIELD(moby, float, 0x14)), 0.0f, 0.0f)) {
                if (FIELD(moby, u8, 0x43)) anim_start_blended(moby, 0, 0, 180);
                moby_set_state(moby, 3, -1);
            }
            if (FIELD(vars, int, 0x164) != 2 && !FIELD(vars, s16, 0x1BC)) {
                if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, math_random_int_range(15, 30));
                FIELD(moby, u8, 0x30) = 255;
                moby_set_state(moby, 4, 2);
            }
            goto patrol_heading;
        case 2:
            creature_compute_aim_point(moby);
            FIELD(vars, float, 0x188) = FIELD(vars, float, 0x1C8);
            if (FastDecTimer(vars + 0x1B8)) {
                moby_move_to_target_braking_pal(moby, 5.5f, 5.5f, 1,
                    mat_fast_helper_a(FIELD(vars, float, 0x120) - FIELD(moby, float, 0x10),
                                 FIELD(vars, float, 0x124) - FIELD(moby, float, 0x14)), 0.0f, 0.0f);
            } else {
                moby_move_to_target_braking_pal(moby, 32.0f, 12.0f, 1,
                    mat_fast_helper_a(FIELD(vars, float, 0x120) - FIELD(moby, float, 0x10),
                                 FIELD(vars, float, 0x124) - FIELD(moby, float, 0x14)), 0.0f, 0.0f);
            }
            if (FIELD(moby, u8, 0x60) & 2) {
                if (FastVecLength(vars + 0x190) < 0.020000001f) {
                    if (FIELD(moby, u8, 0x43) != (func_001163B0() & 1) + 4)
                        anim_start_blended(moby, (func_001163B0() & 1) | 4, 0, 10);
                } else if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, 10);
            }
            if (FIELD(vars, int, 0x164) == 2) {
                if (!FastDecTimer(vars + 0x1B4)) goto patrol_heading;
                goto resume_patrol;
            }
            if (FIELD(vars, s16, 0x1BC) >= 200) {
resume_patrol:
            if (FIELD(moby, u8, 0x43) != (func_001163B0() & 2) + 2)
                anim_start_blended(moby, (func_001163B0() & 2) + 2, 0, 10);
            FIELD(moby, u8, 0x30) = FIELD(vars, u8, 0x20E);
            moby_set_state(moby, 4, 0);
                goto patrol_heading;
            } else {
                FIELD(vars, s16, 0x1B4) = 200;
                if ((FIELD(moby, u8, 0x21) != 255 &&
                        FIELD(FIELD(vars, char *, 0x1F8), int, 0) != FIELD(vars, u8, 0x20D)) ||
                    !FastDecTimer(vars + 0x1B6) || !ClaimTaboraSlot(moby, 1, 0) ||
                    FIELD(vars, s16, 0x1BC)) goto patrol_heading;
                FIELD(vars, float, 0x1F4) = -0.78539824f;
                FIELD(vars, float, 0x1F0) = 1.0f;
                FIELD(vars, int, 0x204) = 0;
                FIELD(vars, int, 0x21C) = 0;
                FIELD(vars, u8, 0x219) = 0;
                if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, math_random_int_range(15, 30));
                moby_set_state(moby, 4, 3);
                FIELD(vars, u8, 0x218) = 0;
                FIELD(moby, u8, 0x30) = 255;
                goto patrol_heading;
            }
            goto patrol_heading;
        case 3:
            creature_compute_aim_point(moby);
            angle = mat_fast_helper_a(FIELD(vars, float, 0x120) - FIELD(moby, float, 0x10),
                                 FIELD(vars, float, 0x124) - FIELD(moby, float, 0x14));
            if (FastDecTimer(vars + 0x1B8)) {
                moby_move_to_target_braking_pal(moby, 5.5f, 5.5f, 1, angle, 0.0f,
                    -mat_fast_helper_a(vec_distance_xy(moby + 0x10, vars + 0x140),
                        FIELD(vars, float, 0x148) - FIELD(moby, float, 0x18)));
            } else {
                moby_move_to_target_braking_pal(moby, 32.0f, 12.0f, 1, angle, 0.0f,
                    -mat_fast_helper_a(vec_distance_xy(moby + 0x10, vars + 0x140),
                        FIELD(vars, float, 0x148) - FIELD(moby, float, 0x18)));
            }
            switch (FIELD(vars, u8, 0x218)) {
            case 0:
                if (FastDiffRots(angle, FIELD(vars, float, 0x208)) < 0.6981318f) {
                    FIELD(vars, float, 0x1F4) = -0.78539824f;
                    FIELD(vars, float, 0x1F0) = 1.0f;
                    if (FIELD(moby, u8, 0x43) != 7) anim_start_blended(moby, 7, 0, math_random_int_range(8, 15));
                    FIELD(vars, u8, 0x218) = 1;
                }
                goto attack_check_cancel;
            case 1:
                FIELD(vars, float, 0x21C) += 0.012f;
                if (FIELD(vars, float, 0x21C) >= 1.0f) {
                    FIELD(vars, float, 0x21C) = 1.0f;
                    FIELD(vars, u8, 0x218) = 2;
                    FIELD(vars, u8, 0x219) = 0;
                }
                goto attack_move;
            case 2: {
                float sweep, direction;
                FIELD(vars, float, 0x1F4) = FastAddRotations(FIELD(vars, float, 0x1F4), FIELD(vars, float, 0x1F0) * 0.024434613f);
                sweep = FIELD(vars, float, 0x1F4);
                direction = FIELD(vars, float, 0x1F0);
                if (direction > 0.0f) {
                    if (!(sweep >= 0.78539824f)) goto sweep_done;
                } else if (!(sweep <= -0.78539824f)) goto sweep_done;
                {
                    FIELD(vars, s16, 0x21A) = 0;
                    FIELD(vars, float, 0x1F0) = -direction;
                    FIELD(vars, u8, 0x219)++;
                }
sweep_done:
                if (FIELD(vars, u8, 0x219) >= 3 && !FIELD(vars, s16, 0x1B8)) FIELD(vars, u8, 0x218) = 4;
                else FIELD(vars, u8, 0x218) = 3;
                goto attack_move;
            }
            case 3:
                if (FastDecTimer(vars + 0x21A)) FIELD(vars, u8, 0x218) = 2;
                goto attack_move;
            case 4:
                FIELD(vars, float, 0x21C) -= 0.012f;
                if (FIELD(vars, float, 0x21C) <= 0.012f) {
                    FIELD(vars, u8, 0x219) = 0;
                    FIELD(vars, u8, 0x218) = 5;
                }
attack_move:
                dune_monster_sweep_attack(moby);
                goto attack_check_cancel;
            case 5:
                group_advance_turn(moby);
                slot_release_by_key(moby);
                FIELD(vars, int, 0x204) = 0;
                FIELD(vars, s16, 0x1B6) = 75;
                if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, math_random_int_range(8, 15));
                moby_set_state(moby, 4, 0);
                goto attack_check_cancel;
            default: goto attack_check_cancel;

            }
attack_check_cancel:
            if (FIELD(vars, int, 0x164) == 2 || FIELD(vars, s16, 0x1BC) >= 200) {
                group_advance_turn(moby);
                slot_release_by_key(moby);
                FIELD(vars, s16, 0x1B6) = 0;
                if (FIELD(moby, u8, 0x43) != 6) anim_start_blended(moby, 6, 0, math_random_int_range(8, 15));
                FIELD(moby, u8, 0x30) = FIELD(vars, u8, 0x20E);
                moby_set_state(moby, 4, 0);
            } else FIELD(vars, s16, 0x1B4) = 200;
patrol_heading:
            FIELD(moby, float, 0xF8) = FIELD(vars, float, 0x208);
            break;
        }
        break;
    case 5:
        FIELD(moby, u8, 0x30) = 255;
        FIELD(moby, s16, 0x32) = 255;
        slot_release_by_key(moby);
        FIELD(vars, u16, 0x1BA)++;
        flags = moby_dispatch_action_by_kind(moby, vars + 0x50);
        FIELD(vars, float, 0x208) = FIELD(moby, float, 0xF8);
        if (flags & 1) moby_set_state(moby, 6, -1);
        else if ((flags & 2) || FIELD(vars, s16, 0x1BA) >= 96) {
            if (FIELD(vars, float, 0x20) > 0.0f) {
                qzero(vars + 0x1A0);
                FIELD(vars, u8, 0x6A) = 2;
                if (FIELD(moby, u8, 0x43) != 4) anim_start_blended(moby, 4, 0, 40);
                FIELD(vars, s16, 0x1BA) = 0;
                qzero(vars + 0x190);
                FIELD(moby, u8, 0x30) = FIELD(vars, u8, 0x20E);
                moby_set_state(moby, 4, 2);
                group_advance_turn(moby);
            } else moby_set_state(moby, 6, -1);
        }
        if ((flags & 4) || FIELD(moby, float, 0x18) < FIELD(vars, float, 0x1C4) + 1.5f) {
            FIELD(vars, u16, 0x1BA)++;
            qcopy(local, moby + 0x10);
            local[2] = FIELD(vars, float, 0x1C4);
            part_spawn_dust_burst_motion_pal(moby, local, 10, 14.0f, 6.0f, 5.5f, 0.0f, 0.5f, 4.0f);
        }
        break;
    case 6:
    case 7: {
        char *child;
        u16 id;
        u8 *bits;
        slot_release_by_key(moby);
        child = CreateMoby(0x8C4);
        if (!child) break;
        FIELD(child, u8, 0x23) = 80;
        FIELD(child, u16, 0x34) |= 0x800;
        FIELD(child, u8, 0x30) = 255;
        FIELD(child, s16, 0x32) = 255;
        FIELD(child, u8, 0x31) = 1;
        FIELD(child, u8, 0x20) = 0;
        FIELD(child, u8, 0xBC) = 0;
        qcopy(child + 0x10, moby + 0x10);
        if (FIELD(vars, float, 0x1C4) != 0.0f) FIELD(child, float, 0x18) = FIELD(vars, float, 0x1C4);
        FIELD(FIELD(child, char *, 0x68), char *, 4) = moby;
        func_002A0F48(child);
        hero_copy_field_to_moby(child);
        if (FIELD(moby, u8, 0x20) == 7)
            SpawnExplosionEffects(moby, vars + 0x190, 0, 0.0f, 0.0f, 20, 6, 32,
                8.0f, 4.0f, 9.0f, 2.0f, -1, 30.0f, 1, 2, -1, 0, 0x810001);
        group_remove_member(moby);
        SetDeathBits(moby, 0, 3);
        g_moby_spawn_state_flags_a.flags[FIELD(moby, s16, 0xB2)] = 0;
        g_moby_spawn_state_flags_b.flags[FIELD(moby, s16, 0xB2)] = 0;
        id = FIELD(moby, u16, 0xB2);
        bits = &g_moby_nibble_table[((short)id >> 1) + (g_current_map_index << 10)];
        {
            u8 value = *bits;
            u8 low = value & 0xF8;
            u8 high = value & 0x8F;
            value = !(id & 1) ? low : high;
            *bits = value;
        }
        moby_mark_spawned(moby);
        return;
    }
    case 8: break;
    }
    hover_update_follow_counters_pal(moby);
    if ((unsigned int)(FIELD(moby, u8, 0x20) - 2) < 4 && FIELD(moby, u8, 0x31)) {
        int index = FIELD(vars, int, 0x1E8);
        if (index != -1 && FIELD(FIELD(vars, char *, 0x1FC), int, 0)) {
            char *target = (char *)(g_moby_array + (index << 8));
            if (!target || FIELD(target, u8, 0x20) == 0xFE || FIELD(target, u8, 0x20) == 0xFD)
                UpdateNearestTarget(moby, moby + 0x10);
            else UpdateNearestTarget(moby, target + 0x10);
        } else UpdateNearestTarget(moby, moby + 0x10);
    }
    if (FIELD(moby, float, 0x10) < 30.0f || FIELD(moby, float, 0x10) > 993.0f ||
        FIELD(moby, float, 0x14) < 30.0f || FIELD(moby, float, 0x14) > 993.0f ||
        FIELD(moby, float, 0x18) < 30.0f || FIELD(moby, float, 0x18) > 993.0f) {
        group_remove_member(moby);
        moby_mark_spawned(moby);
    }
}
