#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef TI128 s128;
#define NULL ((void *)0)
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern char g_pad_state[];
extern char g_item_slot_to_record[];
extern char g_sound_state[];
extern char g_hero_state[];
extern u8 g_option_toggle_b[] MACRO_ADDR;
extern u8 g_item_owned_flags[] MACRO_ADDR;
extern s32 g_current_map_index;
extern f32 g_hero_l20_speed_params[][4] MACRO_ADDR;
extern s32 g_hero_l20_animation_id_extra;
extern s32 g_hero_l20_lock_flag_b;
extern f32 g_level_shared_float;
extern s32 g_hero_l20_input_block_flag;
extern s32 g_hero_input_lock_flag;
extern s32 g_hero_flag_cleared;
extern u8 g_hero_l20_particle_params_a[16] __attribute__((sda));
extern u8 g_hero_l20_particle_params_b[16] __attribute__((sda));
extern s32 g_hero_l20_animation_ids[2] __attribute__((sda));
extern char g_hero_decision_records[];
extern char g_hero_l20_state_alias[];
typedef struct { s32 w[11]; } Rec2C;
extern Rec2C g_hero_l20_action_table[];
extern char g_item_l20_record_table[];
extern char g_hero_l20_extra_state[];
s32 CollLine(void *, void *, s32, void *, s32);
s32 coll_test_point(void *, s32, void *, f32);
s32 math_fast_float_d(void *);
s32 FastDecTimer(s16 *);
f32 math_fabs(f32);
void FastVecAdd(void *, void *, void *);
void FastVecScale(void *, void *, f32);
f32 FastVecLength(void *);
f32 vec_length_xy(void *);
f32 fast_vec_dist(void *, void *);
f32 vec_distance_xy(void *, void *);
void vec_scale_to_length(void *, void *, f32);
f32 math_fast_sin_or_cos_a(f32);
f32 math_fast_sin_or_cos_b(f32);
f32 FastAddRotations(f32 a0, f32 a1);
f32 FastDiffRots(f32 a0, f32 a1);
s32 FloatToInt(f32);
int hud_set_slot_contents(s32, s32, void *, void *, void *, s32, s32);
void menu_init_panel_layout(u8 *object);
void weapon_wheel_update_select(s8 *);
s32 weapon_wheel_draw(s8 *);
void weapon_wheel_init(void *a0);
void UpdateRadialMenuSelection(u8 *object);
int DrawRadialSelectorPanel();
void moby_transform_joint_to_world(s8 *a0, s32 a1, s8 *a2);
void anim_start_blended(u8 *object, s32 animation, s32 frame, s32 rate);
s32 math_random_int_range(s32 a0, s32 a1);
f32 math_random_float_range(f32 a0, f32 a1);
f32 ApproachValue(f32 *value, f32 target, f32 step);
void vec_clamp_length(f32 *, f32);
void snd_stop_voice(s32 a0);
s32 SelectHeroStateAnimation(s32 arg);
u32 math_l00_return_argument(u32 param_1);
void hero_play_footstep_effect(void);
void hero_play_footstep_sound_dust(s32 kind, s32 side, s32 play_sound, s32 duration);
void hero_clear_tracked_slots(void);
float AdjustHeroAnimationSpeedForTargetFrame(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void part_emit_hero_dust_and_debris(s32 dust, s32 debris, s32 model);
s32 hero_test_reach_blend(f32 *out, f32 scale, f32 amount);
s32 hero_find_ledge_grab(s8 *, s8 *, s8 *);
s32 hero_slot_item_id(s32 index);
void cancel_hero_item_animation(void);
void hero_record_play_counters(void);
s32 moby_is_class_71(u8 *object);
s32 hero_is_turned_past_angle(f32 x);
s32 math_is_below_plane_within_depth(f32 value);
void hero_resolve_stick_direction(s32, f32);
void hero_update_target_speed(void);
s32 hero_play_sound(s32 index, s32 flags);
s32 hero_get_step_offset_from_direction(void);
s32 hero_l20_set_move_state_us2(s32, s32);
void hero_load_state_by_game_mode(s32 a0);
s32 hero_try_start_transition(void);
s32 hero_try_start_ledge_move(void);
s32 hero_check_ledge_fall(void);
s32 hero_select_context_action_us2(void);
s32 hero_try_start_move_from_buffer(s32 arg0, s32 arg1);
void hero_update_anim_scale(void);
void hero_clear_target_flags(void);
s32 hero_choose_idle_anim(s32 *selected);
void hero_choose_next_move_after_landing(void);
s32 hero_choose_jump_or_roll_move(void);
s32 hero_check_step_ahead(void);
s32 hero_try_start_grab(void);
void UpdateHeroHeldTarget(void);
void hero_update_button_hold_timers(void);
void hero_apply_pending_change(void);
void hero_set_linked_objects_anim(void);
void set_hero_animation(s32 a0, s32 a1, f32 f12);
void hero_clear_queued_anim(void);
void hero_set_anim_mode(s32 value);
f32 hero_find_collision_time(f32 time, f32 acceleration, f32 height);
void hero_set_level_clock_and_bytes(s16, u8, u8, u8, f32, f32);
void matrix_mul_vec3(f32 *p, s32 flag, f32 x, f32 y, f32 z);
f32 cam_get_view_space_height(s8 *in);
void cam_set_view_space_height(void *dst, void *src, f32 k);
f32 EvaluateQuantizedHeight(f32 *a0, f32 *a1, s32 *out, f32 scale);
void func_L00_0030C710(s32 argument);
void module_l00_call_handler_with_arg_4_us2(s32 argument);
f32 math_compute_falling_step_offset(f32 *a0, f32 *a1, s32 *a2, f32 factor);
f32 weapon_compute_shot_launch_speed(f32 *a, f32 *b, f32 *out, f32 d, f32 e);
void moby_set_flag_bit(u8 *entity, s32 enabled);
s32 PadPressedWithin(u32 mask, s32 arg1, s32 *out);
void *part_spawn_object_relative_particle(s8 *object,void *position,f32 *velocity,s32 *config,s32 flag);
s32 Spline_AdvanceByDistance(void *path, void *out, s32 *index, f32 *offset, s32 wrap, f32 step);
s32 find_nearest_path_point(void *, void *, void *, s32 *, f32 *, s32, f32, f32, f32);
s32 level_get_saved_value(void);
s32 hero_handle_hazard_contact_us2(s32);
s32 nearest_rail_point(s8 *, void **, s128 *, void *, void *, s32 *, void *, s32, s32);
void hero_update_held_grab(void);
extern void euler_rotation_basis(void *, void *);

/* Decides which state the hero enters next from the pad, contacts and the current state (USA v2.00). */
void hero_l20_decide_state_transition_us2(void) {
    f32 v10[4] __attribute__((aligned(16)));
    f32 v20[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[12] __attribute__((aligned(16)));
    s32 sp40;
    s32 sp44;
    s32 sp48;
    f32 sp4C;
    void *sp50;
    void *sp54;
    void *sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 sp6C;
    s32 sp70;
    s32 sp74w;
    void *sp74;
    s32 sp78;
    s32 sp7C;
    s32 sp80;
    s32 temp_a0_11;
    s32 temp_a0_31;
    s32 pad3C;

    sp74 = FLD(g_hero_state, void *, 0x2290);
    sp78 = FLD(g_hero_state, s32, 0x229C);
    sp7C = FLD(g_hero_state, s32, 0x2298);
    sp80 = FLD(sp74, u8, 0x43);
    if (hero_handle_hazard_contact_us2(1) != 0) {
        goto end;
    }
    UpdateHeroHeldTarget();
    if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
        if ((FLD(g_hero_state, u32, 0x2294) == 0) || (FLD(g_hero_state, u32, 0x2294) == 2)) {
            hero_l20_set_move_state_us2(0x39, 1);
            goto end;
        }
    }
    if (hero_select_context_action_us2() != 0) {
        goto end;
    }
    if ((hero_check_ledge_fall() != 0) || (hero_try_start_ledge_move() != 0) || (hero_try_start_transition() != 0)) {
        goto end;
    }
    if (((FLD(g_pad_state, s32, 0x1A4) & 0x10) || (FLD(g_pad_state, s32, 0x1C4) & 0x10)) && (FLD(g_hero_state, u8, 0x123C) != 2) && (g_hero_l20_input_block_flag == 0) && (g_option_toggle_b[1] == 0) && (g_hero_input_lock_flag >= 8)) {
        if (((FLD(g_hero_state, u8, 0x22BC) == 0) || (FLD(g_hero_state, u8, 0x22B4) == 1) || (FLD(g_hero_state, s16, 0x1D2) != 0))
            && ((FLD(g_hero_state, u8, 0x22B7) == 0) || (FLD(g_hero_state, u8, 0x22B4) == 1) || (FLD(g_hero_state, s16, 0x1D2) != 0))) {
            switch (FLD(g_hero_state, u8, 0x22B4)) {
            case 0:
            case 3:
                if (FLD(g_hero_state, s16, 0x24FA) != 0) {
                    FLD(g_hero_state, s16, 0x24F6) = 0x1B;
                } else {
                    FLD(g_hero_state, s16, 0x24F6) = 0xF;
                }
                hud_set_slot_contents(0x23, 0, menu_init_panel_layout, weapon_wheel_update_select, weapon_wheel_draw, 0, 0);
                module_l00_call_handler_with_arg_4_us2(0x168);
                func_L00_0030C710(0xB4);
                break;
            case 1:
                hud_set_slot_contents(0x23, 0, weapon_wheel_init, UpdateRadialMenuSelection, DrawRadialSelectorPanel, 0, 0);
                break;
            }
        }
    }
    hero_update_button_hold_timers();
    hero_apply_pending_change();
    if (FLD(g_hero_state, f32, 0x88) < g_level_shared_float) {
        if ((FLD(g_hero_state, f32, 0x31C) > 2.0f) && (FLD(g_hero_state, u8, 0x22B4) != 2) && (FLD(g_hero_state, u32, 0x2294) != 0x74)) {
            if (FLD(g_hero_state, u8, 0x22B4) == 4) {
                hero_l20_set_move_state_us2(0x91, 1);
                goto end;
            }
            hero_l20_set_move_state_us2(0x74, 1);
            goto end;
        }
    }
    if ((FLD(g_hero_state, u8, 0x22B4) == 4) && (FLD(g_hero_state, f32, 0x88) < FLD(FLD(FLD(g_hero_state, void *, 0x2290), void *, 0x68), f32, 0x3EC))) {
        hero_l20_set_move_state_us2(0x91, 1);
    }
    switch (FLD(g_hero_state, u32, 0x2294)) {
    case 0x0:
    {
        s32 notcrouch;
        s32 anim;
        u8 *obj;
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l20_set_move_state_us2(1, 1);
            break;
        }
        hero_clear_queued_anim();
        if (FLD(g_hero_state, u8, 0x24EF) != 0) {
            hero_l20_set_move_state_us2(0x82, 1);
            break;
        }
        notcrouch = FLD(g_hero_state, u8, 0x1492) == 0;
        {
        s32 one = 1;
        FLD(g_hero_state, s8, 0x1456) = 0;
        if (FLD(g_hero_state, s32, 0x1334) == 2) {
            obj = FLD(g_hero_state, u8 *, 0x1310);
            if ((obj != NULL) && (FLD(obj, u8, 0x60) & 2) && (FLD(obj, u8, 0x43) != one)) {
                anim_start_blended(obj, one, 0, 7);
            }
            obj = FLD(g_hero_state, u8 *, 0x1314);
            if ((obj != NULL) && (FLD(obj, u8, 0x60) & 2) && (FLD(obj, u8, 0x43) != 1)) {
                anim_start_blended(obj, 1, 0, 7);
            }
        }
        }
        if ((FLD(g_hero_l20_state_alias, f32, 0x258) > 0.6108653f) || (FLD(g_hero_l20_state_alias, f32, 0x254) > 0.43633235f)) {
            obj = FLD(g_hero_state, u8 *, 0x1310);
            if ((obj != NULL) && (FLD(obj, u8, 0x43) != 1)) {
                anim_start_blended(obj, 1, 0, 0xC);
            }
            obj = FLD(g_hero_state, u8 *, 0x1314);
            if ((obj != NULL) && (FLD(obj, u8, 0x43) != 1)) {
                anim_start_blended(obj, 1, 0, 0xC);
            }
        }
        anim = math_l00_return_argument(FLD(sp74, u8, 0x43));
        if ((anim == SelectHeroStateAnimation(0)) && notcrouch) {
            if (hero_choose_idle_anim(&sp40) != 0) {
                u8 *rec;
                FLD(g_hero_state, s16, 0x208) = 0x78;
                FLD(g_hero_state, s32, 0x248C) = sp40;
                rec = g_hero_decision_records + sp40 * 0x70;
                FLD(rec, s32, 0x60) = FLD(rec, f32, 0x5C) * 60.0f;
                if (FLD(rec, s32, 0x44) != 0) {
                    hero_l20_set_move_state_us2(0x3C, 1);
                } else {
                    set_hero_animation(FLD(rec, s32, 0x48), 0, 12.0f);
                }
            }
        } else if (FLD(g_hero_state, s32, 0xC28) & 2) {
            s32 keep = 0;
            if ((FLD(g_hero_state, u8, 0x22B8) != 0) && (FLD(g_hero_state, u8, 0x22BA) != 0) && ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == FLD(g_hero_state, s32, 0x24B0)) || (FLD(g_hero_state, s32, 0xE98) != 0))) {
                keep = 1;
            }
            if (keep == 0) {
                FLD(g_hero_state, s8, 0x22B8) = 0;
                if (SelectHeroStateAnimation(0) == 0x51) {
                    set_hero_animation(SelectHeroStateAnimation(0), 0, 18.0f);
                } else {
                    set_hero_animation(SelectHeroStateAnimation(0), 0, -2.0f);
                }
            }
        }
        if (FLD(g_hero_state, s32, 0x1B8) >= 0xB) {
            u8 *o2 = FLD(g_hero_state, u8 *, 0x1314);
            if ((o2 != NULL) && (FLD(o2, u8, 0x43) == 1) && (math_fast_float_d(g_hero_state + 0x24E8) != 0) && (FLD(g_hero_l20_state_alias, f32, 0x258) < 0.5585054f) && (FLD(g_hero_l20_state_alias, f32, 0x254) < 0.3490659f) && (FLD(g_hero_state, s32, 0x1334) == 2)) {
                FLD(g_hero_state, s32, 0x24E8) = math_random_int_range(0x6E, 0x10E);
                hero_set_linked_objects_anim();
            }
        }
        if ((FLD(g_hero_state, u8, 0x22B8) != 0) && (FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, u8, 0x22BA) != 0) && (FLD(g_hero_state, s16, 0x24EC) == 0)) {
            s32 slot = hero_slot_item_id(0);
            if (slot != FLD(g_hero_state, s32, 0x24B4)) {
                cancel_hero_item_animation();
            } else {
                s32 want = FLD(g_item_l20_record_table + ((u8 *)g_item_slot_to_record)[slot] * 0xE0, s32, 0x28);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != want) {
                    if (FLD(g_hero_state, s32, 0xE98) != 0) {
                        FLD(g_hero_state, s32, 0xEA4) = 1;
                    }
                    FLD(g_hero_state, s32, 0x24B0) = want;
                    set_hero_animation(want, 0, -4.0f);
                }
            }
        }
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, u8, 0x149A) != 0) && (FLD(g_hero_state, s16, 0x34C) == 0)) {
            hero_l20_set_move_state_us2(0x76, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 5) && (FLD(g_hero_state, f32, 0x31C) > 0.4f)) {
            if ((FLD(g_hero_state, s32, 0x22A0) != 8) || (FLD(g_hero_state, s32, 0x1B8) >= 0xF)) {
                hero_l20_set_move_state_us2(6, 1);
            }
            break;
        }
        if (FLD(g_hero_state, s16, 0x1E0) != 0) {
            break;
        }
        {
            s32 ok = 1;
            if ((FLD(g_hero_state, s32, 0x22A0) == 1) || (FLD(g_hero_state, s32, 0x22A0) == 0x1D)) {
                if (FLD(g_hero_state, s32, 0x1B8) <= 4) {
                    ok = 0;
                }
            }
            if (ok && (FLD(g_hero_state, s16, 0x348) != 1)) {
                if (hero_try_start_move_from_buffer((FLD(g_hero_state, s16, 0x1EE) != 0) ? 1 : 7, 0) != 0) {
                    break;
                }
            }
        }
        if ((FLD(g_hero_state, s16, 0x348) == 1) && (g_hero_l20_lock_flag_b == 0) && (PadPressedWithin(0x40, 7, NULL) != 0)) {
            hero_l20_set_move_state_us2(0x6E, 1);
            break;
        }
        if ((FLD(g_pad_state, s32, 0x1A0) & 8) && (FLD(g_hero_state, s32, 0x340) != 0)) {
            if ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0x1A) || (FLD(g_hero_state, f32, 0xC38) >= 108.0f)) {
                hero_l20_set_move_state_us2(4, 1);
                break;
            }
        }
        if (FLD(g_hero_state, s32, 0x63C) != 0) {
            hero_l20_set_move_state_us2(0x27, 1);
            break;
        }
        if ((FLD(g_hero_state, u8, 0x1492) != 0) && (FLD(g_hero_state, f32, 0x320) > 0.087266475f)) {
            hero_l20_set_move_state_us2(0x2E, 1);
            break;
        }
        {
            s32 go = 1;
            s32 turned;
            if (((FLD(g_hero_state, s32, 0x22A0) == 1) || (FLD(g_hero_state, s32, 0x22A0) == 0x1D)) && (FLD(g_hero_state, s32, 0x1B8) < 0x18) && (FLD(g_hero_state, s16, 0x348) != 1)) {
                hero_resolve_stick_direction(0, 1.0f);
                if ((FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_l20_extra_state, f32, 0x158)) > 1.2217306f) && (fast_vec_dist(g_hero_state + 0x80, g_hero_l20_extra_state + 0x140) < 2.5f)) {
                    go = 0;
                }
            }
            turned = hero_is_turned_past_angle(0.17453295f);
            if (go == 0) {
                break;
            }
            if ((turned != 0) || (FLD(g_hero_state, f32, 0x24B8) > 0.22f)) {
                s32 side = FLD(g_hero_state, u8, 0x149D);
                hero_play_footstep_sound_dust(side, 0, 0, 0x1E);
                hero_play_footstep_sound_dust(side, 1, 0, 0x1E);
                hero_l20_set_move_state_us2(2, 1);
            }
        }
        break;
    }
    case 0x3C:
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l20_set_move_state_us2(1, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) != 0) || ((pad3C = FLD(g_pad_state, s32, 0x1A0)) & 0x40) || (pad3C & 8)) {
            hero_l20_set_move_state_us2(0x3D, 1);
            break;
        }
        hero_update_target_speed();
        if (FLD(g_hero_state, f32, 0x1B0) > 0.0f) {
            hero_l20_set_move_state_us2(0x3D, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_clear_target_flags();
            hero_l20_set_move_state_us2(0, 1);
        }
        break;
    case 0x3D:
        if (FLD(g_hero_state, s32, 0x1B8) < 9) {
            break;
        }
        hero_clear_target_flags();
        if (FLD(g_hero_state, s16, 0x34E) != 0) {
            hero_l20_set_move_state_us2(6, 1);
            break;
        }
        if (hero_try_start_move_from_buffer(7, 0) != 0) {
            break;
        }
        if (FLD(g_pad_state, s32, 0x1A0) & 8) {
            hero_l20_set_move_state_us2(4, 1);
            break;
        }
        hero_update_target_speed();
        if (FLD(g_hero_state, f32, 0x1B0) > 0.0f) {
            hero_l20_set_move_state_us2(2, 1);
            break;
        }
        hero_l20_set_move_state_us2(0, 1);
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
            hero_record_play_counters();
            return;
        }
        break;
    case 0x7C:
        if (FLD(g_hero_state, s32, 0x1B8) < 0xDD) {
            break;
        }
        hero_record_play_counters();
        return;
    case 0x32:
    case 0x34:
    {
        u32 st = FLD(g_hero_state, u32, 0x2294);
        if (st == 0x32) {
            f32 h;
            FLD(g_hero_state, f32, 0xC20) = FLD(g_hero_state, f32, 0x1B4) * 15.0f;
            if (FLD(g_hero_state, f32, 0xC20) < 0.25f) {
                FLD(g_hero_state, f32, 0xC20) = 0.25f;
            }
            if (FLD(g_hero_state, f32, 0xC20) > 0.75f) {
                FLD(g_hero_state, f32, 0xC20) = 0.75f;
            }
            if ((FLD(g_hero_state, u32, 0x2294) == st) && !(FLD(g_pad_state, s32, 0x1A0) & 0xC0) && ((h = FLD(g_hero_state, f32, 0xC38)) > 9.0f) && (h < 19.0f) && (FLD(g_hero_state, s32, 0x2298) != 1) && (FLD(g_hero_state, f32, 0x24B8) < 0.1f) && (FLD(g_hero_state, f32, 0x1B4) < 0.033333335f)) {
                hero_l20_set_move_state_us2(0x33, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_pad_state, s32, 0x1A0) & 0xA)) {
            if ((FLD(g_hero_state, u32, 0x2294) == 0x32) && (FLD(g_hero_state, s32, 0x1B8) >= 0x15)) {
                hero_l20_set_move_state_us2(0x34, 1);
                break;
            }
        } else if (FLD(g_hero_state, u32, 0x2294) == 0x34) {
            if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
                hero_l20_set_move_state_us2(0x32, 1);
                break;
            }
        }
        if (FLD(g_hero_state, u32, 0x2294) == 0x34) {
            s32 pad = FLD(g_pad_state, s32, 0x1A0);
            if (!(pad & 0xC0) && (FLD(g_hero_state, s32, 0x2298) != 1) && (FLD(g_hero_state, f32, 0x24B8) < 0.7f) && !(pad & 0xA)) {
                hero_l20_set_move_state_us2(0x33, 1);
            }
        }
        break;
    }
    case 0x33:
    {
        s32 pad;
        if ((FLD(g_hero_state, s32, 0xC28) & 2) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0x3C)) {
            set_hero_animation(0x3C, 0, 11.0f);
        }
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.2f) || ((pad = FLD(g_pad_state, s32, 0x1A0)) & 0xC0) || ((FLD(g_hero_state, s16, 0x24FC) == 0) && (pad & 0xA))) {
            if (FLD(g_hero_state, s16, 0x24FC) != 0) {
                hero_l20_set_move_state_us2(0x32, 1);
            } else if (FLD(g_pad_state, s32, 0x1A0) & 0xA) {
                hero_l20_set_move_state_us2(0x34, 1);
            } else {
                hero_l20_set_move_state_us2(0x32, 1);
            }
        }
        break;
    }
    case 0x36:
        if ((FLD(g_hero_state, s16, 0x1F8) == 0) && (PadPressedWithin(0x40, 8, NULL) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0xB)) {
            hero_l20_set_move_state_us2(0x12, 1);
            break;
        }
        FLD(g_hero_state, u8, 0x22B7) = 1;
        if ((FLD(g_hero_state, s16, 0x1FE) == 0) && (FLD(FLD(FLD(g_hero_state, u8 *, 0x2290), u8 *, 0x24), s32, 0x134) != 0)) {
            if ((PadPressedWithin(0x80, 7, NULL) != 0) || ((FLD(g_hero_state, s16, 0x24FC) == 0) && (PadPressedWithin(0xA, 7, NULL) != 0))) {
                if (FLD(g_hero_state, s16, 0x24FC) != 0) {
                    hero_l20_set_move_state_us2(0x32, 1);
                } else if (FLD(g_pad_state, s32, 0x1A0) & 0xA) {
                    hero_l20_set_move_state_us2(0x34, 1);
                } else {
                    hero_l20_set_move_state_us2(0x32, 1);
                }
                break;
            }
        }
        if ((FLD(g_hero_state, u8, 0x22B9) != 0) && (FLD(g_hero_state, f32, 0x24C4) < 0.4f) && (hero_l20_set_move_state_us2(0, 0) != 0)) {
            set_hero_animation(SelectHeroStateAnimation(0), 0, 18.0f);
        }
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.2f) && (FLD(g_hero_state, s32, 0x1B8) >= 0xB)) {
            hero_l20_set_move_state_us2(0x35, 1);
        }
        break;
    case 0x35:
        if ((FLD(g_hero_state, s16, 0x1F8) == 0) && (PadPressedWithin(0x40, 8, NULL) != 0)) {
            hero_l20_set_move_state_us2(0x12, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x1FE) == 0) && (FLD(FLD(FLD(g_hero_state, u8 *, 0x2290), u8 *, 0x24), s32, 0x134) != 0) && (PadPressedWithin(0x80, 7, NULL) != 0)) {
            if (FLD(g_hero_state, s16, 0x24FC) != 0) {
                hero_l20_set_move_state_us2(0x32, 1);
            } else if (FLD(g_pad_state, s32, 0x1A0) & 0xA) {
                hero_l20_set_move_state_us2(0x34, 1);
            } else {
                hero_l20_set_move_state_us2(0x32, 1);
            }
            break;
        }
        if ((FLD(g_hero_state, u8, 0x22B9) != 0) && (FLD(g_hero_state, f32, 0x24C4) < 0.7f)) {
            hero_l20_set_move_state_us2(0x70, 0);
            set_hero_animation(0x59, 0, 17.0f);
            FLD(g_hero_state, s32, 0xF8) = 0;
            FLD(g_hero_state, s32, 0x118) = 0;
        }
        if ((FLD(g_hero_state, f32, 0x24B8) < 0.1f) && (FLD(g_hero_state, f32, 0x1B4) == 0.0f) && (FLD(g_hero_state, s32, 0x798) == 0)) {
            hero_l20_set_move_state_us2(0x36, 1);
        }
        break;
    case 0x73:
        if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
            hero_l20_set_move_state_us2(0x67, 1);
            set_hero_animation(0x58, 0x28, 18.0f);
        } else if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l20_set_move_state_us2(0x33, 1);
        } else if (FLD(g_hero_state, s32, 0x1B8) >= 0x33) {
            hero_l20_set_move_state_us2(0x33, 0);
        }
        break;
    case 0x72:
        if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
            hero_l20_set_move_state_us2(0x67, 1);
            set_hero_animation(0x58, 0x25, 18.0f);
        } else if (FLD(g_hero_state, s32, 0x1B8) >= 0x33) {
            hero_l20_set_move_state_us2(0x36, 0);
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
                set_hero_animation(0xD, 0, 8.0f);
            } else {
                s32 a = SelectHeroStateAnimation(1);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != a) {
                    set_hero_animation(a, 0, 8.0f);
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
            late = FLD(g_hero_state, s32, 0x1B8) >= 0x1F;
        }
        if ((!(FLD(g_pad_state, s32, 0x1A0) & 4) && ok) || late) {
            if (FLD(g_hero_state, u8, 0x22B4) != 0) {
                hero_load_state_by_game_mode(0);
            } else if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                hero_l20_set_move_state_us2(4, 1);
            } else {
                hero_l20_set_move_state_us2(0, 0);
                anim = SelectHeroStateAnimation(1);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation(anim, 0, 8.0f);
                }
            }
        }
        break;
    }
    case 0x2F:
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230)) && (FLD(g_hero_state, s16, 0x1EC) == 0)) {
            if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x36) {
                hero_l20_set_move_state_us2(0, 0);
            } else {
                hero_l20_set_move_state_us2(0, 1);
            }
        }
        break;
    case 0x14:
    {
        u8 *rec;
        s32 frames;
        if (FLD(g_hero_state, u32, 0x2294) == 0x14) {
            s32 n = FloatToInt(hero_find_collision_time(60.0f, 0.036111113f, -1.0f));
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
        rec = (u8 *)&g_hero_l20_action_table[FLD(g_hero_state, s16, 0xBFC)];
        frames = (FloatToInt(FLD(g_hero_state, f32, 0xC38)) - FLD(rec, s32, 0xC)) * 2;
        if ((f32)FLD(rec, s32, 0x14) < FLD(g_hero_state, f32, 0xC38)) {
            if (FLD(g_hero_state, s32, 0xC2C) != 0) {
                break;
            }
            if (PadPressedWithin(0x40, frames, NULL) != 0) {
                if (!(FLD(g_pad_state, s32, 0x1A0) & 8)) {
                    hero_l20_set_move_state_us2(7, 1);
                    break;
                }
                if (hero_choose_jump_or_roll_move() != 0) {
                    break;
                }
            }
        }
        if ((FLD(g_hero_state, s32, 0xC2C) == 0) && ((f32)FLD(rec, s32, 0x18) < FLD(g_hero_state, f32, 0xC38))) {
            hero_l20_set_move_state_us2(0, 0);
        }
        break;
    }
    case 0x13:
    case 0x15:
    {
        u8 *rec = (u8 *)&g_hero_l20_action_table[FLD(g_hero_state, s16, 0xBFC)];
        s32 frames = (FloatToInt(FLD(g_hero_state, f32, 0xC38)) - FLD(rec, s32, 0xC)) * 2;
        u32 st = FLD(g_hero_state, u32, 0x2294);
        s32 lim;
        f32 h;
        if (st == 0x15) {
            frames = 8;
        }
        if ((f32)FLD(rec, s32, 0x14) < FLD(g_hero_state, f32, 0xC38)) {
            if (FLD(g_hero_state, s32, 0xC2C) != 0) {
                goto tail13;
            }
            if ((st != 0x15) || (FLD(g_hero_state, s16, 0x348) != 1)) {
                if (PadPressedWithin(0x40, frames, NULL) != 0) {
                    if (!(FLD(g_pad_state, s32, 0x1A0) & 8)) {
                        hero_l20_set_move_state_us2(7, 1);
                        break;
                    }
                    if (hero_choose_jump_or_roll_move() != 0) {
                        break;
                    }
                }
            }
        }
        if (FLD(g_hero_state, s32, 0xC2C) != 0) {
            goto tail13;
        }
        if ((FLD(g_hero_state, f32, 0xC38) > 34.0f) && (FLD(g_hero_state, f32, 0x24B8) > 0.9f)) {
            hero_l20_set_move_state_us2(2, 0);
            set_hero_animation(3, g_hero_l20_animation_ids[FLD(g_hero_state, s32, 0x2298)], 13.0f);
            break;
        }
        if (FLD(g_hero_state, s32, 0xC2C) != 0) {
            goto tail13;
        }
        lim = FLD(rec, s32, 0x18);
        h = FLD(g_hero_state, f32, 0xC38);
        if ((f32)lim < h) {
            if (FLD(g_hero_state, f32, 0x24B8) > 0.8f) {
                hero_l20_set_move_state_us2(2, 1);
                break;
            }
            if ((f32)(lim + 5) < h) {
                hero_l20_set_move_state_us2(0, 0);
                break;
            }
            if (FLD(g_hero_state, s32, 0xC28) & 2) {
                hero_l20_set_move_state_us2(0, 0);
            }
            break;
        }
    tail13:
        if (FLD(g_hero_state, u32, 0x2294) == 0x15) {
            if (FLD(g_hero_state, s32, 0x1248) != 0xA) {
                hero_l20_set_move_state_us2(0, 1);
                break;
            }
            if ((FLD(g_hero_state, s32, 0x1B8) >= 0x65) && (FLD(g_hero_state, s32, 0xC44) < 0x1A)) {
                hero_set_anim_mode(2);
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
            if (PadPressedWithin(0x40, 7, NULL) != 0) {
                if (!(FLD(g_pad_state, s32, 0x1A0) & 8)) {
                    hero_l20_set_move_state_us2(7, 1);
                    break;
                }
                if (hero_choose_jump_or_roll_move() != 0) {
                    break;
                }
            }
        }
        if ((FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0xC38) > 37.0f)) {
            hero_l20_set_move_state_us2(0, 0);
            set_hero_animation(SelectHeroStateAnimation(0), 0, 15.0f);
            break;
        }
    tail83:
        if ((FLD(g_hero_state, u32, 0x2294) == 0x15) && (FLD(g_hero_state, s32, 0x1B8) >= 0x65) && (FLD(g_hero_state, s32, 0xC44) < 0x1A)) {
            hero_set_anim_mode(2);
            FLD(g_hero_state, s32, 0xC44) = 0x1A;
        }
        break;
    case 0x77:
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l20_set_move_state_us2(0, 1);
        }
        break;
    case 0x2:
    case 0x2E:
    case 0x70:
    {
        s32 n;
        s32 turned;
        u32 st;
        if ((FLD(g_hero_state, u8, 0x40E) != 0) && ((FLD(sp74, f32, 0x44) > 0.9f) || (FLD(sp74, u8, 0x42) != 0xFF))) {
            FLD(g_hero_state, u8, 0x40E) = 0;
        }
        if ((FLD(g_hero_state, u8, 0x149A) != 0) && (FLD(g_hero_state, s16, 0x34C) == 0)) {
            hero_l20_set_move_state_us2(0x76, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 5) && ((FLD(g_hero_state, s32, 0x22A4) != 0x12) || (FLD(g_hero_state, u8, 0x22B9) == 0)) && (FLD(g_hero_state, f32, 0x31C) > 1.35f) && (hero_check_step_ahead() == 0)) {
            hero_l20_set_move_state_us2(6, 1);
            break;
        }
        n = 9;
        if (FLD(g_hero_state, s16, 0x1EE) != 0) {
            n = 1;
        }
        if ((PadPressedWithin(0x40, n, NULL) != 0) && ((FLD(g_hero_state, s16, 0x34E) < 5) || (FLD(g_hero_state, s16, 0x202) != 0))) {
            hero_resolve_stick_direction(0, 1.0f);
            if (hero_try_start_move_from_buffer(n, 1) != 0) {
                break;
            }
            if (FLD(g_hero_state, f32, 0x24B8) > 0.85f) {
                if (FLD(g_hero_state, s16, 0x1454) == 0) {
                    hero_l20_set_move_state_us2(9, 1);
                } else {
                    hero_l20_set_move_state_us2(7, 1);
                }
            } else {
                hero_l20_set_move_state_us2(7, 1);
            }
            break;
        }
        if (FLD(g_hero_state, s16, 0x34E) != 0) {
            break;
        }
        if (((FLD(g_hero_state, u8, 0x1492) == 0) || ((FLD(g_hero_state, f32, 0x174) < 0.033333335f) && (FLD(g_hero_state, f32, 0x320) < 0.087266475f))) && (FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l20_set_move_state_us2(1, 1);
            break;
        }
        if (FLD(g_pad_state, s32, 0x1A0) & 8) {
            hero_l20_set_move_state_us2(4, 1);
            break;
        }
        if ((FLD(g_hero_state, u8, 0x1492) != 0) && (FLD(g_hero_state, u32, 0x2294) == 0x2E)) {
            f32 speed = vec_length_xy(g_hero_state + 0x110);
            s32 anim;
            if ((FLD(g_hero_state, f32, 0x24B8) < 0.17f) && ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x37) || (((anim = FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43)) == SelectHeroStateAnimation(0)) && (FLD(g_hero_state, f32, 0x320) > 0.087266475f))) && (FLD(g_hero_state, s32, 0x1CC) >= 9) && (FLD(g_hero_state, s32, 0xC2C) == 0)) {
                set_hero_animation(0x66, 0, 14.0f);
            } else if ((FLD(g_hero_state, f32, 0x24B8) > 0.3f) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0x37) && (FLD(g_hero_state, s32, 0xC2C) == 0)) {
                set_hero_animation(0x37, 0, 14.0f);
            } else if ((FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x66) && (FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0x24B8) < 0.17f) && (FLD(g_hero_state, f32, 0x320) < 0.087266475f) && (speed < 0.028333336f)) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, 20.0f);
            }
        }
        st = FLD(g_hero_state, u32, 0x2294);
        if ((st == 2) || (st == 0x7B)) {
            if (FLD(g_hero_state, u8, 0x1492) != 0) {
                hero_l20_set_move_state_us2(0x2E, 1);
            }
        } else if (st == 0x2E) {
            if (FLD(g_hero_state, u8, 0x1492) == 0) {
                hero_l20_set_move_state_us2(2, 1);
            }
        }
        st = FLD(g_hero_state, u32, 0x2294);
        if (st == 2) {
            if (FLD(g_hero_state, u8, 0x22B9) != 0) {
                hero_l20_set_move_state_us2(0x70, 1);
            }
        } else if (st == 0x70) {
            if (FLD(g_hero_state, u8, 0x22B9) == 0) {
                hero_l20_set_move_state_us2(2, 1);
            }
        }
        if (FLD(g_hero_state, s32, 0x63C) != 0) {
            hero_l20_set_move_state_us2(0x27, 1);
            break;
        }
        turned = hero_is_turned_past_angle(0.03490659f);
        st = FLD(g_hero_state, u32, 0x2294);
        if (st == 2) {
            if (((FLD(g_hero_state, f32, 0x24B8) < 0.17f) || (FLD(g_hero_state, s16, 0x1E0) != 0)) && (turned == 0) && ((FLD(g_hero_state, s32, 0x410) == 0) || (math_fabs(FLD(g_hero_state, f32, 0x1A8)) < 0.017453294f))) {
                s32 anim;
                if (hero_try_start_grab() != 0) {
                    break;
                }
                if (hero_l20_set_move_state_us2(0, 0) == 0) {
                    break;
                }
                vec_clamp_length(g_hero_state + 0x160, 0.025000002f);
                if (FLD(g_hero_state, f32, 0x1B4) > 0.025000002f) {
                    FLD(g_hero_state, f32, 0x1B4) = 0.025000002f;
                }
                anim = SelectHeroStateAnimation(1);
                if (anim == 0x51) {
                    set_hero_animation(0x51, 0, 15.0f);
                } else {
                    set_hero_animation(anim, 0, -1.0f);
                }
            } else {
                hero_update_anim_scale();
            }
        } else if (st == 0x2E) {
            if ((FLD(g_pad_state, s32, 0x1D4) != 0) && (vec_length_xy(g_hero_state + 0xF0) < 0.0008333334f) && (FLD(g_hero_state, f32, 0x320) < 0.087266475f) && (hero_l20_set_move_state_us2(0, 0) != 0)) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, 17.0f);
            }
            if (FLD(sp74, u8, 0x43) == 0x37) {
                FLD(g_hero_state, f32, 0xC20) = (1.0f - FLD(g_hero_state, f32, 0x400)) * 2.0f;
                if (FLD(g_hero_state, f32, 0xC20) > 1.7f) {
                    FLD(g_hero_state, f32, 0xC20) = 1.7f;
                }
                if (FLD(g_hero_state, f32, 0xC20) < 0.75f) {
                    FLD(g_hero_state, f32, 0xC20) = 0.75f;
                }
            } else if (FLD(sp74, u8, 0x43) == 0x66) {
                FLD(g_hero_state, f32, 0xC20) = FLD(g_hero_state, f32, 0x170) * 10.0f;
                if (FLD(g_hero_state, f32, 0xC20) > 1.1f) {
                    FLD(g_hero_state, f32, 0xC20) = 1.1f;
                }
                if (FLD(g_hero_state, f32, 0xC20) < 0.3f) {
                    FLD(g_hero_state, f32, 0xC20) = 0.3f;
                }
            }
        } else if (st == 0x70) {
            if ((FLD(g_pad_state, s32, 0x1D4) != 0) && (vec_length_xy(g_hero_state + 0xF0) < 0.05333334f) && (hero_l20_set_move_state_us2(0, 0) != 0)) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, 17.0f);
            }
            FLD(g_hero_state, f32, 0xC20) = FLD(g_hero_state, f32, 0x170) * 35.0f;
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
            if (FLD(g_hero_state, s32, 0x1B8) >= 0x3D) {
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
            FLD(g_hero_state, s16, 0x1E0) = 0x1E;
            hero_l20_set_move_state_us2(3, 0);
            set_hero_animation(6, 4, 11.0f);
        } else {
            if (FLD(g_hero_state, u8, 0x287) != 0) {
                f32 a = FastVecLength(g_hero_state + 0x110);
                if (a < FastVecLength(g_hero_state + 0xF0) * 0.75f) {
                    hero_l20_set_move_state_us2(0x77, 1);
                    break;
                }
                if (hero_test_reach_blend(NULL, 1.0f, 1.25f) != 0) {
                    hero_l20_set_move_state_us2(0x77, 1);
                    break;
                }
            }
            *(s128 *)v30 = 0;
            v30[0] = -0.083333336f;
            moby_transform_joint_to_world(FLD(g_hero_state, s8 *, 0x2290), 0x16, (s8 *)v10);
            moby_transform_joint_to_world(FLD(g_hero_state, s8 *, 0x2290), 0x17, (s8 *)v20);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), v10, v30, (s32 *)g_hero_l20_particle_params_a, 1);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), v10, v30, (s32 *)g_hero_l20_particle_params_b, 1);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), v20, v30, (s32 *)g_hero_l20_particle_params_a, 1);
            part_spawn_object_relative_particle(FLD(g_hero_state, s8 *, 0x2290), v20, v30, (s32 *)g_hero_l20_particle_params_b, 1);
        }
        break;
    }
    case 0x62:
        if (vec_distance_xy(g_hero_state + 0x80, g_hero_state + 0x18A0) < 0.2f) {
            if ((FLD(g_hero_state, f32, 0x170) < 0.045f) && (FastDiffRots(FLD(g_hero_state, f32, 0x98), FLD(g_hero_state, f32, 0x18AC)) < 0.03490659f)) {
                hero_l20_set_move_state_us2(0x64, 1);
                break;
            }
            if ((FLD(g_hero_state, u8, 0x22B4) != 0) && (FLD(g_hero_state, f32, 0x170) >= 0.045f)) {
                hero_l20_set_move_state_us2(0x63, 1);
            }
        } else {
            hero_update_anim_scale();
        }
        break;
    case 0x63:
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l20_set_move_state_us2(0x62, 1);
        }
        break;
    case 0x64:
        if ((FLD(g_hero_state, s32, 0xC28) & 2) || (FLD(g_hero_state, s32, 0x18B0) != 0)) {
            hero_l20_set_move_state_us2(0, 1);
        }
        if (vec_distance_xy(g_hero_state + 0x80, g_hero_state + 0x18A0) > 0.2f) {
            hero_l20_set_move_state_us2(0x62, 1);
        }
        break;
                case 0x65:                          /* switch 2 */
                    temp_a0_11 = FLD(g_hero_state, s32, 0x18C0);
                    if ((temp_a0_11 < 3) && (((temp_a0_11 * 7) + 0xA) < FLD(g_hero_state, s32, 0x1B8)) && (PadPressedWithin(0x40U, 7, &sp44) != 0)) {
                        hero_l20_set_move_state_us2(0x66, 1);
                    }
                    if (FLD(g_hero_state, f32, 0x88) < (FLD(g_hero_state, f32, 0x334) - 1.2f)) {
                        hero_record_play_counters();
                        return;
                    }
                    if (FLD(g_hero_state, s32, 0x1B8) < 0xAB) {
                        break;
                    }
                    hero_record_play_counters();
                    return;
                case 0x78:                          /* switch 2 */
                    if (FLD(g_hero_state, f32, 0x88) < (FLD(g_hero_state, f32, 0x334) - 1.2f)) {
                        hero_record_play_counters();
                        return;
                    }
                    if (FLD(g_hero_state, s32, 0x1B8) < 0x97) {
                        break;
                    }
                    hero_record_play_counters();
                    return;
                case 0x79:                          /* switch 2 */
                    if (FLD(g_hero_state, f32, 0x88) < (FLD(g_hero_state, f32, 0x334) - 1.2f)) {
                        hero_record_play_counters();
                        return;
                    }
                    if (FLD(g_hero_state, s32, 0x1B8) < 0x65) {
                        break;
                    }
                    hero_record_play_counters();
                    return;
                case 0x7A:                          /* switch 2 */
                    if (FLD(g_hero_state, f32, 0x88) < (FLD(g_hero_state, f32, 0x334) - 0.8f)) {
                        hero_record_play_counters();
                        return;
                    }
                    if (FLD(g_hero_state, s32, 0x1B8) < 0x97) {
                        break;
                    }
                    hero_record_play_counters();
                    return;
    case 0x6D:
        if ((f32)g_hero_l20_action_table[FLD(g_hero_state, s16, 0xBFC)].w[6] < FLD(g_hero_state, f32, 0xC38)) {
            hero_l20_set_move_state_us2(0, 1);
        }
        break;
    case 0x30:
        if (((FLD(g_hero_state, u8, 0x1493) == 0) && (FLD(g_hero_state, s16, 0x200) == 0)) || (FLD(g_hero_state, f32, 0x31C) > 1.0f)) {
            s32 slot = FLD(g_hero_state, s32, 0x2434);
            if (slot != -1) {
                u8 *ent = g_sound_state + slot * 0x70;
                if ((FLD(ent, s32, 0x88) == FLD(g_hero_state, s32, 0x2290)) && (FLD(ent, u8, 0x74) != 0)) {
                    snd_stop_voice(slot);
                }
            }
            FLD(g_hero_state, s32, 0x2434) = -1;
            if (hero_l20_set_move_state_us2(0, 0) != 0) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, 17.0f);
                FLD(g_hero_state, s128, 0x160) = FLD(g_hero_state, s128, 0x150);
            }
        }
        break;
    case 0x3:
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l20_set_move_state_us2(1, 1);
            break;
        }
        if (FLD(g_hero_state, s16, 0x1E0) == 0) {
            if (FLD(g_pad_state, s32, 0x1A4) & 0x40) {
                hero_l20_set_move_state_us2(7, 1);
                break;
            }
            if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                hero_l20_set_move_state_us2(4, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 9) && (FLD(g_hero_state, f32, 0x31C) > 0.3f)) {
            hero_l20_set_move_state_us2(6, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l20_set_move_state_us2(0, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x63C) != 0) {
            hero_l20_set_move_state_us2(0x27, 1);
            break;
        }
        if (!(FLD(g_hero_state, f32, 0x24B8) > 0.2f) || (FLD(g_hero_state, s16, 0x1E0) != 0)) {
            break;
        }
        if (SelectHeroStateAnimation(0) != 0x51) {
            if (FLD(g_hero_state, f32, 0x1B4) == 0.0f) {
                hero_l20_set_move_state_us2(0, 0);
                break;
            }
        } else if ((FLD(g_hero_state, f32, 0xC38) > 10.0f) && (hero_l20_set_move_state_us2(0, 0) != 0)) {
            set_hero_animation(SelectHeroStateAnimation(0), 0, 17.0f);
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            hero_l20_set_move_state_us2(2, 1);
        }
        break;
    case 0x4:
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l20_set_move_state_us2(1, 1);
            break;
        }
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0xC) && !(FLD(g_pad_state, s32, 0x1A0) & 8)) {
            hero_l20_set_move_state_us2(0, 0);
            set_hero_animation(SelectHeroStateAnimation(0), 0, -2.0f);
            break;
        }
        if ((FLD(g_hero_state, u8, 0x149A) != 0) && (FLD(g_hero_state, s16, 0x34C) == 0)) {
            hero_l20_set_move_state_us2(0x76, 1);
            break;
        }
        if (hero_choose_jump_or_roll_move() != 0) {
            break;
        }
        if ((PadPressedWithin(0x80, 0xF, NULL) != 0) && (FLD(g_hero_state, u8, 0x123A) == 0) && (FLD(g_hero_state, s32, 0x1248) == 0xA)) {
            hero_l20_set_move_state_us2(0x15, 1);
        }
        if (FLD(g_hero_state, s16, 0x34E) >= 9) {
            if ((FLD(g_hero_state, s32, 0x22A0) != 8) || (FLD(g_hero_state, s32, 0x1B8) >= 0xF)) {
                hero_l20_set_move_state_us2(6, 1);
            }
        }
        break;
    case 0x8A:
        if (FLD(g_hero_state, s32, 0x1248) != 0xD) {
            hero_l20_set_move_state_us2(0, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0xB1C) != 0) {
            u8 *obj = FLD(g_hero_state, u8 *, 0xB10);
            if (obj != NULL) {
                moby_set_flag_bit(obj, 1);
            }
            hero_l20_set_move_state_us2(0x8B, 1);
        }
        break;
    case 0x8B:
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x5B) {
            hero_l20_set_move_state_us2(0, 1);
        }
        break;
    case 0x23:
        if (FLD(g_hero_state, s32, 0x1248) != 0xD) {
            hero_l20_set_move_state_us2(0, 1);
        }
        break;
    case 0x24:
    {
        s32 go;
        AdjustHeroAnimationSpeedForTargetFrame(10.0f, FLD(g_hero_state, f32, 0xAAC), 0.5f, -1.0f);
        if ((FLD(g_hero_state, f32, 0xAAC) < 22.0f) && (FLD(g_hero_state, f32, 0xAAC) < 30.0f)) {
            set_hero_animation(0xA, 0, 16.0f);
        }
        go = 0;
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230))) {
            if (FLD(g_hero_state, f32, 0xAAC) > 25.0f) {
                FLD(g_hero_state, s32, 0xAC8) = 1;
            }
            go = 1;
        }
        if ((FLD(g_hero_state, s32, 0x2298) == 1) && (FLD(g_hero_state, f32, 0xAA0) < 0.06666667f)) {
            go = 1;
        }
        if (go != 0) {
            FLD(g_hero_state, f32, 0x1B4) = FLD(g_hero_state, f32, 0xAA0);
            if (FLD(g_hero_state, f32, 0x1B4) > 0.116666675f) {
                FLD(g_hero_state, f32, 0x1B4) = 0.116666675f;
            }
            if (FLD(g_hero_state, f32, 0x31C) < 0.3f) {
                hero_l20_set_move_state_us2(0, 0);
                set_hero_animation(SelectHeroStateAnimation(0), 0, 30.0f);
                break;
            }
            if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0xA) {
                hero_l20_set_move_state_us2(6, 0);
            } else {
                hero_l20_set_move_state_us2(6, 0);
                set_hero_animation(0xA, 0, 17.0f);
            }
            FLD(g_hero_state, f32, 0xA84) = 0.011666667f;
            FLD(g_hero_state, f32, 0xA80) = 0.008055556f;
            FLD(g_hero_state, s32, 0x24A0) = 0;
        }
        break;
    }
    case 0x25:
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230))) {
            FLD(g_hero_state, f32, 0x1B4) = FLD(g_hero_state, f32, 0xAA0);
            if (FLD(g_hero_state, f32, 0x1B4) > 0.116666675f) {
                FLD(g_hero_state, f32, 0x1B4) = 0.116666675f;
            }
            if (FLD(g_hero_state, f32, 0x31C) < 0.4f) {
                hero_l20_set_move_state_us2(0, 1);
            } else {
                hero_l20_set_move_state_us2(6, 1);
                FLD(g_hero_state, s32, 0x24A0) = 0;
            }
        }
        break;
    case 0x2B:
        if (!(FLD(g_pad_state, s32, 0x1A0) & FLD(g_hero_state, s32, 0x1230))) {
            s32 t = FLD(g_hero_state, s32, 0x1B8);
            if (t >= 0xB) {
                if (t < 0x28) {
                    FLD(g_hero_state, s32, 0xAC8) = 1;
                }
                hero_l20_set_move_state_us2(0x2C, 1);
                FLD(g_hero_state, f32, 0xA84) = 0.0019444445f;
                FLD(g_hero_state, f32, 0xA80) = 0.0075000003f;
            }
        }
        break;
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x3E:
    {
        u32 st;
        if (FLD(g_hero_state, u32, 0x2294) == 0x3E) {
            FLD(g_hero_state, s16, 0x68E) = 0;
        }
        if (FLD(g_hero_state, u32, 0x2294) == 0x2A) {
            FLD(g_hero_state, s8, 0x1239) = 2;
        }
        if (FLD(g_hero_state, u32, 0x2294) != 0x3E) {
            s32 hit = 0;
            if (FLD(g_hero_state, u8, 0x287) != 0) {
                f32 half = 0.5f;
                f32 up = 0.02f;
                if ((u32)(FLD(g_hero_state, u32, 0x2294) - 0x28) < 2) {
                    up = 0.45f;
                }
                if (g_current_map_index == 0x14) {
                    up = 0.3f;
                }
                qzero_nc(v10);
                v10[2] = FLD(g_hero_state, f32, 0x64C);
                v10[1] = -FLD(g_hero_state, f32, 0x650);
                euler_rotation_basis(v40, v10);
                *(s128 *)v20 = 0;
                v20[0] = 0.25f;
                v20[2] = half + up;
                ((void (*)(void *, void *, void *))matrix_mul_vec3)(v20, v20, v40);
                ((void (*)(void *, void *, void *))FastVecAdd)(v20, v20, g_hero_state + 0x80);
                hit = coll_test_point(v20, 2, NULL, half) != 0;
            }
            if ((hit != 0) || (FLD(g_hero_state, s16, 0x68E) != 0)) {
                s32 clear = 1;
                s32 level;
                if (FLD(g_hero_state, u8, 0x287) != 0) {
                    qcopy(v10, g_hero_state + 0x5D0);
                    if (g_current_map_index == 0x12) {
                        v10[2] += 1.8f;
                    } else {
                        v10[2] += 1.5f;
                    }
                    v20[0] = math_fast_sin_or_cos_a(FLD(g_hero_state, f32, 0x64C)) * 5.0f;
                    v20[1] = math_fast_sin_or_cos_b(FLD(g_hero_state, f32, 0x64C)) * 5.0f;
                    v20[2] = 0.0f;
                    FastVecAdd(v20, v20, v10);
                    if (CollLine(v10, v20, 2, NULL, 0) != 0) {
                        clear = 0;
                    }
                }
                level = g_current_map_index;
                FLD(g_hero_state, s16, 0x68E) = 0;
                if (((level == 0xD) || (level == 0x12)) && (clear == 0)) {
                    vec_scale_to_length(g_hero_state + 0x120, g_hero_state + 0x10, 0.21666668f);
                    FLD(g_hero_state, f32, 0x128) = 0.16666667f;
                    hero_l20_set_move_state_us2(0x16, 1);
                    FLD(g_hero_state, s16, 0x1F4) = 0x46;
                    FLD(g_hero_state, s16, 0x1D0) = 0x46;
                } else {
                    hero_l20_set_move_state_us2(0x3E, 1);
                }
                break;
            }
        }
        st = FLD(g_hero_state, u32, 0x2294);
        if (st == 0x27) {
            s32 a;
            s32 b;
            if (PadPressedWithin(0x40, 7, NULL) != 0) {
                if (FLD(g_hero_state, s32, 0x688) != 0) {
                    FLD(g_hero_state, s32, 0x690) = 1;
                } else {
                    hero_l20_set_move_state_us2(0x28, 1);
                }
                break;
            }
            a = FLD(g_hero_state, s32, 0x640);
            if ((a >= 6) || ((b = FLD(g_hero_state, s32, 0x6C8)) >= 6)) {
                if (FLD(g_hero_state, f32, 0x31C) > 8.0f) {
                    FLD(g_hero_state, s16, 0x1E0) = 0x46;
                }
                FLD(g_hero_state, s16, 0x1D0) = 0x46;
                if ((g_current_map_index == 0xD) && (FLD(g_hero_state, f32, 0x31C) > 4.0f)) {
                    hero_l20_set_move_state_us2(0x74, 1);
                } else {
                    hero_l20_set_move_state_us2(6, 1);
                }
                FLD(g_hero_state, s16, 0x1F4) = 8;
                FLD(g_hero_state, s16, 0x1D0) = 0x46;
                break;
            }
            if ((a == 0) && (b == 0) && (PadPressedWithin(0x80, 0xA, NULL) != 0)) {
                hero_l20_set_move_state_us2(0x2A, 1);
                break;
            }
            if (FLD(g_hero_state, s32, 0x67C) == -1) {
                s32 anim = FLD(g_hero_state, s32, 0x65C) + 0x31;
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation(anim, 0, 12.0f);
                }
            } else {
                s32 anim = FLD(g_hero_state, s32, 0x67C) + 0x47;
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation(anim, 0, 12.0f);
                }
            }
            if ((FLD(g_hero_state, s16, 0x68C) != 0) && (FLD(g_hero_state, s32, 0x690) != 0)) {
                f32 h;
                f32 t;
                hero_l20_set_move_state_us2(0x28, 1);
                FLD(g_hero_state, s32, 0x694) = 1;
                h = weapon_compute_shot_launch_speed((f32 *)(g_hero_state + 0x80), (f32 *)(g_hero_state + 0x620), NULL, FLD(g_hero_state, f32, 0x174), -FLD(g_hero_state, f32, 0x520));
                *(s128 *)v20 = 0;
                v20[2] = h;
                *(s128 *)v10 = 0;
                t = math_compute_falling_step_offset(v10, v20, NULL, FLD(g_hero_state, f32, 0x520));
                FLD(g_hero_state, f32, 0x508) = t;
                FLD(g_hero_state, f32, 0x520) = FLD(g_hero_state, f32, 0x698);
                FLD(g_hero_state, f32, 0x4A8) = t;
                FLD(g_hero_state, f32, 0x50C) = t + 0.05f;
            }
            FLD(g_hero_state, s32, 0x688) = 0;
            FLD(g_hero_state, s16, 0x68C) = 0;
        } else if (st == 0x2A) {
            s32 top;
            if ((PadPressedWithin(0x40, 5, NULL) != 0) && ((f32)g_hero_l20_action_table[FLD(g_hero_state, s16, 0xBFC)].w[5] <= FLD(g_hero_state, f32, 0xC38))) {
                hero_l20_set_move_state_us2(0x28, 1);
                break;
            }
            top = 0xE;
            if (FLD(g_hero_state, s16, 0xBFC) == 0) {
                top = 0x17;
            }
            if ((FLD(g_hero_state, s32, 0x640) == 0) && (FLD(g_hero_state, s32, 0x6C8) == 0) && (PadPressedWithin(0x80, 0xA, NULL) != 0)) {
                if ((f32)top < FLD(g_hero_state, f32, 0xC38)) {
                    hero_l20_set_move_state_us2(0x2A, 1);
                }
                break;
            }
            if ((f32)g_hero_l20_action_table[FLD(g_hero_state, s16, 0xBFC)].w[6] < FLD(g_hero_state, f32, 0xC38)) {
                hero_l20_set_move_state_us2(0x27, 1);
                break;
            }
            if ((FLD(g_hero_state, s32, 0x640) >= 6) || (FLD(g_hero_state, s32, 0x6C8) >= 6)) {
                if ((g_current_map_index == 0xD) && (FLD(g_hero_state, f32, 0x31C) > 4.0f)) {
                    hero_l20_set_move_state_us2(0x74, 1);
                } else {
                    hero_l20_set_move_state_us2(6, 1);
                }
                FLD(g_hero_state, s16, 0x1F4) = 8;
                FLD(g_hero_state, s16, 0x1D0) = 0x46;
            }
        } else if ((u32)(st - 0x28) < 2) {
            s32 lo;
            s32 now;
            if (((FLD(g_hero_state, s32, 0x640) >= 6) || (FLD(g_hero_state, s32, 0x694) != 0)) && (FLD(g_hero_state, s32, 0x63C) != 0) && ((FLD(g_hero_state, f32, 0x88) - FLD(g_hero_state, f32, 0x5D8)) < 0.35f)) {
                hero_l20_set_move_state_us2(0x27, 1);
                break;
            }
            if ((FLD(g_hero_state, s32, 0x640) >= 6) && (g_current_map_index == 0x14)) {
                hero_l20_set_move_state_us2(6, 1);
                break;
            }
            if ((FLD(g_hero_state, u32, 0x2294) == 0x28) && (FLD(g_hero_state, s32, 0x1B8) < 0xA) && (FLD(g_hero_state, u8, 0x49E) == 0) && (FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (FLD(g_hero_state, s32, 0x660) == 0)) {
                hero_resolve_stick_direction(0, 1.0f);
                if (FastDiffRots(FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x64C)), 1.5707965f) < 1.2217306f) {
                    f32 ang;
                    f32 d;
                    f32 lim;
                    ang = FastAddRotations(FLD(g_hero_state, f32, 0x64C), 1.5707965f);
                    if (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), ang) > 1.5707965f) {
                        ang = FastAddRotations(FLD(g_hero_state, f32, 0x64C), -1.5707965f);
                    }
                    lim = 4.5f;
                    for (d = 2.0f; d <= lim; d += 0.75f) {
                        char *pos = g_hero_state + 0x80;
                        *(s128 *)v10 = *(s128 *)pos;
                        sp48 = FLD(g_hero_state, s32, 0x634);
                        sp4C = FLD(g_hero_state, f32, 0x638);
                        if (Spline_AdvanceByDistance(FLD(g_hero_state, void *, 0x630), v10, &sp48, &sp4C, FLD(g_hero_state, s32, 0x654), 0.0f) != 0) {
                            FastVecScale(v20, g_hero_state + 0x110, 48.0f);
                            FastVecAdd(v10, pos, v20);
                        }
                        v10[0] += math_fast_sin_or_cos_a(ang) * d;
                        v10[1] += math_fast_sin_or_cos_b(ang) * d;
                        if (nearest_rail_point((s8 *)v10, &sp50, (s128 *)v20, &sp54, &sp58, &sp5C, FLD(g_hero_state, void *, 0x630), 0, 1) != 0) {
                            FLD(g_hero_state, void *, 0x664) = FLD(g_hero_state, void *, 0x630);
                            FLD(g_hero_state, s32, 0x668) = FLD(g_hero_state, s32, 0x634);
                            FLD(g_hero_state, f32, 0x66C) = FLD(g_hero_state, f32, 0x638);
                            FLD(g_hero_state, s32, 0x670) = FLD(g_hero_state, s32, 0x654);
                            *(s128 *)(g_hero_state + 0x610) = *(s128 *)(g_hero_state + 0x5D0);
                            FLD(g_hero_state, void *, 0x630) = sp50;
                            FLD(g_hero_state, s32, 0x654) = sp5C;
                            find_nearest_path_point(sp50, pos, g_hero_state + 0x5D0, (s32 *)(g_hero_state + 0x634), (f32 *)(g_hero_state + 0x638), sp5C, 999.0f, 2.0f, 0.0f);
                            FLD(g_hero_state, s32, 0x660) = 1;
                            FLD(g_hero_state, s32, 0x678) = 0;
                            hero_l20_set_move_state_us2(0x29, 1);
                            break;
                        }
                    }
                }
            }
            if ((FLD(g_hero_state, s16, 0x4AC) < FLD(g_hero_state, s32, 0x1B8)) && (cam_get_view_space_height((s8 *)(g_hero_state + 0xF0)) < 0.001f)) {
                FLD(g_hero_state, s8, 0x49E) = 1;
            }
            lo = FLD(g_hero_state, s16, 0x4AC);
            now = FLD(g_hero_state, s32, 0x1B8);
            if ((now >= lo + 1) && (now < lo + 9) && (FLD(g_hero_state, u8, 0x49E) == 0) && (FLD(g_hero_state, s32, 0xC2C) == 0)) {
                EvaluateQuantizedHeight((f32 *)(g_hero_state + 0x80), (f32 *)(g_hero_state + 0xF0), &sp60, FLD(g_hero_state, f32, 0x520));
                AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4C8), (f32)sp60, 0.5f, 0.25f);
                if (FLD(g_hero_state, s32, 0x660) != 0) {
                    if (FLD(g_hero_state, f32, 0xC20) > 2.0f) {
                        FLD(g_hero_state, f32, 0xC20) = 2.0f;
                    }
                    if (FLD(g_hero_state, f32, 0xC20) < 0.5f) {
                        FLD(g_hero_state, f32, 0xC20) = 0.5f;
                    }
                }
            } else if ((FLD(g_hero_state, u8, 0x49E) != 0) && (FLD(g_hero_state, u8, 0x49C) == 0)) {
                FLD(g_hero_state, s16, 0x4AE) = 0x1E;
                if (FLD(g_hero_state, s32, 0x640) == 0) {
                    FLD(g_hero_state, s16, 0x4AE) = FloatToInt(hero_find_collision_time(60.0f, FLD(g_hero_state, f32, 0x520), FLD(g_hero_state, f32, 0x5D8)));
                }
                if (FLD(g_hero_state, s16, 0x4AE) != 0) {
                    AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4CC), (f32)FLD(g_hero_state, s16, 0x4AE), 0.5f, 0.25f);
                }
                if (FLD(g_hero_state, s32, 0x660) != 0) {
                    if (FLD(g_hero_state, f32, 0xC20) > 2.0f) {
                        FLD(g_hero_state, f32, 0xC20) = 2.0f;
                    }
                    if (FLD(g_hero_state, f32, 0xC20) < 0.5f) {
                        FLD(g_hero_state, f32, 0xC20) = 0.5f;
                    }
                }
                if ((FLD(g_hero_state, s32, 0x640) == 0) && (FLD(g_hero_state, s32, 0x6C8) == 0) && (FLD(g_hero_state, f32, 0x31C) < 0.5f)) {
                    f32 y = FLD(g_hero_state, f32, 0x88);
                    f32 floor = FLD(g_hero_state, f32, 0x5D8);
                    if (y + FLD(g_hero_state, f32, 0xF8) < floor) {
                        FLD(g_hero_state, u8, 0x49C) = 1;
                        FLD(g_hero_state, f32, 0xF8) = floor - y;
                        FLD(g_hero_state, f32, 0xC20) = 1.0f;
                    }
                }
                if ((FLD(g_hero_state, f32, 0x88) - FLD(g_hero_state, f32, 0x5D8)) < -2.5f) {
                    hero_l20_set_move_state_us2(6, 1);
                    FLD(g_hero_state, s16, 0x1E0) = 0x46;
                    FLD(g_hero_state, s16, 0x1F4) = 8;
                    FLD(g_hero_state, s16, 0x1D0) = 0x46;
                    break;
                }
            }
            if (FLD(g_hero_state, s32, 0x6EC) != 0) {
                hero_l20_set_move_state_us2(0x71, 1);
                break;
            }
            {
                if (FLD(g_hero_state, u8, 0x49C) != 0) {
                    if (++FLD(g_hero_state, u8, 0x49C) >= 3) {
                        FLD(g_hero_state, s32, 0x2294) = 0x27;
                        set_hero_animation(FLD(g_hero_state, s32, 0x65C) + 0x31, 0, 7.0f);
                        break;
                    }
                }
            }
            if ((FLD(g_hero_state, s32, 0x640) != 0) && (FLD(g_hero_state, s16, 0x34E) == 0) && (hero_l20_set_move_state_us2(0, 0) != 0)) {
                set_hero_animation(0xC, 4, 6.0f);
            }
        } else if (st == 0x3E) {
            if (FLD(g_hero_state, f32, 0xF8) > 0.0f) {
                EvaluateQuantizedHeight((f32 *)(g_hero_state + 0x80), (f32 *)(g_hero_state + 0xF0), &sp64, 0.006388889f);
                AdjustHeroAnimationSpeedForTargetFrame(9.0f, (f32)sp64, 0.5f, -1.0f);
            }
            if ((FLD(g_hero_state, s32, 0x640) != 0) && (FLD(g_hero_state, s32, 0x340) != 0)) {
                if (hero_l20_set_move_state_us2(0, 0) != 0) {
                    set_hero_animation(0xC, 4, 6.0f);
                }
                break;
            }
            if (FLD(g_hero_state, s32, 0xC28) & 2) {
                hero_l20_set_move_state_us2(0x27, 1);
                break;
            }
            if ((FLD(g_hero_state, s32, 0x1B8) >= 0x10) && (FLD(g_hero_state, f32, 0xF8) < 0.0f) && (math_fabs(FLD(g_hero_state, f32, 0x88) - FLD(g_hero_state, f32, 0x5D8)) < 0.3f)) {
                hero_l20_set_move_state_us2(0x27, 1);
            }
        }
        break;
    }
    case 0x17:
        if (FLD(g_hero_state, f32, 0xC38) > 13.5f) {
            hero_l20_set_move_state_us2(0x18, 0);
        }
        break;
    case 0x18:
        if ((FLD(g_hero_state, s32, 0xC28) & 2) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x20)) {
            set_hero_animation(0x21, 0, 6.0f);
        }
        hero_resolve_stick_direction(0, 1.0f);
        if (hero_find_ledge_grab((s8 *)(g_hero_state + 0x80), (s8 *)(g_hero_state + 0x90), NULL) == 0) {
            hero_l20_set_move_state_us2(6, 1);
            FLD(g_hero_state, s16, 0x1D0) = 0xA;
            break;
        }
        if (((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 9, NULL) != 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) > 2.3561947f)) || (FLD(g_pad_state, s32, 0x1A4) & 8)) {
            hero_l20_set_move_state_us2(6, 1);
            FLD(g_hero_state, s8, 0x22BF) = 1;
            FLD(g_hero_state, s16, 0x1D0) = 0xA;
            break;
        }
        if (PadPressedWithin(0x40, 0x11, NULL) != 0) {
            hero_l20_set_move_state_us2(0x1B, 1);
            break;
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) < 0.78539824f) {
                qcopy(v10, g_hero_state + 0x80);
                v10[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) * 0.3f;
                v10[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) * 0.3f;
                if (hero_find_ledge_grab((s8 *)v10, (s8 *)(g_hero_state + 0x90), NULL) != 0) {
                    hero_l20_set_move_state_us2(0x19, 1);
                }
                break;
            }
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) < 0.78539824f) {
                qcopy(v10, g_hero_state + 0x80);
                v10[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) * 0.3f;
                v10[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) * 0.3f;
                if (hero_find_ledge_grab((s8 *)v10, (s8 *)(g_hero_state + 0x90), NULL) != 0) {
                    hero_l20_set_move_state_us2(0x1A, 1);
                }
            }
        }
        break;
    case 0x19:
    case 0x1A:
    {
        f32 side;
        *(s128 *)v10 = FLD(g_hero_state + 0x80, s128, 0);
        side = 1.5707965f;
        if (FLD(g_hero_state, u32, 0x2294) == 0x1A) {
            side = -1.5707965f;
        }
        v10[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) * 0.3f;
        v10[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) * 0.3f;
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, f32, 0x24B8) < 0.5f) || (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) > 0.78539824f) || (hero_find_ledge_grab((s8 *)v10, (s8 *)(g_hero_state + 0x90), NULL) == 0)) {
            if (FLD(g_hero_state, s32, 0xC28) & 2) {
                hero_l20_set_move_state_us2(0x18, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 9, NULL) != 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) > 2.3561947f)) {
            hero_l20_set_move_state_us2(6, 1);
            FLD(g_hero_state, s8, 0x22BF) = 1;
            FLD(g_hero_state, s16, 0x1D0) = 0x28;
            break;
        }
        if (PadPressedWithin(0x40, 9, NULL) != 0) {
            hero_l20_set_move_state_us2(0x1B, 1);
        }
        break;
    }
    case 0x76:
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x12D) {
            hero_record_play_counters();
        }
        if (FLD(g_hero_state, u8, 0x149A) == 0) {
            if (FLD(g_hero_state, s16, 0x34E) != 0) {
                hero_l20_set_move_state_us2(6, 1);
            } else {
                hero_l20_set_move_state_us2(0, 1);
            }
        }
        break;
    case 0x6:
    case 0x2C:
        if ((FLD(g_hero_state, s32, 0x2298) == 0) && ((FLD(g_hero_state, s32, 0x1B8) >= 0x12) || (FLD(g_hero_state, f32, 0x31C) > 1.75f))) {
            set_hero_animation(0xB, 0, 16.0f);
            FLD(g_hero_state, s32, 0x2298) = 1;
            if (FLD(g_hero_state, u32, 0x2294) == 0x2C) {
                FLD(g_hero_state, s32, 0x24A0) = 7;
            } else {
                FLD(g_hero_state, s32, 0x24A0) = 0;
            }
        }
        if (FLD(g_hero_state, s16, 0x34E) == 0) {
            hero_play_footstep_effect();
            if (FLD(g_hero_state, f32, 0x118) < -0.15f) {
                FLD(g_hero_state, f32, 0x118) = -0.15f;
            }
            if (FLD(g_hero_state, f32, 0xF8) < -0.15f) {
                FLD(g_hero_state, f32, 0xF8) = -0.15f;
            }
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l20_set_move_state_us2(0x39, 1);
            } else {
                s32 one = 1;
                s32 low = FLD(g_hero_state, s32, 0x33C) == 0;
                if (FLD(g_hero_state, s32, 0x1B8) >= 0x5A) {
                    if (hero_l20_set_move_state_us2(0, 0) != 0) {
                        set_hero_animation(0xC, 4, 6.0f);
                    }
                    if (low != 0) {
                        FLD(g_hero_state, s16, 0x1E0) = 0x16;
                    }
                    hero_set_level_clock_and_bytes(0xA, 4, 0, 1, 0.022f, 0.004f);
                } else if (FLD(g_hero_state, s32, 0x2298) == one) {
                    if (hero_l20_set_move_state_us2(0, 0) != 0) {
                        set_hero_animation(0xC, 9, -1.0f);
                    }
                    cam_set_view_space_height(g_hero_state + 0x160, g_hero_state + 0x160, 0.0f);
                    vec_clamp_length((f32 *)(g_hero_state + 0x160), 0.116666675f);
                    FLD(g_hero_state, s16, 0x1E0) = 7;
                    if (FLD(g_hero_state, s32, 0x22A0) == 0x2C) {
                        FLD(g_hero_state, s16, 0x1E0) = 0xA;
                    }
                    if ((low != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0x33)) {
                        FLD(g_hero_state, s16, 0x1E0) = 0x12;
                    }
                    hero_set_level_clock_and_bytes(0xA, 2, 0, 1, 0.019f, 0.002f);
                } else if ((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (FLD(g_hero_state, s16, 0x1E0) == 0)) {
                    hero_l20_set_move_state_us2(2, 1);
                    hero_set_level_clock_and_bytes(7, 2, 0, 1, 0.016f, 0.002f);
                } else if (FLD(g_hero_state, f32, 0x174) > 0.050000004f) {
                    if (hero_l20_set_move_state_us2(3, 0) != 0) {
                        set_hero_animation(6, 0, 12.0f);
                        vec_clamp_length((f32 *)(g_hero_state + 0x160), 0.12833333f);
                    }
                } else {
                    hero_l20_set_move_state_us2(0, 1);
                    hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
                }
            }
        } else if (FLD(g_hero_state, s32, 0x24CC) > 0) {
            if ((FLD(g_pad_state, s32, 0x1A0) & 0x40) && (g_item_owned_flags[2] != 0) && (hero_slot_item_id(3) != 4) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (FLD(g_hero_state, f32, 0x31C) > 0.6f)) {
                hero_l20_set_move_state_us2(8, 1);
                break;
            }
            if ((FLD(g_hero_state, s16, 0x202) >= 0x15) && (hero_try_start_move_from_buffer((FLD(g_hero_state, s16, 0x1EE) != 0) ? 1 : 6, 0) != 0)) {
                break;
            }
            if (FLD(g_hero_state, s32, 0x578) != 0) {
                hero_l20_set_move_state_us2(0x17, 1);
                break;
            }
            if (FLD(g_hero_state, s32, 0x63C) != 0) {
                hero_l20_set_move_state_us2(0x27, 1);
                break;
            }
        }
        break;
    case 0x74:
        if (g_current_map_index == 0xD) {
            f32 y = FLD(g_hero_state, f32, 0x88);
            if ((FLD(g_hero_state, s32, 0x22A4) == 0x1E) || (FLD(g_hero_state, s32, 0x22B0) == 0x1E)) {
                s32 t = FLD(g_hero_state, s32, 0x1B8);
                if (((y < 51.0f) && (t >= 0x1F)) || (t >= 0x1F) && (FLD(g_hero_state, u8, 0x287) != 0) && ((FLD(g_hero_state, f32, 0x118) >= 0.0f) || (FLD(g_hero_state, u8, 0x149B) != 0))) {
                    hero_record_play_counters();
                    return;
                }
            } else if ((y < 89.0f) || ((FLD(g_hero_state, s32, 0x1B8) >= 0x15) && (FLD(g_hero_state, u8, 0x287) != 0) && (FLD(g_hero_state, f32, 0x118) >= 0.0f))) {
                hero_record_play_counters();
                return;
            }
        }
        if (FLD(g_hero_state, s32, 0x1B8) < 0x79) {
            break;
        }
        hero_record_play_counters();
        return;
    case 0x82:
    {
        u8 *p = g_hero_state + 0xF0;
        if (cam_get_view_space_height((s8 *)p) < 0.0f) {
            p -= 0xF0;
            if (FLD(p, s32, 0x340) != 0) {
                u8 *q = FLD(p, u8 *, 0x33C);
                if ((q == NULL) || (FLD(q, s16, 0xAA) == 0x8E2)) {
                    if (hero_l20_set_move_state_us2(0, 0) != 0) {
                        FLD(p, s8, 0x24EF) = 0;
                        set_hero_animation(7, 0x17, 9.0f);
                        hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
                    }
                }
            }
        }
        if (FLD(g_hero_state, f32, 0x5B0) == 0.0f) {
            if ((g_current_map_index == 0xD) && (FLD(g_hero_state, f32, 0x318) < 69.0f)) {
                hero_l20_set_move_state_us2(0x74, 1);
            } else {
                hero_l20_set_move_state_us2(6, 1);
            }
        }
        break;
    }
    case 0x8:
        if ((FLD(g_hero_state, s32, 0x1D4) != 0) && (FLD(g_hero_state, s32, 0x1B8) < 9)) {
            s32 prev = FLD(g_hero_state, s32, 0x22A0);
            s32 ok = 0;
            if ((prev == 7) || (prev == 9) || (prev == 0xE) || (prev == 0x11)) {
                ok = 1;
            }
            if (ok != 0) {
                hero_l20_set_move_state_us2(0x11, 1);
            }
            break;
        }
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0x1F) && !(FLD(g_pad_state, s32, 0x1A0) & 0x40) && !(FLD(g_pad_state, s32, 0x1C0) & 0x40)) {
            hero_l20_set_move_state_us2(6, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x578) != 0) {
            hero_l20_set_move_state_us2(0x17, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) != 0) && !(FLD(g_hero_state, f32, 0x31C) < 0.4f)) {
            break;
        }
        if (FLD(g_hero_state, s32, 0x1B8) < 0xA) {
            FLD(g_hero_state, s16, 0x1EE) = 0xC - FLD(g_hero_state, u16, 0x1B8);
        }
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, s32, 0x22A0) == 0x10) && (FLD(g_hero_state, s32, 0x1B8) < 4)) {
            if (hero_l20_set_move_state_us2(3, 0) != 0) {
                set_hero_animation(5, 0, -1.0f);
                FLD(g_hero_state, s16, 0x1E0) = 0x22;
            }
            break;
        }
        if (FLD(g_pad_state, s32, 0x1A0) & 8) {
            hero_l20_set_move_state_us2(4, 1);
            hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
            break;
        }
        if ((g_hero_l20_speed_params[0][2] < FLD(g_hero_state, f32, 0x1B0)) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) < 1.5707964f)) {
            if ((FLD(g_hero_state, u8, 0x1492) != 0) || (FLD(g_hero_state, u8, 0x22B9) != 0)) {
                hero_l20_set_move_state_us2(2, 1);
                break;
            }
            hero_l20_set_move_state_us2(2, 0);
            if (FLD(g_hero_state, u32, 0x2294) == 2) {
                FLD(g_hero_state, s32, 0x2298) = 1;
                set_hero_animation(4, 2, 8.0f);
                FLD(g_hero_state, s8, 0x40E) = 1;
            }
            hero_set_level_clock_and_bytes(5, 2, 1, 0, 0.016f, 0.002f);
        } else if (g_hero_l20_speed_params[0][2] < FLD(g_hero_state, f32, 0x1B0)) {
            if ((FLD(g_hero_state, u8, 0x1492) != 0) || (FLD(g_hero_state, u8, 0x22B9) != 0)) {
                hero_l20_set_move_state_us2(2, 1);
                break;
            }
            hero_l20_set_move_state_us2(2, 0);
            if (FLD(g_hero_state, u32, 0x2294) == 2) {
                FLD(g_hero_state, s32, 0x2298) = 1;
                set_hero_animation(4, g_hero_l20_animation_id_extra, 12.0f);
            }
            hero_set_level_clock_and_bytes(5, 2, 1, 0, 0.016f, 0.002f);
        } else if (FLD(g_hero_state, s16, 0x34E) == 0) {
            if (hero_l20_set_move_state_us2(0, 0) != 0) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, -2.0f);
                hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
            }
        } else if (hero_l20_set_move_state_us2(0, 0) != 0) {
            set_hero_animation(7, 0x17, 9.0f);
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
        u32 sa;
        u32 sb;
        u32 sc;
        s32 lim;
        s32 frames;
        if (FLD(g_hero_state, u8, 0x52E) != 0) {
            s32 n = hero_get_step_offset_from_direction();
            if ((n > 0) && ((FLD(g_hero_state, s32, 0x1B8) < n) || (FLD(g_hero_state, u8, 0x49C) != 0)) && (FLD(g_hero_state, s32, 0x340) != 0)) {
                if ((FLD(g_hero_state, u32, 0x2294) != 0xB) || (PadPressedWithin(0x40, 7, NULL) != 0)) {
                    s32 go = 1;
                    if ((FLD(g_hero_state, u32, 0x2294) == 0x1B) || (FLD(g_hero_state, u8, 0x49C) != 0)) {
                        if (PadPressedWithin(0x40, 7, NULL) == 0) {
                            go = 0;
                        }
                    }
                    if (FLD(g_hero_state, u32, 0x2294) == 0xB) {
                        if (FLD(g_hero_state, u8, 0x49C) == 0) {
                            go = 0;
                        }
                    }
                    if ((go != 0) && (PadPressedWithin(0x1F000, 5, NULL) != 0) && (FLD(g_pad_state, s32, 0x1A0) & 8)) {
                        hero_l20_set_move_state_us2(0xB, 1);
                        break;
                    }
                }
            }
        }
        if ((FLD(g_hero_state, s16, 0x1F2) != 0) && ((FLD(g_hero_state, u32, 0x2294) == 7) || (FLD(g_hero_state, u32, 0x2294) == 9)) && (FLD(g_hero_state, s32, 0x1B8) < 0x14)) {
            hero_l20_set_move_state_us2(0x82, 1);
            break;
        }
        if ((FLD(g_hero_state, u32, 0x2294) == 0x1B) && (FLD(g_hero_state, s32, 0x1B8) >= 0x15) && (FLD(g_hero_state, f32, 0x278) > 0.7f)) {
            FLD(g_hero_state, s8, 0x22BF) = 0;
            FLD(g_hero_state, s8, 0x22BC) = 0;
        }
        if ((FLD(g_hero_state, s32, 0x1B8) < 7) && (PadPressedWithin(8, 2, NULL) != 0) && ((sa = FLD(g_hero_state, u32, 0x2294)) != 0x10) && (sa != 0xA) && (sa != 0x12) && (sa != 0x38) && (sa != 0x11) && (sa != 0xE) && (sa != 0x66)) {
            if ((hero_slot_item_id(3) == 2) && (g_item_owned_flags[2] != 0) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_hero_state, f32, 0x178) > 0.015000001f)) {
                hero_l20_set_move_state_us2(0xA, 1);
            } else if ((hero_slot_item_id(3) == 3) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_hero_state, f32, 0x178) > 0.015000001f) && (FLD(g_hero_state, s16, 0x1E4) == 0)) {
                hero_l20_set_move_state_us2(0x10, 1);
            }
        }
        if (FLD(g_hero_state, s32, 0x63C) != 0) {
            hero_l20_set_move_state_us2(0x27, 1);
            break;
        }
        {
            if (FLD(g_hero_state, s16, 0x51A) < FLD(g_hero_state, s32, 0x1B8)) {
                if (FLD(g_hero_state, u8, 0x49C) == 0) {
                    hero_l20_set_move_state_us2(6, 1);
                    break;
                }
            } else if ((FLD(g_hero_state, u8, 0x49C) == 0) && ((FLD(g_hero_state, u32, 0x2294) == 0xA) || (FLD(g_hero_state, u32, 0x2294) == 0x10)) && (FLD(g_hero_state, f32, 0x278) < 0.9f) && (FLD(g_hero_state, u8, 0x287) != 0) && (FastVecLength(g_hero_state + 0xF0) > 0.116666675f)) {
                f32 a = FastVecLength(g_hero_state + 0x110);
                if ((a < FastVecLength(g_hero_state + 0xF0) * 0.5f) && (FLD(g_hero_state, s32, 0x578) == 0) && (FLD(g_hero_state, f32, 0x31C) < 2.0f)) {
                    hero_l20_set_move_state_us2(0x77, 1);
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
                EvaluateQuantizedHeight((f32 *)(g_hero_state + 0x80), (f32 *)(g_hero_state + 0xF0), &sp68, FLD(g_hero_state, f32, 0x520));
                AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4C8), (f32)sp68, FLD(g_hero_state, f32, 0x514), -1.0f);
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
            part_emit_hero_dust_and_debris(3, 0x18, 1);
        }
        {
            u8 c = FLD(g_hero_state, u8, 0x49C);
            if (c != 0) {
                FLD(g_hero_state, u8, 0x49C) = c + 1;
            } else if ((FLD(g_hero_state, s16, 0x34E) == 0) && (FLD(g_hero_state, u8, 0x49E) != 0) && (near == 0)) {
                hero_play_footstep_effect();
                FLD(g_hero_state, u8, 0x49C) = 1;
                FLD(g_hero_state, s8, 0x24DB) = 0;
                if ((FLD(g_hero_state, f32, 0x24B8) < 0.2f) && (FLD(g_hero_state, f32, 0x1B4) > 0.041666668f)) {
                    FLD(g_hero_state, f32, 0x1B4) = 0.041666668f;
                }
                hero_set_level_clock_and_bytes(5, 2, 0, 1, 0.016f, 0.002f);
                if (near == 0) {
                    s32 k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 2;
                    if (FLD(g_hero_state, f32, 0xC38) < FLD(g_hero_state, f32, 0x4CC) - 1.5f) {
                        set_hero_animation(math_l00_return_argument(FLD(sp74, u8, 0x43)), k, 7.0f);
                    }
                }
            }
        }
        if (FLD(g_hero_state, u8, 0x49C) != 0) {
            FLD(g_hero_state, f32, 0xC20) = 1.0f;
        } else if (FLD(g_hero_state, u8, 0x49E) != 0) {
            s32 cur;
            if ((s32)FLD(sp74, u8, 0x41) < FloatToInt(FLD(g_hero_state, f32, 0x4D0))) {
                if ((FLD(g_hero_state, u32, 0x2294) == 0xE) && (FLD(g_hero_state, f32, 0xC38) < 37.0f)) {
                    ApproachValue((f32 *)(g_hero_state + 0xC20), 1.0f, 0.15f);
                } else {
                    FLD(g_hero_state, s16, 0x4AE) = FloatToInt(hero_find_collision_time(60.0f, FLD(g_hero_state, f32, 0x520), -1.0f));
                    AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4CC), (f32)FLD(g_hero_state, s16, 0x4AE), FLD(g_hero_state, f32, 0x514), 0.2f);
                }
                if (near == 0) {
                    s32 k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 2;
                    if (FLD(g_hero_state, f32, 0xC20) > 1.8f) {
                        set_hero_animation(math_l00_return_argument(FLD(sp74, u8, 0x43)), k, (f32)(FLD(g_hero_state, s16, 0x4AE) + 3));
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
            if ((cur == 9) && ((FLD(g_hero_state, f32, 0x4CC) - FLD(g_hero_state, f32, 0xC38)) > 6.0f) && ((math_l00_return_argument(FLD(sp74, u8, 0x42)) == 8) || (math_l00_return_argument(FLD(sp74, u8, 0x42)) == cur)) && (FLD(sp74, u8, 0x42) == FLD(sp74, u8, 0x43)) && (FLD(g_hero_state, f32, 0x1B0) < g_hero_l20_speed_params[1][1] * 0.0016666668f) && (FLD(g_hero_state, f32, 0x174) < 0.041666668f)) {
                f32 rate = 9.0f / FLD(g_hero_state, f32, 0xC20);
                s32 at;
                if (rate > 10.0f) {
                    rate = 10.0f;
                }
                at = FloatToInt(FLD(g_hero_state, f32, 0xC38)) + 4;
                set_hero_animation(7, at / 2, rate);
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
                if (hero_l20_set_move_state_us2(3, 0) != 0) {
                    set_hero_animation(5, 0, -2.0f);
                    FastVecScale(g_hero_state + 0x160, g_hero_state + 0x160, 0.8f);
                }
                break;
            }
            if ((FLD(g_hero_state, u8, 0x149A) == 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (PadPressedWithin(0x40, 8, NULL) != 0) && (FLD(g_hero_state, s16, 0x34E) < 4)) {
                if (!(FLD(g_hero_state, f32, 0x1B0) > g_hero_l20_speed_params[0][2])) {
                    hero_l20_set_move_state_us2(7, 1);
                } else if (!(FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) < 1.0471976f)) {
                    hero_l20_set_move_state_us2(7, 1);
                } else if (g_hero_l20_speed_params[1][1] * 0.014166668f < FLD(g_hero_state, f32, 0x174)) {
                    hero_l20_set_move_state_us2(9, 1);
                } else {
                    hero_l20_set_move_state_us2(7, 1);
                }
                break;
            }
        }
        if ((FLD(g_hero_state, u8, 0x49C) >= 2) && (FLD(g_hero_state, u32, 0x2294) != 0xA)) {
            hero_choose_next_move_after_landing();
        } else if ((FLD(g_hero_state, u8, 0x49E) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= FLD(g_hero_state, s16, 0x52A)) && (FLD(g_hero_state, f32, 0x31C) > FLD(g_hero_state, f32, 0x510))) {
            hero_l20_set_move_state_us2(6, 1);
        }
        if ((FLD(g_hero_state, u32, 0x2294) == 0x10) && (FLD(g_hero_state, s32, 0x1B8) >= 0x3D) && (FLD(g_hero_state, f32, 0x31C) > 1.5f)) {
            hero_l20_set_move_state_us2(6, 1);
            break;
        }
        {
            u32 s = FLD(g_hero_state, u32, 0x2294);
            s32 ok = 0;
            if ((s == 7) || (s == 9) || (s == 0x11)) {
                ok = 1;
            }
            if ((FLD(g_hero_state, s32, 0x1D4) != 0) && (FLD(g_hero_state, u8, 0x49C) == 0) && (ok != 0) && ((FLD(g_hero_state, u32, 0x2294) != 0x11) || (FLD(g_hero_state, s32, 0x1B8) >= 0x1A)) && (PadPressedWithin(0x40, 7, &sp6C) != 0) && (sp6C < FLD(g_hero_state, s32, 0x1B8))) {
                hero_l20_set_move_state_us2(0x11, 1);
                break;
            }
        }
        if (((FLD(g_hero_state, u32, 0x2294) == 0xA) || (FLD(g_hero_state, u32, 0x2294) == 0x10)) && (FLD(g_hero_state, s32, 0x1B8) >= 0x1A) && (FLD(g_hero_state, s16, 0x34A) != 0)) {
            FLD(g_hero_state, s16, 0x526) = 0x14;
        }
        sc = FLD(g_hero_state, u32, 0x2294);
        lim = 0x14;
        if (sc == 0x10) {
            lim = 8;
        }
        if ((sc == 0xE) && (FLD(g_hero_state, f32, 0x31C) > 4.0f)) {
            if ((FLD(g_hero_state, u8, 0x49E) == 0) && (FLD(g_hero_state, f32, 0xC20) < 1.3f)) {
                ApproachValue((f32 *)(g_hero_state + 0xC20), 1.3f, 0.1f);
            }
            lim = 0x11;
            FLD(g_hero_state, s16, 0x526) = lim;
        }
        frames = FLD(g_hero_state, s32, 0x1B8) - 4;
        if (frames <= 1) {
            frames = 2;
        }
        if (frames >= 0x1F) {
            frames = 0x1E;
        }
        if (!(FLD(g_hero_state, s64, 0x498) & 0xFF0000FF00000000LL)) {
            if ((PadPressedWithin(0x40, frames, NULL) != 0) || (FLD(g_hero_state, u32, 0x2294) == 0xE) || (FLD(g_hero_state, u32, 0x2294) == 0xF) || (FLD(g_hero_state, u32, 0x2294) == 0xD)) {
                if ((FLD(g_hero_state, u32, 0x2294) != 0xE) && (FLD(g_hero_state, u8, 0x22B8) == 0) && ((FLD(g_hero_state, u8, 0x149A) == 0) || (FLD(g_hero_state, f32, 0x31C) >= 0.4f)) && (FLD(g_hero_state, u8, 0x52F) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0xF) && ((FLD(g_hero_state, u8, 0x49E) == 0) || ((FLD(g_hero_state, f32, 0x31C) > 0.7f) && (math_fabs(cam_get_view_space_height((s8 *)(g_hero_state + 0xF0))) < 0.09666667f)))) {
                    hero_l20_set_move_state_us2(0xE, 1);
                } else if ((g_item_owned_flags[2] != 0) && (hero_slot_item_id(3) != 4) && (FLD(g_hero_state, s16, 0x24FC) == 0) && (FLD(g_pad_state, s32, 0x1A0) & 0x40) && (lim < FLD(g_hero_state, s32, 0x1B8)) && (FLD(g_hero_state, s16, 0x526) < FLD(g_hero_state, s32, 0x1B8))) {
                    f32 need = 0.6f;
                    if ((FLD(g_hero_state, u32, 0x2294) == 9) || (FLD(g_hero_state, u32, 0x2294) == 7)) {
                        need = 1.0f;
                    }
                    if (FLD(g_hero_state, u32, 0x2294) == 0xE) {
                        need = 1.5f;
                    }
                    if (need < FLD(g_hero_state, f32, 0x31C)) {
                        hero_l20_set_move_state_us2(8, 1);
                    }
                }
            }
        }
        if ((FLD(g_hero_state, s32, 0x578) != 0) && (FLD(g_hero_state, u32, 0x2294) != 0xB)) {
            hero_l20_set_move_state_us2(0x17, 1);
        }
        break;
    }
    case 0x16:
        if ((FLD(g_hero_state, f32, 0xC38) > 12.5f) && (FLD(g_hero_state, u8, 0x24EF) == 0) && (FLD(g_hero_state, s16, 0x34E) != 0) && (FLD(g_hero_state, f32, 0x31C) > 1.0f)) {
            hero_l20_set_move_state_us2(6, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x1C) {
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                if (FLD(g_hero_state, u8, 0x1495) != 0) {
                    hero_l20_set_move_state_us2(0x79, 1);
                } else {
                    hero_l20_set_move_state_us2(0x39, 1);
                }
            } else if (FLD(g_hero_state, u8, 0x24EF) != 0) {
                hero_l20_set_move_state_us2(0x82, 1);
            } else {
                hero_l20_set_move_state_us2(0, 0);
            }
        }
        break;
    case 0x8C:
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            set_hero_animation(0x97, 0, 2.0f);
        }
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0x33) && (FLD(g_hero_state, s16, 0x1E0) == 0)) {
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l20_set_move_state_us2(0x39, 1);
            } else if (hero_l20_set_move_state_us2(0, 0) != 0) {
                set_hero_animation(SelectHeroStateAnimation(0), 0, 13.0f);
            }
        }
        break;
    case 0x85:
        if ((FLD(g_hero_state, s32, 0x1B8) >= 4) && (FLD(g_pad_state, s32, 0x1A4) & 0x10)) {
            hero_load_state_by_game_mode(0);
        }
        break;
    case 0x3F:
    {
        s16 t = FLD(g_hero_state, s16, 0x2520);
        if (t >= 0x2B) {
            set_hero_animation(0x12, 0, 10.0f);
            break;
        }
        if ((t == 0) && (FLD(g_hero_state, s32, 0xC28) & 2)) {
            if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0) {
                set_hero_animation(0, 0, 12.0f);
            } else if (math_random_float_range(0.0f, 1.0f) < 0.5f) {
                set_hero_animation(1, 0, 8.0f);
            }
        }
        if (FLD(g_hero_state, u8, 0x149A) != 0) {
            hero_l20_set_move_state_us2(0x4E, 1);
            break;
        }
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l20_set_move_state_us2(1, 1);
            break;
        }
        if (FLD(g_hero_state, s16, 0x34E) != 0) {
            hero_l20_set_move_state_us2(0x41, 1);
            break;
        }
        if (PadPressedWithin(0x40, 8, NULL) != 0) {
            hero_l20_set_move_state_us2(0x45, 1);
            break;
        }
        if (PadPressedWithin(0x80, 9, NULL) != 0) {
            hero_l20_set_move_state_us2(0x4D, 1);
            break;
        }
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.2f) && (FLD(g_hero_state, f32, 0x1B0) > 0.0f)) {
            hero_l20_set_move_state_us2(0x40, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x2520) == 0) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 0x12)) {
            set_hero_animation(0, 0, 12.0f);
        }
        break;
    }
    case 0x4D:
    {
        u8 *rec;
        s32 frames;
        if (FLD(g_hero_state, u8, 0x149A) != 0) {
            hero_l20_set_move_state_us2(0x4E, 1);
            break;
        }
        rec = (u8 *)&g_hero_l20_action_table[FLD(g_hero_state, s16, 0xBFC)];
        if (FLD(g_hero_state, s32, 0xC2C) == 0) {
            s32 busy;
            if ((f32)FLD(rec, s32, 0x18) < FLD(g_hero_state, f32, 0xC38)) {
                hero_l20_set_move_state_us2(0x3F, 0);
            }
            busy = FLD(g_hero_state, s32, 0xC2C);
            if ((busy == 0) && ((f32)FLD(rec, s32, 0x10) <= FLD(g_hero_state, f32, 0xC38))) {
                s32 n = FloatToInt(FLD(g_hero_state, f32, 0xC38)) - FLD(rec, s32, 0xC);
                if (n < 1) {
                    n = 1;
                }
                if (PadPressedWithin(0x80, (n < 0x10) ? n : 0xF, NULL) != 0) {
                    hero_l20_set_move_state_us2(0x4D, 1);
                }
            }
        }
        frames = (FloatToInt(FLD(g_hero_state, f32, 0xC38)) - FLD(rec, s32, 0xC)) * 2;
        if (((f32)FLD(rec, s32, 0x14) < FLD(g_hero_state, f32, 0xC38)) && (FLD(g_hero_state, s32, 0xC2C) == 0) && (PadPressedWithin(0x40, frames, NULL) != 0)) {
            hero_l20_set_move_state_us2(0x45, 1);
        }
        break;
    }
    case 0x45:
    case 0x48:
    {
        s16 lo = FLD(g_hero_state, s16, 0x4AC);
        s32 now = FLD(g_hero_state, s32, 0x1B8);
        if (!(lo < now)) {
            break;
        }
        if (now == lo + 1) {
            EvaluateQuantizedHeight((f32 *)(g_hero_state + 0x80), (f32 *)(g_hero_state + 0xF0), &sp70, FLD(g_hero_state, f32, 0x520));
            AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4C8), (f32)sp70, FLD(g_hero_state, f32, 0x514), -1.0f);
            break;
        }
        if ((FLD(g_hero_state, u8, 0x49D) != 0) && (now >= FLD(g_hero_state, s32, 0x430)) && (now < FLD(g_hero_state, s32, 0x434))) {
            f32 left = (f32)(FLD(g_hero_state, s32, 0x440) - FLD(g_hero_state, s32, 0x430));
            if (left > 0.0f) {
                AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4C8), left, FLD(g_hero_state, f32, 0x514), -1.0f);
            }
            break;
        }
        {
            u8 c = FLD(g_hero_state, u8, 0x49C);
            if (c != 0) {
                FLD(g_hero_state, u8, 0x49C) = c + 1;
            } else if ((FLD(g_hero_state, s16, 0x34E) == 0) && (FLD(g_hero_state, u8, 0x49E) != 0)) {
                s32 k;
                FLD(g_hero_state, u8, 0x49C) = 1;
                k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 3;
                if (FLD(g_hero_state, f32, 0xC38) < FLD(g_hero_state, f32, 0x4CC)) {
                    set_hero_animation(FLD(sp74, u8, 0x43), k, 6.0f);
                }
            }
        }
        if (FLD(g_hero_state, u8, 0x49C) != 0) {
            FLD(g_hero_state, f32, 0xC20) = 1.0f;
        } else if (FLD(g_hero_state, u8, 0x49E) != 0) {
            s32 a;
            if ((s32)FLD(sp74, u8, 0x41) < FloatToInt(FLD(g_hero_state, f32, 0x4D0))) {
                s32 k;
                FLD(g_hero_state, s16, 0x4AE) = FloatToInt(hero_find_collision_time(60.0f, FLD(g_hero_state, f32, 0x520), -1.0f));
                AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4CC), (f32)FLD(g_hero_state, s16, 0x4AE), FLD(g_hero_state, f32, 0x514), -1.0f);
                k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 1;
                if (FLD(g_hero_state, f32, 0xC20) > 1.8f) {
                    set_hero_animation(FLD(sp74, u8, 0x43), k, (f32)(FLD(g_hero_state, s16, 0x4AE) + 2));
                }
                if (FLD(g_hero_state, f32, 0xC20) < 0.2f) {
                    FLD(g_hero_state, f32, 0xC20) = 0.2f;
                }
                if (FLD(g_hero_state, f32, 0xC20) > 2.7f) {
                    FLD(g_hero_state, f32, 0xC20) = 2.7f;
                }
            }
            a = FloatToInt(FLD(g_hero_state, f32, 0xC38));
            if (a == FloatToInt(FLD(g_hero_state, f32, 0x4CC))) {
                FLD(g_hero_state, s32, 0xC20) = 0;
            }
        }
        if ((FLD(g_hero_state, u8, 0x49C) != 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (FLD(g_hero_state, u8, 0x149A) == 0) && (PadPressedWithin(0x40, 4, NULL) != 0) && (FLD(g_hero_state, s16, 0x34E) < 4)) {
            hero_resolve_stick_direction(0, 1.0f);
            hero_l20_set_move_state_us2(0x45, 1);
            break;
        }
        if (FLD(g_hero_state, u8, 0x49C) >= 2) {
            FLD(g_hero_state, s32, 0x24A0) = 0;
            hero_resolve_stick_direction(0, 1.0f);
            if ((FLD(g_hero_state, f32, 0x1B0) > g_hero_l20_speed_params[0][2]) && (FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (FLD(g_hero_state, u8, 0x149A) == 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) < 1.5707964f)) {
                hero_l20_set_move_state_us2(0x40, 1);
            } else if (FLD(g_hero_state, u8, 0x49C) >= 0xD) {
                hero_l20_set_move_state_us2(0x3F, 1);
            }
        }
        if ((FLD(g_hero_state, f32, 0x31C) > 2.0f) && (FLD(g_hero_state, u8, 0x49E) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0x29)) {
            hero_l20_set_move_state_us2(0x41, 1);
            break;
        }
        if ((FLD(g_hero_state, u8, 0x49E) != 0) && (FLD(g_hero_state, f32, 0x31C) < 0.2f) && (PadPressedWithin(0x80, 5, NULL) != 0)) {
            hero_l20_set_move_state_us2(0x4D, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x578) != 0) {
            hero_l20_set_move_state_us2(0x46, 1);
            break;
        }
        if ((FLD(g_hero_state, u32, 0x2294) != 0x48) && (PadPressedWithin(0x40, 5, NULL) != 0) && (FLD(g_hero_state, f32, 0x31C) > 0.55f)) {
            hero_l20_set_move_state_us2(0x4B, 1);
        }
        break;
    }
    case 0x4B:
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0x1F) && !(FLD(g_pad_state, s32, 0x1A0) & 0x40)) {
            hero_l20_set_move_state_us2(0x41, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x578) != 0) {
            hero_l20_set_move_state_us2(0x46, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) != 0) && !((FLD(g_hero_state, f32, 0x88) - FLD(g_hero_state, f32, 0x318)) < 0.0f)) {
            break;
        }
        if (FLD(g_hero_state, s32, 0x1B8) < 0xA) {
            FLD(g_hero_state, s16, 0x1EE) = 0xC - FLD(g_hero_state, u16, 0x1B8);
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.3f) {
            hero_l20_set_move_state_us2(0x40, 1);
            break;
        }
        if (FLD(g_hero_state, s16, 0x34E) == 0) {
            hero_l20_set_move_state_us2(0x3F, 1);
        }
        break;
    case 0x41:
        if (FLD(g_hero_state, s16, 0x34E) == 0) {
            if (FLD(g_hero_state, f32, 0x118) < -0.15f) {
                FLD(g_hero_state, f32, 0x118) = -0.15f;
            }
            if (FLD(g_hero_state, f32, 0xF8) < -0.15f) {
                FLD(g_hero_state, f32, 0xF8) = -0.15f;
            }
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l20_set_move_state_us2(0x43, 1);
            } else if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
                if (FLD(g_hero_state, s16, 0x1E0) == 0) {
                    hero_l20_set_move_state_us2(0x40, 1);
                } else {
                    hero_l20_set_move_state_us2(0x3F, 1);
                }
            } else {
                hero_l20_set_move_state_us2(0x3F, 1);
            }
        } else if (FLD(g_hero_state, s32, 0x24CC) > 0) {
            if (FLD(g_hero_state, s32, 0x578) != 0) {
                hero_l20_set_move_state_us2(0x46, 1);
                break;
            }
            if ((PadPressedWithin(0x40, 5, NULL) != 0) && (FLD(g_hero_state, f32, 0x31C) > 0.6f)) {
                hero_l20_set_move_state_us2(0x4B, 1);
            }
        }
        break;
    case 0x44:
        if ((FLD(g_hero_state, f32, 0xF8) < 0.0f) && (FLD(g_hero_state, s32, 0x340) != 0)) {
            hero_l20_set_move_state_us2(0x3F, 1);
        }
        break;
    case 0x4E:
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x12D) {
            hero_record_play_counters();
        }
        if (FLD(g_hero_state, u8, 0x149A) == 0) {
            if (FLD(g_hero_state, s16, 0x34E) != 0) {
                hero_l20_set_move_state_us2(0x41, 1);
            } else {
                hero_l20_set_move_state_us2(0x3F, 1);
            }
        }
        break;
    case 0x40:
    {
        f32 speed;
        u8 *o;
        s32 anim;
        if (FLD(g_hero_state, u8, 0x149A) != 0) {
            hero_l20_set_move_state_us2(0x4E, 1);
            break;
        }
        if ((FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0x170) < 0.025000002f) && (FLD(o = FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 2)) {
            u8 *info = FLD(o, u8 *, 0x24);
            s32 n = FLD(FLD(info, u8 *, 0x50), u8, 0x10);
            set_hero_animation(2, (FLD(o, u8, 0x41) * n / FLD(FLD(info, u8 *, 0x54), u8, 0x10) + 1) % n, 8.0f);
        } else if ((FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0x170) > 0.030000003f) && (FLD(o = FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 3)) {
            u8 *info = FLD(o, u8 *, 0x24);
            s32 n = FLD(FLD(info, u8 *, 0x54), u8, 0x10);
            set_hero_animation(3, (FLD(o, u8, 0x41) * n / FLD(FLD(info, u8 *, 0x50), u8, 0x10) + 7) % n, 8.0f);
        }
        speed = FLD(g_hero_state, f32, 0x170);
        if (FLD(g_hero_state, u8, 0x40F) != 0) {
            speed = 0.050000004f;
        }
        anim = FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43);
        if (anim == 2) {
            FLD(g_hero_state, f32, 0xC20) = speed * 90.0f;
        } else if (anim == 3) {
            FLD(g_hero_state, f32, 0xC20) = speed * 20.0f;
        }
        if (FLD(g_hero_state, f32, 0xC20) < 0.57f) {
            FLD(g_hero_state, f32, 0xC20) = 0.57f;
        }
        if (PadPressedWithin(0x40, 8, NULL) != 0) {
            hero_l20_set_move_state_us2(0x45, 1);
            break;
        }
        if (PadPressedWithin(0x80, 9, NULL) != 0) {
            hero_l20_set_move_state_us2(0x4D, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 5) && ((FLD(g_hero_state, f32, 0x31C) > 0.8f) || (FLD(g_hero_state, f32, 0x320) > 0.8726647f))) {
            hero_l20_set_move_state_us2(0x41, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) == 0) && (FLD(g_hero_state, f32, 0x24B8) < 0.17f)) {
            hero_l20_set_move_state_us2(0x3F, 1);
        }
        break;
    }
    case 0x42:
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0x20) && (FLD(g_hero_state, s16, 0x34E) != 0) && (FLD(g_hero_state, f32, 0x31C) > 1.0f)) {
            hero_l20_set_move_state_us2(0x41, 1);
            break;
        }
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x24) {
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l20_set_move_state_us2(0x43, 1);
            } else {
                hero_l20_set_move_state_us2(0x3F, 0);
            }
        }
        break;
    case 0x46:
        if (FLD(g_hero_state, s32, 0xC28) & 2) {
            hero_l20_set_move_state_us2(0x47, 1);
        }
        break;
    case 0x47:
        hero_resolve_stick_direction(0, 1.0f);
        *(s128 *)v10 = FLD(g_hero_state + 0x80, s128, 0);
        if (hero_find_ledge_grab((s8 *)v10, (s8 *)(g_hero_state + 0x90), NULL) == 0) {
            hero_l20_set_move_state_us2(0x41, 1);
            FLD(g_hero_state, s16, 0x1D0) = 0xA;
            break;
        }
        if (((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 9, NULL) != 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) > 2.3561947f)) || (FLD(g_pad_state, s32, 0x1A0) & 8)) {
            hero_l20_set_move_state_us2(0x41, 1);
            FLD(g_hero_state, s16, 0x1D0) = 0xA;
            break;
        }
        if (PadPressedWithin(0x40, 9, NULL) != 0) {
            hero_l20_set_move_state_us2(0x48, 1);
            break;
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) < 0.78539824f) {
                qcopy(v20, g_hero_state + 0x80);
                v20[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) * 0.3f;
                v20[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), 1.5707965f)) * 0.3f;
                if (hero_find_ledge_grab((s8 *)v20, (s8 *)(g_hero_state + 0x90), NULL) != 0) {
                    hero_l20_set_move_state_us2(0x49, 1);
                }
                break;
            }
        }
        if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
            if (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) < 0.78539824f) {
                qcopy(v20, g_hero_state + 0x80);
                v20[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) * 0.3f;
                v20[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), -1.5707965f)) * 0.3f;
                if (hero_find_ledge_grab((s8 *)v20, (s8 *)(g_hero_state + 0x90), NULL) != 0) {
                    hero_l20_set_move_state_us2(0x4A, 1);
                }
            }
        }
        break;
    case 0x49:
    case 0x4A:
    {
        f32 side;
        *(s128 *)v10 = FLD(g_hero_state + 0x80, s128, 0);
        side = 1.5707965f;
        if (FLD(g_hero_state, u32, 0x2294) == 0x4A) {
            side = -1.5707965f;
        }
        v10[0] += math_fast_sin_or_cos_a(FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) * 0.3f;
        v10[1] += math_fast_sin_or_cos_b(FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) * 0.3f;
        hero_resolve_stick_direction(0, 1.0f);
        if ((FLD(g_hero_state, f32, 0x24B8) < 0.5f) || (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FastAddRotations(FLD(g_hero_state, f32, 0x98), side)) > 0.78539824f) || (hero_find_ledge_grab((s8 *)v10, (s8 *)(g_hero_state + 0x90), NULL) == 0)) {
            if (FLD(g_hero_state, s32, 0xC28) & 2) {
                hero_l20_set_move_state_us2(0x47, 1);
                break;
            }
        }
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (PadPressedWithin(0x40, 9, NULL) != 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) > 2.3561947f)) {
            hero_l20_set_move_state_us2(0x41, 1);
            FLD(g_hero_state, s16, 0x1D0) = 0x28;
            break;
        }
        if (PadPressedWithin(0x40, 9, NULL) != 0) {
            hero_l20_set_move_state_us2(0x48, 1);
        }
        break;
    }
    case 0x8D:
    {
        s32 turned;
        if ((FLD(g_hero_state, s32, 0xC28) & 2) && (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 0xD)) {
            set_hero_animation(0xD, 0, 12.0f);
        }
        if (FLD(g_hero_state, u8, 0x149A) != 0) {
            hero_l20_set_move_state_us2(0x94, 1);
            break;
        }
        if ((FLD(g_pad_state, s32, 0x1A0) & 4) && (FLD(g_hero_state, s32, 0x1500) == 0) && (level_get_saved_value() == 0)) {
            hero_l20_set_move_state_us2(1, 1);
            break;
        }
        if (FLD(g_hero_state, s16, 0x34E) != 0) {
            hero_l20_set_move_state_us2(0x8F, 1);
            break;
        }
        if (PadPressedWithin(0x40, 8, NULL) != 0) {
            hero_l20_set_move_state_us2(0x92, 1);
            break;
        }
        if ((FLD(FLD(g_hero_state, u8 *, 0x2290), s16, 0xAA) != 0xEE1) && (PadPressedWithin(0x80, 9, NULL) != 0)) {
            hero_l20_set_move_state_us2(0x93, 1);
            break;
        }
        hero_resolve_stick_direction(0, 1.0f);
        turned = hero_is_turned_past_angle(0.17453295f);
        if ((FLD(g_hero_state, f32, 0x24B8) > 0.2f) || (turned != 0)) {
            hero_l20_set_move_state_us2(0x8E, 1);
        }
        break;
    }
    case 0x93:
        if (FLD(g_hero_state, u8, 0x149A) != 0) {
            hero_l20_set_move_state_us2(0x94, 1);
        }
        break;
    case 0x92:
    {
        s32 lo;
        s32 now;
        hero_update_held_grab();
        lo = FLD(g_hero_state, s16, 0x4AC);
        now = FLD(g_hero_state, s32, 0x1B8);
        if (!(lo < now)) {
            break;
        }
        if (now == lo + 1) {
            if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 6) {
                EvaluateQuantizedHeight((f32 *)(g_hero_state + 0x80), (f32 *)(g_hero_state + 0xF0), &sp74w, FLD(g_hero_state, f32, 0x520));
                AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4C8), (f32)sp74w, 0.5f, -1.0f);
            }
            break;
        }
        {
            u8 c = FLD(g_hero_state, u8, 0x49C);
            if (c != 0) {
                FLD(g_hero_state, u8, 0x49C) = c + 1;
            } else if ((FLD(g_hero_state, s16, 0x34E) == 0) && (FLD(g_hero_state, u8, 0x49E) != 0)) {
                FLD(g_hero_state, u8, 0x49C) = 1;
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != 6) {
                    goto after_pose;
                }
                {
                    s32 k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 3;
                    if (FLD(g_hero_state, f32, 0xC38) < FLD(g_hero_state, f32, 0x4CC)) {
                        set_hero_animation(FLD(sp74, u8, 0x43), k, 6.0f);
                    }
                }
            }
        }
        if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) == 6) {
            if (FLD(g_hero_state, u8, 0x49C) != 0) {
                FLD(g_hero_state, f32, 0xC20) = 1.0f;
            } else if (FLD(g_hero_state, u8, 0x49E) != 0) {
                s32 a;
                if ((s32)FLD(sp74, u8, 0x41) < FloatToInt(FLD(g_hero_state, f32, 0x4D0))) {
                    s32 k;
                    FLD(g_hero_state, s16, 0x4AE) = FloatToInt(hero_find_collision_time(60.0f, FLD(g_hero_state, f32, 0x520), -1.0f));
                    AdjustHeroAnimationSpeedForTargetFrame(FLD(g_hero_state, f32, 0x4CC), (f32)FLD(g_hero_state, s16, 0x4AE), 0.5f, -1.0f);
                    k = FloatToInt(FLD(g_hero_state, f32, 0x4D0)) + 1;
                    if (FLD(g_hero_state, f32, 0xC20) > 1.8f) {
                        set_hero_animation(FLD(sp74, u8, 0x43), k, (f32)(FLD(g_hero_state, s16, 0x4AE) + 2));
                    }
                    if (FLD(g_hero_state, f32, 0xC20) < 0.2f) {
                        FLD(g_hero_state, f32, 0xC20) = 0.2f;
                    }
                    if (FLD(g_hero_state, f32, 0xC20) > 2.7f) {
                        FLD(g_hero_state, f32, 0xC20) = 2.7f;
                    }
                }
                a = FloatToInt(FLD(g_hero_state, f32, 0xC38));
                if (a == FloatToInt(FLD(g_hero_state, f32, 0x4CC))) {
                    FLD(g_hero_state, s32, 0xC20) = 0;
                }
            }
        }
    after_pose:
        if ((FLD(g_hero_state, u8, 0x49C) != 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (PadPressedWithin(0x40, 4, NULL) != 0) && (FLD(g_hero_state, s16, 0x34E) < 4)) {
            hero_resolve_stick_direction(0, 1.0f);
            hero_l20_set_move_state_us2(0x92, 1);
            break;
        }
        if (FLD(g_hero_state, u8, 0x49C) >= 2) {
            FLD(g_hero_state, s32, 0x24A0) = 0;
            hero_resolve_stick_direction(0, 1.0f);
            if ((FLD(g_hero_state, f32, 0x1B0) > g_hero_l20_speed_params[0][2]) && (FLD(g_hero_state, f32, 0x24B8) > 0.5f) && (FLD(g_hero_state, u8, 0x149A) == 0) && (FLD(g_hero_state, s16, 0x1E0) == 0) && (FastDiffRots(FLD(g_hero_state, f32, 0x1A0), FLD(g_hero_state, f32, 0x98)) < 1.5707964f)) {
                hero_l20_set_move_state_us2(0x8E, 1);
            } else if (FLD(g_hero_state, u8, 0x49C) >= 0xD) {
                hero_l20_set_move_state_us2(0x8D, 1);
            }
        }
        if ((FLD(g_hero_state, f32, 0x31C) > 2.0f) && (FLD(g_hero_state, u8, 0x49E) != 0) && (FLD(g_hero_state, s32, 0x1B8) >= 0x29)) {
            hero_l20_set_move_state_us2(0x8F, 1);
        }
        break;
    }
    case 0x8F:
        if (FLD(g_hero_state, s16, 0x34E) == 0) {
            if (FLD(g_hero_state, f32, 0x118) < -0.15f) {
                FLD(g_hero_state, f32, 0x118) = -0.15f;
            }
            if (FLD(g_hero_state, f32, 0xF8) < -0.15f) {
                FLD(g_hero_state, f32, 0xF8) = -0.15f;
            }
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l20_set_move_state_us2(0x91, 1);
            } else if (FLD(g_hero_state, f32, 0x24B8) > 0.5f) {
                if (FLD(g_hero_state, s16, 0x1E0) == 0) {
                    hero_l20_set_move_state_us2(0x8E, 1);
                } else {
                    hero_l20_set_move_state_us2(0x8D, 1);
                }
            } else {
                hero_l20_set_move_state_us2(0x8D, 1);
            }
        }
        break;
    case 0x94:
        if (FLD(g_hero_state, s32, 0x1B8) >= 0x12D) {
            hero_record_play_counters();
        }
        if (FLD(g_hero_state, u8, 0x149A) == 0) {
            if (FLD(g_hero_state, s16, 0x34E) != 0) {
                hero_l20_set_move_state_us2(0x8F, 1);
            } else {
                hero_l20_set_move_state_us2(0x8D, 1);
            }
        }
        break;
    case 0x8E:
        if (FLD(g_hero_state, u8, 0x149A) != 0) {
            hero_l20_set_move_state_us2(0x94, 1);
            break;
        }
        if (PadPressedWithin(0x40, 8, NULL) != 0) {
            hero_l20_set_move_state_us2(0x92, 1);
            break;
        }
        if ((FLD(FLD(g_hero_state, u8 *, 0x2290), s16, 0xAA) != 0xEE1) && (PadPressedWithin(0x80, 9, NULL) != 0)) {
            hero_l20_set_move_state_us2(0x93, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) >= 5) && ((FLD(g_hero_state, f32, 0x31C) > 0.8f) || (FLD(g_hero_state, f32, 0x320) > 0.8726647f))) {
            hero_l20_set_move_state_us2(0x8F, 1);
            break;
        }
        if ((FLD(g_hero_state, s16, 0x34E) == 0) && (FLD(g_hero_state, f32, 0x24B8) < 0.17f) && (FLD(g_hero_state, s16, 0x1454) == 0)) {
            hero_l20_set_move_state_us2(0x8D, 1);
        }
        break;
    case 0x90:
        if ((FLD(g_hero_state, s32, 0x1B8) >= 0x20) && (FLD(g_hero_state, s16, 0x34E) != 0) && (FLD(g_hero_state, f32, 0x31C) > 1.0f)) {
            hero_l20_set_move_state_us2(0x8F, 1);
            break;
        }
        if ((FLD(g_hero_state, s32, 0xC28) & 2) || (FLD(g_hero_state, s32, 0x1B8) >= 0x24)) {
            if (FLD(g_hero_state, s32, 0x24CC) <= 0) {
                hero_l20_set_move_state_us2(0x91, 1);
            } else {
                hero_l20_set_move_state_us2(0x8D, 0);
            }
        }
        break;
    case 0x1D:
        if ((FLD(g_hero_state, u8, 0x22B4) == 0) && ((FLD(g_hero_state, u8, 0x22BA) == 0) || (FLD(g_hero_state, u8, 0x22B5) != 0))) {
            if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                set_hero_animation(0xD, 0, 8.0f);
            } else {
                set_hero_animation(SelectHeroStateAnimation(1), 0, 8.0f);
            }
        }
        if (!(FLD(g_pad_state, s32, 0x1A0) & 4)) {
            if (FLD(g_hero_state, u32, 0x2294) == 0x1D) {
                s32 anim;
                hero_l20_set_move_state_us2(0, 0);
                anim = SelectHeroStateAnimation(1);
                if (FLD(FLD(g_hero_state, u8 *, 0x2290), u8, 0x43) != anim) {
                    set_hero_animation(anim, 0, 8.0f);
                }
            }
            g_hero_flag_cleared = 0;
        }
        break;
    case 0x1F:
        if ((FLD(g_hero_state, s32, 0x1220) != 0) && (FLD(g_hero_state, s32, 0xC2C) == 0) && (FLD(g_hero_state, f32, 0xC38) > 20.0f)) {
            hero_l20_set_move_state_us2(0, 0);
        }
        break;
    case 0x22:
        if (FLD(g_hero_state, f32, 0xC38) > 19.0f) {
            if (PadPressedWithin(0x40, 0xB, NULL) != 0) {
                if (FLD(g_pad_state, s32, 0x1A0) & 8) {
                    hero_choose_jump_or_roll_move();
                    break;
                }
                hero_l20_set_move_state_us2(7, 1);
                break;
            }
        }
        if (FLD(g_hero_state, f32, 0xC38) >= 21.0f) {
            hero_l20_set_move_state_us2(0, 0);
        }
        break;
    default:
        break;
    }
end:
    if (sp78 != FLD(g_hero_state, s32, 0x229C)) {
        hero_clear_tracked_slots();
    }
    temp_a0_31 = FLD(g_hero_state, s32, 0x22A0);
    if (((temp_a0_31 == 0x3C) && (FLD(g_hero_state, s32, 0x2294) != 0x3D)) || ((temp_a0_31 == 0x3D) && (FLD(g_hero_state, s32, 0x1854) != 0))) {
        hero_clear_target_flags();
    }
    if (sp7C != FLD(g_hero_state, s32, 0x2298)) {
        FLD(g_hero_state, s32, 0x1C0) = 0;
    }
    if (sp80 != FLD(sp74, u8, 0x43)) {
        FLD(g_hero_state, s32, 0x1C4) = 0;
    }
}
