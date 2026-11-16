#include "include_asm.h"

#include "common.h"
extern int g_spark_slot_pool MACRO_ADDR;
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern int FloatToInt(float), math_random_int_range(int, int);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_set_state(void *, int, int), anim_start_blended(void *, int, int, int);
typedef int TI128_00318340 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128_00318340 q[0x260]; } Hero_00318340;
extern u8 g_hero_state[];
extern char g_hero_position[];
extern u8 g_sound_state[];
extern char g_default_effect_vector[16] MACRO_ADDR;
extern char g_str_hover_enemy_debug[];
extern void STUB_printf(const char *, ...);
extern void gfx_register_overlay_draw_callback(void (*)(char *), char *);
extern int math_fast_float_d(void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(void *);
extern void SetDeathBits_us2(void *, int, int);
extern int math_random_int_below(int);
extern float moby_turn_toward_position(void *, void *, void *, float, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern float math_spring_float_to_goal(void *, float, void *, float, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern int IsPointInCuboid(void *, int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int math_is_value_within_step_us2(void *, float);
extern int flag_set_first_pending(void *);
extern int flag_is_third_pending_set(void *);
extern void *part_spawn_gravity_fade(void *, void *, int, u32, int, int, int, int, float, float, float);
extern void path_sample_position(void *, int, void *, void *, int, float);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void hover_enemy_update_body_group(char *);
extern void hover_enemy_draw_effects(char *);
extern void hover_enemy_tick_timers(char *);
extern int group_claim_lead_token(char *);
extern int group_pass_lead_token(char *);
extern int group_is_moby_member(unsigned char *);
extern int moby_is_target_outside_turn_limit(char *, float);
extern void moby_turn_toward_target(char *);
extern void *part_spawn_spinning_effect_moby(char *, void *, void *, int, int, float);
extern float vec_distance_xy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);
extern int math_fast_float_d(void *timer);
extern int flag_set_second_pending(char *);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void SetDeathBits_us2(void *, int, int);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern unsigned char g_sound_state[];
extern unsigned char g_hero_state[];
extern char *g_path_table[];
extern void moby_scale_owner_words_by_angles(float, float, char *, char *, float, char *);

/* A moby's per-frame update: pvars at moby+0x68, a switch on moby+0x95, a switch on the state at
   moby+0x20, then the sound-slot keep-alive on pvars+0x2C4. The template vector is MACRO_ADDR: retail
   schedules its address as one `la`, not a split %hi/%lo pair. func_L00_003BD7E0 is the level twin. */
void hover_enemy_update_us2(char *moby)
{
    f32 joint_pos[4] __attribute__((aligned(16)));
    f32 target_pos[4] __attribute__((aligned(16)));
    f32 direction[4] __attribute__((aligned(16)));
    f32 axis[4] __attribute__((aligned(16)));
    f32 to_target[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    char *follow_target, *shoot_target, *shoot_target_b;
    f32 *pos;
    s32 *path;
    int voice_id;
    int mode_a, mode_b, flags, state;
    float ground_height_a, ground_height_b, floor_height, height_b, above_ground_b, ground_height_c, above_ground_c, anim_pos_a, dot, anim_pos_b, anim_pos_c, spawn_x, spawn_y, spawn_z;

    if (((Hero_00318340 *)g_hero_state)->b[0x22B4] == 1)
        return;
    switch (*(u8 *)(moby + 0x95)) {
    case 0:
        if (*(s32 *)(vars + 0x2E0) != 0 && flag_is_third_pending_set(moby) == 0)
            break;
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        mode_a = *(s32 *)(vars + 0x34);
        if (mode_a == 1 && *(s32 *)(vars + 0x2A4) != 0) {
            if (math_fast_float_d(vars + 0x2D0) != 0) {
                moby_set_state(moby, 9, 3);
                if (*(u8 *)(moby + 0x43) != mode_a)
                    anim_start_blended(moby, 1, 0, 4);
            }
        } else if (*(s16 *)(vars + 0x286) != 0) {
            moby_set_state(moby, 8, 2);
            *(s16 *)(vars + 0x286) = 0;
            if (*(s16 *)(vars + 0x280) < 300)
                *(s16 *)(vars + 0x280) = math_random_int_range(0x1E0, 0x258);
        }
        break;
    case 2:
        if (flag_set_second_pending(moby) != 0) {
            moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
            *(f32 *)(moby + 0x48) = 1.0f;
        }
        mode_b = *(s32 *)(vars + 0x34);
        if (mode_b == 1 && *(s32 *)(vars + 0x2A4) != 0) {
            moby_set_state(moby, 9, 3);
            if (*(u8 *)(moby + 0x43) != mode_b)
                anim_start_blended(moby, 1, 0, 4);
        } else if (*(s16 *)(vars + 0x280) == 0) {
            moby_set_state(moby, 2, 0);
            if (*(u8 *)(moby + 0x43) != 2)
                anim_start_blended(moby, 2, 0, 10);
        }
        break;
    case 1:
        if (flag_set_second_pending(moby) != 0)
            moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
        if (*(s32 *)(vars + 0x34) == 1 && *(s32 *)(vars + 0x2A4) != 0) {
            if (math_fast_float_d(vars + 0x2D0) == 0)
                break;
        } else {
            if (*(s16 *)(vars + 0x286) == 0 || *(s32 *)(vars + 0x2A4) == 0)
                break;
            *(s16 *)(vars + 0x286) = 0;
        }
        moby_set_state(moby, 0xD, 3);
        if (*(u8 *)(moby + 0x43) != 0x19)
            anim_start_blended(moby, 0x19, 0, 4);
        break;
    case 3:
        if (flag_set_second_pending(moby) != 0) {
            moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            *(f32 *)(moby + 0x48) = 1.0f;
        }
        if (*(s32 *)(vars + 0x34) != 1 && *(u8 *)(moby + 0x20) != 0xD && *(u8 *)(moby + 0x20) != 0xC && *(u8 *)(moby + 0x20) != 0xF) {
            moby_set_state(moby, 8, 2);
            if (*(u8 *)(moby + 0x43) != 6)
                anim_start_blended(moby, 6, 0, 10);
            *(s16 *)(vars + 0x280) = math_random_int_range(0x244, 0x258);
            if (*(s32 *)(vars + 0x28C) != 0) {
                moby_set_state(moby, 3, 1);
                if (*(u8 *)(moby + 0x43) != 0xB)
                    anim_start_blended(moby, 0xB, 0, 0x14);
            }
        }
        break;
    case 4:
        if (flag_set_first_pending(moby) != 0)
            *(s16 *)(vars + 0x46) = 0x3C;
        flags = moby_dispatch_action_by_kind(moby, vars + 0x80);
        if ((flags & 1) || *(f32 *)(vars + 0x40) <= 0.0f) {
            part_spawn_explosion_with_sparks(moby, moby + 0x10, -1, 1.0f, 13.0f);
            SetDeathBits_us2(moby, 0, 3);
            moby_mark_spawned(moby);
            return;
        }
        if (flags & 2) {
            if (*(s32 *)(vars + 0x34) == 1) {
                moby_set_state(moby, 7, 3);
                if (*(u8 *)(moby + 0x43) != 7)
                    anim_start_blended(moby, 7, 0, 6);
            } else {
                moby_set_state(moby, 8, 2);
                if (*(u8 *)(moby + 0x43) != 6)
                    anim_start_blended(moby, 6, 0, 10);
                *(s16 *)(vars + 0x280) = math_random_int_range(0x244, 0x258);
            }
            if (*(s32 *)(vars + 0x2A4) != 1)
                *(s32 *)(vars + 0x2A4) = 1;
        }
        break;
    }

    switch (*(u8 *)(moby + 0x20)) {
    case 2:
        break;
    case 7:
        if (moby_is_target_outside_turn_limit(moby, 10.0f) != 0) {
            moby_turn_toward_target(moby);
        } else {
            moby_set_state(moby, 0xA, -1);
            if (*(u8 *)(moby + 0x43) != 0x1E)
                anim_start_blended(moby, 0x1E, 0, 6);
        }
        break;
    case 3:
        moby_scale_owner_words_by_angles(0.06981318f, 0.052359886f, moby, vars + 0x2A8, 0.013089972f, vars + 0x2AC);
        break;
    case 13:
        follow_target = *(char **)(vars + 0x30);
        *(s32 *)(vars + 0x2C0) += 1;
        if (follow_target != 0) {
            moby_turn_toward_position(moby, follow_target, vars + 0x29C, 0.001f, 0.01f, 0.1f);
            math_spring_float_to_goal(moby + 0xF4, 0.0f, vars + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            math_spring_float_to_goal(moby + 0xF0, 0.0f, vars + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            ground_height_a = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
            if (*(f32 *)(moby + 0x18) - ground_height_a > 0.05f) {
                *(f32 *)(moby + 0x18) -= ground_height_a * 0.00025f;
            } else {
                moby_set_state(moby, 6, -1);
                if (*(u8 *)(moby + 0x43) != 0xE)
                    anim_start_blended(moby, 0xE, 0, 3);
            }
            if (*(u8 *)(moby + 0x60) & 2) {
                moby_set_state(moby, 0xC, -1);
                if (*(u8 *)(moby + 0x43) != 0x1A)
                    anim_start_blended(moby, 0x1A, 0, 0xF);
            }
        }
        break;
    case 12:
        *(s32 *)(vars + 0x2C0) += 1;
        moby_turn_toward_target(moby);
        ground_height_b = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        height_b = *(f32 *)(moby + 0x18);
        floor_height = *(f32 *)(vars + 0x2DC);
        above_ground_b = height_b - ground_height_b;
        ground_height_b -= 3.0f;
        if (floor_height != -1.0f && height_b <= floor_height) {
            if (group_is_moby_member(moby) == 0) {
                moby_set_state(moby, 0x10, -1);
                if (*(u8 *)(moby + 0x43) != 0x1D)
                    anim_start_blended(moby, 0x1D, 0, 3);
            } else {
                *(s32 *)(vars + 0x354) = 0;
                group_claim_lead_token(moby);
                moby_set_state(moby, 0xE, -1);
            }
        } else if (above_ground_b > 0.05f) {
            math_step_value_toward_target(moby + 0x18, vars + 0x290, ground_height_b, 0.016666668f, 0.16333334f, 0.16666667f);
        } else {
            STUB_printf(g_str_hover_enemy_debug, *(s32 *)(vars + 0x2C0));
            moby_set_state(moby, 6, -1);
            if (*(u8 *)(moby + 0x43) != 0xE)
                anim_start_blended(moby, 0xE, 0, 3);
        }
        break;
    case 14:
        if (flag_set_first_pending(moby) != 0) {
            *(TI128_00318340 *)(vars + 0x360) = *(TI128_00318340 *)(moby + 0x10);
            if (*(s32 *)(vars + 0x350) != 0)
                *(f32 *)(vars + 0x368) = *(f32 *)(vars + 0x2DC) + math_random_float_range(4.0f, 7.0f);
            else
                *(f32 *)(vars + 0x368) = *(f32 *)(vars + 0x2DC) + math_random_float_range(-3.0f, 3.0f);
        }
        if (fast_vec_dist(moby + 0x10, vars + 0x360) < 0.05f) {
            *(s32 *)(vars + 0x354) = 0;
            moby_set_state(moby, 0x10, -1);
        }
        *(s32 *)(vars + 0x2C0) += 1;
        moby_turn_toward_target(moby);
        math_step_value_toward_target(moby + 0x18, vars + 0x290, *(f32 *)(vars + 0x368), 0.004166667f, 0.004166667f, 0.16666667f);
        break;
    case 4:
        if (*(u8 *)(moby + 0x60) & 2) {
            moby_set_state(moby, 5, -1);
            if (*(u8 *)(moby + 0x43) != 0xD)
                anim_start_blended(moby, 0xD, 0, 0xF);
        }
        break;
    case 5:
        if (*(char **)(vars + 0x30) != 0) {
            math_spring_float_to_goal(moby + 0xF4, 0.0f, vars + 0x2A0, 0.016666668f, 0.0f, 0.06666667f);
            euler_rotation_basis(moby + 0xC0, moby + 0xF0);
            moby_turn_toward_position(moby, *(char **)(vars + 0x30), vars + 0x29C, 0.001f, 0.01f, 0.1f);
            ground_height_c = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
            above_ground_c = *(f32 *)(moby + 0x18) - ground_height_c;
            ground_height_c -= 3.0f;
            if (above_ground_c > 0.05f) {
                math_step_value_toward_target(moby + 0x18, vars + 0x290, ground_height_c, 0.025000002f, 0.16333334f, 0.25f);
            } else {
                moby_set_state(moby, 6, -1);
                if (*(u8 *)(moby + 0x43) != 0xE)
                    anim_start_blended(moby, 0xE, 0, 3);
            }
        }
        break;
    case 6:
        if (*(u8 *)(moby + 0x60) & 2) {
            moby_set_state(moby, 0xA, 3);
            if (*(u8 *)(moby + 0x43) != 0x1E)
                anim_start_blended(moby, 0x1E, 0, 6);
            *(f32 *)(moby + 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        }
        break;
    case 9:
        if (*(u8 *)(moby + 0x60) & 2) {
            moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
            moby_set_state(moby, 7, -1);
            if (*(u8 *)(moby + 0x43) != 7)
                anim_start_blended(moby, 7, 0, 6);
        }
        break;
    case 10:
        if (*(u8 *)(moby + 0x60) & 2) {
            if (moby_is_target_outside_turn_limit(moby, 10.0f) != 0) {
                moby_set_state(moby, 7, -1);
                if (*(u8 *)(moby + 0x43) != 7)
                    anim_start_blended(moby, 7, 0, 6);
            } else if (((Hero_00318340 *)g_hero_state)->ptr[0x249C / 4] == (u8 *)moby || math_random_int_below(6) == 1) {
                moby_set_state(moby, 0xB, -1);
                if (*(u8 *)(moby + 0x43) != 0x10)
                    anim_start_blended(moby, 0x10, 0, 7);
            }
        }
        anim_pos_a = moby_get_anim_value(moby);
        if (math_is_value_within_step_us2(moby, 17.0f) != 0) {
            moby_transform_joint_to_world(moby, 4, joint_pos);
            shoot_target = *(char **)(vars + 0x30);
            if (shoot_target == (char *)((Hero_00318340 *)g_hero_state)->ptr[0x2290 / 4]) {
                qcopy(target_pos, &((Hero_00318340 *)g_hero_state)->q[0xD0 / 16]);
                pos = target_pos;
            } else {
                if (shoot_target == 0)
                    break;
                qcopy(target_pos, shoot_target + 0x10);
                pos = target_pos;
                target_pos[2] += *(f32 *)(shoot_target + 0xC) * 0.0009765625f;
            }
            if (moby_is_target_outside_turn_limit(moby, 10.0f) != 0) {
                FastVecSub(to_target, pos, joint_pos);
                qcopy(direction, g_default_effect_vector);
                direction[0] = 1.0f;
                matrix_mul_vec3(direction, direction, moby + 0xC0);
                FastVecCross(axis, direction, to_target);
                dot = FastVecDot(direction, to_target);
                if (dot > 0.0f)
                    math_apply_axis_rotation_to_quat(direction, direction, axis, -0.17453294f);
                else
                    math_apply_axis_rotation_to_quat(direction, direction, axis, 0.17453294f);
            } else {
                FastVecSub(direction, pos, joint_pos);
            }
            vec_scale_to_length(direction, direction, 0.33333334f);
            part_spawn_spinning_effect_moby(moby, direction, joint_pos, 0, 0, *(u8 *)(vars + 0x54));
        } else if (anim_pos_a < 17.0f && *(u8 *)(moby + 0x43) == 0x1E) {
            moby_transform_joint_to_world(moby, 4, joint_pos);
        }
        break;
    case 11:
        if (*(u8 *)(moby + 0x60) & 2) {
            if (vec_distance_xy(moby + 0x10, g_hero_position) > 4.0f) {
                moby_set_controller_speed_limits(moby, 0.0033333334f, 0.10000001f, 0.001163553f, 0.10471977f);
                moby_set_state(moby, 0xA, -1);
                if (*(u8 *)(moby + 0x43) != 0x1E)
                    anim_start_blended(moby, 0x1E, 0, 6);
            } else {
                moby_set_controller_speed_limits(moby, 0.0022222223f, 0.06666667f, 0.001163553f, 0.10471977f);
                moby_set_state(moby, 0xA, -1);
                if (*(u8 *)(moby + 0x43) != 0x1E)
                    anim_start_blended(moby, 0x1E, 0, 6);
            }
        }
        anim_pos_b = moby_get_anim_value(moby);
        if (*(u8 *)(moby + 0x42) == 0x10 && (anim_pos_b <= 5.0f || (anim_pos_b >= 12.0f && anim_pos_b <= 15.0f)))
            *(s32 *)(vars + 0x2C8) = 1;
        else
            *(s32 *)(vars + 0x2C8) = 0;
        break;
    case 15:
        if (flag_set_first_pending(moby) != 0) {
            *(f32 *)(vars + 0x374) = 0.0f;
            *(f32 *)(vars + 0x378) = 0.0f;
        }
        if (*(s32 *)(vars + 0x37C) == 0) {
            if (IsPointInCuboid(g_hero_position, *(s32 *)(vars + 0x35C)) != 0)
                *(s32 *)(vars + 0x37C) = 1;
        } else {
            path = (s32 *)g_path_table[*(s32 *)(vars + 0x370)];
            math_step_value_toward_target(vars + 0x374, vars + 0x378, (f32)(*path - 1), 0.013888889f, 0.0013888889f, 0.33333334f);
            path_sample_position(path, 0, moby + 0x10, moby + 0xF0, 0, *(f32 *)(vars + 0x374));
            euler_rotation_basis(moby + 0xC0, moby + 0xF0);
            if ((f32)(*path - 1) <= *(f32 *)(vars + 0x374))
                moby_set_state(moby, 0xA, 3);
        }
        break;
    case 16:
        if ((*(u8 *)(moby + 0x60) & 2) && group_is_moby_member(moby) != 0) {
            *(s32 *)(vars + 0x354) += 1;
            if (*(s32 *)(vars + 0x350) != 0) {
                if (*(s32 *)(vars + 0x354) >= 3 && group_pass_lead_token(moby) != 0) {
                    moby_set_state(moby, 0xE, -1);
                    if (*(u8 *)(moby + 0x43) != 0x1A)
                        anim_start_blended(moby, 0x1A, 0, 0xF);
                }
            } else {
                moby_set_state(moby, 0xE, -1);
                if (*(u8 *)(moby + 0x43) != 0x1A)
                    anim_start_blended(moby, 0x1A, 0, 0xF);
            }
        }
        anim_pos_c = moby_get_anim_value(moby);
        if (math_is_value_within_step_us2(moby, 16.0f) != 0) {
            moby_transform_joint_to_world(moby, 4, joint_pos);
            shoot_target_b = *(char **)(vars + 0x30);
            if (shoot_target_b == (char *)((Hero_00318340 *)g_hero_state)->ptr[0x2290 / 4]) {
                qcopy(target_pos, &((Hero_00318340 *)g_hero_state)->q[0xD0 / 16]);
                pos = target_pos;
            } else {
                if (shoot_target_b == 0)
                    break;
                qcopy(target_pos, shoot_target_b + 0x10);
                pos = target_pos;
                target_pos[2] += *(f32 *)(shoot_target_b + 0xC) * 0.0009765625f;
            }
            FastVecSub(direction, pos, joint_pos);
            vec_scale_to_length(direction, direction, 0.33333334f);
            PlayMobySound(0xB, 0, moby);
            part_spawn_spinning_effect_moby(moby, direction, joint_pos, 0, 0, *(u8 *)(vars + 0x54));
        } else if (anim_pos_c < 17.0f && *(u8 *)(moby + 0x43) == 0x1E) {
            moby_transform_joint_to_world(moby, 4, joint_pos);
            spawn_x = math_random_float_range(1.0f, 1.5f) * 210000.0f;
            spawn_y = math_random_float_range(0.2f, 0.4f) * 210000.0f;
            spawn_z = math_random_signed_float_range(0.0f, 0.1f);
            part_spawn_gravity_fade(joint_pos, g_default_effect_vector, 4, 0x808080, 9, 0x4F, 0, 0, spawn_x, spawn_y, spawn_z);
        }
        break;
    }

    state = *(u8 *)(moby + 0x20);
    if (state == 12 || state == 13 || state == 14 || state == 16) {
        u8 *voice_a;
        voice_a = *(s32 *)(vars + 0x2C4) * 0x70 + g_sound_state;
        if (*(char **)(voice_a + 0x88) != moby || voice_a[0x74] == 0)
            *(s32 *)(vars + 0x2C4) = PlayMobySound(10, 4, moby);
    } else {
        u8 *voice_b;
        voice_id = *(s32 *)(vars + 0x2C4);
        if (voice_id != -1) {
            voice_b = voice_id * 0x70 + g_sound_state;
            if (*(char **)(voice_b + 0x88) == moby && voice_b[0x74] != 0)
                snd_stop_voice(voice_id);
        }
        *(s32 *)(vars + 0x2C4) = -1;
    }
    hover_enemy_update_body_group(moby);
    hover_enemy_tick_timers(moby);
    gfx_register_overlay_draw_callback(hover_enemy_draw_effects, moby);
}
