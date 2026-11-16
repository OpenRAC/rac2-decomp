#include "names.h"
/* func_PAL_L11_00458F28, the PAL copy of func_L11_00453358: the same C, where rename func_L11_00454508 becomes func_PAL_L11_0045A0D8; rename func_L01_00321178 becomes func_PAL_L01_00323068; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L02_00333438 becomes func_PAL_L02_00335630; rename func_002B4FF0 becomes func_PAL_002B5BA8; rename-macro func_L02_003FC248 becomes func_PAL_L02_004009A0; rename func_L11_00454DD8 becomes func_PAL_L11_0045A9A8; rename func_L11_00441A38 becomes func_PAL_L02_004009A0. */
/* func_PAL_L11_00458F28: the Joba drone's state machine (patrol path, chase, grab, release, fall).
 * Own -G8 unit: the level gate D_L11_001A8FF4 and D_L11_001B1D40 are $gp-relative, and its jump
 * table and float pool need a .rodata of their own.
 * The four spilled pointers (self+0x10, self+0xC0, self+0xF0, pv+0x1B0) are gcse reaching
 * registers; their stack slots follow gcse's hash-bucket order, which depends on the insn count
 * at gcse. The anim() and turn() helpers are inlined; written as helpers they give retail's count
 * (539 buckets) without changing any instruction.
 * Case 9's `height = 0.0f;` is the same construct as case 9 of the matched twin
 * func_L02_0040BE08: it keeps case 9's tail apart from case 13's in jump2's cross-jumping.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 q; } Vec;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

extern char g_hero_state[];
extern s32 g_hero_l11_input_blocked __attribute__((sda));
extern f32 g_drone_target_angle_a __attribute__((sda));
extern f32 g_drone_target_angle_b;
extern f32 g_drone_target_angle_c;
extern u8 *g_path_l11_table[];

extern int CollLine(void *, void *, int, void *, void *);
extern s32 coll_test_point(void *, s32, void *, float);
extern float math_fabs(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float mat_fast_helper_a(float, float);
extern void euler_rotation_basis(void *, void *);
extern float FastAddRotations(float, float);
extern void func_002A677C(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern int coll_sweep_from_object(void *, void *, int, float, float, float, int, int, int);
extern int coll_test_hit_at_bone(void *, int, int, float, float, float, int, int, int);
extern float math_move_angle_toward_target(float, float, float);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void mat_get_euler_angles(void *, void *);
extern int flag_set_first_pending(u8 *);
extern int flag_set_second_pending(u8 *);
extern void moby_rotate_about_point(void *, void *, float, float, float);
extern int moby_turn_toward_target_and_step_pal(void *, void *, float);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern char *part_spawn_ground_effect(void *, float, float, int, unsigned int, int, int, void *, float, int);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern void moby_aim_at_target_offset_pal(void *, void *);
extern int hero_set_control_motion_and_step(void *, void *);
extern u8 *arena_get_center_point(u8 *);
extern int arena_is_point_in_polygon(u8 *, void *);
extern void moby_set_anim_type_three_pal(u8 *, int, int);
extern void drone_launcher_update_state_pal(u8 *);
extern void drone_update_timer(u8 *);
extern void drone_reset_to_idle_pal(u8 *);

/* Start animation a (blend b) unless it is already playing. */
static __inline__ void anim(u8 *self, int a, int b)
{
    if (self[0x43] != a)
        anim_start_blended_pal(self, a, 0, b);
}

/* Movement tuning with the shared turn limits. */
static __inline__ void turn(u8 *self, float rate, float speed)
{
    moby_set_controller_speed_limits(self, rate, speed, 0.0016755164f, 0.12566373f);
}

