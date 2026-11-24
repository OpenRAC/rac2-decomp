/* func_PAL_L11_004439E4, the PAL copy of func_L11_0043E1A0: the same C, where these change:
 * timers 0x1F>0x1A, 0x3D>0x33, 0xB4>0x96, 0xB5>0x97, 0x168>0x12C, 0xF1>0xC9, 0x12D>0xFB;
 * frame limits 0x1519>0x1195, 0x2A31>0x2329, 0xE11>0xBB9, 0x1771>0x1389;
 * text ids 0x2F3C>0xE61, 0x2F61>0xE86, 0x3269>0x1B37, 0x326A>0x1B38;
 * floats 0.05f>0.05882353f, 0.016666668f>0.020000001f, 0.008333334f>0.010000001f,
 * 0.033333335f>0.040000003f;
 * and st->sound = 0 after func_002A7750(obj, 11, -1) on the class-9 and class-3/11 exits. */
/* func_PAL_L11_004439E4 in its own unit (-G64 -Wa,-G64: the 56-byte class table is small data).
 * What decided the match:
 * - The state block and the object are real structs (JobaState, JobaObj), not byte views.
 * - Globals by retail form: lui/load in ordinary flow plus $gp in delay slots = a plain
 *   sized scalar; $gp everywhere = sda with its measured size; explicit %hi/%lo = an
 *   incomplete array. 0x001B3774 is element 1 of the sound pair D_L11_001B3770[2] (a
 *   symbol+offset access never fills a slot); the height band's bounds are two sda scalars.
 * - The clear loops count up; the marks and limits loops share one counter.
 * - Case 2's shared tail is written out per arm; case 9's 13-or-5 code per arm with the
 *   timer store in each arm (cross-jumping keeps retail's then-arm + b).
 * - The sound-slot blocks read st->sound before the slot test and pass the second slot's
 *   buffer as a pointer plus 0xE0; index-first sums where retail adds the index first.
 * - Case 8's wave end reads the class as (u16) into cls3 right after cls1.
 * - func_L00_0030DD70 is called for its effect only and declared void here: its ignored
 *   $v0 result otherwise takes v0 from the case-9 light/lamp chain in local-alloc.
 *   (Its definition in src/levels/shared/L00_002FC7A0.c returns its argument or the
 *   helper's value.)
 * - Case 9's start flags are set D_L11_001A8FF4 first, then D_L11_001A8FF0.
 */
#include "common.h"

/* func_PAL_L11_004439E4: the level's scripted-encounter driver, dispatched on the object's state
   byte 0x20.  Built -G8 in its own unit: the class tables and their constants sit in the level's
   small data and are reached through $gp, while the controls declared MACRO_ADDR are macro
   operands that the assembler expands to lui/low-half in ordinary flow and to one $gp access in
   a delay slot. */

/* The hero block at D_00189E20; 0x80 is the position read as D_00189EA0 elsewhere. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; void *ptr[0x980]; } Hero;

/* The object's own fields (state 0x20, timer 0x96, phase 0xBC) and the state block at 0x68. */
typedef struct JobaState {
    u8 pad000[0x90];
    f32 delay[4];        /* 0x90 */
    f32 phase[4];        /* 0xA0 */
    f32 speed[4];        /* 0xB0 */
    u8 pad0C0[0x20];
    s32 limits[6];       /* 0xE0 */
    u8 pad0F8[8];
    s32 counts[8];       /* 0x100 */
    u8 *slots[8];        /* 0x120 */
    s32 lost;            /* 0x140 */
    u8 pad144[0xC];
    s32 trigger1;        /* 0x150 */
    s32 trigger2;        /* 0x154 */
    u8 pad158[0x14];
    s32 camera;          /* 0x16C */
    u8 pad170[0x10];
    s32 sound;           /* 0x180 */
    s32 owner;           /* 0x184 */
    s32 frames;          /* 0x188 */
    s32 slot;            /* 0x18C */
    u8 pad190[0xC];
    f32 heading;         /* 0x19C */
    u8 pad1A0[0x18];
    s32 door;            /* 0x1B8 */
    u8 pad1BC[4];
    s32 light;           /* 0x1C0 */
    u8 pad1C4[0xC];
    s32 lamp;            /* 0x1D0 */
    s32 gate1;           /* 0x1D4 */
    s32 gate2;           /* 0x1D8 */
    s32 gate3;           /* 0x1DC */
    u8 pad1E0[4];
    s32 zone;            /* 0x1E4 */
    s16 result;          /* 0x1E8 */
    u8 pad1EA[6];
    s16 cls;             /* 0x1F0 */
    s16 wave;            /* 0x1F2 */
    s16 fade;            /* 0x1F4 */
    u8 pad1F6[4];
    s16 mode;            /* 0x1FA */
    u8 pad1FC[0xA4];
    s16 marks[0x28];     /* 0x2A0 */
    s32 music;           /* 0x2F0 */
    u8 pad2F4[4];
    s32 volume;          /* 0x2F8 */
    u8 pad2FC[4];
    s32 track;           /* 0x300 */
    s32 track_volume;     /* 0x304 */
} JobaState;

typedef struct {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x68 - 0x21];
    JobaState *vars;       /* 0x68 */
    u8 pad6C[0x96 - 0x6C];
    u16 timer;           /* 0x96 */
    u8 pad98[0xBC - 0x98];
    u8 phase;            /* 0xBC */
} JobaObj;

typedef int TI128 __attribute__((mode(TI)));

/* One 26-byte class record: the six target counts, then the flag bytes. */
typedef struct {
    s16 h[10];
    u8 b[6];
} JobaRecord;

typedef struct {
    s16 count;
    JobaRecord *records;
    s32 id;
} JobaClass;

typedef struct {
    u8 pad0[0x284];
    s32 owner;
    s32 timer;
} JobaFlags;

