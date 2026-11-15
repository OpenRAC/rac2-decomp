#include "common.h"

/* func_L17_003E7068 has a unit of its own for two flags (config/cflags.txt):
 * -frac2-gcse-unsplit-edges lets PRE put the &v30 copy before the state switch's
 * bounds check, as GCC 2.95 does, instead of in a split-off default block; and
 * -fmove-all-movables hoists the case 8 loop's D_L17_001C0020 address in loop.c's
 * first pass, ahead of st + 0x710, which decides the loop's s1/s5 allocation.
 * The pool reads use Moby member access (index scaled first), the address-of
 * uses plain pointer sums (base first), as retail's operand order shows. */
typedef union { u8 b[0x2000]; s8 c[0x2000]; s16 h[0x1000]; u16 uh[0x1000]; s32 i[0x800]; u32 u[0x800]; f32 f[0x800]; void *p[0x800]; } UView;
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { u8 pad0[0xAA]; s16 oclass; u8 padAC[0xF8 - 0xAC]; float rotz; u8 padFC[0x100 - 0xFC]; } Moby;
typedef struct { float sn, cs, one, big; void *obj; int flags; u8 z, o; u16 id; float val; int k; } Hit;
extern void STUB_printf(const char *, ...);
extern int CollLine(void *, void *, int, void *, int);
extern int math_fast_float_d(void *);
extern int FastDecTimer(short *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern void moby_mark_spawned(void *);
extern float moby_get_anim_value(u8 *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void SetDeathBits(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern int math_random_int_below(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern int coll_test_hit_at_bone(float, float, float, void *, int, int, int, int, int);
extern void StepAngleTowardTarget(void *, int, float, float);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(u8 *);
extern int flag_set_second_pending(u8 *);
extern int moby_step_controller(void *, void *, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int moby_l01_turn_toward_target(void *, void *);
extern void part_queue_moby_for_glow(u8 *, int, void *);
extern int ComputeRegionRouteHeading(void *, void *, void *, void *, int, void *, void *, float, float);
extern void path_clamp_move_to_area(void *, void *, void *, int, float);
extern int coll_find_clear_side_point(void *, void *, void *, int, float, float);
extern void ride_platform_start(u8 *);
extern int ride_platform_can_start(u8 *);
extern void platform_set_path_index(u8 *, u8 *);
extern int ClaimNearestObjectSlot(u8 *);
extern void grulch_release_slot(u8 *);
extern int grulch_pick_random_path_point(u8 *);
extern int grulch_is_target_reachable(u8 *);
extern void snapper_init_state_check_hits(void);
extern u8 g_hero_state[];
extern u8 *g_moby_l17_pool[] __attribute__((sda));
extern int D_L17_001B3940[] __attribute__((sda));
extern u8 *D_L17_001FB720[];
extern u8 *g_path_l17_table[];
extern Vec D_L17_001B9BC0;
extern Vec D_L17_001C0020;
extern char D_L17_001B0ED0[], D_L17_001B0EE8[], D_L17_001B0F10[], D_L17_001B0F20[];
extern float D_L17_001B0E3C __attribute__((sda));
extern float D_L17_001B0E58 __attribute__((sda));
extern int D_L17_001B0E68 __attribute__((sda));
extern int D_L17_001B0E6C __attribute__((sda));
extern float D_L17_001B0E70 __attribute__((sda));
extern float D_L17_001B0E74 __attribute__((sda));
extern float D_L17_001B0E7C __attribute__((sda));
extern float D_L17_001B0E80 __attribute__((sda));
extern float D_L17_001B0E88 __attribute__((sda));
extern int D_L17_001B0E8C __attribute__((sda));
extern float D_L17_001B0E90 __attribute__((sda));
extern int D_L17_001B0E94 __attribute__((sda));
extern int D_L17_001B0E9C __attribute__((sda));
extern float D_L17_001B0EA4 __attribute__((sda));
extern int D_L17_001B0EA8 __attribute__((sda));
extern float D_L17_001B0EAC __attribute__((sda));
extern float D_L17_001B0EB0 __attribute__((sda));
extern float D_L17_001B0EB4 __attribute__((sda));
extern float D_L17_001B0EB8 __attribute__((sda));
extern int D_L17_001B0EC0 __attribute__((sda));
extern int D_L17_001B0EC4 __attribute__((sda));
extern float D_L17_001B0EC8 __attribute__((sda));

/* Updates the two-headed Smolgian snapper (moby class 3019): it sets itself up, walks along
   its path, chases the player, bites when close, and is removed if it falls out of the
   level. */
void snapper_update(u8 *self) {
    Hit hit_info;
    u8 *vars = ((u8 *)((UView *)(self))->p[0x1A]);
    float dist, ang, anim_progress, anim_speed, attack_progress, chase_scale, bite_progress, turn_angle, height, idle_progress;
    Vec target_point, probe_point, probe_end;
    float path_cost;
    int attached_index, damage_type, hit_flags, point_index;
    int leader_index, attached_index2;
    u8 *leader;
    int attempts, move_flags, near_ground, move_flags13;
    float fallback_distance;
    Moby *moby_pool;

    snapper_init_state_check_hits();
    dist = vec_distance_xy(self + 0x10, vars + 0x240);
    ang = mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]);
    attached_index = *(int *)(vars + 0x6B8);
    if (attached_index != -1) {
        if (((Moby *)g_moby_l17_pool[0])[attached_index].oclass != 0x929 /* moby class 2345 */) {
            STUB_printf(D_L17_001B0ED0);
        } else {
            platform_set_path_index((u8 *)&((Moby *)g_moby_l17_pool[0])[attached_index], self);
        }
    }
    switch (self[0x95]) {
    case 5:
        moby_transform_point_and_rotation_by_parent(self, g_moby_l17_pool[0] + (*(int *)(vars + 0x6B8) << 8), self + 0x10, self + 0xF0, self + 0x10, self + 0xF0);
        leader_index = *(int *)(vars + 0x6DC);
        if (leader_index == -1 || (leader = g_moby_l17_pool[0] + (leader_index << 8)) == self || leader == 0 || leader[0x20] == 0xFE || leader[0x20] == 0xFD) {
            attached_index2 = *(int *)(vars + 0x6B8);
            if (attached_index2 != -1) {
                if (*(s16 *)(vars + 0x69E) == 1 && ride_platform_can_start(g_moby_l17_pool[0] + (attached_index2 << 8))) {
                    ride_platform_start(g_moby_l17_pool[0] + (*(int *)(vars + 0x6B8) << 8));
                    if (((Moby *)g_moby_l17_pool[0])[*(int *)(vars + 0x6B8)].oclass == 0x929 /* moby class 2345 */) {
                        if (self[0x20] != 6) moby_set_state(self, 6, -1);
                        moby_pool = (Moby *)g_moby_l17_pool[0];
                        ((UView *)(self))->uh[0x1A] = ((UView *)(self))->uh[0x1A] & 0xFFBE;
                        ((UView *)(self))->i[0x26] = *(int *)(((u8 *)((UView *)(self))->p[0x9]) + 0x10);
                        ((UView *)(self))->f[0x3E] = moby_pool[*(int *)(vars + 0x6B8)].rotz;
                    } else if (self[0x20] != 6) {
                        moby_set_state(self, 6, -1);
                    }
                }
                break;
            }
            goto case0;
        }
        break;
    case 0:
    case0:
        if (*(s16 *)(vars + 0x69E) == 1) {
            if (*(int *)(vars + 0x730) == 0 || D_L17_001FB720[self[0x21]] == 0 || ClaimNearestObjectSlot(self) != 0) {
                moby_set_state(self, 0xF, 2);
            } else {
                moby_set_state(self, 7, 6);
                if (self[0x43] != 1) anim_start_blended(self, 1, 0, D_L17_001B0E9C);
            }
            moby_set_controller_speed_limits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            *(s16 *)(vars + 0x69C) = 0xC8;
            *(int *)(vars + 0x148) = *(int *)(vars + 0x148) | 0x10;
        }
        break;
    case 2:
        if (*(s16 *)(vars + 0x69E) == 1) *(s16 *)(vars + 0x69C) = 0xC8;
        if (FastDecTimer((short *)(vars + 0x69C)) != 0) {
            moby_set_state(self, 5, 4);
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 3) anim_start_blended(self, 3, 0, 0x14);
            *(s16 *)(vars + 0x69C) = 0xDC;
        }
        break;
    case 4:
        if (*(s16 *)(vars + 0x69E) == 1) goto alert;
        goto b62;
    case 6:
        if (ClaimNearestObjectSlot(self) != 0) {
            if ((self[0x42] != 1 && self[0x43] != 1) || (self[0x60] & 2)) {
alert:
                moby_set_state(self, 0xB, 2);
                moby_set_controller_speed_limits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
                *(s16 *)(vars + 0x69C) = 0xC8;
                *(int *)(vars + 0x148) = *(int *)(vars + 0x148) | 0x10;
            }
        } else {
            anim_progress = moby_get_anim_value(self);
            if (*(s16 *)(vars + 0x69E) == 1) *(s16 *)(vars + 0x69C) = 0xC8;
            if ((self[0x60] & 2) && self[0x42] == 3 && self[0x43] != 0xE) anim_start_blended(self, 0xE, 0, D_L17_001B0E9C);
            if (anim_progress >= 20.0f && self[0x42] == 0xE && self[0x43] != 3) anim_start_blended(self, 3, 0, D_L17_001B0E9C);
            if (self[0x60] & 2) {
                if (self[0x42] == 1) {
                    if (self[0x43] != 0xE) anim_start_blended(self, 0xE, 0, D_L17_001B0E9C);
                    goto b60;
                }
            } else {
b60:
                if (self[0x42] == 1) {
                    StepAngleTowardTarget(self + 0xF8, 0, mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), 0.10471977f);
                }
            }
b62:
            if (FastDecTimer((short *)(vars + 0x69C)) != 0) {
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 2) anim_start_blended(self, 2, 0, 0x14);
                moby_set_state(self, 3, 0);
            }
        }
        break;
    case 3:
        if (flag_set_second_pending(self) != 0) {
            anim_speed = ((UView *)(self))->f[0x12];
            if (anim_speed <= 0.0f || anim_speed > 1.0f) ((UView *)(self))->f[0x12] = 1.0f;
            moby_set_controller_speed_limits(self, (float)(D_L17_001B0E68 * 8) * 0.00027777778f, D_L17_001B0E70 * 0.13333334f, 0.10471977f, 0.10471977f);
        }
        if (((UView *)(self))->f[0x6] < D_L17_001B0E3C) goto b262;
        if (*(float *)(vars + 0xE8) > 0.016666668f) {
            *(float *)(vars + 0xE8) = 0.016666668f;
            STUB_printf(D_L17_001B0F10);
        }
        hit_flags = moby_dispatch_action_by_kind(self, vars + 0x60);
        if (hit_flags & 1) {
            part_queue_moby_for_glow(self, 0, 0);
            SetDeathBits(self, 0, 3);
        }
        attack_progress = moby_get_anim_value(self);
        if (attack_progress >= 13.0f && attack_progress <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, vars + 0x240) < D_L17_001B0E58) {
            if (self[0x42] == 4) {
                if (grulch_is_target_reachable(self) != 0) {
                    hit_info.obj = self;
                    hit_info.flags = 0x10001;
                    hit_info.val = *(float *)(vars + 0x700);
                    hit_info.sn = math_fast_sin_or_cos_a(mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
                    hit_info.cs = math_fast_sin_or_cos_b(mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
                    hit_info.one = 1.0f;
                    hit_info.big = 5627.925f;
                    hit_info.o = hit_info.k = 1;
                    hit_info.z = 0;
                    hit_info.id = ((UView *)(self))->uh[0x55];
                    damage_type = self[0x42] == 4 ? D_L17_001B0EC4 : D_L17_001B0EC0;
                    coll_test_hit_at_bone(D_L17_001B0EC8, *(float *)(vars + 0x700), 1.0f, self, damage_type, 0x10001, 0, 1, 0);
                }
            }
        }
        if ((self[0x42] == 4 || self[0x43] == 4) && !(attack_progress > 13.0f)) {
            moby_l01_turn_toward_target(self, vars + 0x240);
        }
        if ((hit_flags & 2) && D_L17_001B0EB0 <= attack_progress) moby_set_state(self, 0xD, 2);
        if (self[0x42] == 0xD && D_L17_001B0EB4 <= attack_progress) {
            if (self[0x43] != 4) anim_start_blended(self, 4, 0, 8);
            *(s16 *)(g_hero_state + 0x1DC) = 0;
        }
        break;
    }
    switch (self[0x20]) {
    case 3:
        if (flag_set_first_pending(self) != 0) {
            if (math_random_int_below(2) == 0) {
                if (self[0x43] != 2) anim_start_blended(self, 2, 0, D_L17_001B0E9C);
            } else if (self[0x43] != 0xE) {
                anim_start_blended(self, 0xE, 0, D_L17_001B0E9C);
            }
        }
        idle_progress = moby_get_anim_value(self);
        if ((self[0x42] == 2 && (self[0x60] & 2)) || (self[0x42] == 0xE && idle_progress >= 20.0f)) {
            if (math_random_int_below(2) == 0) {
                if (self[0x43] != 2) anim_start_blended(self, 2, 0, D_L17_001B0E9C);
            } else if (self[0x43] != 0xE) {
                anim_start_blended(self, 0xE, 0, D_L17_001B0E9C);
            }
        }
        break;
    case 8:
        if (flag_set_first_pending(self) != 0) {
            attempts = 0;
            do {
                point_index = grulch_pick_random_path_point(self);
                qcopy(&target_point, self + 0x10);
                qcopy(&probe_point, &((Vec *)g_path_l17_table[*(int *)(vars + 0x684)])[point_index + 1]);
                target_point.f[2] = target_point.f[2] + 1.0f;
                probe_point.f[2] = target_point.f[2];
                if (CollLine(&target_point, &probe_point, 0, self, 0) != 0) {
                    if (!(vec_distance_xy(self + 0x10, &D_L17_001C0020) < 2.0f)) {
                        qcopy(vars + 0x710, &D_L17_001C0020);
                        break;
                    }
                } else {
                    qcopy(vars + 0x710, &probe_point);
                    break;
                }
                attempts++;
            } while (attempts < 5);
            if (attempts != 5) {
                if (self[0x43] != 0xC) anim_start_blended(self, 0xC, 0, D_L17_001B0E9C);
            } else {
                moby_set_state(self, 3, -1);
                break;
            }
        }
        move_flags = moby_l01_turn_toward_target(self, vars + 0x710);
        StepAngleTowardTarget(self + 0xF8, 0, mat_fast_helper_a(*(float *)(vars + 0x710) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x714) - ((UView *)(self))->f[0x5]), 0.043633237f);
        if (!(move_flags & 0x80) && *(int *)(vars + 0x190) < 0xB && !(move_flags & 0x10F)) {
        } else {
            moby_set_state(self, 3, -1);
        }
        break;
    case 6:
        if (flag_set_first_pending(self) != 0) {
            if (((Moby *)g_moby_l17_pool[0])[*(int *)(vars + 0x6B8)].oclass != 0x929 /* moby class 2345 */) {
                if (self[0x43] != 1) anim_start_blended(self, 1, 0, D_L17_001B0E9C);
                moby_set_controller_speed_limits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            } else {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) anim_start_blended(self, 0xA, 0, D_L17_001B0E9C);
                moby_set_controller_speed_limits(self, (float)D_L17_001B0E68 * 0.00027777778f, D_L17_001B0E70 * 0.016666668f, 0.10471977f, 0.10471977f);
            }
            ((UView *)(self))->f[0x6] = coll_probe_ground_height_below(self + 0x10, 0, 3.0f);
            qcopy(vars + 0x6C0, self + 0x10);
        }
        if (self[0x60] & 2) {
            if (self[0x42] == 1) {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) anim_start_blended(self, 0xA, 0, 0x14);
                moby_l01_turn_toward_target(self, self + 0x10);
                goto s6_157;
            }
            goto s6_159;
        }
