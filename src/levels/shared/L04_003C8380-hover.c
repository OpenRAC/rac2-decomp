#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
extern char ref_L04_00400EE0_00[];
extern int g_current_map_index __attribute__((sda));
extern int g_race_time_ticks __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern float D_L04_001BFB00[];
extern char D_L04_001A8F20[] __attribute__((sda));
extern float coll_probe_ground_height_below(char *, int, float);
extern int GetCollHitMaterial(void);
extern void set_identity_matrix(float *);
extern void matrix_from_basis_rows(void *dst, void *src);
extern void FastVecSub(float *out, float *a, float *b);
extern void transform_vector(float *out, float *a, float *m);
extern float math_fabs(float);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void FastVecScale(float *out, float *in, float scale);
extern void FastVecAdd(float *out, float *a, float *b);
extern void add_vectors(float *out, float *a, float *b);
extern float FastVecDot(void *, void *);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);
extern void matrix_mul_vec3(float *out, float *in, void *m);
extern float FastVecLength(float *);
extern float math_approach_with_velocity(float *position, float target, float *velocity,
                           float acceleration, float damping, float limit, int direction);
extern void hoverbike_select_route_point(u8 *, u8 *, int);
extern float ApproachValue(float *value, float target, float step);
extern void part_spawn_impact_smoke_and_sparks(Vec *, int, int, float, float);
extern float IntToFloat(int);
extern int vec_apply_scaled_value(u8 *, float);
extern float math_lerp_float(float, float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_clamp_length(float *p, float threshold);
extern void moby_update_eased_node(void *a0, void *a1, int a2, float f12, float f13);
extern int math_fast_float_d(void *);
extern void part_l04_spawn_burst(Vec *, void *, int, int);
extern void vec_scale_to_length(float *, float *, float);
extern void mat_aim_with_spring(void *a0, void *a1, void *a2, void *a3, float f1, float f2, float f3);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern int ResolveVehicleMovementCollisions(u8 *, u8 *, u8 *, u8 *, Vec *, Vec *, Vec *, u8 *, int, int *,
                             float, float, float, float, float);
extern int racer_is_in_jump_window(int a0, int a1, float f12);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern u8 *debris_spawn(u8 *, int, Vec *, u8 *, int, int, float, Vec *, char *, float, char *);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
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
/* Moves a racing hoverbike each frame: it follows the track or steers freely, hovers above the ground, and crashes into debris and an explosion when hit. */
void hoverbike_update_racing_movement(u8 *object, u8 *bike)
{
    Vec hit, v30, v40, start, v60, delta;
    Vec matrix[4];
    Vec target_pos, local_offset, local_delta;
    int flag;
    float ground, height, limit, speed, rate, side, blend;
    u8 *rider;
    int crash_result;

    hit.q = 0;
    hit.f[3] = -1.0f;
    start.q = *(Quad *)(object + 0x10);
    ground = coll_probe_ground_height_below((char *)(object + 0x10), 0, 0.5f);
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
        set_identity_matrix(matrix[0].f);
        matrix_from_basis_rows(matrix, P(0x164) + 0xC0);
        FastVecSub(delta.f, (float *)(object + 0x10), (float *)(P(0x164) + 0x10));
        transform_vector(local_delta.f, delta.f, matrix[0].f);
        side = math_fabs(local_delta.f[0]);
        if (I(0x1F0) == 0 && F(0x1E4) >= 1.0f && side < 1.5f && math_fabs(local_delta.f[1]) >= 1.0f) {
            I(0x1F0) = 1;
            F(0x1E8) = 0.05f;
            F(0x1F8) = 2.0f;
            if (local_delta.f[1] > 0.0f) F(0x1F4) = 0.3490659f;
            else F(0x1F4) = -0.3490659f;
        }
        F(0x2B0) = 0.0f;
        if (I(0x1F0) == 1 && *(s16 *)(rider + 0x274) == 0) {
            F(0x2B0) = fast_subtract_rotations(mat_fast_helper_a(delta.f[0], delta.f[1]), OF(0xF8)) * 0.9f;
            if (F(0x2B0) > 1.5707964f) F(0x2B0) = 1.5707964f;
            if (F(0x2B0) < -1.5707964f) F(0x2B0) = -1.5707964f;
            if (I(0x178) > 0) F(0x2B0) = F(0x2B0) * 0.45f;
            math_step_value_toward_target((float *)(bike + 0x1E4), (float *)(bike + 0x1EC), F(0x1E8), 0.0025f, 0.0025f, 0.200000018f);
            if (F(0x1E8) == 1.0f && F(0x1E4) >= 1.0f) {
                F(0x1E8) = 1.0f;
                I(0x1F0) = 0;
            }
        } else {
            math_step_value_toward_target((float *)(bike + 0x1E4), (float *)(bike + 0x1EC), F(0x1E8), 0.000277777785f, 0.000277777785f, 0.13333334f);
        }
        if (local_delta.f[1] > 0.0f)
            FastVecScale(delta.f, (float *)(P(0x164) + 0xD0), F(0x1E4));
        else
            FastVecScale(delta.f, (float *)(P(0x164) + 0xD0), -F(0x1E4));
        FastVecAdd(target_pos.f, (float *)(P(0x164) + 0x10), delta.f);
        FastVecScale(delta.f, (float *)(rider + 0x290), 5.0f);
        FastVecAdd(target_pos.f, target_pos.f, delta.f);
        set_identity_matrix(matrix[0].f);
        matrix_from_basis_rows(matrix, object + 0xC0);
        FastVecSub(delta.f, target_pos.f, (float *)(object + 0x10));
        transform_vector(local_offset.f, delta.f, matrix[0].f);
        rate = math_fabs(local_delta.f[0]) * 0.8f;
        if (rate > 1.0f) rate = 1.0f;
        if (rate < 0.0f) rate = 0.0f;
        RF(0x63C) = (1.0f - rate) * 1.75f;
        if (RF(0x63C) < 1.0f) RF(0x63C) = 1.0f;
        rate = (0.1f - local_delta.f[0]) * 12.5f;
        F(0x134) = RF(0x30C) + RF(0x27C);
        if (rate > 0.0f) {
            if (rate < 1.0f) rate = 0.0f;
            else if (rate > 4.0f) rate = 4.0f;
        } else if (rate > -1.0f) {
            rate = 0.0f;
        } else if (rate < -4.0f) {
            rate = -4.0f;
        }
        blend = F(0x134) * (rate * 0.03f);
        F(0x134) = F(0x134) + blend;
        if (math_fabs(F(0x1D4)) > 1.04719758f || *(int *)(rider + 0x3A4) > 0 ||
            FastVecDot(&local_delta, &local_delta) > 121.0f || F(0x134) < 0.100000009f) {
            I(0x1C0) = 0;
            I(0x1F0) = 5;
        }
        if (F(0x2D0) > 0.0f) {
            cap = F(0x2D4) * 0.0166666675f;
            if (cap < F(0x134)) F(0x134) = cap;
        }
        math_spring_float_to_goal((float *)(bike + 0x138), (float *)(bike + 0x158), F(0x134), 0.027f, 0.2f, 0.00555555569f);
        if (local_offset.f[0] < 5.0f) local_offset.f[0] = 5.0f;
        matrix_mul_vec3(delta.f, local_offset.f, object + 0xC0);
        FastVecScale((float *)(bike + 0xD0), delta.f, F(0x138) / FastVecLength(delta.f));
        F(0xD8) = F(0xE8);
        math_approach_with_velocity((float *)(object + 0xF8), *(float *)(P(0x164) + 0xF8), (float *)(bike + 0x130), 0.03f, 0.3f, 0.0727220625f, 0);
        if (--I(0x1C0) <= 0) hoverbike_select_route_point(object, bike, 0);
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
            matrix[0].q = *(Quad *)(object + 0x10);
            matrix[0].f[2] = z;
            part_spawn_impact_smoke_and_sparks(&matrix[0], 2, 0, z, F(0x138) + F(0x13C));
        }
        if (idle) {
            if (g_race_time_ticks < 240 && I(0x9C) >= 11)
                rate = 0.0162000004f;
            else
                rate = (float)(I(0x1A8) / 10) * 0.05f + 0.027f;
            math_spring_float_to_goal((float *)(bike + 0x138), (float *)(bike + 0x158), F(0x134),
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
            heading = mat_fast_helper_a(F(0xF0) - OF(0x10), F(0xF4) - OF(0x14));
            blend = F(0x138) * 2.70880365f;
            if (blend > side) blend = side;
            if (vec_apply_scaled_value(object, IntToFloat(*(s16 *)(object + 0x32))) < 0) blend = limit;
            limit = math_lerp_float(0.0727220625f, 0.034906592f, blend);
            factor = (side - blend) + side;
            if (factor > 1.9f) factor = 1.9f;
            if (I(0x244) != 0) {
                limit = limit * 1.25f;
                factor = 2.75f;
            }
            damping = factor * damping;
            if (limit < 2.9088826e-05f) limit = 2.9088826e-05f;
            math_approach_with_velocity((float *)(object + 0xF8), heading, (float *)(bike + 0x130), damping, 0.3f, limit, 0);
        }
        if (*(u8 **)(rider + 0x730) == object) speed = RF(0x30C) + RF(0x27C);
        if (F(0x2D0) > 0.0f) {
            float cap = F(0x2D4) * 0.0166666675f;
            if (cap < speed) speed = cap;
        }
        blend = OF(0xF8);
        delta.f[0] = math_fast_sin_or_cos_a(blend) * speed;
        delta.f[1] = math_fast_sin_or_cos_b(blend) * speed;
        delta.i[2] = 0;
        if (I(0x244) != 0) {
            if (I(0x178) != 0 && I(0x248) != 0) {
                FastVecScale(delta.f, (float *)(bike + 0x100), (float)I(0x178) * 0.025f);
                FastVecSub((float *)(bike + 0xD0), (float *)(bike + 0xD0), delta.f);
                I(0x248) = 0;
            }
            FastVecScale(delta.f, delta.f, 0.025f);
            FastVecAdd((float *)(bike + 0xD0), (float *)(bike + 0xD0), delta.f);
            vec_clamp_length((float *)(bike + 0xD0), speed);
        } else {
            *(Quad *)(bike + 0xD0) = delta.q;
        }
    }
    if (D_001A7A40[7] != 0) F(0x2C0) = 2.5f;
    else F(0x2C0) = 1.0f;
    if (P(0x8C) != 0) moby_update_eased_node(P(0x8C), bike + 0x250, 0, 0.08f, 0.5f);
    if (!math_fast_float_d(bike + 0x178)) {
        FastVecScale(delta.f, (float *)(bike + 0x100), (float)I(0x178) * 0.025f);
        FastVecAdd((float *)(bike + 0xD0), (float *)(bike + 0xD0), delta.f);
        I(0x248) = 1;
    }
    if (I(0x148) >= 8) {
        F(0xD8) = F(0xE8) + 0.00333333341f;
    } else if (height > 0.3f) {
        float extra;
        if (((int)ref_L04_00400EE0_00 == 0x28 || g_current_map_index == 4) && bike[0xA5] != 0 && I(0x120) == -1 && I(0x124) >= 476) {
            blend = F(0x13C) * 9.99999905f;
            if (blend > 1.0f) blend = 1.0f;
            else if (blend < 0.0f) blend = 0.0f;
            extra = blend * 3.0f + 1.5f;
        } else {
            extra = 0.0f;
        }
        blend = ((height - 0.2f) + 0.1f) * 3.33333325f;
        if (blend > 1.0f) blend = 1.0f;
        if (blend < 0.0f) blend = 0.0f;
        F(0xD8) = F(0xE8) - (extra + 12.0f) * blend * 0.000277777785f;
    } else {
        blend = ((0.2f - height) + 0.1f) * 5.0f;
        if (blend > 1.0f) blend = 1.0f;
        if (blend < 0.0f) blend = 0.0f;
        blend *= 0.23f;
        F(0xD8) = F(0xE8) + blend * 0.00333333341f;
    }
    if (height > 0.44f) {
        bike[0xA5] = 1;
        *(u16 *)(bike + 0xA6) = *(u16 *)(bike + 0xA6) + 1;
    } else {
        if (bike[0xA5] != 0 && S(0xA6) >= 13 && F(0x154) < 0.0f) {
            if (GetCollHitMaterial() == 0) {
                if (S(0xA6) >= 46) {
                    float z = ground - 0.25f;
                    matrix[0].q = *(Quad *)(object + 0x10);
                    matrix[0].f[2] = z;
                    part_spawn_impact_smoke_and_sparks(&matrix[0], 10, 1, z, F(0x138) + F(0x13C));
                }
            } else {
                if (S(0xA6) >= 46) {
                    FastVecScale(hit.f, (float *)(bike + 0xE0), 0.5f);
                    add_vectors(matrix[0].f, hit.f, (float *)(object + 0x10));
                    v30.q = *(Quad *)(bike + 0xE0);
                    hit.f[2] = OF(0x18);
                    v30.f[2] = 0.0166666675f;
                    FastVecScale(v30.f, v30.f, 0.85f);
                    part_l04_spawn_burst(&hit, &v30, 8, 1);
                }
                if (bike[0xA4] == 0 && GetCollHitMaterial() != 5) {
                    float sink;
                    if (F(0x154) > -0.05f) F(0x154) = -0.05f;
                    sink = F(0x154);
                    blend = 1.0f - (sink + 0.35f) * 2.85714293f;
                    if (blend > 1.0f) blend = 1.0f;
                    if (blend < 0.0f) blend = 0.0f;
                    I(0x148) = (int)(blend * 5.0f) + 15;
                    if (blend < 0.5f) blend = 0.5f;
                    bike[0xA4] = 1;
                    F(0x14C) = blend * 0.06f;
                    F(0xE8) = sink * -0.3f;
                }
            }
        }
        bike[0xA5] = 0;
        *(u16 *)(bike + 0xA6) = 0;
    }
    {
        blend = OF(0xF0);
        if (bike[0xA4] != 0) {
            OF(0xF4) = OF(0xF4) + F(0x14C);
            math_fast_float_d(bike + 0x148);
            if (I(0x148) == 0) bike[0xA4] = 0;
        } else if (bike[0xA5] == 0) {
            vec_scale_to_length(v40.f, D_L04_001BFB00, 1.0f);
            mat_aim_with_spring(object + 0xC0, object + 0xF0, bike + 0x12C, &v40, 0.03f, 0.3f, 0.0f);
        } else {
            vec_build_spherical_offset(v40.f, 1.0f, FastAddRotations(OF(0xF8), 3.14159274f), 0.87266469f);
            mat_aim_with_spring(object + 0xC0, object + 0xF0, bike + 0x12C, &v40, 0.03f, 0.3f, 0.0f);
        }
        OF(0xF0) = blend;
    }
    {
        float wobble;
        F(0x150) = FastAddRotations(F(0x150), 0.15f);
        wobble = math_fast_sin_or_cos_a(F(0x150)) * 0.004f;
        OF(0xF4) = OF(0xF4) + math_fast_sin_or_cos_b(F(0x150)) * 0.004f;
        OF(0xF0) = OF(0xF0) + wobble;
    }
    *(Quad *)(bike + 0xE0) = *(Quad *)(bike + 0xD0);
    F(0x154) = F(0xE8);
    crash_result = ResolveVehicleMovementCollisions(object, object + 0x10, bike + 0xD0, bike + 0xE0, &hit, &v60, &v40, bike + 0x144, 0, &flag,
                               speed, limit, F(0x134), F(0x94), F(0x90));
    if (crash_result != 0 && I(0x244) != 0) FastVecScale((float *)(bike + 0xD0), (float *)(bike + 0xD0), 0.85f);
    if (flag != 0)
        I(0x1AC) = I(0x1AC) + 1;
    else
        I(0x1AC) = 0;
    if (OF(0x18) < F(0x98) || racer_is_in_jump_window(I(0x120), I(0x124), OF(0x18))) crash_result = 2;
    if (part_find_owned_effect_slot(object, -1, 0)) {
        crash_result = 2;
        v60.q = *(Quad *)(bike + 0xD0);
    }
    object[0xA8] = 0xFF;
    if (I(0x1AC) >= 2 && I(0x1C0) > 0 && I(0x178) > 0 && I(0x1BC) >= 4) crash_result = 2;
    if ((u32)(P(0x164)[0xBC] - 5) < 2) {
        FastVecSub(delta.f, (float *)(object + 0x10), start.f);
        delta.i[2] = 0;
        if (FastVecDot(&delta, &delta) < 0.01f) {
            if (++I(0x24C) >= 26) crash_result = 2;
        } else {
            I(0x24C) = 0;
        }
    }
    switch (crash_result) {
    case 1: {
        float a = FastAddRotations(mat_fast_helper_a(hit.f[0] - OF(0x10), hit.f[1] - OF(0x14)), 3.14159274f);
        math_approach_with_velocity((float *)(object + 0xF8), a, (float *)(bike + 0x130), 0.011f, 0.3f, 6.0f, 0);
        if (P(0x8C) != 0) {
            int dir;
            a = fast_subtract_rotations(OF(0xF8), mat_fast_helper_a(hit.f[0] - OF(0x10), hit.f[1] - OF(0x14)));
            if (a > 0.52359885f && a < 2.61799407f) dir = 2;
            else if (a < -0.52359885f && a > -2.61799407f) dir = 1;
            else if (math_fabs(a) < 0.52359885f) dir = 4;
            else dir = 3;
            if (S(0x17E) != 0 && S(0x17C) == dir) {
                S(0x17E) = 30;
            } else {
                S(0x17E) = 30;
                S(0x17C) = dir;
                anim_start_blended(P(0x8C), dir, 3, 3);
            }
        }
        if (hit.f[2] > 0.0f) {
            hit.f[2] = OF(0x18) + 0.05f;
            part_l04_spawn_burst(&hit, bike + 0xD0, 4, 0);
        }
        break;
    }
    case 2: {
        FastVecAdd(matrix[0].f, (float *)(object + 0x10), (float *)(bike + 0xD0));
        *(s16 *)(object + 0x96) = 0;
        object[0x20] = 3;
        I(0x244) = 0;
        if (I(0x1C0) > 0) hoverbike_select_route_point(object, bike, 1);
        *(u16 *)(object + 0x34) &= 0xEFFF;
        *(int *)(object + 0x98) = 0;
        FastVecScale(v60.f, v60.f, math_random_float_range(0.7f, 1.0f));
        vec_build_spherical_offset(matrix[1].f, 0.0833333358f, math_random_angle(), math_random_float_range(0.785398245f, 1.57079649f));
        add_vectors(matrix[2].f, matrix[1].f, v60.f);
        debris_spawn(object, 0xB3D, &matrix[0], object + 0xF0, 0, 0, 0.0f, &matrix[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        vec_build_spherical_offset(matrix[1].f, 0.0833333358f, math_random_angle(), math_random_float_range(0.785398245f, 1.57079649f));
        add_vectors(matrix[2].f, matrix[1].f, v60.f);
        debris_spawn(object, 0xB3E, &matrix[0], object + 0xF0, 0, 0, 0.0f, &matrix[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        vec_build_spherical_offset(matrix[1].f, 0.0833333358f, math_random_angle(), math_random_float_range(0.785398245f, 1.57079649f));
        add_vectors(matrix[2].f, matrix[1].f, v60.f);
        debris_spawn(object, 0xB3F, &matrix[0], object + 0xF0, 0, 0, 0.0f, &matrix[1], D_L04_001A8F20, 0.0f, D_L04_001A8F20);
        vec_build_spherical_offset(matrix[1].f, 0.0833333358f, math_random_angle(), math_random_float_range(0.785398245f, 1.57079649f));
        add_vectors(matrix[2].f, matrix[1].f, v60.f);
        debris_spawn(object, 0xB40, &matrix[0], object + 0xF0, 0, 0, 0.0f, &matrix[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        vec_build_spherical_offset(matrix[1].f, 0.0833333358f, math_random_angle(), math_random_float_range(0.785398245f, 1.57079649f));
        add_vectors(matrix[2].f, matrix[1].f, v60.f);
        debris_spawn(object, 0xB40, &matrix[0], object + 0xF0, 0, 0, 0.0f, &matrix[1], D_L04_001A8F20, 0.1f, D_L04_001A8F20);
        *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xFBFF;
        SpawnExplosion(&matrix[0], 0, 4, 4, 4, 8, 4, 0, 0.42f, 20.0f, 1, 0, 0, 0);
        if (P(0x8C) != 0) *(u16 *)(P(0x8C) + 0x34) |= 0x41;
        break;
    }
    }
}