/* A moby record of the level's moby array (0x100 bytes). */
typedef struct {
    u8 pad0[0x18];
    f32 y;
    u8 pad1[0x31 - 0x1C];
    u8 hidden;
    u8 pad2[2];
    u16 flags;
    u8 pad3[0x100 - 0x36];
} JobaMoby;

/* A 0x40-byte record of the level's light table. */
typedef struct {
    u8 pad0[0x30];
    f32 pos[2];
    f32 height;
    u8 pad1[0x40 - 0x3C];
} JobaLight;

extern char g_hero_state[];
extern u8 g_game_flag_table[];
extern u8 g_arena_choice_enabled[];
extern s32 g_arena_timer_a[];
extern s32 g_arena_state_flag;
extern u16 g_arena_fade_value[];
extern s32 g_player_stats;
extern s32 g_frame_counter_2;
extern s32 g_frame_counter;
extern u8 g_music_state[];

extern f32 g_hero_speed_param;
extern s32 g_arena_state;
extern s32 g_hero_control_locked;
extern s32 g_hero_l11_input_blocked;
extern s32 g_arena_l11_active_flag;
extern u16 **g_arena_light_lists;
extern s32 g_arena_challenge_display_id;
extern u8 g_arena_wave_limits[8] __attribute__((sda));
extern s32 g_arena_wave_kill_targets_a[6] __attribute__((sda));
extern s32 g_arena_wave_kill_targets_b[2] __attribute__((sda));
extern s32 g_arena_wave_kill_targets_c[8] __attribute__((sda));
extern JobaClass *g_arena_challenge_table[14] __attribute__((sda));
extern f32 g_arena_hero_reset_direction[4] __attribute__((sda));
extern f32 g_arena_hero_height_max __attribute__((sda));
extern f32 g_arena_hero_height_min __attribute__((sda));
extern s32 g_arena_saved_hero_word __attribute__((sda));
extern f32 g_l11_laser_speed_range[2];
extern f32 g_arena_spawn_delay_range[2];
extern char g_str_count_line_format[];
extern f32 g_arena_timer_fraction;
extern s32 g_arena_progress_level;
extern JobaMoby *g_moby_l11_table;
extern s32 g_arena_saved_value;
extern u8 *g_arena_camera_table;
extern s32 g_arena_sound_handles[2];
extern JobaLight *g_joba_lights;
extern JobaFlags g_hero_l11_state_block;
extern s32 g_enemy_freeze_flag[];
extern u8 g_enemy_damage_accum[];
/* One 0xE0-byte record of the level's selection table. */
typedef struct {
    u8 pad0[4];
    u8 enabled;
    u8 pad5[0xE0 - 5];
} JobaChoice;

extern JobaChoice g_item_l11_record_table[];

