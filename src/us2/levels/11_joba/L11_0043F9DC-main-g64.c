/* func_US2_L11_0043F9DC, the USA v2.00 copy of func_L11_0043E1A0: the same C, where the message ids
 * change (0x2F3C>0x2DD2, 0x3269>0x30FF, 0x2F61>0x2DF7, 0x326A>0x3100) and both give-up arms without
 * a buffer (class 9 at 0x2A31 frames, classes 3/11 on the D_001A7A00 limit) gain st->sound = 0 after
 * func_002A7750.  Its catalogue name keeps the padding word's address; the entry is 0x43F9E0. */
/* func_US2_L11_0043F9DC in its own unit (-G64 -Wa,-G64: the 56-byte class table is small data).
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

/* func_US2_L11_0043F9DC: the level's scripted-encounter driver, dispatched on the object's state
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
    s32 trackVolume;     /* 0x304 */
} JobaState;

typedef struct {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x68 - 0x21];
    JobaState *st;       /* 0x68 */
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
extern s32 hero_l11_enter_state(s32, s32);
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

void func_US2_L11_0043F9DC(u8 *obj) {
    JobaState *st;
    JobaRecord *rec1;
    JobaRecord *rec3;
    JobaRecord *rec2;
    JobaRecord *rec6;
    JobaRecord *rec8;
    JobaRecord *rec9;
    s32 ok1;
    s32 ok2;
    s32 sum1;
    s32 sum2;
    s32 sum3;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 cls1;
    s32 cls2;
    u32 cls3;
    JobaLight *lt1;
    JobaLight *lt2;
    JobaLight *lt3;
    JobaLight *lt4;
    JobaMoby *m1;
    JobaMoby *m2;
    JobaMoby *m3;
    u8 *e1;
    u8 *e2;
    f32 f1;
    f32 f2;
    u8 *p1;
    u8 *q1;
    s32 slot1;
    s32 k1;
    s32 k2;
    s32 k3;
    s32 k4;
    s32 k5;
    s32 k6;
    s32 k7;
    s32 k8;
    s32 k9;
    s32 k10;
    s32 c10;
    s32 c11;
    s32 k11;
    s32 k12;
    s32 k13;
    s32 sel;
    s32 code;
    JobaClass *cl1;
    s32 w1;
    JobaRecord *next1;
    s32 snd1;
    u8 *buf2;
    u8 *buf3;
    s32 snd2;
    s32 snd3;

    st = OBJ->st;
    blast_call_helper_no_args();
    g_arena_l11_active_flag = 1;
    switch (OBJ->state) {
    case 0:
        arena_reset_state(obj);
        arena_run_helper_on_spawn_groups(obj);
        g_hero_control_locked = 0;
        g_hero_l11_input_blocked = 0;
        g_moby_l11_table[st->door].flags |= 1;
        g_moby_l11_table[st->door].hidden = 0;
        if (g_arena_state_flag == 2) {
            g_arena_state_flag = 0;
            moby_set_state(obj, 2, -1);
            state_set_flag_one();
            st->fade = g_arena_fade_value[0];
            gfx_add_draw_callback_first(hud_draw_fade_bar, obj);
            OBJ->timer = 0x1F;
        }
        break;
    case 1:
        if (coll_point_inside_record_volume(&((Hero *)g_hero_state)->f[0x80 / 4], st->zone) != 0) {
            moby_set_state(obj, 4, -1);
        } else if (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x80 / 4], st->trigger1) != 0) {
            TryClaimNotice(4, 0x2DD2, 1);
            moby_try_alloc_enter_state2(obj);
        } else if (g_game_flag_table[arena_get_challenge_flag_index(1)] != 0) {
            if (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x80 / 4], st->trigger2) != 0) {
                TryClaimNotice(4, 0x2DD2, 1);
                moby_try_alloc_enter_state2(obj);
            }
        }
        if (g_arena_state_flag == 2) {
            g_arena_state_flag = 0;
            moby_set_state(obj, 2, -1);
            state_set_flag_one();
            st->fade = g_arena_fade_value[0];
            gfx_add_draw_callback_first(hud_draw_fade_bar, obj);
            OBJ->timer = 0x1F;
        }
        g_arena_l11_active_flag = 0;
        break;
    case 2:
        if (flag_set_first_pending(obj) != 0) {
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            OBJ->phase = 0;
            g_moby_l11_table[st->door].flags |= 1;
            g_moby_l11_table[st->door].hidden = 0;
            lt3 = &g_joba_lights[*g_arena_light_lists[st->light] & 0x7FFF];
            m1 = &g_moby_l11_table[st->lamp];
            lt3->height = 419.766f;
            m1->y = 419.766f;
        } else if (OBJ->phase == 0) {
            if (OBJ->timer < 0x1F) {
                g_arena_timer_fraction = IntToFloat(OBJ->timer) * 0.05f < 1.0f
                                     ? IntToFloat(OBJ->timer) * 0.05f
                                     : 1.0f;
            } else {
                f32 v[4] __attribute__((aligned(16)));

                st->fade = g_arena_fade_value[0];
                gfx_add_draw_callback_first(hud_draw_fade_bar, obj);
                if (g_enemy_freeze_flag[0] != 1) {
                    load_scene_chunk(1, st->music);
                }
                p1 = g_arena_camera_table + (st->camera << 7);
                hero_reset_position_and_direction(p1 + 0x30, p1 + 0x70, 0x6F, 1);
                level_capture_checkpoint_state(&((Hero *)g_hero_state)->f[0x80 / 4], &((Hero *)g_hero_state)->f[0x90 / 4]);
                script_queue_keyed_request(st->music, st->volume);
                *(TI128 *)v = *(TI128 *)(g_arena_camera_table + ((st->camera << 7) + 0x30));
                v[2] += 2.0f;
                SetCamera5Pose((char *)v, (char *)(g_arena_camera_table + (st->camera << 7) + 0x70), 1, 0, 0);
                OBJ->phase = 2;
            }
        } else if (OBJ->phase == 2) {
            gfx_add_draw_callback_third(hud_draw_fade_bar, obj);
            g_arena_timer_fraction = 0.0f;
            if (st->fade <= 0) {
                OBJ->phase = 3;
                hero_start_loader_state(0);
                hero_start_target_state(arena_get_center_point(obj), 0, 0.0f);
            }
        } else if (OBJ->phase == 3) {
            if (vec_distance_xy(&((Hero *)g_hero_state)->f[0x80 / 4], arena_get_center_point(obj)) < 10.0f) {
                if (g_game_flag_table[0x4A] == 0) {
                    g_game_flag_table[0x4A] = 1;
                    OBJ->phase = 1;
                    moby_set_flag_bit((u8 *)&g_moby_l11_table[st->gate1], 1);
                    OBJ->timer = 0;
                } else if (g_game_flag_table[arena_get_challenge_flag_index(0)] != 0) {
                    moby_set_state(obj, 4, -1);
                } else {
                    hero_reset_position_and_direction(arena_get_center_point(obj), g_arena_hero_reset_direction, 0, 1);
                    st->cls = 0;
                    st->wave = 0;
                    moby_set_state(obj, 8, -1);
                    cam_set_mode_state(2);
                }
            }
        } else if (OBJ->phase == 1) {
            if (OBJ->timer >= 0x3D && g_arena_state != 2) {
                if (g_game_flag_table[arena_get_challenge_flag_index(0)] == 0) {
                    hero_reset_position_and_direction(arena_get_center_point(obj), g_arena_hero_reset_direction, 0, 1);
                    st->cls = 0;
                    st->wave = 0;
                    moby_set_state(obj, 8, -1);
                    cam_set_mode_state(2);
                } else {
                    moby_set_state(obj, 4, -1);
                }
            }
        }
        break;
    case 5:
        if (OBJ->timer < 0xB4) {
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            ((Hero *)g_hero_state)->f[0x24A4 / 4] = 300.0f;
            arena_update_fighters_inside(obj);
            break;
        }
    case 4:
        if (flag_set_first_pending(obj) != 0) {
            if (OBJ->state == 5) {
                arena_start_challenge_result_scene((char *)obj, st->cls);
            }
            g_moby_l11_table[st->door].flags |= 1;
            g_moby_l11_table[st->door].hidden = 0;
            arena_run_helper_on_spawn_groups(obj);
            arena_run_member_handlers(obj);
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            hero_reset_position_and_direction(arena_get_center_point(obj), g_arena_hero_reset_direction, 0x6F, 1);
            level_capture_checkpoint_state(&((Hero *)g_hero_state)->f[0x80 / 4], &((Hero *)g_hero_state)->f[0x90 / 4]);
            arena_start_intro_script(obj);
            st->mode = 5;
            joba_update_ribbon_scale(obj);
            g_hero_l11_input_blocked = 0;
            g_hero_control_locked = 0;
        }
        arena_update_intro_script(obj);
        break;
    case 11:
        if (OBJ->timer < 0x168) {
            arena_set_group_a_active_count(obj, 0);
            arena_set_group_b_active_count(obj, 0);
            if (OBJ->timer >= 0xB5) {
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
            if (OBJ->timer < 0xB4) {
                ((Hero *)g_hero_state)->f[0x24A4 / 4] = 200.0f;
                arena_update_fighters_inside(obj);
                break;
            }
            if (OBJ->state == 12) {
                moby_set_flag_bit((u8 *)&g_moby_l11_table[st->gate2], 1);
            } else if (OBJ->state == 13) {
                moby_set_flag_bit((u8 *)&g_moby_l11_table[st->gate3], 1);
            }
            OBJ->timer = 0;
            OBJ->phase = 1;
        } else if (((Hero *)g_hero_state)->i[0x24CC / 4] > 0 && g_arena_state != 2 && OBJ->timer >= 0xF1) {
            arena_start_challenge_result_scene((char *)obj, st->cls);
            OBJ->state = 5;
            g_moby_l11_table[st->door].flags |= 1;
            g_moby_l11_table[st->door].hidden = 0;
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
            sel = g_game_flag_table[0x49];
            if (sel != 0 && (g_game_flag_table[arena_get_challenge_flag_index(g_arena_challenge_table[sel]->id)] == 0 ||
                             (sel >= 11 && flag_is_byte_set() == 0) ||
                             (sel == 8 && g_arena_choice_enabled[0][g_item_l11_record_table].enabled == 0))) {
                sel = 0;
            }
            st->result = sel;
        }
        UpdateJobaClassSelectionMenu(obj);
        break;
    case 8:
        arena_get_challenge_flag_index(1);
        if (flag_set_first_pending(obj) != 0) {
            st->wave = 0;
            for (k1 = 0; k1 < 8; k1++) {
                st->counts[k1] = 0;
            }
            st->frames = 0;
            st->lost = 0;
            arena_run_helper_on_spawn_groups(obj);
            arena_count_fighters(obj);
            arena_assign_fighters_to_spawns(obj);
            rec1 = &g_arena_challenge_table[st->cls]->records[st->wave];
            arena_set_group_a_active_count(obj, rec1->h[7]);
            arena_set_group_b_active_count(obj, rec1->h[6]);
            for (k3 = 0; k3 < 40; k3++) {
                st->marks[k3] = 0;
            }
            for (k3 = 0; k3 < 6; k3++) {
                st->limits[k3] = g_arena_wave_limits[k3];
            }
            ((Hero *)g_hero_state)->i[0x24CC / 4] = g_player_stats;
            moby_update_class_specials((char *)obj);
            g_moby_l11_table[st->door].flags |= 1;
            g_moby_l11_table[st->door].hidden = 0;
            if (st->cls == 7) {
                r1 = ((Hero *)g_hero_state)->i[0x18D4 / 4];
                ((Hero *)g_hero_state)->i[0x18D4 / 4] = 0;
                g_arena_saved_hero_word = r1;
            } else if (st->cls == 8) {
                r2 = ((Hero *)g_hero_state)->i[0x18D4 / 4];
                ((Hero *)g_hero_state)->i[0x18D4 / 4] = 0;
                g_arena_timer_a[0] = 300;
                g_arena_saved_hero_word = r2;
            }
        }
        rec2 = &g_arena_challenge_table[st->cls]->records[st->wave];
        if (rec2->b[3] != 0) {
            moby_set_state(obj, 9, -1);
            return;
        }
        arena_update_loss_history(obj);
        if (arena_l11_is_wave_complete(obj) != 0) {
            st->wave++;
            for (k4 = 0; k4 < 7; k4++) {
                st->counts[k4] = 0;
            }
            st->lost = 0;
            if (g_hero_l11_state_block.owner == st->owner) {
                g_hero_l11_state_block.owner = 0;
            }
            cls1 = st->cls;
            cls3 = (u16)st->cls;
            st->sound = 0;
            st->owner = 0;
            if (st->wave >= g_arena_challenge_table[cls1]->count) {
                if (cls3 - 7U < 2) {
                    ((Hero *)g_hero_state)->i[0x18D4 / 4] = g_arena_saved_hero_word;
                }
                st->result = st->cls;
                if (st->result == 0 && g_game_flag_table[arena_get_challenge_flag_index(0)] == 0) {
                    moby_set_state(obj, 12, -1);
                    return;
                }
                moby_set_state(obj, 5, -1);
                tracked_moby_set_state(1, -1);
                global_object_start((char *)1, -1);
                return;
            }
            if (cls1 >= 13) {
                st->cls = 0;
            }
            arena_assign_fighters_to_spawns(obj);
            rec3 = &g_arena_challenge_table[st->cls]->records[st->wave];
            arena_set_group_a_active_count(obj, rec3->h[7]);
            arena_set_group_b_active_count(obj, rec3->h[6]);
        }
        st->frames++;
        if (st->cls == 5) {
            if (st->frames >= 0x1519) {
                char buf[0x70];

                sum1 = 0;
                for (k5 = 0; k5 < 6; k5++) {
                    sum1 += st->counts[k5];
                }
                sprintf(buf, g_str_count_line_format, GetLocalizedString(0x30FF), g_arena_wave_kill_targets_a[st->wave] + sum1 - st->lost,
                              GetLocalizedString(0x2DF7));
                level_l00_call_module_handler_with_arg_9((int)buf, -1);
                moby_set_state(obj, 11, -1);
                tracked_moby_set_state(1, -1);
                global_object_start((char *)1, -1);
                return;
            }
        }
        if (st->cls == 9 && st->frames >= 0x2A31) {
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x30FF), -1);
            moby_set_state(obj, 11, -1);
            st->sound = 0;
            tracked_moby_set_state(1, -1);
            global_object_start((char *)1, -1);
            return;
        }
        if (st->cls == 8) {
            if (st->frames >= 0xE11) {
                char buf[0x70];

                sum2 = 0;
                for (k6 = 0; k6 < 6; k6++) {
                    sum2 += st->counts[k6];
                }
                sprintf(buf, g_str_count_line_format, GetLocalizedString(0x30FF), g_arena_wave_kill_targets_b[st->wave] + sum2 - st->lost,
                              GetLocalizedString(0x2DF7));
                level_l00_call_module_handler_with_arg_9((int)buf, -1);
                moby_set_state(obj, 11, -1);
                tracked_moby_set_state(1, -1);
                global_object_start((char *)1, -1);
                return;
            }
        }
        if ((st->cls == 3 || st->cls == 11) && ((Hero *)g_hero_state)->i[0x24CC / 4] < g_player_stats) {
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x3100), -1);
            moby_set_state(obj, 11, -1);
            st->sound = 0;
            tracked_moby_set_state(1, -1);
            global_object_start((char *)1, -1);
            return;
        }
        rec2 = &g_arena_challenge_table[st->cls]->records[st->wave];
        if (OBJ->timer >= 0x3D || rec2->b[0] != 0) {
            ok1 = 0;
            arena_clear_squad_slots_when_done(obj);
            arena_choose_next_squad_member(obj);
            e1 = st->slots[st->slot];
            if (e1 != 0 && moby_has_free_child_slot_state2(e1) != 0) {
                for (k7 = st->counts[3]; k7 < rec2->h[3]; k7++) {
                    ok1 |= arena_activate_fighter_of_class(obj, 0xDF7, 0);
                }
                for (k7 = st->counts[1]; k7 < rec2->h[1]; k7++) {
                    ok1 |= arena_activate_fighter_of_class(obj, 0xDCF, 0);
                }
                for (k7 = st->counts[2]; k7 < rec2->h[2]; k7++) {
                    ok1 |= arena_activate_fighter_of_class(obj, 0xDF4, 0);
                }
                for (k7 = st->counts[0]; k7 < rec2->h[0]; k7++) {
                    ok1 |= arena_activate_fighter_of_class(obj, 0xD98, 0);
                }
                for (k7 = st->counts[4]; k7 < rec2->h[4]; k7++) {
                    ok1 |= arena_activate_fighter_of_class(obj, 0xDF9, 0);
                }
                for (k7 = st->counts[5]; k7 < rec2->h[5]; k7++) {
                    ok1 |= arena_activate_fighter_of_class(obj, 0xD37, 0);
                }
            }
            if (st->counts[6] == 0 && rec2->b[0] != 0) {
                r3 = arena_activate_boss_of_class(obj, 0xD4A, 0);
                st->sound = r3;
                st->owner = r3;
                if (g_hero_l11_state_block.owner == 0) {
                    g_hero_l11_state_block.owner = r3;
                    g_hero_l11_state_block.timer = 0;
                }
                snd1 = st->sound;
                if (g_arena_sound_handles[0] == 0) {
                    g_arena_sound_handles[0] = snd1;
                    mem_clear(g_enemy_damage_accum, 0, 0xE0);
                }
                arena_queue_voice_line(obj, 10);
                script_queue_keyed_request(st->track, st->trackVolume);
            }
            if (rec2->b[0] == 0) {
                if (g_music_state[0x48] != st->music && g_music_state[0x3C] != st->music) {
                    script_queue_keyed_request(st->music, st->volume);
                }
            }
            if (ok1 != 0) {
                arena_refresh_squad_slots(obj);
            }
        }
        if (st->cls == 7) {
            moby_handle_request_slot_state(10);
            ((Hero *)g_hero_state)->b[0x22B7] = 1;
        }
        if (st->cls == 8) {
            moby_handle_request_slot_state(30);
        }
        gfx_add_draw_callback_first(joba_hud_draw_challenge, obj);
        arena_update_camera_guide(obj);
        joba_boss_pick_action_by_target(obj);
        if ((g_frame_counter_2 & 3) == 0) {
            arena_mark_nearest_fighters_to_attack(obj);
        }
        arena_update_fighters_inside(obj);
        if (arena_get_challenge_display_id(st->cls) != -1) {
            g_arena_challenge_display_id = arena_get_challenge_display_id(st->cls);
            g_arena_saved_value = g_frame_counter;
        }
        break;
    case 9:
        arena_get_challenge_flag_index(1);
        if (flag_set_first_pending(obj) != 0) {
            if (st->counts[7] == 0) {
                if (g_arena_challenge_table[st->cls]->records[st->wave].b[1] != 0) {
                    r4 = arena_activate_boss_of_class(obj, 0xB3A, 0);
                    st->sound = r4;
                    st->owner = r4;
                    if (g_hero_l11_state_block.owner == 0) {
                        g_hero_l11_state_block.owner = r4;
                        g_hero_l11_state_block.timer = 0;
                    }
                    snd2 = st->sound;
                    if (g_arena_sound_handles[1] == 0) {
                        g_arena_sound_handles[1] = snd2;
                        buf2 = g_enemy_damage_accum;
                        mem_clear(buf2 + 0xE0, 0, 0xE0);
                    }
                    arena_queue_voice_line(obj, 4);
                    script_queue_keyed_request(st->track, st->trackVolume);
                }
            }
            st->mode = 1;
            OBJ->phase = 0;
            arena_queue_voice_line(obj, math_random_int_below(2) + 0x1B);
            for (k8 = 0; k8 < 4; k8++) {
                st->phase[k8] = (f32)k8 * 0.25f;
                st->speed[k8] = math_random_float_range(g_l11_laser_speed_range[0], g_l11_laser_speed_range[1]) * 0.016666668f;
                st->delay[k8] = math_random_float_range(g_arena_spawn_delay_range[0], g_arena_spawn_delay_range[1]);
            }
        } else if (OBJ->phase == 0) {
            joba_update_ribbon_scale(obj);
            arena_update_loss_history(obj);
            lt1 = &g_joba_lights[*g_arena_light_lists[st->light] & 0x7FFF];
            q1 = (u8 *)&g_moby_l11_table[st->lamp];
            if (lt1->height < 421.266f) {
                f1 = lt1->height + 0.008333334f;
                lt1->height = f1;
                *(f32 *)(q1 + 0x18) = f1;
            }
            if (((Hero *)g_hero_state)->ptr[0x33C / 4] == (void *)q1 && ((Hero *)g_hero_state)->i[0x340 / 4] != 0 &&
                (((Hero *)g_hero_state)->i[0x2294 / 4] == 7 || OBJ->timer >= 0x12D)) {
                ((Hero *)g_hero_state)->i[0xF0 / 4] = 0;
                g_hero_speed_param = 80.0f;
                ((Hero *)g_hero_state)->i[0xF4 / 4] = 0;
                if (((Hero *)g_hero_state)->i[0x2294 / 4] != 7) {
                    if (((Hero *)g_hero_state)->i[0x2294 / 4] != 0x81) {
                        hero_l11_enter_state(7, 1);
                    }
                } else {
                    hero_l11_enter_state(0x81, 1);
                }
                if (vec_distance_xy(&((Hero *)g_hero_state)->f[0x80 / 4], lt1->pos) < 0.01f) {
                    ((Hero *)g_hero_state)->f[0x84 / 4] += 0.01f;
                }
            }
            ok2 = 0;
            arena_clear_squad_slots_when_done(obj);
            arena_choose_next_squad_member(obj);
            e2 = st->slots[st->slot];
            if (e2 != 0 && moby_has_free_child_slot_state2(e2) != 0) {
                for (k9 = st->counts[1]; k9 < 4; k9++) {
                    ok2 |= arena_activate_fighter_of_class(obj, 0xDCF, 0);
                }
                for (k9 = st->counts[2]; k9 < 4; k9++) {
                    ok2 |= arena_activate_fighter_of_class(obj, 0xDF4, 0);
                }
                for (k9 = st->counts[0]; k9 < 4; k9++) {
                    ok2 |= arena_activate_fighter_of_class(obj, 0xD98, 0);
                }
            }
            part_emit_robot_laser(obj);
            gfx_add_draw_callback_first(part_spawn_channel_beam_effects, obj);
            if (ok2 != 0) {
                arena_refresh_squad_slots(obj);
            }
            if (g_hero_l11_input_blocked == 0) {
                if (((Hero *)g_hero_state)->f[0x88 / 4] > 480.0f && ((Hero *)g_hero_state)->f[0x180 / 4] < 0.033333335f) {
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
            if (g_hero_l11_input_blocked != 0 && st->mode == 3) {
                OBJ->timer = 0;
                OBJ->phase = 1;
                rec6 = &g_arena_challenge_table[st->cls]->records[st->wave];
                for (c10 = 0; c10 < 6; c10++) {
                    st->counts[c10] = 0;
                }
                st->heading = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((f32 *)arena_get_center_point(obj))[0],
                                           ((Hero *)g_hero_state)->f[0x84 / 4] - ((f32 *)arena_get_center_point(obj))[1]);
                st->heading = FastAddRotations(st->heading, -1.5707965f);
                for (k10 = st->counts[3]; k10 < rec6->h[3]; k10++) {
                    arena_activate_fighter_of_class(obj, 0xDF7, 1);
                }
                for (k10 = st->counts[5]; k10 < rec6->h[5]; k10++) {
                    arena_activate_fighter_of_class(obj, 0xD37, 1);
                }
                for (k10 = st->counts[1]; k10 < rec6->h[1]; k10++) {
                    arena_activate_fighter_of_class(obj, 0xDCF, 1);
                }
                for (k10 = st->counts[2]; k10 < rec6->h[2]; k10++) {
                    arena_activate_fighter_of_class(obj, 0xDF4, 1);
                }
                for (k10 = st->counts[0]; k10 < rec6->h[0]; k10++) {
                    arena_activate_fighter_of_class(obj, 0xD98, 1);
                }
            }
        } else if (OBJ->phase == 1) {
            arena_update_loss_history(obj);
            joba_update_ribbon_scale(obj);
            if (g_arena_challenge_table[st->cls]->records[st->wave].b[4] != 0) {
                part_spawn_timed_effect_near_anchor(obj, &g_arena_challenge_table[st->cls]->records[st->wave]);
            }
            part_emit_object_sparks(obj, 0);
            if (arena_l11_is_wave_complete(obj) != 0) {
                for (c11 = 0; c11 < 8; c11++) {
                    st->counts[c11] = 0;
                }
                st->lost = 0;
                cl1 = g_arena_challenge_table[st->cls];
                w1 = st->wave;
                next1 = &cl1->records[w1 + 1];
                if (w1 + 1 < cl1->count && next1->b[3] != 0) {
                    st->heading = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - ((f32 *)arena_get_center_point(obj))[0],
                                               ((Hero *)g_hero_state)->f[0x84 / 4] - ((f32 *)arena_get_center_point(obj))[1]);
                    st->heading = FastAddRotations(st->heading, -1.5707965f);
                    st->wave++;
                    rec8 = &g_arena_challenge_table[st->cls]->records[st->wave];
                    for (k11 = st->counts[3]; k11 < rec8->h[3]; k11++) {
                        arena_activate_fighter_of_class(obj, 0xDF7, 1);
                    }
                    for (k11 = st->counts[5]; k11 < rec8->h[5]; k11++) {
                        arena_activate_fighter_of_class(obj, 0xD37, 1);
                    }
                    for (k11 = st->counts[1]; k11 < rec8->h[1]; k11++) {
                        arena_activate_fighter_of_class(obj, 0xDCF, 1);
                    }
                    for (k11 = st->counts[2]; k11 < rec8->h[2]; k11++) {
                        arena_activate_fighter_of_class(obj, 0xDF4, 1);
                    }
                    for (k11 = st->counts[0]; k11 < rec8->h[0]; k11++) {
                        arena_activate_fighter_of_class(obj, 0xD98, 1);
                    }
                    if (st->counts[7] == 0 && rec8->b[1] != 0) {
                        r5 = arena_activate_boss_of_class(obj, 0xB3A, 0);
                        st->sound = r5;
                        st->owner = r5;
                        if (g_hero_l11_state_block.owner == 0) {
                            g_hero_l11_state_block.owner = r5;
                            g_hero_l11_state_block.timer = 0;
                        }
                        snd3 = st->sound;
                        if (g_arena_sound_handles[1] == 0) {
                            g_arena_sound_handles[1] = snd3;
                            buf3 = g_enemy_damage_accum;
                            mem_clear(buf3 + 0xE0, 0, 0xE0);
                        }
                        arena_queue_voice_line(obj, 4);
                    }
                } else {
                    hero_l11_enter_state(0x6F, 1);
                    OBJ->phase = 2;
                    st->mode = 4;
                    OBJ->timer = 0;
                    tracked_moby_set_state(1, -1);
                    global_object_start((char *)1, -1);
                }
            }
            st->frames++;
            if (st->cls == 12) {
                if (st->frames >= 0x1771) {
                    char buf[0x70];

                    sum3 = 0;
                    for (k12 = 0; k12 < 6; k12++) {
                        sum3 += st->counts[k12];
                    }
                    sprintf(buf, g_str_count_line_format, GetLocalizedString(0x30FF), g_arena_wave_kill_targets_c[st->wave] + sum3 - st->lost,
                                  GetLocalizedString(0x2DF7));
                    level_l00_call_module_handler_with_arg_9((int)buf, -1);
                    lt4 = &g_joba_lights[*g_arena_light_lists[st->light] & 0x7FFF];
                    m2 = &g_moby_l11_table[st->lamp];
                    lt4->height = 419.766f;
                    m2->y = 419.766f;
                    moby_set_state(obj, 11, -1);
                    tracked_moby_set_state(1, -1);
                    global_object_start((char *)1, -1);
                    return;
                }
            }
        } else if (OBJ->phase == 2) {
            joba_update_ribbon_scale(obj);
            if (OBJ->timer >= 0xB5) {
                ((Hero *)g_hero_state)->h[0x348 / 2] = 0;
                g_hero_speed_param = 5.0f;
                hero_l11_enter_state(0x81, 1);
                OBJ->phase = 3;
            }
        } else if (OBJ->phase == 3) {
            g_hero_l11_input_blocked = 0;
            g_hero_control_locked = 0;
            if (((Hero *)g_hero_state)->f[0x88 / 4] < g_arena_hero_height_max && g_arena_hero_height_min < ((Hero *)g_hero_state)->f[0x88 / 4]) {
                ((Hero *)g_hero_state)->h[0x1F0 / 2] = 1;
            }
            joba_update_ribbon_scale(obj);
            lt2 = &g_joba_lights[*g_arena_light_lists[st->light] & 0x7FFF];
            m3 = &g_moby_l11_table[st->lamp];
            if (lt2->height > 419.766f) {
                f2 = lt2->height - 0.008333334f;
                lt2->height = f2;
                m3->y = f2;
            }
            if (st->mode == 0) {
                st->wave++;
                for (k13 = 0; k13 < 7; k13++) {
                    st->counts[k13] = 0;
                }
                st->lost = 0;
                if (g_hero_l11_state_block.owner == st->owner) {
                    g_hero_l11_state_block.owner = 0;
                }
                cls2 = st->cls;
                st->sound = 0;
                st->owner = 0;
                if (st->wave >= g_arena_challenge_table[cls2]->count) {
                    if (cls2 == 1 && g_game_flag_table[arena_get_challenge_flag_index(1)] == 0) {
                        moby_set_state(obj, 13, -1);
                        OBJ->timer = 0xB4;
                    } else {
                        moby_set_state(obj, 5, -1);
                        OBJ->timer = 0xB4;
                    }
                    tracked_moby_set_state(1, -1);
                    global_object_start((char *)1, -1);
                    st->result = st->cls;
                    return;
                }
                if (cls2 >= 13) {
                    st->cls = 0;
                }
                arena_assign_fighters_to_spawns(obj);
                rec9 = &g_arena_challenge_table[st->cls]->records[st->wave];
                arena_set_group_a_active_count(obj, rec9->h[7]);
                arena_set_group_b_active_count(obj, rec9->h[6]);
                OBJ->state = 8;
            }
        }
    tail9:
        slot1 = (s32)obj >> 8;
        gfx_add_draw_callback_first(joba_hud_draw_challenge, obj);
        arena_update_camera_guide(obj);
        joba_boss_pick_action_by_target(obj);
        if ((g_arena_progress_level & 7) == (slot1 & 7)) {
            arena_update_fighters_inside(obj);
        }
        if ((g_arena_progress_level & 0x3F) == (slot1 & 0x3F)) {
            arena_mark_nearest_fighters_to_attack(obj);
        }
        if (arena_get_challenge_display_id(st->cls) != -1) {
            g_arena_challenge_display_id = arena_get_challenge_display_id(st->cls);
            g_arena_saved_value = g_frame_counter;
        }
        break;
    }
    arena_end_frame(obj);
}

