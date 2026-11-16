/* func_US2_L12_003E3838, the USA v2.00 copy of func_L12_003E2460: the same C, where rename func_002A6C58 becomes func_US2_002A7AA8; rename func_002AEB60 becomes func_US2_002AF9C8. */
/* func_US2_L12_003E3838: update of a path-following enemy (levels 12 and 17).
 * Own unit for its -G8 data, -ffast-math and jump tables.
 * The kill counter is read through two views of D_L12_001A79F0: the $gp view, and an incomplete
 * array whose unknown size gives the even arm its absolute lui/lw.
 */
#include "common.h"

typedef struct { float x, y, z, w; } L12Vector __attribute__((aligned(16)));

/* The path and combat portion of the object's private state. */
typedef struct {
    u8 prefix[0x1A8];
    int flags;
    u8 reserved1AC[0xB4];
    s16 idle_timer;
    s16 attack_timer;
    int path_index;
    int next_point;
    int destination;
    u8 *target_object;
    s16 alert_timer;
    s16 perception;
    int damage_state;
    u8 reserved27C[0x18];
    int *owner_slot;
    int grouped;
    s16 group_timer;
    s16 reserve_timer;
    int reserved2A0;
    int persistent;
    float minimum_height;
} L12PathEnemyState;

extern struct { u8 pad[0x464]; u8 flags[0]; } g_object_flags;
extern int D_L12_001A79F0_GP SDATA(D_L12_001A79F0);
extern u8 g_robot_guard_entry_flags[];
extern int g_hero_l12_control_mode[3] __attribute__((sda));
extern int g_robot_kill_counter[] __attribute__((sda));
extern u8 *g_path_zone_table[];
extern u8 g_robot_guard_effect_offset[8] __attribute__((sda));
extern float g_robot_guard_turn_speed __attribute__((sda));
extern float g_robot_guard_move_speed __attribute__((sda));
extern float g_robot_guard_state_value __attribute__((sda));
extern float g_robot_guard_time_limit __attribute__((sda));
extern float g_robot_guard_max_fall_speed __attribute__((sda));
extern float g_enemy_height_limit __attribute__((sda));
extern float g_robot_guard_height_offset __attribute__((sda));
extern float g_robot_guard_step_limit __attribute__((sda));
extern float g_robot_guard_climb_speed __attribute__((sda));
extern int g_robot_guard_effect_id __attribute__((sda));
extern float g_robot_guard_size_min __attribute__((sda));
extern float g_robot_guard_size_max __attribute__((sda));
extern float g_robot_guard_effect_type __attribute__((sda));
extern int g_robot_guard_effect_count __attribute__((sda));
extern char g_str_debug_ground_height[], g_str_debug_robot_guard[], g_str_debug_initial_distance[];
extern u8 g_zero_l12_vec[] __attribute__((sda));

