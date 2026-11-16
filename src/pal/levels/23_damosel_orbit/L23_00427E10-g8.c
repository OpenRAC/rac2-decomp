#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
typedef struct View_00422A30 {
    u8 pad0[0x188C];
    u8 *f188C;
    u8 pad1[0x2290 - 0x1890];
    u8 *f2290;
    s32 f2294;
} View_00422A30;
extern View_00422A30 g_hero_state;
extern float g_shot_l23_speed_scale __attribute__((sda));
extern float g_shot_min_aim_dot __attribute__((sda));
extern u8 *g_mothership_boss_moby __attribute__((sda));
extern s32 g_boss_effect_position;
extern TI16 g_hero_back_dir MACRO_ADDR;
extern u8 *CreateMoby(s32);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern void mothership_project_point_onto_surface(void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float gravity_get_center_distance(void *);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);
extern s32 mothership_is_held(void);
extern s32 PlayMobySound(s32, s32, u8 *);

/* Creates the follower object for `src` (the effect that tracks `target`, or the hero, or nothing): copies
   the pose rows, fills the state, and when it has a live target works out the direction, the distance and
   the aim test, dropping the target when the aim, the range or the helper says so. */
u8 *SpawnTrackingEffect_pal(u8 *src, TI16 *pos, u8 *target, s32 track_flag, s32 chase_flag) {
    u8 *follower;
    u8 *vars;
    TI16 path_pts[4];
    float target_height;
    float src_height;
    float target_dist;
    float dot;
    s32 too_far_up;
    u8 *hero;
    TI16 row0;
    TI16 row1;
    TI16 row2;
    TI16 *back_row;

    follower = CreateMoby(0x118F);
    if (follower != 0) {
        vars = *(u8 **)(follower + 0x68);
        moby_init_child_from_parent(follower, src);
        *(float *)(follower + 0x2C) = *(float *)(follower + 0x2C) * g_shot_l23_speed_scale;
        *(u16 *)(follower + 0x34) = *(u16 *)(follower + 0x34) | 0x100;
        *(float *)(vars + 0x1C) = 0.40000004f;
        row0 = *(TI16 *)(src + 0xC0);
        *(TI16 *)(follower + 0xC0) = row0;
        row1 = *(TI16 *)(src + 0xD0);
        *(TI16 *)(follower + 0xD0) = row1;
        row2 = *(TI16 *)(src + 0xE0);
        *(TI16 *)(follower + 0xE0) = row2;
        *(u8 **)(vars + 0x10) = src;
        qcopy(follower + 0x10, pos);
        *(s32 *)(vars + 0x14) = 0x7D;
        *(float *)(follower + 0x2C) = *(float *)(follower + 0x2C) + *(float *)(follower + 0x2C);
        vars[0x28] = track_flag;
        vars[0x29] = chase_flag;
        hero = g_mothership_boss_moby;
        if (target != 0) {
            *(u8 **)(vars + 0x18) = target;
            *(s32 *)(vars + 0x24) = 0x890000;
        } else {
            if (hero != 0) {
                *(u8 **)(vars + 0x18) = hero;
                if (*(s16 *)(hero + 0xAA) == 0xF7F) {
                    *(s32 **)(vars + 0x2C) = &g_boss_effect_position;
                } else {
                    *(u8 **)(vars + 0x2C) = hero + 0x10;
                }
                *(s32 *)(vars + 0x24) = 0x890000;
            } else {
                *(s32 *)(vars + 0x18) = 0;
                *(s32 *)(vars + 0x24) = 0x890000;
                vars[0x29] = 0;
                vars[0x28] = 0;
            }
        }
        if (src == g_hero_state.f2290) {
            vars[0x29] = 1;
        }
        if (vars[0x28] == 0 && *(s32 *)(vars + 0x18) != 0) {
            qcopy(&path_pts[0], *(void **)(vars + 0x2C));
            mothership_project_point_onto_surface(&path_pts[0], 0.0f);
            FastVecSub(vars + 0x30, *(u8 **)(vars + 0x2C), follower + 0x10);
            qcopy(&path_pts[1], follower + 0x10);
            mothership_project_point_onto_surface(&path_pts[1], 0.0f);
            FastVecSub(&path_pts[2], &path_pts[0], &path_pts[1]);
            too_far_up = 0;
            vec_scale_to_length(&path_pts[2], &path_pts[2], 1.0f);
            vec_scale_to_length(vars + 0x30, vars + 0x30, 1.0f);
            src_height = gravity_get_center_distance(src + 0x10);
            target_height = gravity_get_center_distance(*(u8 **)(vars + 0x2C));
            target_dist = fast_vec_dist(&path_pts[0], &path_pts[1]);
            if (target_dist < 5.0f) {
                if (math_fabs(src_height - target_height) > 10.0f) {
                    too_far_up = 1;
                }
            }
            qcopy(&path_pts[3], follower + 0xC0);
            dot = FastVecDot(&path_pts[2], &path_pts[3]);
            if ((src == g_hero_state.f2290 && *(*(u8 **)(vars + 0x18) + 0x31) == 0) ||
                dot < g_shot_min_aim_dot || 50.0f < target_dist || too_far_up != 0 || mothership_is_held() != 0) {
                *(s32 *)(vars + 0x18) = 0;
            }
            if (src == g_hero_state.f2290) {
                if (*(s32 *)(vars + 0x18) != 0) {
                    g_hero_state.f188C = vars + 0x30;
                } else if (g_hero_state.f2294 == 0x5B) {
                    back_row = (TI16 *)(src + 0xE0);
                    qcopy(&g_hero_back_dir, back_row);
                    FastVecScale(&g_hero_back_dir, &g_hero_back_dir, -1.0f);
                    g_hero_state.f188C = (u8 *)&g_hero_back_dir;
                    qcopy(vars + 0x30, &g_hero_back_dir);
                    vars[0x28] = 0;
                    *(s32 *)(vars + 0x18) = 1;
                    vars[0x29] = 0;
                }
            }
        }
        *(s32 *)(vars + 0x20) = 0;
        PlayMobySound(1, 0, follower);
        *(u16 *)(follower + 0x34) = *(u16 *)(follower + 0x34) | 0x41;
        follower[0xBC] = 0;
    }
    return follower;
}

