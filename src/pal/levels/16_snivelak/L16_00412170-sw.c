#include "include_asm.h"

#include "common.h"
typedef int BossQuadword __attribute__((mode(TI)));
typedef struct {
    u8 reserved00[0x20];
    float health;
    short max_health;
    u8 reserved26[15];
    u8 power;
    u8 reserved36[0x142];
    int entry_area;
    u8 reserved17c[0x18];
    int exit_area;
    u8 reserved198[0x24];
    int intro_started;
    u8 reserved1c0[0x30];
    u8 *body;
    u8 reserved1f4[12];
    float destination[4];
    float last_player[4];
    u8 reserved220[0x14];
    float turn_velocity;
    u8 *arms[2];
    int active_arm;
    int fired;
    int reserved248;
    u8 *target;
    float aim_time;
    float aim_blend;
    int reserved258;
    int aim_timeout;
    int reserved260;
    float floor_height;
    float vertical_speed;
    int body_mode;
    int resume_state;
    int resume_argument;
    u8 reserved278[0xa8];
    u8 taunted;
    u8 reserved321[0x2f];
    int suppress_speech;
    int reserved354[2];
    int fire_timer;
    u8 *projectile;
    short left_used;
    short right_used;
    int attack_sound;
    int body_sound;
} SnivelakBossState;
typedef union {
    float bone[16];
    struct { float position[4], offset[4]; } vectors;
} BossWork;
typedef struct {
    u8 prefix[0x30];
    int field30, field34, field38, field3c, field40, field44;
} BarlowUtilityQueueView;
typedef int HeroTI __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; HeroTI q[0x260]; } Hero;
extern char g_hero_state[];
extern u8 g_game_flag_table[];
extern u8 g_sound_state[];
extern BarlowUtilityQueueView g_request_l16_queue;
extern int g_snivelak_state;
extern u8 *g_snivelak_target __attribute__((sda));
extern float g_snivelak_path_speed_a __attribute__((sda));
extern float g_snivelak_path_speed_b __attribute__((sda));
extern float g_snivelak_path_slot_arg_a __attribute__((sda));
extern float g_snivelak_path_slot_arg_b __attribute__((sda));
extern float g_snivelak_aim_time __attribute__((sda));
extern float g_snivelak_aim_decay_rate __attribute__((sda));
extern unsigned int g_frame_l16_counter;
extern float g_snivelak_room_fade;
extern float g_scene_origin_transform[4];
extern void UpdateSnivelakBossDamage_pal(u8 *);
extern int IsPointInCuboid(void *, int);
extern int req_push_queue(u8 *, int);
extern int req_launch_queued(BarlowUtilityQueueView *);
extern void game_set_stored_value_pair(int, int);
extern int game_is_either_mode_two(void);
extern void snivelak_finish_boss_intro_state_pal(u8 *);
extern void snivelak_clean_up_boss_and_free_pal(u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern int flag_set_first_pending(u8 *);
extern void anim_play_on_self_or_child(u8 *, int, int, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float vec_distance_squared_xy(void *, void *);
extern void snd_play_unplayed_voice_line_pal(u8 *, int, int);
extern void snivelak_find_closest_path_point(u8 *, void *);
extern void snivelak_move_along_path_pal(u8 *, float);
extern float vec_distance_xy(void *, void *);
extern float moby_get_anim_value(char *);
extern float math_fabs(float);
extern int PlayMobySound(int, int, char *);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void snd_stop_voice(int);
extern void RequestVoiceLine_pal(u8 *, int);
extern void snivelak_fire_body_shots_pal(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_approach_target_with_direction_mode(float *, float, float, float, float, float *, int);
extern int math_fast_float_d(int *);
extern void snivelak_drop_falling_shot_pal(u8 *);
extern int snd_start_in_slot(int, int, int);
extern void snivelak_fire_arm_shot_pal(u8 *);
extern void path_pick_new_slot(u8 *, float, float);
extern void snivelak_switch_fly_hover_state_pal(u8 *);
extern void anim_start_blended_pal(u8 *, int, int, int);
extern float ApproachValue(float *, float, float);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void snivelak_draw_laser_beam_pal(void *);
extern int coll_sweep_from_object(u8 *, void *, int, int, int, int, float, float, float);
extern u8 *snivelak_spawn_rock_projectile_pal(u8 *, int);
extern void snivelak_fire_lobbed_shot_pal(u8 *);
extern void moby_transform_joint_point(char *, int, char *);
extern int coll_is_behind_surface(u8 *);
extern void snivelak_attach_child_to_parent_pose(u8 *, u8 *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float weapon_compute_shot_launch_speed(void *, void *, float *, float, float);
extern void snivelak_launch_projectile_pal(u8 *, void *, float);
extern float math_random_signed_float_range(float, float), math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_blast_effect_moby_pal(u8 *, void *, void *, float);
extern void transition_arm_shared(int, float, float);
extern void SetMobyAndGroupsEnabled(u8 *, int);
extern void snivelak_part_update(u8 *);
extern void snivelak_copy_bones_to_children(u8 *);

/* Advances the boss's arena, animation, aiming and projectile phases. */
void snivelak_update_pal(u8 *moby)
{
    u8 *attack_rec, *attack_end_rec, *death_attack_rec, *death_body_rec, *body_rec, *body_stop_rec;
    SnivelakBossState *state = *(SnivelakBossState **)(moby + 0x68);
    BossWork work;
    float velocity[4] __attribute__((aligned(16)));
    float angle, distance, frame, swing_frame, gravity;
    u8 *flags;
    float *turn_heading, *fire_heading, *arm_heading, *recover_heading, *lob_heading, *lob_fire_heading, *death_heading;
    int next, attack_end_sound, death_attack_sound, death_body_sound, body_stop_sound;
    UpdateSnivelakBossDamage_pal(moby);
    if (!moby || moby[0x20] == 254 || moby[0x20] == 253) return;

    switch (moby[0x95]) {
    case 0:
        if (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x20], state->entry_area) ||
            (IsPointInCuboid(&((Hero *)g_hero_state)->f[0x20], state->exit_area) && g_game_flag_table[0x83] == 1)) {
            flags = g_game_flag_table;
            if (!flags[0x83]) {
                if (req_push_queue((u8 *)&g_request_l16_queue, 132)) {
                    req_launch_queued(&g_request_l16_queue);
                    game_set_stored_value_pair((int)snivelak_finish_boss_intro_state_pal, (int)moby);
                    flags[0x83] = 1;
                    state->intro_started = 1;
                }
            } else if (!game_is_either_mode_two()) {
                snivelak_finish_boss_intro_state_pal(moby);
            }
        } else if ((*(unsigned short *)(moby + 0x34) & 1) && ((Hero *)g_hero_state)->f[0x20] >= 610.0f) {
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xffbe) | 0x1000;
            *(int *)(moby + 0x98) = *(int *)(*(u8 **)(moby + 0x24) + 0x10);
            if (state->body) {
                *(unsigned short *)(state->body + 0x34) &= 0xffbe;
                *(unsigned short *)(state->body + 0x34) |= 0x1000;
                *(int *)(state->body + 0x98) = *(int *)(*(u8 **)(state->body + 0x24) + 0x10);
            }
            if (state->arms[0]) {
                *(unsigned short *)(state->arms[0] + 0x34) &= 0xffbe;
                *(unsigned short *)(state->arms[0] + 0x34) |= 0x1000;
                *(int *)(state->arms[0] + 0x98) = *(int *)(*(u8 **)(state->arms[0] + 0x24) + 0x10);
            }
            if (state->arms[1]) {
                *(unsigned short *)(state->arms[1] + 0x34) &= 0xffbe;
                *(unsigned short *)(state->arms[1] + 0x34) |= 0x1000;
                *(int *)(state->arms[1] + 0x98) = *(int *)(*(u8 **)(state->arms[1] + 0x24) + 0x10);
            }
        }
        break;
    case 1:
        if (g_snivelak_target) {
            state->target = g_snivelak_target;
            moby_set_state(moby, 7, 2);
        }
        break;
    case 2:
        if (!g_snivelak_target) moby_set_state(moby, 2, 1);
        break;
    }
    if (g_snivelak_state == 2) return;

    switch (moby[0x20]) {
    case 1:
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 10, 12, 3.0f);
            if (!math_random_int_below(1)) {
                if (vec_distance_squared_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x20]) > 1600.0f)
                    snd_play_unplayed_voice_line_pal(moby, 3, 6);
                else snd_play_unplayed_voice_line_pal(moby, 7, 11);
            }
        }
        snivelak_find_closest_path_point(moby, &((Hero *)g_hero_state)->f[0x20]);
        snivelak_move_along_path_pal(moby, g_snivelak_path_speed_a * 0.020000001f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 32.0f) {
            frame = moby_get_anim_value((char *)moby);
            if (math_fabs(frame - 5.0f) < 1.0f || math_fabs(frame - 21.0f) < 1.0f) {
                PlayMobySound(8, 0, (char *)moby);
                moby_set_state(moby, 3, -1);
            }
        }
        snivelak_switch_fly_hover_state_pal(moby);
        break;
    case 16:
        if (flag_set_first_pending(moby)) state->vertical_speed = 0.0f;
        state->vertical_speed -= 0.012f;
        *(float *)(moby + 0x18) += state->vertical_speed;
        if (*(float *)(moby + 0x18) <= state->floor_height) {
            *(float *)(moby + 0x18) = state->floor_height;
            PlayMobySound(9, 0, (char *)moby);
            moby_set_state(moby, state->resume_state, state->resume_argument);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            PlayMobySound(9, 0, (char *)moby);
            anim_play_on_self_or_child(moby, 3, 12, 6.0f);
            if (!math_random_int_below(1)) snd_play_unplayed_voice_line_pal(moby, 12, 15);
        }
        if (!state->taunted && !state->suppress_speech && !math_random_int_below(2) &&
            ((Hero *)g_hero_state)->i[0x8A5] == 22 && ((Hero *)g_hero_state)->i[0x6E] == 1 && ((u8 *)((Hero *)g_hero_state)->ptr[0x927]) &&
            *(short *)(((u8 *)((Hero *)g_hero_state)->ptr[0x927]) + 0xaa) == 0xea7) {
            state->taunted = 1;
            RequestVoiceLine_pal(moby, 16);
        }
        if ((g_frame_l16_counter & 15) == (((int)moby >> 8) & 15)) snivelak_fire_body_shots_pal(moby);
        snivelak_find_closest_path_point(moby, &((Hero *)g_hero_state)->f[0x20]);
        if (((Hero *)g_hero_state)->i[0x8A5] == 129) moby_set_state(moby, 6, -1);
        else if (vec_distance_xy(moby + 0x10, state->destination) > 48.0f) moby_set_state(moby, 2, -1);
        else if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x20]) < 12.0f &&
                 math_fabs(((Hero *)g_hero_state)->f[0x22] - state->floor_height) < 10.0f) moby_set_state(moby, 5, -1);
        else {
            angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
            if (FastDiffRots(*(float *)(moby + 0xf8), angle) > 0.26179942f) moby_set_state(moby, 4, -1);
            else if (*(unsigned short *)(moby + 0x96) > 750) {
                moby_set_state(moby, 11, -1);
                state->target = 0;
                qcopy(state->last_player, &((Hero *)g_hero_state)->f[0x34]);
            }
        }
        snivelak_switch_fly_hover_state_pal(moby);
        break;
    case 4:
        if (flag_set_first_pending(moby)) {
            angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
            if (fast_subtract_rotations(*(float *)(moby + 0xf8), angle) > 0.0f)
                anim_play_on_self_or_child(moby, 10, 25, 1.0f);
            else
                anim_play_on_self_or_child(moby, 10, 25, 10.0f);
        }
        turn_heading = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(turn_heading, angle, 0.0025132746f, 0.0025132746f, 0.12566373f, &state->turn_velocity, 0);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xf8), angle) < 0.087266475f && moby[0x42] == moby[0x43]) moby_set_state(moby, 3, -1);
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            state->vertical_speed = 0.0f;
            state->body_mode = 1;
            state->fire_timer = 25;
            anim_play_on_self_or_child(moby, 0, 25, state->vertical_speed);
        }
        fire_heading = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(fire_heading, angle, 0.0012566373f, 0.0012566373f, 0.12566373f, &state->turn_velocity, 0);
        if (math_fast_float_d(&state->fire_timer)) {
            snivelak_drop_falling_shot_pal(moby);
            snd_start_in_slot(17, 0, (int)moby);
            state->fire_timer = ((s32)(math_random_int_range(45, 75)) * 5 + 2) / 6;
        }
        if (vec_distance_xy(moby + 0x10, &((Hero *)g_hero_state)->f[0x20]) > 16.0f || math_fabs(((Hero *)g_hero_state)->f[0x22] - state->floor_height) > 10.0f) moby_set_state(moby, 2, -1);
        break;
    case 6:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 16, 25, 0.0f);
            *(float *)(moby + 0x48) = 0.666f;
        }
        if (state->body[0x60] & 2) moby_set_state(moby, 2, -1);
        break;
    case 8:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, state->active_arm + 11, 17, 0.0f);
            if (!state->suppress_speech) snd_play_unplayed_voice_line_pal(moby, 17, 23);
            state->fired = 0;
            *(float *)(moby + 0x48) = 1.0f;
        }
        arm_heading = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(arm_heading, angle, 0.005026549f, 0.005026549f, 0.25132746f, &state->turn_velocity, 0);
        if (!state->fired && state->body[0x42] == state->body[0x43] && moby_get_anim_value((char *)state->body) >= 13.0f) {
            if (state->body[0x42] == 11) PlayMobySound(7, 0, (char *)moby);
            snivelak_fire_arm_shot_pal(moby);
            state->fired = 1;
        } else if (moby_get_anim_value((char *)state->body) > 20.0f) {
            anim_play_on_self_or_child(moby, state->active_arm + 11, 17, 0.0f);
            state->fired = 0;
        }
        if (*(unsigned short *)(moby + 0x96) > 250) moby_set_state(moby, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 10, 25, 6.0f);
            path_pick_new_slot(moby, g_snivelak_path_slot_arg_a, g_snivelak_path_slot_arg_b);
        }
        snivelak_move_along_path_pal(moby, g_snivelak_path_speed_b * 0.020000001f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 1.0f) moby_set_state(moby, 8, -1);
        snivelak_switch_fly_hover_state_pal(moby);
        break;
    case 9:
        if (flag_set_first_pending(moby)) anim_play_on_self_or_child(moby, 16, 25, 6.0f);
        recover_heading = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(recover_heading, angle, 0.005026549f, 0.005026549f, 0.25132746f, &state->turn_velocity, 0);
        if (state->body[0x60] & 2) {
            if ((float)state->max_health * 0.55f <= state->health) moby_set_state(moby, 10, -1);
            else if (math_random_int_below(2) || !state->left_used || !state->right_used) moby_set_state(moby, 13, -1);
            else moby_set_state(moby, 10, -1);
        }
        break;
    case 10:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 10, 25, 6.0f);
            snivelak_find_closest_path_point(moby, state->target + 0x10);
        }
        snivelak_move_along_path_pal(moby, g_snivelak_path_speed_b * 0.020000001f);
        if (vec_distance_xy(moby + 0x10, state->destination) < 1.0f) {
            if (math_fabs(*(float *)(state->target + 0x18) - 120.0f) < 1.0f) moby_set_state(moby, 12, -1);
            else moby_set_state(moby, 11, -1);
        }
        break;
    case 11:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != 22) anim_start_blended_pal(moby, 22, 0, 17);
            anim_start_blended_pal(state->body, 3, 0, 25);
            state->aim_timeout = 100;
            state->aim_time = g_snivelak_aim_time;
            state->aim_blend = 0.0f;
            state->vertical_speed = 0.0f;
        }
        if (state->target) {
            angle = mat_fast_helper_a(*(float *)(state->target + 0x10) - *(float *)(moby + 0x10), *(float *)(state->target + 0x14) - *(float *)(moby + 0x14));
        } else {
            angle = mat_fast_helper_a(state->last_player[0] - *(float *)(moby + 0x10), state->last_player[1] - *(float *)(moby + 0x14));
        }
        math_approach_target_with_direction_mode((float *)(moby + 0xf8), angle, 0.005026549f, 0.005026549f, 0.25132746f, &state->turn_velocity, 0);
        if (FastDiffRots(angle, *(float *)(moby + 0xf8)) < 0.087266475f) {
            ApproachValue(&state->aim_time, 0.0f, g_snivelak_aim_decay_rate * 0.020000001f);
            ApproachValue(&state->aim_blend, 1.0f, 0.080000006f);
            attack_rec = g_sound_state + state->attack_sound * 112;
            if (*(u8 **)(attack_rec + 0x88) != state->body || !attack_rec[0x74])
                state->attack_sound = PlayMobySound(2, 4, (char *)state->body);
            gfx_add_draw_callback_first(snivelak_draw_laser_beam_pal, moby);
        }
        if ((state->target && (*(unsigned short *)(state->target + 0x34) & 1) && math_fast_float_d(&state->aim_timeout)) || (!state->target && state->aim_time <= 0.0f)) {
            moby_set_state(moby, 3, 1);
            attack_end_sound = state->attack_sound;
            if (attack_end_sound != -1) {
                attack_end_rec = g_sound_state + attack_end_sound * 112;
                if (*(u8 **)(attack_end_rec + 0x88) == state->body && attack_end_rec[0x74]) snd_stop_voice(attack_end_sound);
            }
            state->attack_sound = -1;
        }
        break;
    case 12:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 1, 25, 0.0f);
            *(float *)(moby + 0x48) = 0.5f;
        }
        angle = mat_fast_helper_a(*(float *)(state->target + 0x10) - *(float *)(moby + 0x10), *(float *)(state->target + 0x14) - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode((float *)(moby + 0xf8), angle, 0.005026549f, 0.005026549f, 0.25132746f, &state->turn_velocity, 0);
        swing_frame = moby_get_anim_value((char *)moby);
        if (swing_frame > 30.0f) ApproachValue((float *)(moby + 0x48), 1.0f, 0.16000001f);
        if (swing_frame > 40.0f && swing_frame < 42.0f) coll_sweep_from_object(moby, state->target + 0x10, 0x10001, 0, 1, 0, 4.0f, (float)state->power, 1.0f);
        if (moby[0x60] & 2) moby_set_state(moby, 2, 1);
        else if (((Hero *)g_hero_state)->i[0x8A5] == 22 && ((Hero *)g_hero_state)->i[0x6E] == 1 && ((u8 *)((Hero *)g_hero_state)->ptr[0x927]) == moby) snd_play_unplayed_voice_line_pal(moby, 24, 27);
        break;
    case 13:
        if (flag_set_first_pending(moby)) {
            state->vertical_speed = 0.0f;
            state->body_mode = 1;
            anim_play_on_self_or_child(moby, 0, 25, state->vertical_speed);
            if (state->left_used == state->right_used) {
                state->projectile = !math_random_int_below(2) ? 0 : snivelak_spawn_rock_projectile_pal(moby, 1);
            } else if (!state->left_used) state->projectile = snivelak_spawn_rock_projectile_pal(moby, 1);
            else state->projectile = 0;
        }
        lob_heading = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(lob_heading, angle, 0.005026549f, 0.005026549f, 0.25132746f, &state->turn_velocity, 0);
        if (*(float *)(moby + 0x18) > state->floor_height + 20.0f) {
            if (state->projectile) { moby_set_state(moby, 14, -1);
            state->left_used = 1; }
            else { moby_set_state(moby, 15, -1);
            state->right_used = 1; }
        }
        break;
    case 15:
        if (flag_set_first_pending(moby)) anim_play_on_self_or_child(moby, 14, 25, 0.0f);
        lob_fire_heading = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(lob_fire_heading, angle, 0.005026549f, 0.005026549f, 0.25132746f, &state->turn_velocity, 0);
        if (state->body[0x42] == state->body[0x43] && (g_frame_l16_counter & 15) == (((int)moby >> 8) & 15)) snivelak_fire_lobbed_shot_pal(moby);
        if (*(unsigned short *)(moby + 0x96) > 150) moby_set_state(moby, 2, 1);
        break;
    case 14:
        if (flag_set_first_pending(moby)) anim_play_on_self_or_child(moby, 6, 25, 0.0f);
        moby_transform_joint_point((char *)state->body, 3, (char *)work.bone);
        switch (state->body[0x43]) {
        case 6:
            if (coll_is_behind_surface(state->projectile)) {
                snivelak_attach_child_to_parent_pose(state->projectile, (u8 *)work.bone);
                anim_play_on_self_or_child(moby, 7, 5, 0.0f);
            }
            break;
        case 7:
            snivelak_attach_child_to_parent_pose(state->projectile, (u8 *)work.bone);
            if (state->body[0x60] & 2) anim_play_on_self_or_child(moby, 9, 5, 0.0f);
            break;
        case 9:
            if (state->projectile) {
                snivelak_attach_child_to_parent_pose(state->projectile, (u8 *)work.bone);
                if (state->body[0x42] == 9 && moby_get_anim_value((char *)state->body) > 16.0f) {
                    gravity = 0.002f;
                    distance = vec_distance_xy(state->projectile + 0x10, state->target + 0x10) * 0.01f;
                    FastVecSub(velocity, state->target + 0x10, state->projectile + 0x10);
                    velocity[2] = 0.0f;
                    vec_scale_to_length(velocity, velocity, distance);
                    velocity[2] = weapon_compute_shot_launch_speed(state->projectile + 0x10, state->target + 0x10, 0, distance, -gravity);
                    snivelak_launch_projectile_pal(state->projectile, velocity, gravity);
                    state->projectile = 0;
                }
            }
            if (state->body[0x60] & 2) moby_set_state(moby, 2, 1);
            break;
        }
        break;
    case 17:
        if (flag_set_first_pending(moby)) {
            anim_play_on_self_or_child(moby, 16, 25, 0.0f);
            *(float *)(moby + 0x48) = 0.5f;
            state->body_mode = 1;
            if (state->vertical_speed < 0.0f) state->vertical_speed = 0.0f;
            death_attack_sound = state->attack_sound;
            if (death_attack_sound != -1) {
                death_attack_rec = g_sound_state + death_attack_sound * 112;
                if (*(u8 **)(death_attack_rec + 0x88) == state->body && death_attack_rec[0x74]) snd_stop_voice(death_attack_sound);
            }
            state->attack_sound = -1;
            death_body_sound = state->body_sound;
            if (death_body_sound != -1) {
                death_body_rec = g_sound_state + death_body_sound * 112;
                if (*(u8 **)(death_body_rec + 0x88) == moby && death_body_rec[0x74]) snd_stop_voice(death_body_sound);
            }
            state->body_sound = -1;
        }
        death_heading = (float *)(moby + 0xf8);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->f[0x20] - *(float *)(moby + 0x10), ((Hero *)g_hero_state)->f[0x21] - *(float *)(moby + 0x14));
        math_approach_target_with_direction_mode(death_heading, angle, 0.0025132746f, 0.0025132746f, 0.12566373f, &state->turn_velocity, 0);
        if ((g_frame_l16_counter & 15) == (((int)moby >> 8) & 15)) {
            *(BossQuadword *)work.vectors.offset = 0;
            work.vectors.offset[0] = math_random_signed_float_range(0.0f, 6.0f);
            work.vectors.offset[1] = math_random_signed_float_range(0.0f, 6.0f);
            work.vectors.offset[2] = math_random_float_range(5.0f, 20.0f);
            {
                BossQuadword q = *(BossQuadword *)work.vectors.offset;
                *(BossQuadword *)work.vectors.position = q;
            }
            FastVecAdd(work.vectors.position, work.vectors.position, moby + 0x10);
            FastVecSub(work.vectors.offset, g_scene_origin_transform, work.vectors.position);
            vec_scale_to_length(work.vectors.offset, work.vectors.offset, 1.0f);
            part_spawn_blast_effect_moby_pal(moby, work.vectors.position, work.vectors.offset, 0.0f);
            snd_play_from_class_bank(6, 0, (char *)moby, 0xf78);
        }
        if (state->body[0x42] == state->body[0x43] && state->body[0x41] > 29) transition_arm_shared(5, 5.0f, 15.0f);
        if (g_snivelak_room_fade >= 1.0f) {
            moby_set_state(moby, 18, -1);
            moby[0x31] = 0;
            *(unsigned short *)(moby + 0x34) |= 1;
            state->body_mode = 0;
        }
        break;
    case 18:
        *(float *)(moby + 0x48) = 0.1f;
        *(float *)(state->body + 0x48) = 0.1f;
        state->body_mode = 0;
        state->vertical_speed -= 0.008f;
        *(float *)(moby + 0x18) += state->vertical_speed;
        if (*(unsigned short *)(moby + 0x96) > 75 && g_game_flag_table[0x83] != 2 && req_push_queue((u8 *)&g_request_l16_queue, 133)) {
            moby_set_state(moby, 19, -1);
            req_push_queue((u8 *)&g_request_l16_queue, 17);
            req_push_queue((u8 *)&g_request_l16_queue, 134);
            req_launch_queued(&g_request_l16_queue);
            game_set_stored_value_pair((int)snivelak_clean_up_boss_and_free_pal, (int)moby);
        }
        break;
    case 19:
        if (flag_set_first_pending(moby)) {
            *(int *)(moby + 0x98) = 0;
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xefff;
            *(unsigned short *)(state->body + 0x34) |= 0x41;
            *(unsigned short *)(state->body + 0x34) &= 0xefff;
            *(int *)(state->body + 0x98) = 0;
            *(unsigned short *)(state->arms[0] + 0x34) |= 0x41;
            *(unsigned short *)(state->arms[0] + 0x34) &= 0xefff;
            *(int *)(state->arms[0] + 0x98) = 0;
            *(unsigned short *)(state->arms[1] + 0x34) |= 0x41;
            *(unsigned short *)(state->arms[1] + 0x34) &= 0xefff;
            *(int *)(state->arms[1] + 0x98) = 0;
        }
        if (g_snivelak_state == 2) SetMobyAndGroupsEnabled(moby, 0);
        break;
    }
    snivelak_part_update(moby);
    snivelak_copy_bones_to_children(moby);
    if (state->body_mode) {
        body_rec = g_sound_state + state->body_sound * 112;
        if (*(u8 **)(body_rec + 0x88) != moby || !body_rec[0x74])
            state->body_sound = PlayMobySound(10, 4, (char *)moby);
    } else {
        body_stop_sound = state->body_sound;
        if (body_stop_sound != -1) {
            body_stop_rec = g_sound_state + body_stop_sound * 112;
            if (*(u8 **)(body_stop_rec + 0x88) == moby && body_stop_rec[0x74])
                snd_stop_voice(body_stop_sound);
        }
        state->body_sound = -1;
    }
}