/* Per-frame update of the Joba drone (moby class 3575): it patrols its path, chases, grabs and releases the player, and falls when hit. */
void drone_update_pal(u8 *self)
{
    f32 target_pos[4];
    f32 goal[4];
    f32 step[4];
    f32 offset[4];
    f32 basis[4][4];
    u8 *vars;
    u8 *center;
    f32 target_dist;
    f32 height;

    vars = *(u8 **)(self + 0x68);
    if (self[0x20] == 1)
        return;
    if (*(s16 *)(vars + 0x1FC) != 0 && g_hero_l11_input_blocked == 0 && self[0x20] != 0xE && self[0x20] != 0xD)
        return;
    drone_launcher_update_state_pal(self);
    if (*(u8 **)(vars + 0x1C4) != 0) {
        *(TI128 *)target_pos = *(TI128 *)(*(u8 **)(vars + 0x1C4) + 0x10);
        mat_fast_helper_a(*(f32 *)(*(u8 **)(vars + 0x1C4) + 0x10) - *(f32 *)(self + 0x10),
                      *(f32 *)(*(u8 **)(vars + 0x1C4) + 0x14) - *(f32 *)(self + 0x14));
    } else {
        *(Vec *)target_pos = *(Vec *)(g_hero_state + 0x80);
        mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(self + 0x10),
                      ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(self + 0x14));
    }
    target_dist = fast_vec_dist((self + 0x10), target_pos);
    if (self[0x20] == 1)
        return;
    if (*(s16 *)(vars + 0x1FC) != 0 && g_hero_l11_input_blocked == 0)
        return;
    center = 0;
    if (*(s32 *)(self + 0xB8) != 0)
        center = arena_get_center_point(*(u8 **)(self + 0xB8));

    switch (self[0x20]) {
    case 3: {
        if (flag_set_first_pending(self) != 0) {
            turn(self, 0.040000003f, 2.0000002f);
            self[0xBC] = 0;
            *(u16 *)(self + 0x96) = 0;
        }
        if (self[0xBC] == 0 && *(u16 *)(self + 0x96) > *(s16 *)(vars + 0x1EE)) {
            self[0xBC] = 1;
            break;
        }
        if (self[0xBC] == 1) {
            if (arena_is_point_in_polygon(*(u8 **)(self + 0xB8), (self + 0x10)) != 0)
                moby_set_state(self, 7, 3);
            moby_l01_turn_toward_target_pal(self, arena_get_center_point(*(u8 **)(self + 0xB8)));
        }
        break;
    }
    case 4:
        if (flag_set_first_pending(self) != 0)
            *(u16 *)(self + 0x96) = 0;
        if (*(u16 *)(self + 0x96) < 0x16)
            break;
        anim(self, 0, 4);
        moby_set_state(self, 8, 3);
        break;
    case 7: {
        u8 *path;
        u8 *point;
        s32 i;
        s32 best;
        f32 best_dist;
        f32 reach;

        if (*(s16 *)(vars + 0x1FC) != 0)
            path = g_path_l11_table[*(s32 *)(vars + 0x1E0)];
        else
            path = g_path_l11_table[*(s32 *)(vars + 0x1C0)];
        if (flag_set_first_pending(self) != 0) {
            point = path + 0x10;
            best = 0;
            turn(self, 0.040000003f, 4.0000005f);
            *(f32 *)(vars + 0x1C8) = math_random_float_range(1.0f, 3.0f);
            best_dist = fast_vec_dist((self + 0x10), point);
            for (i = 0; i < *(s32 *)path - 1; i++, point += 0x10) {
                f32 next_dist = fast_vec_dist((self + 0x10), point);
                if (next_dist < best_dist) {
                    best_dist = next_dist;
                    best = i;
                }
            }
            *(s32 *)(vars + 0x1D4) = best;
            *(s16 *)(vars + 0x1E8) = math_random_int_below(2);
        } else {
            qcopy(goal, path + 0x10 + (*(s32 *)(vars + 0x1D4) << 4));
            if (*(s16 *)(vars + 0x1FC) != 0) {
                FastVecSub(offset, goal, center);
                offset[2] = 0.0f;
                vec_scale_to_length(offset, offset, 15.0f - *(f32 *)(vars + 0x1C8));
                goal[0] = *(f32 *)(center + 0) + offset[0];
                goal[1] = *(f32 *)(center + 4) + offset[1];
            } else {
                goal[2] = *(f32 *)(vars + 0x1C8) + *(f32 *)(center + 8);
            }
            FastVecSub(step, goal, (self + 0x10));
            reach = 2.0f;
            vec_scale_to_length(step, step, *(f32 *)(vars + 0x1D8));
            FastVecAdd((self + 0x10), (self + 0x10), step);
            if (*(s16 *)(vars + 0x1FC) != 0)
                reach = 4.0f;
            if (*(s16 *)(vars + 0x1E8) != 0) {
                if (fast_vec_dist((self + 0x10), goal) < reach)
                    *(s32 *)(vars + 0x1D4) -= 1;
                if (*(s32 *)(vars + 0x1D4) < 0)
                    *(s32 *)(vars + 0x1D4) = *(s32 *)path - 1;
            } else {
                if (fast_vec_dist((self + 0x10), goal) < reach)
                    *(s32 *)(vars + 0x1D4) += 1;
                if (*(s32 *)(vars + 0x1D4) >= *(s32 *)path)
                    *(s32 *)(vars + 0x1D4) = 0;
            }
            if (*(s32 *)(vars + 0x1D4) >= *(s32 *)path - 6 && *(f32 *)(vars + 0x1D8) >= 0.120000005f)
                *(f32 *)(vars + 0x1D8) = *(f32 *)(vars + 0x1D8) - 0.0036000002f;
            func_002A677C(self);
            if (*(s16 *)(vars + 0x1FC) != 0) {
                moby_aim_at_target_offset_pal(self, goal);
            } else {
                moby_turn_toward_target_and_step_pal(self, goal, *(f32 *)(vars + 0x1D0));
                math_step_value_toward_target(self + 0x18, vars + 0x108, *(f32 *)(vars + 0x1C8), 0.00080000004f, 0.00080000004f,
                              0.20000002f);
            }
        }
        if (*(s16 *)(vars + 0x1EC) != 0)
            moby_set_state(self, 8, 3);
        break;
    }
    case 8: {
        s32 reached;
        if (flag_set_first_pending(self) != 0)
            turn(self, 0.016f, 1.6000001f);
        reached = 0;
        if (*(s16 *)(vars + 0x1FC) != 0) {
            if (4.0f < target_dist) {
                FastVecSub(goal, target_pos, (self + 0x10));
                vec_scale_to_length(goal, goal, 10.0f);
                FastVecAdd(goal, goal, (self + 0x10));
                moby_aim_at_target_offset_pal(self, goal);
            } else {
                moby_aim_at_target_offset_pal(self, target_pos);
            }
            reached = target_dist < 4.0f;
        } else {
            height = *(f32 *)(center + 8) + 0.5f;
            math_step_value_toward_target(self + 0x18, vars + 0x108, height, 0.008f, 0.040000003f, 0.20000002f);
            moby_turn_toward_target_and_step_pal(self, target_pos, *(f32 *)(vars + 0x1D0));
            if (math_fabs(*(f32 *)(self + 0x18) - height) < 0.1f &&
                vec_distance_xy((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16]) < 2.0f)
                reached = 1;
        }
        if (reached) {
            *(u16 *)(self + 0x96) = 0;
            moby_set_state(self, 10, -1);
        }
        coll_sweep_from_object(self, (self + 0x10), 1, 0.3f, (f32)vars[0x34], 1.0f, 0, 1, 0);
        break;
    }
    case 9:
        if (flag_set_first_pending(self) != 0)
            anim(self, 2, 2);
        if (self[0x60] & 2) {
            anim(self, 3, 4);
            moby_set_state(self, 11, -1);
        }
        height = 0.0f;
        break;
    case 11: {
        s32 i;
        f32 reach;
        if (flag_set_second_pending(self) != 0) {
            turn(self, 0.0032000002f, 0.080000006f);
            *(u16 *)(self + 0x96) = 0;
        }
        *(f32 *)(self + 0x48) = 1.75f;
        for (i = 0; i < 4; i++)
            coll_test_hit_at_bone(self, i, 1, 0.5f, (f32)vars[0x34], 1.0f, 0, 1, 0);
        reach = 1.8f;
        if (reach <= fast_vec_dist((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16])) {
            qcopy(goal, target_pos);
        } else if (fast_vec_dist((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16]) < reach) {
            FastVecSub(goal, (self + 0x10), target_pos);
            vec_scale_to_length(goal, goal, 2.0f);
            FastVecAdd(goal, goal, (self + 0x10));
        } else {
            qcopy(goal, (self + 0x10));
        }
        if (*(s16 *)(vars + 0x1FC) != 0) {
            moby_aim_at_target_offset_pal(self, goal);
        } else {
            math_step_value_toward_target(self + 0x18, vars + 0x108, *(f32 *)(center + 8) + 0.5f, 0.008f, 0.040000003f,
                          0.20000002f);
            moby_l01_turn_toward_target_pal(self, goal);
        }
        if (((Hero *)g_hero_state)->ptr[0x249C / 4] == self) {
            moby_set_state(self, 12, -1);
            anim(self, 4, 4);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        if (fast_vec_dist((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16]) > 4.0f && *(u16 *)(self + 0x96) >= 0x65) {
            anim(self, 5, 12);
            moby_set_state(self, 4, -1);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        break;
    }
    case 12:
        if (!(self[0x60] & 2))
            break;
        anim(self, 0, 12);
        moby_set_state(self, 8, -1);
        break;
    case 10:
        if (*(u16 *)(self + 0x96) >= 0xc) {
            moby_set_state(self, 9, -1);
            anim(self, 2, 2);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        qcopy(goal, (self + 0x10));
        if (target_dist < 1.0f)
            coll_sweep_from_object(self, goal, 1, 0.3f, (f32)vars[0x34], 1.0f, 0, 1, 0);
        break;
    case 13:
        qcopy_nc(goal, (self + 0x10));
        *(f32 *)(vars + 0x108) = *(f32 *)(vars + 0x108) - *(f32 *)(vars + 0x8C);
        FastVecAdd((self + 0x10), (self + 0x10), vars + 0x100);
        if (CollLine(goal, (self + 0x10), 0, self, 0) == 0 && coll_test_point((self + 0x10), 4, self, 0.3f) == 0 &&
            math_random_int_below(0x1E) != 0)
            break;
        coll_sweep_from_object(self, (self + 0x10), 0x10000, 0.5f, (f32)vars[0x34], 1.0f, 0, 1, 0);
        if (*(f32 *)(vars + 0x20) > 0.0f) {
            moby_set_state(self, 8, 3);
            anim(self, 0, 4);
        } else if (*(s16 *)(vars + 0x1FC) != 0 && math_random_int_below(2) == 0) {
            moby_set_state(self, 14, -1);
        } else {
            moby_set_anim_type_three_pal(self, 0, 1);
            drone_reset_to_idle_pal(self);
        }
        break;
    case 14: {
        s32 j;
        u8 *ring_center;
        f32 *rot;
        if (flag_set_first_pending(self) != 0) {
            ring_center = arena_get_center_point(*(u8 **)(self + 0xB8));
            FastVecSub(vars + 0x100, ring_center, (self + 0x10));
            *(f32 *)(vars + 0x108) = 0.0f;
            vec_scale_to_length(vars + 0x100, vars + 0x100, math_random_float_range(3.0f, 5.0f) * 0.020000001f);
            *(s16 *)(vars + 0x1FC) = 0;
            for (j = 0; j < 3; j++) {
                rot = (f32 *)(vars + 0x1B0);
                rot[j] = math_random_float_range(240.0f, 720.0f) * 0.0003490659f;
                qcopy(basis[j], self + 0xC0 + j * 0x10);
            }
            mat_get_euler_angles(basis, self + 0xF0);
            *(u16 *)(self + 0x34) &= 0xEFFF;
        }
        *(f32 *)(vars + 0x108) = *(f32 *)(vars + 0x108) - *(f32 *)(vars + 0x8C);
        hero_set_control_motion_and_step(self, vars + 0x100);
        FastVecScale(vars + 0x1B0, vars + 0x1B0, 0.98f);
        *(TI128 *)step = 0;
        step[2] = *(f32 *)(vars + 0x30);
        *(TI128 *)goal = *(TI128 *)step;
        moby_rotate_about_point(self, goal, *(f32 *)(vars + 0x1B0), *(f32 *)(vars + 0x1B4), *(f32 *)(vars + 0x1B8));
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        ring_center = arena_get_center_point(*(u8 **)(self + 0xB8));
        if (*(f32 *)(self + 0x18) < *(f32 *)(ring_center + 8) + 5.0f || math_random_int_below(0x1C2) == 0 ||
            *(u16 *)(self + 0x96) >= 0x12D) {
            moby_set_anim_type_three_pal(self, 0, -1);
            drone_reset_to_idle_pal(self);
        }
        break;
    }
    }

    if (*(s16 *)(vars + 0x1FC) != 0 && self[0x95] != 4) {
        f32 saved_z = *(f32 *)(self + 0x18);
        FastVecSub(goal, (self + 0x10), center);
        goal[2] = 0.0f;
        vec_scale_to_length(goal, goal, 14.3f);
        FastVecAdd((self + 0x10), goal, center);
        *(f32 *)(self + 0x18) = saved_z;
    }
    if (self[0x20] != 0xE) {
        *(f32 *)(vars + 0x1B0) = math_move_angle_toward_target(*(f32 *)(vars + 0x1B0), g_drone_target_angle_a * 0.0003490659f, 0.0625f);
        *(f32 *)(vars + 0x1B4) = math_move_angle_toward_target(*(f32 *)(vars + 0x1B4), g_drone_target_angle_b * 0.0003490659f, 0.0625f);
        *(f32 *)(vars + 0x1B8) = math_move_angle_toward_target(*(f32 *)(vars + 0x1B8), g_drone_target_angle_c * 0.0003490659f, 0.0625f);
        *(f32 *)(self + 0xF0) = FastAddRotations(*(f32 *)(self + 0xF0), *(f32 *)(vars + 0x1B0));
        *(f32 *)(self + 0xF4) = FastAddRotations(*(f32 *)(self + 0xF4), *(f32 *)(vars + 0x1B4));
        *(f32 *)(self + 0xF8) = FastAddRotations(*(f32 *)(self + 0xF8), *(f32 *)(vars + 0x1B8));
    }
    if (center != 0 && *(s16 *)(vars + 0x1FC) == 0 && *(f32 *)(self + 0x18) <= *(f32 *)(center + 8) + 0.4f) {
        if (self[0x31] == 0) {
            *(f32 *)(vars + 0x108) = 0.020000001f;
            *(f32 *)(self + 0x18) = *(f32 *)(center + 8) + 0.3f;
        } else if (coll_test_point((self + 0x10), 6, 0, 0.3f) != 0) {
            f32 spark_size;
            s32 spark_dir;
            *(f32 *)(vars + 0x108) = 0.020000001f;
            *(f32 *)(self + 0x18) = *(f32 *)(center + 8) + 0.3f;
            goal[0] = *(f32 *)(self + 0x10) + math_random_float_range(-0.01f, 0.01f);
            goal[1] = *(f32 *)(self + 0x14) + math_random_float_range(-0.01f, 0.01f);
            goal[2] = *(f32 *)(self + 0x18) - 0.3f;
            spark_size = math_random_float_range(0.3f, 0.8f);
            spark_dir = math_random_int_below(2);
            if (spark_dir == 0)
                spark_dir--;
            vec_random_direction(step, 0.001f, 0.060000002f);
            step[2] = math_random_float_range(1.0f, 5.0f) * 0.020000001f;
            part_spawn_ground_effect(goal, spark_size * 0.1f, spark_size, 0x32, 0x7F007F7F, 0, spark_dir, step, 0.0028800003f, 0);
        }
    }
    coll_sweep_from_object(self, (self + 0x10), 0x4000000, 0.8f, 5.0f, 1.0f, 0, 1, 0);
    drone_update_timer(self);
}
