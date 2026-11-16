#include "names.h"
/* func_PAL_L04_0041E49C, the PAL copy of func_L04_00419918: the same C, where rename func_L00_002B9D60 becomes func_PAL_L00_002B9CD8; rename func_L04_002E7C08 becomes func_PAL_L04_002E7DA8; rename func_L00_00303530 becomes func_PAL_L00_00305110; rename func_0029B758 becomes func_PAL_0029C0F0; rename func_002E4AC8 becomes func_PAL_002E5898; rename func_L04_0040A958 becomes func_PAL_L04_0040EEE0; rename func_L04_00418A58 becomes func_PAL_L04_0041D5F0; rename func_002A05A8 becomes func_PAL_002A0F68; rename func_00288E18 becomes func_PAL_00289730; rename func_L04_00412308 becomes func_PAL_L04_004169C0; rename func_L04_00418BF0 becomes func_PAL_L04_0041D788; rename func_L00_002B30E8 becomes func_PAL_L00_002B3000. */
/* func_PAL_L04_0041E49C, the hoverbike race controller of Barlow and Joba. Its own -G8 unit,
 * built with -g (config/cflags.txt): the line notes give retail's nop pair before case 2's div.s. */
#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));

extern char g_hero_state[];
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot g_sound_state[];
extern int g_pad_pressed_flags NOT_SDA;
extern int g_pad_held_flags NOT_SDA;
extern int g_current_map_index MACRO_ADDR;
extern int g_arena_state_flag MACRO_ADDR;
extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern int g_race_init_flag MACRO_ADDR;
extern float g_race_float_param MACRO_ADDR;
extern int g_race_state_value MACRO_ADDR;
extern int g_race_state_flags MACRO_ADDR;
/* The race flag words; [5] is the flag func_L04_00402D90 sets. */
extern int D_L04_001A8ED0_flags[] __asm__("D_L04_001A8ED0") MACRO_ADDR;
extern int g_game_l04_mode MACRO_ADDR;
extern int g_game_mode_alt MACRO_ADDR;
extern int g_current_lap MACRO_ADDR;
extern int g_race_time_ticks MACRO_ADDR;
extern void *g_race_callback_a MACRO_ADDR;
extern void *g_race_callback_b MACRO_ADDR;
extern void *g_race_callback_c MACRO_ADDR;
extern void *g_race_callback_d MACRO_ADDR;
extern u8 *g_race_bike_child_moby __attribute__((sda));
extern int g_race_bike_mode __attribute__((sda));
extern int g_race_extra_ticks __attribute__((sda));
extern int g_race_voice_busy_flag __attribute__((sda));
extern int g_race_voice_state __attribute__((sda));
extern int g_race_state_request __attribute__((sda));
extern int g_current_race_index __attribute__((sda));
/* D_L04_001B0910 in Barlow; in Joba that name is bound to another variable. */
extern int ref_L04_00419918_01 __attribute__((sda));
extern u8 *g_race_controller __attribute__((sda));
extern int g_race_progress_counter __attribute__((sda));
extern int g_race_banner_timer __attribute__((sda));
extern int g_race_voice_pending __attribute__((sda));
extern int g_race_mode_active_flag __attribute__((sda));
extern int g_race_l04_state_flag_c_2 __attribute__((sda));
extern int g_race_state_flag_d __attribute__((sda));
extern int g_race_trick_state __attribute__((sda));
extern int g_level_l04_event_flag __attribute__((sda));
extern int g_race_mode_started_flag __attribute__((sda));
extern float g_level_float_setting __attribute__((sda));
extern int g_game_tick_counter __attribute__((sda));
extern u8 *g_moby_l04_pool MACRO_ADDR;
extern u8 *g_linked_record_table MACRO_ADDR;
extern int g_race_warning_stage MACRO_ADDR;
extern char g_route_frame_delta[] MACRO_ADDR;
extern char g_hero_l04_state[];
extern char g_tether_zero_vec[];
extern Quad g_collision_quad;
extern float g_projection_scale_float NOT_SDA;
extern void hero_record_play_counters_pal(void);
extern void hero_reset_position_and_direction_pal(void *, void *, int, int);
extern int hero_l04_enter_state_pal(int, int);
extern void cam_set_transition_frames(float);
extern int coll_test_point(void *, int, void *, float);
extern void UpdateViewContext(void);
extern void gfx_add_draw_callback_third(void *, void *);
extern void FadeToBlack(int);
extern int math_fast_float_d(void *);
extern float fast_vec_dist(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void set_identity_rotation_rows(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void help_unlock_entry(int);
extern int subtitle_request_voice_line_pal(int, int);
extern void load_scene_chunk_pal(int, int);
extern void level_store_value_pair_pal(int, void *);
extern void moby_mark_spawned(void *);
extern void AttachManipulator(void *, int, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void anim_start_immediate(void *, int, int);
extern float math_random_float_range(float, float);
extern void mat_build_rotation_from_angles(void *, float *);
extern void moby_update_ground_check(void *);
extern void moby_mark_flag_and_append_to_list(int);
extern int TryClaimNotice(int, int, int);
extern int level_release_matching_resource(int);
extern int flag_is_third_pending_set(void *);
extern void script_queue_keyed_request(int, int);
extern void anim_sample_key_track(float, float, void *, void *, void *, void *);
extern void level_capture_checkpoint_state(void *, void *);
extern int UpdateSoundVoices_pal(void);
extern int snd_is_voice_playing_for_owner(void *, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern int snd_play_from_global_bank(int, int, void *);
extern int snd_start_in_slot(int, int, void *);
extern int snd_set_slot_field(int, int);
extern void state_set_flag_one(void);
extern int FindNearestRoutePointIndex(void *, void *, int);
extern int race_get_course_win_count(int);
extern int race_get_course_finish_count(int);
extern void part_refresh_active_records(void *);
extern void racer_reset_state(void *, int);
extern void racer_activate_linked(void *);
extern void race_reset_controller_pal(void *, int);
extern void racer_release_link_state(void *, void *);
extern void UpdateRaceSelectionMenu(void *, void *);
extern void racer_release_sound_handles(void *, void *);
extern void race_recompute_branch_route_links(void *);
extern void FindNearestRoutePoint(void *, void *, void *, void *, void *, int);
extern int racer_is_in_jump_window(int, int, float);
extern int race_update_player_progress_pal(void *, void *);
extern void math_step_angle_offset(void *, void *, float, float);
extern void trail_clear_by_owner(void *);
extern s32 hud_draw_race_ruler(void);
extern void hoverbike_update_rider_entry_state_pal(void *, void *);
extern void hoverbike_update_rail_grind_trick_pal(void *, void *);
extern void hoverbike_init_race_course(void *);
extern void barlow_init_animation_paths(void);
extern void race_set_state_flags_a(void);
/* func_L04_0040AC98 in Barlow; Joba places its copy elsewhere. */
extern void ref_L04_00419918_00(void);
extern void race_set_state_flags_c(void);
extern int race_draw_results_panel(void);
extern void racer_draw_glow_effects(void);
extern s32 DrawRaceStandingsHud(void);
extern void snd_send_cmd23(int);
extern int snd_Pump(void);

#define M_(p, t, o) (((struct { u8 pad[o]; t v; } *)(p))->v)
#define I(p, o) M_(p, int, o)
#define F(p, o) M_(p, float, o)
#define H(p, o) M_(p, unsigned short, o)
#define P(p, o) M_(p, u8 *, o)
#define Q(p, o) M_(p, Quad, o)
typedef struct { u8 b[0x100]; } MobyRec;
typedef struct { int v[1]; } IdList;
typedef struct { u8 b[0x80]; } NodeRec;
#define MOBY(i) (((MobyRec *)D_L04_001B24DC)[i].b)
#define NODE(i) (((NodeRec *)D_L04_001B25CC)[i].b)

/* The hoverbike race controller of Barlow and Joba: spawns the bikes and the course, waits for
   the hero to mount, runs the countdown, the race and the finish, and puts everything back. */
void update_hoverbike_race_pal(u8 *self)
{
    Vector a;
    Vector b;
    u8 *s = P(self, 0x68);
    u8 *o;
    int k, flag, path;
    IdList *ids;
    float *fp;
    int id;
    float d;

    if (self[0x31] != 0 && fast_vec_dist(self + 0x10, g_tether_zero_vec) < 24.0f) {
        moby_update_ground_check(self);
        self[0x6F] = 22;
    }
    if ((g_game_mode_alt == 2 || g_game_l04_mode == 2) && g_race_mode_started_flag == 0 && g_current_map_index != 11) {
        H(self, 0x34) = (H(self, 0x34) | 0x41) & ~0x1000;
        I(self, 0x98) = 0;
        g_race_mode_started_flag = 1;
        return;
    }
    if (g_game_mode_alt != 2 && g_game_l04_mode != 2 && g_race_mode_started_flag != 0) {
        H(self, 0x34) = (H(self, 0x34) & ~0x41) | 0x1000;
        I(self, 0x98) = I(P(self, 0x24), 0x10);
        g_race_mode_started_flag = 0;
    }
    switch (self[0x20]) {
    case 0:
        I(s, 0x748) = -1;
        I(s, 0x74C) = -1;
        I(s, 0x714) = -1;
        I(s, 0x3BC) = -1;
        I(s, 0x328) = -1;
        I(s, 0x330) = -1;
        I(s, 0x334) = -1;
        g_race_callback_a = race_set_state_flags_a;
        g_race_callback_b = ref_L04_00419918_00;
        g_race_callback_c = race_set_state_flags_c;
        g_race_callback_d = ref_L04_00419918_00;
        set_identity_rotation_rows(g_route_frame_delta);
        g_race_controller = self;
        barlow_init_animation_paths();
        self[0x30] = 0x40;
        H(self, 0x32) = 0x40;
        self[0x20] = 1;
        race_recompute_branch_route_links(self);
        H(self, 0x34) |= 0x400;
        if (g_arena_state_flag == 3) {
            g_race_voice_busy_flag = 1;
            hero_reset_position_and_direction_pal(NODE(I(s, 0x19C)) + 0x30, NODE(I(s, 0x19C)) + 0x70, 0, 1);
            g_arena_state_flag = 0;
            state_set_flag_one();
        } else {
            g_race_voice_busy_flag = 0;
        }
        Q(s, 0x2D0) = Q(self, 0x10);
        Q(s, 0x2E0) = Q(self, 0xF0);
        qzero(s + 0x290);
        qzero(s + 0x2A0);
        I(s, 0x314) = -1;
        I(s, 0x494) = -1;
        F(s, 0x660) = 0.01f;
        F(s, 0x664) = 0.02f;
        F(s, 0x668) = 0.03f;
        F(s, 0x66C) = 0.04f;
        I(s, 0x318) = 0;
        I(s, 0x498) = 0;
        I(s, 0x640) = 0;
        if (g_current_map_index == 4) {
            I(s, 0x648) = 0x48;
            I(s, 0x644) = 0x4D;
        } else {
            I(s, 0x648) = 0x41;
            I(s, 0x644) = 0x42;
        }
        I(s, 0x768) = 0;
        I(s, 0x764) = 33;
        fp = (float *)(s + 0x370);
        for (k = 0; k < 21; k++) {
            int id = ((int *)(s + 0x1E4))[k];

            if (id != -1) {
                u8 *rider = P(MOBY(id), 0x68);

                I(rider, 0x120) = -1;
                I(rider, 0x124) = 0;
                I(rider, 0x1C4) = -1;
                I(rider, 0x1C8) = 0;
            }
        }
        I(s, 0x340) = 0;
        I(s, 0x344) = 0;
        for (k = 0; k < 5; k++) {
            I(s, 0x344) += race_get_course_win_count(k);
            I(s, 0x340) += race_get_course_finish_count(k);
        }
        for (k = 0; k < 6; k++) {
            fp[k] = math_random_float_range(0.0f, 1.0f);
        }
        if (g_current_map_index == 11 && race_get_course_win_count(0) > 0 && g_item_owned_flags[0x36] == 0) {
            help_unlock_entry(0x36);
        } else if (g_current_map_index == 4 && race_get_course_win_count(0) > 0) {
            moby_mark_flag_and_append_to_list(5);
        }
        if (s[0x441] == 0) {
            AttachManipulator(self, 5, s + 0x440);
        }
        return;
    case 1:
        flag = g_race_voice_busy_flag != 0;
        if (I(s, 0x238) == -1 || flag_is_third_pending_set(MOBY(I(s, 0x238))) != 0) {
            math_step_angle_offset(self, s, 0.02f, 0.00029f);
            flag = 1;
            F(self, 0x18) = F(s, 0x2D8) + math_fast_sin_or_cos_b(F(s, 0x38C)) * 0.04f;
            qzero_nc(a);
            a[0] = F(s, 0x38C);
            mat_build_rotation_from_angles(s + 0x450, a);
            if (I(s, 0x238) != -1) {
                u8 *m = MOBY(I(s, 0x238));

                I(m, 0x98) = 0;
                H(m, 0x34) |= 0x43;
                if (I(s, 0x1E0) != -1) {
                    m = MOBY(I(s, 0x1E0));
                    I(m, 0x98) = 0;
                    H(m, 0x34) |= 0x43;
                }
            }
        }
        d = fast_vec_dist(g_hero_state + 0x80, self + 0x10);
        if (g_race_voice_busy_flag == 0) {
            if (!flag || !(d < 5.5f) || g_game_tick_counter < 4) {
                return;
            }
            if (I(g_hero_state, 0x229C) == 0x1F || I(g_hero_state, 0x2294) == 0x1D
                || I(g_hero_state, 0x2294) == 0x1C || I(g_hero_state, 0x2294) == 1
                || g_game_l04_mode == 2 || g_game_mode_alt == 2) {
                return;
            }
            if (g_race_voice_pending == 0 && snd_is_voice_playing_for_owner(self, I(s, 0x330)) == 0) {
                I(s, 0x330) = snd_start_in_slot(g_current_map_index == 4 ? 0x16 : 0x1A, 5, self);
                snd_set_slot_field(I(s, 0x330), FloatToInt(IntToFloat(0x400) * 0.75f));
            }
        }
        TryClaimNotice(4, 0x12f3, 1);
        if (g_race_voice_busy_flag == 0 && g_race_voice_pending == 0 && !(g_pad_held_flags & 0x10)) {
            return;
        }
        {
            int sound = I(s, 0x330);

            if (sound != -1) {
                SoundSlot *slot = (SoundSlot *)((char *)g_sound_state + sound * 0x70);

                if (slot->owner == (char *)self && slot->active) {
                    snd_stop_voice(sound);
                }
            }
            I(s, 0x330) = -1;
        }
        if (g_current_map_index == 0xCE) {
            hero_l04_enter_state_pal(0x86, 1);
        } else {
            if (I(s, 0x198) != -1) {
                if (I(s, 0x19C) != -1) {
                    level_capture_checkpoint_state(NODE(I(s, 0x19C)) + 0x30, NODE(I(s, 0x19C)) + 0x70);
                } else {
                    level_capture_checkpoint_state(self + 0x10, self + 0xF0);
                }
                FadeToBlack(0xd);
                hero_reset_position_and_direction_pal(NODE(I(s, 0x198)) + 0x30, NODE(I(s, 0x198)) + 0x70, 0x31, 1);
                Q(self, 0xd) = Q(NODE(I(s, 0x198)), 0x30);
                Q(self, 0xF0) = Q(NODE(I(s, 0x198)), 0x70);
            }
            hero_l04_enter_state_pal(0x31, 1);
            load_scene_chunk_pal(1, I(s, 0x488));
            I(s, 0x58) |= 1;
            I(s, 0x340) = 0;
            F(s, 0x28) = 2.0f;
            I(s, 0x54) = 0;
            F(s, 0x40) = 0.012f;
            F(s, 0x24) = 0.1f;
            F(s, 0x20) = 0.25f;
            F(s, 0x2C) = 2.0f;
            F(s, 0x30) = 1.0f;
            F(s, 0x44) = 0.012f;
            F(s, 0x48) = 0.6f;
            F(s, 0x4C) = 0.0048f;
            I(s, 0x270) = 0;
            g_current_lap = 0;
            g_race_time_ticks = 0;
            g_race_progress_counter = 0;
            I(s, 0x31C) = 0;
        }
        H(self, 0x34) |= 0x41;
        {
            u8 *m = 0;

            if (I(s, 0x1DC) != -1) {
                m = MOBY(I(s, 0x1DC));
            }
            if (m != 0) {
                H(m, 0x34) |= 0x41;
                if (g_race_bike_child_moby != 0) {
                    H(g_race_bike_child_moby, 0x34) |= 0x41;
                }
            }
        }
        self[0x20] = 2;
        if (g_race_voice_pending != 0) {
            self[0xBC] = 2;
        } else {
            level_store_value_pair_pal(0, race_draw_results_panel);
            self[0xBC] = 0;
        }
        g_race_voice_busy_flag = 0;
        I(s, 0x394) = 125;
        self[0x30] = 0xFF;
        level_release_matching_resource(4);
        g_hero_state[0x22B5] = 1;
        I(P(g_hero_state, 0x2290), 0x98) = 0;
        script_queue_keyed_request(I(s, 0x488), -1);
        return;
    case 2:
        if (I(g_hero_state, 0x2294) == 0x86) {
            u8 *bike = P(g_hero_state, 0x2290);
            float ratio = F(bike, 0x2C) / F(P(bike, 0x24), 0x24);

            F(self, 0x2C) = F(P(self, 0x24), 0x24) * ratio;
            return;
        }
        if (g_race_state_request != 0) {
            g_race_state_flags = 2;
            UpdateSoundVoices_pal();
            FadeToBlack(0xd);
            if (g_race_state_request == 2) {
                race_reset_controller_pal(self, 1);
            } else {
                race_reset_controller_pal(self, 0);
            }
            g_race_state_request = 0;
            return;
        }
        if (ref_L04_00419918_01 != 0) {
            g_race_state_flags = 1;
            H(self, 0x34) &= ~0x41;
            racer_release_link_state(self, s);
            I(s, 0x320) = -1;
            self[0x20] = 4;
            ref_L04_00419918_01 = 0;
            return;
        }
        switch (self[0xBC]) {
        case 0:
            g_level_l04_event_flag = 0;
            UpdateRaceSelectionMenu(self, s);
            level_store_value_pair_pal(0, race_draw_results_panel);
            return;
        case 1:
            hoverbike_update_rider_entry_state_pal(self, s);
            if (*(u8 *)&g_pad_held_flags != 0) {
                snd_play_from_global_bank(4, 0, 0);
                self[0xBC] = 3;
            }
            return;
        case 2:
            g_race_state_flags = 0;
            o = 0;
            if (I(s, 0x1DC) != -1) {
                o = MOBY(I(s, 0x1DC));
            }
            if (o != 0) {
                H(o, 0x34) &= ~0x41;
                if (g_race_bike_child_moby != 0) {
                    H(g_race_bike_child_moby, 0x34) &= ~0x41;
                }
                Q(o, 0xd) = Q(self, 0xd);
                Q(o, 0xF0) = Q(self, 0xF0);
                o[0x30] = 0;
                anim_start_immediate(o, 0, 0);
                func_PAL_002A0F68(o);
                func_002A0F48(o);
            }
            H(self, 0x34) &= ~0x41;
            g_race_banner_timer = 0;
            g_race_warning_stage = 0;
            level_store_value_pair_pal(0, hud_draw_race_ruler);
            g_race_l04_state_flag_c_2 = 0;
            g_race_trick_state = 0;
            trail_clear_by_owner(0);
            g_race_bike_mode = 0;
            hoverbike_init_race_course(self);
            g_hero_state[0x22B5] = 1;
            I(P(g_hero_state, 0x2290), 0x98) = 0;
            if (g_race_voice_pending != 0) {
                self[0xBC] = 1;
                H(self, 0x96) = 100;
                g_race_voice_pending = 0;
                return;
            }
            self[0xBC] = 3;
        case 3:
            g_race_mode_active_flag = 0;
            racer_activate_linked(self);
            part_refresh_active_records(self);
            self[0xBC] = 4;
        case 4:
            hoverbike_update_rider_entry_state_pal(self, s);
            if (I(s, 0x394) < 100 && g_race_warning_stage == 0) {
                PlayMobySound(0xD, 0, self);
                g_race_warning_stage++;
            } else if (I(s, 0x394) < 75 && g_race_warning_stage == 1) {
                PlayMobySound(0xD, 0, self);
                g_race_warning_stage++;
            } else if (I(s, 0x394) < 50 && g_race_warning_stage == 2) {
                PlayMobySound(0xD, 0, self);
                g_race_warning_stage++;
            } else if (I(s, 0x394) < 25 && g_race_warning_stage == 3) {
                PlayMobySound(0xD, 0, self);
                g_race_warning_stage++;
            }
            math_fast_float_d(s + 0x394);
            if (I(s, 0x394) != 0) {
                return;
            }
            PlayMobySound(0xE, 0, self);
            self[0xBC] = 5;
            if (g_pad_pressed_flags & 0x40) {
                g_race_l04_state_flag_c_2 = 0;
            } else {
                g_race_l04_state_flag_c_2 = 1;
            }
            return;
        case 5:
            hoverbike_update_rider_entry_state_pal(self, s);
            if (g_race_state_flag_d != 0) {
                subtitle_request_voice_line_pal(0xA26, 0x7D);
                g_race_state_flag_d = 0;
            }
            if (race_update_player_progress_pal(self, s) != 0) {
                return;
            }
            hoverbike_update_rail_grind_trick_pal(self, s);
            gfx_add_draw_callback_third(racer_draw_glow_effects, self);
            if (F(self, 0x18) < F(s, 0x26C) || racer_is_in_jump_window(I(s, 0x314), I(s, 0x318), F(self, 0x18)) != 0) {
                racer_release_sound_handles(self, s);
                self[0xBC] = 6;
                H(self, 0x96) = 1;
            }
            if (g_race_voice_state == 0) {
                return;
            }
            FadeToBlack(0xd);
            race_reset_controller_pal(self, 1);
            I(s, 0x340) = 0;
            g_race_voice_state = 0;
            return;
        case 6:
            if (P(s, 0x4C4) != 0) {
                I(P(P(s, 0x4C4), 0x68), 0x1C0) = 0;
                P(s, 0x4C4) = 0;
            }
            if (I(s, 0x724) != 0) {
                I(s, 0x724) = 0;
            }
            I(s, 0x720) = 0;
            gfx_add_draw_callback_third(racer_draw_glow_effects, self);
            o = 0;
            I(s, 0x30C) = 0;
            I(s, 0x27C) = 0;
            if (I(s, 0x1DC) != -1) {
                o = MOBY(I(s, 0x1DC));
            }
            racer_release_sound_handles(self, s);
            if (o != 0) {
                H(o, 0x34) |= 0x41;
                if (g_race_bike_child_moby != 0) {
                    H(g_race_bike_child_moby, 0x34) |= 0x41;
                }
                F(o, 0x2C) = F(P(o, 0x24), 0x24) * 0.25f;
                H(o, 0x32) = 0x7F;
                o[0x31] = 1;
                Q(o, 0x10) = Q(self, 0x10);
                Q(o, 0xF0) = Q(self, 0xF0);
                o[0x30] = 0;
                func_PAL_002A0F68(o);
                func_002A0F48(o);
                H(o, 0x34) |= 6;
            }
            if (--H(self, 0x96) != 0) {
                return;
            }
            FadeToBlack(0xd);
            ids = (IdList *)(s + 0x110);
            id = ids->v[I(s, 0x270)];
            if (id != -1) {
                Q(a, 0) = Q(NODE(id), 0x30);
                Q(b, 0) = Q(NODE(ids->v[I(s, 0x270)]), 0x70);
            } else if (I(s, 0x198) == -1) {
                hero_record_play_counters_pal();
                return;
            } else {
                Q(a, 0) = Q(NODE(I(s, 0x198)), 0x30);
                Q(b, 0) = Q(NODE(I(s, 0x198)), 0x70);
            }
            g_level_float_setting = 1.0f;
            cam_set_transition_frames(8.0f);
            if (coll_test_point(a, 4, self, F(s, 0x20)) != 0) {
                Q(a, 0) = g_collision_quad;
            }
            racer_reset_state(self, 1);
            trail_clear_by_owner(self);
            hero_reset_position_and_direction_pal(a, b, 0x31, 1);
            g_hero_state[0x22B7] = 1;
            g_hero_state[0x22B5] = 1;
            I(s, 0x49C) = -1;
            I(s, 0x4A0) = -1;
            F(s, 0x4A4) = -1.0f;
            I(s, 0x4B0) = 0;
            I(s, 0x4A8) = 0;
            I(s, 0x4AC) = 0;
            Q(self, 0x10) = Q(a, 0);
            Q(self, 0xF0) = Q(b, 0);
            FindNearestRoutePoint(self, s, s + 0x314, s + 0x318, s + 0x310, g_current_lap);
            H(self, 0x34) &= ~0x41;
            if (o != 0) {
                Q(o, 0x10) = Q(self, 0x10);
                Q(o, 0xF0) = Q(self, 0xF0);
                anim_start_immediate(o, 0, 0);
                func_PAL_002A0F68(o);
                func_002A0F48(o);
                H(o, 0x34) &= ~0x41;
                if (g_race_bike_child_moby != 0) {
                    H(g_race_bike_child_moby, 0x34) &= ~0x41;
                }
            }
            self[0xBC] = 5;
            self[0x30] = 0xFF;
            H(self, 0x34) |= 0x400;
            return;
        }
        return;
    case 3:
        g_race_state_flags = 1;
        hoverbike_update_rider_entry_state_pal(self, s);
        g_race_extra_ticks++;
        if (F(self, 0x18) < F(s, 0x26C) || racer_is_in_jump_window(I(s, 0x314), I(s, 0x318), F(self, 0x18)) != 0) {
            float ahead, along;
            int node = FindNearestRoutePointIndex(self, P(s, 0x6D0), 1);

            /* The path's points are 16-byte records from +0x10. */
            Q(self, 0x10) = Q(((Vector *)P(s, 0x6D0))[node], 0x10);
            along = IntToFloat(node) * F(P(s, 0x6D0), 0x1C);
            if (g_race_bike_mode != 0) {
                ahead = along + 15.0f;
            } else {
                ahead = along + 5.0f;
            }
            F(s, 0x6D8) = ahead;
            anim_sample_key_track(ahead, F(P(s, 0x6D0), 0x1C), P(s, 0x6D0), s + 0x654, s + 0x6D4, s + 0x6A0);
            FindNearestRoutePoint(self, s, s + 0x314, s + 0x318, s + 0x310, g_current_lap);
        }
        level_store_value_pair_pal(0, DrawRaceStandingsHud);
        math_fast_float_d(s + 0x398);
        if (g_race_init_flag == 0) {
            if (I(s, 0x398) > 0 || !(g_pad_held_flags & 0x10)) {
                return;
            }
            g_race_init_flag = 1;
            g_race_float_param = 0.05f;
            g_race_state_value = 0;
        }
        if (g_race_state_value != 1) {
            return;
        }
        snd_send_cmd23(0x5D);
        snd_Pump();
        D_L04_001A8ED0_flags[5] = 0;
        racer_release_link_state(self, s);
        self[0x20] = 4;
        script_queue_keyed_request(I(s, 0x488), -1);
        return;
    case 4:
        g_race_state_flags = 1;
        I(g_hero_l04_state, 0x160) = 0;
        I(g_hero_l04_state, 0x168) = 0;
        I(g_hero_l04_state, 0x180) = 0;
        I(g_hero_l04_state, 0x188) = 0;
        I(g_hero_l04_state, 0x16C) = 0;
        if (g_race_init_flag == 0) {
            g_race_init_flag = 1;
            g_race_float_param = 0.05f;
            g_race_state_value = 0;
        }
        if ((unsigned int)(g_race_state_value - 1) >= 2) {
            return;
        }
        part_refresh_active_records(self);
        g_race_state_flags = 0;
        H(self, 0x34) &= ~0x41;
        level_store_value_pair_pal(0, 0);
        if (I(s, 0x19C) != -1) {
            if (I(s, 0x320) == -1 || (g_current_race_index == 0 && race_get_course_win_count(0) == 1)) {
                u8 *bike;

                path = I(s, 0x480);
                if (g_current_map_index == 11) {
                    path = I(s, 0x484);
                }
                Q(a, 0) = Q(NODE(I(s, 0x19C)), 0x70);
                if (g_level_l04_event_flag != 0) {
                    a[2] = 0.92f;
                }
                if (I(s, 0x320) == 1 && g_current_race_index == 0) {
                    g_current_race_index = I(s, 0x320);
                }
                if (g_race_bike_child_moby != 0) {
                    moby_mark_spawned(g_race_bike_child_moby);
                    g_race_bike_child_moby = 0;
                }
                bike = P(g_hero_state, 0x2290);
                g_hero_state[0x22B5] = 0;
                I(bike, 0x98) = I(P(bike, 0x24), 0x10);
                hero_reset_position_and_direction_pal(NODE(I(s, 0x19C)) + 0x30, a, 0, 1);
                {
                    u8 *ride = P(g_hero_state, 0x2290);

                    F(ride, 0x2C) = F(P(ride, 0x24), 0x24);
                }
                Q(self, 0x10) = Q(s, 0x2D0);
                Q(self, 0xF0) = Q(s, 0x2E0);
                self[0x20] = 1;
                F(self, 0x2C) = F(P(self, 0x24), 0x24);
                load_scene_chunk_pal(0, path);
                {
                    float q = math_fast_sin_or_cos_b(0.56217057f) / math_fast_sin_or_cos_a(0.56217057f);

                    g_projection_scale_float = q;
                }
                UpdateViewContext();
                for (k = 0; k < 21; k++) {
                    int id = ((int *)(s + 0x1E4))[k];

                    if (id != -1) {
                        u8 *rider = P(MOBY(id), 0x68);

                        I(rider, 0x2C8) = 0;
                        rider[0x251] = 0;
                        if (P(rider, 0x8C) != 0) {
                            moby_mark_spawned(P(rider, 0x8C));
                            P(rider, 0x8C) = 0;
                        }
                    }
                }
                return;
            }
            if (race_get_course_win_count(g_current_race_index) == 1) {
                g_current_race_index++;
                if (g_current_race_index >= 5) {
                    g_current_race_index = 4;
                }
            }
            race_reset_controller_pal(self, 1);
        } else {
            race_reset_controller_pal(self, 1);
            g_race_voice_state = 0;
        }
        return;
    }
}
