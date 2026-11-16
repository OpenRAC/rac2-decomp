#include "common.h"

/* func_PAL_L17_003EB968, the PAL copy of func_L17_003E7068: the same C at 50 Hz. Frame counts
 * become literals or (x * 5 + 2) / 6, rates per frame are multiplied by 6/5. It has a unit of its
 * own for the template's two flags (config/cflags.txt). The scaled limit at st + 0x738 no longer
 * lets the jump thread past the second test, so the template's goto is gone here. */
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
extern void SetDeathBits_pal(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern int math_random_int_below(int);
extern float coll_probe_ground_height_below(void *, int, float);
extern int coll_test_hit_at_bone(float, float, float, void *, int, int, int, int, int);
extern void StepAngleTowardTarget(void *, int, float, float);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(u8 *);
extern int flag_set_second_pending(u8 *);
extern int moby_step_controller_pal(void *, void *, float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern int moby_l01_turn_toward_target_pal(void *, void *);
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
extern void func_PAL_L17_003ED568(void);
extern u8 g_hero_state[];
extern u8 *g_moby_l17_pool[] __attribute__((sda));
extern int g_snapper_joint_index[] __attribute__((sda));
extern u8 *g_group_l17_member_table[];
extern u8 *g_path_l17_table[];
extern Vec g_tether_origin_pos;
extern Vec g_aim_origin_vec;
extern char g_str_snapper_debug_a[], g_str_snapper_state_change[], g_str_snapper_debug_b[], g_str_snapper_debug_c[];
extern float g_snapper_min_value __attribute__((sda));
extern float g_snapper_chase_distance __attribute__((sda));
extern int g_snapper_turn_rate_a __attribute__((sda));
extern int g_snapper_turn_rate_b __attribute__((sda));
extern float g_snapper_speed_a __attribute__((sda));
extern float g_snapper_speed_b __attribute__((sda));
extern float g_snapper_attack_distance __attribute__((sda));
extern float g_snapper_attack_margin __attribute__((sda));
extern float g_snapper_turn_radius __attribute__((sda));
extern int g_snapper_int_param_a __attribute__((sda));
extern float g_snapper_side_point_dist __attribute__((sda));
extern int g_snapper_int_param_b __attribute__((sda));
extern int g_snapper_anim_blend_frames __attribute__((sda));
extern float g_snapper_arrive_distance __attribute__((sda));
extern int g_snapper_timer_limit __attribute__((sda));
extern float g_snapper_bite_end_progress __attribute__((sda));
extern float g_snapper_attack_hit_progress __attribute__((sda));
extern float g_snapper_attack_end_progress __attribute__((sda));
extern float g_snapper_chase_scale __attribute__((sda));
extern int g_snapper_damage_type_move __attribute__((sda));
extern int g_snapper_damage_type_bite __attribute__((sda));
extern float g_snapper_hit_radius __attribute__((sda));

void func_PAL_L17_003EB968(u8 *self) {
    Hit h;
    u8 *st = ((u8 *)((UView *)(self))->p[0x1A]);
    float dist, ang, f20, fa, fb, fc, fd, fe, ff, fg;
    Vec v30, v40, v50;
    float f60;
    int idx, a1, hit, n;
    int idx2, idx3;
    u8 *o2;
    int cnt, hit8, near, hit13;
    float fx;
    Moby *pool;

    func_PAL_L17_003ED568();
    dist = vec_distance_xy(self + 0x10, st + 0x240);
    ang = mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]);
    idx = *(int *)(st + 0x6B8);
    if (idx != -1) {
        if (((Moby *)g_moby_l17_pool[0])[idx].oclass != 0x929) {
            STUB_printf(g_str_snapper_debug_a);
        } else {
            platform_set_path_index((u8 *)&((Moby *)g_moby_l17_pool[0])[idx], self);
        }
    }
    switch (self[0x95]) {
    case 5:
        moby_transform_point_and_rotation_by_parent(self, g_moby_l17_pool[0] + (*(int *)(st + 0x6B8) << 8), self + 0x10, self + 0xF0, self + 0x10, self + 0xF0);
        idx2 = *(int *)(st + 0x6DC);
        if (idx2 == -1 || (o2 = g_moby_l17_pool[0] + (idx2 << 8)) == self || o2 == 0 || o2[0x20] == 0xFE || o2[0x20] == 0xFD) {
            idx3 = *(int *)(st + 0x6B8);
            if (idx3 != -1) {
                if (*(s16 *)(st + 0x69E) == 1 && ride_platform_can_start(g_moby_l17_pool[0] + (idx3 << 8))) {
                    ride_platform_start(g_moby_l17_pool[0] + (*(int *)(st + 0x6B8) << 8));
                    if (((Moby *)g_moby_l17_pool[0])[*(int *)(st + 0x6B8)].oclass == 0x929) {
                        if (self[0x20] != 6) moby_set_state(self, 6, -1);
                        pool = (Moby *)g_moby_l17_pool[0];
                        ((UView *)(self))->uh[0x1A] = ((UView *)(self))->uh[0x1A] & 0xFFBE;
                        ((UView *)(self))->i[0x26] = *(int *)(((u8 *)((UView *)(self))->p[0x9]) + 0x10);
                        ((UView *)(self))->f[0x3E] = pool[*(int *)(st + 0x6B8)].rotz;
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
        if (*(s16 *)(st + 0x69E) == 1) {
            if (*(int *)(st + 0x730) == 0 || g_group_l17_member_table[self[0x21]] == 0 || ClaimNearestObjectSlot(self) != 0) {
                moby_set_state(self, 0xF, 2);
            } else {
                moby_set_state(self, 7, 6);
                if (self[0x43] != 1) func_PAL_002A7E68(self, 1, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            }
            moby_set_controller_speed_limits(self, (float)g_snapper_turn_rate_a * 0.00040000002f, g_snapper_speed_a * 0.020000001f, 0.12566373f, 0.12566373f);
            *(s16 *)(st + 0x69C) = 0xA7;
            *(int *)(st + 0x148) = *(int *)(st + 0x148) | 0x10;
        }
        break;
    case 2:
        if (*(s16 *)(st + 0x69E) == 1) *(s16 *)(st + 0x69C) = 0xA7;
        if (FastDecTimer((short *)(st + 0x69C)) != 0) {
            moby_set_state(self, 5, 4);
            if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 3) func_PAL_002A7E68(self, 3, 0, 0x11);
            *(s16 *)(st + 0x69C) = 0xB7;
        }
        break;
    case 4:
        if (*(s16 *)(st + 0x69E) == 1) goto alert;
        goto b62;
    case 6:
        if (ClaimNearestObjectSlot(self) != 0) {
            if ((self[0x42] != 1 && self[0x43] != 1) || (self[0x60] & 2)) {
alert:
                moby_set_state(self, 0xB, 2);
                moby_set_controller_speed_limits(self, (float)g_snapper_turn_rate_a * 0.00040000002f, g_snapper_speed_a * 0.020000001f, 0.12566373f, 0.12566373f);
                *(s16 *)(st + 0x69C) = 0xA7;
                *(int *)(st + 0x148) = *(int *)(st + 0x148) | 0x10;
            }
        } else {
            f20 = moby_get_anim_value(self);
            if (*(s16 *)(st + 0x69E) == 1) *(s16 *)(st + 0x69C) = 0xA7;
            if ((self[0x60] & 2) && self[0x42] == 3 && self[0x43] != 0xE) func_PAL_002A7E68(self, 0xE, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            if (f20 >= 20.0f && self[0x42] == 0xE && self[0x43] != 3) func_PAL_002A7E68(self, 3, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            if (self[0x60] & 2) {
                if (self[0x42] == 1) {
                    if (self[0x43] != 0xE) func_PAL_002A7E68(self, 0xE, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
                    goto b60;
                }
            } else {
b60:
                if (self[0x42] == 1) {
                    StepAngleTowardTarget(self + 0xF8, 0, mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), 0.12566373f);
                }
            }
b62:
            if (FastDecTimer((short *)(st + 0x69C)) != 0) {
                if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 2) func_PAL_002A7E68(self, 2, 0, 0x11);
                moby_set_state(self, 3, 0);
            }
        }
        break;
    case 3:
        if (flag_set_second_pending(self) != 0) {
            fa = ((UView *)(self))->f[0x12];
            if (fa <= 0.0f || fa > 1.0f) ((UView *)(self))->f[0x12] = 1.0f;
            moby_set_controller_speed_limits(self, (float)(g_snapper_turn_rate_a * 8) * 0.00040000002f, g_snapper_speed_a * 0.16000001f, 0.12566373f, 0.12566373f);
        }
        if (((UView *)(self))->f[0x6] < g_snapper_min_value) goto b262;
        if (*(float *)(st + 0xE8) > 0.020000001f) {
            *(float *)(st + 0xE8) = 0.020000001f;
            STUB_printf(g_str_snapper_debug_b);
        }
        hit = moby_dispatch_action_by_kind(self, st + 0x60);
        if (hit & 1) {
            part_queue_moby_for_glow(self, 0, 0);
            SetDeathBits_pal(self, 0, 3);
        }
        fb = moby_get_anim_value(self);
        if (fb >= 13.0f && fb <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, st + 0x240) < g_snapper_chase_distance) {
            if (self[0x42] == 4) {
                if (grulch_is_target_reachable(self) != 0) {
                    h.obj = self;
                    h.flags = 0x10001;
                    h.val = *(float *)(st + 0x700);
                    h.sn = math_fast_sin_or_cos_a(mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
                    h.cs = math_fast_sin_or_cos_b(mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
                    h.one = 1.0f;
                    h.big = 5627.925f;
                    h.o = h.k = 1;
                    h.z = 0;
                    h.id = ((UView *)(self))->uh[0x55];
                    a1 = self[0x42] == 4 ? g_snapper_damage_type_bite : g_snapper_damage_type_move;
                    coll_test_hit_at_bone(g_snapper_hit_radius, *(float *)(st + 0x700), 1.0f, self, a1, 0x10001, 0, 1, 0);
                }
            }
        }
        if ((self[0x42] == 4 || self[0x43] == 4) && !(fb > 13.0f)) {
            moby_l01_turn_toward_target_pal(self, st + 0x240);
        }
        if ((hit & 2) && g_snapper_attack_hit_progress <= fb) moby_set_state(self, 0xD, 2);
        if (self[0x42] == 0xD && g_snapper_attack_end_progress <= fb) {
            if (self[0x43] != 4) func_PAL_002A7E68(self, 4, 0, 8);
            *(s16 *)(g_hero_state + 0x1DC) = 0;
        }
        break;
    }
    switch (self[0x20]) {
    case 3:
        if (flag_set_first_pending(self) != 0) {
            if (math_random_int_below(2) == 0) {
                if (self[0x43] != 2) func_PAL_002A7E68(self, 2, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            } else if (self[0x43] != 0xE) {
                func_PAL_002A7E68(self, 0xE, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            }
        }
        fg = moby_get_anim_value(self);
        if ((self[0x42] == 2 && (self[0x60] & 2)) || (self[0x42] == 0xE && fg >= 20.0f)) {
            if (math_random_int_below(2) == 0) {
                if (self[0x43] != 2) func_PAL_002A7E68(self, 2, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            } else if (self[0x43] != 0xE) {
                func_PAL_002A7E68(self, 0xE, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            }
        }
        break;
    case 8:
        if (flag_set_first_pending(self) != 0) {
            cnt = 0;
            do {
                n = grulch_pick_random_path_point(self);
                qcopy(&v30, self + 0x10);
                qcopy(&v40, &((Vec *)g_path_l17_table[*(int *)(st + 0x684)])[n + 1]);
                v30.f[2] = v30.f[2] + 1.0f;
                v40.f[2] = v30.f[2];
                if (CollLine(&v30, &v40, 0, self, 0) != 0) {
                    if (!(vec_distance_xy(self + 0x10, &g_aim_origin_vec) < 2.0f)) {
                        qcopy(st + 0x710, &g_aim_origin_vec);
                        break;
                    }
                } else {
                    qcopy(st + 0x710, &v40);
                    break;
                }
                cnt++;
            } while (cnt < 5);
            if (cnt != 5) {
                if (self[0x43] != 0xC) func_PAL_002A7E68(self, 0xC, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            } else {
                moby_set_state(self, 3, -1);
                break;
            }
        }
        hit8 = moby_l01_turn_toward_target_pal(self, st + 0x710);
        StepAngleTowardTarget(self + 0xF8, 0, mat_fast_helper_a(*(float *)(st + 0x710) - ((UView *)(self))->f[0x4], *(float *)(st + 0x714) - ((UView *)(self))->f[0x5]), 0.052359886f);
        if (!(hit8 & 0x80) && *(int *)(st + 0x190) < 9 && !(hit8 & 0x10F)) {
        } else {
            moby_set_state(self, 3, -1);
        }
        break;
    case 6:
        if (flag_set_first_pending(self) != 0) {
            if (((Moby *)g_moby_l17_pool[0])[*(int *)(st + 0x6B8)].oclass != 0x929) {
                if (self[0x43] != 1) func_PAL_002A7E68(self, 1, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
                moby_set_controller_speed_limits(self, (float)g_snapper_turn_rate_a * 0.00040000002f, g_snapper_speed_a * 0.020000001f, 0.12566373f, 0.12566373f);
            } else {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) func_PAL_002A7E68(self, 0xA, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
                moby_set_controller_speed_limits(self, (float)g_snapper_turn_rate_a * 0.00040000002f, g_snapper_speed_a * 0.020000001f, 0.12566373f, 0.12566373f);
            }
            ((UView *)(self))->f[0x6] = coll_probe_ground_height_below(self + 0x10, 0, 3.0f);
            qcopy(st + 0x6C0, self + 0x10);
        }
        if (self[0x60] & 2) {
            if (self[0x42] == 1) {
                ((UView *)(self))->f[0x12] = -1.0f;
                if (self[0x43] != 0xA) func_PAL_002A7E68(self, 0xA, 0, 0x11);
                moby_l01_turn_toward_target_pal(self, self + 0x10);
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
            (&v30)->f[0] = math_fast_sin_or_cos_a(((UView *)(self))->f[0x3E]) * 3.0f;
            (&v30)->f[1] = math_fast_sin_or_cos_b(((UView *)(self))->f[0x3E]) * 3.0f;
            (&v30)->f[2] = 0.0f;
            FastVecAdd(&v40, self + 0x10, (&v30));
            ((UView *)(self))->f[0x6] = coll_probe_ground_height_below(self + 0x10, 0, 0.5f);
            moby_l01_turn_toward_target_pal(self, &v40);
            if (!(vec_distance_xy(self + 0x10, st + 0x6C0) > 4.9f)) {
            } else if (*(int *)(st + 0x730) == 0 || g_group_l17_member_table[self[0x21]] == 0 || (((UView *)(self))->f[0x12] = 1.0f, ClaimNearestObjectSlot(self) != 0)) {
                moby_set_state(self, 0xB, 2);
            } else {
                moby_set_state(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) func_PAL_002A7E68(self, 3, 0, 0x11);
            }
        }
        break;
    case 11:
        if (flag_set_first_pending(self) != 0) {
            if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) func_PAL_002A7E68(self, 0xA, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            fc = g_snapper_chase_scale;
            ((UView *)(self))->f[0x12] = -fc;
            moby_set_controller_speed_limits(self, (float)g_snapper_turn_rate_a * 0.00040000002f, fc * g_snapper_speed_a * 0.020000001f, 0.06981318f, 0.06981318f);
        }
        if (self[0x42] == 0xA) {
            if (dist < g_snapper_attack_distance) {
                qcopy((&v30), &g_tether_origin_pos);
                if (vec_distance_xy((&v30), self + 0x10) < g_snapper_arrive_distance) {
                    if (*(int *)(st + 0x738) < (g_snapper_timer_limit * 5 + 2) / 6) {
                        (&v30)->f[2] = *(float *)(st + 0x248);
                        FastVecSub((&v30), st + 0x240, (&v30));
                        vec_scale_to_length((&v30), (&v30), 2.0f * g_snapper_arrive_distance);
                        FastVecAdd((&v30), &g_tether_origin_pos, (&v30));
                        v40.q = *(Quad *)(self + 0x10);
                        path_clamp_move_to_area(&v40, (&v30), (&v30), *(int *)(st + 0x684), 3.0f);
                        fx = vec_distance_xy(self + 0x10, (&v30));
                        if (g_snapper_arrive_distance + 0.3f < fx) {
                            moby_l01_turn_toward_target_pal(self, (&v30));
                            *(int *)(st + 0x738) = *(int *)(st + 0x738) + 1;
                            break;
                        }
                    }
                }
                if (*(int *)(st + 0x738) >= (g_snapper_timer_limit * 5 + 2) / 6) {
                    STUB_printf(g_str_snapper_debug_c);
                }
                *(int *)(st + 0x738) = 0;
                moby_set_state(self, 0xC, -1);
                ((UView *)(self))->f[0x12] = 1.0f;
                if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != math_random_int_below(2) + 4) func_PAL_002A7E68(self, math_random_int_below(2) + 4, 2, 0x11);
            } else {
                ComputeRegionRouteHeading(self + 0x10, st + 0x240, &f60, st + 0x280, *(int *)(st + 0x750), st + 0x758, st + 0x754, 0.0f, 0.5f);
                moby_step_controller_pal(self, st + 0x240, f60);
                StepAngleTowardTarget(self + 0xF8, 0, ang, 0.06981318f);
                if (*(int *)(st + 0x190) >= 0x33) {
                    *(int *)(st + 0x704) = (g_snapper_int_param_a * 5 + 2) / 6;
                    moby_set_state(self, 4, -1);
                    ((UView *)(self))->f[0x12] = 1.0f;
                    if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
                    if (self[0x43] != 2) func_PAL_002A7E68(self, 2, 0, 0x11);
                }
            }
        }
        break;
    case 15:
        if (flag_set_first_pending(self) != 0 && self[0x43] != 1) func_PAL_002A7E68(self, 1, 0, 0x11);
        StepAngleTowardTarget(self + 0xF8, 0, mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), 0.12566373f);
        if (self[0x60] & 2) moby_set_state(self, 0xB, -1);
        break;
    case 12:
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.06981318f);
        fd = moby_get_anim_value(self);
        if (fd >= 13.0f && fd <= 14.0f && self[0x42] == self[0x43]
            && FastDiffRots(mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]), ((UView *)(self))->f[0x3E]) < 1.9198624f
            && fast_vec_dist(self + 0x10, st + 0x240) < g_snapper_chase_distance
            && grulch_is_target_reachable(self) != 0) {
            h.obj = self;
            h.flags = 0x10001;
            h.val = *(float *)(st + 0x700);
            h.sn = math_fast_sin_or_cos_a(mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
            h.cs = math_fast_sin_or_cos_b(mat_fast_helper_a(*(float *)(st + 0x240) - ((UView *)(self))->f[0x4], *(float *)(st + 0x244) - ((UView *)(self))->f[0x5]));
            h.one = 1.0f;
            h.big = 5627.925f;
            h.o = h.k = 1;
            h.z = 0;
            h.id = ((UView *)(self))->uh[0x55];
            a1 = self[0x42] == 4 ? g_snapper_damage_type_bite : g_snapper_damage_type_move;
            coll_test_hit_at_bone(g_snapper_hit_radius, *(float *)(st + 0x700), 1.0f, self, a1, 0x10001, 0, 1, 0);
        }
        if ((u32)(self[0x42] - 4) < 2U && g_snapper_bite_end_progress <= fd) moby_set_state(self, 0xD, -1);
        break;
    case 4:
        if (math_fast_float_d(st + 0x704) != 0) {
            moby_set_state(self, 0xC, -1);
            if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != math_random_int_below(2) + 4) func_PAL_002A7E68(self, math_random_int_below(2) + 4, 0, 0x11);
        }
        break;
    case 13:
        if (flag_set_first_pending(self) != 0) {
            fe = FastAddRotations(((UView *)(self))->f[0x3E], 3.141593f);
            (&v30)->f[0] = math_fast_sin_or_cos_a(fe) * g_snapper_turn_radius;
            (&v30)->f[1] = math_fast_sin_or_cos_b(fe) * g_snapper_turn_radius;
            (&v30)->f[2] = 0.0f;
            FastVecAdd((&v30), (&v30), self + 0x10);
            v40.q = *(Quad *)(self + 0x10);
            path_clamp_move_to_area(&v40, (&v30), (&v30), *(int *)(st + 0x684), 3.0f);
            if (fast_vec_dist(self + 0x10, (&v30)) < g_snapper_turn_radius * 0.5f) {
                coll_find_clear_side_point(self + 0x10, st + 0x240, (&v30), *(int *)(st + 0x684), g_snapper_side_point_dist, 1.0f);
            }
            qcopy(&v40, self + 0x10);
            v40.f[2] += 0.5f;
            qcopy(&v50, (&v30));
            v50.f[2] += 0.5f;
            if (CollLine(&v40, &v50, 2, 0, 0) != 0) qcopy((&v30), &g_aim_origin_vec);
            qcopy(st + 0x710, (&v30));
            if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != 0xA) func_PAL_002A7E68(self, 0xA, 0, (g_snapper_anim_blend_frames * 5 + 2) / 6);
            moby_set_controller_speed_limits(self, (float)g_snapper_turn_rate_b * 0.00040000002f, g_snapper_speed_b * 0.020000001f, 0.12566373f, 0.12566373f);
            *(int *)(st + 0x708) = (g_snapper_int_param_b * 5 + 2) / 6;
            grulch_release_slot(self);
            ((UView *)(self))->f[0x12] = g_snapper_chase_scale;
        }
        near = 0;
        hit13 = moby_l01_turn_toward_target_pal(self, st + 0x710);
        moby_transform_joint_to_world(self, 3, (&v30));
        if (coll_probe_ground_height_below((&v30), 0, 0.5f) < 10.0f) near = 1;
        if (!(hit13 & 0x80) && *(int *)(st + 0x190) < 8 && !(hit13 & 0xF) && near != 1) {
        } else {
            ((UView *)(self))->f[0x12] = 1.0f;
            if (dist < g_snapper_attack_distance + g_snapper_attack_margin) {
                moby_set_state(self, 0xC, -1);
                if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != math_random_int_below(2) + 4) func_PAL_002A7E68(self, math_random_int_below(2) + 4, 0, 0x11);
            } else {
                moby_set_state(self, 7, 6);
                if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
                if (self[0x43] != 3) func_PAL_002A7E68(self, 3, 0, 0x11);
            }
        }
        if (math_fast_float_d(st + 0x708) != 0 && dist < g_snapper_attack_distance) {
            moby_set_state(self, 0xC, -1);
            ((UView *)(self))->f[0x12] = 1.0f;
            if (self[0x43] != self[0x42]) STUB_printf(g_str_snapper_state_change, self[0x42], ((UView *)(self))->h[0x59]);
            if (self[0x43] != math_random_int_below(2) + 4) func_PAL_002A7E68(self, math_random_int_below(2) + 4, 0, 0x11);
        }
        StepAngleTowardTarget(self + 0xF8, 0, ang, 0.06981318f);
        break;
    case 9:
        if (flag_set_first_pending(self) != 0 && self[0x43] != 7) func_PAL_002A7E68(self, 7, 0, 0x11);
        qcopy((&v30), self + 0x10);
        ff = ((UView *)(self))->f[0x6] - 0.060000002f;
        (&v30)->f[2] = 70.0f;
        ((UView *)(self))->f[0x6] = ff;
        if (ff < 70.0f) {
b262:
            SetDeathBits_pal(self, 0, 3);
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    moby_transform_joint_to_world(self, g_snapper_joint_index[0], (&v30));
    if (coll_probe_ground_height_below((&v30), 0, 1.0f) < 20.0f && self[0x95] != 3 && self[0x20] != 9) {
        if (self[0x20] == 0xD || self[0x20] == 0xB) moby_set_state(self, 9, 7);
    }
}
