#include "names.h"
/* func_L11_00453358: the Joba drone's state machine (patrol path, chase, grab, release, fall).
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
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern f32 D_L11_001B1D40 __attribute__((sda));
extern f32 D_L11_001B1D44;
extern f32 D_L11_001B1D48;
extern u8 *D_L11_001FF580[];

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
extern void anim_start_blended(void *, int, int, int);
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
extern int moby_turn_toward_target_and_step(void *, void *, float);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern char *part_spawn_ground_effect(void *, float, float, int, unsigned int, int, int, void *, float, int);
extern int moby_l01_turn_toward_target(void *, void *);
extern int moby_aim_at_target_offset(void *, void *);
extern int hero_set_control_motion_and_step(void *, void *);
extern u8 *arena_get_center_point(u8 *);
extern int arena_is_point_in_polygon(u8 *, void *);
extern void func_L11_00441A38(u8 *, int, int);
extern void drone_launcher_update_state(u8 *);
extern void drone_update_timer(u8 *);
extern void drone_reset_to_idle(u8 *);

/* Start animation a (blend b) unless it is already playing. */
static __inline__ void anim(u8 *self, int a, int b)
{
    if (self[0x43] != a)
        anim_start_blended(self, a, 0, b);
}

/* Movement tuning with the shared turn limits. */
static __inline__ void turn(u8 *self, float rate, float speed)
{
    moby_set_controller_speed_limits(self, rate, speed, 0.001163553f, 0.10471977f);
}

