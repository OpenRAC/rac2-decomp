#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* the level-class table entry, 0xE0 bytes */
typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 pad5[0x4B];
    f32 f50;
    u8 pad54[0x1C];
    f32 f70;
    u8 pad74[0x6C];
} LevelClass;

/* the collision query's result */
typedef struct {
    u8 pad0[0x18];
    char *moby;
    s32 count;
    f32 pos[4];
    u8 pad30[0x10];
    f32 normal[4];
} CollResult;

/* the query passed to func_002761F8 */
typedef struct {
    f32 v[4];
    char *moby;
    s32 mask;
    s8 b18;
    s8 b19;
    u16 h1A;
    f32 f1C;
    s32 i20;
} CollQuery;

extern char g_hero_state[];
extern u8 g_item_slot_to_record[];
extern u8 g_sound_state[];
extern LevelClass g_weapon_l00_table[];
extern void *g_hero_moby __attribute__((nosda));
extern CollResult g_collision_result __attribute__((aligned(16)));
extern char g_camera_l00_position[];
extern f32 D_L00_001B1470 __attribute__((sda));

extern int level_get_slot_body(int id, int index);
extern int *level_get_slot_header(int id, int index);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern int FastDecTimer(void *);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_move_angle_toward_target(float, float, float);
extern float *moby_get_private_value_0(char *);
extern char *SelectBestTargetInCone(void *, void *, int *, float, float, int, int, int,
                           float, float, float, int, int);