extern void robot_guard_init_update_state(void *);
extern void group_try_claim_attack_slot(void *);
extern void group_release_attack_slot(void *);
extern void moby_init_state_byte(void *);
extern void enemy_choose_nearest_visible_path_point(void *);
extern void enemy_move_along_path_keep_height(void *);
extern int AdvanceAlongPath(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern int PlayMobySound(int, int, void *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void STUB_printf(char *, ...);
extern void SetDeathBits_us2(void *, int, int);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
/* Keeps state 21's transition from cross-jumping into state 23's call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeModeL12Patrol(void *, int, int) __asm__("func_002A7750");
extern void anim_start_blended(void *, int, int, int);
extern int flag_set_second_pending(void *);
extern int flag_set_first_pending(void *);
extern int FastDecTimer(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void moby_transform_joint_point(void *, int, void *);
extern void transform_vector(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern float mat_fast_helper_a(float, float);
extern void StepAngleTowardTarget(void *, int, float, float);
extern int moby_l01_turn_toward_target(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float fast_subtract_rotations(float, float);
extern float math_fabs(float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_is_value_within_step_us2(void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_ground_effect(void *, int, float, float, int, int, int, void *, int, float);
extern void FastVecSub(void *, void *, void *);
extern u8 *blast_projectile_spawn(void *, void *, void *, int, float);

/* Updates a path-following robot guard (levels 12 and 17): patrols, spots the hero, attacks and explodes when destroyed (v2.00 copy). */
void robot_guard_update_us2(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    L12Vector pos;
    u8 matrix[64] __attribute__((aligned(16)));
    L12Vector velocity;
    L12Vector target;
    float distance;
    float angle;
    float limit;
    int i, next;
    int forward, backward;

    if (((L12PathEnemyState *)state)->persistent) {
        u16 id = *(u16 *)(moby + 0xB2);
        int value;
        if (g_object_flags.flags[(s16)id])
            goto destroy;
        value = g_robot_guard_entry_flags[((s16)id >> 1) + (D_L12_001A79F0_GP << 10)];
        if (id & 1)
            value = (value >> 4) & 7;
        else
            value &= 7;
        if (value)
            goto destroy;
    }
    if (g_hero_l12_control_mode[0] == 2) {
        *(int *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        return;
    }
    if (moby[0x95] != 7) {
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
        *(int *)(moby + 0x98) = *(int *)(*(u8 **)(moby + 0x24) + 0x10);
    }
    robot_guard_init_update_state(moby);
    distance = vec_distance_xy(((L12PathEnemyState *)state)->target_object + 0x10, moby + 0x10);
    if (distance < 8.0f && !((L12PathEnemyState *)state)->damage_state) {
        ((L12PathEnemyState *)state)->damage_state = 3;
        ((L12PathEnemyState *)state)->alert_timer = 50;
    }
    if (((L12PathEnemyState *)state)->damage_state == 5) {
        PlayMobySound(3, 0, moby);
        SpawnExplosion((moby + 0x10), 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        if (((L12PathEnemyState *)state)->persistent) {
            u16 id = *(u16 *)(moby + 0xB2);
            if (id & 1) {
                if (((g_robot_guard_entry_flags[((s16)id >> 1) + (D_L12_001A79F0_GP << 10)] >> 4) & 7) != 7)
                    g_robot_guard_entry_flags[((s16)id >> 1) + (D_L12_001A79F0_GP << 10)] += 0x10;
            } else {
                if ((g_robot_guard_entry_flags[((s16)id >> 1) + (g_robot_kill_counter[0] << 10)] & 7) != 7)
                    g_robot_guard_entry_flags[((s16)id >> 1) + (g_robot_kill_counter[0] << 10)]++;
            }
        }
        goto deathFinish;
    } else if (((L12PathEnemyState *)state)->damage_state == 1 || ((L12PathEnemyState *)state)->damage_state == 5) {
        int damage;
        float oldAngle = *(float *)(moby + 0xF8);
        qcopy(&pos, (moby + 0x10));
        damage = moby_dispatch_action_by_kind(moby, state + 0x60);
        if (*(float *)(state + 0x218) >= g_robot_guard_time_limit * 0.01666666753590107f) {
            STUB_printf(g_str_debug_robot_guard);
            *(float *)(state + 0x218) = 0;
        }
        if (damage & 1) {
            PlayMobySound(3, 0, moby);
            SpawnExplosion((moby + 0x10), 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            if (((L12PathEnemyState *)state)->persistent) {
                u16 id = *(u16 *)(moby + 0xB2);
                if (id & 1) {
                    u8 *entry = g_robot_guard_entry_flags + (((s16)id >> 1) + (D_L12_001A79F0_GP << 10));
                    if (((*entry >> 4) & 7) != 7)
                        *entry += 0x10;
                } else {
                    u8 *entry = g_robot_guard_entry_flags + (((s16)id >> 1) + (g_robot_kill_counter[0] << 10));
                    if ((*entry & 7) != 7)
                        ++*entry;
                }
            }
deathFinish:
            SetDeathBits_us2(moby, 0, 3);
destroy:
            moby_mark_spawned(moby);
            return;
        }
        if (damage & 2)
            ((L12PathEnemyState *)state)->damage_state = 2;
        qcopy((moby + 0x10), &pos);
        *(float *)(moby + 0xF8) = oldAngle;
    }
    switch (moby[0x95]) {
    case 0:
        if (((L12PathEnemyState *)state)->perception == 1 || ((L12PathEnemyState *)state)->damage_state == 1 || ((L12PathEnemyState *)state)->damage_state == 2) {
            ((L12PathEnemyState *)state)->destination = ((L12PathEnemyState *)state)->next_point = -1;
            if (!((L12PathEnemyState *)state)->grouped) {
                moby_set_state(moby, 15, 5);
            } else {
                group_try_claim_attack_slot(moby);
                if (moby[0x20] != 15) {
                    moby_set_state(moby, 4, 10);
                    ((L12PathEnemyState *)state)->reserve_timer = 800;
                }
            }
        }
        break;
    case 7:
        i = ((L12PathEnemyState *)state)->perception;
        if (i == 1) {
            moby_set_state(moby, 3, 8);
            moby[0x31] = i;
            *(u16 *)(moby + 0x34) &= 0xFFFE;
        } else {
            moby[0x31] = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        break;
    case 9:
        flag_set_second_pending(moby);
        if (moby[0x20] == 23 && ((L12PathEnemyState *)state)->damage_state != 1) {
            moby_set_state(moby, 4, -1);
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 20);
        }
        if (FastDecTimer(state + 0x29E)) {
            group_release_attack_slot(moby);
            moby_set_state(moby, 4, 10);
            if (moby[0x43] != 3)
                anim_start_blended(moby, 3, 0, 20);
        } else if (((L12PathEnemyState *)state)->damage_state == 1 && moby[0x20] == 4) {
            moby_set_state(moby, 15, 5);
            ((L12PathEnemyState *)state)->group_timer = 150;
        }
        break;
    case 10:
        if (flag_set_second_pending(moby))
            enemy_choose_nearest_visible_path_point(moby);
        if ((moby[0x60] & 2) && moby[0x42] != 2 && moby[0x43] != 2)
            anim_start_blended(moby, 2, 0, 20);
        group_try_claim_attack_slot(moby);
        if (((L12PathEnemyState *)state)->damage_state == 1) {
            moby_set_state(moby, 15, 5);
            ((L12PathEnemyState *)state)->group_timer = 150;
        } else {
            if (((L12PathEnemyState *)state)->perception == 1 || ((L12PathEnemyState *)state)->damage_state)
                ((L12PathEnemyState *)state)->idle_timer = 250;
            if (((L12PathEnemyState *)state)->perception == 0 && ((L12PathEnemyState *)state)->damage_state == 0 && FastDecTimer(state + 0x260)) {
                if (moby[0x43] != 0)
                    anim_start_blended(moby, 0, 0, 20);
                moby_set_state(moby, 5, 0);
            }
        }
        break;
    case 5:
        if (flag_set_second_pending(moby)) {
            float turn = g_robot_guard_turn_speed * 0.00027777778450399637f;
            float speed = g_robot_guard_move_speed * 0.01666666753590107f;
            *(float *)(state + 0x198) = g_robot_guard_state_value;
            moby_set_controller_speed_limits(moby, turn, speed, 0.0017453294713050127f, 0.20943954586982727f);
            ((L12PathEnemyState *)state)->flags |= 0x10;
        }
        if (((L12PathEnemyState *)state)->damage_state == 3) {
            if (moby[0x95] != 15)
                moby_set_state(moby, moby[0x20], 6);
            flag_set_first_pending(moby);
        }
        if (((L12PathEnemyState *)state)->grouped && FastDecTimer(state + 0x29C) && ((L12PathEnemyState *)state)->damage_state != 1) {
            moby_init_state_byte(moby);
            break;
        }
        moby_transform_joint_point(moby, 2, matrix);
        transform_vector(&pos, g_robot_guard_effect_offset, matrix);
        if (moby[0x95] != 15 && CollLine(&pos, state + 0x130, 2, moby, 0)) {
            moby_set_state(moby, moby[0x20], 6);
            flag_set_first_pending(moby);
        }
        if (((L12PathEnemyState *)state)->perception == 1 || ((L12PathEnemyState *)state)->damage_state)
            ((L12PathEnemyState *)state)->idle_timer = 250;
        if (((L12PathEnemyState *)state)->perception == 0 && ((L12PathEnemyState *)state)->damage_state == 0 && FastDecTimer(state + 0x260)) {
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 20);
            moby_set_state(moby, 5, 0);
            break;
        }
        {
            u8 *other = ((L12PathEnemyState *)state)->target_object;
            angle = mat_fast_helper_a(*(float *)(other + 0x10) - *(float *)(moby + 0x10),
                                  *(float *)(other + 0x14) - *(float *)(moby + 0x14));
            StepAngleTowardTarget(moby + 0xF8, 0, angle, 0.10471977293491364f);
        }
        break;
    case 6: {
        u8 *path;
        int flags;
        float oldZ, ground, angle;
        if (flag_set_second_pending(moby)) {
            u8 *initialPath;
            float initialDistance;
            ((L12PathEnemyState *)state)->destination = -1;
            initialPath = g_path_zone_table[*(int *)(state + 0x158)];
            enemy_choose_nearest_visible_path_point(moby);
            initialDistance = fast_vec_dist((moby + 0x10), initialPath + 0x10 + (((L12PathEnemyState *)state)->path_index << 4));
            if (initialDistance > 0.5f)
                STUB_printf(g_str_debug_initial_distance, (double)initialDistance);
        }
        if (*(int *)(state + 0x16C)) {
            enemy_move_along_path_keep_height(moby);
            break;
        }
        path = g_path_zone_table[*(int *)(state + 0x158)];
        if (*(long long *)(state + 0x268) == -1) {
            ((L12PathEnemyState *)state)->next_point = -1;
            i = ((L12PathEnemyState *)state)->path_index - 1;
            next = ((L12PathEnemyState *)state)->path_index + 1;
            if (i < 0)
                i = *(int *)path - 1;
            if (next == *(int *)path)
                next = 0;
            if (i >= 0 && !CollLine(path + 0x10 + i * 16, state + 0x130, 2, 0, 0))
                ((L12PathEnemyState *)state)->destination = i;
            if (((L12PathEnemyState *)state)->destination == -1) {
                if (next < *(int *)path && !CollLine(path + 0x10 + next * 16, state + 0x130, 2, 0, 0))
                    ((L12PathEnemyState *)state)->destination = next;
                if (((L12PathEnemyState *)state)->destination == -1) {
                    int j;
                    for (j = i - 1; j >= 0; j--) {
                        if (!CollLine(path + 0x10 + j * 16, state + 0x130, 2, 0, 0)) {
                            ((L12PathEnemyState *)state)->destination = j;
                            break;
                        }
                    }
                    if (((L12PathEnemyState *)state)->destination == -1) {
                        for (i = next + 1; i < *(int *)path; i++) {
                            if (!CollLine(path + 0x10 + i * 16, state + 0x130, 2, 0, 0)) {
                                ((L12PathEnemyState *)state)->destination = i;
                                break;
                            }
                        }
                        if (((L12PathEnemyState *)state)->destination == -1) {
                            moby_set_state(moby, moby[0x20], 5);
                            flag_set_first_pending(moby);
                            break;
                        }
                    }
                }
            }
            forward = ((L12PathEnemyState *)state)->destination - ((L12PathEnemyState *)state)->path_index;
            if (forward < 0)
                { int t = forward - 1; forward = t + *(int *)path; }
            backward = ((L12PathEnemyState *)state)->path_index - ((L12PathEnemyState *)state)->destination;
            if (backward < 0)
                { int t = backward - 1; backward = t + *(int *)path; }
            ((L12PathEnemyState *)state)->next_point = forward < backward ? ((L12PathEnemyState *)state)->path_index + 1 : ((L12PathEnemyState *)state)->path_index - 1;
            if (((L12PathEnemyState *)state)->next_point < 0)
                ((L12PathEnemyState *)state)->next_point = *(int *)path - 1;
            if (((L12PathEnemyState *)state)->next_point == *(int *)path)
                ((L12PathEnemyState *)state)->next_point = 0;
        }
        {
            u8 *other = ((L12PathEnemyState *)state)->target_object;
            angle = mat_fast_helper_a(*(float *)(other + 0x10) - *(float *)(moby + 0x10),
                                  *(float *)(other + 0x14) - *(float *)(moby + 0x14));
            StepAngleTowardTarget(moby + 0xF8, 0, angle, 6.000000476837158f);
        }
        oldZ = *(float *)(moby + 0x18);
        *(float *)(state + 0x218) = 0;
        flags = moby_l01_turn_toward_target(moby, path + 0x10 + (((L12PathEnemyState *)state)->next_point << 4));
        ground = coll_probe_ground_height_below((moby + 0x10), 0, 0.5f);
        if (flags & 0x20) {
            if (!*(int *)(state + 0x248) || *(float *)(moby + 0x18) - ground > g_enemy_height_limit)
                *(float *)(moby + 0x18) = oldZ;
            else if (*(float *)(moby + 0x18) < ((L12PathEnemyState *)state)->minimum_height)
                *(float *)(moby + 0x18) = ((L12PathEnemyState *)state)->minimum_height;
            else
                STUB_printf(g_str_debug_ground_height, (double)(*(float *)(moby + 0x18) - coll_probe_ground_height_below((moby + 0x10), 0, 0.5f)), *(s16 *)(moby + 0xB2));
        }
        if (*(float *)(moby + 0x18) < *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) - *(float *)(moby + 0x18) > 0.8f) {
            *(float *)(moby + 0x18) += g_robot_guard_climb_speed * 0.01666666753590107f;
            if (*(float *)(moby + 0x18) < ground)
                *(float *)(moby + 0x18) = ground;
        }
        if (*(float *)(moby + 0x18) > *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) - *(float *)(moby + 0x18) < -0.8f) {
            *(float *)(moby + 0x18) -= g_robot_guard_climb_speed * 0.01666666753590107f;
            if (*(float *)(moby + 0x18) < ground)
                *(float *)(moby + 0x18) = ground;
        }
        if (flags & 0x80) {
            if (((L12PathEnemyState *)state)->destination == ((L12PathEnemyState *)state)->next_point) {
                ((L12PathEnemyState *)state)->path_index = ((L12PathEnemyState *)state)->next_point;
                ((L12PathEnemyState *)state)->next_point = -1;
                moby_set_state(moby, moby[0x20], 5);
                flag_set_first_pending(moby);
            } else {
                forward = ((L12PathEnemyState *)state)->destination - ((L12PathEnemyState *)state)->next_point;
                ((L12PathEnemyState *)state)->path_index = ((L12PathEnemyState *)state)->next_point;
                if (forward < 0)
                    { int t = forward - 1; forward = t + *(int *)path; }
                backward = ((L12PathEnemyState *)state)->next_point - ((L12PathEnemyState *)state)->destination;
                if (backward < 0)
                    { int t = backward - 1; backward = t + *(int *)path; }
                ((L12PathEnemyState *)state)->next_point = forward < backward ? ((L12PathEnemyState *)state)->next_point + 1 : ((L12PathEnemyState *)state)->next_point - 1;
                if (((L12PathEnemyState *)state)->next_point < 0)
                    ((L12PathEnemyState *)state)->next_point = *(int *)path - 1;
                if (((L12PathEnemyState *)state)->next_point == *(int *)path)
                    ((L12PathEnemyState *)state)->next_point = 0;
            }
        }
        break;
    }
    }
    switch (moby[0x20]) {
    case 5:
        if (flag_set_first_pending(moby)) {
            ((L12PathEnemyState *)state)->flags = (((L12PathEnemyState *)state)->flags & ~0x10) | 1;
            *(float *)(state + 0x198) = g_robot_guard_state_value * 0.5f;
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 20);
            ((L12PathEnemyState *)state)->attack_timer = 150;
        }
        if (FastDecTimer(state + 0x262)) {
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 20);
            moby_set_state(moby, 21, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            moby_set_controller_speed_limits(moby, 0.008888889104127884f, 0.5333333611488342f, 0.10471977293491364f, 0.10471977293491364f);
            ((L12PathEnemyState *)state)->flags = (((L12PathEnemyState *)state)->flags & ~0x10) | 1;
            *(int *)(state + 0x168) = 1;
        }
        if (AdvanceAlongPath(moby, g_path_zone_table[*(int *)(state + 0x164)])) {
            moby_set_state(moby, 5, 0);
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 0);
            ((L12PathEnemyState *)state)->flags |= 0x10;
        }
        break;
    case 21: {
        u8 *path;
        int flags;
        float oldZ, ground, heightLimit;
        path = g_path_zone_table[*(int *)(state + 0x158)];
        if (flag_set_first_pending(moby)) {
            int nextIndex = ((L12PathEnemyState *)state)->path_index + 1;
            if (nextIndex == *(int *)path)
                ((L12PathEnemyState *)state)->next_point = 0;
            else
                ((L12PathEnemyState *)state)->next_point = nextIndex;
            enemy_choose_nearest_visible_path_point(moby);
        }
        if (*(int *)(state + 0x16C))
            enemy_move_along_path_keep_height(moby);
        oldZ = *(float *)(moby + 0x18);
        *(float *)(state + 0x218) = 0;
        flags = moby_l01_turn_toward_target(moby, path + 0x10 + (((L12PathEnemyState *)state)->next_point << 4));
        ground = coll_probe_ground_height_below((moby + 0x10), 0, 0.5f);
        if (flags & 0x20) {
            if (!*(int *)(state + 0x248) || *(float *)(moby + 0x18) - ground > g_enemy_height_limit)
                *(float *)(moby + 0x18) = oldZ;
            else if (*(float *)(moby + 0x18) < ((L12PathEnemyState *)state)->minimum_height)
                *(float *)(moby + 0x18) = ((L12PathEnemyState *)state)->minimum_height;
            else
                STUB_printf(g_str_debug_ground_height, (double)(*(float *)(moby + 0x18) - coll_probe_ground_height_below((moby + 0x10), 0, 0.5f)), *(s16 *)(moby + 0xB2));
            heightLimit = *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) < oldZ ? *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) : oldZ;
            if (*(float *)(moby + 0x18) < heightLimit)
                *(float *)(moby + 0x18) = heightLimit;
        }
        if (*(float *)(moby + 0x18) < *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) - *(float *)(moby + 0x18) > 0.8f) {
            *(float *)(moby + 0x18) += g_robot_guard_climb_speed * 0.01666666753590107f;
            if (*(float *)(moby + 0x18) < ground)
                *(float *)(moby + 0x18) = ground;
        }
        if (*(float *)(moby + 0x18) > *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) &&
            *(float *)(path + (((L12PathEnemyState *)state)->next_point << 4) + 0x18) - *(float *)(moby + 0x18) < -0.8f) {
            *(float *)(moby + 0x18) -= g_robot_guard_climb_speed * 0.01666666753590107f;
            if (*(float *)(moby + 0x18) < ground)
                *(float *)(moby + 0x18) = ground;
        }
        if (flags & 0x80) {
            ((L12PathEnemyState *)state)->attack_timer = 200;
            ((L12PathEnemyState *)state)->path_index = ((L12PathEnemyState *)state)->next_point;
            if (moby[0x43] != 0)
                anim_start_blended(moby, 0, 0, 20);
            changeModeL12Patrol(moby, 5, -1);
        }
        break;
    }
    case 15:
        if (flag_set_first_pending(moby)) {
            ((L12PathEnemyState *)state)->attack_timer = 40;
            if (moby[0x43] != 8)
                anim_start_blended(moby, 8, 0, 20);
            moby_set_controller_speed_limits(moby, g_robot_guard_turn_speed * 0.000034722223062999546f,
                          g_robot_guard_move_speed * 0.0020833334419876337f,
                          0.10471977293491364f, 0.10471977293491364f);
            *(float *)(state + 0x198) = g_robot_guard_state_value * 0.25f;
        }
        if (FastDecTimer(state + 0x262) || (distance < 4.0f && ((L12PathEnemyState *)state)->attack_timer < 20)) {
            float turn = g_robot_guard_turn_speed * 0.00027777778450399637f;
            float speed = g_robot_guard_move_speed * 0.01666666753590107f;
            *(float *)(state + 0x198) = g_robot_guard_state_value;
            moby_set_controller_speed_limits(moby, turn, speed, 0.0017453294713050127f, 0.20943954586982727f);
            if (moby[0x43] != 7)
                anim_start_blended(moby, 7, 0, 20);
            ((L12PathEnemyState *)state)->attack_timer = 20;
            moby_set_state(moby, 16, -1);
        } else {
            moby_transform_joint_point(moby, 2, matrix);
            transform_vector(&pos, g_robot_guard_effect_offset, matrix);
            goto smoke;
        }
        break;
    case 16:
        if (flag_set_first_pending(moby))
            PlayMobySound(3, 0, moby);
        moby_transform_joint_point(moby, 2, matrix);
        transform_vector(&pos, g_robot_guard_effect_offset, matrix);
        angle = mat_fast_helper_a(*(float *)(state + 0x130) - *(float *)(moby + 0x10),
                              *(float *)(state + 0x134) - *(float *)(moby + 0x14));
        if (math_fabs(fast_subtract_rotations(*(float *)(moby + 0xF8), angle)) > 0.174532949924469f) {
            float speed = vec_distance_xy(&pos, (moby + 0x10));
            vec_scale_to_length(&velocity, moby + 0xC0, speed * 0.01666666753590107f);
            velocity.z = (*(float *)(state + 0x138) - pos.z) * 0.01666666753590107f;
        }
        if (!math_is_value_within_step_us2(moby, g_robot_guard_step_limit)) {
smoke:
            limit = math_random_float_range(g_robot_guard_size_min, g_robot_guard_size_max);
            i = math_random_int_below(g_robot_guard_effect_count);
            part_spawn_ground_effect(&pos, (int)g_robot_guard_effect_type, limit * 0.3f, limit,
                         g_robot_guard_effect_id, 0, i, g_zero_l12_vec, 0, 0.0f);
            break;
        }
        if (math_fabs(fast_subtract_rotations(*(float *)(moby + 0xF8), angle)) > 0.174532949924469f) {
            vec_scale_to_length(&velocity, moby + 0xC0, 0.5333333611488342f);
            velocity.z = (*(float *)(state + 0x138) - pos.z + g_robot_guard_height_offset) * 0.01666666753590107f;
        } else {
            qcopy(&target, state + 0x130);
            target.z += g_robot_guard_height_offset;
            FastVecSub(&velocity, &target, &pos);
            vec_scale_to_length(&velocity, &velocity, 0.5333333611488342f);
        }
        if (velocity.z > g_robot_guard_max_fall_speed * 0.01666666753590107f)
            velocity.z = g_robot_guard_max_fall_speed * 0.01666666753590107f;
        else if (velocity.z < -100.0f)
            velocity.z = -100.0f;
        blast_projectile_spawn(moby, &velocity, &pos, 0, (float)state[0x34]);
        ((L12PathEnemyState *)state)->attack_timer = 50;
        moby_set_state(moby, 23, -1);
        break;
    case 23:
        if (FastDecTimer(state + 0x262))
            moby_set_state(moby, 15, -1);
        if (((L12PathEnemyState *)state)->attack_timer < 30 && moby[0x42] != 3 && moby[0x43] != 3)
            anim_start_blended(moby, 3, 0, 20);
        if (vec_distance_xy(state + 0x130, (moby + 0x10)) < 8.0f && ((L12PathEnemyState *)state)->attack_timer < 35) {
            if (moby[0x43] != 7)
                anim_start_blended(moby, 7, 0, 20);
            moby_set_state(moby, 16, -1);
        }
        break;
    case 24:
        if (flag_set_first_pending(moby) && moby[0x43] != 9)
            anim_start_blended(moby, 9, 0, 20);
        if (math_is_value_within_step_us2(moby, 12.5f))
            *(int *)(moby + 0x48) = 0;
        break;
    }
}
