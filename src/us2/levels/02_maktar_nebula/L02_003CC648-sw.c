#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
struct L02NearObject;
struct L02GroupObject;
extern char g_hero_state[] NOT_SDA;
typedef struct { char pad[0x18]; char *hit; int count; } L02Collision;
extern L02Collision D_L02_001C0940;
extern char *g_route_polygons[];
extern int g_frame_l02_counter[] __attribute__((sda));
extern int linked_child_update(char *), moby_compute_aligned_direction(char *, void *);
extern void moby_update_glow_pulse_timers(char *), turret_l02_aim_at_hero(char *), moby_set_random_spread_velocity(char *, void *), linked_effect_update(char *);
extern void moby_delay_group_except_nearest(struct L02NearObject *), moby_randomize_group_timers(struct L02GroupObject *), moby_teleport_to_new_pose(char *, void *, void *);
extern u8 *moby_find_group_in_state_13(int);
extern void moby_mark_spawned(void *), moby_set_state(u8 *, int, int), anim_start_blended(char *, int, int, int), func_US2_002A7AA8(char *, void *, int);
extern int flag_set_first_pending(u8 *), flag_set_second_pending(u8 *), math_random_int_below(int), math_random_int_range(int, int), FastDecTimer(short *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern int moby_dispatch_action_by_kind(void *, void *);
extern void part_queue_moby_for_glow(char *, int, void (*)(char *));
extern int moby_l01_turn_toward_target(char *, char *), moby_start_effect_from_entry(int, float), moby_move_to_target_temp_limits(void *, void *, int, float, float, float), moby_check_target_point_from_offset(char *, void *);
extern float mat_fast_helper_a(float, float), FastDiffRots(float, float), fast_vec_dist(void *, void *), vec_distance_xy(void *, void *), math_fabs(float), FastVecDot(void *, void *), moby_get_anim_value(char *);
extern int CollLine(void *, void *, int, char *, void *), moby_is_in_special_class_range(char *), func_US2_002AF9C8(char *, float), IsPointInCuboid(void *, int), path_follow_nodes(char *, char *), coll_check_object_inside_polygon(u8 *);
extern int coll_test_hit_at_bone(float, float, float, void *, void *, int, int, int, int);
extern void moby_transform_joint_point(char *, int, char *), moby_transform_joint_to_world(char *, int, char *), FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float), FastVecScale(void *, void *, float);
extern void *part_spawn_trail_effect_moby(void *, void *, void *, float, float, float, int, int, int);
typedef struct {
    u8 prefix[0x80]; Vector position_80; u8 gap_90[0x40]; Vector target_d0;
    u8 gap_e0[0x21B0]; char *pointer_2290; u8 gap_2294[8]; int mode_229c;
    u8 gap_22a0[0x1FC]; char *pointer_249c;
} L02_ResidentCombatPrefix;

