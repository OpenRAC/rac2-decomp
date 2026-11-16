#include "names.h"
/* func_PAL_L23_0041B350, the PAL copy of func_L23_00416388: the same C, where the hero
 * state written in state 4 becomes 8, the three frame counts are scaled to 50 Hz and the
 * age limit 40 becomes 33. Level 23 boss state update: a 21-way state switch, shared
 * cleanup and the attached-object tables. "Boss" is inferred from its behaviour. It reads
 * $gp data (hence -G8) and has its own jump table and constants, so it lives in a unit of
 * its own.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    char prefix[0x18]; u8 enabled, count, kind;
    char reserved[0x65]; u8 payload[1];
} DispatchContext;
typedef struct LvlSlotNode { char prefix[0x1c]; struct LvlSlotNode *next; } LvlSlotNode;
typedef struct LvlSlotCtx { char prefix[0x50]; LvlSlotNode *head; } LvlSlotCtx;
extern unsigned char g_hero_state[];
extern char g_hero_position[];
/* A partial resident view; the external byte array keeps its unknown full extent. */
typedef struct {
    u8 prefix[0x80];
    float position[4];
    u8 middle0[0x150];
    short state1e0;
    u8 middle1[0x168e];
    struct LvlSlotNode *slotList;
    u8 middle2[8];
    int slotCount;
    u8 middle3[0xa10];
    char *player;
    int field2294;
} ResidentHeroView;
extern u8 *g_mothership_crowd_mobys[];
extern float g_mothership_height_thresholds[] __attribute__((sda));
extern float g_mothership_surface_radius[] __attribute__((sda));
extern int g_enemy_relocate_count[] __attribute__((sda));
extern int g_boss_player_above_flag[] __attribute__((sda));
extern int g_boss_fight_timer[] __attribute__((sda));
extern int g_boss_camera_timer[] __attribute__((sda));
extern float g_player_target_point[4] __attribute__((sda));
extern float g_boss_hit_point[4] __attribute__((sda));
extern float g_boss_target_pos_a[4] __attribute__((sda));
extern float g_boss_target_pos_b[4] __attribute__((sda));
extern float g_boss_joint_world_pos[4] __attribute__((sda));
extern float g_boss_blended_world_pos[4] __attribute__((sda));
extern float g_camera_l23_position[];
extern Quad g_boss_part_transform_rows[] NOT_SDA;
extern Quad g_light_effect_table NOT_SDA;
extern Quad g_boss_part_zero_quad NOT_SDA;
extern float g_boss_part_back_offset_scale __attribute__((sda));
extern float g_boss_part_surface_radius_a __attribute__((sda));
extern float g_boss_part_back_offset_scale_b __attribute__((sda));
extern int g_boss_fade_duration_frames __attribute__((sda));
extern int g_boss_part_was_active __attribute__((sda));
extern int g_boss_part_mode_flag __attribute__((sda));
extern float g_boss_drift_active_flag __attribute__((sda));
extern float g_boss_part_third_position_scale __attribute__((sda));
extern int g_boss_part_age_counter __attribute__((sda));
extern int g_boss_part_timer_default __attribute__((sda));
extern int g_boss_part_timer __attribute__((sda));
extern int g_counter_effect_active __attribute__((sda));
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern float g_boss_hero_offset_scale_a __attribute__((sda));
extern float g_boss_hero_offset_scale_b __attribute__((sda));
extern float g_boss_first_measure_a __attribute__((sda));
extern float g_boss_first_measure_b __attribute__((sda));
extern float g_boss_second_measure_a __attribute__((sda));
extern float g_boss_second_measure_b __attribute__((sda));
extern float g_boss_second_measure_limit __attribute__((sda));
extern float g_boss_surface_height __attribute__((sda));
extern float g_boss_second_measure_c __attribute__((sda));
extern int g_boss_part_enable_value __attribute__((sda));
extern float g_boss_timer_base_value __attribute__((sda));
extern float g_boss_timer_value __attribute__((sda));
extern int g_boss_part_phase_value __attribute__((sda));
extern int g_boss_part_age_limit __attribute__((sda));
extern float g_boss_arena_radius __attribute__((sda));
extern int g_boss_part_sound_voice __attribute__((sda));
extern float g_boss_joint_vec_scale __attribute__((sda));
extern float g_boss_blend_position_length __attribute__((sda));
extern float g_boss_timer_mode_limit __attribute__((sda));
extern int g_boss_part_cooldown_frames __attribute__((sda));
extern int g_boss_half_time_frames __attribute__((sda));
extern int g_boss_part_index __attribute__((sda));
extern float g_boss_blast_range __attribute__((sda));
extern int g_charged_l23_blast_timer __attribute__((sda));
extern float g_mothership_max_health __attribute__((sda));
extern int g_boss_part_hit_counter[] __attribute__((sda));
extern int g_boss_player_seen_flag __attribute__((sda));

