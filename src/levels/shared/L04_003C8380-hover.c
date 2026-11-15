#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
extern char ref_L04_00400EE0_00[];
extern int D_001A79F0 __attribute__((sda));
extern int D_L04_001A8FE8 __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern float D_L04_001BFB00[];
extern char D_L04_001A8F20[] __attribute__((sda));
extern float func_002A89A8(char *, int, float);
extern int func_00278E78(void);
extern void func_00283388(float *);
extern void func_00283698(void *dst, void *src);
extern void func_00282CF0(float *out, float *a, float *b);
extern void func_002830C0(float *out, float *a, float *m);
extern float func_00282C48(float);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00282D30(float *out, float *in, float scale);
extern void func_00282CC0(float *out, float *a, float *b);
extern void func_00282CD8(float *out, float *a, float *b);
extern float func_00282DB0(void *, void *);
extern float func_002AA3A8(float *, float *, float, float, float, float);
extern void func_00283098(float *out, float *in, void *m);
extern float func_00282DF0(float *);
extern float func_002AA898(float *position, float target, float *velocity,
                           float acceleration, float damping, float limit, int direction);
extern void func_L04_00400D48(u8 *, u8 *, int);
extern float func_002AA2E8(float *value, float target, float step);
extern void func_L04_0040BD50(Vec *, int, int, float, float);
extern float func_00283CE0(int);
extern int func_L04_00343498(u8 *, float);
extern float func_002AA140(float, float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002AC9F8(float *p, float threshold);
extern void func_002AEC48(void *a0, void *a1, int a2, float f12, float f13);
extern int func_00282948(void *);
extern void func_L04_0040C0C0(Vec *, void *, int, int);
extern void func_00282F20(float *, float *, float);
extern void func_L04_00347AB8(void *a0, void *a1, void *a2, void *a3, float f1, float f2, float f3);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern int func_L04_00413A38(u8 *, u8 *, u8 *, u8 *, Vec *, Vec *, Vec *, u8 *, int, int *,
                             float, float, float, float, float);
extern int func_L04_00410E48(int a0, int a1, float f12);
extern int func_002A9640(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern u8 *func_L04_00407078(u8 *, int, Vec *, u8 *, int, int, float, Vec *, char *, float, char *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
/* Struct views for the rider lookup: retail schedules these loads as struct-field accesses
 * (no alias with the stack slot of `flag`), unlike plain pointer casts. */
typedef struct { u8 pad[0x68]; u8 *rider; } TrackTarget;
typedef struct { u8 pad[0x164]; TrackTarget *target; } BikeTarget;
#define I(o) (*(s32 *)(bike + (o)))
#define F(o) (*(float *)(bike + (o)))
#define S(o) (*(s16 *)(bike + (o)))
#define P(o) (*(u8 **)(bike + (o)))
#define OF(o) (*(float *)(object + (o)))
#define RF(o) (*(float *)(rider + (o)))

/* Hoverbike race movement (Barlow and Joba): follows the track target or steers freely, sets
 * speed, hover height and landing, applies the collision result and, on a crash (result 2),
 * spawns debris and an explosion.  ref_L04_00400EE0_00 is the link-time level number (4 or 11).
 * object+0x10, bike+0xD0 and bike+0xE0 are written as expressions: retail keeps them in
 * gcse's PRE registers, not in source variables. */
void func_L04_00400EE0(u8 *object, u8 *bike)
{
    Vec hit, v30, v40, start, v60, delta;
    Vec m[4];
    Vec vC0, vD0, vE0;
    int flag;
    float ground, height, limit, speed, rate, side, t;
    u8 *rider;
    int result;

    hit.q = 0;
    hit.f[3] = -1.0f;
    start.q = *(Quad *)(object + 0x10);
    ground = func_002A89A8((char *)(object + 0x10), 0, 0.5f);
    limit = 0.0f;
    speed = limit;
    flag = 0;
    height = OF(0x18) - ground;
    rider = ((BikeTarget *)bike)->target->rider;
    if (GetCollHitMaterial() == 7 && bike[0xA5] == 0)
        I(0x244) = 1;
    else
        I(0x244) = 0;
    if (I(0x1C0) > 0) {
        float cap;
        set_identity_matrix(m[0].f);
        matrix_from_basis_rows(m, P(0x164) + 0xC0);
        FastVecSub(delta.f, (float *)(object + 0x10), (float *)(P(0x164) + 0x10));
        transform_vector(vE0.f, delta.f, m[0].f);
        side = func_00282C48(vE0.f[0]);
        if (I(0x1F0) == 0 && F(0x1E4) >= 1.0f && side < 1.5f && func_00282C48(vE0.f[1]) >= 1.0f) {
            I(0x1F0) = 1;
            F(0x1E8) = 0.05f;
            F(0x1F8) = 2.0f;
            if (vE0.f[1] > 0.0f) F(0x1F4) = 0.3490659f;
            else F(0x1F4) = -0.3490659f;
        }
        F(0x2B0) = 0.0f;
        if (I(0x1F0) == 1 && *(s16 *)(rider + 0x274) == 0) {
            F(0x2B0) = fast_subtract_rotations(func_00283248(delta.f[0], delta.f[1]), OF(0xF8)) * 0.9f;
            if (F(0x2B0) > 1.5707964f) F(0x2B0) = 1.5707964f;
            if (F(0x2B0) < -1.5707964f) F(0x2B0) = -1.5707964f;
            if (I(0x178) > 0) F(0x2B0) = F(0x2B0) * 0.45f;
            func_002AA548((float *)(bike + 0x1E4), (float *)(bike + 0x1EC), F(0x1E8), 0.0025f, 0.0025f, 0.200000018f);
            if (F(0x1E8) == 1.0f && F(0x1E4) >= 1.0f) {
                F(0x1E8) = 1.0f;
                I(0x1F0) = 0;
            }
        } else {
            func_002AA548((float *)(bike + 0x1E4), (float *)(bike + 0x1EC), F(0x1E8), 0.000277777785f, 0.000277777785f, 0.13333334f);
        }
        if (vE0.f[1] > 0.0f)
            FastVecScale(delta.f, (float *)(P(0x164) + 0xD0), F(0x1E4));
        else
            FastVecScale(delta.f, (float *)(P(0x164) + 0xD0), -F(0x1E4));
        FastVecAdd(vC0.f, (float *)(P(0x164) + 0x10), delta.f);
        FastVecScale(delta.f, (float *)(rider + 0x290), 5.0f);
        FastVecAdd(vC0.f, vC0.f, delta.f);
        set_identity_matrix(m[0].f);
        matrix_from_basis_rows(m, object + 0xC0);
        FastVecSub(delta.f, vC0.f, (float *)(object + 0x10));
        transform_vector(vD0.f, delta.f, m[0].f);
        rate = func_00282C48(vE0.f[0]) * 0.8f;
        if (rate > 1.0f) rate = 1.0f;
        if (rate < 0.0f) rate = 0.0f;
        RF(0x63C) = (1.0f - rate) * 1.75f;
        if (RF(0x63C) < 1.0f) RF(0x63C) = 1.0f;
        rate = (0.1f - vE0.f[0]) * 12.5f;
        F(0x134) = RF(0x30C) + RF(0x27C);
        if (rate > 0.0f) {
            if (rate < 1.0f) rate = 0.0f;
            else if (rate > 4.0f) rate = 4.0f;
        } else if (rate > -1.0f) {
            rate = 0.0f;
        } else if (rate < -4.0f) {
            rate = -4.0f;
        }
        t = F(0x134) * (rate * 0.03f);
        F(0x134) = F(0x134) + t;
        if (func_00282C48(F(0x1D4)) > 1.04719758f || *(int *)(rider + 0x3A4) > 0 ||
            FastVecDot(&vE0, &vE0) > 121.0f || F(0x134) < 0.100000009f) {
            I(0x1C0) = 0;
            I(0x1F0) = 5;
        }
        if (F(0x2D0) > 0.0f) {
            cap = F(0x2D4) * 0.0166666675f;
            if (cap < F(0x134)) F(0x134) = cap;
        }
        func_002AA3A8((float *)(bike + 0x138), (float *)(bike + 0x158), F(0x134), 0.027f, 0.2f, 0.00555555569f);
        if (vD0.f[0] < 5.0f) vD0.f[0] = 5.0f;
        matrix_mul_vec3(delta.f, vD0.f, object + 0xC0);
        FastVecScale((float *)(bike + 0xD0), delta.f, F(0x138) / FastVecLength(delta.f));
        F(0xD8) = F(0xE8);
        func_002AA898((float *)(object + 0xF8), *(float *)(P(0x164) + 0xF8), (float *)(bike + 0x130), 0.03f, 0.3f, 0.0727220625f, 0);
        if (--I(0x1C0) <= 0) func_L04_00400D48(object, bike, 0);
    } else {
        int idle = 1;
        F(0x2B0) = 0.0f;
        I(0x2B4) = 0;
        I(0x2B8) = 0;
        I(0x1F4) = 0;
        if (I(0x144) != 0 && bike[0xA5] == 0) {
            ApproachValue((float *)(bike + 0x138), 0.0500000045f, 0.00305555575f);
            idle = 0;
        } else if (GetCollHitMaterial() == 0 && bike[0xA5] == 0) {
            float z;
            if (F(0x138) > 0.191666678f) {
                ApproachValue((float *)(bike + 0x138), 0.191666678f, 0.00319444458f);
                idle = 0;
            }
            S(0x140) = 0;
            z = ground - 0.25f;
            m[0].q = *(Quad *)(object + 0x10);
            m[0].f[2] = z;
            func_L04_0040BD50(&m[0], 2, 0, z, F(0x138) + F(0x13C));
        }
        if (idle) {
            if (D_L04_001A8FE8 < 240 && I(0x9C) >= 11)
                rate = 0.0162000004f;
            else
                rate = (float)(I(0x1A8) / 10) * 0.05f + 0.027f;
            func_002AA3A8((float *)(bike + 0x138), (float *)(bike + 0x158), F(0x134),
                          I(0x244) != 0 ? rate * 0.5f : rate, 0.2f,
                          I(0x244) != 0 ? 0.00277777785f : 0.00555555569f);
        }
        if (P(0x164)[0x20] == 2 && (u32)(P(0x164)[0xBC] - 3) < 2) {
            F(0x138) = 0.0f;
            speed = F(0x138);
        } else {
            float damping, heading, factor;
            speed = F(0x138) + F(0x13C);
            if (I(0x1F0) == 5 && F(0x138) >= 0.33225f) I(0x1F0) = 0;
            if (I(0x1F0) == 4 && I(0x168) == 0) I(0x1F0) = 0;
            side = 1.0f;
            damping = 0.03f;
            limit = 0.0f;
            heading = func_00283248(F(0xF0) - OF(0x10), F(0xF4) - OF(0x14));
            t = F(0x138) * 2.70880365f;
            if (t > side) t = side;
            if (func_L04_00343498(object, IntToFloat(*(s16 *)(object + 0x32))) < 0) t = limit;
            limit = func_002AA140(0.0727220625f, 0.034906592f, t);
            factor = (side - t) + side;
            if (factor > 1.9f) factor = 1.9f;
            if (I(0x244) != 0) {
                limit = limit * 1.25f;
                factor = 2.75f;
            }
            damping = factor * damping;
            if (limit < 2.9088826e-05f) limit = 2.9088826e-05f;
            func_002AA898((float *)(object + 0xF8), heading, (float *)(bike + 0x130), damping, 0.3f, limit, 0);
        }
        if (*(u8 **)(rider + 0x730) == object) speed = RF(0x30C) + RF(0x27C);
        if (F(0x2D0) > 0.0f) {
            float cap = F(0x2D4) * 0.0166666675f;
            if (cap < speed) speed = cap;
        }
        t = OF(0xF8);
        delta.f[0] = func_00283180(t) * speed;
        delta.f[1] = func_00283198(t) * speed;
        delta.i[2] = 0;
        if (I(0x244) != 0) {
            if (I(0x178) != 0 && I(0x248) != 0) {
                FastVecScale(delta.f, (float *)(bike + 0x100), (float)I(0x178) * 0.025f);
                FastVecSub((float *)(bike + 0xD0), (float *)(bike + 0xD0), delta.f);
                I(0x248) = 0;
            }
            FastVecScale(delta.f, delta.f, 0.025f);
            FastVecAdd((float *)(bike + 0xD0), (float *)(bike + 0xD0), delta.f);
            func_002AC9F8((float *)(bike + 0xD0), speed);
        } else {
            *(Quad *)(bike + 0xD0) = delta.q;
        }
    }
    if (D_001A7A40[7] != 0) F(0x2C0) = 2.5f;
    else F(0x2C0) = 1.0f;
    if (P(0x8C) != 0) func_002AEC48(P(0x8C), bike + 0x250, 0, 0.08f, 0.5f);
    if (!func_00282948(bike + 0x178)) {
        FastVecScale(delta.f, (float *)(bike + 0x100), (float)I(0x178) * 0.025f);
        FastVecAdd((float *)(bike + 0xD0), (float *)(bike + 0xD0), delta.f);
        I(0x248) = 1;
    }
    if (I(0x148) >= 8) {
        F(0xD8) = F(0xE8) + 0.00333333341f;
    } else if (height > 0.3f) {
        float extra;
        if (((int)ref_L04_00400EE0_00 == 0x28 || D_001A79F0 == 4) && bike[0xA5] != 0 && I(0x120) == -1 && I(0x124) >= 476) {
            t = F(0x13C) * 9.99999905f;
            if (t > 1.0f) t = 1.0f;
            else if (t < 0.0f) t = 0.0f;
            extra = t * 3.0f + 1.5f;
        } else {
            extra = 0.0f;
        }
        t = ((height - 0.2f) + 0.1f) * 3.33333325f;
        if (t > 1.0f) t = 1.0f;
        if (t < 0.0f) t = 0.0f;
        F(0xD8) = F(0xE8) - (extra + 12.0f) * t * 0.000277777785f;
    } else {
        t = ((0.2f - height) + 0.1f) * 5.0f;
        if (t > 1.0f) t = 1.0f;
        if (t < 0.0f) t = 0.0f;
        t *= 0.23f;
        F(0xD8) = F(0xE8) + t * 0.00333333341f;
    }
    if (height > 0.44f) {
        bike[0xA5] = 1;
        *(u16 *)(bike + 0xA6) = *(u16 *)(bike + 0xA6) + 1;
    } else {
        if (bike[0xA5] != 0 && S(0xA6) >= 13 && F(0x154) < 0.0f) {
            if (GetCollHitMaterial() == 0) {
                if (S(0xA6) >= 46) {
                    float z = ground - 0.25f;
                    m[0].q = *(Quad *)(object + 0x10);
                    m[0].f[2] = z;
                    func_L04_0040BD50(&m[0], 10, 1, z, F(0x138) + F(0x13C));
                }
            } else {
                if (S(0xA6) >= 46) {
                    FastVecScale(hit.f, (float *)(bike + 0xE0), 0.5f);
                    add_vectors(m[0].f, hit.f, (float *)(object + 0x10));
                    v30.q = *(Quad *)(bike + 0xE0);
                    hit.f[2] = OF(0x18);
                    v30.f[2] = 0.0166666675f;
                    FastVecScale(v30.f, v30.f, 0.85f);
                    func_L04_0040C0C0(&hit, &v30, 8, 1);
                }
                if (bike[0xA4] == 0 && GetCollHitMaterial() != 5) {
                    float sink;
                    if (F(0x154) > -0.05f) F(0x154) = -0.05f;
                    sink = F(0x154);
                    t = 1.0f - (sink + 0.35f) * 2.85714293f;
                    if (t > 1.0f) t = 1.0f;
                    if (t < 0.0f) t = 0.0f;
                    I(0x148) = (int)(t * 5.0f) + 15;
                    if (t < 0.5f) t = 0.5f;
                    bike[0xA4] = 1;
                    F(0x14C) = t * 0.06f;
                    F(0xE8) = sink * -0.3f;
                }
            }
        }
        bike[0xA5] = 0;
        *(u16 *)(bike + 0xA6) = 0;
    }
    {
        t = OF(0xF0);
        if (bike[0xA4] != 0) {
            OF(0xF4) = OF(0xF4) + F(0x14C);
            func_00282948(bike + 0x148);
            if (I(0x148) == 0) bike[0xA4] = 0;
        } else if (bike[0xA5] == 0) {
            vec_scale_to_length(v40.f, D_L04_001BFB00, 1.0f);
            func_L04_00347AB8(object + 0xC0, object + 0xF0, bike + 0x12C, &v40, 0.03f, 0.3f, 0.0f);
        } else {
            func_002AF000(v40.f, 1.0f, FastAddRotations(OF(0xF8), 3.14159274f), 0.87266469f);
            func_L04_00347AB8(object + 0xC0, object + 0xF0, bike + 0x12C, &v40, 0.03f, 0.3f, 0.0f);
        }
        OF(0xF0) = t;
    }
    {
        float wobble;
        F(0x150) = FastAddRotations(F(0x150), 0.15f);
        wobble = func_00283180(F(0x150)) * 0.004f;
        OF(0xF4) = OF(0xF4) + func_00283198(F(0x150)) * 0.004f;
        OF(0xF0) = OF(0xF0) + wobble;
    }
    *(Quad *)(bike + 0xE0) = *(Quad *)(bike + 0xD0);
    F(0x154) = F(0xE8);
    result = ResolveVehicleMovementCollisions(object, object + 0x10, bike + 0xD0, bike + 0xE0, &hit, &v60, &v40, bike + 0x144, 0, &flag,
                               speed, limit, F(0x134), F(0x94), F(0x90));
    if (result != 0 && I(0x244) != 0) FastVecScale((float *)(bike + 0xD0), (float *)(bike + 0xD0), 0.85f);
    if (flag != 0)
        I(0x1AC) = I(0x1AC) + 1;
    else
        I(0x1AC) = 0;
    if (OF(0x18) < F(0x98) || func_L04_00410E48(I(0x120), I(0x124), OF(0x18))) result = 2;
    if (func_002A9640(object, -1, 0)) {
        result = 2;
        v60.q = *(Quad *)(bike + 0xD0);
    }
    object[0xA8] = 0xFF;
    if (I(0x1AC) >= 2 && I(0x1C0) > 0 && I(0x178) > 0 && I(0x1BC) >= 4) result = 2;
    if ((u32)(P(0x164)[0xBC] - 5) < 2) {
        FastVecSub(delta.f, (float *)(object + 0x10), start.f);
        delta.i[2] = 0;
        if (FastVecDot(&delta, &delta) < 0.01f) {
            if (++I(0x24C) >= 26) result = 2;
        } else {
            I(0x24C) = 0;
        }
    }
    switch (result) {
    case 1: {
        float a = FastAddRotations(func_00283248(hit.f[0] - OF(0x10), hit.f[1] - OF(0x14)), 3.14159274f);
        func_002AA898((float *)(object + 0xF8), a, (float *)(bike + 0x130), 0.011f, 0.3f, 6.0f, 0);
        if (P(0x8C) != 0) {
            int dir;
            a = fast_subtract_rotations(OF(0xF8), func_00283248(hit.f[0] - OF(0x10), hit.f[1] - OF(0x14)));
            if (a > 0.52359885f && a < 2.61799407f) dir = 2;
            else if (a < -0.52359885f && a > -2.61799407f) dir = 1;
            else if (func_00282C48(a) < 0.52359885f) dir = 4;
            else dir = 3;
            if (S(0x17E) != 0 && S(0x17C) == dir) {
                S(0x17E) = 30;
            } else {
                S(0x17E) = 30;
                S(0x17C) = dir;
                func_002A7470(P(0x8C), dir, 3, 3);
            }
        }
        if (hit.f[2] > 0.0f) {
            hit.f[2] = OF(0x18) + 0.05f;
            func_L04_0040C0C0(&hit, bike + 0xD0, 4, 0);
        }
        break;
    }
    case 2: {
        FastVecAdd(m[0].f, (float *)(object + 0x10), (float *)(bike + 0xD0));
        *(s16 *)(object + 0x96) = 0;
        object[0x20] = 3;
        I(0x244) = 0;
        if (I(0x1C0) > 0) func_L04_00400D48(object, bike, 1);
        *(u16 *)(object + 0x34) &= 0xEFFF;
        *(int *)(object + 0x98) = 0;
        FastVecScale(v60.f, v60.f, func_002A7878(0.7f, 1.0f));
        func_002AF000(m[1].f, 0.0833333358f, func_002A7940(), func_002A7878(0.785398245f, 1.57079649f));
        add_vectors(m[2].f, m[1].f, v60.f);
        func_L04_00407078(object, 0xB3D, &m[0], object + 0xF0, 0, 0, 0.0f, &m[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        func_002AF000(m[1].f, 0.0833333358f, func_002A7940(), func_002A7878(0.785398245f, 1.57079649f));
        add_vectors(m[2].f, m[1].f, v60.f);
        func_L04_00407078(object, 0xB3E, &m[0], object + 0xF0, 0, 0, 0.0f, &m[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        func_002AF000(m[1].f, 0.0833333358f, func_002A7940(), func_002A7878(0.785398245f, 1.57079649f));
        add_vectors(m[2].f, m[1].f, v60.f);
        func_L04_00407078(object, 0xB3F, &m[0], object + 0xF0, 0, 0, 0.0f, &m[1], D_L04_001A8F20, 0.0f, D_L04_001A8F20);
        func_002AF000(m[1].f, 0.0833333358f, func_002A7940(), func_002A7878(0.785398245f, 1.57079649f));
        add_vectors(m[2].f, m[1].f, v60.f);
        func_L04_00407078(object, 0xB40, &m[0], object + 0xF0, 0, 0, 0.0f, &m[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        func_002AF000(m[1].f, 0.0833333358f, func_002A7940(), func_002A7878(0.785398245f, 1.57079649f));
        add_vectors(m[2].f, m[1].f, v60.f);
        func_L04_00407078(object, 0xB40, &m[0], object + 0xF0, 0, 0, 0.0f, &m[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xFBFF;
        SpawnExplosion(&m[0], 0, 4, 4, 4, 8, 4, 0, 0.42f, 20.0f, 1, 0, 0, 0);
        if (P(0x8C) != 0) *(u16 *)(P(0x8C) + 0x34) |= 0x41;
        break;
    }
    }
}