s6_157:
        if (self[0x42] == 1) {
            ((UView *)(self))->f[0x6] = coll_probe_ground_height_below(self + 0x10, 0, 3.0f);
            break;
        }
s6_159:
        if (self[0x42] == 0xA) {
            (&target_point)->f[0] = math_fast_sin_or_cos_a(((UView *)(self))->f[0x3E]) * 3.0f;
            (&target_point)->f[1] = math_fast_sin_or_cos_b(((UView *)(self))->f[0x3E]) * 3.0f;
            (&target_point)->f[2] = 0.0f;
            FastVecAdd(&probe_point, self + 0x10, (&target_point));
            ((UView *)(self))->f[0x6] = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
            moby_l01_turn_toward_target(self, &probe_point);
            if (!(vec_distance_xy(self + 0x10, vars + 0x6C0) > 4.9f)) {
            } else if (*(int *)(vars + 0x730) == 0 || D_L17_001FB720[self[0x21]] == 0 || (((UView *)(self))->f[0x12] = 1.0f, ClaimNearestObjectSlot(self) != 0)) {
                moby_set_state(self, 0xB, 2);
            } else {
                moby_set_state(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) anim_start_blended(self, 3, 0, 0x14);
            }
        }
        break;
    case 11:
        if (flag_set_first_pending(self) != 0) {
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) anim_start_blended(self, 0xA, 0, D_L17_001B0E9C);
            chase_scale = D_L17_001B0EB8;
            ((UView *)(self))->f[0x12] = -chase_scale;
            moby_set_controller_speed_limits(self, (float)D_L17_001B0E68 * 0.00027777778f, chase_scale * D_L17_001B0E70 * 0.016666668f, 0.05817765f, 0.05817765f);
        }
        if (self[0x42] == 0xA) {
            if (dist < D_L17_001B0E7C) {
                qcopy((&target_point), &D_L17_001B9BC0);
                if (vec_distance_xy((&target_point), self + 0x10) < D_L17_001B0EA4) {
                    if (*(int *)(vars + 0x738) < D_L17_001B0EA8) {
                        (&target_point)->f[2] = *(float *)(vars + 0x248);
                        FastVecSub((&target_point), vars + 0x240, (&target_point));
                        vec_scale_to_length((&target_point), (&target_point), 2.0f * D_L17_001B0EA4);
                        FastVecAdd((&target_point), &D_L17_001B9BC0, (&target_point));
                        probe_point.q = *(Quad *)(self + 0x10);
                        path_clamp_move_to_area(&probe_point, (&target_point), (&target_point), *(int *)(vars + 0x684), 3.0f);
                        fallback_distance = vec_distance_xy(self + 0x10, (&target_point));
                        if (D_L17_001B0EA4 + 0.3f < fallback_distance) {
                            moby_l01_turn_toward_target(self, (&target_point));
                            *(int *)(vars + 0x738) = *(int *)(vars + 0x738) + 1;
                            break;
                        }
                    } else {
                        goto s11_184;
                    }
                }
                if (*(int *)(vars + 0x738) >= D_L17_001B0EA8) {
s11_184:
                    STUB_printf(D_L17_001B0F20);
                }
                *(int *)(vars + 0x738) = 0;
                moby_set_state(self, 0xC, -1);
                ((UView *)(self))->f[0x12] = 1.0f;
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != math_random_int_below(2) + 4) anim_start_blended(self, math_random_int_below(2) + 4, 2, 0x14);
            } else {
                ComputeRegionRouteHeading(self + 0x10, vars + 0x240, &path_cost, vars + 0x280, *(int *)(vars + 0x750), vars + 0x758, vars + 0x754, 0.0f, 0.5f);
                moby_step_controller(self, vars + 0x240, path_cost);
                StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
                if (*(int *)(vars + 0x190) >= 0x3D) {
                    *(int *)(vars + 0x704) = D_L17_001B0E8C;
                    moby_set_state(self, 4, -1);
                    ((UView *)(self))->f[0x12] = 1.0f;
                    if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                    if (self[0x43] != 2) anim_start_blended(self, 2, 0, 0x14);
                }
            }
        }
        break;
    case 15:
        if (flag_set_first_pending(self) != 0 && self[0x43] != 1) anim_start_blended(self, 1, 0, 0x14);
        StepAngleTowardTarget(self + 0xF8, 0, mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), 0.10471977f);
        if (self[0x60] & 2) moby_set_state(self, 0xB, -1);
        break;
    case 12:
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
        bite_progress = moby_get_anim_value(self);
        if (bite_progress >= 13.0f && bite_progress <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, vars + 0x240) < D_L17_001B0E58
            && grulch_is_target_reachable(self) != 0) {
            hit_info.obj = self;
            hit_info.flags = 0x10001;
            hit_info.val = *(float *)(vars + 0x700);
            hit_info.sn = math_fast_sin_or_cos_a(mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
            hit_info.cs = math_fast_sin_or_cos_b(mat_fast_helper_a(*(float *)(vars + 0x240) - ((UView *)(self))->f[0x4], *(float *)(vars + 0x244) - ((UView *)(self))->f[0x5]));
            hit_info.one = 1.0f;
            hit_info.big = 5627.925f;
            hit_info.o = hit_info.k = 1;
            hit_info.z = 0;
            hit_info.id = ((UView *)(self))->uh[0x55];
            damage_type = self[0x42] == 4 ? D_L17_001B0EC4 : D_L17_001B0EC0;
            coll_test_hit_at_bone(D_L17_001B0EC8, *(float *)(vars + 0x700), 1.0f, self, damage_type, 0x10001, 0, 1, 0);
        }
        if ((u32)(self[0x42] - 4) < 2U && D_L17_001B0EAC <= bite_progress) moby_set_state(self, 0xD, -1);
        break;
    case 4:
        if (math_fast_float_d(vars + 0x704) != 0) {
            moby_set_state(self, 0xC, -1);
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != math_random_int_below(2) + 4) anim_start_blended(self, math_random_int_below(2) + 4, 0, 0x14);
        }
        break;
    case 13:
        if (flag_set_first_pending(self) != 0) {
            turn_angle = FastAddRotations(((UView *)(self))->f[0x3E], 3.141593f);
            (&target_point)->f[0] = math_fast_sin_or_cos_a(turn_angle) * D_L17_001B0E88;
            (&target_point)->f[1] = math_fast_sin_or_cos_b(turn_angle) * D_L17_001B0E88;
            (&target_point)->f[2] = 0.0f;
            FastVecAdd((&target_point), (&target_point), self + 0x10);
            probe_point.q = *(Quad *)(self + 0x10);
            path_clamp_move_to_area(&probe_point, (&target_point), (&target_point), *(int *)(vars + 0x684), 3.0f);
            if (fast_vec_dist(self + 0x10, (&target_point)) < D_L17_001B0E88 * 0.5f) {
                coll_find_clear_side_point(self + 0x10, vars + 0x240, (&target_point), *(int *)(vars + 0x684), D_L17_001B0E90, 1.0f);
            }
            qcopy(&probe_point, self + 0x10);
            probe_point.f[2] += 0.5f;
            qcopy(&probe_end, (&target_point));
            probe_end.f[2] += 0.5f;
            if (CollLine(&probe_point, &probe_end, 2, 0, 0) != 0) qcopy((&target_point), &D_L17_001C0020);
            qcopy(vars + 0x710, (&target_point));
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) anim_start_blended(self, 0xA, 0, D_L17_001B0E9C);
            moby_set_controller_speed_limits(self, (float)D_L17_001B0E6C * 0.00027777778f, D_L17_001B0E74 * 0.016666668f, 0.10471977f, 0.10471977f);
            *(int *)(vars + 0x708) = D_L17_001B0E94;
            grulch_release_slot(self);
            ((UView *)(self))->f[0x12] = D_L17_001B0EB8;
        }
        near_ground = 0;
        move_flags13 = moby_l01_turn_toward_target(self, vars + 0x710);
        moby_transform_joint_to_world(self, 3, (&target_point));
        if (coll_probe_ground_height_below((&target_point), 0, 0.5f) < 10.0f) near_ground = 1;
        if (!(move_flags13 & 0x80) && *(int *)(vars + 0x190) < 0xA && !(move_flags13 & 0xF) && near_ground != 1) {
        } else {
            ((UView *)(self))->f[0x12] = 1.0f;
            if (dist < D_L17_001B0E7C + D_L17_001B0E80) {
                moby_set_state(self, 0xC, -1);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != math_random_int_below(2) + 4) anim_start_blended(self, math_random_int_below(2) + 4, 0, 0x14);
            } else {
                moby_set_state(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) anim_start_blended(self, 3, 0, 0x14);
            }
        }
        if (math_fast_float_d(vars + 0x708) != 0 && dist < D_L17_001B0E7C) {
            moby_set_state(self, 0xC, -1);
            ((UView *)(self))->f[0x12] = 1.0f;
            if (self[0x43] != self[0x42]) STUB_printf(D_L17_001B0EE8, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != math_random_int_below(2) + 4) anim_start_blended(self, math_random_int_below(2) + 4, 0, 0x14);
        }
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.05817765f);
        break;
    case 9:
        if (flag_set_first_pending(self) != 0 && self[0x43] != 7) anim_start_blended(self, 7, 0, 0x14);
        qcopy((&target_point), self + 0x10);
        height = ((UView *)(self))->f[0x6] - 0.050000004f;
        (&target_point)->f[2] = 70.0f;
        ((UView *)(self))->f[0x6] = height;
        if (height < 70.0f) {
b262:
            SetDeathBits(self, 0, 3);
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    moby_transform_joint_to_world(self, D_L17_001B3940[0], (&target_point));
    if (coll_probe_ground_height_below((&target_point), 0, 1.0f) < 20.0f && self[0x95] != 3 && self[0x20] != 9) {
        if (self[0x20] == 0xD || self[0x20] == 0xB) moby_set_state(self, 9, 7);
    }
}