extern int math_fast_float_d(char *);
extern void FastVecScale(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern void FastVecSub(char *, char *, char *);
extern float FastVecLength(char *);
extern float fast_vec_dist(char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float gravity_get_center_distance(char *);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void moby_transform_joint_point(char *, int, char *);
extern void AttachManipulator(u8 *, unsigned int, u8 *);
extern void moby_set_state(u8 *, int, int);
extern float math_random_float_range(float, float);
extern int flag_set_first_pending(u8 *);
extern void mat_get_euler_angles(float *, float *);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int moby_dispatch_action_by_kind(void *, DispatchContext *);
extern void cancel_hero_item_animation_pal(void);
extern void release_moby_animation_slot(LvlSlotCtx *, LvlSlotNode **);
extern void moby_store_position_private(u8 *, void *);
extern int player_slot_has_object(unsigned int);
extern int charged_shot_get_for_owner(int);
extern void charged_shot_release(int, int);
extern int queue_copy_record_by_index(unsigned int);
extern int moby_check_target_point_from_offset(char *, void *);
extern void boss_turn_gun_toward_target_pal(char *);
extern void mothership_project_point_onto_surface(char *, float);
extern void mothership_update_gun_pick_target(char *);
extern void mothership_tick_timers(char *);
extern void mothership_relatch_first_measure(char *, float *);
extern void mothership_relatch_second_measure(char *, float *);
extern void mothership_mark_held(char *);
extern void mothership_set_timer_value(float);
extern void mothership_disable_part_flags(char *);
extern void mothership_free_effect_handles(void);
extern void mothership_spring_second_measure_pal(char *);
extern void mothership_clear_measure_flags(char *);
extern void mothership_ease_value_to_target_pal(char *);
extern void mothership_release_effect_handles(char *);
/* Action-helper inputs were checked against retail. Their discarded result
   declarations remain hypotheses where no deliberate result bank is observable. */
extern void mothership_update_pal(u8 *);
extern void mothership_fire_gun_at_target_pal(char *);
extern void FollowWaypointPath_pal(char *, float);
extern void mothership_update_shield_fade_pal(char *);
extern int UpdateAimTurn_pal(char *, char *);
extern int mothership_fire_weapon_pal(char *, char *);
extern void mothership_update_energy_barrier_pal(char *);
extern void boss_drift_along_path(char *);
extern void mothership_update_charged_blast_pal(char *);
extern void boss_update_effect_pools(char *);
extern void boss_update_damage_phases_pal(char *);
extern void object_copy_vector_to_selected(char *);
extern void cam_set_state_rotation(char *);
extern void SetCamera5Pose(char *, char *, int, int, void *);
extern char *SpawnExplosion_pal(char *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void FadeToBlack(int);
extern void moby_copy_joint_transform_to_object(u8 *, char *, int, int);
extern void hero_reset_position_and_direction_pal(char *, char *, int, int);
extern int hero_l22_set_action_pal(int, int);
extern char *effect_create_attached(char *, char *);
extern void build_axis_rotation_quaternion(char *, int, float);

/* Measured accesses to the boss's private state, not a claim about its complete type:
   each one is a member of the state structure. */
typedef struct { int value; } StateInt;
typedef struct { float value; } StateFloat;
typedef struct { u8 value; } StateByte;
typedef struct { char *value; } StatePointer;
/* The five attached objects listed at state + 0x358. */
typedef struct { char *entry[5]; } LinkTable;
#define S32(o) (((StateInt *)(state + (o)))->value)
#define SF(o) (((StateFloat *)(state + (o)))->value)
#define SB(o) (((StateByte *)(state + (o)))->value)
#define SP(o) (((StatePointer *)(state + (o)))->value)
#define FLAGS(p) (*(unsigned short *)((p) + 0x34))
#define AGE (*(unsigned short *)(object + 0x96))

/* Runs the Mothership boss part: keeps track of the hero, the aim point and the timers, then handles each boss state (flying, firing, hit, dying). (PAL) */
void mothership_boss_part_update_pal(u8 *object)
{
    char direction[16] __attribute__((aligned(16)));
    float joint_matrix[16] __attribute__((aligned(16)));
    char joint_offset[16] __attribute__((aligned(16)));
    char blended_position[16] __attribute__((aligned(16)));
    char local_position[16] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *joint_position;
    char *enemy;
    float height, distance;
    unsigned int mode;
    int was_active;

    mothership_update_pal(object);
    if (g_boss_part_age_counter > 200)
        return;
    g_boss_drift_active_flag = 0.0f;
    math_fast_float_d((char *)g_boss_fight_timer);
    was_active = S32(0x604);
    g_boss_part_was_active = was_active != 0;
    if (!was_active && S32(0x60c) != -1)
        g_counter_effect_active = 1;
    else
        g_counter_effect_active = 0;
    if (!g_mothership_boss_moby)
        return;
    boss_turn_gun_toward_target_pal((char *)object);
    S32(0x604) = 0;
    FastVecScale((char *)g_player_target_point, (((ResidentHeroView *)g_hero_state)->player) + 0xe0, g_boss_hero_offset_scale_a);
    FastVecAdd((char *)g_player_target_point, (char *)g_player_target_point, ((char *)((ResidentHeroView *)g_hero_state)->position));
    FastVecScale((char *)g_boss_hit_point, (((ResidentHeroView *)g_hero_state)->player) + 0xe0, g_boss_hero_offset_scale_b);
    FastVecAdd((char *)g_boss_hit_point, (char *)g_boss_hit_point, ((char *)((ResidentHeroView *)g_hero_state)->position));
    qcopy(state+(0x3f0),((char *)((ResidentHeroView *)g_hero_state)->position));
    mothership_project_point_onto_surface(state + 0x3f0, 0.0f);
    qcopy(state+(0x3e0),object + 0x10);
    mothership_project_point_onto_surface(state + 0x3e0, 0.0f);
    {
        float player_height = gravity_get_center_distance(((char *)((ResidentHeroView *)g_hero_state)->position)) - g_mothership_surface_radius[0];
        SF(0x5c0) = player_height;
        g_boss_player_above_flag[0] = SF(0x588) < player_height;
    }
    FastVecSub(direction, state + 0x3f0, state + 0x3e0);
    SF(0x5b8) = FastVecLength(direction);
    mothership_update_gun_pick_target((char *)object);
    SF(0x5bc) = fast_vec_dist(((char *)object + 0x10), ((char *)((ResidentHeroView *)g_hero_state)->position));
    moby_transform_joint_to_world((char *)object, 0x2a, joint_offset);
    moby_transform_joint_point((char *)object, 0x27, (char *)joint_matrix);
    FastVecScale((char *)g_boss_joint_world_pos, (char *)joint_matrix, g_boss_joint_vec_scale);
    FastVecAdd((char *)g_boss_joint_world_pos, (char *)g_boss_joint_world_pos, joint_offset);
    joint_position = (char *)joint_matrix + 0x30;
    FastVecSub(blended_position, (char *)g_player_target_point, joint_position);
    vec_scale_to_length(blended_position, blended_position, g_boss_blend_position_length);
    FastVecAdd((char *)g_boss_blended_world_pos, joint_position, blended_position);
    SB(0x404) = 0;
    if (SF(0x5bc) < g_boss_timer_mode_limit)
        SB(0x404) = !CollLine(g_boss_blended_world_pos, g_player_target_point, 0x10, (((ResidentHeroView *)g_hero_state)->player), 0);
    if (!(g_boss_half_time_frames / 2 < g_enemy_relocate_count[0])) {
        math_fast_float_d((char *)&g_boss_part_timer);
        if (object[0x20] == 7 &&
            (!SB(0x404) || !object[0x31] || g_boss_timer_base_value + 40.0f < SF(0x5bc)) &&
            !g_boss_part_timer && !S32(0x590)) {
            g_boss_part_timer = g_boss_part_timer_default;
            moby_set_state(g_mothership_crowd_mobys[g_boss_part_index], 6, 0);
            g_boss_part_index = (g_boss_part_index + 1) % 25;
        }
    }
    SB(0x405) = 0;
    mode = object[0x20];
    if (mode != 4 && (SF(0x5bc) < g_boss_timer_mode_limit || mode == 16) &&
        (SF(0x5b8) >= g_boss_blast_range || SF(0x5c0) <= SF(0x588)))
        SB(0x405) = moby_check_target_point_from_offset((char *)object, g_hero_position);
    mode = object[0x20];
    switch (mode) {
    case 0: goto state_default;
    case 4: goto state4;
    case 2: goto state2;
    case 3: goto state3;
    case 1: goto state1;
    case 7: goto state7;
    case 8: goto state8;
    case 9: goto state9;
    case 10: goto state10;
    case 11: goto state11;
    case 13: goto state13;
    case 14: goto state14;
    case 15: goto state15;
    case 12: goto state12;
    case 19: goto state19;
    case 5: goto state5;
    case 6: goto state6;
    case 16: goto state16;
    case 20: goto state20;
    default: goto state_default;
    }
state4:
    mothership_disable_part_flags((char *)object);
    ((ResidentHeroView *)g_hero_state)->state1e0 = 8;
    if (flag_set_first_pending(object)) {
        mothership_free_effect_handles();
        FadeToBlack(g_boss_fade_duration_frames);
    } else {
        char transform[64] __attribute__((aligned(16)));
        char second_position[16] __attribute__((aligned(16)));
        char third_position[16] __attribute__((aligned(16)));

        if (g_boss_fade_duration_frames / 2 < AGE) {
            boss_update_damage_phases_pal((char *)object);
        } else if (AGE == g_boss_fade_duration_frames / 2 - 4) {
            FadeToBlack(1);
            qcopy(transform+0x00,&g_boss_part_transform_rows[0]);
            qcopy(transform+0x10,&g_boss_part_transform_rows[1]);
            qcopy(transform+0x20,&g_boss_part_transform_rows[2]);
            qzero_nc(transform + 0x30);
            mat_get_euler_angles((float *)transform, (float *)local_position);
            SetCamera5Pose((char *)g_camera_l23_position, local_position, 1, 0, 0);
        } else if (g_boss_fade_duration_frames / 2 - 4 < AGE) {
            FadeToBlack(1);
            qcopy((transform + 0x00) ,(object + 0xc0));
            qcopy((transform + 0x10) ,(object + 0xd0));
            qcopy((transform + 0x20) ,(object + 0xe0));
            qzero_nc(transform + 0x30);
            mat_get_euler_angles((float *)transform, (float *)local_position);
            FastVecScale(second_position, (char *)object + 0xc0, -g_boss_part_back_offset_scale_b);
            FastVecAdd(second_position, second_position, ((char *)object + 0x10));
            mothership_project_point_onto_surface(second_position, 0.0f);
            hero_reset_position_and_direction_pal(second_position, local_position, 0x6f, 0);
            cam_set_state_rotation(local_position);
            FastVecScale(third_position, (char *)object + 0xc0, -g_boss_part_back_offset_scale);
            FastVecAdd(third_position, third_position, ((char *)object + 0x10));
            mothership_project_point_onto_surface(third_position, g_boss_part_surface_radius_a);
            object_copy_vector_to_selected(third_position);
            qzero(&g_boss_part_zero_quad);
            qzero(&g_light_effect_table);
        } else {
            FadeToBlack(1);
        }
    }
    ++AGE;
    return;
state2:
    if (flag_set_first_pending(object)) {
        mothership_relatch_first_measure((char *)object, &g_boss_first_measure_b);
        mothership_relatch_second_measure((char *)object, &g_boss_surface_height);
        if (!SB(0x4b1))
            AttachManipulator(object, 0x27, (u8 *)state + 0x4b0);
        SF(0x578) = 1.4726215600967407f;
        build_axis_rotation_quaternion(state + 0x4c0, 1, 1.4726215600967407f);
    }
    goto state_default;
state3:
    qcopy(state+(0x3d0),g_boss_target_pos_a);
    SP(0x400) = state + 0x3d0;
    FollowWaypointPath_pal((char *)object, SF(0x588));
    mothership_release_effect_handles((char *)object);
    moby_set_state(object, 7, 1);
    goto state_default;
state1:
    mothership_mark_held((char *)object);
    if (flag_set_first_pending(object)) {
        SP(0x400) = (char *)g_boss_target_pos_a;
        mothership_relatch_first_measure((char *)object, &g_boss_first_measure_b);
        mothership_relatch_second_measure((char *)object, &g_boss_second_measure_a);
    }
    if (fast_vec_dist(state + 0x3e0, (char *)g_boss_target_pos_a) < 10.0f)
        moby_set_state(object, 3, 0);
    else
        FollowWaypointPath_pal((char *)object, SF(0x588));
    goto state_default;
state7:
    mothership_mark_held((char *)object);
    math_fast_float_d(state + 0x608);
    if (flag_set_first_pending(object)) {
        mothership_relatch_first_measure((char *)object, &g_boss_first_measure_a);
        mothership_relatch_second_measure((char *)object, &g_boss_second_measure_a);
        mothership_set_timer_value(g_boss_timer_base_value + math_random_float_range(5.0f, 45.0f));
    }
    if (S32(0x60c) == -1) {
        moby_set_state(object, 6, 1);
        goto state_default;
    }
    if (!(g_boss_half_time_frames / 2 < g_enemy_relocate_count[0]) && !S32(0x608)) {
        if (g_boss_part_hit_counter[0] % 3 == 2)
            mothership_set_timer_value(g_boss_timer_base_value);
        else
            mothership_set_timer_value(g_boss_timer_base_value + math_random_float_range(25.0f, 55.0f));
        moby_set_state(object, 8, 1);
        ++g_boss_part_hit_counter[0];
    } else {
        boss_drift_along_path((char *)object);
        if (AGE % 480 == 0) {
            if (g_enemy_relocate_count[0] < 4)
                mothership_set_timer_value(g_boss_timer_base_value + 60.0f);
            else
                mothership_set_timer_value(g_boss_timer_base_value + math_random_float_range(-4.0f, 80.0f));
        }
    }
    goto state_default;
state8:
    mothership_mark_held((char *)object);
    flag_set_first_pending(object);
    if (g_boss_timer_value - 6.0f <= SF(0x5b8) && SF(0x5b8) <= g_boss_timer_value + 6.0f)
        moby_set_state(object, 9, 1);
    else
        boss_drift_along_path((char *)object);
    goto state_default;
state9:
    if (flag_set_first_pending(object)) {
        boss_drift_along_path((char *)object);
        mothership_relatch_second_measure((char *)object, &g_boss_second_measure_b);
        S32(0x598) = ((s32)g_boss_part_phase_value * 5 + 2) / 6;
        PlayMobySound(6, 0, (char *)object);
    } else if (S32(0x5d8)) {
        if (S32(0x598) <= 0) {
            moby_set_state(object, 10, 1);
        } else {
            if (S32(0x598) == ((s32)g_boss_part_phase_value * 5 + 2) / 6) {
                int next;
                int i;
                PlayMobySound(0, 0, (char *)object);
                next = g_boss_part_index;
                for (i = 0; i < 4; ++i) {
                    char joint_vector[16] __attribute__((aligned(16)));
                    float matrix[16] __attribute__((aligned(16)));
                    char third_position[16] __attribute__((aligned(16)));
                    char extra_position[16] __attribute__((aligned(16)));

                    enemy = (char *)g_mothership_crowd_mobys[next];
                    moby_set_state((u8 *)enemy, 2, 0);
                    next = (next + 1) % 25;
                    moby_transform_joint_to_world((char *)object, i + 30, joint_vector);
                    moby_transform_joint_point((char *)object, i + 30, (char *)matrix);
                    FastVecScale(local_position, (char *)matrix + 0x20, -16.0f);
                    qcopy_nc(extra_position, joint_vector);
                    mothership_project_point_onto_surface(extra_position, 0.0f);
                    FastVecSub(third_position, extra_position, state + 0x3e0);
                    FastVecScale(third_position, third_position, g_boss_part_third_position_scale);
                    FastVecAdd(local_position, local_position, third_position);
                    FastVecAdd(joint_vector, state + 0x3e0, local_position);
                    mothership_project_point_onto_surface(joint_vector, 0.0f);
                    qcopy((enemy + 0xc0) ,(object + 0xc0));
                    qcopy((enemy + 0xd0) ,(object + 0xd0));
                    qcopy((enemy + 0xe0) ,(object + 0xe0));
                    qcopy((enemy + 0x10) ,joint_vector);
                }
            }
            math_fast_float_d(state + 0x598);
        }
    }
    goto state_default;
state10:
    if (S32(0x60c) == -1)
        mothership_mark_held((char *)object);
    if (flag_set_first_pending(object))
        mothership_relatch_second_measure((char *)object, &g_boss_second_measure_a);
    if (SF(0x588) > g_boss_second_measure_limit) {
        int enable;
        int i;
        char **children;
        char **links;
        S32(0x598) = 0;
        S32(0x590) = 4;
        moby_set_state(object, 11, 1);
        enable = g_boss_part_enable_value;
        links = (char **)(state + 0x358);
        children = (char **)(state + 0x36c);
        for (i = 0; i < 5; ++i) {
            if (*children) {
                qcopy_nc(*children + 0xc0, *links + 0xc0);
                qcopy_nc(*children + 0xd0, *links + 0xd0);
                qcopy_nc(*children + 0xe0, *links + 0xe0);
                qcopy_nc(*children + 0x10, *links + 0x10);
                FLAGS(*children) &= 0xbff9;
                *(int *)(*children + 0x98) = *(int *)(*(char **)(*children + 0x24) + 0x10);
                if (enable)
                    FLAGS(*children) &= 0xffbe;
            }
            ++links;
            ++children;
        }
    }
    goto state_default;
state11:
    if (flag_set_first_pending(object))
        mothership_set_timer_value(g_boss_timer_base_value);
    if (S32(0x60c) == -1)
        mothership_mark_held((char *)object);
    if (S32(0x5d8) && !S32(0x598) && !S32(0x590)) {
        int i;
        char **children = (char **)(state + 0x36c);
        for (i = 0; i < 5; ++i, ++children) {
            if (*children) {
                *(int *)(*children + 0x98) = 0;
                FLAGS(*children) |= 0x41;
            }
        }
        S32(0x608) = g_boss_part_cooldown_frames;
        if (object[0x31] && SB(0x404)) {
            moby_set_state(object, 13, 2);
            g_boss_part_sound_voice = PlayMobySound(8, 4, (char *)object);
            g_boss_part_mode_flag = 0;
        } else {
            moby_set_state(object, 7, 1);
        }
    } else if (S32(0x590) && !S32(0x598)) {
        mothership_fire_gun_at_target_pal((char *)object);
    }
    boss_drift_along_path((char *)object);
    goto state_default;
state13:
    mothership_mark_held((char *)object);
    if (AGE)
        moby_set_state(object, 14, 2);
    boss_drift_along_path((char *)object);
    goto state_default;
state14:
    mothership_mark_held((char *)object);
    if (AGE >= 33)
        moby_set_state(object, 15, 2);
    boss_drift_along_path((char *)object);
    goto state_default;
state15:
    mothership_mark_held((char *)object);
    flag_set_first_pending(object);
    if (AGE >= 33) {
        if (g_boss_part_sound_voice != -1) {
            snd_stop_voice(g_boss_part_sound_voice);
            g_boss_part_sound_voice = -1;
        }
        moby_set_state(object, 7, 1);
    }
    goto state_default;
state12:
    if (!S32(0x598) && !S32(0x590)) {
        moby_set_state(object, 16, 2);
        S32(0x608) = g_boss_part_cooldown_frames;
    } else if (S32(0x590) && !S32(0x598)) {
        mothership_fire_gun_at_target_pal((char *)object);
    }
    goto state_default;
state19:
    if (flag_set_first_pending(object)) {
        mothership_relatch_second_measure((char *)object, &g_boss_second_measure_c);
    } else if (AGE > ((s32)g_boss_part_age_limit * 5 + 2) / 6) {
        moby_set_state(object, 7, 0);
    }
    if (SF(0x588) > g_mothership_height_thresholds[0])
        boss_drift_along_path((char *)object);
    goto state_default;
state5:
    if (flag_set_first_pending(object)) {
        SP(0x400) = (char *)g_boss_target_pos_b;
        mothership_relatch_first_measure((char *)object, &g_boss_first_measure_a);
    } else if (fast_vec_dist(state + 0x3e0, (char *)g_boss_target_pos_b) > 1.0f) {
        FollowWaypointPath_pal((char *)object, SF(0x588));
    } else {
        moby_set_state(object, 17, 2);
    }
    goto state_default;
state6:
    mothership_mark_held((char *)object);
    if (flag_set_first_pending(object)) {
        SP(0x400) = (char *)g_boss_target_pos_a;
        mothership_relatch_first_measure((char *)object, &g_boss_first_measure_a);
        mothership_relatch_second_measure((char *)object, &g_boss_second_measure_a);
    } else if (fast_vec_dist(state + 0x3e0, (char *)g_boss_target_pos_a) > 1.0f) {
        FollowWaypointPath_pal((char *)object, SF(0x588));
    } else {
        moby_set_state(object, 16, 2);
    }
    goto state_default;
state16:
    if (flag_set_first_pending(object))
        mothership_relatch_second_measure((char *)object, &g_boss_surface_height);
    if (g_boss_arena_radius + g_boss_arena_radius * 0.6200000047683716f < SF(0x5b8)) {
        mothership_release_effect_handles((char *)object);
        if (!S32(0x5b0)) {
            math_fast_float_d(state + 0x608);
            if (!(g_boss_half_time_frames / 2 < g_enemy_relocate_count[0]) && !S32(0x608)) {
                moby_set_state(object, 12, 2);
                S32(0x598) = 0;
                S32(0x590) = 4;
            }
        }
    } else if (!g_boss_player_seen_flag) {
        if (*(float *)(*(char **)(SP(0x610) + 0x68) + 0x20) < g_mothership_max_health ||
            SF(0x5b8) < g_boss_arena_radius * 0.5f) {
            mothership_update_energy_barrier_pal((char *)object);
            g_boss_player_seen_flag = 1;
        } else {
            math_fast_float_d(state + 0x608);
            if (!(g_boss_half_time_frames / 2 < g_enemy_relocate_count[0]) && !S32(0x608)) {
                moby_set_state(object, 12, 2);
                S32(0x598) = 0;
                S32(0x590) = 4;
            }
        }
    } else {
        mothership_update_energy_barrier_pal((char *)object);
    }
    goto state_default;
state20:
    mothership_release_effect_handles((char *)object);
    if (moby_dispatch_action_by_kind(object, (DispatchContext *)(state + 0x140)) & 1) {
        moby_set_state(object, 4, 0);
        ((ResidentHeroView *)g_hero_state)->field2294 = 0;
        cancel_hero_item_animation_pal();
        release_moby_animation_slot((LvlSlotCtx *)(((ResidentHeroView *)g_hero_state)->player), &((ResidentHeroView *)g_hero_state)->slotList);
        ((ResidentHeroView *)g_hero_state)->slotCount = 0;
        hero_l22_set_action_pal(0, 1);
        g_charged_l23_blast_timer = 0;
        return;
    }
state_default:
    S32(0x5a8) = 0;
    {
        int i;
        for (i = 0; i < 5; ++i) {
            char *child = SP(0x36c + i * 4);
            if (child && !*(unsigned short *)(child + 0x7c))
                *(unsigned short *)(child + 0x7c) = 0x3ff;
        }
    }
    boss_update_effect_pools((char *)object);
    mothership_tick_timers((char *)object);
    {
        int i;
        LinkTable *links = (LinkTable *)(state + 0x358);
        for (i = 0; i < 5; ++i) {
            if (links->entry[i]) {
                moby_copy_joint_transform_to_object(object, links->entry[i], i + 1, 0);
                FLAGS(links->entry[i]) &= 0xfff9;
                FLAGS(links->entry[i]) |= 0x4000;
            }
        }
    }
    if (SP(0x610)) {
        moby_copy_joint_transform_to_object(object, SP(0x610), 0x22, 0);
        FLAGS(SP(0x610)) &= 0xfff9;
        FLAGS(SP(0x610)) |= 0x800;
        if (S32(0x60c) == -1 && (object[0x20] == 16 || object[0x20] == 12))
            FLAGS(SP(0x610)) |= 0x4000;
        else
            FLAGS(SP(0x610)) &= 0xbfff;
    } else {
        FLAGS(object) |= 0x4000;
    }
    if (SP(0x614)) {
        moby_copy_joint_transform_to_object(object, SP(0x614), 0x22, 0);
        FLAGS(SP(0x614)) &= 0xfff9;
        FLAGS(SP(0x614)) &= 0xbfff;
        FLAGS(SP(0x614)) |= 0x100;
    }
    mothership_update_shield_fade_pal((char *)object);
    qcopy(local_position ,g_player_target_point);
    UpdateAimTurn_pal((char *)object, local_position);
    mothership_fire_weapon_pal((char *)object, local_position);
    mothership_update_charged_blast_pal((char *)object);
    if (!SP(0x40c))
        SP(0x40c) = effect_create_attached((char *)object, ((char *)object + 0x10));
    else
        moby_store_position_private((u8 *)SP(0x40c), ((char *)object + 0x10));
    mothership_spring_second_measure_pal((char *)object);
    if (g_boss_drift_active_flag != 0.0f)
        mothership_ease_value_to_target_pal((char *)object);
    else
        mothership_clear_measure_flags((char *)object);
    if (player_slot_has_object((unsigned int)(((ResidentHeroView *)g_hero_state)->player)) && g_boss_player_seen_flag &&
        (object[0x20] == 16 || object[0x20] == 12) && g_boss_arena_radius < SF(0x5bc)) {
        char *attachment = (char *)charged_shot_get_for_owner((int)(((ResidentHeroView *)g_hero_state)->player)) + 0x10;
        height = gravity_get_center_distance(attachment) - g_mothership_surface_radius[0];
        distance = fast_vec_dist(attachment, (char *)g_boss_target_pos_a);
        if (distance < g_boss_arena_radius * 0.6f && height < g_boss_surface_height - 2.0f) {
            SpawnExplosion_pal(attachment, 0, 15, 10, 15, 15, 15, 1, 2.0f, 20.0f, 0, 0, 0, 0);
            charged_shot_release((int)(((ResidentHeroView *)g_hero_state)->player), 1);
        }
    }
    math_fast_float_d((char *)&g_boss_camera_timer[0]);
    if (g_boss_camera_timer[0])
        queue_copy_record_by_index(0x2b);
}
