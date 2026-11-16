#include "names.h"
/* func_L04_00414698: hover board physics for the rider (Barlow, Joba). A unit of its own for
 * -G8, -g, -frac2-hazard-labels and -frac2-frame-pointer-liveness (config/cflags.txt). The hazard
 * option puts the 00414AD8 bc1f target on the nop at 00414BF8, as retail. Without the liveness
 * option flow keeps $fp live after reload and reorg annuls the slot of the branch at 004147A8
 * (bnel where retail has bne, same slot `addiu $fp,$s7,0x10`; docs/build/compiler-notes.md).
 * D_L04_001B08F0 and D_001A7CC0 are sda ($gp); D_00189FC0 and D_00138320 are NOT_SDA (absolute);
 * D_L04_001B24DC is plain (unsplit -G8 macro load); D_L04_001A8F20 is MACRO_ADDR (unsplit la).
 * Source notes:
 *  - x is one float reused for the sink factor, the saved OF(0xF0) and the case-2 pitch (all retail
 *    $f21); yaw stays a separate block-local.
 *  - object + 0xC0, object + 0x10 and st + 0x2A0 are written as expressions at every use: gcse's PRE
 *    makes retail's reaching-register copies, and a local pseudo would block $s5 for st and object.
 *  - SPAWN's `r` is block-scoped, one pseudo per spawn, so local-alloc takes each (single-death rule)
 *    and the case-2 constants land in retail's $f20-$f24.
 *  - Retail keeps a dead pitch comparison: `if (x > 1.2217306f) height = 0.0f;`. flow1 deletes the
 *    dead store and jump2 the empty branch; the c.lt.s stays.
 *  - The block-scope `extern int D_001A7CC0;` in one arm is a second declaration without the sda
 *    flag, which gives retail's absolute read there.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; int i[4]; } Vec;
extern u8 g_sound_state[];
extern u8 g_hero_state[];
extern float g_hoverboard_rotation NOT_SDA;
extern u8 g_hover_config[];
extern u8 g_hero_position[];
extern u8 g_hover_target_buffer[];
extern Quad g_hover_debug_quad;
extern int g_pad_pressed_flags NOT_SDA;
extern int g_hoverboard_debug_flag __attribute__((sda));
extern int g_race_bike_mode __attribute__((sda));
extern u8 *g_moby_l04_pool;
extern float g_hover_direction_vec[];
extern char g_effect_default_params[] MACRO_ADDR;
extern float coll_probe_ground_height_below(char *, int, float);
extern int GetCollHitMaterial(void);
extern int snd_is_voice_playing_for_owner(void *, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void hoverbike_update_route_steering(u8 *, u8 *);
extern void pad_clamp_stick_to_unit_range(void *, void *, float);
extern float FastAddRotations(float, float);
extern float mat_fast_helper_a(float, float);
extern float math_fabs(float);
extern float ApproachValue(float *, float, float);
extern void FastVecScale(void *, void *, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecAdd(void *, void *, void *);
extern void add_vectors(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void part_spawn_impact_smoke_and_sparks(Vec *, int, int, float, float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern int FloatToInt(float);
extern void *part_spawn_sparkle(void *, void *, u32, float);
extern void * part_spawn_drifting(void *, int, int, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);
extern float math_lerp_float(float, float, float);
extern float math_approach_with_velocity(float *, float, float *, float, float, float, int);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void vec_clamp_length(float *, float);
extern void vec_scale_to_length(float *, float *, float);
extern int math_fast_float_d(void *);
extern void bike_compute_target_height(u8 *, u8 *, float, float, float, float, float);
extern void part_spawn_spark_and_smoke_burst(Vec *, Vec *, int, u8 *, float);
extern void part_l04_spawn_burst(Vec *, Vec *, int, int);
extern void mat_aim_with_spring(void *, void *, void *, void *, float, float, float);
extern void math_step_angle_offset(void *, void *, float, float);
extern int ResolveVehicleMovementCollisions(u8 *, u8 *, u8 *, u8 *, Vec *, Vec *, u8 *, int *, int, int *,
                             float, float, float, float, float);
extern void anim_start_blended(void *, int, int, int);
extern void racer_release_sound_handles(u8 *, u8 *);
extern int queue_copy_record_by_index(int);
extern void * SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void level_release_slot_list(void *);
extern float math_random_angle(void);
extern void * debris_spawn(u8 *, int, Vec *, u8 *, int, int, Vec *, char *, char *, float, float);
extern int CollLine(void *, void *, int, void *, int);
extern float vec_length_xy(void *);
extern float fast_subtract_rotations(float, float);
extern float FastDiffRots(float, float);
extern float FastVecLength(void *);
extern void Hero_ProbeGround(Quad);
typedef struct { u8 pad000[0x1A0]; float heading; u8 pad1A4[0x24B8 - 0x1A4]; float turnScale; } L04_HoverHero;
typedef struct { u8 pad000[0x158]; float f158; u8 pad15C[4]; float f160; u8 pad164[4]; int f168; int f16C;
                 u8 pad170[0x10]; float f180; u8 pad184[4]; int f188; } L04_HoverCfg;
typedef struct { u8 pad00[0x40]; float v[4]; } L04_HoverTarget;
#define HERO ((L04_HoverHero *)D_00189E20)
#define CFG ((L04_HoverCfg *)D_001B9540)
#define I(o) (*(s32 *)(st + (o)))
#define F(o) (*(float *)(st + (o)))
#define S(o) (*(s16 *)(st + (o)))
#define U16(o) (*(u16 *)(st + (o)))
#define OF(o) (*(float *)(object + (o)))
#define HEAD (HERO->heading)
#define SND_STOP(field) { int h = I(field); if (h != -1) { u8 *e = D_00188660 + h * 0x70; if (*(u8 **)(e + 0x88) == object && e[0x74] != 0) func_002E59F8(h); } I(field) = -1; }

#define SPAWN(id, a, b) { float r = func_002A7940(); func_002AF000(dir->f, 0.083333336f, r, func_002A7878(0.78539824f, 1.5707965f)); func_00282CD8(&v80, dir, &v50); func_L04_00407078(object, id, (Vec *)(object + 0x10), object + 0xF0, 0, 0, dir, tag, tag, a, b); }

/* Hover board physics for the rider: steering, speed, landing and crash handling. */
void hoverboard_update_rider_physics(u8 *object, u8 *st)
{
    Vec v20, v30, v40, v50, start, v70, v80, v90, vA0, vB0, vC0, vD0, vE0, vF0;
    int flag, flag2, idle, dbg;
    float ground, height, limit, speed, grip, factor, damping, x;

    flag = 0;
    start.q = *(Quad *)(object + 0x10);
    ground = coll_probe_ground_height_below((char *)(object + 0x10), 0, 0.5f);
    height = OF(0x18) - ground;
    if ((GetCollHitMaterial() != 0 || S(0x274) != 0) && snd_is_voice_playing_for_owner(object, I(0x3BC)) != 0) {
        SND_STOP(0x3BC)
    }
    if (object[0x20] == 3) hoverbike_update_route_steering(object, st);
    if (object[0xBC] == 5) {
        if (object[0x20] != 3) {
            pad_clamp_stick_to_unit_range(&v20, st + 0x2C0, 0.12f);
            g_hoverboard_rotation = FastAddRotations(CFG->f158,
                                       mat_fast_helper_a(math_fabs(v20.f[1]), v20.f[0]));
        } else {
            float t = mat_fast_helper_a(F(0x6A0) - OF(0x10), F(0x6A4) - OF(0x14));
            HEAD = t;
            if (I(0x750) >= 11) HEAD = FastAddRotations(t, (float)I(0x750) * 0.01f);
        }
        idle = 1;
        if (st[0x348] != 0 && I(0x4D8) == 0) {
            idle = 0;
            ApproachValue((float *)(st + 0x30C), 0.050000004f, 0.0030555557f);
        } else {
            if (GetCollHitMaterial() == 0 && S(0x274) == 0) {
                u8 *s0;
                float yaw, z;
                if (F(0x30C) > 0.19166668f) {
                    idle = 0;
                    ApproachValue((float *)(st + 0x30C), 0.19166668f, 0.0031944446f);
                }
                I(0x278) = 0;
                FastVecScale(&v70, (object + 0xC0), 0.95f);
                s0 = object + 0xD0;
                FastVecScale(&v80, s0, 0.45f);
                FastVecScale(&v90, s0, -0.45f);
                moby_transform_joint_to_world(object, 0, &vA0);
                FastVecAdd(&vA0, &vA0, &v70);
                FastVecAdd(&vA0, &vA0, &v80);
                z = ground - 0.25f;
                vA0.f[2] = ground;
                part_spawn_impact_smoke_and_sparks(&vA0, 1, 0, z, F(0x30C));
                moby_transform_joint_to_world(object, 1, &vB0);
                FastVecAdd(&vB0, &vB0, &v70);
                FastVecAdd(&vB0, &vB0, &v90);
                vB0.f[2] = ground;
                part_spawn_impact_smoke_and_sparks(&vB0, 1, 0, z, F(0x30C));
                qcopy(&vD0, &vB0);
                qcopy(&vE0, &vA0);
                yaw = OF(0xF8);
                vC0.f[0] = math_fast_sin_or_cos_a(yaw) * math_random_float_range(0.031666666f, 0.06666667f);
                vC0.f[1] = math_fast_sin_or_cos_b(yaw) * math_random_float_range(0.031666666f, 0.06666667f);
                vC0.f[2] = F(0x30C) * 0.5f;
                if (math_random_int_below(FloatToInt(1.0f / F(0x30C)) - 1) == 0) {
                    if (F(0x30C) >= 0.1f) {
                        part_spawn_sparkle(&vD0, &vC0, 0x40, 0.6f);
                        FastVecScale(&v70, (object + 0xC0), -0.4f);
                        FastVecAdd(&vD0, &vD0, &v70);
                        part_spawn_sparkle(&vD0, &vC0, 0x40, 0.7f);
                        FastVecAdd(&vD0, &vD0, &v70);
                        part_spawn_sparkle(&vD0, &vC0, 0x40, 0.8f);
                        part_spawn_sparkle(&vE0, &vC0, 0x40, 0.6f);
                        FastVecScale(&v70, (object + 0xC0), -0.4f);
                        FastVecAdd(&vE0, &vE0, &v70);
                        part_spawn_sparkle(&vE0, &vC0, 0x40, 0.7f);
                        FastVecAdd(&vE0, &vE0, &v70);
                        part_spawn_sparkle(&vE0, &vC0, 0x40, 0.8f);
                    }
                }
                if (F(0x30C) <= 0.1f && math_random_int_below(2) == 0) {
                    FastVecScale(&v70, (object + 0xC0), 0.5f);
                    FastVecAdd(&vF0, (object + 0x10), &v70);
                    vF0.f[2] = ground;
                    part_spawn_drifting(&vF0, 0, 0x40645050, 0.8f, 14700.0f);
                }
                if (snd_is_voice_playing_for_owner(object, I(0x3BC)) == 0 && object[0x20] != 3) {
                    I(0x3BC) = PlayMobySound(0x10, 4, object);
                    if (height < 0.5f) PlayMobySound(6, 0, object);
                }
            }
        }
        if (GetCollHitMaterial() == 7 && S(0x274) == 0) {
            if (g_race_bike_mode == 0) PlayMobySound(0x11, 0, object);
            if (snd_is_voice_playing_for_owner(object, I(0x748)) == 0) I(0x748) = PlayMobySound(0x12, 4, object);
            if (snd_is_voice_playing_for_owner(object, I(0x74C)) == 0) I(0x74C) = PlayMobySound(0x13, 4, object);
            g_race_bike_mode = 1;
        } else {
            SND_STOP(0x748)
            SND_STOP(0x74C)
            g_race_bike_mode = 0;
        }
        if (idle) {
            if ((g_pad_pressed_flags & 0x40) || object[0x20] == 3) {
                math_spring_float_to_goal((float *)(st + 0x30C), (float *)(st + 0x288), 0.33333334f,
                              g_race_bike_mode != 0 ? 0.011f : 0.022f, 0.5f,
                              g_race_bike_mode != 0 ? 0.013888889f : 0.027777778f);
            } else {
                ApproachValue((float *)(st + 0x30C), 0.050000004f, 0.0027777778f);
            }
        }
        speed = F(0x30C) + F(0x27C);
    } else {
        speed = 0.0f;
    }
    grip = F(0x30C) * 3.0f;
    damping = 0.016f;
    if (grip > 1.0f) grip = 1.0f;
    limit = math_lerp_float(0.05817765f, I(0x338) != 0 ? 0.01658063f : 0.021816619f, grip);
    factor = (1.0f - grip) + 1.0f;
    if (factor > 1.9f) factor = 1.9f;
    if (g_race_bike_mode != 0) {
        factor = 2.75f;
        limit = limit * 1.25f;
    }
    if (I(0x4C4) != 0) {
        factor = 4.0f;
        limit = limit * F(0x63C);
    }
    damping = factor * damping;
    if (object[0xBC] == 5) {
        if (object[0x20] != 3) limit = limit * HERO->turnScale;
        if (limit < 0.000029088826f) limit = 0.000029088826f;
        math_approach_with_velocity((float *)(object + 0xF8), HEAD, (float *)(st + 0x308), damping, 0.3f, limit, 0);
    }
    if (g_race_bike_mode != 0) {
        if (I(0x64C) != 0 && I(0x71C) != 0) {
            FastVecScale(&v20, st + 0x2F0, (float)I(0x64C) * 0.025f);
            FastVecSub((st + 0x290), (st + 0x290), &v20);
            I(0x71C) = 0;
        }
        vec_build_spherical_offset(v20.f, speed, OF(0xF8), 0.0f);
        FastVecScale(&v20, &v20, 0.025f);
        FastVecAdd((st + 0x290), (st + 0x290), &v20);
        vec_clamp_length((float *)(st + 0x290), speed);
    } else {
        vec_build_spherical_offset((float *)(st + 0x290), speed, OF(0xF8), 0.0f);
        vec_clamp_length((float *)(st + 0x290), speed);
        qcopy(&v20, object + 0xD0);
        vec_scale_to_length(v20.f, v20.f, F(0x30C) * (F(0x308) * -1.75f));
        FastVecAdd((st + 0x290), (st + 0x290), &v20);
    }
    if (math_fast_float_d(st + 0x64C) == 0) {
        extern int g_hoverboard_debug_flag;
        FastVecScale(&v20, st + 0x2F0, (float)I(0x64C) * 0.025f);
        FastVecAdd((st + 0x290), (st + 0x290), &v20);
        I(0x71C) = 1;
        dbg = g_hoverboard_debug_flag;
    } else {
        dbg = g_hoverboard_debug_flag;
    }
    if (dbg != 0) qcopy(&g_hover_debug_quad, &v20);
    bike_compute_target_height(object, st, height, 0.2f, 0.23f, 12.0f, 0.1f);
    if (height > 0.44f) {
        S(0x274) = 1;
        U16(0x276) = U16(0x276) + 1;
    } else {
        if (S(0x274) != 0 && S(0x276) >= 13 && F(0x358) < 0.0f && GetCollHitMaterial() != 0) {
            if (S(0x276) >= 46) {
                FastVecScale(&v30, (st + 0x2A0), 0.5f);
                add_vectors(&v70, &v30, (object + 0x10));
                v40.q = *(Quad *)(st + 0x2A0);
                v30.f[2] = OF(0x18);
                v40.f[2] = 0.016666668f;
                FastVecScale(&v40, &v40, 0.85f);
                part_spawn_spark_and_smoke_burst(&v30, &v40, 0, object, F(0x30C));
                part_l04_spawn_burst(&v30, &v40, 8, 1);
                if (object[0x20] != 3) {
                    SND_STOP(0x328)
                    I(0x328) = PlayMobySound(4, 4, object);
                    I(0x32C) = 4;
                    I(0x324) = 15;
                }
            }
            if (st[0x349] == 0 && GetCollHitMaterial() != 5) {
                float sink;
                if (F(0x358) > -0.05f) F(0x358) = -0.05f;
                sink = F(0x358);
                x = 1.0f - (sink + 0.35f) * 2.857143f;
                if (x > 1.0f) x = 1.0f;
                if (x < 0.0f) x = 0.0f;
                I(0x34C) = (int)(x * 5.0f) + 15;
                if (x < 0.5f) x = 0.5f;
                st[0x349] = 1;
                F(0x354) = x * 0.06f;
                F(0x2A8) = sink * -0.3f;
            }
        }
        S(0x274) = 0;
        U16(0x276) = 0;
    }
    x = OF(0xF0);
    if (st[0x349] != 0) {
        OF(0xF4) = OF(0xF4) + F(0x354);
        math_fast_float_d(st + 0x34C);
        if (I(0x34C) == 0) st[0x349] = 0;
    } else if (S(0x274) == 0) {
        vec_scale_to_length((float *)(st + 0x2B0), g_hover_direction_vec, 1.0f);
        mat_aim_with_spring(object + 0xC0, object + 0xF0, st + 0x304, (st + 0x2B0), 0.03f, 0.3f, 0.0f);
    } else {
        vec_build_spherical_offset((float *)(st + 0x2B0), 1.0f, FastAddRotations(OF(0xF8), 3.1415927f), 0.99483776f);
        mat_aim_with_spring(object + 0xC0, object + 0xF0, st + 0x304, (st + 0x2B0), 0.03f, 0.3f, 0.0f);
    }
    OF(0xF0) = x;
    math_step_angle_offset(object, st, 0.15f, 0.004f);
    *(Quad *)(st + 0x2A0) = *(Quad *)(st + 0x290);
    F(0x358) = F(0x2A8);
    {
    int result = ResolveVehicleMovementCollisions(object, (object + 0x10), (st + 0x290), (st + 0x2A0), &v30, &v50, (st + 0x2B0), &flag, 1, &flag2,
                                   F(0x30C) + F(0x27C), F(0x280), 0.16666667f, F(0x24), F(0x20));
    if (result != 0) {
        if (g_race_bike_mode != 0) FastVecScale((st + 0x290), (st + 0x290), 0.85f);
        if (flag2 != 0)
            I(0x70C) = I(0x70C) + 1;
        else
            I(0x70C) = 0;
        switch (result) {
        case 1:
            if (I(0x1DC) != -1) {
                u8 *target = g_moby_l04_pool + (I(0x1DC) << 8);
                float a = fast_subtract_rotations(OF(0xF8), mat_fast_helper_a(v30.f[0] - OF(0x10), v30.f[1] - OF(0x14)));
                int dir;
                if (a > 0.52359885f && a < 2.617994f) {
                    dir = 3;
                } else {
                    dir = 5;
                    if (a < -0.52359885f && a > -2.617994f) dir = 4;
                }
                if (I(0x36C) != 0 && S(0x34A) == dir) {
                    I(0x36C) = 30;
                } else {
                    I(0x36C) = 30;
                    S(0x34A) = dir;
                    anim_start_blended(target, dir, 3, 3);
                }
            }
            switch (flag) {
            case 0:
                if (object[0x20] != 3) {
                    if (I(0x32C) != 4) {
                        SND_STOP(0x328)
                        I(0x328) = PlayMobySound(4, 4, object);
                        I(0x32C) = 4;
                        I(0x324) = 15;
                    } else {
                        I(0x324) = 15;
                    }
                }
                break;
            case 1:
                if (object[0x20] != 3) {
                    if (I(0x32C) != 5) {
                        SND_STOP(0x328)
                        I(0x328) = PlayMobySound(5, 4, object);
                        I(0x32C) = 5;
                        I(0x324) = 15;
                    } else {
                        I(0x324) = 15;
                    }
                }
                break;
            case 2:
                if (object[0x20] != 3) PlayMobySound(2, 0, object);
                break;
            case 3:
                if (I(0x4D8) == 0) F(0x30C) = F(0x30C) * 0.25f;
                break;
            }
            v30.f[2] = OF(0x18) + 0.05f;
            part_spawn_spark_and_smoke_burst(&v30, (Vec *)(st + 0x290), flag, object, F(0x30C));
            break;
        case 2:
            if (I(0x4D8) == 0) {
                if (object[0x20] != 3) {
                    char *tag;
                    Vec *dir;
                    racer_release_sound_handles(object, st);
                    CFG->f188 = 0x5A;
                    CFG->f168 = 0x3C;
                    CFG->f160 = 0.2f;
                    CFG->f180 = 0.1f;
                    tag = g_effect_default_params;
                    CFG->f16C = 0;
                    queue_copy_record_by_index(0x1C);
                    SpawnExplosion((object + 0x10), 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 0.666f, 20.0f, 1, 1, 0, 0);
                    level_release_slot_list(st + 0x4E0);
                    PlayMobySound(3, 0, object);
                    object[0xBC] = 6;
                    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x41) & 0xFBFF;
                    *(s16 *)(object + 0x96) = 0x64;
                    FastVecScale(&v50, &v50, math_random_float_range(0.1f, 0.2f));
                    dir = &v70;
                    SPAWN(0xB3D /* moby class 2877 */, 0.0f, 0.05f)
                    SPAWN(0xB3E /* moby class 2878 */, 0.0f, 0.05f)
                    SPAWN(0xB3F /* moby class 2879 */, 0.0f, 0.0f)
                    SPAWN(0xB40 /* moby class 2880 */, 0.0f, 0.05f)
                    SPAWN(0xB40 /* moby class 2880 */, 0.0f, 0.05f)
                    if (I(0x1DC) != -1) {
                        v90.q = *(Quad *)(object + 0x10);
                        v90.f[2] = v90.f[2] + 0.25f;
                        v80.f[0] = math_fast_sin_or_cos_a(OF(0xF8));
                        v80.f[1] = math_fast_sin_or_cos_b(OF(0xF8));
                        v80.f[2] = 0.0f;
                        add_vectors(&vA0, &v80, &v90);
                        if (CollLine(&v90, &v80, 2, 0, 0) != 0) {
                            if (GetCollHitMaterial() != result) {
                                L04_HoverTarget *hit = (L04_HoverTarget *)g_hover_target_buffer;
                                float f20;
                                x = mat_fast_helper_a(hit->v[2], vec_length_xy(hit->v));
                                f20 = FastAddRotations(mat_fast_helper_a(hit->v[0], hit->v[1]), 3.1415927f);
                                FastDiffRots(mat_fast_helper_a(v80.f[0], v80.f[1]), f20);
                                if (x > 1.2217306f) height = 0.0f;
                            }
                        }
                    }
                }
            }
            break;
        }
    } else {
        I(0x750) = 0;
    }
    }
    FastVecSub(&v20, &start, (object + 0x10));
    v20.i[2] = 0;
    F(0x280) = FastVecLength(&v20);
    if (F(0x280) < 0.01f) I(0x750) = I(0x750) + 1;
    {
        Quad q = *(Quad *)(object + 0x10);
        *(Quad *)g_hero_position = q;
        *(Quad *)(g_hero_position + 0x10) = *(Quad *)(object + 0xF0);
        Hero_ProbeGround(q);
    }
}
