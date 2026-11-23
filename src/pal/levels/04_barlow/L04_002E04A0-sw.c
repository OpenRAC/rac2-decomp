#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef TI128 s128;
#define NULL ((void *)0)
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern char g_pad_state[];
extern char g_item_slot_to_record[];
extern char g_hero_state[];
extern u8 g_option_toggle_b[] MACRO_ADDR;
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern s32 g_current_map_index;
extern f32 g_hero_l04_speed_params[][4] MACRO_ADDR;
extern s32 g_hero_l04_animation_id;
extern s32 g_hero_l04_lock_flag_b;
extern f32 g_hero_l04_speed_threshold;
extern s32 g_hero_l04_input_block;
extern s32 g_hero_l04_input_state_word;
extern s32 g_hero_l04_decide_flag;
extern u8 g_hero_l04_particle_params_a[16] __attribute__((sda));
extern u8 g_hero_l04_particle_params_b[16] __attribute__((sda));
extern s32 g_hero_l04_animation_ids[2] __attribute__((sda));
extern char g_hero_transition_records[];
extern char g_hero_l04_tuning_params[];
extern char g_hero_state_entries[];
extern char g_item_l04_record_table[];
extern char g_hero_l04_state[];
s32 CollLine(void *, void *, s32, void *, s32);
s32 coll_test_point(void *, s32, void *, f32);
s32 math_fast_float_d(void *);
s32 FastDecTimer(s16 *);
f32 math_fabs(f32);
void FastVecScale(void *, void *, f32);
f32 FastVecLength(void *);
f32 vec_length_xy(void *);
f32 fast_vec_dist(void *, void *);
f32 vec_distance_xy(void *, void *);
f32 math_fast_sin_or_cos_a(f32);
f32 math_fast_sin_or_cos_b(f32);
f32 FastAddRotations(f32 a0, f32 a1);
f32 FastDiffRots(f32 a0, f32 a1);
s32 FloatToInt(f32);
int hud_set_slot_contents(s32, s32, void *, void *, void *, s32, s32);
void menu_init_panel_layout_pal(u8 *object);
void weapon_wheel_update_select_pal(s8 *);
s32 weapon_wheel_draw_pal(s8 *);
void moby_transform_joint_to_world(s8 *a0, s32 a1, s8 *a2);
void anim_start_blended_pal(u8 *object, s32 animation, s32 frame, s32 rate);
s32 math_random_int_range(s32 a0, s32 a1);
f32 math_random_float_range(f32 a0, f32 a1);
f32 ApproachValue(f32 *value, f32 target, f32 step);
void vec_clamp_length(f32 *, f32);
s32 hero_get_weapon_animation_id(s32 arg);
u32 math_l00_return_argument(u32 param_1);
void hero_play_footstep_effect_pal(void);
void hero_play_footstep_sound_dust_pal(s32 kind, s32 side, s32 play_sound, s32 duration);
void hero_clear_tracked_slots(void);
float AdjustHeroAnimationSpeedForTargetFrame(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void part_emit_hero_dust_and_debris_pal(s32 dust, s32 debris, s32 model);
s32 hero_test_reach_blend(f32 *out, f32 scale, f32 amount);
s32 ProbeLedgeGrab_pal(s8 *, s8 *, s8 *);
s32 hero_slot_item_id(s32 index);
void cancel_hero_item_animation_pal(void);
void hero_record_play_counters_pal(void);
s32 moby_is_class_71(u8 *object);
s32 hero_is_turned_past_angle(f32 x);
s32 math_is_below_plane_within_depth(f32 value);
void hero_resolve_stick_direction(s32, f32);
void hero_update_target_speed_pal(void);
s32 hero_play_sound(s32 index, s32 flags);
s32 hero_get_step_offset_from_direction_pal(void);
s32 hero_l04_set_move_state_pal(s32, s32);
void hero_start_move_state_walk_or_run(s32 a0);
s32 hero_try_start_transition_pal(void);
s32 hero_try_start_ledge_move(void);
s32 hero_check_fall_transition(void);
s32 ProcessHeroEquippedItemInput_pal(void);
s32 hero_try_start_move_from_buffer_pal(s32 arg0, s32 arg1);
void hero_update_anim_scale_pal(void);
void hero_clear_target_flags(void);
s32 hero_choose_idle_anim_pal(s32 *selected);
void hero_l00_choose_next_move_after_landing_pal(void);
s32 hero_choose_jump_or_roll_move_pal(void);
s32 hero_check_step_ahead_pal(void);
s32 hero_try_start_grab_pal(void);
void UpdateHeroHeldTarget_pal(void);
void hero_update_button_hold_timers_pal(void);
void hero_apply_pending_change_pal(void);
void hero_set_linked_objects_anim_pal(void);
void set_hero_animation_pal(s32 a0, s32 a1, f32 f12);
void hero_clear_queued_anim(void);
void hero_set_anim_mode_pal(s32 value);
f32 hero_find_collision_time(f32 time, f32 acceleration, f32 height);
void hero_set_level_clock_and_bytes(s16, u8, u8, u8, f32, f32);
f32 cam_get_view_space_height(s8 *in);
void cam_set_view_space_height(void *dst, void *src, f32 k);
f32 EvaluateQuantizedHeight(f32 *a0, f32 *a1, s32 *out, f32 scale);
void func_L00_0030C710(s32 argument);
void module_l00_call_handler_with_arg_4_pal(s32 argument);
f32 math_compute_falling_step_offset(f32 *a0, f32 *a1, s32 *a2, f32 factor);
f32 weapon_compute_shot_launch_speed(f32 *a, f32 *b, f32 *out, f32 d, f32 e);
void moby_set_flag_bit(u8 *entity, s32 enabled);
s32 PadPressedWithin(u32 mask, s32 arg1, s32 *out);
void *part_spawn_object_relative_particle(s8 *object,void *position,f32 *velocity,s32 *config,s32 flag);
s32 Spline_AdvanceByDistance(void *path, void *out, s32 *index, f32 *offset, s32 wrap, f32 step);
s32 find_nearest_path_point(void *, void *, void *, s32 *, f32 *, s32, f32, f32, f32);
s32 level_get_saved_value(void);
s32 hero_check_surface_contact_pal(s32);
s32 nearest_rail_point(s8 *, void **, s128 *, void *, void *, s32 *, void *, s32, s32);

/* Decides the hero's next action from the current one: checks input, surface contact, items and transitions each frame (PAL). */
void hero_l04_decide_state_transition_pal(void) {
    f32 vec_10[4] __attribute__((aligned(16)));
    f32 vec_20[4] __attribute__((aligned(16)));
    f32 vec_30[4] __attribute__((aligned(16)));
    s32 transition_index;
    s32 val_1;
    s32 val_2;
    f32 fval_1;
    void *ptr_1;
    void *ptr_2;
    void *ptr_3;
    s32 val_3;
    s32 val_4;
    s32 val_5;
    s32 val_6;
    s32 val_7;
    s32 val_8;
    void *hero_target;
    s32 last_action;
    s32 action_step;
    s32 target_anim;
    s32 val_9;
    s32 val_10;
    s32 pad_3c;

    hero_target = FLD(g_hero_state, void *, 0x2290);
    last_action = FLD(g_hero_state, s32, 0x229C);
    action_step = FLD(g_hero_state, s32, 0x2298);
    target_anim = FLD(hero_target, u8, 0x43);
    if (hero_check_surface_contact_pal(1) != 0) {
        goto end;
    }
    UpdateHeroHeldTarget_pal();
    if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
        if ((FLD(g_hero_state, u32, 0x2294) == 0) || (FLD(g_hero_state, u32, 0x2294) == 2)) {
            hero_l04_set_move_state_pal(0x39, 1);
            goto end;
        }
    }
    if (ProcessHeroEquippedItemInput_pal() != 0) {
        goto end;
    }
    if ((hero_check_fall_transition() != 0) || (hero_try_start_ledge_move() != 0) || (hero_try_start_transition_pal() != 0)) {
        goto end;
    }
    if (((FLD(g_pad_state, s32, 0x1A4) & 0x10) || (FLD(g_pad_state, s32, 0x1C4) & 0x10)) && (FLD(g_hero_state, u8, 0x123C) != 2) && (g_hero_l04_input_block == 0) && (g_option_toggle_b[1] == 0) && (g_hero_l04_input_state_word >= 8)) {
        if (((FLD(g_hero_state, u8, 0x22BC) == 0) || (FLD(g_hero_state, u8, 0x22B4) == 1) || (FLD(g_hero_state, s16, 0x1D2) != 0))
            && ((FLD(g_hero_state, u8, 0x22B7) == 0) || (FLD(g_hero_state, u8, 0x22B4) == 1) || (FLD(g_hero_state, s16, 0x1D2) != 0))) {
            if ((FLD(g_hero_state, u8, 0x22B4) == 0) || (FLD(g_hero_state, u8, 0x22B4) == 3)) {
                if (FLD(g_hero_state, s16, 0x24FA) != 0) {
                    FLD(g_hero_state, s16, 0x24F6) = 0x16;
                } else {
                    FLD(g_hero_state, s16, 0x24F6) = 0xC;
                }
                hud_set_slot_contents(0x23, 0, menu_init_panel_layout_pal, weapon_wheel_update_select_pal, weapon_wheel_draw_pal, 0, 0);
                module_l00_call_handler_with_arg_4_pal(0x12C);
                func_L00_0030C710(0x96);
            }
        }
    }
    hero_update_button_hold_timers_pal();
    hero_apply_pending_change_pal();
    if (FLD(g_hero_state, f32, 0x88) < g_hero_l04_speed_threshold) {
        if ((FLD(g_hero_state, f32, 0x31C) > 2.0f) && (FLD(g_hero_state, u8, 0x22B4) != 2) && (FLD(g_hero_state, u32, 0x2294) != 0x74)) {
            hero_l04_set_move_state_pal(0x74, 1);
            goto end;
        }
    }
    switch (FLD(g_hero_state, u32, 0x2294)) {
    case 0x0:
    {
        s32 notcrouch;
        s32 anim;
        u8 *obj;
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l04_set_move_state_pal(1, 1);
            break;
        }
        hero_clear_queued_anim();
        if (FLD(g_hero_state, u8, 0x24EF) != 0) {
            hero_l04_set_move_state_pal(0x82, 1);
            break;
        }
        notcrouch = FLD(g_hero_state, u8, 0x1492) == 0;
        {
        s32 one = 1;
        FLD(g_hero_state, s8, 0x1456) = 0;
        if (FLD(g_hero_state, s32, 0x1334) == 2) {
            obj = FLD(g_hero_state, u8 *, 0x1310);
            if ((obj != NULL) && (FLD(obj, u8, 0x60) & 2) && (FLD(obj, u8, 0x43) != one)) {
                anim_start_blended_pal(obj, one, 0, 6);
            }
            obj = FLD(g_hero_state, u8 *, 0x1314);
            if ((obj != NULL) && (FLD(obj, u8, 0x60) & 2) && (FLD(obj, u8, 0x43) != 1)) {
                anim_start_blended_pal(obj, 1, 0, 6);
            }
        }
        }
        if ((FLD(g_hero_l04_tuning_params, f32, 0x258) > 0.6108653f) || (FLD(g_hero_l04_tuning_params, f32, 0x254) > 0.43633235f)) {
            obj = FLD(g_hero_state, u8 *, 0x1310);
            if ((obj != NULL) && (FLD(obj, u8, 0x43) != 1)) {
                anim_start_blended_pal(obj, 1, 0, 0xA);
            }
            obj = FLD(g_hero_state, u8 *, 0x1314);
            if ((obj != NULL) && (FLD(obj, u8, 0x43) != 1)) {
                anim_start_blended_pal(obj, 1, 0, 0xA);
            }
        }
        anim = math_l00_return_argument(FLD(hero_target, u8, 0x43));
        if ((anim == hero_get_weapon_animation_id(0)) && notcrouch) {
            if (hero_choose_idle_anim_pal(&transition_index) != 0) {
                u8 *rec;
                FLD(g_hero_state, s16, 0x207) = 0x64;
                FLD(g_hero_state, s32, 0x248C) = transition_index;
                rec = g_hero_transition_records + transition_index * 0x70;
                FLD(rec, s32, 0x60) = FLD(rec, f32, 0x5C) * 5e+01f;
                if (FLD(rec, s32, 0x44) != 0) {
                    hero_l04_set_move_state_pal(0x3C, 1);
                } else {
                    set_hero_animation_pal(FLD(rec, s32, 0x48), 0, 1e+01f);
                }
            }
        } else if (FLD(g_hero_state, s32, 0xC28) & 2) {
            s32 keep = 0;
            if ((FLD(g_hero_state, u8, 0x22B8) != 0) && (FLD(g_hero_state, u8, 0x22BA) != 0) && ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == FLD(g_hero_state, s32, 0x24B0)) || (FLD(g_hero_state, s32, 0xE98) != 0))) {
                keep = 1;
            }
            if (keep == 0) {
                FLD(g_hero_state, s8, 0x22B8) = 0;
                if (hero_get_weapon_animation_id(0) == 0x51) {
                    set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 15.0f);
                } else {
                    set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, -2.0f);
                }
            }
        }
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x9) {
            u8 *second_obj = FLD(g_hero_state, u8 *, 0x1314);
            if ((second_obj != NULL) && (FLD(second_obj, u8, 0x43) == 1) && (math_fast_float_d(g_hero_state + 0x24E8) != 0) && (FLD(g_hero_l04_tuning_params, f32, 0x258) < 0.5585054f) && (FLD(g_hero_l04_tuning_params, f32, 0x254) < 0.3490659f) && (FLD(g_hero_state, s32, 0x1334) == 2)) {
                FLD(g_hero_state, s32, 0x24E8) = math_random_int_range(0x5C, 0xE1);
                hero_set_linked_objects_anim_pal();
            }
        }
        if ((FLD(g_hero_state, u8, 0x22B8) != 0) && (FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, u8, 0x22BA) != 0) && (FLD(g_hero_state, s16, 0x24EC) == 0)) {
            s32 slot = hero_slot_item_id(0);
            if (slot != FLD(g_hero_state, s32, 0x24B4)) {
                cancel_hero_item_animation_pal();
            } else {
                s32 want = FLD(g_item_l04_record_table + ((u8 *)g_item_slot_to_record)[slot] * 0xE0, s32, 0x28);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != want) {
                    if (FLD(g_hero_state, s32, 0xE98) != 0) {
                        FLD(g_hero_state, s32, 0xEA4) = 1;
                    }
                    FLD(g_hero_state, s32, 0x24B0) = want;
                    set_hero_animation_pal(want, 0, -4.0f);
                }
            }
        }
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, u8, 0x149A) != 0) && (FLD(g_hero_state, s16, 0x34C) == 0)) {
            hero_l04_set_move_state_pal(0x76, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 4) && (FLD(g_hero_state, f32, 0x31C) > 0.4f)) {
            if ((FLD(g_hero_state, s32, 0x22A0) != 8) || (FLD(g_hero_state, s32, 0x1B8) >= 0xC)) {
                hero_l04_set_move_state_pal(6, 1);
            }
            break;
        }
        if (FLD(g_hero_state, s16, 0x1E0) != 0) {
            break;
        }
        {
            s32 ok = 1;
            if ((FLD(g_hero_state, s32, 0x22A0) == 1) || (FLD(g_hero_state, s32, 0x22A0) == 0x1D)) {
                if (FLD(g_hero_state, s32, 0x1B8) <= 3) {
                    ok = 0;
                }
            }
            if (ok && (FLD(g_hero_state, s16, 0x348) != 1)) {
                if (hero_try_start_move_from_buffer_pal((FLD(g_hero_state, s16, 0x1EE) != 0) ? 1 : 6, 0) != 0) {
                    break;
                }
            }
        }
        if ((FLD(g_hero_state, s16, 0x348) == 1) && (g_hero_l04_lock_flag_b == 0) && (PadPressedWithin(0x40, 6, NULL) != 0)) {
            hero_l04_set_move_state_pal(0x6E, 1);
            break;
        }
        if ((FLD(g_pad_state, s32, 0x1A0) & 8) && (FLD(g_hero_state, s32, 0x340) != 0)) {
            if ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0x1A) || (FLD(g_hero_state, f32, 0xC38) >= 108.0f)) {
                hero_l04_set_move_state_pal(4, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, u8, 0x1492) != 0) && (FLD(g_hero_state, f32, 0x320) > 0.087266475f)) {
            hero_l04_set_move_state_pal(0x2E, 1);
            break;
        }
        {
            s32 go = 1;
            s32 turned;
            if (((FLD(g_hero_state, s32, 0x22A0) == 1) || (FLD(g_hero_state, s32, 0x22A0) == 0x1D)) && (FLD(g_hero_state, s32, 0x1B8) < 0x14) && (FLD(g_hero_state, s16, 0x348) != 1)) {
                hero_resolve_stick_direction(0, 1.0f);
                if ((FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_l04_state, f32, 0x158)) > 1.2217306f) && (fast_vec_dist(g_hero_state + 0x80, g_hero_l04_state + 0x140) < 2.5f)) {
                    go = 0;
                }
            }
            turned = hero_is_turned_past_angle(0.17453295f);
            if (go == 0) {
                break;
            }
            if ((turned != 0) || (FLD(g_hero_state, f32, 0x24B8) > 0.22f)) {
                s32 side = FLD(g_hero_state, u8, 0x149D);
                hero_play_footstep_sound_dust_pal(side, 0, 0, 0x1E);
                hero_play_footstep_sound_dust_pal(side, 1, 0, 0x1E);
                hero_l04_set_move_state_pal(2, 1);
            }
        }
        break;
    }
    case 0x3C:
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l04_set_move_state_pal(1, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) != 0) || ((pad_3c = FLD(g_pad_state, s32, 0x1A0)) & 0x40) || (pad_3c & 8)) {
            hero_l04_set_move_state_pal(0x3D, 1);
            break;
        }
        hero_update_target_speed_pal();
        if (FLD(g_hero_state, f32, 0x1B0) > 0.0f) {
            hero_l04_set_move_state_pal(0x3D, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_clear_target_flags();
            hero_l04_set_move_state_pal(0, 1);
        }
        break;
    case 0x3D:
        if (FLD(g_hero_state, s32, 0x1B8) < 8) {
            break;
        }
        hero_clear_target_flags();
        if (FLD(g_hero_state, s16, 0x34E) != 0) {
            hero_l04_set_move_state_pal(6, 1);
            break;
        }
        if (hero_try_start_move_from_buffer_pal(6, 0) != 0) {
            break;
        }
        if (FLD(g_pad_state, s32, 0x1A0) & 8) {
            hero_l04_set_move_state_pal(4, 1);
            break;
        }
        hero_update_target_speed_pal();
        if (FLD(g_hero_state, f32, 0x1B0) > 0.0f) {
            hero_l04_set_move_state_pal(2, 1);
            break;
        }
        hero_l04_set_move_state_pal(0, 1);
        break;
    case 0x39:
    case 0x43:
    case 0x5F:
    case 0x67:
    case 0x7D:
    case 0x7F:
        if ((FLD(g_hero_state, s32, 0xC28) & 2) || (FLD(g_hero_state, u8, 0x22C0) != 0)) {
            if (FLD(g_hero_state, s16, 0x21E) != 0) {
                FLD(g_hero_state, u8, 0x22C0) = 1;
                FLD(g_hero_state, s32, 0xC20) = 0;
                FastDecTimer(g_hero_state + 0x21E);
                return;
            }
            hero_record_play_counters_pal();
            return;
        }
        break;
    case 0x7C:
        if (FLD(g_hero_state, s32, 0x1B8) < 0xB8) {
            break;
        }
        hero_record_play_counters_pal();
        return;
    case 0x32:
    case 0x34:
    {
        u32 st = FLD(g_hero_state, u32, 0x2294);
        if (st == 0x32) {
            f32 h;
            FLD(g_hero_state, f32, 0xC20) = FLD(g_hero_state, f32, 0x1B4) * 12.5f;
            if (FLD(g_hero_state, f32, 0xC20) < 0.25f) {
                FLD(g_hero_state, f32, 0xC20) = 0.25f;
            }
            if (FLD(g_hero_state, f32, 0xC20) > 0.75f) {
                FLD(g_hero_state, f32, 0xC20) = 0.75f;
            }
            if ((FLD(g_hero_state, u32, 0x2294) == st) && !(FLD(g_pad_state, s32, 0x1A0) & 0xC0) && ((h = FLD(g_hero_state, f32, 0xC38)) > 9.0f) && (h < 19.0f) && (FLD(g_hero_state, s32, 0x2298) != 1) && (FLD(g_hero_state, f32, 0x24B8) < 0.1f) && (FLD(g_hero_state, f32, 0x1B4) < 0.040000003f)) {
                hero_l04_set_move_state_pal(0x33, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_pad_state, s32, 0x1A0) & 0xA)) {
            if ((FLD(g_hero_state, u32, 0x2294) == 0x32) && (FLD(g_hero_state, s32, 0x1B8) >= 0x12)) {
                hero_l04_set_move_state_pal(0x34, 1);
                break;
            }
        } else if (FLD(g_hero_state, u32, 0x2294) == 0x34) {
            if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
                hero_l04_set_move_state_pal(0x32, 1);
                break;
            }
        }
        if (FLD(g_hero_state, u32, 0x2294) == 0x34) {
            s32 pad = FLD(g_pad_state, s32, 0x1A0);
            if (!(pad & 0xC0) && (FLD(g_hero_state, s32, 0x2298) != 1) && (FLD(g_hero_state, f32, 0x24B8) < 0.7f) && !(pad & 0xA)) {
                hero_l04_set_move_state_pal(0x33, 1);
            }
        }
        break;
    }
    case 0x33:
    {
        s32 pad;
        if ((FLD(g_hero_state, s32, 0xC28) & 2) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0x3C)) {
            set_hero_animation_pal(0x3C, 0, 9.0f);
        }
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.2f) || ((pad = FLD(g_pad_state, s32, 0x1A0)) & 0xC0) || ((FLD(g_hero_state, s16, 0x24FC) == 0) && (pad & 0xA))) {
            if (FLD(g_hero_state, s16, 0x24FC) != 0) {
                hero_l04_set_move_state_pal(0x32, 1);
            } else if (FLD(g_pad_state, s32, 0x1A0) & 0xA) {
                hero_l04_set_move_state_pal(0x34, 1);
            } else {
                hero_l04_set_move_state_pal(0x32, 1);
            }
        }
        break;
    }
    case 0x36:
        if ((FLD(g_hero_state, s16, 0x1F8) == 0) && (PadPressedWithin(0x40, 7, NULL) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0x9)) {
            hero_l04_set_move_state_pal(0x12, 1);
            break;
        }
        FLD(g_hero_state, u8, 0x22B7) = 1;
        if ((FLD(g_hero_state, s16, 0x1FE) == 0) && (FLD(FLD(FLD(g_hero_state, u8 *, 0x2290), u8 *, 0x24), s32, 0x134) != 0)) {
            if ((PadPressedWithin(0x80, 6, NULL) != 0) || ((FLD(g_hero_state, s16, 0x24FC) == 0) && (PadPressedWithin(0xA, 6, NULL) != 0))) {
                if (FLD(g_hero_state, s16, 0x24FC) != 0) {
                    hero_l04_set_move_state_pal(0x32, 1);
                } else if (FLD(g_pad_state, s32, 0x1A0) & 0xA) {
                    hero_l04_set_move_state_pal(0x34, 1);
                } else {
                    hero_l04_set_move_state_pal(0x32, 1);
                }
                break;
            }
        }
        if ((FLD(g_hero_state, u8, 0x22B9) != 0) && (FLD(g_hero_state, f32, 0x24C4) < 0.4f) && (hero_l04_set_move_state_pal(0, 0) != 0)) {
            set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 15.0f);
        }
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.2f) && (FLD(g_hero_state, s32, 0x1B8) >= 0x9)) {
            hero_l04_set_move_state_pal(0x35, 1);
        }
        break;
    case 0x35:
        if ((FLD(g_hero_state, s16, 0x1F8) == 0) && (PadPressedWithin(0x40, 7, NULL) != 0)) {
            hero_l04_set_move_state_pal(0x12, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x1FE) == 0) && (FLD(FLD(FLD(g_hero_state, u8 *, 0x2290), u8 *, 0x24), s32, 0x134) != 0) && (PadPressedWithin(0x80, 6, NULL) != 0)) {
            if (FLD(g_hero_state, s16, 0x24FC) != 0) {
                hero_l04_set_move_state_pal(0x32, 1);
            } else if (FLD(g_pad_state, s32, 0x1A0) & 0xA) {
                hero_l04_set_move_state_pal(0x34, 1);
            } else {
                hero_l04_set_move_state_pal(0x32, 1);
            }
            break;
        }
        if ((FLD(g_hero_state, u8, 0x22B9) != 0) && (FLD(g_hero_state, f32, 0x24C4) < 0.7f)) {
            hero_l04_set_move_state_pal(0x70, 0);
            set_hero_animation_pal(0x59, 0, 14.0f);
            FLD(g_hero_state, s32, 0xF8) = 0;
            FLD(g_hero_state, s32, 0x118) = 0;
        }
        if ((FLD(g_hero_state, f32, 0x24B8) < 0.1f) && (FLD(g_hero_state, f32, 0x1B4) == 0.0f) && (FLD(g_hero_state, s32, 0x798) == 0)) {
            hero_l04_set_move_state_pal(0x36, 1);
        }
        break;
    case 0x73:
        if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
            hero_l04_set_move_state_pal(0x67, 1);
            set_hero_animation_pal(0x58, 0x28, 15.0f);
        } else if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l04_set_move_state_pal(0x33, 1);
        } else if (FLD(g_hero_state, s32, 0x1B8) >= 0x2B) {
            hero_l04_set_move_state_pal(0x33, 0);
        }
        break;
    case 0x72:
        if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
            hero_l04_set_move_state_pal(0x67, 1);
            set_hero_animation_pal(0x58, 0x25, 15.0f);
        } else if (FLD(g_hero_state, s32, 0x1B8) >= 0x2B) {
            hero_l04_set_move_state_pal(0x36, 0);
        }
        break;
    case 0x1:
    {
        u8 *p;
        s32 ok;
        s32 late;
        s32 anim;
        if ((FLD(g_hero_state, u8, 0x22B4) == 0) && ((FLD(g_hero_state, u8, 0x22BA) == 0) || (FLD(g_hero_state, u8, 0x22B5) != 0))) {
            if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                set_hero_animation_pal(0xD, 0, 7.0f);
            } else {
                s32 anim0 = hero_get_weapon_animation_id(1);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != anim0) {
                    set_hero_animation_pal(anim0, 0, 7.0f);
                }
            }
        }
        p = FLD(g_hero_state, u8 *, 0x1220);
        ok = 1;
        if ((p != NULL) && (moby_is_class_71(p) != 0)) {
            if (FLD(p, u8, 0x20) != 0) {
                ok = 0;
            }
        }
        late = 0;
        if (FLD(g_hero_state, u8, 0x22B5) == 0) {
            late = FLD(g_hero_state, s32, 0x1B8) >= 0x1A;
        }
        if ((!(FLD(g_pad_state, s32, 0x1A0) & 4) && ok) || late) {
            if (FLD(g_hero_state, u8, 0x22B4) != 0) {
                hero_start_move_state_walk_or_run(0);
            } else if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                hero_l04_set_move_state_pal(4, 1);
            } else {
                hero_l04_set_move_state_pal(0, 0);
                anim = hero_get_weapon_animation_id(1);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation_pal(anim, 0, 7.0f);
                }
            }
        }
        break;
    }
    case 0x2F:
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230)) && (FLD(g_hero_state, s16, 0x1EC) == 0)) {
            if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x36) {
                hero_l04_set_move_state_pal(0, 0);
            } else {
                hero_l04_set_move_state_pal(0, 1);
            }
        }
        break;
    case 0x14:
    {
        u8 *rec;
        s32 frames;
        if (FLD(g_hero_state, u32, 0x2294) == 0x14) {
            s32 n = FloatToInt(hero_find_collision_time(60.0f, 0.052f, -1.0f));
            f32 c00 = FLD(g_hero_state, f32, 0xC00);
            s32 top = 0x1A;
            if (c00 == 0.0f) {
                FLD(g_hero_state, f32, 0xC20) = 0.33f;
            } else if ((c00 != 0.0f) && (FLD(g_hero_state, s16, 0x34E) != 0) && (n != 0) && (((f32)top - FLD(g_hero_state, f32, 0xC38)) > 1.0f)) {
                AdjustHeroAnimationSpeedForTargetFrame((f32)top, (f32)n, 0.5f, -1.0f);
                if ((FLD(g_hero_state, f32, 0x31C) < 0.7f) && (FLD(g_hero_state, f32, 0xC20) < 0.75f)) {
                    FLD(g_hero_state, f32, 0xC20) = 0.75f;
                }
            } else if ((FLD(g_hero_state, s16, 0x34E) == 0) && (FLD(g_hero_state, f32, 0xC38) < (f32)top)) {
                FLD(g_hero_state, f32, 0xC20) = 2.0f;
            } else {
                FLD(g_hero_state, f32, 0xC20) = 1.0f;
            }
        }
        rec = g_hero_state_entries + FLD(g_hero_state, s16, 0xBFC) * 0x2C;
        frames = (FloatToInt(FLD(g_hero_state, f32, 0xC38)) - FLD(rec, s32, 0xC)) * 2;
        if ((f32)FLD(rec, s32, 0x14) < FLD(g_hero_state, f32, 0xC38)) {
            if (FLD(g_hero_state, s32, 0xC2C) != 0) {
                break;
            }
            if (PadPressedWithin(0x40, frames, NULL) != 0) {
                if (!(FLD(g_pad_state, s32, 0x1A0) & 8)) {
                    hero_l04_set_move_state_pal(7, 1);
                    break;
                }
                if (hero_choose_jump_or_roll_move_pal() != 0) {
                    break;
                }
            }
        }
        if ((FLD(g_hero_state, s32, 0xC2C) == 0) && ((f32)FLD(rec, s32, 0x18) < FLD(g_hero_state, f32, 0xC38))) {
            hero_l04_set_move_state_pal(0, 0);
        }
        break;
    }
    case 0x13:
    case 0x15:
    {
        u8 *rec = g_hero_state_entries + FLD(g_hero_state, s16, 0xBFC) * 0x2C;
        s32 frames = (FloatToInt(FLD(g_hero_state, f32, 0xC38)) - FLD(rec, s32, 0xC)) * 2;
        u32 st = FLD(g_hero_state, u32, 0x2294);
        s32 lim;
        f32 h;
        if (st == 0x15) {
            frames = 7;
        }
        if ((f32)FLD(rec, s32, 0x14) < FLD(g_hero_state, f32, 0xC38)) {
            if (FLD(g_hero_state, s32, 0xC2C) != 0) {
                goto tail13;
            }
            if ((st != 0x15) || (FLD(g_hero_state, s16, 0x348) != 1)) {
                if (PadPressedWithin(0x40, frames, NULL) != 0) {
                    if (!(FLD(g_pad_state, s32, 0x1A0) & 8)) {
                        hero_l04_set_move_state_pal(7, 1);
                        break;
                    }
                    if (hero_choose_jump_or_roll_move_pal() != 0) {
                        break;
                    }
                }
            }
        }
        if (FLD(g_hero_state, s32, 0xC2C) != 0) {
            goto tail13;
        }
        if ((FLD(g_hero_state, f32, 0xC38) > 34.0f) && (FLD(g_hero_state, f32, 0x24B8) > 0.9f)) {
            hero_l04_set_move_state_pal(2, 0);
            set_hero_animation_pal(3, g_hero_l04_animation_ids[FLD(g_hero_state, s32, 0x2298)], 11.0f);
            break;
        }
        if (FLD(g_hero_state, s32, 0xC2C) != 0) {
            goto tail13;
        }
        lim = FLD(rec, s32, 0x18);
        h = FLD(g_hero_state, f32, 0xC38);
        if ((f32)lim < h) {
            if (FLD(g_hero_state, f32, 0x24B8) > 0.8f) {
                hero_l04_set_move_state_pal(2, 1);
                break;
            }
            if ((f32)(lim + 5) < h) {
                hero_l04_set_move_state_pal(0, 0);
                break;
            }
            if (FLD(g_hero_state, s32, 0xC28) & 2) {
                hero_l04_set_move_state_pal(0, 0);
            }
            break;
        }
    tail13:
        if (FLD(g_hero_state, u32, 0x2294) == 0x15) {
            if (FLD(g_hero_state, s32, 0x1248) != 0xA) {
                hero_l04_set_move_state_pal(0, 1);
                break;
            }
            if ((FLD(g_hero_state, s32, 0x1B8) >= 0x54) && (FLD(g_hero_state, s32, 0xC44) < 0x1A)) {
                hero_set_anim_mode_pal(2);
                FLD(g_hero_state, s32, 0xC44) = 0x1A;
            }
        }
        break;
    }
    case 0x83:
        if (FLD(g_hero_state, f32, 0xC38) > 37.0f) {
            if (FLD(g_hero_state, s32, 0xC2C) != 0) {
                goto tail83;
            }
            if (PadPressedWithin(0x40, 6, NULL) != 0) {
                if (!(FLD(g_pad_state, s32, 0x1A0) & 8)) {
                    hero_l04_set_move_state_pal(7, 1);
                    break;
                }
                if (hero_choose_jump_or_roll_move_pal() != 0) {
                    break;
                }
            }
        }
        if ((FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0xC38) > 37.0f)) {
            hero_l04_set_move_state_pal(0, 0);
            set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 12.0f);
            break;
        }
    tail83:
        if ((FLD(g_hero_state, u32, 0x2294) == 0x15) && (FLD(g_hero_state, s32, 0x1B8) >= 0x54) && (FLD(g_hero_state, s32, 0xC44) < 0x1A)) {
            hero_set_anim_mode_pal(2);
            FLD(g_hero_state, s32, 0xC44) = 0x1A;
        }
        break;
    case 0x77:
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l04_set_move_state_pal(0, 1);
        }
        break;
    case 0x2:
    case 0x2E:
    case 0x70:
    {
        s32 n;
        s32 turned;
        u32 st;
        if ((FLD(g_hero_state, u8, 0x40E) != 0) && ((FLD(hero_target, f32, 0x44) > 0.9f) || (FLD(hero_target, u8, 0x42) != 0xFF))) {
            FLD(g_hero_state, u8, 0x40E) = 0;
        }
        if ((FLD(g_hero_state, u8, 0x149A) != 0) && (FLD(g_hero_state, s16, 0x34C) == 0)) {
            hero_l04_set_move_state_pal(0x76, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 4) && ((FLD(g_hero_state, s32, 0x22A4) != 0x12) || (FLD(g_hero_state, u8, 0x22B9) == 0)) && (FLD(g_hero_state, f32, 0x31C) > 1.35f) && (hero_check_step_ahead_pal() == 0)) {
            hero_l04_set_move_state_pal(6, 1);
            break;
        }
        n = 7;
        if (FLD(g_hero_state, s16, 0x1EE) != 0) {
            n = 1;
        }
        if ((PadPressedWithin(0x40, n, NULL) != 0) && ((FLD(g_hero_state, s16, 0x34E) < 4) || (FLD(g_hero_state, s16, 0x202) != 0))) {
            hero_resolve_stick_direction(0, 1.0f);
            if (hero_try_start_move_from_buffer_pal(n, 1) != 0) {
                break;
            }
            if (FLD(g_hero_state, f32, 0x24B8) > 0.85f) {
                if (FLD(g_hero_state, s16, 0x1454) == 0) {
                    hero_l04_set_move_state_pal(9, 1);
                } else {
                    hero_l04_set_move_state_pal(7, 1);
                }
            } else {
                hero_l04_set_move_state_pal(7, 1);
            }
            break;
        }
        if (FLD(g_hero_state, s16, 0x34E) != 0) {
            break;
        }
        if (((FLD(g_hero_state, u8, 0x1492) == 0) || ((FLD(g_hero_state, f32, 0x174) < 0.040000003f) && (FLD(g_hero_state, f32, 0x320) < 0.087266475f))) && (FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l04_set_move_state_pal(1, 1);
            break;
        }
        if (FLD(g_pad_state, s32, 0x1A0) & 8) {
            hero_l04_set_move_state_pal(4, 1);
            break;
        }
        if ((FLD(g_hero_state, u8, 0x1492) != 0) && (FLD(g_hero_state, u32, 0x2294) == 0x2E)) {
            f32 speed = vec_length_xy(g_hero_state + 0x110);
            s32 anim;
            if ((FLD(g_hero_state, f32, 0x24B8) < 0.17f) && ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x37) || (((anim = FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43)) == hero_get_weapon_animation_id(0)) && (FLD(g_hero_state, f32, 0x320) > 0.087266475f))) && (FLD(g_hero_state, s32, 0x1CC) >= 8) && (FLD(g_hero_state, s32, 0xC2C) == 0)) {
                set_hero_animation_pal(0x66, 0, 12.0f);
            } else if ((FLD(g_hero_state, f32, 0x24B8) > 0.3f) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0x37) && (FLD(g_hero_state, s32, 0xC2C) == 0)) {
                set_hero_animation_pal(0x37, 0, 12.0f);
            } else if ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x66) && (FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0x24B8) < 0.17f) && (FLD(g_hero_state, f32, 0x320) < 0.087266475f) && (speed < 0.034f)) {
                set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 17.0f);
            }
        }
        st = FLD(g_hero_state, u32, 0x2294);
        if ((st == 2) || (st == 0x7B)) {
            if (FLD(g_hero_state, u8, 0x1492) != 0) {
                hero_l04_set_move_state_pal(0x2E, 1);
            }
        } else if (st == 0x2E) {
            if (FLD(g_hero_state, u8, 0x1492) == 0) {
                hero_l04_set_move_state_pal(2, 1);
            }
        }
        st = FLD(g_hero_state, u32, 0x2294);
        if (st == 2) {
            if (FLD(g_hero_state, u8, 0x22B9) != 0) {
                hero_l04_set_move_state_pal(0x70, 1);
            }
        } else if (st == 0x70) {
            if (FLD(g_hero_state, u8, 0x22B9) == 0) {
                hero_l04_set_move_state_pal(2, 1);
            }
        }
        turned = hero_is_turned_past_angle(0.03490659f);
        st = FLD(g_hero_state, u32, 0x2294);
        if (st == 2) {
            if (((FLD(g_hero_state, f32, 0x24B8) < 0.17f) || (FLD(g_hero_state, s16, 0x1E0) != 0)) && (turned == 0) && ((FLD(g_hero_state, s32, 0x40D) == 0) || (math_fabs(FLD(g_hero_state, f32, 0x1A8)) < 0.017453294f))) {
                s32 anim;
                if (hero_try_start_grab_pal() != 0) {
                    break;
                }
                if (hero_l04_set_move_state_pal(0, 0) == 0) {
                    break;
                }
                vec_clamp_length(g_hero_state + 0x160, 0.030000001f);
                if (FLD(g_hero_state, f32, 0x1B4) > 0.030000001f) {
                    FLD(g_hero_state, f32, 0x1B4) = 0.030000001f;
                }
                anim = hero_get_weapon_animation_id(1);
                if (anim == 0x51) {
                    set_hero_animation_pal(0x51, 0, 12.0f);
                } else {
                    set_hero_animation_pal(anim, 0, -1.0f);
                }
            } else {
                hero_update_anim_scale_pal();
            }
        } else if (st == 0x2E) {
            if ((FLD(g_pad_state, s32, 0x1D4) != 0) && (vec_length_xy(g_hero_state + 0xF0) < 0.001f) && (FLD(g_hero_state, f32, 0x320) < 0.087266475f) && (hero_l04_set_move_state_pal(0, 0) != 0)) {
                set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 14.0f);
            }
            if (FLD(hero_target, u8, 0x43) == 0x37) {
                FLD(g_hero_state, f32, 0xC20) = (1.0f - FLD(g_hero_state, f32, 0x400)) * 2.0f;
                if (FLD(g_hero_state, f32, 0xC20) > 1.7f) {
                    FLD(g_hero_state, f32, 0xC20) = 1.7f;
                }
                if (FLD(g_hero_state, f32, 0xC20) < 0.75f) {
                    FLD(g_hero_state, f32, 0xC20) = 0.75f;
                }
            } else if (FLD(hero_target, u8, 0x43) == 0x66) {
                FLD(g_hero_state, f32, 0xC20) = FLD(g_hero_state, f32, 0x170) * 8.333334f;
                if (FLD(g_hero_state, f32, 0xC20) > 1.1f) {
                    FLD(g_hero_state, f32, 0xC20) = 1.1f;
                }
                if (FLD(g_hero_state, f32, 0xC20) < 0.3f) {
                    FLD(g_hero_state, f32, 0xC20) = 0.3f;
                }
            }
        } else if (st == 0x70) {
            if ((FLD(g_pad_state, s32, 0x1D4) != 0) && (vec_length_xy(g_hero_state + 0xF0) < 0.064f) && (hero_l04_set_move_state_pal(0, 0) != 0)) {
                set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 14.0f);
            }
            FLD(g_hero_state, f32, 0xC20) = FLD(g_hero_state, f32, 0x170) * 29.166668f;
            if (FLD(g_hero_state, f32, 0xC20) < 0.6f) {
                FLD(g_hero_state, f32, 0xC20) = 0.6f;
            }
            if (FLD(g_hero_state, f32, 0xC20) > 1.05f) {
                FLD(g_hero_state, f32, 0xC20) = 1.05f;
            }
        }
        break;
    }
    case 0x7B:
    {
        s32 one = 1;
        s32 flag = 0;
        if (FLD(g_hero_state, s16, 0x348) != 0) {
            flag = 1;
        }
        if (!(FLD(g_pad_state, s32, 0x1A0) & 8)) {
            if (FLD(g_hero_state, s32, 0x1B8) >= 0x33) {
                flag = one;
            }
        }
        if (FLD(g_hero_state, u8, 0x22B8) != 0) {
            flag = one;
        }
        if (flag != 0) {
            if (FLD(g_hero_state, s32, 0x2304) != 0) {
                FLD(g_hero_state, s32, 0x2320) = one;
            }
            hero_play_sound(9, 0);
            FLD(g_hero_state, s16, 0x1E0) = 0x19;
            hero_l04_set_move_state_pal(3, 0);
            set_hero_animation_pal(6, 4, 9.0f);
        } else {
            if (FLD(g_hero_state, u8, 0x287) != 0) {
                f32 a = FastVecLength(g_hero_state + 0x110);
                if (a < FastVecLength(g_hero_state + 0xF0) * 0.75f) {
                    hero_l04_set_move_state_pal(0x77, 1);
                    break;
                }
                if (hero_test_reach_blend(NULL, 1.0f, 1.25f) != 0) {
                    hero_l04_set_move_state_pal(0x77, 1);
                    break;
                }
            }
            *(s128 *)vec_30 = 0;
            vec_30[0] = -0.10000001f;
            moby_transform_joint_to_world(FLD(g_hero_state, s8 *, 0x2290), 0x16, (s8 *)vec_10);
            moby_transform_joint_to_world(FLD(g_hero_state, s8 *, 0x2290), 0x17, (s8 *)vec_20);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), vec_10, vec_30, (s32 *)g_hero_l04_particle_params_a, 1);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), vec_10, vec_30, (s32 *)g_hero_l04_particle_params_b, 1);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), vec_20, vec_30, (s32 *)g_hero_l04_particle_params_a, 1);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), vec_20, vec_30, (s32 *)g_hero_l04_particle_params_b, 1);
        }
        break;
    }
    case 0x62:
        if (vec_distance_xy(g_hero_state + 0x80, g_hero_state + 0x18A0) < 0.2f) {
            if ((FLD(g_hero_state, f32, 0x170) < 0.054000005f) && (FastDiffRots(FLD(g_hero_state, f32, 0x98), FLD(g_hero_state, f32, 0x18AC)) < 0.03490659f)) {
                hero_l04_set_move_state_pal(0x64, 1);
                break;
            }
            if ((FLD(g_hero_state, u8, 0x22B4) != 0) && (FLD(g_hero_state, f32, 0x170) >= 0.054000005f)) {
                hero_l04_set_move_state_pal(0x63, 1);
            }
        } else {
            hero_update_anim_scale_pal();
        }
        break;
    case 0x63:
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l04_set_move_state_pal(0x62, 1);
        }
        break;
    case 0x64:
        if ((FLD(g_hero_state, s32, 0xC28) & 2) || (FLD(g_hero_state, s32, 0x18B0) != 0)) {
            hero_l04_set_move_state_pal(0, 1);
        }
        if (vec_distance_xy(g_hero_state + 0x80, g_hero_state + 0x18A0) > 0.2f) {
            hero_l04_set_move_state_pal(0x62, 1);
        }
        break;
    case 0x3:
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l04_set_move_state_pal(1, 1);
            break;
        }
        if (FLD(g_hero_state, s16, 0x1E0) == 0) {
            if (FLD(g_pad_state, s32, 0x1A4) & 0x40) {
                hero_l04_set_move_state_pal(7, 1);
                break;
            }
            if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                hero_l04_set_move_state_pal(4, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 8) && (FLD(g_hero_state, f32, 0x31C) > 0.3f)) {
            hero_l04_set_move_state_pal(6, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l04_set_move_state_pal(0, 1);
            break;
        }
        if (!(FLD(g_hero_state, f32, 0x24B8) > 0.2f) || (FLD(g_hero_state, s16, 0x1E0) != 0)) {
            break;
        }
        if (hero_get_weapon_animation_id(0) != 0x51) {
            if (FLD(g_hero_state, f32, 0x1B4) == 0.0f) {
                hero_l04_set_move_state_pal(0, 0);
                break;
            }
        } else if ((FLD(g_hero_state, f32, 0xC38) > 1e+01f) && (hero_l04_set_move_state_pal(0, 0) != 0)) {
            set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 14.0f);
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            hero_l04_set_move_state_pal(2, 1);
        }
        break;
    case 0x4:
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l04_set_move_state_pal(1, 1);
            break;
        }
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0xA) && !(FLD(g_pad_state, s32, 0x1A0) & 8)) {
            hero_l04_set_move_state_pal(0, 0);
            set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, -2.0f);
            break;
        }
        if ((FLD(g_hero_state, u8, 0x149A) != 0) && (FLD(g_hero_state, s16, 0x34C) == 0)) {
            hero_l04_set_move_state_pal(0x76, 1);
            break;
        }
        if (hero_choose_jump_or_roll_move_pal() != 0) {
            break;
        }
        if ((PadPressedWithin(0x80, 0xC, NULL) != 0) && (FLD(g_hero_state, u8, 0x123A) == 0) && (FLD(g_hero_state, s32, 0x1248) == 0xA)) {
            hero_l04_set_move_state_pal(0x15, 1);
        }
        if (FLD(g_hero_state, s16, 0x34E) >= 8) {
            if ((FLD(g_hero_state, s32, 0x22A0) != 8) || (FLD(g_hero_state, s32, 0x1B8) >= 0xC)) {
                hero_l04_set_move_state_pal(6, 1);
            }
        }
        break;
    case 0x8A:
        if (FLD(g_hero_state, s32, 0x1248) != 0xD) {
            hero_l04_set_move_state_pal(0, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0xB1C) != 0) {
            u8 *obj = FLD(g_hero_state, u8 *, 0xB10);
            if (obj != NULL) {
                moby_set_flag_bit(obj, 1);
            }
            hero_l04_set_move_state_pal(0x8B, 1);
        }
        break;
    case 0x8B:
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x4C) {
            hero_l04_set_move_state_pal(0, 1);
        }
        break;
    case 0x23:
        if (FLD(g_hero_state, s32, 0x1248) != 0xD) {
            hero_l04_set_move_state_pal(0, 1);
        }
        break;
    case 0x24:
    {
        s32 go;
        AdjustHeroAnimationSpeedForTargetFrame(1e+01f, FLD(g_hero_state, f32, 0xAAC), 0.5f, -1.0f);
        if ((FLD(g_hero_state, f32, 0xAAC) < 18.0f) && (FLD(g_hero_state, f32, 0xAAC) < 25.0f)) {
            set_hero_animation_pal(0xA, 0, 13.0f);
        }
        go = 0;
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230))) {
            if (FLD(g_hero_state, f32, 0xAAC) > 21.0f) {
                FLD(g_hero_state, s32, 0xAC8) = 1;
            }
            go = 1;
        }
        if ((FLD(g_hero_state, s32, 0x2298) == 1) && (FLD(g_hero_state, f32, 0xAA0) < 0.080000006f)) {
            go = 1;
        }
        if (go != 0) {
            FLD(g_hero_state, f32, 0x1B4) = FLD(g_hero_state, f32, 0xAA0);
            if (FLD(g_hero_state, f32, 0x1B4) > 0.14000002f) {
                FLD(g_hero_state, f32, 0x1B4) = 0.14000002f;
            }
            if (FLD(g_hero_state, f32, 0x31C) < 0.3f) {
                hero_l04_set_move_state_pal(0, 0);
                set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 25.0f);
                break;
            }
            if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0xA) {
                hero_l04_set_move_state_pal(6, 0);
            } else {
                hero_l04_set_move_state_pal(6, 0);
                set_hero_animation_pal(0xA, 0, 14.0f);
            }
            FLD(g_hero_state, f32, 0xA84) = 0.016800001f;
            FLD(g_hero_state, f32, 0xA80) = 0.011600001f;
            FLD(g_hero_state, s32, 0x24A0) = 0;
        }
        break;
    }
    case 0x25:
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230))) {
            FLD(g_hero_state, f32, 0x1B4) = FLD(g_hero_state, f32, 0xAA0);
            if (FLD(g_hero_state, f32, 0x1B4) > 0.14000002f) {
                FLD(g_hero_state, f32, 0x1B4) = 0.14000002f;
            }
            if (FLD(g_hero_state, f32, 0x31C) < 0.4f) {
                hero_l04_set_move_state_pal(0, 1);
            } else {
                hero_l04_set_move_state_pal(6, 1);
                FLD(g_hero_state, s32, 0x24A0) = 0;
            }
        }
        break;
    case 0x2B:
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230))) {
            s32 t = FLD(g_hero_state, s32, 0x1B8);
            if (t >= 0x9) {
                if (t < 0x21) {
                    FLD(g_hero_state, s32, 0xAC8) = 1;
                }
                hero_l04_set_move_state_pal(0x2C, 1);
                FLD(g_hero_state, f32, 0xA84) = 0.0028000001f;
                FLD(g_hero_state, f32, 0xA80) = 0.0108f;
            }
        }
        break;
    case 0x17:
        if (FLD(g_hero_state, f32, 0xC38) > 13.5f) {
            hero_l04_set_move_state_pal(0x18, 0);
        }
        break;
    case 0x18:
        if ((FLD(g_hero_state, s32, 0xC28) & 2) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x20)) {
            set_hero_animation_pal(0x21, 0, 5.0f);
        }
        hero_resolve_stick_direction(0, 1.0f);
        if (ProbeLedgeGrab_pal((s8 *)(g_hero_state + 0x80), (s8 *)(g_hero_state + 0x90), NULL) == 0) {
            hero_l04_set_move_state_pal(6, 1);
            FLD(g_hero_state, s16, 0x1D0) = 0x8;
            break;
        }
        if (((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 7, NULL) != 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) > 2.3561947f)) || (FLD(g_pad_state, s32, 0x1A4) & 8)) {
            hero_l04_set_move_state_pal(6, 1);
            FLD(g_hero_state, s8, 0x22BF) = 1;
            FLD(g_hero_state, s16, 0x1D0) = 0x8;
            break;
        }
        if (PadPressedWithin(0x40, 0xE, NULL) != 0) {
            hero_l04_set_move_state_pal(0x1B, 1);
            break;
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) < 0.78539824f) {
                qcopy(vec_10, g_hero_state + 0x80);
                vec_10[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) * 0.3f;
                vec_10[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) * 0.3f;
                if (ProbeLedgeGrab_pal((s8 *)vec_10, (s8 *)(g_hero_state + 0x90), NULL) != 0) {
                    hero_l04_set_move_state_pal(0x19, 1);
                }
                break;
            }
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) < 0.78539824f) {
                qcopy(vec_10, g_hero_state + 0x80);
                vec_10[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) * 0.3f;
                vec_10[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) * 0.3f;
                if (ProbeLedgeGrab_pal((s8 *)vec_10, (s8 *)(g_hero_state + 0x90), NULL) != 0) {
                    hero_l04_set_move_state_pal(0x1A, 1);
                }
            }
        }
        break;
    case 0x19:
    case 0x1A:
    {
        f32 side;
        *(s128 *)vec_10 = FLD(g_hero_state + 0x80, s128, 0);
        side = 1.5707965f;
        if (FLD(g_hero_state, u32, 0x2294) == 0x1A) {
            side = -1.5707965f;
        }
        vec_10[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) * 0.3f;
        vec_10[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) * 0.3f;
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, f32, 0x24B8) < 0.5f) || (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) > 0.78539824f) || (ProbeLedgeGrab_pal((s8 *)vec_10, (s8 *)(g_hero_state + 0x90), NULL) == 0)) {
            if (FLD(g_hero_state, s32, 0xC28) & 2) {
                hero_l04_set_move_state_pal(0x18, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 7, NULL) != 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) > 2.3561947f)) {
            hero_l04_set_move_state_pal(6, 1);
            FLD(g_hero_state, s8, 0x22BF) = 1;
            FLD(g_hero_state, s16, 0x1D0) = 0x21;
            break;
        }
        if (PadPressedWithin(0x40, 7, NULL) != 0) {
            hero_l04_set_move_state_pal(0x1B, 1);
        }
        break;
    }
    case 0x76:
        if (FLD(g_hero_state, s32, 0x1B8) >= 0xFB) {
            hero_record_play_counters_pal();
        }
        if (FLD(g_hero_state, u8, 0x149A) == 0) {
            if (FLD(g_hero_state, s16, 0x34E) != 0) {
                hero_l04_set_move_state_pal(6, 1);
            } else {
                hero_l04_set_move_state_pal(0, 1);
            }
        }
        break;
    case 0x6:
    case 0x2C:
        if ((FLD(g_hero_state, s32, 0x2298) == 0) && ((FLD(g_hero_state, s32, 0x1B8) >= 0xF) || (FLD(g_hero_state, f32, 0x31C) > 1.75f))) {
            set_hero_animation_pal(0xB, 0, 13.0f);
            FLD(g_hero_state, s32, 0x2298) = 1;
            if (FLD(g_hero_state, u32, 0x2294) == 0x2C) {
                FLD(g_hero_state, s32, 0x24A0) = 7;
            } else {
                FLD(g_hero_state, s32, 0x24A0) = 0;
            }
        }
        if (FLD(g_hero_state, s16, 0x34E) == 0) {
            hero_play_footstep_effect_pal();
            if (FLD(g_hero_state, f32, 0x118) < -0.18f) {
                FLD(g_hero_state, f32, 0x118) = -0.18f;
            }
            if (FLD(g_hero_state, f32, 0xF8) < -0.18f) {
                FLD(g_hero_state, f32, 0xF8) = -0.18f;
            }
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l04_set_move_state_pal(0x39, 1);
            } else {
                s32 one = 1;
                s32 low = FLD(g_hero_state, s32, 0x33C) == 0;
                if (FLD(g_hero_state, s32, 0x1B8) >= 0x4B) {
                    if (hero_l04_set_move_state_pal(0, 0) != 0) {
                        set_hero_animation_pal(0xC, 4, 5.0f);
                    }
                    if (low != 0) {
                        FLD(g_hero_state, s16, 0x1E0) = 0x12;
                    }
                    hero_set_level_clock_and_bytes(0xA, 4, 0, 1, 0.022f, 0.004f);
                } else if (FLD(g_hero_state, s32, 0x2298) == one) {
                    if (hero_l04_set_move_state_pal(0, 0) != 0) {
                        set_hero_animation_pal(0xC, 9, -1.0f);
                    }
                    cam_set_view_space_height(g_hero_state + 0x160, g_hero_state + 0x160, 0.0f);
                    vec_clamp_length((f32 *)(g_hero_state + 0x160), 0.14000002f);
                    FLD(g_hero_state, s16, 0x1E0) = 6;
                    if (FLD(g_hero_state, s32, 0x22A0) == 0x2C) {
                        FLD(g_hero_state, s16, 0x1E0) = 0x8;
                    }
                    if ((low != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0x2B)) {
                        FLD(g_hero_state, s16, 0x1E0) = 0xF;
                    }
                    hero_set_level_clock_and_bytes(0xA, 2, 0, 1, 0.019f, 0.002f);
                } else if ((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (FLD(g_hero_state, s16, 0x1E0) == 0)) {
                    hero_l04_set_move_state_pal(2, 1);
                    hero_set_level_clock_and_bytes(7, 2, 0, 1, 0.016f, 0.002f);
                } else if (FLD(g_hero_state, f32, 0x174) > 0.060000002f) {
                    if (hero_l04_set_move_state_pal(3, 0) != 0) {
                        set_hero_animation_pal(6, 0, 1e+01f);
                        vec_clamp_length((f32 *)(g_hero_state + 0x160), 0.15400001f);
                    }
                } else {
                    hero_l04_set_move_state_pal(0, 1);
                    hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
                }
            }
        } else if (FLD(g_hero_state, s32, 0x24CC) > 0) {
            if ((FLD(g_pad_state, s32, 0x1A0) & 0x40) && (g_item_owned_flags[2] != 0) && (hero_slot_item_id(3) != 4) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (FLD(g_hero_state, f32, 0x31C) > 0.6f)) {
                hero_l04_set_move_state_pal(8, 1);
                break;
            }
            if ((FLD(g_hero_state, s16, 0x202) >= 0x12) && (hero_try_start_move_from_buffer_pal((FLD(g_hero_state, s16, 0x1EE) != 0) ? 1 : 5, 0) != 0)) {
                break;
            }
            if (FLD(g_hero_state, s32, 0x578) != 0) {
                hero_l04_set_move_state_pal(0x17, 1);
                break;
            }
        }
        break;
    case 0x74:
        if (g_current_map_index == 0xD) {
            f32 y = FLD(g_hero_state, f32, 0x88);
            if ((FLD(g_hero_state, s32, 0x22A4) == 0x1E) || (FLD(g_hero_state, s32, 0x22B0) == 0x1E)) {
                s32 t = FLD(g_hero_state, s32, 0x1B8);
                if (((y < 51.0f) && (t >= 0x1A)) || (t >= 0x1A) && (FLD(g_hero_state, u8, 0x287) != 0) && ((FLD(g_hero_state, f32, 0x118) >= 0.0f) || (FLD(g_hero_state, u8, 0x149B) != 0))) {
                    hero_record_play_counters_pal();
                    return;
                }
            } else if ((y < 89.0f) || ((FLD(g_hero_state, s32, 0x1B8) >= 0x12) && (FLD(g_hero_state, u8, 0x287) != 0) && (FLD(g_hero_state, f32, 0x118) >= 0.0f))) {
                hero_record_play_counters_pal();
                return;
            }
        }
        if (FLD(g_hero_state, s32, 0x1B8) < 0x65) {
            break;
        }
        hero_record_play_counters_pal();
        return;
    case 0x82:
    {
        u8 *p = g_hero_state + 0xF0;
        if (cam_get_view_space_height((s8 *)p) < 0.0f) {
            p -= 0xF0;
            if (FLD(p, s32, 0x340) != 0) {
                u8 *q = FLD(p, u8 *, 0x33C);
                if ((q == NULL) || (FLD(q, s16, 0xAA) == 0x8E2)) {
                    if (hero_l04_set_move_state_pal(0, 0) != 0) {
                        FLD(p, s8, 0x24EF) = 0;
                        set_hero_animation_pal(7, 0x17, 7.0f);
                        hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
                    }
                }
            }
        }
        if (FLD(g_hero_state, f32, 0x5B0) == 0.0f) {
            if (g_current_map_index == 0xD) {
                if (FLD(g_hero_state, f32, 0x318) < 69.0f) {
                    hero_l04_set_move_state_pal(0x74, 1);
                } else {
                    hero_l04_set_move_state_pal(6, 1);
                }
            } else {
                hero_l04_set_move_state_pal(6, 1);
            }
        }
        break;
    }
    case 0x8:
        if ((FLD(g_hero_state, s32, 0x1D4) != 0) && (FLD(g_hero_state, s32, 0x1B8) < 7)) {
            s32 prev = FLD(g_hero_state, s32, 0x22A0);
            s32 ok = 0;
            if ((prev == 7) || (prev == 9) || (prev == 0xE) || (prev == 0x11)) {
                ok = 1;
            }
            if (ok != 0) {
                hero_l04_set_move_state_pal(0x11, 1);
            }
            break;
        }
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0x1A) && !(FLD(g_pad_state, s32, 0x1A0) & 0x40) && !(FLD(g_pad_state, s32, 0x1C0) & 0x40)) {
            hero_l04_set_move_state_pal(6, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x578) != 0) {
            hero_l04_set_move_state_pal(0x17, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) != 0) && !(FLD(g_hero_state, f32, 0x31C) < 0.4f)) {
            break;
        }
        if (FLD(g_hero_state, s32, 0x1B8) < 0x8) {
            FLD(g_hero_state, s16, 0x1EE) = 0xA - FLD(g_hero_state, u16, 0x1B8);
        }
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, s32, 0x22A0) == 0x10) && (FLD(g_hero_state, s32, 0x1B8) < 3)) {
            if (hero_l04_set_move_state_pal(3, 0) != 0) {
                set_hero_animation_pal(5, 0, -1.0f);
                FLD(g_hero_state, s16, 0x1E0) = 0x1C;
            }
            break;
        }
        if (FLD(g_pad_state, s32, 0x1A0) & 8) {
            hero_l04_set_move_state_pal(4, 1);
            hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
            break;
        }
        if ((FLD(g_hero_state, f32, 0x1B0) > g_hero_l04_speed_params[0][2]) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) < 1.5707964f)) {
            if ((FLD(g_hero_state, u8, 0x1492) != 0) || (FLD(g_hero_state, u8, 0x22B9) != 0)) {
                hero_l04_set_move_state_pal(2, 1);
                break;
            }
            hero_l04_set_move_state_pal(2, 0);
            if (FLD(g_hero_state, u32, 0x2294) == 2) {
                FLD(g_hero_state, s32, 0x2298) = 1;
                set_hero_animation_pal(4, 2, 7.0f);
                FLD(g_hero_state, s8, 0x40E) = 1;
            }
            hero_set_level_clock_and_bytes(5, 2, 1, 0, 0.016f, 0.002f);
        } else if (FLD(g_hero_state, f32, 0x1B0) > g_hero_l04_speed_params[0][2]) {
            if ((FLD(g_hero_state, u8, 0x1492) != 0) || (FLD(g_hero_state, u8, 0x22B9) != 0)) {
                hero_l04_set_move_state_pal(2, 1);
                break;
            }
            hero_l04_set_move_state_pal(2, 0);
            if (FLD(g_hero_state, u32, 0x2294) == 2) {
                FLD(g_hero_state, s32, 0x2298) = 1;
                set_hero_animation_pal(4, g_hero_l04_animation_id, 1e+01f);
            }
            hero_set_level_clock_and_bytes(5, 2, 1, 0, 0.016f, 0.002f);
        } else if (FLD(g_hero_state, s16, 0x34E) == 0) {
            if (hero_l04_set_move_state_pal(0, 0) != 0) {
                set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, -2.0f);
                hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
            }
        } else if (hero_l04_set_move_state_pal(0, 0) != 0) {
            set_hero_animation_pal(7, 0x17, 7.0f);
            hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
        }
        break;
    case 0x7:
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x1B:
    case 0x38:
    case 0x66:
    case 0x6E:
    case 0x81:
    case 0x89:
    {
        s32 near;
        s16 lo;
        s32 now;
        u32 st;
        u32 old_action;
        s32 lim;
        s32 frames;
        if (FLD(g_hero_state, u8, 0x52E) != 0) {
            s32 n = hero_get_step_offset_from_direction_pal();
            if ((n > 0) && ((FLD(g_hero_state, s32, 0x1B8) < n) || (FLD(g_hero_state, u8, 0x49C) != 0)) && (FLD(g_hero_state, s32, 0x340) != 0)) {
                if ((FLD(g_hero_state, u32, 0x2294) != 0xB) || (PadPressedWithin(0x40, 6, NULL) != 0)) {
                    s32 go = 1;
                    if ((FLD(g_hero_state, u32, 0x2294) == 0x1B) || (FLD(g_hero_state, u8, 0x49C) != 0)) {
                        if (PadPressedWithin(0x40, 6, NULL) == 0) {
                            go = 0;
                        }
                    }
                    if (FLD(g_hero_state, u32, 0x2294) == 0xB) {
                        if (FLD(g_hero_state, u8, 0x49C) == 0) {
                            go = 0;
                        }
                    }
                    if ((go != 0) && (PadPressedWithin(0x1F000, 4, NULL) != 0) && (FLD(g_pad_state, s32, 0x1A0) & 8)) {
                        hero_l04_set_move_state_pal(0xB, 1);
                        break;
                    }
                }
            }
        }
        if ((FLD(g_hero_state, s16, 0x1F2) != 0) && ((FLD(g_hero_state, u32, 0x2294) == 7) || (FLD(g_hero_state, u32, 0x2294) == 9)) && (FLD(g_hero_state, s32, 0x1B8) < 0x11)) {
            hero_l04_set_move_state_pal(0x82, 1);
            break;
        }
        if ((FLD(g_hero_state, u32, 0x2294) == 0x1B) && (FLD(g_hero_state, s32, 0x1B8) >= 0x12) && (FLD(g_hero_state, f32, 0x278) > 0.7f)) {
            FLD(g_hero_state, s8, 0x22BF) = 0;
            FLD(g_hero_state, s8, 0x22BC) = 0;
        }
        if ((FLD(g_hero_state, s32, 0x1B8) < 6) && (PadPressedWithin(8, 2, NULL) != 0) && ((old_action = FLD(g_hero_state, u32, 0x2294)) != 0x10) && (old_action != 0xA) && (old_action != 0x12) && (old_action != 0x38) && (old_action != 0x11) && (old_action != 0xE) && (old_action != 0x66)) {
            if ((hero_slot_item_id(3) == 2) && (g_item_owned_flags[2] != 0) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_hero_state, f32, 0x178) > 0.018000001f)) {
                hero_l04_set_move_state_pal(0xA, 1);
            } else if ((hero_slot_item_id(3) == 3) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_hero_state, f32, 0x178) > 0.018000001f) && (FLD(g_hero_state, s16, 0x1E4) == 0)) {
                hero_l04_set_move_state_pal(0x10, 1);
            }
        }
        {
            if (FLD(g_hero_state, s16, 0x51A) < FLD(g_hero_state, s32, 0x1B8)) {
                if (FLD(g_hero_state, u8, 0x49C) == 0) {
                    hero_l04_set_move_state_pal(6, 1);
                    break;
                }
            } else if ((FLD(g_hero_state, u8, 0x49C) == 0) && ((FLD(g_hero_state, u32, 0x2294) == 0xA) || (FLD(g_hero_state, u32, 0x2294) == 0x10)) && (FLD(g_hero_state, f32, 0x278) < 0.9f) && (FLD(g_hero_state, u8, 0x287) != 0) && (FastVecLength(g_hero_state + 0xF0) > 0.14000002f)) {
                f32 a = FastVecLength(g_hero_state + 0x110);
                if ((a < FastVecLength(g_hero_state + 0xF0) * 0.5f) && (FLD(g_hero_state, s32, 0x578) == 0) && (FLD(g_hero_state, f32, 0x31C) < 2.0f)) {
                    hero_l04_set_move_state_pal(0x77, 1);
                    break;
                }
            }
        }
        near = 0;
        if ((FLD(g_hero_state, u32, 0x2294) == 0xE) && (FLD(g_hero_state, f32, 0xC38) < 35.0f)) {
            near = 1;
        }
        lo = FLD(g_hero_state, s16, 0x4AC);
        now = FLD(g_hero_state, s32, 0x1B8);
        if (!(lo < now)) {
            break;
        }
        if (now == lo + 1) {
            if (FLD(g_hero_state, u8, 0x49D) != 0) {
                f32 left = (f32)(FLD(g_hero_state, s32, 0x430) - now);
                if (left > 0.0f) {
                    AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x438), left, FLD(g_hero_state, f32, 0x514), -1.0f);
                }
            } else if (FLD(g_hero_state, u32, 0x2294) != 0xE) {
                EvaluateQuantizedHeight((f32 *)(g_hero_state + 0x80), (f32 *)(g_hero_state + 0xF0), &val_6, FLD(g_hero_state, f32, 0x520));
                AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4C8), (f32)val_6, FLD(g_hero_state, f32, 0x514), -1.0f);
                if (FLD(g_hero_state, f32, 0xC20) > 1.5f) {
                    FLD(g_hero_state, f32, 0xC20) = 1.5f;
                }
            }
            break;
        }
        if ((FLD(g_hero_state, u8, 0x49D) != 0) && (now >= FLD(g_hero_state, s32, 0x430)) && (now < FLD(g_hero_state, s32, 0x434))) {
            f32 left = (f32)(FLD(g_hero_state, s32, 0x440) - FLD(g_hero_state, s32, 0x430));
            if (left > 0.0f) {
                AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4C8), left, FLD(g_hero_state, f32, 0x514), -1.0f);
            }
            break;
        }
        if (FLD(g_hero_state, s32, 0x338) == 1) {
            hero_play_sound(0xC, 0);
            part_emit_hero_dust_and_debris_pal(3, 0x18, 1);
        }
        {
            u8 c = FLD(g_hero_state, u8, 0x49C);
            if (c != 0) {
                FLD(g_hero_state, u8, 0x49C) = c + 1;
            } else if ((FLD(g_hero_state, s16, 0x34E) == 0) && (FLD(g_hero_state, u8, 0x49E) != 0) && (near == 0)) {
                hero_play_footstep_effect_pal();
                FLD(g_hero_state, u8, 0x49C) = 1;
                FLD(g_hero_state, s8, 0x24DB) = 0;
                if ((FLD(g_hero_state, f32, 0x24B8) < 0.2f) && (FLD(g_hero_state, f32, 0x1B4) > 0.050000004f)) {
                    FLD(g_hero_state, f32, 0x1B4) = 0.050000004f;
                }
                hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
                if (near == 0) {
                    s32 k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 2;
                    if (FLD(g_hero_state, f32, 0xC38) < FLD(g_hero_state, f32, 0x4CC) - 1.5f) {
                        set_hero_animation_pal(math_l00_return_argument(FLD(hero_target, u8, 0x43)), k, 6.0f);
                    }
                }
            }
        }
        if (FLD(g_hero_state, u8, 0x49C) != 0) {
            FLD(g_hero_state, f32, 0xC20) = 1.0f;
        } else if (FLD(g_hero_state, u8, 0x49E) != 0) {
            s32 cur;
            if ((s32)FLD(hero_target, u8, 0x41) < FloatToInt(FLD(g_hero_state, f32, 0x4D0))) {
                if ((FLD(g_hero_state, u32, 0x2294) == 0xE) && (FLD(g_hero_state, f32, 0xC38) < 37.0f)) {
                    ApproachValue((f32 *)(g_hero_state + 0xC20), 1.0f, 0.21600002f);
                } else {
                    FLD(g_hero_state, s16, 0x4AE) = FloatToInt(hero_find_collision_time(60.0f, FLD(g_hero_state, f32, 0x520), -1.0f));
                    AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4CC), (f32)FLD(g_hero_state, s16, 0x4AE), FLD(g_hero_state, f32, 0x514), 0.28800002f);
                }
                if (near == 0) {
                    s32 k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 2;
                    if (FLD(g_hero_state, f32, 0xC20) > 1.8f) {
                        set_hero_animation_pal(math_l00_return_argument(FLD(hero_target, u8, 0x43)), k, (f32)(FLD(g_hero_state, s16, 0x4AE) + 3));
                    }
                }
                if (FLD(g_hero_state, f32, 0xC20) < 0.2f) {
                    FLD(g_hero_state, f32, 0xC20) = 0.2f;
                }
                if (FLD(g_hero_state, f32, 0xC20) > 2.7f) {
                    FLD(g_hero_state, f32, 0xC20) = 2.7f;
                }
            }
            cur = FLD(g_hero_state, u32, 0x2294);
            if ((cur == 9) && ((FLD(g_hero_state, f32, 0x4CC) - FLD(g_hero_state, f32, 0xC38)) > 6.0f) && ((math_l00_return_argument(FLD(hero_target, u8, 0x42)) == 8) || (math_l00_return_argument(FLD(hero_target, u8, 0x42)) == cur)) && (FLD(hero_target, u8, 0x42) == FLD(hero_target, u8, 0x43)) && (FLD(g_hero_state, f32, 0x1B0) < g_hero_l04_speed_params[1][1] * 0.002f) && (FLD(g_hero_state, f32, 0x174) < 0.050000004f)) {
                f32 rate = 7.0f / FLD(g_hero_state, f32, 0xC20);
                s32 at;
                if (rate > 8.0f) {
                    rate = 8.0f;
                }
                at = FloatToInt(FLD(g_hero_state, f32, 0xC38)) + 4;
                set_hero_animation_pal(7, at / 2, rate);
                FLD(g_hero_state, s32, 0x2294) = 7;
            }
            {
                s32 a = FloatToInt(FLD(g_hero_state, f32, 0xC38));
                if (a == FloatToInt(FLD(g_hero_state, f32, 0x4CC))) {
                    FLD(g_hero_state, s32, 0xC20) = 0;
                }
            }
        }
        if (FLD(g_hero_state, u8, 0x49C) != 0) {
            if (FLD(g_hero_state, u32, 0x2294) == 0xA) {
                if (hero_l04_set_move_state_pal(3, 0) != 0) {
                    set_hero_animation_pal(5, 0, -2.0f);
                    FastVecScale(g_hero_state + 0x160, g_hero_state + 0x160, 0.8f);
                }
                break;
            }
            if ((FLD(g_hero_state, u8, 0x149A) == 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (PadPressedWithin(0x40, 7, NULL) != 0) && (FLD(g_hero_state, s16, 0x34E) < 3)) {
                if (!(FLD(g_hero_state, f32, 0x1B0) > g_hero_l04_speed_params[0][2])) {
                    hero_l04_set_move_state_pal(7, 1);
                } else if (!(FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) < 1.0471976f)) {
                    hero_l04_set_move_state_pal(7, 1);
                } else if (g_hero_l04_speed_params[1][1] * 0.017f < FLD(g_hero_state, f32, 0x174)) {
                    hero_l04_set_move_state_pal(9, 1);
                } else {
                    hero_l04_set_move_state_pal(7, 1);
                }
                break;
            }
        }
        if ((FLD(g_hero_state, u8, 0x49C) >= 2) && (FLD(g_hero_state, u32, 0x2294) != 0xA)) {
            hero_l00_choose_next_move_after_landing_pal();
        } else if ((FLD(g_hero_state, u8, 0x49E) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= FLD(g_hero_state, s16, 0x52A)) && (FLD(g_hero_state, f32, 0x31C) > FLD(g_hero_state, f32, 0x510))) {
            hero_l04_set_move_state_pal(6, 1);
        }
        if ((FLD(g_hero_state, u32, 0x2294) == 0x10) && (FLD(g_hero_state, s32, 0x1B8) >= 0x33) && (FLD(g_hero_state, f32, 0x31C) > 1.5f)) {
            hero_l04_set_move_state_pal(6, 1);
            break;
        }
        {
            u32 s = FLD(g_hero_state, u32, 0x2294);
            s32 ok = 0;
            if ((s == 7) || (s == 9) || (s == 0x11)) {
                ok = 1;
            }
            if ((FLD(g_hero_state, s32, 0x1D4) != 0) && (FLD(g_hero_state, u8, 0x49C) == 0) && (ok != 0) && ((FLD(g_hero_state, u32, 0x2294) != 0x11) || (FLD(g_hero_state, s32, 0x1B8) >= 0x16)) && (PadPressedWithin(0x40, 6, &val_7) != 0) && (val_7 < FLD(g_hero_state, s32, 0x1B8))) {
                hero_l04_set_move_state_pal(0x11, 1);
                break;
            }
        }
        if (((FLD(g_hero_state, u32, 0x2294) == 0xA) || (FLD(g_hero_state, u32, 0x2294) == 0x10)) && (FLD(g_hero_state, s32, 0x1B8) >= 0x16) && (FLD(g_hero_state, s16, 0x34A) != 0)) {
            FLD(g_hero_state, s16, 0x526) = 0x11;
        }
        st = FLD(g_hero_state, u32, 0x2294);
        lim = 0x11;
        if (st == 0x10) {
            lim = 7;
        }
        if ((st == 0xE) && (FLD(g_hero_state, f32, 0x31C) > 4.0f)) {
            if ((FLD(g_hero_state, u8, 0x49E) == 0) && (FLD(g_hero_state, f32, 0xC20) < 1.3f)) {
                ApproachValue((f32 *)(g_hero_state + 0xC20), 1.3f, 0.120000005f);
            }
            lim = 0xE;
            FLD(g_hero_state, s16, 0x526) = lim;
        }
        frames = FLD(g_hero_state, s32, 0x1B8) - 4;
        if (frames <= 1) {
            frames = 2;
        }
        if (frames >= 0x1A) {
            frames = 0x19;
        }
        if (!(FLD(g_hero_state, s64, 0x498) & 0xFF0000FF00000000LL)) {
            if ((PadPressedWithin(0x40, frames, NULL) != 0) || (FLD(g_hero_state, u32, 0x2294) == 0xE) || (FLD(g_hero_state, u32, 0x2294) == 0xF) || (FLD(g_hero_state, u32, 0x2294) == 0xD)) {
                if ((FLD(g_hero_state, u32, 0x2294) != 0xE) && (FLD(g_hero_state, u8, 0x22B8) == 0) && ((FLD(g_hero_state, u8, 0x149A) == 0) || (FLD(g_hero_state, f32, 0x31C) >= 0.4f)) && (FLD(g_hero_state, u8, 0x52F) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0xD) && ((FLD(g_hero_state, u8, 0x49E) == 0) || ((FLD(g_hero_state, f32, 0x31C) > 0.7f) && (math_fabs(cam_get_view_space_height((s8 *)(g_hero_state + 0xF0))) < 0.11600001f)))) {
                    hero_l04_set_move_state_pal(0xE, 1);
                } else if ((g_item_owned_flags[2] != 0) && (hero_slot_item_id(3) != 4) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_pad_state, s32, 0x1A0) & 0x40) && (lim < FLD(g_hero_state, s32, 0x1B8)) && (FLD(g_hero_state, s16, 0x526) < FLD(g_hero_state, s32, 0x1B8))) {
                    f32 need = 0.6f;
                    if ((FLD(g_hero_state, u32, 0x2294) == 9) || (FLD(g_hero_state, u32, 0x2294) == 7)) {
                        need = 1.0f;
                    }
                    if (FLD(g_hero_state, u32, 0x2294) == 0xE) {
                        need = 1.5f;
                    }
                    if (need < FLD(g_hero_state, f32, 0x31C)) {
                        hero_l04_set_move_state_pal(8, 1);
                    }
                }
            }
        }
        if ((FLD(g_hero_state, s32, 0x576) != 0) && (FLD(g_hero_state, u32, 0x2294) != 0xB)) {
            hero_l04_set_move_state_pal(0x17, 1);
        }
        break;
    }
    case 0x16:
        if ((FLD(g_hero_state, f32, 0xC38) > 12.5f) && (FLD(g_hero_state, u8, 0x24EF) == 0) && (FLD(g_hero_state, s16, 0x34E) != 0) && (FLD(g_hero_state, f32, 0x31C) > 1.0f)) {
            hero_l04_set_move_state_pal(6, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x17) {
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l04_set_move_state_pal(0x39, 1);
            } else if (FLD(g_hero_state, u8, 0x24EF) != 0) {
                hero_l04_set_move_state_pal(0x82, 1);
            } else {
                hero_l04_set_move_state_pal(0, 0);
            }
        }
        break;
    case 0x8C:
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            set_hero_animation_pal(0x97, 0, 2.0f);
        }
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0x2B) && (FLD(g_hero_state, s16, 0x1E0) == 0)) {
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l04_set_move_state_pal(0x39, 1);
            } else if (hero_l04_set_move_state_pal(0, 0) != 0) {
                set_hero_animation_pal(hero_get_weapon_animation_id(0), 0, 11.0f);
            }
        }
        break;
    case 0x85:
        if ((FLD(g_hero_state, s32, 0x1B8) >= 4) && (FLD(g_pad_state, s32, 0x1A4) & 0x10)) {
            hero_start_move_state_walk_or_run(0);
        }
        break;
    case 0x1D:
        if ((FLD(g_hero_state, u8, 0x22B4) == 0) && ((FLD(g_hero_state, u8, 0x22BA) == 0) || (FLD(g_hero_state, u8, 0x22B5) != 0))) {
            if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                set_hero_animation_pal(0xD, 0, 7.0f);
            } else {
                set_hero_animation_pal(hero_get_weapon_animation_id(1), 0, 7.0f);
            }
        }
        if (!(FLD(g_pad_state, s32, 0x1A0) & 4)) {
            if (FLD(g_hero_state, u32, 0x2294) == 0x1D) {
                s32 anim;
                hero_l04_set_move_state_pal(0, 0);
                anim = hero_get_weapon_animation_id(1);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation_pal(anim, 0, 7.0f);
                }
            }
            g_hero_l04_decide_flag = 0;
        }
        break;
    case 0x1F:
        if ((FLD(g_hero_state, s32, 0x1220) != 0) && (FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0xC38) > 20.0f)) {
            hero_l04_set_move_state_pal(0, 0);
        }
        break;
    case 0x22:
        if (FLD(g_hero_state, f32, 0xC38) > 19.0f) {
            if (PadPressedWithin(0x40, 0x9, NULL) != 0) {
                if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                    hero_choose_jump_or_roll_move_pal();
                    break;
                }
                hero_l04_set_move_state_pal(7, 1);
                break;
            }
        }
        if (FLD(g_hero_state, f32, 0xC38) >= 21.0f) {
            hero_l04_set_move_state_pal(0, 0);
        }
        break;
    default:
        break;
    }
end:
    if (last_action != FLD(g_hero_state, s32, 0x229C)) {
        hero_clear_tracked_slots();
    }
    val_10 = FLD(g_hero_state, s32, 0x22A0);
    if (((val_10 == 0x3C) && (FLD(g_hero_state, s32, 0x2294) != 0x3D)) || ((val_10 == 0x3D) && (FLD(g_hero_state, s32, 0x1854) != 0))) {
        hero_clear_target_flags();
    }
    if (action_step != FLD(g_hero_state, s32, 0x2298)) {
        FLD(g_hero_state, s32, 0x1C0) = 0;
    }
    if (target_anim != FLD(hero_target, u8, 0x43)) {
        FLD(g_hero_state, s32, 0x1C4) = 0;
    }
}