void func_US2_L02_003CC648(char *self) {
    /* One frame area, two layouts: the aiming states and the case-21 hand-off. */
    union {
        struct { Vector muzzle, velocity, acceleration, transform[4]; } aim;
        struct { Vector frame[4], direction, origin; } relay;
    } work;
    char *state = *(char **)(self + 0x68), *path, *other;
    L02Collision *col;
    int flags;
    float angle, time, power;

    int choice, animation, collision, contact;
    if (linked_child_update(self)) { moby_mark_spawned(self); return; }
    switch (((u8 *)self)[0x95]) {
    case 0:
        if (flag_set_second_pending((u8 *)self)) moby_set_controller_speed_limits((u8 *)self, 0.0011111111380159855f, 0.050000004f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(state + 0x204) == 1) {
            if (*(int *)(state + 0x33C)) { *(int *)(state + 0x33C) = 0; moby_set_state((u8 *)self, 8, 2); }
            else moby_set_state((u8 *)self, 10, 2);
        } else if (*(short *)(state + 0x382)) {
            moby_set_state((u8 *)self, 3, 1); *(short *)(state + 0x382) = 0; *(short *)(state + 0x374) = math_random_int_range(480, 600);
        }
        break;
    case 1:
        if (flag_set_second_pending((u8 *)self)) moby_set_controller_speed_limits((u8 *)self, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        if (*(int *)(state + 0x204) == 1) moby_set_state((u8 *)self, 10, 2);
        else if (!*(short *)(state + 0x374)) {
            if (vec_distance_xy(self + 0x10, &((L02_ResidentCombatPrefix *)g_hero_state)->position_80) > 26) moby_set_state((u8 *)self, 1, 0);
            else *(short *)(state + 0x374) = 120;
        }
        break;
    case 2:
        if (flag_set_second_pending((u8 *)self)) {
            moby_delay_group_except_nearest((struct L02NearObject *)self);
            moby_set_controller_speed_limits((u8 *)self, 0.002222222276031971f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f);
        }
        if (*(int *)(state + 0x204) != 1 && (((u8 *)self)[0x60] & 2) && ((u8 *)self)[0x20] != 11) {
            if (fast_vec_dist(self + 0x10, state + 0x340) > 4) moby_set_state((u8 *)self, 6, -1);
            else {
                switch (math_random_int_below(4)) {
                case 0: moby_set_state((u8 *)self, 3, 1); break;
                case 1: moby_set_state((u8 *)self, 4, 1); break;
                case 2: moby_set_state((u8 *)self, 5, 1); break;
                case 3: moby_set_state((u8 *)self, 7, 1); break;
                }
            }
            *(short *)(state + 0x374) = math_random_int_range(580, 600);
        }
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(self, state + 0x50);
        if (flags & 1) {
            *(u16 *)(*(char **)(state + 0x370) + 0x34) |= 0x41; *(u16 *)(*(char **)(state + 0x370) + 0x34) &= 0xEFFF; *(int *)(*(char **)(state + 0x370) + 0x98) = 0;
            func_US2_002A7AA8(self, 0, 3); part_queue_moby_for_glow(self, 0, linked_effect_update); return;
        }
        if (flags & 2) {
            *(int *)(state + 0x33C) = 0;
            if (*(int *)(state + 0x320) != -1) moby_set_state((u8 *)self, 18, 4);
            else if (*(int *)(state + 0x204) == 1) moby_set_state((u8 *)self, 10, 2);
            else { moby_set_state((u8 *)self, 3, 1); *(short *)(state + 0x374) = math_random_int_range(580, 600); }

        }
        break;
    case 4:
        if (flag_set_second_pending((u8 *)self)) {
            moby_set_controller_speed_limits((u8 *)self, 0.0033333334140479565f, 0.10000001f, 0.0034906589426100254f, 0.41887909173965454f); *(float *)(state + 0x134) = 0.25f;
        }
        break;
    }
    switch (((u8 *)self)[0x20]) {
    case 1:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43]) anim_start_blended(self, 0, 0, 20);
        if (!(((u8 *)self)[0x60] & 2)) break;
        if (!math_random_int_below(4)) { moby_set_state((u8 *)self, 5, -1); break; }
        else if (!*(int *)(state + 0x33C)) { moby_set_state((u8 *)self, 2, -1); break; }
        break;
    case 2:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x43] != 5) anim_start_blended(self, 5, 0, 20); moby_set_random_spread_velocity(self, state + 0x350);
        }
        if ((moby_l01_turn_toward_target(self, state + 0x350) & 0x80) || *(u16 *)(self + 0x96) >= 181 || *(int *)(state + 0x180) >= 21) { moby_set_state((u8 *)self, 5, -1); break; }
        break;
    case 3:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 9) anim_start_blended(self, 9, 0, 20);
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.26179942f) { moby_set_state((u8 *)self, 9, -1); break; }
        else if ((((u8 *)self)[0x60] & 2) && math_random_int_below(2)) {
            switch (math_random_int_below(3)) {
            case 0: moby_set_state((u8 *)self, 4, -1); break;
            case 1: moby_set_state((u8 *)self, 5, -1); break;
            case 2: moby_set_state((u8 *)self, 7, -1); break;
            }

        }
        break;
    case 4:
        if (flag_set_first_pending((u8 *)self)) {
            animation = moby_compute_aligned_direction(self, state + 0x350) ? 18 : 17;
            if (*(u16 *)(self + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)self)[0x43] != animation) anim_start_blended(self, animation, 0, 10);
        }
        angle = mat_fast_helper_a(*(float *)(state + 0x350) - *(float *)(self + 0x10), *(float *)(state + 0x354) - *(float *)(self + 0x14));
        if ((moby_move_to_target_temp_limits(self, state + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(self + 0x96) >= 121) { moby_set_state((u8 *)self, 3, -1); break; }
        break;
    case 5:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x95]) { if (((u8 *)self)[0x95] == 1 && ((u8 *)self)[0x43] != math_random_int_below(2) + 3) anim_start_blended(self, math_random_int_below(2) + 3, 0, 20); }
            else if (((u8 *)self)[0x43] != 1) anim_start_blended(self, 1, 0, 20);
        }
        if (((u8 *)self)[0x60] & 2) { if (((u8 *)self)[0x95]) { if (((u8 *)self)[0x95] == 1) { moby_set_state((u8 *)self, 3, -1); break; } } else { moby_set_state((u8 *)self, 1, -1); break; } }

        break;
    case 7:
        if (flag_set_first_pending((u8 *)self)) { animation = math_random_int_below(2) ? 20 : 21; if (((u8 *)self)[0x43] != animation) anim_start_blended(self, animation, 0, 15); }
        if (((u8 *)self)[0x60] & 2) { moby_set_state((u8 *)self, 3, -1); break; }
        break;
    case 6:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 6) anim_start_blended(self, 6, 0, 15);
        if ((moby_l01_turn_toward_target(self, state + 0x340) & 0x80) || *(u16 *)(self + 0x96) >= 241) { moby_set_state((u8 *)self, 3, -1); break; }
        break;
    case 9:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 5) anim_start_blended(self, 5, 0, 10);
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        moby_start_effect_from_entry((int)self, angle); turret_l02_aim_at_hero(self);
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) < 0.087266475f) {
            switch (((u8 *)self)[0x95]) {
            case 2: moby_set_state((u8 *)self, 10, -1); break;
            case 1: moby_set_state((u8 *)self, 3, -1); break;
            }

        }

        break;
    case 8:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 2) anim_start_blended(self, 2, 0, 10);
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        moby_start_effect_from_entry((int)self, angle); turret_l02_aim_at_hero(self); if (((u8 *)self)[0x60] & 2) { moby_set_state((u8 *)self, 10, -1); break; }
        break;
    case 10:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 9) anim_start_blended(self, 9, 0, 20);
        turret_l02_aim_at_hero(self);
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.52359885f) { { moby_set_state((u8 *)self, 9, -1); break; } break; }
        if (!*(short *)(state + 0x378) && *(u16 *)(self + 0x96) > 15) {
            moby_transform_joint_to_world(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
            contact = CollLine(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)g_hero_state)->target_d0, 16, self, 0);
            if (contact && D_L02_001C0940.hit && *(short *)(D_L02_001C0940.hit + 0xAA) == 0xC1B) { { moby_set_state((u8 *)self, 13, -1); break; } break; }
            if (contact && (col = &D_L02_001C0940)->hit != ((L02_ResidentCombatPrefix *)g_hero_state)->pointer_2290 && !*(short *)(state + 0x386)) {
                if (!col->hit || (!moby_is_in_special_class_range(col->hit) && (!*(char **)(col->hit + 0x24) || *(short *)(*(char **)(col->hit + 0x24) + 0x46) != 22))) break;
            }
            { moby_set_state((u8 *)self, 11, -1); break; }
        } else {
            if (vec_distance_xy(self + 0x10, &((L02_ResidentCombatPrefix *)g_hero_state)->position_80) < 3 && math_fabs(*(float *)(self + 0x18) - ((L02_ResidentCombatPrefix *)g_hero_state)->position_80.f[2]) < 0.5f) { { moby_set_state((u8 *)self, 14, -1); break; } break; }
            if ((((u8 *)self)[0x60] & 2) && !math_random_int_below(2)) { moby_set_state((u8 *)self, 13, -1); break; }
        }
        break;
    case 13:
        if (flag_set_first_pending((u8 *)self)) {
            animation = moby_compute_aligned_direction(self, state + 0x350) ? 18 : 17;
            if (*(u16 *)(self + 0x34) & 0x8000) animation = animation == 17 ? 18 : 17;
            if (((u8 *)self)[0x43] != animation) anim_start_blended(self, animation, 0, 10);
        }
        angle = mat_fast_helper_a(*(float *)(state + 0x350) - *(float *)(self + 0x10), *(float *)(state + 0x354) - *(float *)(self + 0x14));
        if ((moby_move_to_target_temp_limits(self, state + 0x350, 16, angle, -1, -1) & 0x80) || *(u16 *)(self + 0x96) > 120 || *(int *)(state + 0x180) >= 21) { moby_set_state((u8 *)self, 10, -1); break; }
        break;
    case 11:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x43] != 10) anim_start_blended(self, 10, 0, 10);
            *(short *)(state + 0x380) = math_random_int_range(3, 5); moby_randomize_group_timers((struct L02GroupObject *)self);
            qcopy(state + 0x360,state + 0x1F0); *(float *)(state + 0x368) += 0.5f;
        }
        turret_l02_aim_at_hero(self);
        if ((g_frame_l02_counter[0] & 15) == (((int)self >> 8) & 15))
 moby_randomize_group_timers((struct L02GroupObject *)self);
        if (func_US2_002AF9C8(self, 5)) {
            moby_transform_joint_to_world(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
            FastVecSub(&work.aim.velocity, state + 0x360, &work.aim.muzzle); vec_scale_to_length(&work.aim.velocity, &work.aim.velocity, 0.23333334922790527f);
            FastVecScale(&work.aim.acceleration, &work.aim.velocity, 0.25f);
            power = (float)(u8)state[0x34];
            if (*(short *)(state + 0x380) >= 2)
                part_spawn_trail_effect_moby(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, power, power, 0.0055555556900799274f, 10, 30, 1);
            else
                part_spawn_trail_effect_moby(&work.aim.muzzle, &work.aim.acceleration, &work.aim.velocity, power, power, 0.0055555556900799274f, 30, 80, 1);
            break;
        }
        if (!(((u8 *)self)[0x60] & 2)) break;
        moby_transform_joint_to_world(*(char **)(state + 0x370), 0, (char *)&work.aim.muzzle);
        collision = CollLine(&work.aim.muzzle, &((L02_ResidentCombatPrefix *)g_hero_state)->target_d0, 0, self, 0);
        if (FastDecTimer((short *)(state + 0x380)) || (collision && D_L02_001C0940.hit != ((L02_ResidentCombatPrefix *)g_hero_state)->pointer_2290)) {
            *(short *)(state + 0x378) += 15; { if (!math_random_int_below(3)) moby_set_state((u8 *)self, 12, -1); else moby_set_state((u8 *)self, 13, -1); break; }
        } else {
            angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
            if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.52359885f) { moby_set_state((u8 *)self, 9, -1); break; }
            else if (((L02_ResidentCombatPrefix *)g_hero_state)->mode_229c == 7 && ((L02_ResidentCombatPrefix *)g_hero_state)->pointer_249c && *(short *)(((L02_ResidentCombatPrefix *)g_hero_state)->pointer_249c + 0xAA) == 0xB5A) { moby_set_state((u8 *)self, 12, -1); break; }
        }
        break;
    case 14:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 13) anim_start_blended(self, 13, 0, 10);
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        moby_start_effect_from_entry((int)self, angle); time = moby_get_anim_value(self);
        if (time >= 11 && time < 12.5f) coll_test_hit_at_bone(0.6f, (float)(u8)state[0x35], 3.0f, self, (void *)3, 1, 0, 1, 0);
        if (((u8 *)self)[0x60] & 2) { moby_set_state((u8 *)self, 15, -1); break; }
        break;
    case 15:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 11) anim_start_blended(self, 11, 10, 10);
        turret_l02_aim_at_hero(self); if (!(((u8 *)self)[0x60] & 2)) break;
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) > 0.52359885f) moby_set_state((u8 *)self, 9, -1); else moby_set_state((u8 *)self, 11, -1);
        break;
    case 12:
        if (flag_set_first_pending((u8 *)self)) {
            if (((L02_ResidentCombatPrefix *)g_hero_state)->mode_229c == 7) { if (((u8 *)self)[0x43] != 12) anim_start_blended(self, 12, 0, 20); }
            else if (((u8 *)self)[0x43] != 11) anim_start_blended(self, 11, 0, 20);
        }

        turret_l02_aim_at_hero(self); if (((u8 *)self)[0x60] & 2) { moby_set_state((u8 *)self, 10, -1); break; }
        break;
    case 16:
        if (!(*(float *)(state + 0x20) > 0)) {

            if (flag_set_first_pending((u8 *)self)) { *(short *)(state + 0x378) = math_random_int_range(10, 15); *(short *)(state + 0x384) = math_random_int_below(3) == 0; }
            if (*(short *)(state + 0x384) && FastDecTimer((short *)(state + 0x378))) {
                moby_transform_joint_point(*(char **)(state + 0x370), 0, (char *)work.aim.transform);
                vec_scale_to_length(&work.aim.muzzle, work.aim.transform, 0.23333334922790527f);
                FastVecSub(&work.aim.velocity, g_hero_state + 0xE0, &work.aim.transform[3]); vec_scale_to_length(&work.aim.velocity, &work.aim.velocity, 1);
                if (FastVecDot(&work.aim.velocity, work.aim.transform) < 0.2f) {
                part_spawn_trail_effect_moby(&work.aim.transform[3], &work.aim.muzzle, &work.aim.muzzle, 1.0f, 0.0f, 1.0f, 30, 80, 1);
                    *(short *)(state + 0x378) = math_random_int_range(15, 30);
                }
            }
        }
        break;
    case 17:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43]) anim_start_blended(self, 0, 0, 20);
        if (IsPointInCuboid(&((L02_ResidentCombatPrefix *)g_hero_state)->position_80, *(int *)(state + 0x324)) || *(int *)(state + 0x204) == 1) { moby_set_state((u8 *)self, 18, -1); break; }
        break;
    case 18:
        path = g_route_polygons[*(int *)(state + 0x320)];
        if (flag_set_first_pending((u8 *)self)) { if (((u8 *)self)[0x43] != 6) anim_start_blended(self, 6, 0, 20); coll_check_object_inside_polygon((u8 *)self); }
        if (!(vec_distance_xy(self + 0x10, path + *(int *)path * 16) < *(float *)(state + 0x134)) && !path_follow_nodes(self, path)) break;

        if (((u8 *)self)[0x43] != 2) {
            angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
            if (FastDiffRots(*(float *)(self + 0xF8), angle > 0.3490659f ? 1.0f : 0.0f) != 0 && ((u8 *)self)[0x43] != 2) anim_start_blended(self, 2, 5, 10);
        }
        moby_check_target_point_from_offset(self, state + 0x1F0);
        angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(self + 0x10), *(float *)(state + 0x1F4) - *(float *)(self + 0x14));
        if (FastDiffRots(*(float *)(self + 0xF8), angle) < 0.087266475f && (((u8 *)self)[0x43] != 2 || (((u8 *)self)[0x60] & 2))) {
            *(int *)(state + 0x320) = -1; qcopy(state + 0x340,self + 0x10);
            if (*(int *)(state + 0x328) != -1) moby_set_state((u8 *)self, 19, 4); else moby_set_state((u8 *)self, 1, 0);

        }
        break;
    case 22:
        if (flag_set_first_pending((u8 *)self)) { if (((u8 *)self)[0x43] != 6) anim_start_blended(self, 6, 0, 20); coll_check_object_inside_polygon((u8 *)self); }
        if (moby_l01_turn_toward_target(self, state + 0x340) & 0x80) { moby_set_state((u8 *)self, 1, 0); qcopy(state + 0x340,self + 0x10); }
        break;
    case 19:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43]) anim_start_blended(self, 0, 0, 20);
        if (*(int *)(state + 0x32C) == -1 || IsPointInCuboid(&((L02_ResidentCombatPrefix *)g_hero_state)->position_80, *(int *)(state + 0x32C)) || *(int *)(state + 0x204) == 1) { moby_set_state((u8 *)self, 20, -1); break; }
        break;
    case 20:
        if (flag_set_first_pending((u8 *)self)) {
            if (((u8 *)self)[0x43] != 9) anim_start_blended(self, 9, 0, 20);
            if (*(float *)(state + 0x37C) == 0) *(float *)(state + 0x37C) = math_random_int_below(2) ? 0.3490659f : -0.3490659f;
            else *(float *)(state + 0x37C) = -*(float *)(state + 0x37C);
        }
        *(float *)(state + 0x278) = *(float *)(state + 0x37C);
        if (*(u16 *)(self + 0x96) < 11) break;
        if (moby_find_group_in_state_13(*(int *)(state + 0x328))) moby_set_state((u8 *)self, 21, -1); else moby_set_state((u8 *)self, 3, 1);
        break;
    case 21:
        if (flag_set_first_pending((u8 *)self) && ((u8 *)self)[0x43] != 10) anim_start_blended(self, 10, 0, 10);
        *(float *)(state + 0x278) = *(float *)(state + 0x37C);
        if (func_US2_002AF9C8(self, 5)) {
            if ((other = (char *)moby_find_group_in_state_13(*(int *)(state + 0x328))) != 0) {
                moby_transform_joint_point(*(char **)(state + 0x370), 0, (char *)work.relay.frame);
                vec_scale_to_length(&work.relay.direction, work.relay.frame, 0.23333334922790527f);
                {
                    Quad q = *(Quad *)&work.relay.frame[3];
                    *(Quad *)&work.relay.origin = q;
                }
                moby_teleport_to_new_pose(other, &work.relay.origin, &work.relay.direction);
            }
        } else if (((u8 *)self)[0x60] & 2) moby_set_state((u8 *)self, 20, -1);

        break;
    }
    moby_update_glow_pulse_timers(self);
}
