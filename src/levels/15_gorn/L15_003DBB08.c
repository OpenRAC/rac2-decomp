#include "names.h"
/* func_L15_003DBB08 (5,824 bytes), ported from its twin func_L02_003CB0F0. The last spot, in case 11, was
 * D_L15_001B2148's absolute macro read (lui $v1; lw $v1 in one register, before the sra of
 * self): the sda incomplete-array declaration at -G0 gives it (docs/build/compiler-notes.md), and
 * retail compares the table value first.
 * The shape (big13): case bodies of the second switch in jump-table address order;
 * every state change written out per arm (retail cross-jumps the func_002A7750 tails); hero
 * fields through D_00189E20 directly (no resident pointer, which cost $s5 and the 0xC0 frame);
 * switch statements for the func_002A77E0 choices; retail's compare senses and arm orders;
 * case 10's own contact local and the collision record through L02Collision *col;
 * func_002B1C20 returns int; func_L02_00401530 is (p, p, p, float, float, float, int, int, int);
 * one frame area with two views (union work) for case 21's matrix, as func_L16_0040ECC0 does.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
struct L02NearObject;
struct L02GroupObject;
extern char g_hero_state[] NOT_SDA;
typedef struct { char pad[0x18]; char *hit; int count; } L02Collision;
extern L02Collision D_L15_001BFC00;
extern char *D_L15_001FE480[];
extern int D_L15_001B2148[] __attribute__((sda));
extern int linked_child_update(char *), moby_compute_aligned_direction(char *, void *);
extern void moby_update_glow_pulse_timers(char *), turret_l02_aim_at_hero(char *), moby_set_random_spread_velocity(char *, void *), linked_effect_update(char *);
extern void moby_delay_group_except_nearest(struct L02NearObject *), moby_randomize_group_timers(struct L02GroupObject *), moby_teleport_to_new_pose(char *, void *, void *);
extern u8 *moby_find_group_in_state_13(int);
extern void moby_mark_spawned(void *), moby_set_state(u8 *, int, int), anim_start_blended(char *, int, int, int), SetDeathBits(char *, void *, int);
extern int flag_set_first_pending(u8 *), flag_set_second_pending(u8 *), math_random_int_below(int), math_random_int_range(int, int), FastDecTimer(short *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void part_queue_moby_for_glow(char *, int, void (*)(char *));
/* The retail wrapper forwards B50E0's GPR flags. */
extern int moby_l01_turn_toward_target(char *, char *), moby_start_effect_from_entry(int, float), moby_move_to_target_temp_limits(void *, void *, int, float, float, float), moby_check_target_point_from_offset(char *, void *);
extern float mat_fast_helper_a(float, float), FastDiffRots(float, float), fast_vec_dist(void *, void *), vec_distance_xy(void *, void *), math_fabs(float), FastVecDot(void *, void *), moby_get_anim_value(char *);
extern int CollLine(void *, void *, int, char *, void *), moby_is_in_special_class_range(char *), math_is_value_within_step(char *, float), IsPointInCuboid(void *, int), path_follow_nodes(char *, char *), coll_check_object_inside_polygon(u8 *);
extern int coll_test_hit_at_bone(float, float, float, void *, void *, int, int, int, int);
extern void moby_transform_joint_point(char *, int, char *), moby_transform_joint_to_world(char *, int, char *), FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float), FastVecScale(void *, void *, float);
extern void *part_spawn_trail_effect_moby(void *, void *, void *, float, float, float, int, int, int);
/* Runs a ranged enemy's patrol, attack, group coordination and projectile states. */
/* This is a view of observed fields, not the complete resident allocation. */
typedef struct {
    u8 prefix[0x80]; Vector position_80; u8 gap_90[0x40]; Vector target_d0;
    u8 gap_e0[0x21B0]; char *pointer_2290; u8 gap_2294[8]; int mode_229c;
    u8 gap_22a0[0x1FC]; char *pointer_249c;
} L02_ResidentCombatPrefix;
void ranged_l15_enemy_update(char *moby) {
    /* One frame area, two layouts: the aiming states and the case-21 hand-off. */
    union {
        struct { Vector muzzle, velocity, acceleration, transform[4]; } aim;
        struct { Vector frame[4], direction, origin; } relay;
    } work;
    char *vars = *(char **)(moby + 0x68), *pathData, *relayTarget;
    L02Collision *hitRecord;
    int moveFlags;
    float angle, animTime, shotPower;

    int choice, animation, collision, contact;
    if (linked_child_update(moby)) { moby_mark_spawned(moby); return; }
    switch (((u8 *)moby)[0x95]) {
    case 0:
        if (flag_set_second_pending((u8 *)moby)) moby_set_controller_speed_limits((u8 *)moby, 0.0011111111380159855f, 0.050000004f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(vars + 0x204) == 1) {
            if (*(int *)(vars + 0x33C)) { *(int *)(vars + 0x33C) = 0; moby_set_state((u8 *)moby, 8, 2); }
            else moby_set_state((u8 *)moby, 10, 2);
        } else if (*(short *)(vars + 0x382)) {
            moby_set_state((u8 *)moby, 3, 1); *(short *)(vars + 0x382) = 0; *(short *)(vars + 0x374) = math_random_int_range(480, 600);
        }
        break;
    case 1:
        if (flag_set_second_pending((u8 *)moby)) moby_set_controller_speed_limits((u8 *)moby, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(vars + 0x204) == 1) moby_set_state((u8 *)moby, 10, 2);
        else if (!*(short *)(vars + 0x374)) {
            if (vec_distance_xy(moby + 0x10, &((L02_ResidentCombatPrefix *)g_hero_state)->position_80) > 26) moby_set_state((u8 *)moby, 1, 0);
            else *(short *)(vars + 0x374) = 120;
        }
        break;
    case 2:
        if (flag_set_second_pending((u8 *)moby)) {
            moby_delay_group_except_nearest((struct L02NearObject *)moby);
            moby_set_controller_speed_limits((u8 *)moby, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        }
        if (*(int *)(vars + 0x204) != 1 && (((u8 *)moby)[0x60] & 2) && ((u8 *)moby)[0x20] != 11) {
            if (fast_vec_dist(moby + 0x10, vars + 0x340) > 4) moby_set_state((u8 *)moby, 6, -1);
            else {
                switch (math_random_int_below(4)) {
                case 0: moby_set_state((u8 *)moby, 3, 1); break;
                case 1: moby_set_state((u8 *)moby, 4, 1); break;
                case 2: moby_set_state((u8 *)moby, 5, 1); break;
                case 3: moby_set_state((u8 *)moby, 7, 1); break;
                }
            }
            *(short *)(vars + 0x374) = math_random_int_range(580, 600);
        }
        break;
    case 3:
        moveFlags = moby_dispatch_action_by_kind(moby, vars + 0x50);
        if (moveFlags & 1) {
            *(u16 *)(*(char **)(vars + 0x370) + 0x34) |= 0x41; *(u16 *)(*(char **)(vars + 0x370) + 0x34) &= 0xEFFF; *(int *)(*(char **)(vars + 0x370) + 0x98) = 0;
            SetDeathBits(moby, 0, 3); part_queue_moby_for_glow(moby, 0, linked_effect_update); return;
        }
        if (moveFlags & 2) {
            *(int *)(vars + 0x33C) = 0;
            if (*(int *)(vars + 0x320) != -1) moby_set_state((u8 *)moby, 18, 4);
            else if (*(int *)(vars + 0x204) == 1) moby_set_state((u8 *)moby, 10, 2);
            else { moby_set_state((u8 *)moby, 3, 1); *(short *)(vars + 0x374) = math_random_int_range(580, 600); }

        }
        break;
    case 4:
        if (flag_set_second_pending((u8 *)moby)) {
            moby_set_controller_speed_limits((u8 *)moby, 0.0033333334140479565f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f); *(float *)(vars + 0x134) = 0.25f;
        }
        break;
    }
    switch (((u8 *)moby)[0x20]) {
    case 1:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43]) anim_start_blended(moby, 0, 0, 20);
        if (!(((u8 *)moby)[0x60] & 2)) break;
        if (!math_random_int_below(4)) { moby_set_state((u8 *)moby, 5, -1); break; }
        else if (!*(int *)(vars + 0x33C)) { moby_set_state((u8 *)moby, 2, -1); break; }
        break;
    case 2:
        if (flag_set_first_pending((u8 *)moby)) {
            if (((u8 *)moby)[0x43] != 5) anim_start_blended(moby, 5, 0, 20); moby_set_random_spread_velocity(moby, vars + 0x350);
        }
        if ((moby_l01_turn_toward_target(moby, vars + 0x350) & 0x80) || *(u16 *)(moby + 0x96) >= 181 || *(int *)(vars + 0x180) >= 21) { moby_set_state((u8 *)moby, 5, -1); break; }
        break;
    case 3:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 9) anim_start_blended(moby, 9, 0, 20);
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xF8), angle) > 0.26179942f) { moby_set_state((u8 *)moby, 9, -1); break; }
        else if ((((u8 *)moby)[0x60] & 2) && math_random_int_below(2)) {
            switch (math_random_int_below(3)) {
            case 0: moby_set_state((u8 *)moby, 4, -1); break;
            case 1: moby_set_state((u8 *)moby, 5, -1); break;
            case 2: moby_set_state((u8 *)moby, 7, -1); break;
            }

        }
        break;
    case 4:
        if (flag_set_first_pending((u8 *)moby)) {
            animation = moby_compute_aligned_direction(moby, vars + 0x350) ? 18 : 17;
            if (*(u16 *)(moby + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)moby)[0x43] != animation) anim_start_blended(moby, animation, 0, 10);
        }
        angle = mat_fast_helper_a(*(float *)(vars + 0x350) - *(float *)(moby + 0x10), *(float *)(vars + 0x354) - *(float *)(moby + 0x14));
        if ((moby_move_to_target_temp_limits(moby, vars + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(moby + 0x96) >= 121) { moby_set_state((u8 *)moby, 3, -1); break; }
        break;
    case 5:
        if (flag_set_first_pending((u8 *)moby)) {
            if (((u8 *)moby)[0x95]) { if (((u8 *)moby)[0x95] == 1 && ((u8 *)moby)[0x43] != math_random_int_below(2) + 3) anim_start_blended(moby, math_random_int_below(2) + 3, 0, 20); }
            else if (((u8 *)moby)[0x43] != 1) anim_start_blended(moby, 1, 0, 20);
        }
        if (((u8 *)moby)[0x60] & 2) { if (((u8 *)moby)[0x95]) { if (((u8 *)moby)[0x95] == 1) { moby_set_state((u8 *)moby, 3, -1); break; } } else { moby_set_state((u8 *)moby, 1, -1); break; } }

        break;
    case 7:
        if (flag_set_first_pending((u8 *)moby)) { animation = math_random_int_below(2) ? 20 : 21; if (((u8 *)moby)[0x43] != animation) anim_start_blended(moby, animation, 0, 15); }
        if (((u8 *)moby)[0x60] & 2) { moby_set_state((u8 *)moby, 3, -1); break; }
        break;
    case 6:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 6) anim_start_blended(moby, 6, 0, 15);
        if ((moby_l01_turn_toward_target(moby, vars + 0x340) & 0x80) || *(u16 *)(moby + 0x96) >= 241) { moby_set_state((u8 *)moby, 3, -1); break; }
        break;
    case 9:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 5) anim_start_blended(moby, 5, 0, 10);
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        moby_start_effect_from_entry((int)moby, angle); turret_l02_aim_at_hero(moby);
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xF8), angle) < 0.087266475f) {
            switch (((u8 *)moby)[0x95]) {
            case 2: moby_set_state((u8 *)moby, 10, -1); break;
            case 1: moby_set_state((u8 *)moby, 3, -1); break;
            }

        }

        break;
    case 8:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 2) anim_start_blended(moby, 2, 0, 10);
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        moby_start_effect_from_entry((int)moby, angle); turret_l02_aim_at_hero(moby); if (((u8 *)moby)[0x60] & 2) { moby_set_state((u8 *)moby, 10, -1); break; }
        break;
    case 10:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 9) anim_start_blended(moby, 9, 0, 20);
        turret_l02_aim_at_hero(moby);
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xF8), angle) > 0.52359885f) { { moby_set_state((u8 *)moby, 9, -1); break; } break; }
        if (!*(short *)(vars + 0x378) && *(u16 *)(moby + 0x96) > 15) {
            moby_transform_joint_to_world(*(char **)(vars + 0x370), 0, (char *)&work.aim.muzzle);
            contact = CollLine(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)g_hero_state)->target_d0, 16, moby, 0);
            if (contact && D_L15_001BFC00.hit && *(short *)(D_L15_001BFC00.hit + 0xAA) == 0xC1B /* moby class 3099 */) { { moby_set_state((u8 *)moby, 13, -1); break; } break; }
            if (contact && (hitRecord = &D_L15_001BFC00)->hit != ((L02_ResidentCombatPrefix *)g_hero_state)->pointer_2290 && !*(short *)(vars + 0x386)) {
                if (!hitRecord->hit || (!moby_is_in_special_class_range(hitRecord->hit) && (!*(char **)(hitRecord->hit + 0x24) || *(short *)(*(char **)(hitRecord->hit + 0x24) + 0x46) != 22))) break;
            }
            { moby_set_state((u8 *)moby, 11, -1); break; }
        } else {
            if (vec_distance_xy(moby + 0x10, &((L02_ResidentCombatPrefix *)g_hero_state)->position_80) < 3 && math_fabs(*(float *)(moby + 0x18) - ((L02_ResidentCombatPrefix *)g_hero_state)->position_80.f[2]) < 0.5f) { { moby_set_state((u8 *)moby, 14, -1); break; } break; }
            if ((((u8 *)moby)[0x60] & 2) && !math_random_int_below(2)) { moby_set_state((u8 *)moby, 13, -1); break; }
        }
        break;
    case 13:
        if (flag_set_first_pending((u8 *)moby)) {
            animation = moby_compute_aligned_direction(moby, vars + 0x350) ? 18 : 17;
            if (*(u16 *)(moby + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)moby)[0x43] != animation) anim_start_blended(moby, animation, 0, 10);
        }
        angle = mat_fast_helper_a(*(float *)(vars + 0x350) - *(float *)(moby + 0x10), *(float *)(vars + 0x354) - *(float *)(moby + 0x14));
        if ((moby_move_to_target_temp_limits(moby, vars + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(moby + 0x96) > 120 || *(int *)(vars + 0x180) >= 21) { moby_set_state((u8 *)moby, 10, -1); break; }
        break;
    case 11:
        if (flag_set_first_pending((u8 *)moby)) {
            if (((u8 *)moby)[0x43] != 10) anim_start_blended(moby, 10, 0, 10);
            *(short *)(vars + 0x380) = math_random_int_range(3, 5); moby_randomize_group_timers((struct L02GroupObject *)moby);
            qcopy(vars + 0x360,vars + 0x1F0); *(float *)(vars + 0x368) += 0.5f;
        }
        turret_l02_aim_at_hero(moby);
        if ((D_L15_001B2148[0] & 15) == (((int)moby >> 8) & 15))
 moby_randomize_group_timers((struct L02GroupObject *)moby);
        if (math_is_value_within_step(moby, 5)) {
            moby_transform_joint_to_world(*(char **)(vars + 0x370), 0, (char *)&work.aim.muzzle);
            FastVecSub(&work.aim.velocity, vars + 0x360, &work.aim.muzzle); vec_scale_to_length(&work.aim.velocity, &work.aim.velocity, 0.23333334922790527f);
            FastVecScale(&work.aim.acceleration, &work.aim.velocity, 0.25f);
            shotPower = (float)(u8)vars[0x34];
            if (*(short *)(vars + 0x380) >= 2)
                part_spawn_trail_effect_moby(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, shotPower, shotPower, 0.0055555556900799274f, 10, 30, 1);
            else
                part_spawn_trail_effect_moby(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, shotPower, shotPower, 0.0055555556900799274f, 30, 80, 1);
            break;
        }
        if (!(((u8 *)moby)[0x60] & 2)) break;
        moby_transform_joint_to_world(*(char **)(vars + 0x370), 0, (char *)&work.aim.muzzle);
        collision = CollLine(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)g_hero_state)->target_d0, 0, moby, 0);
        if (FastDecTimer((short *)(vars + 0x380)) || (collision && D_L15_001BFC00.hit != ((L02_ResidentCombatPrefix *)g_hero_state)->pointer_2290)) {
            *(short *)(vars + 0x378) += 15; { if (!math_random_int_below(3)) moby_set_state((u8 *)moby, 12, -1); else moby_set_state((u8 *)moby, 13, -1); break; }
        } else {
            angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
            if (FastDiffRots(*(float *)(moby + 0xF8), angle) > 0.52359885f) { moby_set_state((u8 *)moby, 9, -1); break; }
            else if (((L02_ResidentCombatPrefix *)g_hero_state)->mode_229c == 7 && ((L02_ResidentCombatPrefix *)g_hero_state)->pointer_249c && *(short *)(((L02_ResidentCombatPrefix *)g_hero_state)->pointer_249c + 0xAA) == 0xB5A /* moby class 2906 */) { moby_set_state((u8 *)moby, 12, -1); break; }
        }
        break;
    case 14:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 13) anim_start_blended(moby, 13, 0, 10);
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        moby_start_effect_from_entry((int)moby, angle); animTime = moby_get_anim_value(moby);
        if (animTime >= 11 && animTime < 12.5f) coll_test_hit_at_bone(0.6f, (float)(u8)vars[0x35], 3.0f, moby, (void *)3, 1, 0, 1, 0);
        if (((u8 *)moby)[0x60] & 2) { moby_set_state((u8 *)moby, 15, -1); break; }
        break;
    case 15:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 11) anim_start_blended(moby, 11, 10, 10);
        turret_l02_aim_at_hero(moby); if (!(((u8 *)moby)[0x60] & 2)) break;
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xF8), angle) > 0.52359885f) moby_set_state((u8 *)moby, 9, -1); else moby_set_state((u8 *)moby, 11, -1);
        break;
    case 12:
        if (flag_set_first_pending((u8 *)moby)) {
            if (((L02_ResidentCombatPrefix *)g_hero_state)->mode_229c == 7) { if (((u8 *)moby)[0x43] != 12) anim_start_blended(moby, 12, 0, 20); }
            else if (((u8 *)moby)[0x43] != 11) anim_start_blended(moby, 11, 0, 20);
        }

        turret_l02_aim_at_hero(moby); if (((u8 *)moby)[0x60] & 2) { moby_set_state((u8 *)moby, 10, -1); break; }
        break;
    case 16:
        if (!(*(float *)(vars + 0x20) > 0)) {

            if (flag_set_first_pending((u8 *)moby)) { *(short *)(vars + 0x378) = math_random_int_range(10, 15); *(short *)(vars + 0x384) = math_random_int_below(3) == 0; }
            if (*(short *)(vars + 0x384) && FastDecTimer((short *)(vars + 0x378))) {
                moby_transform_joint_point(*(char **)(vars + 0x370), 0, (char *)work.aim.transform);
                vec_scale_to_length(&work.aim.muzzle, work.aim.transform, 0.23333334922790527f);
                FastVecSub(&work.aim.velocity, g_hero_state + 0xE0, &work.aim.transform[3]); vec_scale_to_length(&work.aim.velocity, &work.aim.velocity, 1);
                if (FastVecDot(&work.aim.velocity, work.aim.transform) < 0.2f) {
                part_spawn_trail_effect_moby(&work.aim.transform[3], &work.aim.muzzle, &work.aim.muzzle, 1.0f, 0.0f, 1.0f, 30, 80, 1);
                    *(short *)(vars + 0x378) = math_random_int_range(15, 30);
                }
            }
        }
        break;
    case 17:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43]) anim_start_blended(moby, 0, 0, 20);
        if (IsPointInCuboid(&((L02_ResidentCombatPrefix *)g_hero_state)->position_80, *(int *)(vars + 0x324)) || *(int *)(vars + 0x204) == 1) { moby_set_state((u8 *)moby, 18, -1); break; }
        break;
    case 18:
        pathData = D_L15_001FE480[*(int *)(vars + 0x320)];
        if (flag_set_first_pending((u8 *)moby)) { if (((u8 *)moby)[0x43] != 6) anim_start_blended(moby, 6, 0, 20); coll_check_object_inside_polygon((u8 *)moby); }
        if (!(vec_distance_xy(moby + 0x10, pathData + *(int *)pathData * 16) < *(float *)(vars + 0x134)) && !path_follow_nodes(moby, pathData)) break;

        if (((u8 *)moby)[0x43] != 2) {
            angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
            if (FastDiffRots(*(float *)(moby + 0xF8), angle > 0.3490659f ? 1.0f : 0.0f) != 0 && ((u8 *)moby)[0x43] != 2) anim_start_blended(moby, 2, 5, 10);
        }
        moby_check_target_point_from_offset(moby, vars + 0x1F0);
        angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10), *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));
        if (FastDiffRots(*(float *)(moby + 0xF8), angle) < 0.087266475f && (((u8 *)moby)[0x43] != 2 || (((u8 *)moby)[0x60] & 2))) {
            *(int *)(vars + 0x320) = -1; qcopy(vars + 0x340,moby + 0x10);
            if (*(int *)(vars + 0x328) != -1) moby_set_state((u8 *)moby, 19, 4); else moby_set_state((u8 *)moby, 1, 0);

        }
        break;
    case 22:
        if (flag_set_first_pending((u8 *)moby)) { if (((u8 *)moby)[0x43] != 6) anim_start_blended(moby, 6, 0, 20); coll_check_object_inside_polygon((u8 *)moby); }
        if (moby_l01_turn_toward_target(moby, vars + 0x340) & 0x80) { moby_set_state((u8 *)moby, 1, 0); qcopy(vars + 0x340,moby + 0x10); }
        break;
    case 19:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43]) anim_start_blended(moby, 0, 0, 20);
        if (*(int *)(vars + 0x32C) == -1 || IsPointInCuboid(&((L02_ResidentCombatPrefix *)g_hero_state)->position_80, *(int *)(vars + 0x32C)) || *(int *)(vars + 0x204) == 1) { moby_set_state((u8 *)moby, 20, -1); break; }
        break;
    case 20:
        if (flag_set_first_pending((u8 *)moby)) {
            if (((u8 *)moby)[0x43] != 9) anim_start_blended(moby, 9, 0, 20);
            if (*(float *)(vars + 0x37C) == 0) *(float *)(vars + 0x37C) = math_random_int_below(2) ? 0.3490659f : -0.3490659f;
            else *(float *)(vars + 0x37C) = -*(float *)(vars + 0x37C);
        }
        *(float *)(vars + 0x278) = *(float *)(vars + 0x37C);
        if (*(u16 *)(moby + 0x96) < 11) break;
        if (moby_find_group_in_state_13(*(int *)(vars + 0x328))) moby_set_state((u8 *)moby, 21, -1); else moby_set_state((u8 *)moby, 3, 1);
        break;
    case 21:
        if (flag_set_first_pending((u8 *)moby) && ((u8 *)moby)[0x43] != 10) anim_start_blended(moby, 10, 0, 10);
        *(float *)(vars + 0x278) = *(float *)(vars + 0x37C);
        if (math_is_value_within_step(moby, 5)) {
            if ((relayTarget = (char *)moby_find_group_in_state_13(*(int *)(vars + 0x328))) != 0) {
                moby_transform_joint_point(*(char **)(vars + 0x370), 0, (char *)work.relay.frame);
                vec_scale_to_length(&work.relay.direction, work.relay.frame, 0.23333334922790527f);
                {
                    Quad q = *(Quad *)&work.relay.frame[3];
                    *(Quad *)&work.relay.origin = q;
                }
                moby_teleport_to_new_pose(relayTarget, &work.relay.origin, &work.relay.direction);
            }
        } else if (((u8 *)moby)[0x60] & 2) moby_set_state((u8 *)moby, 20, -1);

        break;
    }
    moby_update_glow_pulse_timers(moby);
}