extern int sprintf(char *, const char *, ...);
extern void mem_clear(void *, int, int);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 IntToFloat(s32);
extern s32 flag_is_byte_set(void);
extern char *GetLocalizedString(s32);
extern void moby_set_state(u8 *, s32, s32);
extern s32 math_random_int_below(s32);
extern f32 math_random_float_range(f32, f32);
extern s32 IsPointInCuboid(void *, s32);
extern int moby_handle_request_slot_state(s32);
extern int TryClaimNotice(s32, s32, s32);
extern s32 flag_set_first_pending(u8 *);
extern void level_capture_checkpoint_state(void *, void *);
extern void SetCamera5Pose(char *, char *, int, int, int);
extern void cam_set_mode_state(int);
extern void hero_reset_position_and_direction(void *, void *, s32, s32);
extern void hero_start_loader_state(s32);
extern void hero_start_target_state(void *, int, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void load_scene_chunk(int, int);
/* Defined returning int (L00_002FC7A0.c), but retail compiled this caller as a void call, as
   the registers after the call show: the original header evidently declared it void. */
extern void level_l00_call_module_handler_with_arg_9(int, int);
extern int coll_point_inside_record_volume(void *, int);
extern void moby_set_flag_bit(u8 *, s32);
extern void state_set_flag_one(void);
extern void tracked_moby_set_state(int, int);
extern void blast_call_helper_no_args(void);
extern void global_object_start(char *, int);
extern void script_queue_keyed_request(s32, s32);
extern s32 moby_has_free_child_slot_state2(u8 *);
extern void moby_try_alloc_enter_state2(void *);
extern s32 hero_l11_set_move_state(s32, s32);
extern int arena_get_challenge_display_id(unsigned int);
extern int arena_get_challenge_flag_index(unsigned int);
extern void arena_end_frame(u8 *);
extern void arena_reset_state(u8 *);
extern void arena_count_fighters(u8 *);
extern void arena_update_loss_history(u8 *);
extern s32 arena_activate_fighter_of_class(u8 *, s32, s32);
extern u8 *arena_activate_boss_of_class(u8 *, s32, s32);
extern void arena_choose_next_squad_member(u8 *);
extern void arena_refresh_squad_slots(u8 *);
extern void arena_clear_squad_slots_when_done(u8 *);
extern void arena_run_member_handlers(u8 *);
extern void arena_mark_nearest_fighters_to_attack(u8 *);
extern u8 *arena_get_center_point(u8 *);
extern void arena_set_group_a_active_count(u8 *, s32);
extern void arena_set_group_b_active_count(u8 *, s32);
extern void arena_update_fighters_inside(u8 *);
extern void arena_update_camera_guide(u8 *);
extern s32 arena_l11_is_wave_complete(u8 *);
extern void arena_start_challenge_result_scene(char *, int);
extern void arena_run_helper_on_spawn_groups(u8 *);
extern void arena_assign_fighters_to_spawns(u8 *);
extern void arena_start_intro_script(u8 *);
extern void arena_update_intro_script(u8 *);
extern void UpdateJobaClassSelectionMenu(u8 *);
extern void joba_hud_draw_challenge(u8 *);
extern void joba_menu_select_next(char *);
extern s32 arena_queue_voice_line(u8 *, s32);
extern void hud_draw_fade_bar(u8 *);
extern void joba_boss_pick_action_by_target(u8 *);
extern void joba_update_ribbon_scale(u8 *);
extern void part_emit_robot_laser(u8 *);
extern void part_spawn_channel_beam_effects(u8 *);
extern void part_emit_object_sparks(u8 *, s32);
extern void part_spawn_timed_effect_near_anchor(u8 *, void *);
extern void moby_update_class_specials(char *);

#define OBJ ((JobaObj *)obj)

/* Per-frame driver of the Joba arena encounter: runs the intro, the waves of fighters and bosses,
   the class selection menu, the lamp and light animation and the result handling (PAL: 50 Hz
   timings). */
void arena_controller_update_pal(u8 *obj) {
    JobaState *vars;
    JobaRecord *reset_record;
    JobaRecord *count_record;
    JobaRecord *wave_record;
    JobaRecord *boss_wave_record;
    JobaRecord *late_wave_record;
    JobaRecord *final_record;
    s32 activated_a;
    s32 activated_b;
    s32 count_sum_a;
    s32 count_sum_b;
    s32 count_sum_c;
    s32 hero_word_a;
    s32 hero_word_b;
    s32 boss_a;
    s32 boss_b;
    s32 boss_c;
    s32 class_index_a;
    s32 class_index_b;
    u32 class_index_u16;
    JobaLight *light_up;
    JobaLight *light_down;
    JobaLight *light_start;
    JobaLight *light_end;
    JobaMoby *lamp_start;
    JobaMoby *lamp_end;
    JobaMoby *lamp_down;
    u8 *squad_moby_a;
    u8 *squad_moby_b;
    f32 height_up;
    f32 height_down;
    u8 *camera_point;
    u8 *lamp_bytes;
    s32 moby_slot;
    s32 i;
    s32 j;
    s32 k;
    s32 count_i;
    s32 sum_i;
    s32 sum_j;
    s32 add_i;
    s32 laser_i;
    s32 fill_i;
    s32 top_i;
    s32 clear_i;
    s32 clear_j;
    s32 add_j;
    s32 sum_k;
    s32 reset_i;
    s32 choice;
    s32 code;
    JobaClass *challenge_class;
    s32 wave_index;
    JobaRecord *next_record;
    s32 sound_a;
    u8 *damage_accum_a;
    u8 *damage_accum_b;
    s32 sound_b;
    s32 sound_c;

    vars = OBJ->vars;
    blast_call_helper_no_args();
    g_arena_l11_active_flag = 1;
    switch (OBJ->state) {
    case 0:
        arena_reset_state(obj);
        arena_run_helper_on_spawn_groups(obj);
        g_hero_control_locked = 0;
        g_hero_l11_input_blocked = 0;
        g_moby_l11_table[vars->door].flags |= 1;
        g_moby_l11_table[vars->door].hidden = 0;
        if (g_arena_state_flag == 2) {
            g_arena_state_flag = 0;
            moby_set_state(obj, 2, -1);
            state_set_flag_one();
            vars->fade = g_arena_fade_value[0];
            gfx_add_draw_callback_first(hud_draw_fade_bar, obj);
            OBJ->timer = 0x1A;
        }
        break;
    case 1:
        if (coll_point_inside_record_volume(&((Hero *)g_hero_state)->f[0x80 / 4], vars->zone) != 0) {
            moby_set_state(obj, 4, -1);
        } else if (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x80 / 4], vars->trigger1) != 0) {
            TryClaimNotice(4, 0xE61, 1);
            moby_try_alloc_enter_state2(obj);
        } else if (g_game_flag_table[arena_get_challenge_flag_index(1)] != 0) {
            if (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x80 / 4], vars->trigger2) != 0) {
                TryClaimNotice(4, 0xE61, 1);
                moby_try_alloc_enter_state2(obj);
            }
        }
        if (g_arena_state_flag == 2) {
            g_arena_state_flag = 0;
            moby_set_state(obj, 2, -1);
            state_set_flag_one();
            vars->fade = g_arena_fade_value[0];
            gfx_add_draw_callback_first(hud_draw_fade_bar, obj);
            OBJ->timer = 0x1A;
        }
        g_arena_l11_active_flag = 0;
        break;
    case 2:
        if (flag_set_first_pending(obj) != 0) {
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            OBJ->phase = 0;
            g_moby_l11_table[vars->door].flags |= 1;
            g_moby_l11_table[vars->door].hidden = 0;
            light_start = &g_joba_lights[*g_arena_light_lists[vars->light] & 0x7FFF];
            lamp_start = &g_moby_l11_table[vars->lamp];
            light_start->height = 419.766f;
            lamp_start->y = 419.766f;
        } else if (OBJ->phase == 0) {
            if (OBJ->timer < 0x1A) {
                g_arena_timer_fraction = IntToFloat(OBJ->timer) * 0.05882353f < 1.0f
                                     ? IntToFloat(OBJ->timer) * 0.05882353f
                                     : 1.0f;
            } else {
                f32 v[4] __attribute__((aligned(16)));

                vars->fade = g_arena_fade_value[0];
                gfx_add_draw_callback_first(hud_draw_fade_bar, obj);
                if (g_enemy_freeze_flag[0] != 1) {
                    load_scene_chunk(1, vars->music);
                }
                camera_point = g_arena_camera_table + (vars->camera << 7);
                hero_reset_position_and_direction(camera_point + 0x30, camera_point + 0x70, 0x6F, 1);
                level_capture_checkpoint_state(&((Hero *)g_hero_state)->f[0x80 / 4], &((Hero *)g_hero_state)->f[0x90 / 4]);
                script_queue_keyed_request(vars->music, vars->volume);
                *(TI128 *)v = *(TI128 *)(g_arena_camera_table + ((vars->camera << 7) + 0x30));
                v[2] += 2.0f;
                SetCamera5Pose((char *)v, (char *)(g_arena_camera_table + (vars->camera << 7) + 0x70), 1, 0, 0);
                OBJ->phase = 2;
            }
        } else if (OBJ->phase == 2) {
            gfx_add_draw_callback_third(hud_draw_fade_bar, obj);
            g_arena_timer_fraction = 0.0f;
            if (vars->fade <= 0) {
                OBJ->phase = 3;
                hero_start_loader_state(0);
                hero_start_target_state(arena_get_center_point(obj), 0, 0.0f);
            }
        } else if (OBJ->phase == 3) {
            if (vec_distance_xy(&((Hero *)g_hero_state)->f[0x80 / 4], arena_get_center_point(obj)) < 10.0f) {
                if (g_game_flag_table[0x4A] == 0) {
                    g_game_flag_table[0x4A] = 1;
                    OBJ->phase = 1;
                    moby_set_flag_bit((u8 *)&g_moby_l11_table[vars->gate1], 1);
                    OBJ->timer = 0;
                } else if (g_game_flag_table[arena_get_challenge_flag_index(0)] != 0) {
                    moby_set_state(obj, 4, -1);
                } else {
                    hero_reset_position_and_direction(arena_get_center_point(obj), g_arena_hero_reset_direction, 0, 1);
                    vars->cls = 0;
                    vars->wave = 0;
                    moby_set_state(obj, 8, -1);
                    cam_set_mode_state(2);
                }
            }
        } else if (OBJ->phase == 1) {
            if (OBJ->timer >= 0x33 && g_arena_state != 2) {
                if (g_game_flag_table[arena_get_challenge_flag_index(0)] == 0) {
                    hero_reset_position_and_direction(arena_get_center_point(obj), g_arena_hero_reset_direction, 0, 1);
                    vars->cls = 0;
                    vars->wave = 0;
                    moby_set_state(obj, 8, -1);
                    cam_set_mode_state(2);
                } else {
                    moby_set_state(obj, 4, -1);
                }
            }
        }
        break;
    case 5:
        if (OBJ->timer < 0x96) {
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            ((Hero *)g_hero_state)->f[0x24A4 / 4] = 300.0f;
            arena_update_fighters_inside(obj);
            break;
        }
    case 4:
        if (flag_set_first_pending(obj) != 0) {
            if (OBJ->state == 5) {
                arena_start_challenge_result_scene((char *)obj, vars->cls);
            }
            g_moby_l11_table[vars->door].flags |= 1;
            g_moby_l11_table[vars->door].hidden = 0;
            arena_run_helper_on_spawn_groups(obj);
            arena_run_member_handlers(obj);
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            hero_reset_position_and_direction(arena_get_center_point(obj), g_arena_hero_reset_direction, 0x6F, 1);
            level_capture_checkpoint_state(&((Hero *)g_hero_state)->f[0x80 / 4], &((Hero *)g_hero_state)->f[0x90 / 4]);
            arena_start_intro_script(obj);
            vars->mode = 5;
            joba_update_ribbon_scale(obj);
            g_hero_l11_input_blocked = 0;
            g_hero_control_locked = 0;
        }
        arena_update_intro_script(obj);
        break;
    case 11:
        if (OBJ->timer < 0x12C) {
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            if (OBJ->timer >= 0x97) {
                ((Hero *)g_hero_state)->f[0x24A4 / 4] = 200.0f;
            }
            arena_update_fighters_inside(obj);
        } else {
            moby_set_state(obj, 4, -1);
        }
        break;
    case 12:
    case 13:
        if (flag_set_first_pending(obj) != 0) {
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            OBJ->phase = 0;
        }
        if (OBJ->phase == 0) {
            if (OBJ->timer < 0x96) {
                ((Hero *)g_hero_state)->f[0x24A4 / 4] = 200.0f;
                arena_update_fighters_inside(obj);
                break;
            }
            if (OBJ->state == 12) {
                moby_set_flag_bit((u8 *)&g_moby_l11_table[vars->gate2], 1);
            } else if (OBJ->state == 13) {
                moby_set_flag_bit((u8 *)&g_moby_l11_table[vars->gate3], 1);
            }
            OBJ->timer = 0;
            OBJ->phase = 1;
        } else if (((Hero *)g_hero_state)->i[0x24CC / 4] > 0 && g_arena_state != 2 && OBJ->timer >= 0xC9) {
            arena_start_challenge_result_scene((char *)obj, vars->cls);
            OBJ->state = 5;
            g_moby_l11_table[vars->door].flags |= 1;
            g_moby_l11_table[vars->door].hidden = 0;
            arena_run_helper_on_spawn_groups(obj);
            arena_run_member_handlers(obj);
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            hero_reset_position_and_direction(arena_get_center_point(obj), g_arena_hero_reset_direction, 0x6F, 1);
            level_capture_checkpoint_state(&((Hero *)g_hero_state)->f[0x80 / 4], &((Hero *)g_hero_state)->f[0x90 / 4]);
            arena_start_intro_script(obj);
            g_hero_l11_input_blocked = 0;
            g_hero_control_locked = 0;
        }
        break;
    case 6:
        joba_menu_select_next((char *)obj);
        break;
    case 7:
        if (flag_set_first_pending(obj) != 0) {
            choice = g_game_flag_table[0x49];
            if (choice != 0 && (g_game_flag_table[arena_get_challenge_flag_index(g_arena_challenge_table[choice]->id)] == 0 ||
                             (choice >= 11 && flag_is_byte_set() == 0) ||
                             (choice == 8 && g_arena_choice_enabled[0][g_item_l11_record_table].enabled == 0))) {
                choice = 0;
            }
            vars->result = choice;
        }
        UpdateJobaClassSelectionMenu(obj);
        break;
    case 8:
        arena_get_challenge_flag_index(1);
        if (flag_set_first_pending(obj) != 0) {
            vars->wave = 0;
            for (i = 0; i < 8; i++) {
                vars->counts[i] = 0;
            }
            vars->frames = 0;
            vars->lost = 0;
            arena_run_helper_on_spawn_groups(obj);
            arena_count_fighters(obj);
            arena_assign_fighters_to_spawns(obj);
            reset_record = &g_arena_challenge_table[vars->cls]->records[vars->wave];
            arena_set_group_a_active_count(obj, reset_record->h[7]);
            arena_set_group_b_active_count(obj, reset_record->h[6]);
            for (k = 0; k < 40; k++) {
                vars->marks[k] = 0;
            }
            for (k = 0; k < 6; k++) {
                vars->limits[k] = g_arena_wave_limits[k];
            }
            ((Hero *)g_hero_state)->i[0x24CC / 4] = g_player_stats;
            moby_update_class_specials((char *)obj);
            g_moby_l11_table[vars->door].flags |= 1;
            g_moby_l11_table[vars->door].hidden = 0;
            if (vars->cls == 7) {
                hero_word_a = ((Hero *)g_hero_state)->i[0x18D4 / 4];
                ((Hero *)g_hero_state)->i[0x18D4 / 4] = 0;
                g_arena_saved_hero_word = hero_word_a;
            } else if (vars->cls == 8) {
                hero_word_b = ((Hero *)g_hero_state)->i[0x18D4 / 4];
                ((Hero *)g_hero_state)->i[0x18D4 / 4] = 0;
                g_arena_timer_a[0] = 300;
                g_arena_saved_hero_word = hero_word_b;
            }
        }
        wave_record = &g_arena_challenge_table[vars->cls]->records[vars->wave];
        if (wave_record->b[3] != 0) {
            moby_set_state(obj, 9, -1);
            return;
        }
        arena_update_loss_history(obj);
        if (arena_l11_is_wave_complete(obj) != 0) {
            vars->wave++;
            for (count_i = 0; count_i < 7; count_i++) {
                vars->counts[count_i] = 0;
            }
            vars->lost = 0;
            if (g_hero_l11_state_block.owner == vars->owner) {
                g_hero_l11_state_block.owner = 0;
            }
            class_index_a = vars->cls;
            class_index_u16 = (u16)vars->cls;
            vars->sound = 0;
            vars->owner = 0;
            if (vars->wave >= g_arena_challenge_table[class_index_a]->count) {
                if (class_index_u16 - 7U < 2) {
                    ((Hero *)g_hero_state)->i[0x18D4 / 4] = g_arena_saved_hero_word;
                }
                vars->result = vars->cls;
                if (vars->result == 0 && g_game_flag_table[arena_get_challenge_flag_index(0)] == 0) {
                    moby_set_state(obj, 12, -1);
                    return;
                }
                moby_set_state(obj, 5, -1);
                tracked_moby_set_state(1, -1);
                global_object_start((char *)1, -1);
                return;
            }
            if (class_index_a >= 13) {
                vars->cls = 0;
            }
            arena_assign_fighters_to_spawns(obj);
            count_record = &g_arena_challenge_table[vars->cls]->records[vars->wave];
            arena_set_group_a_active_count(obj, count_record->h[7]);
            arena_set_group_b_active_count(obj, count_record->h[6]);
        }
        vars->frames++;
        if (vars->cls == 5) {
            if (vars->frames >= 0x1195) {
                char buf[0x70];

                count_sum_a = 0;
                for (sum_i = 0; sum_i < 6; sum_i++) {
                    count_sum_a += vars->counts[sum_i];
                }
                sprintf(buf, g_str_count_line_format, GetLocalizedString(0x1B37), g_arena_wave_kill_targets_a[vars->wave] + count_sum_a - vars->lost,
                              GetLocalizedString(0xE86));
                level_l00_call_module_handler_with_arg_9((int)buf, -1);
                moby_set_state(obj, 11, -1);
                tracked_moby_set_state(1, -1);
                global_object_start((char *)1, -1);
                return;
            }
        }
        if (vars->cls == 9 && vars->frames >= 0x2329) {
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x1B37), -1);
            moby_set_state(obj, 11, -1);
            vars->sound = 0;
            tracked_moby_set_state(1, -1);
            global_object_start((char *)1, -1);
            return;
        }
        if (vars->cls == 8) {
            if (vars->frames >= 0xBB9) {
                char buf[0x70];

                count_sum_b = 0;
                for (sum_j = 0; sum_j < 6; sum_j++) {
                    count_sum_b += vars->counts[sum_j];
                }
                sprintf(buf, g_str_count_line_format, GetLocalizedString(0x1B37), g_arena_wave_kill_targets_b[vars->wave] + count_sum_b - vars->lost,
                              GetLocalizedString(0xE86));
                level_l00_call_module_handler_with_arg_9((int)buf, -1);
                moby_set_state(obj, 11, -1);
                tracked_moby_set_state(1, -1);
                global_object_start((char *)1, -1);
                return;
            }
        }
        if ((vars->cls == 3 || vars->cls == 11) && ((Hero *)g_hero_state)->i[0x24CC / 4] < g_player_stats) {
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x1B38), -1);
            moby_set_state(obj, 11, -1);
            vars->sound = 0;
            tracked_moby_set_state(1, -1);
            global_object_start((char *)1, -1);
            return;
        }
        wave_record = &g_arena_challenge_table[vars->cls]->records[vars->wave];
        if (OBJ->timer >= 0x33 || wave_record->b[0] != 0) {
            activated_a = 0;
            arena_clear_squad_slots_when_done(obj);
            arena_choose_next_squad_member(obj);
            squad_moby_a = vars->slots[vars->slot];
            if (squad_moby_a != 0 && moby_has_free_child_slot_state2(squad_moby_a) != 0) {
                for (add_i = vars->counts[3]; add_i < wave_record->h[3]; add_i++) {
                    activated_a |= arena_activate_fighter_of_class(obj, 0xDF7, 0);
                }
                for (add_i = vars->counts[1]; add_i < wave_record->h[1]; add_i++) {
                    activated_a |= arena_activate_fighter_of_class(obj, 0xDCF, 0);
                }
                for (add_i = vars->counts[2]; add_i < wave_record->h[2]; add_i++) {
                    activated_a |= arena_activate_fighter_of_class(obj, 0xDF4, 0);
                }
                for (add_i = vars->counts[0]; add_i < wave_record->h[0]; add_i++) {
                    activated_a |= arena_activate_fighter_of_class(obj, 0xD98, 0);
                }
                for (add_i = vars->counts[4]; add_i < wave_record->h[4]; add_i++) {
                    activated_a |= arena_activate_fighter_of_class(obj, 0xDF9, 0);
                }
                for (add_i = vars->counts[5]; add_i < wave_record->h[5]; add_i++) {
                    activated_a |= arena_activate_fighter_of_class(obj, 0xD37, 0);
                }
            }
            if (vars->counts[6] == 0 && wave_record->b[0] != 0) {
                boss_a = arena_activate_boss_of_class(obj, 0xD4A, 0);
                vars->sound = boss_a;
                vars->owner = boss_a;
                if (g_hero_l11_state_block.owner == 0) {
                    g_hero_l11_state_block.owner = boss_a;
                    g_hero_l11_state_block.timer = 0;
                }
                sound_a = vars->sound;
                if (g_arena_sound_handles[0] == 0) {
                    g_arena_sound_handles[0] = sound_a;
                    mem_clear(g_enemy_damage_accum, 0, 0xE0);
                }
                arena_queue_voice_line(obj, 10);
                script_queue_keyed_request(vars->track, vars->track_volume);
            }
            if (wave_record->b[0] == 0) {
                if (g_music_state[0x48] != vars->music && g_music_state[0x3C] != vars->music) {
                    script_queue_keyed_request(vars->music, vars->volume);
                }
            }
            if (activated_a != 0) {
                arena_refresh_squad_slots(obj);
            }
        }
        if (vars->cls == 7) {
            moby_handle_request_slot_state(10);
            ((Hero *)g_hero_state)->b[0x22B7] = 1;
        }
        if (vars->cls == 8) {
            moby_handle_request_slot_state(30);
        }
        gfx_add_draw_callback_first(joba_hud_draw_challenge, obj);
        arena_update_camera_guide(obj);
        joba_boss_pick_action_by_target(obj);
        if ((g_frame_counter_2 & 3) == 0) {
            arena_mark_nearest_fighters_to_attack(obj);
        }
        arena_update_fighters_inside(obj);
        if (arena_get_challenge_display_id(vars->cls) != -1) {
            g_arena_challenge_display_id = arena_get_challenge_display_id(vars->cls);
            g_arena_saved_value = g_frame_counter;
        }
        break;
    case 9:
        arena_get_challenge_flag_index(1);
        if (flag_set_first_pending(obj) != 0) {
            if (vars->counts[7] == 0) {
                if (g_arena_challenge_table[vars->cls]->records[vars->wave].b[1] != 0) {
                    boss_b = arena_activate_boss_of_class(obj, MOBY_CLASS_ARACHNOID, 0);
                    vars->sound = boss_b;
                    vars->owner = boss_b;
                    if (g_hero_l11_state_block.owner == 0) {
                        g_hero_l11_state_block.owner = boss_b;
                        g_hero_l11_state_block.timer = 0;
                    }
                    sound_b = vars->sound;
                    if (g_arena_sound_handles[1] == 0) {
                        g_arena_sound_handles[1] = sound_b;
                        damage_accum_a = g_enemy_damage_accum;
                        mem_clear(damage_accum_a + 0xE0, 0, 0xE0);
                    }
                    arena_queue_voice_line(obj, 4);
                    script_queue_keyed_request(vars->track, vars->track_volume);
                }
            }
            vars->mode = 1;
            OBJ->phase = 0;
            arena_queue_voice_line(obj, math_random_int_below(2) + 0x1B);
            for (laser_i = 0; laser_i < 4; laser_i++) {
                vars->phase[laser_i] = (f32)laser_i * 0.25f;
                vars->speed[laser_i] = math_random_float_range(g_l11_laser_speed_range[0], g_l11_laser_speed_range[1]) * 0.020000001f;
                vars->delay[laser_i] = math_random_float_range(g_arena_spawn_delay_range[0], g_arena_spawn_delay_range[1]);
            }
        } else if (OBJ->phase == 0) {
            joba_update_ribbon_scale(obj);
            arena_update_loss_history(obj);
            light_up = &g_joba_lights[*g_arena_light_lists[vars->light] & 0x7FFF];
            lamp_bytes = (u8 *)&g_moby_l11_table[vars->lamp];
            if (light_up->height < 421.266f) {
                height_up = light_up->height + 0.010000001f;
                light_up->height = height_up;
                *(f32 *)(lamp_bytes + 0x18) = height_up;
            }
            if (((Hero *)g_hero_state)->ptr[0x33C / 4] == (void *)lamp_bytes && ((Hero *)g_hero_state)->i[0x340 / 4] != 0 &&
                (((Hero *)g_hero_state)->i[0x2294 / 4] == 7 || OBJ->timer >= 0xFB)) {
                ((Hero *)g_hero_state)->i[0xF0 / 4] = 0;
                g_hero_speed_param = 80.0f;
                ((Hero *)g_hero_state)->i[0xF4 / 4] = 0;
                if (((Hero *)g_hero_state)->i[0x2294 / 4] != 7) {
                    if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x81) {
                        hero_l11_set_move_state(7, 1);
                    }
                } else {
                    hero_l11_set_move_state(0x81, 1);
                }
                if (vec_distance_xy(&((Hero *)g_hero_state)->f[0x80 / 4], light_up->pos) < 0.01f) {
                    ((Hero *)g_hero_state)->f[0x84 / 4] += 0.01f;
                }
            }
            activated_b = 0;
            arena_clear_squad_slots_when_done(obj);
            arena_choose_next_squad_member(obj);
            squad_moby_b = vars->slots[vars->slot];
            if (squad_moby_b != 0 && moby_has_free_child_slot_state2(squad_moby_b) != 0) {
                for (fill_i = vars->counts[1]; fill_i < 4; fill_i++) {
                    activated_b |= arena_activate_fighter_of_class(obj, 0xDCF, 0);
                }
                for (fill_i = vars->counts[2]; fill_i < 4; fill_i++) {
                    activated_b |= arena_activate_fighter_of_class(obj, 0xDF4, 0);
                }
                for (fill_i = vars->counts[0]; fill_i < 4; fill_i++) {
                    activated_b |= arena_activate_fighter_of_class(obj, 0xD98, 0);
                }
            }
            part_emit_robot_laser(obj);
            gfx_add_draw_callback_first(part_spawn_channel_beam_effects, obj);
            if (activated_b != 0) {
                arena_refresh_squad_slots(obj);
            }
            if (g_hero_l11_input_blocked == 0) {
                if (((Hero *)g_hero_state)->f[0x88 / 4] > 480.0f && ((Hero *)g_hero_state)->f[0x180 / 4] < 0.040000003f) {
                    g_hero_l11_input_blocked = 1;
                    g_hero_control_locked = 1;
                    moby_update_class_specials((char *)obj);
                    part_emit_object_sparks(obj, 5);
                }
                if (g_hero_l11_input_blocked == 0) {
                    if (((Hero *)g_hero_state)->f[0x88 / 4] < g_arena_hero_height_max && g_arena_hero_height_min < ((Hero *)g_hero_state)->f[0x88 / 4]) {
                        ((Hero *)g_hero_state)->h[0x1F0 / 2] = 1;
                    }
                    if (g_hero_l11_input_blocked == 0) {
                        goto tail9;
                    }
                }
            }
            part_emit_object_sparks(obj, 0);
            if (g_hero_l11_input_blocked != 0 && vars->mode == 3) {
                OBJ->timer = 0;
                OBJ->phase = 1;
                boss_wave_record = &g_arena_challenge_table[vars->cls]->records[vars->wave];
                for (clear_i = 0; clear_i < 6; clear_i++) {
                    vars->counts[clear_i] = 0;
                }
                vars->heading = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((f32 *)arena_get_center_point(obj))[0],
                                           ((Hero *)g_hero_state)->f[0x84 / 4] - ((f32 *)arena_get_center_point(obj))[1]);
                vars->heading = FastAddRotations(vars->heading, -1.5707965f);
                for (top_i = vars->counts[3]; top_i < boss_wave_record->h[3]; top_i++) {
                    arena_activate_fighter_of_class(obj, 0xDF7, 1);
                }
                for (top_i = vars->counts[5]; top_i < boss_wave_record->h[5]; top_i++) {
                    arena_activate_fighter_of_class(obj, 0xD37, 1);
                }
                for (top_i = vars->counts[1]; top_i < boss_wave_record->h[1]; top_i++) {
                    arena_activate_fighter_of_class(obj, 0xDCF, 1);
                }
                for (top_i = vars->counts[2]; top_i < boss_wave_record->h[2]; top_i++) {
                    arena_activate_fighter_of_class(obj, 0xDF4, 1);
                }
                for (top_i = vars->counts[0]; top_i < boss_wave_record->h[0]; top_i++) {
                    arena_activate_fighter_of_class(obj, 0xD98, 1);
                }
            }
        } else if (OBJ->phase == 1) {
            arena_update_loss_history(obj);
            joba_update_ribbon_scale(obj);
            if (g_arena_challenge_table[vars->cls]->records[vars->wave].b[4] != 0) {
                part_spawn_timed_effect_near_anchor(obj, &g_arena_challenge_table[vars->cls]->records[vars->wave]);
            }
            part_emit_object_sparks(obj, 0);
            if (arena_l11_is_wave_complete(obj) != 0) {
                for (clear_j = 0; clear_j < 8; clear_j++) {
                    vars->counts[clear_j] = 0;
                }
                vars->lost = 0;
                challenge_class = g_arena_challenge_table[vars->cls];
                wave_index = vars->wave;
                next_record = &challenge_class->records[wave_index + 1];
                if (wave_index + 1 < challenge_class->count && next_record->b[3] != 0) {
                    vars->heading = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((f32 *)arena_get_center_point(obj))[0],
                                               ((Hero *)g_hero_state)->f[0x84 / 4] - ((f32 *)arena_get_center_point(obj))[1]);
                    vars->heading = FastAddRotations(vars->heading, -1.5707965f);
                    vars->wave++;
                    late_wave_record = &g_arena_challenge_table[vars->cls]->records[vars->wave];
                    for (add_j = vars->counts[3]; add_j < late_wave_record->h[3]; add_j++) {
                        arena_activate_fighter_of_class(obj, 0xDF7, 1);
                    }
                    for (add_j = vars->counts[5]; add_j < late_wave_record->h[5]; add_j++) {
                        arena_activate_fighter_of_class(obj, 0xD37, 1);
                    }
                    for (add_j = vars->counts[1]; add_j < late_wave_record->h[1]; add_j++) {
                        arena_activate_fighter_of_class(obj, 0xDCF, 1);
                    }
                    for (add_j = vars->counts[2]; add_j < late_wave_record->h[2]; add_j++) {
                        arena_activate_fighter_of_class(obj, 0xDF4, 1);
                    }
                    for (add_j = vars->counts[0]; add_j < late_wave_record->h[0]; add_j++) {
                        arena_activate_fighter_of_class(obj, 0xD98, 1);
                    }
                    if (vars->counts[7] == 0 && late_wave_record->b[1] != 0) {
                        boss_c = arena_activate_boss_of_class(obj, MOBY_CLASS_ARACHNOID, 0);
                        vars->sound = boss_c;
                        vars->owner = boss_c;
                        if (g_hero_l11_state_block.owner == 0) {
                            g_hero_l11_state_block.owner = boss_c;
                            g_hero_l11_state_block.timer = 0;
                        }
                        sound_c = vars->sound;
                        if (g_arena_sound_handles[1] == 0) {
                            g_arena_sound_handles[1] = sound_c;
                            damage_accum_b = g_enemy_damage_accum;
                            mem_clear(damage_accum_b + 0xE0, 0, 0xE0);
                        }
                        arena_queue_voice_line(obj, 4);
                    }
                } else {
                    hero_l11_set_move_state(0x6F, 1);
                    OBJ->phase = 2;
                    vars->mode = 4;
                    OBJ->timer = 0;
                    tracked_moby_set_state(1, -1);
                    global_object_start((char *)1, -1);
                }
            }
            vars->frames++;
            if (vars->cls == 12) {
                if (vars->frames >= 0x1389) {
                    char buf[0x70];

                    count_sum_c = 0;
                    for (sum_k = 0; sum_k < 6; sum_k++) {
                        count_sum_c += vars->counts[sum_k];
                    }
                    sprintf(buf, g_str_count_line_format, GetLocalizedString(0x1B37), g_arena_wave_kill_targets_c[vars->wave] + count_sum_c - vars->lost,
                                  GetLocalizedString(0xE86));
                    level_l00_call_module_handler_with_arg_9((int)buf, -1);
                    light_end = &g_joba_lights[*g_arena_light_lists[vars->light] & 0x7FFF];
                    lamp_end = &g_moby_l11_table[vars->lamp];
                    light_end->height = 419.766f;
                    lamp_end->y = 419.766f;
                    moby_set_state(obj, 11, -1);
                    tracked_moby_set_state(1, -1);
                    global_object_start((char *)1, -1);
                    return;
                }
            }
        } else if (OBJ->phase == 2) {
            joba_update_ribbon_scale(obj);
            if (OBJ->timer >= 0x97) {
                ((Hero *)g_hero_state)->h[0x348 / 2] = 0;
                g_hero_speed_param = 5.0f;
                hero_l11_set_move_state(0x81, 1);
                OBJ->phase = 3;
            }
        } else if (OBJ->phase == 3) {
            g_hero_l11_input_blocked = 0;
            g_hero_control_locked = 0;
            if (((Hero *)g_hero_state)->f[0x88 / 4] < g_arena_hero_height_max && g_arena_hero_height_min < ((Hero *)g_hero_state)->f[0x88 / 4]) {
                ((Hero *)g_hero_state)->h[0x1F0 / 2] = 1;
            }
            joba_update_ribbon_scale(obj);
            light_down = &g_joba_lights[*g_arena_light_lists[vars->light] & 0x7FFF];
            lamp_down = &g_moby_l11_table[vars->lamp];
            if (light_down->height > 419.766f) {
                height_down = light_down->height - 0.010000001f;
                light_down->height = height_down;
                lamp_down->y = height_down;
            }
            if (vars->mode == 0) {
                vars->wave++;
                for (reset_i = 0; reset_i < 7; reset_i++) {
                    vars->counts[reset_i] = 0;
                }
                vars->lost = 0;
                if (g_hero_l11_state_block.owner == vars->owner) {
                    g_hero_l11_state_block.owner = 0;
                }
                class_index_b = vars->cls;
                vars->sound = 0;
                vars->owner = 0;
                if (vars->wave >= g_arena_challenge_table[class_index_b]->count) {
                    if (class_index_b == 1 && g_game_flag_table[arena_get_challenge_flag_index(1)] == 0) {
                        moby_set_state(obj, 13, -1);
                        OBJ->timer = 0x96;
                    } else {
                        moby_set_state(obj, 5, -1);
                        OBJ->timer = 0x96;
                    }
                    tracked_moby_set_state(1, -1);
                    global_object_start((char *)1, -1);
                    vars->result = vars->cls;
                    return;
                }
                if (class_index_b >= 13) {
                    vars->cls = 0;
                }
                arena_assign_fighters_to_spawns(obj);
                final_record = &g_arena_challenge_table[vars->cls]->records[vars->wave];
                arena_set_group_a_active_count(obj, final_record->h[7]);
                arena_set_group_b_active_count(obj, final_record->h[6]);
                OBJ->state = 8;
            }
        }
    tail9:
        moby_slot = (s32)obj >> 8;
        gfx_add_draw_callback_first(joba_hud_draw_challenge, obj);
        arena_update_camera_guide(obj);
        joba_boss_pick_action_by_target(obj);
        if ((g_arena_progress_level & 7) == (moby_slot & 7)) {
            arena_update_fighters_inside(obj);
        }
        if ((g_arena_progress_level & 0x3F) == (moby_slot & 0x3F)) {
            arena_mark_nearest_fighters_to_attack(obj);
        }
        if (arena_get_challenge_display_id(vars->cls) != -1) {
            g_arena_challenge_display_id = arena_get_challenge_display_id(vars->cls);
            g_arena_saved_value = g_frame_counter;
        }
        break;
    }
    arena_end_frame(obj);
}