extern int CollLine(void *, void *, int, void *, void *);
extern void part_l00_spawn_hit_sparks(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void StartAttachedEffect(char *, int, int);
extern char *guided_rocket_create(int, void *, int, int, int, int);
extern float missile_steer_toward_target(char *, void *, void *);
extern void part_steer_effect_direction(int, void *, int);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
extern void level_release_slot_list(void *);
extern void moby_update_transform_history_followers(void *, int);
extern void snd_stop_voice(int);
extern int snd_is_voice_playing_for_owner(void *, int);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern void ref_L00_0041CB80_00(void *, void *);
extern void rocket_draw_trail(void *);
extern int FastTweenColor(int, int, float);
extern void copy_matrix_rotation(void *, void *);
extern void mat_get_euler_angles(void *, void *);

/* Flies the guided rocket (class 2170) each frame: steers toward its target, bounces off or explodes on hits, updates its trail, and removes it when it ends. */
void guided_rocket_update(char *rocket)
{
    f32 old[4] __attribute__((aligned(16)));
    f32 fwd[4] __attribute__((aligned(16)));
    f32 rel[4] __attribute__((aligned(16)));
    f32 npos[4] __attribute__((aligned(16)));
    f32 vecA[4] __attribute__((aligned(16)));
    f32 vecB[4] __attribute__((aligned(16)));
    CollQuery q __attribute__((aligned(16)));
    f32 c90[4] __attribute__((aligned(16)));
    f32 cA0[4] __attribute__((aligned(16)));
    f32 mat[16] __attribute__((aligned(16)));
    int found;
    char *vars;
    char *base;
    int *offs;
    char *segs;
    char *slots;
    char *flags;
    char *target;
    char *splitRocket;
    char *splitVars;
    float *info;
    float *targetHealth;
    float *targetInfo;
    float range;
    LevelClass *cls;
    int lim;
    u64 stateBits;
    u64 stateBits2;
    float dist;
    float ang;
    float roll;
    float spd;
    float sc;
    float glow;
    float rnd;
    int ok;
    int bad;
    int b8;
    int j1, j2, j3, j5, j6, n;
    char *se1, *se2, *e1, *e2, *p1, *p2, *hp;
    int c0;
    int c1;
    int fl;
    void *cq;

    vars = *(char **)(rocket + 0x68);
    base = (char *)level_get_slot_body(*(int *)(vars + 0x50), *(int *)(vars + 0x3C));
    if (base == 0) {
        table_clear_entry_flag(*(int *)(vars + 0x6C));
        moby_mark_spawned(rocket);
        return;
    }
    offs = level_get_slot_header(*(int *)(vars + 0x50), *(int *)(vars + 0x3C));
    slots = base + offs[0];
    flags = base + offs[1];
    segs = base + offs[2];
    qcopy(old, rocket + 0x10);
    cam_compute_view_direction(rocket + 0x10, fwd, 1);
    vec_transform_or_copy(rocket + 0x10, rocket + 0x10);
    vec_transform_or_copy(vars + 0x40, vars + 0x40);
    FastVecSub(rel, vars + 0x40, &((Hero *)g_hero_state)->b[0x80]);
    math_apply_axis_rotation_to_quat(rel, rel, &((Hero *)g_hero_state)->b[0x2C0], -((Hero *)g_hero_state)->f[0x15C / 4]);
    FastVecAdd(vars + 0x40, rel, &((Hero *)g_hero_state)->b[0x80]);
    qcopy(npos, rocket + 0x10);
    switch (*(u8 *)(rocket + 0x20)) {
    case 0:
        if (FastDecTimer(vars + 0x10) != 0) {
            *(u8 *)(rocket + 0x20) = 1;
        }
        FastDecTimer(vars + 0x18);
        if (*(s16 *)(vars + 0x34) != 0) {
            *(s16 *)(vars + 0x34) = 0;
            info = ((Hero *)g_hero_state)->ptr[0x1450 / 4];
            if (info != 0 && *(u8 *)((char *)info + 0x20) != 0xFE && *(u8 *)((char *)info + 0x20) != 0xFD) {
                *(float **)(vars + 0x14) = info;
            } else {
                *(char **)(vars + 0x14) = SelectBestTargetInCone(rocket + 0x10, vars, &found, 3.14159298f, 3.14159298f, 0, 0, 0,
                                                     12.0f, 3.14159298f, 3.14159298f, 1, 0);
            }
            if (*(char **)(vars + 0x14) != 0) {
                *(s16 *)(vars + 0x1A) = 0;
                *(s16 *)(vars + 0x12) = 10;
                *(s16 *)(vars + 0x18) = 0;
            }
        }
        dist = 0.0f;
        bad = 0;
        target = *(char **)(vars + 0x14);
        if (target == 0 || *(u8 *)(target + 0x20) == 0xFE || *(u8 *)(target + 0x20) == 0xFD
            || *(s16 *)(target + 0x32) == 0 || !(*(u16 *)(target + 0x34) & 0x1000)
            || ((targetHealth = moby_get_private_value_0(target)) != 0 && *targetHealth <= dist)) {
            bad = 1;
        }
        if (*(char **)(vars + 0x14) != 0 && bad == 0) {
            if (*(s16 *)(vars + 0x18) == 0) {
                targetInfo = moby_get_private_value_0(*(char **)(vars + 0x14));
                if (targetInfo != 0) {
                    FastVecScale(vecB, fwd, targetInfo[4]);
                    FastVecAdd(vecA, *(char **)(vars + 0x14) + 0x10, vecB);
                } else {
                    qcopy(vecA, *(char **)(vars + 0x14) + 0x10);
                }
                dist = missile_steer_toward_target(rocket, vecA, fwd);
            }
        } else {
            *(char **)(vars + 0x14) = 0;
            if (*(s16 *)(vars + 0x36) != 0) {
                dist = missile_steer_toward_target(rocket, vars + 0x40, fwd);
                FastVecAdd(vecA, rocket + 0x10, vars);
                FastVecSub(vecB, vars + 0x40, vecA);
                if (FastVecDot(vecB, vars) < 0.0f) {
                    *(s16 *)(vars + 0x36) = 0;
                }
            }
        }
        part_steer_effect_direction(*(int *)(vars + 0x6C), vars, 0);
        q.mask = 0x10000;
        q.moby = rocket;
        q.i20 = 1;
        q.f1C = (&g_weapon_l00_table[g_item_slot_to_record[0x16]])->f70;
        qcopy(q.v, vars);
        vec_scale_to_length(q.v, q.v, 1.0f);
        q.b18 = 1;
        q.v[3] = 5627.9248f;
        q.b19 = 1;
        q.h1A = *(u16 *)(rocket + 0xAA);
        FastVecAdd(rocket + 0x10, rocket + 0x10, vars);
        if (*(f32 *)(rocket + 0x10) < 2.0f || *(f32 *)(rocket + 0x10) > 1021.0f
            || *(f32 *)(rocket + 0x14) < 2.0f || *(f32 *)(rocket + 0x14) > 1021.0f
            || *(f32 *)(rocket + 0x18) < 2.0f || *(f32 *)(rocket + 0x18) > 1021.0f) {
            if (*(int *)(vars + 0x30) >= 0) {
                ((int *)flags)[*(int *)(vars + 0x30)] = 0;
                level_release_slot_list(slots + *(int *)(vars + 0x30) * 0x150);
                *(int *)(vars + 0x30) = -1;
            }
            if (*(int *)(vars + 0x38) != -1) {
                se1 = (char *)g_sound_state + *(int *)(vars + 0x38) * 0x70;
                if (*(char **)(se1 + 0x88) == rocket && *(u8 *)(se1 + 0x74) != 0) {
                    snd_stop_voice(*(int *)(vars + 0x38));
                }
            }
            *(int *)(vars + 0x38) = -1;
            table_clear_entry_flag(*(int *)(vars + 0x6C));
            moby_mark_spawned(rocket);
            return;
        }
        if (*(s16 *)(vars + 0x18) != 0) {
            fl = 2;
            cq = 0;
        } else {
            cq = &q;
            fl = 0;
        }
        if (CollLine(npos, rocket + 0x10, fl | 0x10, g_hero_moby, cq) != 0) {
            qcopy(rocket + 0x10, g_collision_result.pos);
            part_l00_spawn_hit_sparks(g_collision_result.pos, 10, *(char **)(vars + 0x68) == 0);
            *(s16 *)(vars + 0x36) = 0;
            ok = 0;
            if (g_collision_result.moby != 0) {
                ok = g_collision_result.count < 1;
            }
            if (ok != 0) {
                info = moby_get_private_value_0(g_collision_result.moby);
                if (info != 0) {
                    if (*(u8 *)((char *)info + 9) == 1) {
                        PlayMobySound(3, 0, rocket);
                    } else {
                        PlayMobySound(4, 0, rocket);
                    }
                } else {
                    PlayMobySound(2, 0, rocket);
                }
                if (g_collision_result.moby == *(char **)(vars + 0x14)) {
                    cls = &g_weapon_l00_table[g_item_slot_to_record[0x16]];
                    range = cls->f70;
                    if (info != 0 && info[0] <= range) {
                        *(char **)(vars + 0x14) = 0;
                        *(s16 *)(vars + 0x34) = 1;
                    }
                }
                *(s16 *)(vars + 0x2C) += 1;
                lim = g_weapon_l00_table[g_item_slot_to_record[0x16]].b4 ? 2 : 3;
                if (*(s16 *)(vars + 0x2C) >= lim) {
                    *(u8 *)(rocket + 0x20) = 1;
                }
                if (g_weapon_l00_table[g_item_slot_to_record[0x16]].b4 != 0) {
                    StartAttachedEffect(g_collision_result.moby, 0x41, *(int *)(rocket + 0xB8));
                } else {
                    StartAttachedEffect(g_collision_result.moby, 0x16, *(int *)(rocket + 0xB8));
                }
            } else {
                PlayMobySound(2, 0, rocket);
            }
            if (*(f32 *)(vars + 0x1C) == 1.0f && ok != 0) {
                FastVecCross(vecA, vars, rocket + 0xE0);
                math_apply_axis_rotation_to_quat(vars, vars, vecA, -math_random_float_range(0.17453295f, 0.610865295f));
                *(f32 *)(vars + 0x1C) = 2.0f;
            } else {
                if (ok != 0) {
                    qcopy(vecA, g_collision_result.moby + 0xE0);
                } else {
                    FastVecScale(vecA, g_collision_result.normal, 0.0009765625f);
                    vec_scale_to_length(vecA, vecA, 1.0f);
                }
                vec_fast_normalize(vars, vars, vecA);
                FastVecScale(vecB, vecA, 0.2f);
                FastVecAdd(rocket + 0x10, rocket + 0x10, vecB);
                if (*(char **)(vars + 0x14) == 0) {
                    *(s16 *)(vars + 0x34) = 1;
                }
                *(f32 *)(vars + 0x1C) = 2.0f;
            }
            if (ok != 0) {
                *(s16 *)(vars + 0x18) = 10;
                *(s16 *)(vars + 0x1A) = 1;
                *(s16 *)(vars + 0x12) = 0;
                if (g_weapon_l00_table[g_item_slot_to_record[0x16]].b4 != 0 && *(char **)(vars + 0x68) != 0) {
                    *(char **)(vars + 0x68) = 0;
                    cam_compute_view_direction(rocket + 0x10, vecA, 1);
                    ang = math_random_signed_float_range(0.785398245f, 1.3962636f);
                    math_build_axis_angle_quat(vecB, vecA, ang);
                    vec_rotate_by_quaternion(vars, vars, vecB);
                    splitRocket = guided_rocket_create(*(int *)(rocket + 0xB8), rocket + 0x10, 0, *(int *)(vars + 0x3C), 0, 0);
                    if (splitRocket != 0) {
                        splitVars = *(char **)(splitRocket + 0x68);
                        *(f32 *)(rocket + 0x2C) = *(f32 *)(rocket + 0x2C) * 0.5f;
                        *(f32 *)(splitRocket + 0x2C) = *(f32 *)(splitRocket + 0x2C) * 0.5f;
                        if (*(int *)(vars + 0x30) >= 0) {
                            e1 = slots + *(int *)(vars + 0x30) * 0x150;
                            for (j1 = 0; j1 < *(int *)(e1 + 0x148); j1++) {
                                p1 = ((char **)(e1 + 0x120))[j1];
                                if (p1 != 0) {
                                    *(f32 *)(p1 + 0x2C) = *(f32 *)(p1 + 0x2C) * 0.5f;
                                }
                            }
                        }
                        if (*(int *)(splitVars + 0x30) >= 0) {
                            e2 = slots + *(int *)(splitVars + 0x30) * 0x150;
                            for (j2 = 0; j2 < *(int *)(e2 + 0x148); j2++) {
                                p2 = ((char **)(e2 + 0x120))[j2];
                                if (p2 != 0) {
                                    *(f32 *)(p2 + 0x2C) = *(f32 *)(p2 + 0x2C) * 0.5f;
                                }
                            }
                        }
                        qcopy(splitRocket + 0x10, rocket + 0x10);
                        b8 = *(int *)(rocket + 0xB8);
                        for (j3 = 0; j3 < 3; j3++) {
                            qcopy(splitRocket + 0xC0 + j3 * 16, rocket + 0xC0 + j3 * 16);
                        }
                        qcopy(splitRocket + 0xF0, rocket + 0xF0);
                        qcopy(splitVars, vars);
                        *(int *)(splitRocket + 0xB8) = b8;
                        math_build_axis_angle_quat(vecB, vecA, -ang);
                        vec_rotate_by_quaternion(splitVars, splitVars, vecB);
                    }
                }
            }
        }
        stateBits = *(u32 *)(vars + 0x18);
        if (stateBits == 0x10000) {
            if (*(char **)(vars + 0x14) == 0) {
                *(s16 *)(vars + 0x1A) = 0;
            } else {
                FastVecSub(vecA, *(char **)(vars + 0x14) + 0x10, rocket + 0x10);
                if (FastVecDot(vars, vecA) >= 0.0f) {
                    *(s16 *)(vars + 0x1A) = 0;
                }
            }
        }
        if (*(char **)(vars + 0x14) != 0 && (stateBits2 = *(u32 *)(vars + 0x18)) == 0) {
            FastVecSub(vecA, *(char **)(vars + 0x14) + 0x10, rocket + 0x10);
            if (FastVecDot(vars, vecA) < 0.0f) {
                *(s16 *)(vars + 0x1A) = 1;
                *(s16 *)(vars + 0x18) = 10;
            }
        }
        vec_scale_to_length(rocket + 0xC0, vars, 1.0f);
        FastVecCross(rocket + 0xD0, rocket + 0xC0, fwd);
        vec_scale_to_length(rocket + 0xD0, rocket + 0xD0, 1.0f);
        FastVecCross(rocket + 0xE0, rocket + 0xD0, rocket + 0xC0);
        roll = -dist * 1.0471977f;
        if (roll == 0.0f) {
            roll = -0.069813177f;
            if (*(f32 *)(vars + 0x58) > 0.0f) {
                roll = 0.069813177f;
            }
        }
        *(f32 *)(vars + 0x58) = math_move_angle_toward_target(*(f32 *)(vars + 0x58), roll, 0.05f);
        if (math_fabs(*(f32 *)(vars + 0x58)) > 1e-05f) {
            math_build_axis_angle_quat(vecA, rocket + 0xC0, *(f32 *)(vars + 0x58));
            vec_rotate_by_quaternion(rocket + 0xD0, rocket + 0xD0, vecA);
            vec_rotate_by_quaternion(rocket + 0xE0, rocket + 0xE0, vecA);
        }
        *(f32 *)(vars + 0x28) = FastAddRotations(*(f32 *)(vars + 0x28), 0.418879062f);
        if (math_fabs(*(f32 *)(vars + 0x28)) > 1e-05f) {
            math_build_axis_angle_quat(vecA, rocket + 0xE0, *(f32 *)(vars + 0x28));
            vec_rotate_by_quaternion(rocket + 0xC0, rocket + 0xC0, vecA);
            vec_rotate_by_quaternion(rocket + 0xD0, rocket + 0xD0, vecA);
        }
        *(f32 *)(rocket + 0xCC) = *(f32 *)(rocket + 0xDC) = *(f32 *)(rocket + 0xEC) = 0.0f;
        spd = (&g_weapon_l00_table[g_item_slot_to_record[0x16]])->f50 * 0.016666668f;
        vec_scale_to_length(vars, vars, spd + (0.25f - spd) * dist);
        if (*(int *)(vars + 0x30) >= 0) {
            for (n = *(int *)(vars + 0x54) - 1; n > 0; n--) {
                hp = (char *)(n * 16 + ((int *)base)[*(int *)(vars + 0x30)]);
                qcopy(hp, hp - 16);
                vec_transform_or_copy(hp, hp);
            }
            qcopy(((char **)base)[*(int *)(vars + 0x30)], npos);
            if (*(int *)(vars + 0x54) < 40) {
                *(int *)(vars + 0x54) += 1;
            }
            if (math_fast_float_d(vars + 0x60) != 0) {
                sc = 0.5f;
                if (*(char **)(vars + 0x68) == 0) {
                    sc = 0.25f;
                }
                FastVecSub(vecA, rocket + 0x10, g_camera_l00_position);
                FastVecCross(vecB, vecA, rocket + 0xE0);
                vec_scale_to_length(vecB, vecB, sc);
                FastVecSub(((char **)segs)[*(int *)(vars + 0x30)], rocket + 0x10, vecB);
                rnd = math_random_signed_float_range(0.0f, 0.1f);
                FastVecScale(c90, rocket + 0xE0, rnd);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)], ((char **)segs)[*(int *)(vars + 0x30)], c90);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x60, rocket + 0x10, vecB);
                FastVecScale(c90, rocket + 0xE0, rnd);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x60, ((char **)segs)[*(int *)(vars + 0x30)] + 0x60, c90);
                FastVecScale(cA0, vecB, 0.666f);
                FastVecSub(((char **)segs)[*(int *)(vars + 0x30)] + 0x10, rocket + 0x10, cA0);
                rnd = rnd + math_random_signed_float_range(0.0f, 0.1f);
                FastVecScale(c90, rocket + 0xE0, rnd);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x10, ((char **)segs)[*(int *)(vars + 0x30)] + 0x10, c90);
                FastVecScale(cA0, vecB, 0.666f);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x50, rocket + 0x10, cA0);
                FastVecScale(c90, rocket + 0xE0, rnd);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x50, ((char **)segs)[*(int *)(vars + 0x30)] + 0x50, c90);
                FastVecScale(cA0, vecB, 0.333f);
                FastVecSub(((char **)segs)[*(int *)(vars + 0x30)] + 0x20, rocket + 0x10, cA0);
                rnd = rnd + math_random_signed_float_range(0.0f, 0.1f);
                FastVecScale(c90, rocket + 0xE0, rnd);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x20, ((char **)segs)[*(int *)(vars + 0x30)] + 0x20, c90);
                FastVecScale(cA0, vecB, 0.333f);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x40, rocket + 0x10, cA0);
                FastVecScale(c90, rocket + 0xE0, rnd);
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x40, ((char **)segs)[*(int *)(vars + 0x30)] + 0x40, c90);
                qcopy(((char **)segs)[*(int *)(vars + 0x30)] + 0x30, rocket + 0x10);
                FastVecScale(c90, rocket + 0xE0, rnd + math_random_signed_float_range(0.0f, 0.1f));
                FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + 0x30, ((char **)segs)[*(int *)(vars + 0x30)] + 0x30, c90);
                for (j5 = 0; j5 < 7; j5++) {
                    *(f32 *)(((char **)segs)[*(int *)(vars + 0x30)] + j5 * 16 + 0xC) = 0.15f;
                }
                *(int *)(vars + 0x60) = 4;
            } else {
                for (j6 = 0; j6 < 7; j6++) {
                    FastVecSub(c90, old, ((char **)segs)[*(int *)(vars + 0x30)] + j6 * 16);
                    FastVecAdd(((char **)segs)[*(int *)(vars + 0x30)] + j6 * 16, c90, rocket + 0x10);
                    *(f32 *)(((char **)segs)[*(int *)(vars + 0x30)] + j6 * 16 + 0xC) = 0.15f;
                }
            }
            ref_L00_0041CB80_00(rocket_draw_trail, rocket);
        }
        *(f32 *)(vars + 0x64) = FastAddRotations(*(f32 *)(vars + 0x64), D_L00_001B1470 * 0.000290888245f);
        glow = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x64)) * 0.5f + 0.5f;
        if (g_weapon_l00_table[g_item_slot_to_record[0x16]].b4 != 0) {
            if (*(char **)(vars + 0x68) != 0) {
                c0 = 0xFF0A0A;
                c1 = 0xFF7F7F;
            } else {
                c0 = 0xFF7FFF;
                c1 = 0xFF7FFF;
            }
        } else {
            c0 = 0x0A0AFF;
            c1 = 0x7F7FFF;
        }
        *(u32 *)(rocket + 0x78) = FastTweenColor(c0, c1, glow) | 0xFF000000;
        if (*(int *)(vars + 0x30) >= 0) {
            copy_matrix_rotation(mat, rocket + 0xC0);
            mat_get_euler_angles(mat, rocket + 0xF0);
            moby_update_transform_history_followers(slots + *(int *)(vars + 0x30) * 0x150, 0);
        }
        if (snd_is_voice_playing_for_owner(rocket, *(int *)(vars + 0x38)) == 0) {
            *(int *)(vars + 0x38) = PlayMobySound(1, 4, rocket);
        }
        break;
    case 1:
        if (*(int *)(vars + 0x30) >= 0) {
            ((int *)flags)[*(int *)(vars + 0x30)] = 0;
            level_release_slot_list(slots + *(int *)(vars + 0x30) * 0x150);
            *(int *)(vars + 0x30) = -1;
        }
        if (*(int *)(vars + 0x38) != -1) {
            se2 = (char *)g_sound_state + *(int *)(vars + 0x38) * 0x70;
            if (*(char **)(se2 + 0x88) == rocket && *(u8 *)(se2 + 0x74) != 0) {
                snd_stop_voice(*(int *)(vars + 0x38));
            }
        }
        *(int *)(vars + 0x38) = -1;
        part_spawn_explosion_with_sparks(rocket, rocket + 0x10, -1, 0.5f, 5.0f);
        table_clear_entry_flag(*(int *)(vars + 0x6C));
        moby_mark_spawned(rocket);
        break;
    }
}
