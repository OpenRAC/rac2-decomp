#include "names.h"
/* EE argument banks are independent; the interleaved call declaration agrees
 * with the matched motion callers and preserves each bank's argument order. */
#include "common.h"

typedef struct { int q __attribute__((mode(TI))); } Vec4;

extern int g_current_map_index MACRO_ADDR;
extern u8 g_hero_frame_flag[];
extern u8 g_sound_state[];
typedef union { u8 b[0x1000]; s16 h[0x800]; u16 uh[0x800]; s32 i[0x400]; u32 ui[0x400]; f32 f[0x400]; u8 *p[0x400]; } View;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *p[0x980]; } Hero;
extern u8 g_hero_state[];
extern u8 g_hero_position[];
extern u8 g_subtitle_history[];
extern u8 g_moby_group_flags[];
extern u8 g_moby_nibble_table[];
extern u8 g_explosion_effect_desc[] MACRO_ADDR;
extern s32 g_hero_frozen_flag MACRO_ADDR;
extern float g_receiver_aim_turn_rate __attribute__((sda));
extern float g_receiver_aim_move_speed __attribute__((sda));
extern s32 g_enemy_timer_min __attribute__((sda));
extern s32 g_enemy_timer_max __attribute__((sda));
extern u16 g_receiver_timer_reset __attribute__((sda));
extern s32 g_receiver_delay_min __attribute__((sda));
extern s32 g_receiver_delay_max __attribute__((sda));
extern s32 g_receiver_delay_limit __attribute__((sda));
extern s32 g_receiver_targeting_frames __attribute__((sda));
extern float g_receiver_targeting_distance __attribute__((sda));
extern float g_receiver_offset_height __attribute__((sda));
extern float g_receiver_sway_angle __attribute__((sda));
extern s32 g_door_trigger_flags[] __attribute__((sda));
extern u8 g_map_flags_table[] MACRO_ADDR;
extern s32 g_moby_l18_table MACRO_ADDR;
extern Vec4 g_camera_l18_position[];
extern u8 g_trigger_flag_tables[][0x464];
extern u8 g_trigger_l18_flags[][0x464];
extern u8 g_receiver_flag_buffer[];

