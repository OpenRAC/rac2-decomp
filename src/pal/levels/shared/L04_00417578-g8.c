#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
typedef struct {
    u8 pad[0x18];
    u8 *object;
    int pad1C;
    Vec point, position, normal;
    float distance;
} Collision;
extern int g_race_mode_active_flag SDATA(D_L04_001B092C);
extern u8 *g_race_controller SDATA(D_L04_001B0914);
extern u8 *g_moby_l04_pool;
extern Collision g_probe_hit;
extern void func_001290E0(void *, void *);
extern float FastVecLength(void *);
extern float vec_length_xy(void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern int coll_test_point(void *, float, int, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern void vec_clamp_length(void *, float);
extern int PlayMobySound(int, int, void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void part_l04_spawn_burst_pal(void *, void *, int, int);
#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define S(p, o) (*(short *)((u8 *)(p) + (o)))
#define B(p, o) (*((u8 *)(p) + (o)))
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))

/* Moves a vehicle along its velocity in steps shorter than its collision radius,
   handles each hit by what was struck, and slides the velocity along the surface. */
int resolve_vehicle_movement_collisions_pal(u8 *object, Vec *pos, Vec *vel, Vec *prev, Vec *hitpos,
                      Vec *bounce, Vec *normal_out, int *flag, int mode, int *wall,
                      float friction, float slope, float slope_limit, float height, float radius)
{
    Vec oldpos, cur, direction, step, up, horizontal, normal;
    u8 damage[0x30] __attribute__((aligned(16)));
    int result = 0, ground, saved_hit, type;
    float remaining, segment, dot, vertical, old_vertical, angle;
    int animation;
    u8 *a, *b, *other, *anim;

    cur.q = oldpos.q = pos->q;
    ground = 1;
    saved_hit = 0;
    if (mode && g_race_mode_active_flag) {
        g_race_mode_active_flag = 0;
        return 2;
    }
    cur.f[2] += height;
    *flag = 0;
    up.f[0] = 0;
    up.f[1] = 0;
    up.f[2] = 1;
    up.f[3] = 0;
    remaining = FastVecLength(vel);
    segment = radius * 0.6f;
    vec_scale_to_length(&direction, vel, 1.0f);
    while (remaining > 0.0f) {
        if (remaining > segment) {
            vec_scale_to_length(&step, &direction, segment);
            remaining -= segment;
        } else {
            vec_scale_to_length(&step, &direction, remaining);
            remaining = 0;
        }
        FastVecAdd(&cur, &cur, &step);
        if (coll_test_point(&cur, radius, 4, object)) {
            vec_scale_to_length(&normal, &g_probe_hit.normal, 1.0f);
            if (g_probe_hit.object) {
                vertical = cur.f[2];
                cur.q = ((Vec *)(&g_probe_hit.position))->q;
                horizontal.q = normal.q;
                cur.f[2] = vertical;
                horizontal.f[2] = 0;
                func_001290E0(&horizontal, &horizontal);
                if (!saved_hit) {
                    hitpos->q = ((Vec *)(&g_probe_hit.point))->q;
                    saved_hit = 1;
                }
                type = 0xA1F;
                result = 1;
                if (S(g_probe_hit.object, 0xAA) == type) {
                    result = 2;
                } else if (!mode && S(g_probe_hit.object, 0xAA) == MOBY_CLASS_ENEMY_HOVERBIKE) {
                    a = P(g_probe_hit.object, 0x68);
                    I(a, 0x178) = 33;
                    FastVecScale(a + 0x100, &horizontal, -0.05f);
                    a = P(object, 0x68);
                    I(a, 0x178) = 33;
                    FastVecScale(a + 0x100, &horizontal, 0.05f);
                } else if ((mode && S(g_probe_hit.object, 0xAA) == MOBY_CLASS_ENEMY_HOVERBIKE)
                           || (!mode && S(g_probe_hit.object, 0xAA) == 0xBBC)) {
                    part_l04_spawn_burst_pal(&g_probe_hit.point, vel, 2, 0);
                    if (mode) {
                        b = P(object, 0x68);
                        other = g_probe_hit.object;
                        a = P(other, 0x68);
                        FastVecScale(b + 0x2F0, &horizontal, 0.04f);
                        FastVecScale(a + 0x100, &horizontal, -0.04f);
                    } else {
                        a = P(object, 0x68);
                        other = object;
                        b = P(P(a, 0x164), 0x68);
                        PlayMobySound(2, 0, P(a, 0x164));
                        FastVecScale(b + 0x2F0, &horizontal, -0.04f);
                        FastVecScale(a + 0x100, &horizontal, 0.04f);
                        if (I(b, 0x1DC) != -1) {
                            anim = g_moby_l04_pool + (I(b, 0x1DC) << 8);
                            angle = mat_fast_helper_a(g_probe_hit.point.f[0] - F(object, 0x10),
                                                  g_probe_hit.point.f[1] - F(object, 0x14));
                            angle = fast_subtract_rotations(F(P(a, 0x164), 0xF8), angle);
                            if (angle > 0.52359885f && angle < 2.61799407f) {
                                animation = 3;
                            } else {
                                animation = 5;
                                if (angle < -0.52359885f && angle > -2.61799407f) animation = 4;
                            }
                            if (I(b, 0x36C) && S(b, 0x34A) == animation) {
                                I(b, 0x36C) = 25;
                            } else {
                                I(b, 0x36C) = 25;
                                S(b, 0x34A) = animation;
                                anim_start_blended_pal(anim, animation, 3, 2);
                            }
                        }
                    }
                    dot = FastVecDot(other + 0xD0, a + 0x100);
                    if (dot < 0) {
                        F(a, 0x1F4) = 0.17453295f;
                        F(b, 0x4C8) = -0.261799425f;
                        F(a, 0x1F8) = 5;
                    } else {
                        F(a, 0x1F4) = -0.17453295f;
                        F(b, 0x4C8) = 0.261799425f;
                        F(a, 0x1F8) = 5;
                    }
                    if (I(a, 0x1C0) > 0) {
                        I(a, 0x1BC)++;
                        if (I(a, 0x1BC) >= 4) FastVecScale(&step, other + 0xC0, 0.02f);
                        else FastVecScale(&step, other + 0xC0, 0.005f);
                        if (dot < 0) FastVecScale(a + 0x100, other + 0xD0, -0.035f);
                        else FastVecScale(a + 0x100, other + 0xD0, 0.035f);
                        FastVecAdd(a + 0x100, a + 0x100, &step);
                        FastVecScale(a + 0x100, a + 0x100, (float)I(a, 0x1BC) * 0.05f + 1.0f);
                        FastVecScale(b + 0x2F0, b + 0x2F0, 1.15f);
                    } else {
                        dot = 1.0f;
                        if (I(b, 0x4D8)) dot = 1.5f;
                        FastVecScale(a + 0x100, a + 0x100, dot);
                    }
                    if ((S(b, 0x274) || B(a, 0xA5)) && FastVecDot(&up, &normal) > 0.707f) {
                        F(a, 0x138) *= 0.65f;
                        F(a, 0x13C) *= 0.65f;
                    }
                    I(b, 0x71C) = 0;
                    I(b, 0x64C) = 33;
                    if (I(a, 0x178) <= 0) I(a, 0x178) = 33;
                    if (I(a, 0x1C0) > 0 && I(a, 0x1F0) == 1) {
                        I(b, 0x64C) = 48;
                        F(a, 0x1E8) = 1;
                    }
                    *flag = 2;
                } else if (S(g_probe_hit.object, 0xAA) == 0x8BA || S(g_probe_hit.object, 0xAA) == MOBY_CLASS_HOVERBIKE_RACE_BOMB) {
                    *flag = 3;
                    make_hit_descriptor(damage, object, 0x30000, &step, 1.0f);
                    B(damage, 0x18) = 0;
                    B(damage, 0x19) = 1;
                    S(damage, 0x1A) = S(object, 0xAA);
                    QueueMobyImpact(g_probe_hit.object, damage);
                    if (friction > 0.3f || S(g_probe_hit.object, 0xAA) == MOBY_CLASS_HOVERBIKE_RACE_BOMB) result = 2;
                }
            } else {
                cur.q = ((Vec *)(&g_probe_hit.position))->q;
                result = 1;
                if (!saved_hit) {
                    hitpos->q = ((Vec *)(&g_probe_hit.point))->q;
                    saved_hit = 1;
                }
                dot = FastVecDot(&direction, &normal);
                if (dot < -0.2f) *wall = 1;
                else *wall = 0;
                if ((slope_limit < slope && dot < -0.866f) || GetCollHitMaterial() == 1 || GetCollHitMaterial() == 3) {
                    cur.q = ((Vec *)(&g_probe_hit.position))->q;
                    vec_fast_normalize(bounce, vel, &normal);
                    result = 2;
                    ground = 0;
                    break;
                }
                if (GetCollHitMaterial() == 2 || GetCollHitMaterial() == 4) *flag = 1;
            }
            if (normal.f[2] > 0.707f && !g_probe_hit.object) {
                normal_out->q = normal.q;
                dot = FastVecDot(vel, normal_out);
                FastVecScale(&step, normal_out, -dot);
                FastVecAdd(vel, vel, &step);
                vertical = vel->f[2];
                vel->f[2] = 0;
                vec_clamp_length(vel, friction);
                if (!g_probe_hit.object || vertical < 0) vel->f[2] = vertical;
                prev->f[2] = vel->f[2];
                ground = 0;
            } else {
                if (normal.f[2] > 0) normal.f[2] = 0;
                if (vel->f[2] > 0) {
                    vel->f[2] = 0;
                    direction.f[2] = 0;
                }
                func_001290E0(&normal, &normal);
                dot = FastVecDot(vel, &normal);
                FastVecScale(&step, &normal, -dot);
                FastVecAdd(vel, vel, &step);
                if (mode) {
                    a = P(object, 0x68);
                    dot = FastVecLength(vel);
                    if (dot < (F(a, 0x30C) + F(a, 0x27C)) * 0.020000001f) {
                        F(a, 0x27C) = 0;
                        if (dot < F(a, 0x30C)) F(a, 0x30C) = dot;
                    }
                }
            }
            dot = FastVecDot(&normal, &direction);
            FastVecScale(&step, &normal, -dot);
            FastVecAdd(&direction, &direction, &step);
        }
    }
    pos->q = cur.q;
    if (ground) {
        pos->f[2] -= height;
        if (coll_test_point(pos, radius, 4, object)) {
            if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 3) result = 2;
            pos->q = ((Vec *)(&g_probe_hit.position))->q;
            angle = mat_fast_helper_a(g_probe_hit.normal.f[2], vec_length_xy(&g_probe_hit.normal));
            if (angle < 0.785398245f) {
                old_vertical = vel->f[2];
                vec_scale_to_length(normal_out, &g_probe_hit.normal, 1.0f);
                dot = FastVecDot(vel, normal_out);
                FastVecScale(&step, normal_out, -dot);
                FastVecAdd(vel, vel, &step);
                vertical = vel->f[2];
                vel->f[2] = 0;
                vec_clamp_length(vel, friction);
                if (!g_probe_hit.object || vertical < 0) vel->f[2] = vertical;
                if (old_vertical < 0 && vel->f[2] > 0) vel->f[2] = 0;
                prev->f[2] = vel->f[2];
            } else if (vel->f[2] > 0) {
                vel->f[2] = 0;
            }
        }
    }
    if (CollLine(&oldpos, pos, 4, object, 0)) {
        result = 2;
        pos->q = oldpos.q;
    }
    if (B(g_race_controller, 0xBC) == 1 || B(g_race_controller, 0xBC) == 3 || B(g_race_controller, 0xBC) == 4) result = 0;
    return result;
}