/* Per-frame update of the Joba drone (moby class 3575): it patrols its path, chases, grabs and releases the player, and falls when hit. */
void drone_update(u8 *self)
{
    f32 v00[4];
    f32 v10[4];
    f32 v20[4];
    f32 v30[4];
    f32 m[4][4];
    u8 *pv;
    u8 *target;
    f32 dist;
    f32 height;

    pv = *(u8 **)(self + 0x68);
    if (self[0x20] == 1)
        return;
    if (*(s16 *)(pv + 0x1FC) != 0 && D_L11_001A8FF4 == 0 && self[0x20] != 0xE && self[0x20] != 0xD)
        return;
    drone_launcher_update_state(self);
    if (*(u8 **)(pv + 0x1C4) != 0) {
        *(TI128 *)v00 = *(TI128 *)(*(u8 **)(pv + 0x1C4) + 0x10);
        mat_fast_helper_a(*(f32 *)(*(u8 **)(pv + 0x1C4) + 0x10) - *(f32 *)(self + 0x10),
                      *(f32 *)(*(u8 **)(pv + 0x1C4) + 0x14) - *(f32 *)(self + 0x14));
    } else {
        *(Vec *)v00 = *(Vec *)(g_hero_state + 0x80);
        mat_fast_helper_a(((Hero *)g_hero_state)->f[0x80 / 4] - *(f32 *)(self + 0x10),
                      ((Hero *)g_hero_state)->f[0x84 / 4] - *(f32 *)(self + 0x14));
    }
    dist = fast_vec_dist((self + 0x10), v00);
    if (self[0x20] == 1)
        return;
    if (*(s16 *)(pv + 0x1FC) != 0 && D_L11_001A8FF4 == 0)
        return;
    target = 0;
    if (*(s32 *)(self + 0xB8) != 0)
        target = arena_get_center_point(*(u8 **)(self + 0xB8));

    switch (self[0x20]) {
    case 3: {
        if (flag_set_first_pending(self) != 0) {
            turn(self, 0.027777778f, 1.6666667f);
            self[0xBC] = 0;
            *(u16 *)(self + 0x96) = 0;
        }
        if (self[0xBC] == 0 && *(u16 *)(self + 0x96) > *(s16 *)(pv + 0x1EE)) {
            self[0xBC] = 1;
            break;
        }
        if (self[0xBC] == 1) {
            if (arena_is_point_in_polygon(*(u8 **)(self + 0xB8), (self + 0x10)) != 0)
                moby_set_state(self, 7, 3);
            moby_l01_turn_toward_target(self, arena_get_center_point(*(u8 **)(self + 0xB8)));
        }
        break;
    }
    case 4:
        if (flag_set_first_pending(self) != 0)
            *(u16 *)(self + 0x96) = 0;
        if (*(u16 *)(self + 0x96) < 0x1A)
            break;
        anim(self, 0, 5);
        moby_set_state(self, 8, 3);
        break;
    case 7: {
        u8 *path;
        u8 *p;
        s32 i;
        s32 best;
        f32 d;
        f32 lim;

        if (*(s16 *)(pv + 0x1FC) != 0)
            path = D_L11_001FF580[*(s32 *)(pv + 0x1E0)];
        else
            path = D_L11_001FF580[*(s32 *)(pv + 0x1C0)];
        if (flag_set_first_pending(self) != 0) {
            p = path + 0x10;
            best = 0;
            turn(self, 0.027777778f, 3.3333335f);
            *(f32 *)(pv + 0x1C8) = math_random_float_range(1.0f, 3.0f);
            d = fast_vec_dist((self + 0x10), p);
            for (i = 0; i < *(s32 *)path - 1; i++, p += 0x10) {
                f32 e = fast_vec_dist((self + 0x10), p);
                if (e < d) {
                    d = e;
                    best = i;
                }
            }
            *(s32 *)(pv + 0x1D4) = best;
            *(s16 *)(pv + 0x1E8) = math_random_int_below(2);
        } else {
            qcopy(v10, path + 0x10 + (*(s32 *)(pv + 0x1D4) << 4));
            if (*(s16 *)(pv + 0x1FC) != 0) {
                FastVecSub(v30, v10, target);
                v30[2] = 0.0f;
                vec_scale_to_length(v30, v30, 15.0f - *(f32 *)(pv + 0x1C8));
                v10[0] = *(f32 *)(target + 0) + v30[0];
                v10[1] = *(f32 *)(target + 4) + v30[1];
            } else {
                v10[2] = *(f32 *)(pv + 0x1C8) + *(f32 *)(target + 8);
            }
            FastVecSub(v20, v10, (self + 0x10));
            lim = 2.0f;
            vec_scale_to_length(v20, v20, *(f32 *)(pv + 0x1D8));
            FastVecAdd((self + 0x10), (self + 0x10), v20);
            if (*(s16 *)(pv + 0x1FC) != 0)
                lim = 4.0f;
            if (*(s16 *)(pv + 0x1E8) != 0) {
                if (fast_vec_dist((self + 0x10), v10) < lim)
                    *(s32 *)(pv + 0x1D4) -= 1;
                if (*(s32 *)(pv + 0x1D4) < 0)
                    *(s32 *)(pv + 0x1D4) = *(s32 *)path - 1;
            } else {
                if (fast_vec_dist((self + 0x10), v10) < lim)
                    *(s32 *)(pv + 0x1D4) += 1;
                if (*(s32 *)(pv + 0x1D4) >= *(s32 *)path)
                    *(s32 *)(pv + 0x1D4) = 0;
            }
            if (*(s32 *)(pv + 0x1D4) >= *(s32 *)path - 6 && *(f32 *)(pv + 0x1D8) >= 0.10000001f)
                *(f32 *)(pv + 0x1D8) = *(f32 *)(pv + 0x1D8) - 0.0025f;
            func_002A677C(self);
            if (*(s16 *)(pv + 0x1FC) != 0) {
                moby_aim_at_target_offset(self, v10);
            } else {
                moby_turn_toward_target_and_step(self, v10, *(f32 *)(pv + 0x1D0));
                math_step_value_toward_target(self + 0x18, pv + 0x108, *(f32 *)(pv + 0x1C8), 0.00055555557f, 0.00055555557f,
                              0.16666667f);
            }
        }
        if (*(s16 *)(pv + 0x1EC) != 0)
            moby_set_state(self, 8, 3);
        break;
    }
    case 8: {
        s32 flag;
        if (flag_set_first_pending(self) != 0)
            turn(self, 0.011111111f, 1.3333334f);
        flag = 0;
        if (*(s16 *)(pv + 0x1FC) != 0) {
            if (4.0f < dist) {
                FastVecSub(v10, v00, (self + 0x10));
                vec_scale_to_length(v10, v10, 10.0f);
                FastVecAdd(v10, v10, (self + 0x10));
                moby_aim_at_target_offset(self, v10);
            } else {
                moby_aim_at_target_offset(self, v00);
            }
            flag = dist < 4.0f;
        } else {
            height = *(f32 *)(target + 8) + 0.5f;
            math_step_value_toward_target(self + 0x18, pv + 0x108, height, 0.0055555557f, 0.027777778f, 0.16666667f);
            moby_turn_toward_target_and_step(self, v00, *(f32 *)(pv + 0x1D0));
            if (math_fabs(*(f32 *)(self + 0x18) - height) < 0.1f &&
                vec_distance_xy((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16]) < 2.0f)
                flag = 1;
        }
        if (flag) {
            *(u16 *)(self + 0x96) = 0;
            moby_set_state(self, 10, -1);
        }
        coll_sweep_from_object(self, (self + 0x10), 1, 0.3f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        break;
    }
    case 9:
        if (flag_set_first_pending(self) != 0)
            anim(self, 2, 3);
        if (self[0x60] & 2) {
            anim(self, 3, 5);
            moby_set_state(self, 11, -1);
        }
        height = 0.0f;
        break;
    case 11: {
        s32 k;
        f32 lim;
        if (flag_set_second_pending(self) != 0) {
            turn(self, 0.0022222223f, 0.06666667f);
            *(u16 *)(self + 0x96) = 0;
        }
        *(f32 *)(self + 0x48) = 1.75f;
        for (k = 0; k < 4; k++)
            coll_test_hit_at_bone(self, k, 1, 0.5f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        lim = 1.8f;
        if (lim <= fast_vec_dist((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16])) {
            qcopy(v10, v00);
        } else if (fast_vec_dist((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16]) < lim) {
            FastVecSub(v10, (self + 0x10), v00);
            vec_scale_to_length(v10, v10, 2.0f);
            FastVecAdd(v10, v10, (self + 0x10));
        } else {
            qcopy(v10, (self + 0x10));
        }
        if (*(s16 *)(pv + 0x1FC) != 0) {
            moby_aim_at_target_offset(self, v10);
        } else {
            math_step_value_toward_target(self + 0x18, pv + 0x108, *(f32 *)(target + 8) + 0.5f, 0.0055555557f, 0.027777778f,
                          0.16666667f);
            moby_l01_turn_toward_target(self, v10);
        }
        if (((Hero *)g_hero_state)->ptr[0x249C / 4] == self) {
            moby_set_state(self, 12, -1);
            anim(self, 4, 5);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        if (fast_vec_dist((self + 0x10), &((Hero *)g_hero_state)->q[0x80 / 16]) > 4.0f && *(u16 *)(self + 0x96) >= 0x79) {
            anim(self, 5, 15);
            moby_set_state(self, 4, -1);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        break;
    }
    case 12:
        if (!(self[0x60] & 2))
            break;
        anim(self, 0, 15);
        moby_set_state(self, 8, -1);
        break;
    case 10:
        if (*(u16 *)(self + 0x96) >= 0xF) {
            moby_set_state(self, 9, -1);
            anim(self, 2, 2);
            *(f32 *)(self + 0x48) = 1.0f;
        }
        qcopy(v10, (self + 0x10));
        if (dist < 1.0f)
            coll_sweep_from_object(self, v10, 1, 0.3f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        break;
    case 13:
        qcopy_nc(v10, (self + 0x10));
        *(f32 *)(pv + 0x108) = *(f32 *)(pv + 0x108) - *(f32 *)(pv + 0x8C);
        FastVecAdd((self + 0x10), (self + 0x10), pv + 0x100);
        if (CollLine(v10, (self + 0x10), 0, self, 0) == 0 && coll_test_point((self + 0x10), 4, self, 0.3f) == 0 &&
            math_random_int_below(0x1E) != 0)
            break;
        coll_sweep_from_object(self, (self + 0x10), 0x10000, 0.5f, (f32)pv[0x34], 1.0f, 0, 1, 0);
        if (*(f32 *)(pv + 0x20) > 0.0f) {
            moby_set_state(self, 8, 3);
            anim(self, 0, 5);
        } else if (*(s16 *)(pv + 0x1FC) != 0 && math_random_int_below(2) == 0) {
            moby_set_state(self, 14, -1);
        } else {
            func_L11_00441A38(self, 0, 1);
            drone_reset_to_idle(self);
        }
        break;
    case 14: {
        s32 j;
        u8 *t;
        f32 *rot;
        if (flag_set_first_pending(self) != 0) {
            t = arena_get_center_point(*(u8 **)(self + 0xB8));
            FastVecSub(pv + 0x100, t, (self + 0x10));
            *(f32 *)(pv + 0x108) = 0.0f;
            vec_scale_to_length(pv + 0x100, pv + 0x100, math_random_float_range(3.0f, 5.0f) * 0.016666668f);
            *(s16 *)(pv + 0x1FC) = 0;
            for (j = 0; j < 3; j++) {
                rot = (f32 *)(pv + 0x1B0);
                rot[j] = math_random_float_range(240.0f, 720.0f) * 0.00029088825f;
                qcopy(m[j], self + 0xC0 + j * 0x10);
            }
            mat_get_euler_angles(m, self + 0xF0);
            *(u16 *)(self + 0x34) &= 0xEFFF;
        }
        *(f32 *)(pv + 0x108) = *(f32 *)(pv + 0x108) - *(f32 *)(pv + 0x8C);
        hero_set_control_motion_and_step(self, pv + 0x100);
        FastVecScale(pv + 0x1B0, pv + 0x1B0, 0.98f);
        *(TI128 *)v20 = 0;
        v20[2] = *(f32 *)(pv + 0x30);
        *(TI128 *)v10 = *(TI128 *)v20;
        moby_rotate_about_point(self, v10, *(f32 *)(pv + 0x1B0), *(f32 *)(pv + 0x1B4), *(f32 *)(pv + 0x1B8));
        euler_rotation_basis(self + 0xC0, self + 0xF0);
        t = arena_get_center_point(*(u8 **)(self + 0xB8));
        if (*(f32 *)(self + 0x18) < *(f32 *)(t + 8) + 5.0f || math_random_int_below(0x1C2) == 0 ||
            *(u16 *)(self + 0x96) >= 0x12D) {
            func_L11_00441A38(self, 0, -1);
            drone_reset_to_idle(self);
        }
        break;
    }
    }

    if (*(s16 *)(pv + 0x1FC) != 0 && self[0x95] != 4) {
        f32 z = *(f32 *)(self + 0x18);
        FastVecSub(v10, (self + 0x10), target);
        v10[2] = 0.0f;
        vec_scale_to_length(v10, v10, 14.3f);
        FastVecAdd((self + 0x10), v10, target);
        *(f32 *)(self + 0x18) = z;
    }
    if (self[0x20] != 0xE) {
        *(f32 *)(pv + 0x1B0) = math_move_angle_toward_target(*(f32 *)(pv + 0x1B0), D_L11_001B1D40 * 0.00029088825f, 0.0625f);
        *(f32 *)(pv + 0x1B4) = math_move_angle_toward_target(*(f32 *)(pv + 0x1B4), D_L11_001B1D44 * 0.00029088825f, 0.0625f);
        *(f32 *)(pv + 0x1B8) = math_move_angle_toward_target(*(f32 *)(pv + 0x1B8), D_L11_001B1D48 * 0.00029088825f, 0.0625f);
        *(f32 *)(self + 0xF0) = FastAddRotations(*(f32 *)(self + 0xF0), *(f32 *)(pv + 0x1B0));
        *(f32 *)(self + 0xF4) = FastAddRotations(*(f32 *)(self + 0xF4), *(f32 *)(pv + 0x1B4));
        *(f32 *)(self + 0xF8) = FastAddRotations(*(f32 *)(self + 0xF8), *(f32 *)(pv + 0x1B8));
    }
    if (target != 0 && *(s16 *)(pv + 0x1FC) == 0 && *(f32 *)(self + 0x18) <= *(f32 *)(target + 8) + 0.4f) {
        if (self[0x31] == 0) {
            *(f32 *)(pv + 0x108) = 0.016666668f;
            *(f32 *)(self + 0x18) = *(f32 *)(target + 8) + 0.3f;
        } else if (coll_test_point((self + 0x10), 6, 0, 0.3f) != 0) {
            f32 s;
            s32 n;
            *(f32 *)(pv + 0x108) = 0.016666668f;
            *(f32 *)(self + 0x18) = *(f32 *)(target + 8) + 0.3f;
            v10[0] = *(f32 *)(self + 0x10) + math_random_float_range(-0.01f, 0.01f);
            v10[1] = *(f32 *)(self + 0x14) + math_random_float_range(-0.01f, 0.01f);
            v10[2] = *(f32 *)(self + 0x18) - 0.3f;
            s = math_random_float_range(0.3f, 0.8f);
            n = math_random_int_below(2);
            if (n == 0)
                n--;
            vec_random_direction(v20, 0.0008333334f, 0.050000004f);
            v20[2] = math_random_float_range(1.0f, 5.0f) * 0.016666668f;
            part_spawn_ground_effect(v10, s * 0.1f, s, 0x3C, 0x7F007F7F, 0, n, v20, 0.002f, 0);
        }
    }
    coll_sweep_from_object(self, (self + 0x10), 0x4000000, 0.8f, 5.0f, 1.0f, 0, 1, 0);
    drone_update_timer(self);
}