extern s32 FastDecTimer(void *);
extern void mem_clear(void *, u32, s32);
extern void add_vectors(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float IntToFloat(s32);
extern s32 subtitle_request_voice_line(s32, s32);
extern void level_store_value_pair(s32, void *);
extern void moby_mark_spawned(void *);
extern void SetDeathBits(void *, s32, s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern void moby_set_state(void *, s32, s32);
extern s32 math_random_int_range(s32, s32);
extern float math_approach_target_with_direction_mode(void *out, float, void *in, s32, float, float, float);
extern void gfx_update_color_fade(void *, void *);
extern float math_wrap_angle_to_pi(float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, s32, s32, s32, float, float,
                          float, float, s32, float, s32, s32, s32, s32, s32);
extern s32 moby_is_in_selected_zone(void *);
extern int TryClaimNotice(s32, s32, s32);
extern s32 moby_dispatch_action_by_kind(void *, void *);
extern s32 flag_set_second_pending(void *);
extern s32 moby_step_at_own_position(void *);
extern int moby_step_at_own_position_factor(void *, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void snd_stop_voice(s32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void cam_set_mode_state(s32);
extern s32 func_001163B0(void);
extern s32 coll_point_inside_region(void *, s32);
extern s32 moby_fuse_linked_objects(void *, void *, void *, void *, s32);
extern int moby_aim_move_record_at_target(void *, void *, float, float);
extern s32 hero_adjust_jump_speed_to_target(void *, float, float, float);
extern void hero_attach_to_object(s32, s32, void *);
extern void hero_detach_from_object(s32);
extern s32 moby_run_slot_handler(void *, s32, s32);
extern float path_find_best_point_by_id(void *, void *, void *, s32, float);
extern s32 hud_draw_timer_bar(void);
extern void moby_reset_color_grey(void *);
extern s32 shooter_is_enemy_alive(void *);
extern s32 moby_is_target_in_sight(void *, void *);
extern void moby_start_or_forward_anim(void *, s32, s32, float);
extern void moby_release_shared_resource(void *);
extern void moby_acquire_shared_resource(void *);
extern s32 moby_set_anim(void *, s32, s32);
extern void moby_wake_linked_enemy(void *);
extern void shooter_flag_group(void *, s32);
extern void receiver_bot_update_targeting(void *);
extern void enemy_tick_timers(void *);
extern s32 enemy_get_kind_index(void *);
extern int shooter_update_ranged_attack(void *);
extern void receiver_bot_move_toward_target(void *);

/* Runs every frame for the Receiver Bot style enemy. It watches the player, picks its next move, handles being grabbed and carried, and finally hands over to the shared per-frame tick. */
void receiver_bot_update(u8 *moby) {
    float camera_pos[4] __attribute__((aligned(16)));
    float dir_vec[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float offset_vec[4] __attribute__((aligned(16)));
    float temp_vec[4] __attribute__((aligned(16)));
    u8 *vars;
    s32 enemy_kind;

    if (moby_is_in_selected_zone(moby + 0x10) == 0)
        return;
    vars = ((View *)moby)->p[0x68 / 4];
    receiver_bot_update_targeting(moby);
    switch (((View *)moby)->b[0x95]) {
    case 1:
        if (((View *)moby)->b[0x42] == 0xD)
            ((View *)moby)->i[0x48 / 4] = 0;
        break;
    case 2:
        if (!(((View *)vars)->b[0x399] & 1) && (((View *)vars)->i[0x234 / 4] == 1 || ((View *)vars)->h[0x390 / 2] != 0)
            && (shooter_is_enemy_alive(*(void **)(vars + 0x230)) == 0
                || moby_is_target_in_sight(moby, *(void **)(vars + 0x230)) != 0)) {
            shooter_flag_group(moby, ((View *)moby)->b[0x21]);
            ((View *)vars)->i[0x37C / 4] = ((View *)vars)->i[0x364 / 4];
            ((View *)vars)->i[0x13C / 4] = ((View *)vars)->i[0x384 / 4];
            ((View *)vars)->h[0x392 / 2] = ((View *)vars)->b[0x398];
            if (((View *)vars)->i[0x368 / 4] != -1
                && (((View *)vars)->i[0x3A4 / 4] == -1 || coll_point_inside_region(vars + 0x220, ((View *)vars)->i[0x3A4 / 4]) == 0)) {
                if (**(s32 **)(vars + 0x3A8) == 0 && **(s32 **)(vars + 0x3AC) < g_receiver_delay_limit) {
                    **(s32 **)(vars + 0x3A8) = math_random_int_range(g_receiver_delay_min, g_receiver_delay_max);
                    moby_acquire_shared_resource(moby);
                    moby_set_state(moby, 1, 4);
                }
            } else {
                moby_set_anim(moby, ((View *)vars)->i[0x370 / 4], -1);
                moby_set_state(moby, 1, 3);
            }
        }
        break;
    case 3:
        if (((View *)vars)->h[0x392 / 2] == 0) {
            moby_start_or_forward_anim(moby, 3, 0, 5.0f);
            if (((View *)vars)->i[0x370 / 4] != -1) {
                moby_set_state(moby, 3, 5);
            } else {
                moby_set_anim(moby, ((View *)vars)->i[0x374 / 4], -1);
                ((View *)vars)->h[0x390 / 2] = math_random_int_range(g_enemy_timer_min, g_enemy_timer_max);
                moby_set_state(moby, 3, 6);
            }
        }
        break;
    case 4:
        if (((View *)vars)->h[0x392 / 2] == 0) {
            ((View *)moby)->b[0x31] = 1;
            ((View *)moby)->uh[0x34 / 2] &= ~1;
            path_find_best_point_by_id(camera_pos, moby + 0x10, g_hero_position, ((View *)vars)->i[0x368 / 4], 0.0f);
            moby_start_or_forward_anim(moby, 6, 0, 5.0f);
            moby_aim_move_record_at_target(moby, camera_pos, g_receiver_aim_move_speed * 0.0166666675f, g_receiver_aim_turn_rate * 0.000277777785f);
            moby_set_state(moby, 5, 10);
        }
        break;
    case 5:
        if (((View *)vars)->i[0x234 / 4] == 1 && ((View *)vars)->h[0x390 / 2] == 0)
            ((View *)vars)->h[0x390 / 2] = math_random_int_range(g_enemy_timer_min, g_enemy_timer_max);
        break;
    case 6:
        if ((((View *)vars)->i[0x234 / 4] != 1 && ((View *)vars)->h[0x390 / 2] == 0)
            || (((View *)vars)->b[0x3B2] != 0 && ((View *)vars)->b[0x3B3] == 0)
            || (((View *)vars)->b[0x3B3] != 0 && (((View *)vars)->p[0x230 / 4])[0xBC] == 0)) {
            ((View *)vars)->h[0x390 / 2] = 0;
            moby_start_or_forward_anim(moby, (func_001163B0() & 1) | 4, 0, 10.0f);
            moby_set_state(moby, 2, 2);
        } else if (((View *)vars)->b[0x3B0] == 0 && ((View *)vars)->i[0x368 / 4] != -1 && ((View *)vars)->i[0x3A4 / 4] != -1
                   && coll_point_inside_region(vars + 0x220, ((View *)vars)->i[0x3A4 / 4]) == 0
                   && **(s32 **)(vars + 0x3A8) == 0 && **(s32 **)(vars + 0x3AC) < g_receiver_delay_limit) {
            **(s32 **)(vars + 0x3A8) = math_random_int_range(g_receiver_delay_min, g_receiver_delay_max);
            moby_acquire_shared_resource(moby);
            moby_set_state(moby, 0, 4);
        }
        break;
    case 9: {
        s32 hit_flags = moby_dispatch_action_by_kind(moby, vars + 0x50);

        if (hit_flags & 1) {
            SetDeathBits(moby, 0, 3);
            moby_set_state(moby, 12, -1);
        } else if (hit_flags & 2) {
            ((View *)vars)->h[0x390 / 2] = math_random_int_range(g_enemy_timer_min, g_enemy_timer_max);
            shooter_flag_group(moby, ((View *)moby)->b[0x21]);
            if (((View *)moby)->b[0xBC] == 1) {
                moby_start_or_forward_anim(moby, 13, 0, 10.0f);
                moby_set_state(moby, 7, 8);
            } else {
                moby_start_or_forward_anim(moby, (func_001163B0() & 1) | 4, 0, 10.0f);
                moby_set_state(moby, 4, 6);
            }
        }
        break;
    }
    case 11: {
        s32 link_index;
        u8 *linked;

        ((View *)vars)->f[0x100 / 4] = 0.699999988f;
        link_index = ((View *)vars)->i[0x3B4 / 4];
        if (link_index != -1 && (linked = (u8 *)((link_index << 8) + g_moby_l18_table), *(s16 *)(linked + 0xAA) == 0x114D /* moby class 4429 */)
            && linked[0x20] != 0xFE && linked[0x20] != 0xFD) {
            if (linked[0xBC] == 0) {
                ((View *)moby)->b[0x23] = 0x80;
                ((View *)moby)->f[0x2C / 4] = *(float *)(((View *)moby)->p[0x24 / 4] + 0x24);
                ((View *)moby)->b[0x31] = 1;
                ((View *)moby)->uh[0x34 / 2] &= ~1;
                moby_set_state(moby, 0, 12);
            }
        } else {
            ((View *)moby)->b[0x31] = 1;
            ((View *)moby)->uh[0x34 / 2] &= ~1;
            moby_fuse_linked_objects(moby, moby + 0x10, moby + 0xF0, 0, 0);
            moby_set_state(moby, 0, 14);
        }
        break;
    }
    case 12: {
        u8 *linked;

        *(Vec4 *)(moby + 0x10) = *(Vec4 *)((u8 *)((((View *)vars)->i[0x3B4 / 4] << 8) + g_moby_l18_table) + 0x10);
        linked = (u8 *)((((View *)vars)->i[0x3B4 / 4] << 8) + g_moby_l18_table);
        if (linked[0xBC] == 2) {
            if (((View *)moby)->b[0x43] != 2)
                anim_start_blended(moby, 2, 0, 10);
            moby_set_state(moby, 4, 13);
        }
        break;
    }
    case 13:
        if (((u8 *)((((View *)vars)->i[0x3B4 / 4] << 8) + g_moby_l18_table))[0xBC] == 3) {
            u8 *link = ((View *)moby)->p[0x24 / 4];

            ((View *)moby)->b[0x30] = ((View *)vars)->b[0x3E0];
            ((View *)moby)->i[0x98 / 4] = *(s32 *)(link + 0x10);
            ((View *)moby)->uh[0x34 / 2] |= 0x1000;
            ((View *)moby)->f[0x2C / 4] = *(float *)(link + 0x24);
            ((View *)vars)->h[0x392 / 2] = 0;
            if (((View *)moby)->h[0xAA / 2] == 0xED4 /* moby class 3796 */)
                ((View *)vars)->f[0x100 / 4] = 1.0f;
            if (((View *)moby)->h[0xAA / 2] == MOBY_CLASS_RECEIVER_BOT)
                ((View *)vars)->f[0x100 / 4] = 1.10000002f;
            moby_set_state(moby, 2, 2);
        }
        break;
    case 14: {
        u8 *link = ((View *)moby)->p[0x24 / 4];

        ((View *)moby)->b[0x23] = 0x80;
        if (*(float *)(link + 0x24) <= ((View *)moby)->f[0x2C / 4]) {
            ((View *)moby)->b[0x30] = ((View *)vars)->b[0x3E0];
            ((View *)moby)->i[0x98 / 4] = *(s32 *)(link + 0x10);
            ((View *)moby)->uh[0x34 / 2] |= 0x1000;
            ((View *)moby)->f[0x2C / 4] = *(float *)(link + 0x24);
            if (((View *)moby)->h[0xAA / 2] == 0xED4 /* moby class 3796 */)
                ((View *)vars)->f[0x100 / 4] = 1.0f;
            if (((View *)moby)->h[0xAA / 2] == MOBY_CLASS_RECEIVER_BOT)
                ((View *)vars)->f[0x100 / 4] = 1.10000002f;
            if (((View *)vars)->b[0x3E8] != 0) {
                if (((View *)moby)->b[0x43] != 13)
                    anim_start_blended(moby, 13, 0, 10);
                moby_set_state(moby, 0, 1);
            } else {
                ((View *)vars)->h[0x392 / 2] = 0;
                moby_set_state(moby, 2, 2);
            }
        }
        break;
    }
    case 7: {
        s32 effect_index;
        float saved_rot;
        float blend;

        TryClaimNotice(6, 0, 20);
        if (flag_set_second_pending(moby) != 0)
            snd_play_from_class_bank(6, 0, moby, MOBY_CLASS_RECEIVER_BOT);
        if (((View *)vars)->i[0x3F0 / 4] != -1) {
            u8 *effect = g_sound_state + ((View *)vars)->i[0x3F0 / 4] * 0x70;
            if (*(u8 **)(effect + 0x88) == moby && effect[0x74] != 0)
                goto have;
        }
        ((View *)vars)->i[0x3F0 / 4] = snd_play_from_class_bank(9, 4, moby, MOBY_CLASS_RECEIVER_BOT);
    have:
        gfx_update_color_fade(moby, vars + 0x50);
        math_approach_target_with_direction_mode(moby + 0xF8,
                      mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((View *)moby)->f[0x10 / 4],
                                    ((Hero *)g_hero_state)->f[0x84 / 4] - ((View *)moby)->f[0x14 / 4]),
                      vars + 0x1B4, 0, ((View *)vars)->f[0x114 / 4], ((View *)vars)->f[0x118 / 4], ((View *)vars)->f[0x11C / 4]);
        g_door_trigger_flags[1] = 1;
        qcopy(camera_pos, g_camera_l18_position);
        ((Hero *)g_hero_state)->h[0x1DC / 2] = 5;
        ((Hero *)g_hero_state)->h[0x1E0 / 2] = 10;
        if (FastDecTimer(vars + 0x396) != 0) {
            level_store_value_pair(0, hud_draw_timer_bar);
            ((View *)vars)->uh[0x3BC / 2] = ((View *)vars)->uh[0x3BE / 2];
            saved_rot = ((View *)moby)->f[0xF8 / 4];
            if (((Hero *)g_hero_state)->b[0x22B4] == 4) {
                if (g_current_map_index == 0x14)
                    g_hero_frame_flag[0] = 1;
                hero_detach_from_object(1);
            }
            moby_reset_color_grey(moby);
            ((View *)moby)->b[0xBC] = 1;
            ((View *)vars)->i[0x13C / 4] = -1;
            ((View *)vars)->h[0x392 / 2] = 30;
            mem_clear(g_receiver_flag_buffer, 0, 0x50);
            hero_attach_to_object(4, 0x8D, moby);
            ((Hero *)g_hero_state)->f[0x98 / 4] = saved_rot;
            ((View *)moby)->f[0xF8 / 4] = saved_rot;
            g_door_trigger_flags[1] = 0;
            if (g_current_map_index == 0x13) {
                if (((View *)g_subtitle_history)->uh[0x504 / 2] == 0)
                    subtitle_request_voice_line(0xA14, 0x6B);
                else
                    ((View *)g_subtitle_history)->uh[0x504 / 2] = 0xFFFF;
            }
            g_hero_frozen_flag = 0;
            moby_set_state(moby, 7, 8);
            effect_index = ((View *)vars)->i[0x3F0 / 4];
            if (effect_index != -1) {
                u8 *effect = g_sound_state + effect_index * 0x70;
                if (*(u8 **)(effect + 0x88) == moby && effect[0x74] != 0)
                    snd_stop_voice(effect_index);
            }
            ((View *)vars)->i[0x3F0 / 4] = -1;
        }
        blend = 1.0f - IntToFloat(((View *)vars)->h[0x396 / 2]) / (float)g_receiver_targeting_frames;
        if (blend > 1.0f)
            blend = 1.0f;
        else if (blend < 0.0f)
            blend = 0.0f;
        FastVecSub(temp_vec, g_hero_position, moby + 0x10);
        *(Vec4 *)offset_vec = *(Vec4 *)temp_vec;
        offset_vec[2] = 0.0f;
        vec_scale_to_length(offset_vec, offset_vec, g_receiver_targeting_distance);
        add_vectors(temp_vec, offset_vec, moby + 0x10);
        offset_vec[2] += g_receiver_offset_height;
        FastVecSub(temp_vec, camera_pos, offset_vec);
        *(Vec4 *)dir_vec = *(Vec4 *)temp_vec;
        vec_scale_to_length(dir_vec, dir_vec, ((View *)vars)->f[0x3B8 / 4] * IntToFloat(((View *)vars)->h[0x396 / 2]));
        add_vectors(temp_vec, dir_vec, offset_vec);
        angles[2] = mat_fast_helper_a(((View *)moby)->f[0x10 / 4] - dir_vec[0], ((View *)moby)->f[0x14 / 4] - dir_vec[1]);
        angles[1] = -mat_fast_helper_a(vec_distance_xy(dir_vec, moby + 0x10), ((View *)moby)->f[0x18 / 4] - dir_vec[2]);
        angles[0] = g_receiver_sway_angle * (math_fast_sin_or_cos_b(math_wrap_angle_to_pi(blend * 6.28318548f)) * 0.0174532942f);
        object_copy_vector_to_selected(dir_vec);
        cam_set_state_rotation(angles);
        if (((View *)moby)->b[0x95] == 8)
            cam_set_mode_state(1);
        break;
    }
    case 8:
        TryClaimNotice(6, 0, 20);
        if ((((Hero *)g_hero_state)->b[0x22B4] != 4 || ((Hero *)g_hero_state)->p[0x2290 / 4] != moby) && ((View *)vars)->h[0x392 / 2] == 0) {
            if (((Hero *)g_hero_state)->b[0x22B4] != 4)
                level_store_value_pair(0, 0);
            g_hero_frozen_flag = 0;
            ((View *)vars)->i[0x13C / 4] = ((View *)vars)->i[0x384 / 4];
            ((View *)vars)->i[0x37C / 4] = ((View *)vars)->i[0x360 / 4];
            ((View *)vars)->i[0x38C / 4] = -1;
            ((View *)moby)->b[0xBC] = 0;
            moby_set_controller_speed_limits(moby, ((View *)vars)->f[0x3C4 / 4] * 0.000277777785f, ((View *)vars)->f[0x3C0 / 4] * 0.0166666675f,
                          ((View *)vars)->f[0x3D4 / 4] * 4.84813745e-06f, ((View *)vars)->f[0x3D0 / 4] * 0.000290888245f);
            ((View *)moby)->uh[0x34 / 2] &= 0xFFBE;
            enemy_kind = enemy_get_kind_index(moby);
            SpawnExplosionEffects(moby, g_explosion_effect_desc, 0, 2.0f, (float)((View *)vars)->b[0x35], 5, 2, 9, 6.0f, 4.0f, 9.0f, 1.10000002f,
                          enemy_kind, 0.0f, 1, 1, -2, 0, 0x850001);
            moby_set_state(moby, 11, -1);
        }
        break;
    }

    switch (((View *)moby)->b[0x20]) {
    case 1:
        moby_step_at_own_position_factor(moby, mat_fast_helper_a(((View *)vars)->f[0x220 / 4] - ((View *)moby)->f[0x10 / 4],
                                        ((View *)vars)->f[0x224 / 4] - ((View *)moby)->f[0x14 / 4]));
        break;
    case 2:
        moby_step_at_own_position(moby);
        if (((View *)vars)->h[0x392 / 2] == 0) {
            ((View *)vars)->h[0x392 / 2] = g_receiver_timer_reset;
            moby_start_or_forward_anim(moby, 2, 0, 10.0f);
            moby_set_state(moby, 4, -1);
        }
        break;
    case 3:
        math_approach_target_with_direction_mode(moby + 0xF8,
                      mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((View *)moby)->f[0x10 / 4],
                                    ((Hero *)g_hero_state)->f[0x84 / 4] - ((View *)moby)->f[0x14 / 4]),
                      vars + 0x1B4, 0, ((View *)vars)->f[0x114 / 4], ((View *)vars)->f[0x118 / 4], ((View *)vars)->f[0x11C / 4]);
        if (((View *)moby)->b[0x60] & 2) {
            moby_start_or_forward_anim(moby, 2, 0, 10.0f);
            moby_set_state(moby, 4, -1);
        }
        break;
    case 4:
        receiver_bot_move_toward_target(moby);
        break;
    case 5:
        if (hero_adjust_jump_speed_to_target(moby, 7.0f, 32.0f, 37.0f) != 0) {
            if (moby_run_slot_handler(moby + 0x10, ((View *)vars)->i[0x380 / 4], 0) != 0) {
                ((View *)vars)->h[0x392 / 2] = 0;
                moby_set_state(moby, 0, 4);
            } else {
                s32 path_index;

                moby_start_or_forward_anim(moby, 2, 0, 10.0f);
                path_index = ((View *)vars)->i[0x370 / 4];
                if (path_index != -1) {
                    moby_set_anim(moby, path_index, -1);
                    moby_set_state(moby, 4, 5);
                } else {
                    if (((View *)vars)->i[0x374 / 4] != -1)
                        moby_set_anim(moby, ((View *)vars)->i[0x374 / 4], -1);
                    else
                        ((View *)vars)->i[0x38C / 4] = -1;
                    moby_set_state(moby, 4, 6);
                }
            }
        }
        break;
    case 6:
        shooter_update_ranged_attack(moby);
        break;
    case 12:
        enemy_kind = enemy_get_kind_index(moby);
        SpawnExplosionEffects(moby, g_explosion_effect_desc, 0, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f,
                      enemy_kind, 15.0f, 1, 1, -1, 0, 0x810001);
    case 11: {
        u16 slot_bits;
        u8 *unused_ptr;
        u8 state_flags;

        moby_release_shared_resource(moby);
        slot_bits = ((View *)moby)->uh[0xB2 / 2];
        if (slot_bits & 1) {
            u8 *slot_flags = g_moby_nibble_table + (((s16)slot_bits >> 1) + (g_current_map_index << 10));
            if (((*slot_flags >> 4) & 7) != 7)
                *slot_flags += 0x10;
        } else {
            u8 *slot_flags = g_moby_nibble_table + (((s16)slot_bits >> 1) + (g_current_map_index << 10));
            if ((*slot_flags & 7) != 7)
                *slot_flags += 1;
        }
        g_trigger_flag_tables[1][((View *)moby)->h[0xB2 / 2]] = ((View *)moby)->b[0xB0] + 2;
        if (((View *)moby)->b[0xB0] == 0xFF || (!(g_map_flags_table[((View *)moby)->b[0xB0]] & 0x80) && (g_moby_group_flags[((View *)moby)->b[0xB0] + (g_current_map_index << 4)] & 0x80)))
            g_trigger_l18_flags[1][((View *)moby)->h[0xB2 / 2]] = ((View *)moby)->b[0xB0] + 2;
        state_flags = ((View *)vars)->b[0x3B1];
        if (state_flags != 0 && state_flags != 0xFE
            && (((View *)moby)->b[0xB0] == 0xFF || !(g_moby_group_flags[((View *)moby)->b[0xB0] + (g_current_map_index << 4)] & 0x80))) {
            moby_wake_linked_enemy(moby);
        } else {
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    }
    enemy_tick_timers(moby);
}
