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
extern int D_L04_001B092C SDATA(D_L04_001B092C);
extern u8 *D_L04_001B0914 SDATA(D_L04_001B0914);
extern u8 *D_L04_001B24DC;
extern Collision D_L04_001BFAC0;
extern void func_001290E0(void *, void *);
extern float func_00282DF0(void *);
extern float func_00282E20(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283028(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern int func_00277258(void *, float, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern void func_002AC9F8(void *, float);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_PAL_L04_00410678(void *, void *, int, int);
#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define S(p, o) (*(short *)((u8 *)(p) + (o)))
#define B(p, o) (*((u8 *)(p) + (o)))
#define P(p, o) (*(u8 **)((u8 *)(p) + (o)))

/* Moves a vehicle along its velocity in steps shorter than its collision radius,
   handles each hit by what was struck, and slides the velocity along the surface. */
int func_PAL_L04_00418180(u8 *object, Vec *pos, Vec *vel, Vec *prev, Vec *hitpos,
                      Vec *bounce, Vec *normalOut, int *flag, int mode, int *wall,
                      float friction, float slope, float slopeLimit, float height, float radius)
{
    Vec oldpos, cur, direction, step, up, horizontal, normal;
    u8 damage[0x30] __attribute__((aligned(16)));
    int result = 0, ground, savedHit, type;
    float remaining, segment, dot, vertical, oldVertical, angle;
    int animation;
    u8 *a, *b, *other, *anim;

    cur.q = oldpos.q = pos->q;
    ground = 1;
    savedHit = 0;
    if (mode && D_L04_001B092C) {
        D_L04_001B092C = 0;
        return 2;
    }
    cur.f[2] += height;
    *flag = 0;
    up.f[0] = 0;
    up.f[1] = 0;
    up.f[2] = 1;
    up.f[3] = 0;
    remaining = func_00282DF0(vel);
    segment = radius * 0.6f;
    func_00282F20(&direction, vel, 1.0f);
    while (remaining > 0.0f) {
        if (remaining > segment) {
            func_00282F20(&step, &direction, segment);
            remaining -= segment;
        } else {
            func_00282F20(&step, &direction, remaining);
            remaining = 0;
        }
        func_00282CC0(&cur, &cur, &step);
        if (func_00277258(&cur, radius, 4, object)) {
            func_00282F20(&normal, &D_L04_001BFAC0.normal, 1.0f);
            if (D_L04_001BFAC0.object) {
                vertical = cur.f[2];
                cur.q = ((Vec *)(&D_L04_001BFAC0.position))->q;
                horizontal.q = normal.q;
                cur.f[2] = vertical;
                horizontal.f[2] = 0;
                func_001290E0(&horizontal, &horizontal);
                if (!savedHit) {
                    hitpos->q = ((Vec *)(&D_L04_001BFAC0.point))->q;
                    savedHit = 1;
                }
                type = 0xA1F;
                result = 1;
                if (S(D_L04_001BFAC0.object, 0xAA) == type) {
                    result = 2;
                } else if (!mode && S(D_L04_001BFAC0.object, 0xAA) == 0xB2D) {
                    a = P(D_L04_001BFAC0.object, 0x68);
                    I(a, 0x178) = 33;
                    func_00282D30(a + 0x100, &horizontal, -0.05f);
                    a = P(object, 0x68);
                    I(a, 0x178) = 33;
                    func_00282D30(a + 0x100, &horizontal, 0.05f);
                } else if ((mode && S(D_L04_001BFAC0.object, 0xAA) == 0xB2D)
                           || (!mode && S(D_L04_001BFAC0.object, 0xAA) == 0xBBC)) {
                    func_PAL_L04_00410678(&D_L04_001BFAC0.point, vel, 2, 0);
                    if (mode) {
                        b = P(object, 0x68);
                        other = D_L04_001BFAC0.object;
                        a = P(other, 0x68);
                        func_00282D30(b + 0x2F0, &horizontal, 0.04f);
                        func_00282D30(a + 0x100, &horizontal, -0.04f);
                    } else {
                        a = P(object, 0x68);
                        other = object;
                        b = P(P(a, 0x164), 0x68);
                        func_002E5CF8(2, 0, P(a, 0x164));
                        func_00282D30(b + 0x2F0, &horizontal, -0.04f);
                        func_00282D30(a + 0x100, &horizontal, 0.04f);
                        if (I(b, 0x1DC) != -1) {
                            anim = D_L04_001B24DC + (I(b, 0x1DC) << 8);
                            angle = func_00283248(D_L04_001BFAC0.point.f[0] - F(object, 0x10),
                                                  D_L04_001BFAC0.point.f[1] - F(object, 0x14));
                            angle = func_00283BE0(F(P(a, 0x164), 0xF8), angle);
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
                                func_PAL_002A7E68(anim, animation, 3, 2);
                            }
                        }
                    }
                    dot = func_00282DB0(other + 0xD0, a + 0x100);
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
                        if (I(a, 0x1BC) >= 4) func_00282D30(&step, other + 0xC0, 0.02f);
                        else func_00282D30(&step, other + 0xC0, 0.005f);
                        if (dot < 0) func_00282D30(a + 0x100, other + 0xD0, -0.035f);
                        else func_00282D30(a + 0x100, other + 0xD0, 0.035f);
                        func_00282CC0(a + 0x100, a + 0x100, &step);
                        func_00282D30(a + 0x100, a + 0x100, (float)I(a, 0x1BC) * 0.05f + 1.0f);
                        func_00282D30(b + 0x2F0, b + 0x2F0, 1.15f);
                    } else {
                        dot = 1.0f;
                        if (I(b, 0x4D8)) dot = 1.5f;
                        func_00282D30(a + 0x100, a + 0x100, dot);
                    }
                    if ((S(b, 0x274) || B(a, 0xA5)) && func_00282DB0(&up, &normal) > 0.707f) {
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
                } else if (S(D_L04_001BFAC0.object, 0xAA) == 0x8BA || S(D_L04_001BFAC0.object, 0xAA) == 0xA77) {
                    *flag = 3;
                    func_002A8C00(damage, object, 0x30000, &step, 1.0f);
                    B(damage, 0x18) = 0;
                    B(damage, 0x19) = 1;
                    S(damage, 0x1A) = S(object, 0xAA);
                    func_002A8E20(D_L04_001BFAC0.object, damage);
                    if (friction > 0.3f || S(D_L04_001BFAC0.object, 0xAA) == 0xA77) result = 2;
                }
            } else {
                cur.q = ((Vec *)(&D_L04_001BFAC0.position))->q;
                result = 1;
                if (!savedHit) {
                    hitpos->q = ((Vec *)(&D_L04_001BFAC0.point))->q;
                    savedHit = 1;
                }
                dot = func_00282DB0(&direction, &normal);
                if (dot < -0.2f) *wall = 1;
                else *wall = 0;
                if ((slopeLimit < slope && dot < -0.866f) || func_00278E78() == 1 || func_00278E78() == 3) {
                    cur.q = ((Vec *)(&D_L04_001BFAC0.position))->q;
                    func_00283028(bounce, vel, &normal);
                    result = 2;
                    ground = 0;
                    break;
                }
                if (func_00278E78() == 2 || func_00278E78() == 4) *flag = 1;
            }
            if (normal.f[2] > 0.707f && !D_L04_001BFAC0.object) {
                normalOut->q = normal.q;
                dot = func_00282DB0(vel, normalOut);
                func_00282D30(&step, normalOut, -dot);
                func_00282CC0(vel, vel, &step);
                vertical = vel->f[2];
                vel->f[2] = 0;
                func_002AC9F8(vel, friction);
                if (!D_L04_001BFAC0.object || vertical < 0) vel->f[2] = vertical;
                prev->f[2] = vel->f[2];
                ground = 0;
            } else {
                if (normal.f[2] > 0) normal.f[2] = 0;
                if (vel->f[2] > 0) {
                    vel->f[2] = 0;
                    direction.f[2] = 0;
                }
                func_001290E0(&normal, &normal);
                dot = func_00282DB0(vel, &normal);
                func_00282D30(&step, &normal, -dot);
                func_00282CC0(vel, vel, &step);
                if (mode) {
                    a = P(object, 0x68);
                    dot = func_00282DF0(vel);
                    if (dot < (F(a, 0x30C) + F(a, 0x27C)) * 0.020000001f) {
                        F(a, 0x27C) = 0;
                        if (dot < F(a, 0x30C)) F(a, 0x30C) = dot;
                    }
                }
            }
            dot = func_00282DB0(&normal, &direction);
            func_00282D30(&step, &normal, -dot);
            func_00282CC0(&direction, &direction, &step);
        }
    }
    pos->q = cur.q;
    if (ground) {
        pos->f[2] -= height;
        if (func_00277258(pos, radius, 4, object)) {
            if (func_00278E78() == 1 || func_00278E78() == 3) result = 2;
            pos->q = ((Vec *)(&D_L04_001BFAC0.position))->q;
            angle = func_00283248(D_L04_001BFAC0.normal.f[2], func_00282E20(&D_L04_001BFAC0.normal));
            if (angle < 0.785398245f) {
                oldVertical = vel->f[2];
                func_00282F20(normalOut, &D_L04_001BFAC0.normal, 1.0f);
                dot = func_00282DB0(vel, normalOut);
                func_00282D30(&step, normalOut, -dot);
                func_00282CC0(vel, vel, &step);
                vertical = vel->f[2];
                vel->f[2] = 0;
                func_002AC9F8(vel, friction);
                if (!D_L04_001BFAC0.object || vertical < 0) vel->f[2] = vertical;
                if (oldVertical < 0 && vel->f[2] > 0) vel->f[2] = 0;
                prev->f[2] = vel->f[2];
            } else if (vel->f[2] > 0) {
                vel->f[2] = 0;
            }
        }
    }
    if (func_002761F8(&oldpos, pos, 4, object, 0)) {
        result = 2;
        pos->q = oldpos.q;
    }
    if (B(D_L04_001B0914, 0xBC) == 1 || B(D_L04_001B0914, 0xBC) == 3 || B(D_L04_001B0914, 0xBC) == 4) result = 0;
    return result;
}