extern int PlayMobySound(int, int, u8 *);
extern void moby_mark_spawned(u8 *object);
extern float g_homing_shot_param_a __attribute__((sda));
extern float g_homing_shot_param_b __attribute__((sda));
extern float g_homing_shot_param_c __attribute__((sda));
extern float g_homing_shot_param_d __attribute__((sda));
extern float g_homing_l23_shot_quat_scale __attribute__((sda));
extern float g_homing_shot_vec_scale __attribute__((sda));
extern float g_mothership_state_param_a[] __attribute__((sda));
extern u8 g_zero_l23_vec[] __attribute__((sda));
typedef struct {
    u8 pad[0x18];
    u8 *f18;
    s32 f1C;
    TI16 f20;
} L23Hit1C0A80;
extern L23Hit1C0A80 g_last_ray_hit;
typedef struct {
    float v[4] __attribute__((aligned(16)));
    u8 *obj;
    s32 flags;
    u8 b18;
    u8 b19;
    u16 h1A;
    float f1C;
    s32 f20;
} L23Rec;
extern void cam_compute_view_direction(void *, void *, s32);
extern float ApproachValue(float *, float, float);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern float square_root(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern void vec_random_direction(void *, float, float);
extern s32 CollLine(void *, void *, s32, s32, void *);
extern s32 math_fast_float_d(void *);
extern void SpawnExplosionEffects_pal(u8 *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                          float, float, float, float, float, float, float);
extern int coll_process_hit(void *, s32, s32, void *, float);
extern void vec_turn_toward_target(void *, void *, void *, void *, void *, void *, float, float, float, float);
extern void *part_spawn_gravity_fade(void *, void *, s32, s32, s32, s32, s32, float, float, float, s32);

void homing_l23_shot_update_pal(u8 *shot) {
    float up[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float basis[12] __attribute__((aligned(16)));
    float quat[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float vec_a[4] __attribute__((aligned(16)));
    float vec_b[4] __attribute__((aligned(16)));
    float vec_c[4] __attribute__((aligned(16)));
    L23Rec rec;
    u8 *vars;
    u8 *ray_hit;
    u8 *hit_target;
    float quat_len;
    float rand_scale;
    s32 rand_color;
    s32 hit_special;
    u16 hit_class;

    *(u16 *)(shot + 0x34) &= 0xFFBE;
    vars = *(u8 **)(shot + 0x68);
    cam_compute_view_direction(shot + 0x10, up, 0);
    ApproachValue((float *)(vars + 0x1C), 2.8000002f, 0.080000006f);
    vec_scale_to_length(vel, shot + 0xC0, *(float *)(vars + 0x1C));
    vec_scale_to_length(axis, up, 1.0f);
    FastVecCross(quat, shot + 0xE0, axis);
    FastVecScale(quat, quat, g_homing_l23_shot_quat_scale * 0.5f);
    quat_len = FastVecLength(quat);
    quat[3] = -square_root(1.0f - quat_len * quat_len);
    quaternion_to_rotation_basis(quat, basis);
    multiply_matrix3x3(shot + 0xC0, basis, shot + 0xC0);
    if (*(u8 **)(vars + 0x18) != 0) {
        if (vars[0x28] != 0) {
            FastVecScale(vec_c, *(u8 **)(vars + 0x18) + 0xE0, g_homing_shot_vec_scale);
            FastVecAdd(vec_b, *(u8 **)(vars + 0x18) + 0x10, vec_c);
            vec_turn_toward_target(shot + 0x10, shot + 0xC0, vec_b, vars + 0x20, up, vec_a,
                              g_homing_shot_param_a, g_homing_shot_param_b, 0.0f, g_homing_shot_param_d);
            vec_scale_to_length(shot + 0xC0, shot + 0xC0, 1.0f);
            FastVecScale(vel, shot + 0xC0, *(float *)(vars + 0x1C));
        } else if (vars[0x29] != 0) {
            if (*(s32 *)(vars + 0x14) < 0x79) {
                FastVecSub(vec_a, shot + 0x10, *(u8 **)(vars + 0x2C));
                if (FastVecDot(vec_a, vel) < 0.0f) {
                    vec_turn_toward_target(shot + 0x10, shot + 0xC0, *(u8 **)(vars + 0x2C), vars + 0x20, up, vec_b,
                                      g_homing_shot_param_a, g_homing_shot_param_b, 0.0f, g_homing_shot_param_c);
                    vec_scale_to_length(shot + 0xC0, shot + 0xC0, 1.0f);
                    FastVecScale(vel, shot + 0xC0, *(float *)(vars + 0x1C));
                }
            }
        } else {
            FastVecScale(vel, vars + 0x30, *(float *)(vars + 0x1C));
            vec_scale_to_length(vec_a, vel, 1.0f);
            qcopy(shot + 0xC0, vec_a);
        }
    }
    qcopy(vec_b, shot + 0x10);
    FastVecScale(vec_c, vel, 0.7f);
    rand_scale = math_random_float_range(0.1f, 0.3f);
    rand_color = math_random_int_below(0xFF);
    vec_random_direction(vec_a, 0.0f, 0.1f);
    FastVecAdd(vec_a, vec_a, vec_b);
    part_spawn_gravity_fade(vec_a, g_zero_l23_vec, 0xC, 0x808080, rand_color, 0x20, 0, rand_scale * 210000.0f, rand_scale * 42000.0f, 0.0f, 0);
    FastVecAdd(vec_b, vec_b, vec_c);
    qcopy(vec_a, shot + 0x10);
    FastVecAdd(shot + 0x10, shot + 0x10, vel);
    if (*(float *)(shot + 0x10) < 0.0f || *(float *)(shot + 0x14) < 0.0f || *(float *)(shot + 0x18) < 0.0f) {
        moby_mark_spawned(shot);
        return;
    }
    rec.obj = shot;
    rec.flags = 0x8B0003;
    rec.f1C = g_mothership_state_param_a[0];
    rec.f20 = 0;
    rec.b18 = 3;
    rec.b19 = 3;
    rec.h1A = *(u16 *)(shot + 0xAA);
    if (shot[0xBC] == 0 && CollLine(vec_a, shot + 0x10, 0x10, *(s32 *)(vars + 0x10), &rec) != 0) {
        ray_hit = g_last_ray_hit.f18;
        if (ray_hit != 0) {
            if (ray_hit != *(u8 **)(shot + 0xB8)) {
                shot[0xBC] = 2;
                qcopy(shot + 0x10, &g_last_ray_hit.f20);
            }
        } else if (g_last_ray_hit.f1C > 0) {
            shot[0xBC] = 1;
            qcopy(shot + 0x10, &g_last_ray_hit.f20);
        }
        hit_special = 0;
        hit_target = g_last_ray_hit.f18;
        if (hit_target != 0) {
            hit_class = *(u16 *)(hit_target + 0xAA);
            if (hit_class == 0xF7E || hit_class == 0xF7F || (s16)hit_class == 0x120F) {
                PlayMobySound(2, 0, shot);
                hit_special = 1;
            }
        }
        if (hit_special == 0) {
            PlayMobySound(0, 0, shot);
        }
    } else if (math_fast_float_d(vars + 0x14) != 0) {
        moby_mark_spawned(shot);
        return;
    }
    if (shot[0xBC] != 0) {
        SpawnExplosionEffects_pal(shot, g_zero_l23_vec, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
                      0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        coll_process_hit(shot + 0x10, 0, *(s32 *)(vars + 0x10), &rec, 2.0f);
        moby_mark_spawned(shot);
    }
}
