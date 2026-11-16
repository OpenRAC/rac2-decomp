#include "names.h"
/* func_US2_L20_00441AD8, the USA v2.00 copy of func_L20_00440598: the same C, where the two text ids
   0x325E and 0x3210 become 0x30F4 and 0x30A6, and state 5's spawn is guarded by a test of the saved
   object pointer against the word after D_L20_001B2F9C (the object table's base). */
#include "common.h"
extern int math_fast_float_d(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern f32 FastDiffRots(f32, f32);
extern void menu_set_size_limits(int, int);
extern void settings_store_four(int, int, int, int);
extern s32 req_push_queue(u8 *, s32);
extern s32 req_launch_queued(u8 *);
extern char *GetLocalizedString(int);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(char *);
extern void SetDeathBits_us2(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float coll_probe_ground_height_below(void *, int, float);
extern int coll_sweep_from_object(void *, void *, s32, s32, s32, s32, f32, f32, f32);
extern float ApproachValue(float *, float, float);
extern void StepAngleTowardTarget(float *, int, f32, f32);
extern void vec_add_random_offset(float *, float);
extern int IsPointInCuboid(void *, int);
extern s32 math_is_value_within_step_us2(u8 *, f32);
extern int flag_set_first_pending(u8 *);
extern int request_begin_slot(int, int, int, int, int);
extern void part_spawn_growing_puff(char *, char *, int, int, int, float);
extern void level_capture_checkpoint_state(void *, void *);
extern void snd_stop_voice(s32);
extern int PlayMobySound(int, int, char *);
extern void hero_record_play_counters(void);
extern void gfx_add_draw_callback_third(void *, void *);
extern void level_clear_first_table_entry(void);
extern int moby_start_effect_from_entry(void *, float);
extern void cutscene_start_scene(void);
extern void trooper_destroy_parts(char *arg0);
extern void electric_orb_set_position_mode(char *arg0, char *arg1, int arg2);
extern void moby_set_motion_limits(char *arg0);
extern void yeedil_boss_start_jump(char *actor);
extern void moby_set_motion_limits_range(char *arg0, float f);
extern void moby_chase_target_update(char *arg0, char *arg1, float f);
extern void enemy_choose_next_state(char *arg0);
extern void moby_run_type_update(char *arg0);
extern int enemy_is_valid_target(char *arg0, char *arg1);
extern char * yeedil_boss_spawn_lobbed_object(char *arg0, int arg1, char *arg2);
extern void yeedil_boss_compute_shot_launch(char *, char *, char *, float *);
extern void yeedil_boss_launch_damage_shot(char *arg0);
extern void enemy_compute_aim_turn_angle(char *arg0, float *arg1);
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; } Hero;
extern u8 g_hero_state[];

extern void yeedil_boss_init_damage(char *);
extern int yeedil_boss_update_grab(char *);
extern int UpdateBouncingMoby(char *);
extern char *yeedil_boss_spawn_minion_at_point(char *);
extern void yeedil_boss_choose_attack(char *);
extern void yeedil_boss_frame_upkeep(char *);
extern void yeedil_boss_compute_side_step(char *, char *);
extern u8 *group_activate_member_along_aim(char *);
extern char *enemy_fire_projectile_along_aim(char *);
extern char *yeedil_boss_fire_lobbed_projectile(char *);
extern char *yeedil_boss_launch_group_shot(char *);
extern void yeedil_boss_explode_death(char *);
extern int group_count_active_members(int);
extern char *electric_orb_spawn(char *, char *);
extern char *yeedil_enemy_spawn_shot(char *, char *, int, float, int, int);
extern void gfx_start_screen_effect(void);
extern s32 g_hero_vehicle_mode[] __attribute__((sda));
/* The same word, read through $gp in some places and absolutely in others. */
extern s32 D_L20_001A8F00_gp SDATA(D_L20_001A8F00);
extern s32 g_boss_timer __attribute__((sda));
extern f32 g_yeedil_boss_scale __attribute__((sda));
extern f32 g_yeedil_boss_motion_range __attribute__((sda));
extern f32 g_yeedil_boss_vec[] SDATA(D_L20_001B2040);
extern f32 g_yeedil_boss_anim_value __attribute__((sda));
extern f32 g_yeedil_boss_local_vec[] SDATA(D_L20_001B2060);
extern s32 g_yeedil_boss_state_value __attribute__((sda));
extern s32 g_yeedil_boss_frame_limit __attribute__((sda));
extern f32 g_yeedil_boss_hero_distance __attribute__((sda));
extern f32 g_level_interp_counter __attribute__((sda));
extern f32 g_local_to_world_vec[] SDATA(D_L20_001B20B0);
extern s32 g_yeedil_boss_flag __attribute__((sda));
extern s32 g_yeedil_boss_debug_flag __attribute__((sda));
extern f32 g_yeedil_boss_vectors[] SDATA(D_L20_001B2100);
extern u8 g_sound_state[];
extern s32 g_yeedil_boss_state_words[] MACRO_ADDR;
extern s32 g_hero_timer_trigger_a[] MACRO_ADDR;
extern s32 g_frame_l20_counter[] __attribute__((sda));
extern s32 g_yeedil_boss_flags[] MACRO_ADDR;
extern f32 g_level_shared_float[] MACRO_ADDR;
extern char *g_moby_l20_list_end __attribute__((sda));
extern char * g_yeedil_moby_list_heads[] __attribute__((sda));
extern char * g_linked_moby_table[] __attribute__((sda));
typedef union { u8 b[0x200]; s32 i[0x80]; f32 f[0x80]; } Blk200;
extern u8 g_hero_l20_extra_state[];
extern s16 g_yeedil_boss_flag_shorts[];
extern u8 g_request_l20_queue[];
extern s32 g_level_mode[];
extern s32 g_yeedil_boss_words[];
extern s8 g_effect_color_table[] __attribute__((sda));
/* Lane 3 of the D_L20_001B2100 vector, read absolutely. */
extern f32 g_yeedil_boss_vector_tail[] MACRO_ADDR;
extern char * g_hero_moby[];
extern s32 g_game_mode[];
#define AT(T, p, o) (*(T *)((char *)(p) + (o)))

/* Runs the Yeedil boss each frame (moby class 4576): the main state machine that picks attacks, lobs shots, spawns minions and handles its death (USA v2.00). */
void yeedil_boss_update_us2(char *moby) {
    float scratch[16] __attribute__((aligned(16)));
    char *vars;
    int level_mode = g_level_mode[0];
    int voice_a, first_frame_a, vehicle_mode_b, first_frame_b, voice_b;
    int vehicle_mode;
    char *hero_moby, *thrown_moby, *hero_pos_a, *side_vec_a, *hero_pos_b, *list_moby, *side_vec_b, *sound_slot_1, *sound_slot_2, *sound_slot_3;

    if (level_mode == 2) {
        vars = AT(char *, moby, 0x68);
        yeedil_boss_init_damage(moby);
        if (AT(u8, moby, 0x95) == 6) {
            if (AT(u8, moby, 0x20) == 0x18 || AT(u8, moby, 0x20) == 0x19) {
                if (IsPointInCuboid(g_hero_state + 0x80, AT(s32, vars, 0x230)) != 0) {
                    qcopy(scratch, g_yeedil_boss_vectors);
                    qzero_nc(&scratch[4]);
                    scratch[6] = g_yeedil_boss_vector_tail[0];
                    level_capture_checkpoint_state(scratch, &scratch[4]);
                    g_level_interp_counter = g_level_interp_counter + 1.0f;
                    moby_set_state(moby, 1, 0);
                    vehicle_mode = g_hero_vehicle_mode[0];
                } else {
                    vehicle_mode = D_L20_001A8F00_gp;
                }
                /* level_mode is 2 here; retail compares against its saved copy. */
                if (vehicle_mode == level_mode) {
                    AT(s32, moby, 0x98) = 0;
                    AT(u16, moby, 0x34) = (AT(u16, moby, 0x34) | 0x41) & 0xEFFF;
                } else {
                    AT(u16, moby, 0x34) = (AT(u16, moby, 0x34) & 0xFFBE) | 0x1000;
                    AT(s32, moby, 0x98) = AT(s32, AT(char *, moby, 0x24), 0x10);
                }
            }
            if (g_level_mode[0] == 2) {
                g_level_shared_float[0] = AT(f32, moby, 0x18) - 2.0f;
            }
        }
        switch (AT(u8, moby, 0x20)) {
        case 1:
            if (flag_set_first_pending(moby) != 0 && AT(u8, moby, 0x43) != 0x13) {
                anim_start_blended(moby, 0x13, 0, 0x14);
            }
            hero_moby = g_hero_moby[0];
            moby_start_effect_from_entry(moby, mat_fast_helper_a(AT(f32, hero_moby, 0x10) - AT(f32, moby, 0x10), AT(f32, hero_moby, 0x14) - AT(f32, moby, 0x14)));
            if (AT(u8, moby, 0x60) & 2) {
                enemy_choose_next_state(moby);
            }
            break;
        case 2:
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 6) {
                    anim_start_blended(moby, 6, 0, 0x14);
                }
                moby_set_motion_limits(moby);
                AT(s32, moby, 0x9C) = 1;
            }
            sound_slot_1 = (char *)g_sound_state + AT(s32, vars, 0x1854) * 0x70;
            if (AT(s32, sound_slot_1, 0x88) != (s32)moby || AT(u8, sound_slot_1, 0x74) == 0) {
                AT(s32, vars, 0x1854) = PlayMobySound(1, 4, moby);
            }
            if (AT(char *, vars, 0x1850) != 0) {
                matrix_mul_vec3(scratch, g_local_to_world_vec, moby + 0xC0);
                FastVecAdd(scratch, scratch, moby + 0x10);
                electric_orb_set_position_mode(AT(char *, vars, 0x1850), (char *)scratch, 1);
            }
            if (yeedil_boss_update_grab(moby) != 0) {
                moby_set_state(moby, 3, -1);
                voice_a = AT(s32, vars, 0x1854);
                if (voice_a != -1 && (sound_slot_2 = (char *)g_sound_state + voice_a * 0x70, AT(s32, sound_slot_2, 0x88) == (s32)moby)) {
                    if (AT(u8, sound_slot_2, 0x74) != 0) {
                        snd_stop_voice(voice_a);
                    }
                }
                AT(s32, vars, 0x1854) = -1;
            }
            break;
        case 3:
            if (flag_set_first_pending(moby) != 0) {
                yeedil_boss_start_jump(moby);
                if (AT(u8, moby, 0x43) != 6) {
                    anim_start_blended(moby, 6, 0, 0x14);
                }
                AT(s32, moby, 0x9C) = 1;
                if (AT(char *, vars, 0x1850) == 0) {
                    if (AT(s32, vars, 0x17F8) != 0) {
                        AT(char *, vars, 0x1850) = electric_orb_spawn(moby, moby + 0x10);
                    }
                }
            }
            if (AT(char *, vars, 0x1850) != 0) {
                matrix_mul_vec3(scratch, g_local_to_world_vec, moby + 0xC0);
                FastVecAdd(scratch, scratch, moby + 0x10);
                electric_orb_set_position_mode(AT(char *, vars, 0x1850), (char *)scratch, 0);
            }
            StepAngleTowardTarget((float *)(vars + 0x1804), 0, 0.0f, 0.10471977f);
            if (UpdateBouncingMoby(moby) != 0) {
                if (g_game_mode[0] != 0x8C && (math_fast_float_d(vars + 0x17F8) == 1 || g_yeedil_boss_debug_flag != 0)) {
                    if (AT(s32, vars, 0x1810) > 0) {
                        AT(s32, vars, 0x1810) = -1;
                        yeedil_boss_spawn_minion_at_point(moby);
                    }
                    enemy_choose_next_state(moby);
                    AT(s32, moby, 0x9C) = 2;
                } else {
                    moby_set_state(moby, 2, 1);
                }
            }
            break;
        case 4:
            if (flag_set_first_pending(moby) != 0) {
                moby_set_motion_limits_range(moby, g_yeedil_boss_motion_range);
                if (AT(u8, moby, 0x43) != 2) {
                    anim_start_blended(moby, 2, 0, 0x14);
                }
            }
            { char *p = AT(char *, vars, 0x17FC);
            moby_chase_target_update(moby, p + 0x10, mat_fast_helper_a(AT(f32, p, 0x10) - AT(f32, moby, 0x10), AT(f32, p, 0x14) - AT(f32, moby, 0x14))); }
            if (enemy_is_valid_target(moby, AT(char *, vars, 0x17FC)) == 0) {
                moby_set_state(moby, 1, -1);
            } else {
                if (AT(f32, vars, 0x11C) <= g_yeedil_boss_motion_range || AT(u16, moby, 0x96) >= 0x12DU) {
                    moby_set_state(moby, 5, -1);
                }
            }
            break;
        case 5:
            if (flag_set_first_pending(moby) != 0 && AT(u8, moby, 0x43) != 0xB) {
                anim_start_blended(moby, 0xB, 0, 0xF);
            }
            if (moby_get_anim_value(moby) < 31.0f) {
                { char *p = AT(char *, vars, 0x17FC);
                moby_start_effect_from_entry(moby, mat_fast_helper_a(AT(f32, p, 0x10) - AT(f32, moby, 0x10), AT(f32, p, 0x14) - AT(f32, moby, 0x14))); }
                if (enemy_is_valid_target(moby, AT(char *, vars, 0x17FC)) == 0) {
                    moby_set_state(moby, 1, -1);
                }
            } else if (math_is_value_within_step_us2((u8 *)moby, 32.0f) != 0) {
                thrown_moby = AT(char *, vars, 0x17FC);
                if (thrown_moby < g_moby_l20_list_end) {
                    FastVecScale(scratch, g_yeedil_boss_vec, g_yeedil_boss_scale);
                    matrix_mul_vec3(scratch, scratch, moby + 0xC0);
                    FastVecAdd(scratch, scratch, moby + 0x10);
                    AT(char *, vars, 0x17FC) = yeedil_boss_spawn_lobbed_object(thrown_moby, AT(s16, thrown_moby, 0xAA), (char *)scratch);
                    AT(s32, vars, 0x183C) = AT(s16, thrown_moby, 0xAA);
                    moby_run_type_update(thrown_moby);
                    AT(f32, moby, 0x48) = g_yeedil_boss_anim_value;
                }
            } else if (math_is_value_within_step_us2((u8 *)moby, 50.0f) != 0) {
                AT(f32, moby, 0x48) = 1.0f;
            }
            if (moby_get_anim_value(moby) >= 60.0f) {
                yeedil_boss_choose_attack(moby);
                moby_set_state(moby, 6, 3);
            }
            break;
        case 6:
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 2) {
                    anim_start_blended(moby, 2, 0, 0x14);
                }
                moby_set_motion_limits_range(moby, AT(f32, vars, 0x1838) * 0.5f);
            }
            hero_pos_a = (char *)(&((Hero *)g_hero_state)->b[0x80]);
            moby_chase_target_update(moby, hero_pos_a, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14)));
            if (AT(f32, vars, 0x11C) < AT(f32, vars, 0x1838) && FastDiffRots(AT(f32, moby, 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14))) < 0.087266475f) {
                moby_set_state(moby, AT(s32, vars, 0x1834), -1);
            }
            break;
        case 7: {
            int n;
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
                AT(s32, vars, 0x180C) = 0;
            }
            moby_start_effect_from_entry(moby, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14)));
            AT(s32, vars, 0x1808) = g_frame_l20_counter[0];
            matrix_mul_vec3(scratch, g_yeedil_boss_local_vec, moby + 0xC0);
            FastVecAdd(scratch, scratch, moby + 0x10);
            for (n = 1; n >= 0; n -= 1) {
                qcopy(&scratch[4], scratch);
                vec_add_random_offset(&scratch[4], 1.5f);
                scratch[2] -= 0.5f;
                part_spawn_growing_puff((char *)&scratch[4], g_effect_color_table, 0x60309030, 0x107090, 0x2D, math_random_float_range(2.0f, 3.0f) * 210000.0f);
            }
            if (AT(u8, moby, 0x42) == AT(u8, moby, 0x43) && math_fast_float_d(vars + 0x180C) != 0) {
                AT(s32, vars, 0x180C) = g_yeedil_boss_state_value;
                yeedil_boss_compute_shot_launch(moby, (char *)&scratch[4], (char *)&scratch[8], &scratch[12]);
                scratch[6] += 1.5f;
                yeedil_enemy_spawn_shot(moby, (char *)&scratch[4], 0x78, (f32)AT(u8, vars, 0x35), math_random_int_below(2), (int)(vars + 0x1808));
            }
            if (g_yeedil_boss_frame_limit < (s32)AT(u16, moby, 0x96)) {
                moby_set_state(moby, 1, -1);
            }
            break;
        }
        case 11:
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
                AT(s32, vars, 0x1840) = math_random_int_range(0xA, 0xF);
            }
            enemy_compute_aim_turn_angle(moby, (float *)(&((Hero *)g_hero_state)->b[0x80]));
            if (AT(u8, moby, 0x42) == AT(u8, moby, 0x43) && (AT(u16, moby, 0x96) % 60U) == 0x1E) {
                yeedil_boss_launch_damage_shot(moby);
                math_fast_float_d(vars + 0x1840);
            }
            if (AT(s32, vars, 0x1840) == 0) {
                moby_set_state(moby, 1, -1);
            }
            break;
        case 10:
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
                AT(s32, vars, 0x1840) = math_random_int_range(0x1E, 0x32);
            }
            if (AT(u8, moby, 0x42) == AT(u8, moby, 0x43) && (g_frame_l20_counter[0] & 7) == (((s32)moby >> 8) & 7)) {
                enemy_fire_projectile_along_aim(moby);
                math_fast_float_d(vars + 0x1840);
            }
            if (AT(s32, vars, 0x1840) == 0) {
                moby_set_state(moby, 1, -1);
            }
            break;
        case 8:
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
                AT(s32, vars, 0x1840) = math_random_int_range(0xA, 0x14);
            }
            if (AT(u8, moby, 0x42) == AT(u8, moby, 0x43) && (g_frame_l20_counter[0] & 0x1F) == (((s32)moby >> 8) & 0x1F)) {
                yeedil_boss_fire_lobbed_projectile(moby);
                math_fast_float_d(vars + 0x1840);
            }
            if (AT(s32, vars, 0x1840) == 0) {
                moby_set_state(moby, 1, -1);
            }
            break;
        case 9:
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 0x11) {
                    anim_start_blended(moby, 0x11, 0, 0x14);
                }
                AT(s32, vars, 0x1840) = math_random_int_range(4, 5);
            }
            if (AT(u8, moby, 0x42) == AT(u8, moby, 0x43) && (g_frame_l20_counter[0] & 0x1F) == (((s32)moby >> 8) & 0x1F)) {
                if (yeedil_boss_launch_group_shot(moby) != 0) {
                    math_fast_float_d(vars + 0x1840);
                } else {
                    AT(s32, vars, 0x1840) = 0;
                }
            }
            if (AT(s32, vars, 0x1840) == 0) {
                moby_set_state(moby, 1, -1);
            }
            break;
        case 12:
            if (flag_set_first_pending(moby) != 0 && AT(u8, moby, 0x43) != 0x11) {
                anim_start_blended(moby, 0x11, 0, 0x14);
            }
            if ((g_frame_l20_counter[0] & 7) == (((s32)moby >> 8) & 7)) {
                if (g_yeedil_boss_flag != 0) {
                    moby_set_state(moby, 0xD, -1);
                } else if (group_activate_member_along_aim(moby) == 0 || group_count_active_members(AT(s32, vars, 0x21C)) >= 0x15) {
                    moby_set_state(moby, 0xD, -1);
                }
            }
            break;
        case 13:
            first_frame_a = flag_set_first_pending(moby);
            side_vec_a = vars + 0x17D0;
            if (first_frame_a != 0) {
                if (AT(u8, moby, 0x43) != 2) {
                    anim_start_blended(moby, 2, 0, 0x14);
                }
                yeedil_boss_compute_side_step(moby, side_vec_a);
                moby_set_motion_limits_range(moby, 1.0f);
            }
            moby_chase_target_update(moby, side_vec_a, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14)));
            if (AT(f32, vars, 0x11C) < 1.0f && FastDiffRots(AT(f32, moby, 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14))) < 0.087266475f) {
                moby_set_state(moby, 0xE, -1);
            } else if (group_count_active_members(AT(s32, vars, 0x21C)) < 3) {
                moby_set_state(moby, 1, -1);
            }
            break;
        case 14:
            if (flag_set_first_pending(moby) != 0 && AT(u8, moby, 0x43) != 1) {
                anim_start_blended(moby, 1, 0, 0x14);
            }
            enemy_compute_aim_turn_angle(moby, (float *)(&((Hero *)g_hero_state)->b[0x80]));
            if (vec_distance_xy(moby + 0x10, g_hero_state + 0x80) < g_yeedil_boss_hero_distance) {
                moby_set_state(moby, 0xD, -1);
            }
            if (group_count_active_members(AT(s32, vars, 0x21C)) < 3) {
                moby_set_state(moby, 1, -1);
            }
            break;
        case 15:
            if (flag_set_first_pending(moby) != 0 && AT(u8, moby, 0x43) != 0x15) {
                anim_start_blended(moby, 0x15, 0, 0xA);
            }
            { float t = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f); ApproachValue((f32 *)(moby + 0x18), t, 0.16666667f); }
            if (AT(u8, moby, 0x60) & 2) {
                if (AT(u8, moby, 0xBC) != 0) {
                    moby_set_state(moby, 1, 0);
                } else {
                    moby_set_state(moby, 0x10, -1);
                }
                AT(u8, moby, 0xBC) = 0;
            }
            break;
        case 16: {
            f32 dist;
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 7) {
                    anim_start_blended(moby, 7, 0, 0x14);
                }
                moby_set_motion_limits_range(moby, 1.0f);
                AT(s32, vars, 0x1830) = 0;
            }
            if (AT(u8, moby, 0x60) & 2) {
                switch (AT(u8, moby, 0x42)) {
                case 7:
                    if (AT(u8, moby, 0x43) != 8) {
                        anim_start_blended(moby, 8, 0, 1);
                    }
                    break;
                case 8:
                    if (AT(u8, moby, 0x43) != 9) {
                        anim_start_blended(moby, 9, 0, 1);
                    }
                    break;
                case 9:
                    AT(s32, vars, 0x1830) = AT(s32, vars, 0x1830) + 1;
                    break;
                }
            }
            if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x8C) {
                ((Hero *)g_hero_state)->h[0x1E0 / 2] = 0xF;
            }
            dist = moby_get_anim_value(moby);
            if (AT(u8, moby, 0x42) == AT(u8, moby, 0x43)) {
                if ((AT(u8, moby, 0x42) == 8 && dist < 9.0f) || (AT(u8, moby, 0x42) == 9 && dist > 12.0f && dist < 30.0f)) {
                    hero_pos_b = (char *)(&((Hero *)g_hero_state)->b[0x80]);
                    moby_chase_target_update(moby, hero_pos_b, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14)));
                    if (AT(u8, moby, 0x42) == AT(u8, moby, 0x43)) {
                        if ((AT(u8, moby, 0x42) == 8 && dist < 9.0f && dist > 7.0f) || (AT(u8, moby, 0x43) == 9 && dist > 25.0f && dist < 30.0f)) {
                            qcopy(scratch, moby + 0x10);
                            scratch[2] += 1.0f;
                            coll_sweep_from_object(moby, scratch, 0x10008, 0, 1, 0, 5.5f, (f32)AT(u8, vars, 0x34), 2.0f);
                        }
                    }
                }
            }
            if (AT(u8, moby, 0x42) == 8 && math_is_value_within_step_us2((u8 *)moby, 6.0f) != 0) {
                ((Blk200 *)g_hero_l20_extra_state)->i[0x16C / 4] = 0;
                ((Blk200 *)g_hero_l20_extra_state)->i[0x188 / 4] = 0x2D;
                ((Blk200 *)g_hero_l20_extra_state)->f[0x180 / 4] = 0.05f;
            }
            if (AT(u8, moby, 0x42) == 9 && math_is_value_within_step_us2((u8 *)moby, 30.0f) != 0) {
                if (AT(s32, vars, 0x1830) >= 2 || ((Hero *)g_hero_state)->i[0x2294 / 4] == 0x8C) {
                    yeedil_boss_explode_death(moby);
                    moby_set_state(moby, 3, -1);
                }
                ((Blk200 *)g_hero_l20_extra_state)->f[0x180 / 4] = (f32)(AT(s32, vars, 0x1830) + 1) * 0.05f;
                ((Blk200 *)g_hero_l20_extra_state)->i[0x16C / 4] = 0;
                ((Blk200 *)g_hero_l20_extra_state)->i[0x188 / 4] = 0x2D;
            }
            break;
        }
        case 17:
            if (flag_set_first_pending(moby) != 0) {
                if (AT(u8, moby, 0x43) != 0x15) {
                    anim_start_blended(moby, 0x15, 0, 0xA);
                }
                list_moby = g_yeedil_moby_list_heads[0];
                vehicle_mode_b = D_L20_001A8F00_gp;
                if (list_moby != 0) {
                    /* Retail keeps these four in saved registers; with literals cc1 folds the two state
                       tests into one range check. */
                    int class_removed = 0xCBC, state_dead = 0xFE, state_dying = 0xFD;
                    int class_reset = 0xD0F;
                    int id;
                    do {
                        id = AT(s16, list_moby, 0xAA);
                        if (id == class_removed && list_moby != 0) {
                            u8 k = AT(u8, list_moby, 0x20);
                            if (k != state_dead && k != state_dying) {
                                moby_mark_spawned(list_moby);
                            }
                            id = AT(s16, list_moby, 0xAA);
                        }
                        if (id == class_reset && list_moby != 0) {
                            u8 k = AT(u8, list_moby, 0x20);
                            if (k != state_dead && k != state_dying && AT(u8, list_moby, 0x21) == AT(s32, vars, 0x21C)) {
                                SetDeathBits_us2(list_moby, 0, 3);
                                trooper_destroy_parts(list_moby);
                            }
                        }
                        list_moby = AT(char *, list_moby, 0x28);
                    } while (list_moby != 0);
                    vehicle_mode_b = g_hero_vehicle_mode[0];
                }
            } else {
                vehicle_mode_b = g_hero_vehicle_mode[0];
            }
            if (vehicle_mode_b == 2) {
                AT(s32, moby, 0x98) = 0;
                AT(u16, moby, 0x34) = (AT(u16, moby, 0x34) | 0x41) & 0xEFFF;
            }
            if (AT(u8, moby, 0x60) & 2) {
                AT(s32, moby, 0x48) = 0;
            }
            break;
        case 18:
            if (flag_set_first_pending(moby) != 0) {
                g_yeedil_boss_state_words[0] = 0;
                request_begin_slot(9, 1, 0, 0, 0);
            }
            if (g_hero_vehicle_mode[0] == 0 && g_boss_timer <= 0 && req_push_queue(g_request_l20_queue, 0x1E) != 0) {
                req_launch_queued(g_request_l20_queue);
                moby_set_state(moby, 0x13, -1);
            }
            break;
        case 19:
            if (g_hero_vehicle_mode[0] == 0) {
                if (g_boss_timer <= 0) {
                    g_yeedil_boss_flags[0] = 1;
                    request_begin_slot(9, 1, 0, 0, 0);
                    moby_set_state(moby, 0x14, -1);
                }
                if (g_hero_vehicle_mode[0] == 0) {
                    gfx_add_draw_callback_third(gfx_start_screen_effect, moby);
                }
            }
            break;
        case 20:
            if (g_hero_vehicle_mode[0] == 0 && g_boss_timer <= 0 && req_push_queue(g_request_l20_queue, 0x1F) != 0) {
                req_launch_queued(g_request_l20_queue);
                moby_set_state(moby, 0x15, -1);
            }
            break;
        case 21:
            if (g_hero_vehicle_mode[0] == 0 && g_boss_timer <= 0) {
                int a, b;
                moby_set_state(moby, 0x16, -1);
                a = GetLocalizedString(0x30F4);
                b = GetLocalizedString(0x30A6);
                settings_store_four(a, b, GetLocalizedString(0xA1F), 1);
                menu_set_size_limits(0x40, 0x20);
                request_begin_slot(4, 1, 9, 0, 0);
            }
            break;
        case 22:
            g_hero_timer_trigger_a[0] = 0;
            if (g_yeedil_boss_flag_shorts[0] == 1) {
                cutscene_start_scene();
                moby_set_state(moby, 0x17, -1);
            } else {
                char *t;
                level_clear_first_table_entry();
                t = g_linked_moby_table[0] + (AT(s32, vars, 0x248) << 7);
                level_capture_checkpoint_state(t + 0x30, t + 0x70);
                g_yeedil_boss_words[0] = 0;
                hero_record_play_counters();
            }
            break;
        case 24:
            first_frame_b = flag_set_first_pending(moby);
            side_vec_b = vars + 0x17D0;
            if (first_frame_b != 0) {
                f32 mag = math_random_float_range(5.0f, 15.0f);
                f32 ang = math_random_angle();
                char *target;
                f32 y;
                AT(f32, vars, 0x17D0) = math_fast_sin_or_cos_a(ang) * mag;
                y = math_fast_sin_or_cos_b(ang) * mag;
                target = g_linked_moby_table[0] + (AT(s32, vars, 0x230) << 7);
                AT(s32, vars, 0x17D8) = 0;
                AT(f32, vars, 0x17D4) = y;
                FastVecAdd(side_vec_b, side_vec_b, target + 0x30);
                if (AT(u8, moby, 0x43) != 2) {
                    anim_start_blended(moby, 2, 0, 0x14);
                }
                moby_set_motion_limits_range(moby, 1.5f);
            }
            moby_chase_target_update(moby, side_vec_b, mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14)));
            if (AT(f32, vars, 0x11C) <= 1.5f && FastDiffRots(AT(f32, moby, 0xF8), mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - AT(f32, moby, 0x10), ((Hero *)g_hero_state)->f[0x84 / 4] - AT(f32, moby, 0x14))) < 0.087266475f) {
                moby_set_state(moby, 0x19, -1);
            }
            break;
        case 25: {
            int anim;
            if (flag_set_first_pending(moby) != 0) {
                anim = (math_random_int_below(3) != 0) ? 0x13 : 0x14;
                if (AT(u8, moby, 0x43) != anim) {
                    anim_start_blended(moby, anim, 0, 0x14);
                }
            }
            if (AT(u8, moby, 0x60) & 2) {
                moby_set_state(moby, 0x18, -1);
            }
            break;
        }
        }
        yeedil_boss_frame_upkeep(moby);
        if (AT(u8, moby, 0x20) != 2) {
            voice_b = AT(s32, vars, 0x1854);
            if (voice_b != -1) {
                sound_slot_3 = (char *)g_sound_state + voice_b * 0x70;
                if (AT(s32, sound_slot_3, 0x88) == (s32)moby && AT(u8, sound_slot_3, 0x74) != 0) {
                    snd_stop_voice(voice_b);
                }
            }
            AT(s32, vars, 0x1854) = -1;
        }
    }
}
