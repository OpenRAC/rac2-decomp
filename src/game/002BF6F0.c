#include "include_asm.h"
#include "common.h"
extern float math_random_signed_float_range(float, float);
/* Copy the xyz components and clear the fourth word. Adapted from RAC1. */
static __inline__ void particle_copy_xyz(float *dst, float *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    *(int *)&dst[3] = 0;
}
extern void vec_add_random_offset(void *, float);
extern float vec_distance_xy(void *, void *);
extern void part_queue_impact_effect(void *, int, int, void *, void *, float);
extern int coll_process_hit(float, void *, int, int, int);
extern char *part_spawn_debris(void *, int, int, int, int, int, int, float, float);
extern char *part_spawn_debris_two_mode(void *, int, int, int, int, int, int, float, float);
extern unsigned char *D_001F2628;
extern char *D_001B1D90[] __attribute__((sda));
extern char g_hero_position[];

typedef struct {
    char pad00[0x88];
    float height;
    char pad8C[0x2290 - 0x8C];
    void *owner;
} ParticleHero2C2C80;

typedef struct {
    char pad00[0x2290];
    void *owner;
} ParticleHero2C58A8;

extern char *part_spawn_owned_spark(int,void *,float,float,int,int,int,void *);
extern void euler_to_matrix(void *,void *);
extern void transform_vector(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern int g_game_time[] __attribute__((sda));
extern int FastTweenColor(int,int,float);
extern float fast_vec_dist(void *,void *);
extern void vec_pack_direction(float *,int *);
extern void vec_decode_byte_color(void *,void *);
extern void lerp_vector(void *,void *,void *,float);
extern char D_00189F00[];

extern char *part_spawn_smoke_alt(void *, void *, int, int);
typedef unsigned int U128 __attribute__((mode(TI)));
typedef union { U128 q; f32 f[4]; } SplitVector;
typedef struct {
    unsigned char b0, b1, b2, b3;
    int x4;
    unsigned char b8, b9;
    short hA;
    int xC;
    SplitVector v10, v20, v30;
} Particle6DD8;

typedef struct SplitMotion {
    f32 x, y, z, w;
    f32 t;
    s16 f14;
    s16 f16;
    u8 f18;
    char pad19[3];
    void *f1C;
} SplitMotion;
typedef struct SplitParticle {
    u8 b00;
    char pad01;
    u8 b02;
    char pad03;
    u32 f04;
    u8 f08;
    char pad09;
    s16 h0A;
    f32 f0C;
    SplitVector posv;
    SplitMotion pv;
} SplitParticle;
typedef struct { SplitVector v; void *f10; s32 f14; s32 f18; f32 f1C; s32 f20; char pad[0xC]; } SplitCollision;
typedef struct { SplitVector v; f32 x10; s16 h14; s16 h16; u8 b18; u8 pad[3]; s32 x1C; } FadeSplitMotion;
typedef struct { u8 pad[2]; u8 b2; u8 pad3; u32 x4; u8 b8; u8 pad9; s16 hA; f32 fC; SplitVector pos; FadeSplitMotion e; } FadeSplitParticle;
typedef struct { SplitVector v; s32 x10; s32 x14; u8 pad[4]; f32 x1C; s32 x20; } FadeSplitCollision;
extern char *part_spawn_scaled_smoke(void *, void *, int, void *, int, int);
extern int CollLine(void *, void *, int, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_clear_128(void *);
extern float D_001BAFC0[];
extern unsigned char *D_001F25F4, *D_001F26A8;
extern int moby_forward_two_values_and_amount(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_angle(void);
extern int gfx_pack_color_floats(float, float, float, float);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern unsigned char *D_001F2570;
extern unsigned char *D_001F2688;
extern int moby_decrement_top_byte(void *, int);
extern void moby_transform_joint_to_world(void *, int, void *);

/* Qwen draft (branch qwen/autonomy, c8b09022), checked by tools/check.py */
void part_kill(void *);

int FastDecTimer(short *);

extern int func_00282978_9(char *p);

extern void func_002B9180_13(char *self);

extern float func_00283CE0_2(int v);

extern int func_00283CF0_6(float f);

extern void func_00282CC0_17(char *dst, char *src, char *vec);

extern void func_00300190_4(char *dst, char *src);

extern void func_00282D30_12(char *dst, char *table, float scale);

extern char D_0018A0E0_1[];

extern void Fa2a84657_FUN_00282D48(float *tmp, char *v, float k);

extern void Fa2a84657_FUN_00282CD8(float *tmp, char *a, char *v);

extern int Fa2a84657_FUN_00282978(char *field);

extern void Fa2a84657_FUN_002B9180(unsigned char *p);

typedef struct { unsigned int f0, f4, f8, f12, f16, f20; } T;

extern int func_00282978_12(short *);

extern void func_002B9180_19(char *);

extern float func_00283CE0_5(int);

extern int func_00283D38_6(int, int, float);

struct T {
    float a;
    float b;
    int c;
    int d;
    float e;
};

extern void F15a8b7f0_FUN_00282D30(char *first, char *second, float blend);

extern void F15a8b7f0_FUN_00282CC0(char *first, char *second, char *third);

extern void F15a8b7f0_FUN_002B9180(char *object);


extern void func_00282CC0_19(void *out, void *in, void *src);

extern int func_00282978_11(void *p);

extern void func_002B9180_15(void *self);

extern float func_00283CE0_4(int n);

extern int func_00283D38_3(int handle, int previous, float ratio);

extern char D_00189E20_18[];

extern void Fccb147a4_FUN_002B9180(char *a, char *b);

extern void Fccb147a4_FUN_00300190(char *a, char *b);

extern void Fa03721e9_FUN_00282CC0(char *a, char *b, char *c);

extern void Fa03721e9_FUN_002B9180(char *p);


#ifndef RAC2_T_S16_F570CFB4B
#define RAC2_T_S16_F570CFB4B
typedef short s16_F570cfb4b;
#endif

extern void func_002B9180_7(u8 *);


extern int F7cacd225_FUN_00282978(short *p);

extern void F7cacd225_FUN_002B9180(char *o);

extern float F7cacd225_FUN_00283CE0(int n);

extern int F7cacd225_FUN_00283D38(int a, int b, float q);

#ifndef RAC2_T_OBJ_F7CACD225
#define RAC2_T_OBJ_F7CACD225
typedef struct {
    int pad0;
    int f4;
    short pad8;
    short s10;
    float f12;
    float f16;
    float f20;
    float f24;
    int pad28;
    int f32;
} Obj_F7cacd225;
#endif

extern int func_00282978_6(char *);

extern void func_002B9180_10(char *);

extern void func_00282CC0_21(char *, char *, char *);

extern void func_00300190_2(char *, char *);

#ifndef RAC2_T_VEC16_F9A4B4D8B
#define RAC2_T_VEC16_F9A4B4D8B
typedef struct {
    float f[4];
} Vec16_F9a4b4d8b;
#endif

#ifndef RAC2_T_V4_FC3CB9262
#define RAC2_T_V4_FC3CB9262
typedef int V4_Fc3cb9262 __attribute__((mode(TI)));
#endif

extern void Fc3cb9262_FUN_00282CC0(char *a, char *b, char *c);

extern int Fc3cb9262_FUN_00283CF0(float f);

extern int Fc3cb9262_FUN_00282978(char *a);

extern void Fc3cb9262_FUN_002B9180(char *a);

/* Frees a particle when its lifetime timer runs out. */
void part_free_when_expired(void *particle)
{
  int expired;

  expired = FastDecTimer((short *)((char *)particle + 10));
  if (expired != 0) {
    part_kill(particle);
  }
  return;
}

/* func_002BF728 uses the quadword-copy profile in 002BF728-qcopy.c. */

extern int math_random_int_below(int);
extern void FastVecAdd(char *, char *, char *);
extern float vec_length_xy(void *);
extern void vec_fast_normalize_helper(char *, char *, float);
extern void ApproachValue(float *, float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float D_001B5358;

/* Advances one object: the halfword at offset 10 is capped at 12 and, when the
   sub-object's float at 0x30 is below the object's float at 0x18, the word at
   offset 4 is cleared; the packed byte in that word is then rescaled by the
   halfword, the float at offset 12 grows by 840.0f and is limited by the
   sub-object's float at 0x3C, the object's vector is moved by the sub-object's
   motion triple and the last pair of floats is written back from the angle
   kept in the sub-object. */
void part_update_smoke_wisp(char *self)
{
    char *motion = self + 0x20;
    float vec[3];
    float f0;
    float f1;
    float f2;
    float f3;
    float angle;
    unsigned int packed;

    if (FastDecTimer((short *)(self + 0xA)) != 0) {
        part_kill(self);
        return;
    }
    f1 = *(float *)(self + 0x18);
    if (*(float *)(motion + 0x10) < f1) {
        *(int *)(motion + 8) = 0;
        if (*(short *)(self + 0xA) >= 13) {
            *(short *)(self + 0xA) = 12;
        }
    }
    if (*(float *)(motion + 0x10) < *(float *)(self + 0x18) + 8.6666667461395263671875e-01f) {
        if (math_random_int_below(20) == 0) {
            if (*(short *)(self + 0xA) >= 13) {
                *(short *)(self + 0xA) = 12;
            }
        }
    }
    if (*(short *)(self + 0xA) < 14) {
        packed = *(unsigned int *)(self + 4);
        *(unsigned int *)(self + 4) = (((int)(packed >> 24) * (int)*(short *)(self + 0xA) / 14) << 24) | (packed & 0xFFFFFF);
    }
    f0 = *(float *)(self + 0xC);
    f0 = f0 + 8.4000006103515625000000e+02f;
    *(float *)(self + 0xC) = f0;
    f1 = *(float *)(motion + 0xC);
    if (f1 < f0) {
        *(float *)(self + 0xC) = f1;
    }
    vec[0] = *(float *)(motion + 0);
    vec[1] = *(float *)(motion + 4);
    vec[2] = *(float *)(motion + 8);
    f0 = vec_length_xy((void *)vec);
    vec_fast_normalize_helper((char *)vec, (char *)vec, f0 * 9.7000002861022949218750e-01f);
    FastVecAdd(self + 0x10, self + 0x10, (char *)vec);
    ApproachValue(&vec[2], 2.1666666492819786071777e-02f, 1.3888889225199818611145e-03f);
    *(float *)(motion + 4) = vec[1];
    *(float *)(motion + 0) = vec[0];
    *(float *)(motion + 8) = vec[2];
    f0 = FastAddRotations(*(float *)(motion + 0x14), *(float *)(motion + 0x18));
    *(float *)(motion + 0x14) = f0;
    angle = FastAddRotations(D_001B5358, 1.5707964897155761718750e+00f);
    f3 = math_fast_sin_or_cos_b(*(float *)(motion + 0x14));
    f2 = f3 * *(float *)(motion + 0x1C);
    f0 = math_fast_sin_or_cos_a(angle);
    vec[0] = f0 * f2;
    vec[1] = math_fast_sin_or_cos_b(angle) * f2;
    vec[2] = 0.0f;
    FastVecAdd(self + 0x10, self + 0x10, (char *)vec);
}


extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void *part_spawn_drifting(void *, float, void *, float, int);
extern void part_spawn_puff(void *, int, float, float);
typedef union { unsigned char b[0x2600]; int i[0x980]; float f[0x980]; } L_BFC50Hero;
extern char g_hero_state[];
extern void *D_001A9E74 __attribute__((section(".sdata")));
extern float g_collision_hit[];
extern char D_001BAFA0[];

/* Moves a falling spark and checks if it hits something. On a hit it makes a small splash and removes the spark, otherwise it keeps falling and fades. */
void part_update_falling_spark(char *self)
{
    char *motion = self + 0x20;
    float vec[4] __attribute__((aligned(16)));
    int state = *(int *)(motion + 0x10);

    if (state == 0) {
        FastVecAdd(self + 0x10, self + 0x10, motion);
    } else if (state == 1) {
        FastVecAdd((char *)vec, self + 0x10, motion);
        if (CollLine(self + 0x10, vec, 2, 0, 0) == 0) {
            goto copy;
        }
        if (GetCollHitMaterial() == 0) {
            part_spawn_drifting(D_001BAFA0, 0.2f, D_001A9E74, 5250.0f, -1);
        }
        part_kill(self);
        return;
    } else if (state == 3) {
        FastVecAdd(self + 0x10, self + 0x10, motion);
        if (*(float *)(self + 0x18) < ((L_BFC50Hero *)g_hero_state)->f[0x330 / 4]) {
            void *t = D_001A9E74;

            *(float *)(self + 0x18) = ((L_BFC50Hero *)g_hero_state)->f[0x330 / 4];
            part_spawn_drifting(self + 0x10, 0.2f, t, 5250.0f, -1);
            part_kill(self);
            return;
        }
    } else {
        FastVecAdd((char *)vec, self + 0x10, motion);
        if (CollLine(self + 0x10, vec, 2, 0, 0) == 0) {
            goto copy;
        }
        if (GetCollHitMaterial() != 0) {
            g_collision_hit[10] = g_collision_hit[10] + 0.05f;
            part_spawn_puff(&g_collision_hit[8], -1, 0.25f, 3150.0f);
        }
        part_kill(self);
        return;
copy:
        qcopy(self + 0x10, vec);
    }
    *(float *)(motion + 8) = *(float *)(motion + 8) - *(float *)(motion + 0x1C);
    self[8] = self[8] + 2;
    if (--*(int *)(motion + 0x14) <= 0 || *(float *)(self + 0x18) < *(float *)(motion + 0x18)) {
        *(int *)(self + 4) = *(int *)(self + 4) - 0x10000000;
        if (*(int *)(self + 4) < 0) {
            part_kill(self);
        }
    }
}

/* func_002BFE80 is defined in 002BFE80-dbg.c. */

extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_lerp_int_fraction(int, int, float);
extern float g_camera_eye_state[];
extern int abs(int);

/* Slides a particle along a smoothed velocity and blends its color by how much life is left. It is removed when its timer ends. */
void part_update_smoothed_drift(char *self)
{
    char *motion = self + 0x20;
    float vec[4];
    int delta;
    float ratio;

    if (FastDecTimer((short *)(self + 0xA)) != 0) {
        part_kill(self);
        return;
    }
    FastVecSub(vec, g_camera_eye_state, motion);
    if (FastVecLength(vec) > 5.0f) {
        vec_scale_to_length(vec, vec, 1.25f);
    } else {
        FastVecScale((char *)vec, (char *)vec, 0.25f);
    }
    FastVecAdd((char *)(self + 0x10), motion, (char *)vec);
    delta = abs(*(short *)(self + 0xA) - *(int *)(motion + 0x14));
    ratio = (float)(*(int *)(motion + 0x14) - delta) / (float)*(int *)(motion + 0x14);
    *(int *)(self + 4) = math_lerp_int_fraction(0, *(int *)(motion + 0x10), ratio);
}


/* func_002C01F8 is in 002BF6F0-c01f8-g8.c. */

/* func_002C02F0 uses the quadword-copy profile in 002C02F0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
/* Updates a bouncing spark that can split in two, bounces off walls, shrinks and fades, and is removed when it is used up. */
void part_update_splitting_spark(SplitParticle *p) {
    SplitVector v0u;
    SplitVector v1u;
    SplitCollision collision;
    f32 v2[4];
    SplitMotion *pv;
    SplitParticle *child;
    u8 *table;
    u8 flags;
    s32 fm;
    s64 hit;
    s32 k, t;
    f32 f, g, s;

    pv = &p->pv;
    if (p->h0A != 0 && FastDecTimer(&p->h0A) != 0) {
        f32 sp, lo, hi, sc, zero, nsp;
        pv->f18 |= 0x88;
        lo = 0.5f;
        sp = p->f0C / (func_00283CE0_2((u8)pv->pad19[0]) * 28125.0f);
        hi = 0.7f;
        sc = 0.2f;
        p->f0C = p->f0C * 0.8f;
        zero = 0.0f;
        f = math_random_float_range(lo, hi);
        nsp = -sp;
        func_00282D30_12((char *)v0u.f, (char *)pv, f);
        v1u.f[0] = p->posv.f[0] + math_random_float_range(nsp, sp);
        v1u.f[1] = p->posv.f[1] + math_random_float_range(nsp, sp);
        v1u.f[2] = p->posv.f[2] + math_random_float_range(nsp, sp);
        v0u.f[0] = v0u.f[0] + math_random_float_range(-p->pv.x * sc, p->pv.x * sc);
        v0u.f[1] = v0u.f[1] + math_random_float_range(-pv->y * sc, pv->y * sc);
        v0u.f[2] = v0u.f[2] + math_random_float_range(-pv->z * sc, zero);
        child = (SplitParticle *)part_spawn_scaled_smoke(v1u.f, v0u.f, (pv->f18 & 0x10) | 0x88, pv->f1C, (u8)pv->pad19[0], 128);
        if (child != 0) {
            child->h0A = 2;
            child->f0C = p->f0C;
        }
        func_00282D30_12((char *)pv, (char *)pv, math_random_float_range(lo, hi));
        p->pv.x = p->pv.x + math_random_float_range(-p->pv.x * sc, p->pv.x * sc);
        pv->y = pv->y + math_random_float_range(-pv->y * sc, pv->y * sc);
        pv->z = pv->z + math_random_float_range(-pv->z * sc, zero);
        p->posv.f[0] = p->posv.f[0] + math_random_float_range(nsp, sp);
        p->posv.f[1] = p->posv.f[1] + math_random_float_range(nsp, sp);
        p->posv.f[2] = p->posv.f[2] + math_random_float_range(nsp, sp);
    }
    table = D_001F2570;
    { int index = p->b02 - table[0];
    p->b02 = table[(p->h0A + pv->f16 + index) & 7]; }
    FastVecAdd((char *)v0u.f, (char *)p->posv.f, (char *)pv);
    hit = 0;
    k = pv->f14;
    if (3 < k) {
        FastVecSub(v1u.f, p->posv.f, pv);
    } else {
        v1u.q = p->posv.q;
    }
    func_00282D30_12((char *)&collision, (char *)&collision, 0.01f);
    flags = pv->f18;
    if (flags & 8) {
        if ((p->f04 & 0xFF000000) == 0) goto kill;
        pv->f18 = flags | 8;
        if (!(pv->f18 & 0x10)) hit = CollLine(v1u.f, v0u.f, 4, pv->f1C, 0) != 0;
    } else {
        collision.f10 = pv->f1C;
        collision.f14 = 0x10001;
        collision.f1C = 1.0f;
        collision.v.q = *(U128 *)pv;
        if (flags & 0x40) vec_clear_128(&collision);
        collision.f20 = 1;
        if (!(pv->f18 & 0x10)) hit = CollLine(v1u.f, v0u.f, 0, pv->f1C, &collision) != 0;
    }
    if (hit) {
        vec_scale_to_length(v2, D_001BAFC0, 1.0f);
        vec_fast_normalize(pv, pv, D_001BAFC0);
        func_00282D30_12((char *)pv, (char *)pv, 0.02f);
        vec_scale_to_length(v2, D_001BAFC0, 0.055f);
        FastVecAdd((char *)p->posv.f, (char *)(D_001BAFC0 - 8), (char *)v2);
        if (p->f0C < 200000.0f && (pv->f18 & 8) == 0) {
            p->f0C = p->f0C + p->f0C;
        }
        pv->f18 |= 8;
    } else {
        qcopy(p->posv.f, v0u.f);
    }
    if (pv->f18 & 8) {
        f32 n;
        pv->f16++;
        n = p->f0C - (func_00283CE0_2((u8)pv->pad19[0]) * 8437.5f - func_00283CE0_2((u8)pv->pad19[0]) * 937.5f) * 0.0694444477558136f;
        p->f0C = n;
        if (n <= 0.0f) {
        kill:
            part_kill(p);
            return;
        }
    } else {
        p->f0C = p->f0C + (func_00283CE0_2((u8)pv->pad19[0]) * 8437.5f - func_00283CE0_2((u8)pv->pad19[0]) * 937.5f) * 0.0555555559694767f;
    }
    f = func_00283CE0_2(pv->f14);
    s = f * 0.000246913579758257f + 0.08f;
    if (s < 0.0f) s = 0.0f;
    if (0.08f < s) s = 0.08f;
    if (pv->f18 & 8) {
        s = s / ((f32)pv->f16 * 0.142857149243355f + 1.0f);
    }
    p->f04 = (p->f04 & 0xFFFFFF) | (FloatToInt(s * 256.0f) << 24);
    pv->z = pv->z + 0.008f;
    t = pv->f14;
    if (25 < t || (pv->f18 & 8)) {
        pv->x = pv->x * 0.95f;
        pv->y = pv->y * 0.95f;
    }
    fm = pv->f18;
    g = -1.0f;
    if (fm & 1) g = 1.0f;
    if (fm & 8) {
        pv->z = pv->z + 0.008f;
        f = func_00283CE0_2(pv->f16);
        pv->t = pv->t + g * (-0.01f) / f;
    } else {
        pv->t = pv->t + g * (-0.01f);
    }
    if (1.0f < pv->t) pv->t = pv->t - 1.0f;
    if (pv->t < 0.0f) pv->t = pv->t + 1.0f;
    p->f08 = (s32)(pv->t * 256.0f);
}



/* func_002C0CC0 uses the quadword-copy profile in 002C0CC0-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
/* Updates a fading spark that can split in two, bounces off surfaces, and fades out until it is removed. */
void part_update_fading_split_spark(FadeSplitParticle *particle) {
    SplitVector new_vel, next_pos;
    FadeSplitCollision collision;
    FadeSplitMotion *motion = &particle->e;
    FadeSplitParticle *child;
    f32 spread, neg_spread, alpha, life_ratio;
    s32 hit;
    u8 flags;
    u8 *table;

    if (particle->hA != 0 && FastDecTimer(&particle->hA)) {
        motion->b18 |= 0x88;
        spread = particle->fC * 0.0000011111111462014378f;
        particle->fC *= 0.8f;
        neg_spread = -spread;
        func_00282D30_12((char *)&new_vel, (char *)motion, math_random_float_range(0.5f, 0.7f));
        next_pos.f[0] = particle->pos.f[0] + math_random_float_range(neg_spread, spread);
        next_pos.f[1] = particle->pos.f[1] + math_random_float_range(neg_spread, spread);
        next_pos.f[2] = particle->pos.f[2] + math_random_float_range(neg_spread, spread);
        new_vel.f[0] += math_random_float_range(-motion->v.f[0] * 0.2f, motion->v.f[0] * 0.2f);
        new_vel.f[1] += math_random_float_range(-motion->v.f[1] * 0.2f, motion->v.f[1] * 0.2f);
        new_vel.f[2] += math_random_float_range(-motion->v.f[2] * 0.2f, 0.0f);
        child = (FadeSplitParticle *)part_spawn_smoke((char *)&next_pos, (char *)&new_vel, (motion->b18 & 0x10) | 0x88, motion->x1C);
        if (child) {
            child->hA = 2;
            child->fC = particle->fC;
        }
        func_00282D30_12((char *)motion, (char *)motion, math_random_float_range(0.5f, 0.7f));
        motion->v.f[0] += math_random_float_range(-motion->v.f[0] * 0.2f, motion->v.f[0] * 0.2f);
        motion->v.f[1] += math_random_float_range(-motion->v.f[1] * 0.2f, motion->v.f[1] * 0.2f);
        motion->v.f[2] += math_random_float_range(-motion->v.f[2] * 0.2f, 0.0f);
        particle->pos.f[0] += math_random_float_range(neg_spread, spread);
        particle->pos.f[1] += math_random_float_range(neg_spread, spread);
        particle->pos.f[2] += math_random_float_range(neg_spread, spread);
    }
    table = D_001F2570;
    { int index = particle->b2 - table[0];
    particle->b2 = table[(particle->hA + motion->h16 + index) & 7]; }
    FastVecAdd((char *)&new_vel, (char *)&particle->pos, (char *)motion);
    hit = 0;
    if (motion->h14 > 3) {
        FastVecSub(&next_pos, &particle->pos, motion);
    } else {
        next_pos.q = particle->pos.q;
    }
    func_00282D30_12((char *)&collision, (char *)&collision, 0.01f);
    flags = motion->b18;
    if (flags & 8) {
        if (!(particle->x4 & 0xFF000000)) goto kill;
        motion->b18 = flags | 8;
        if (!math_random_int_below(3) && !(motion->b18 & 0x10)) hit = CollLine(&next_pos, &new_vel, 0, (void *)motion->x1C, 0) != 0;
    } else {
        collision.x10 = motion->x1C;
        collision.x1C = 1.0f;
        collision.v.q = motion->v.q;
        collision.x14 = 1;
        collision.x20 = 1;
        if (!math_random_int_below(3) && !(motion->b18 & 0x10)) hit = CollLine(&next_pos, &new_vel, 0, (void *)motion->x1C, &collision) != 0;
    }
    if (hit) motion->b18 |= 8;
    else qcopy(&particle->pos, &new_vel);
    if (motion->b18 & 8) {
        motion->h16++;
        particle->fC -= 18055.5546875f;
        if (particle->fC <= 0.0f) {
        kill:
            part_kill(particle);
            return;
        }
    } else {
        particle->fC += 14444.4443359375f;
    }
    life_ratio = func_00283CE0_2(motion->h14);
    alpha = life_ratio * 0.000246913579758257f + 0.08f;
    if (alpha < 0.0f) alpha = 0.0f;
    if (0.08f < alpha) alpha = 0.08f;
    if (motion->b18 & 8) alpha /= (f32)motion->h16 * 0.142857149243355f + 1.0f;
    particle->x4 = (particle->x4 & 0xFFFFFF) | (FloatToInt(alpha * 256.0f) << 24);
    motion->v.f[2] += 0.008f;
    if (motion->h14 > 25 || (motion->b18 & 8)) {
        motion->v.f[0] *= 0.95f;
        motion->v.f[1] *= 0.95f;
    }
    { u8 f2 = motion->b18;
    life_ratio = -1.0f;
    if (f2 & 1) life_ratio = 1.0f;
    if (f2 & 8) {
        motion->v.f[2] += 0.008f;
        motion->x10 += life_ratio * (-0.01f) / func_00283CE0_2(motion->h16);
    } else {
        motion->x10 += life_ratio * (-0.01f);
    } }
    if (1.0f < motion->x10) motion->x10 -= 1.0f;
    if (motion->x10 < 0.0f) motion->x10 += 1.0f;
    particle->b8 = (s32)(motion->x10 * 256.0f);
}

/* Updates one byte-addressed object by packing a converted short-ratio value with three bytes, applying the bound helper sequence to three stored floats, and accumulating one byte and one float. */
void part_update_color_packed(char *self)
{
    float vec[4];
    float tmp[4];
    char *motion;
    char *scratch;
    float scale;
    float total;
    unsigned int packed;

    if (func_00282978_9(self + 10)) {
        func_002B9180_13(self);
        return;
    }
    motion = self + 32;
    scale = func_00283CE0_2(*(short *)(motion + 30));
    total = func_00283CE0_2(*(short *)(motion + 28));
    packed = func_00283CF0_6(scale * ((float)*(short *)(self + 10) / total));
    packed = packed << 24;
    packed = packed | (*(unsigned char *)(motion + 19) << 16);
    packed = packed | (*(unsigned char *)(motion + 18) << 8);
    packed = packed | *(unsigned char *)(motion + 17);
    *(unsigned int *)(self + 4) = packed;
    vec[3] = 0.0f;
    vec[0] = *(float *)(self + 32);
    vec[1] = *(float *)(motion + 4);
    vec[2] = *(float *)(motion + 8);
    func_00282CC0_17((char *)self + 16, (char *)self + 16, (char *)vec);
    if (*(float *)(self + 28) != 0.0f) {
        if (*(float *)(self + 28) == 2.0f)
            func_00300190_4((char *)self + 16, (char *)self + 16);
        *(float *)(self + 28) = 2.0f;
    }
    scratch = (char *)tmp;
    func_00282D30_12(scratch, D_0018A0E0_1, *(float *)(motion + 12));
    func_00282CC0_17((char *)vec, (char *)vec, scratch);
    func_00282D30_12((char *)vec, (char *)vec, *(float *)(motion + 24));
    *(float *)motion = vec[0];
    *(float *)(motion + 4) = vec[1];
    *(float *)(motion + 8) = vec[2];
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 16);
    *(float *)(self + 12) = *(float *)(self + 12) + *(float *)(motion + 20);
}

typedef struct {
    float vx;
    float vy;
    int f8;
    int fC;
    float spin;
    void *owner;
} L_C19D8Payload;
typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    unsigned short size;
    float life;
    float position[4];
    L_C19D8Payload payload;
} L_C19D8Particle;
extern void *part_alloc(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern int func_001163B0(void);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern unsigned char *D_001F25F4;

/* Creates a small drifting particle at a position with a random direction, a size, and an optional color. */
void *part_spawn_drifting(void *position, float size, void *owner, float spin, int color)
{
    L_C19D8Particle *p = (L_C19D8Particle *)part_alloc(0x2D);
    L_C19D8Payload *out;
    float angle;
    float speed;
    int c;

    if (p) {
        qcopy(p->position, position);
        if (color == -1) {
            c = ((math_random_int_below(6) + 0x14) << 24) | 0x808080;
        } else {
            c = color;
        }
        out = &p->payload;
        p->color = c;
        p->alpha = FloatToInt(1.0f) + 32;
        p->b3 = 0x48;
        p->b1 = 1;
        p->b2 = *D_001F25F4;
        p->seed = func_001163B0();
        p->size = 4;
        p->life = size * 210000.0f;
        angle = math_random_angle();
        speed = math_random_float_range(0.0015f, 0.0025f);
        p->payload.vx = math_fast_sin_or_cos_a(angle) * speed;
        out->vy = math_fast_sin_or_cos_b(angle) * speed;
        out->owner = owner;
        out->spin = spin;
        out->f8 = 0;
    }
    return p;
}

/* func_002C1B38 is in the -G8 sibling. */

extern float math_fabs(float);

/* Moves a spark, spins it slower and slower, and fades it out until its timer ends. */
void part_update_spinning_spark(char *self)
{
    char *motion = self + 0x20;
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(float *)(self + 0x0C) += 5880.0f;
    *(float *)(motion + 0x14) *= 0.98f;
    *(float *)(motion + 0x10) += *(float *)(motion + 0x14);
    *(unsigned char *)(self + 8) = func_00283CF0_6(*(float *)(motion + 0x10));
    if (*(float **)(motion + 0x18)) {
        if (math_fabs(*(float *)(self + 0x18) - **(float **)(motion + 0x18)) < 0.2f)
            *(float *)(self + 0x18) = **(float **)(motion + 0x18) + 0.02f;
    }
    if (--*(short *)(self + 0xA) == 0) {
        *(int *)(self + 4) -= 0x01000000;
        *(short *)(self + 0xA) = 1;
    }
    if ((*(unsigned int *)(self + 4) & 0xFF000000) == 0)
        part_kill(self);
}

extern void func_00282D30_fa(void *, void *, float);

/* Slows a particle a little each frame, grows it, and fades it out until it disappears. */
void part_update_slowing_fade(char *particle)
{
    char *particle_copy = particle;
    char *motion = particle_copy + 32;
    int fade_value;

    func_00282D30_fa(motion, motion, 0.975f);
    FastVecAdd(particle_copy + 16, particle_copy + 16, motion);
    *(float *)(particle_copy + 12) = *(float *)(particle_copy + 12) + 14700.0f;
    *(u8 *)(particle_copy + 8) = *(u8 *)(particle_copy + 8) + *(u8 *)(motion + 16);
    fade_value = *(int *)(particle_copy + 4) + 0xFE000000;
    *(int *)(particle_copy + 4) = fade_value;
    if (fade_value < 0) {
        part_kill(particle_copy);
    }
}

extern void FastVecAdd(char *, char *, char *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);

/* Moves a particle and blends its color over its lifetime. It is removed when its timer ends. */
void part_update_color_tween(char *obj) {
    char *tail = obj + 0x20;
    obj[8] += tail[0x1C];
    FastVecAdd(obj + 0x10, obj + 0x10, tail);
    *(int *)(obj + 4) = FastTweenColor(*(int *)(tail + 0x18), *(int *)(tail + 0x14),
        math_fabs(IntToFloat(*(short *)(obj + 0x0A)) * *(float *)(tail + 0x10) - 1.0f));
    if (FastDecTimer((short *)(obj + 0x0A)) != 0) {
        part_kill(obj);
    }
}


/* func_002C1FC0 is defined in 002BF6F0-g8.c. */

/* Slows a particle, lets it drift slowly, and fades it out until it is removed or its timer ends. */
void part_update_drifting_fade(unsigned char *particle)
{
    float tmp[4];
    char *motion;
    int fade_value;

    motion = (char *)particle + 32;
    Fa2a84657_FUN_00282D48(tmp, motion, 9.4999998807907104492188e-01f);
    *(float *)(motion + 8) = *(float *)(motion + 8) + 1.3888889225199818611145e-03f;
    Fa2a84657_FUN_00282CD8(tmp, (char *)particle + 16, motion);

    fade_value = *(int *)(particle + 4) + (int)0xFE000000;
    *(int *)(particle + 4) = fade_value;
    if (((unsigned)(fade_value & 0xFF000000) - 1) > 0x5EFFFFFFu || Fa2a84657_FUN_00282978((char *)particle + 10) != 0) {
        Fa2a84657_FUN_002B9180(particle);
    } else {
        float growth;
        float size;

        size = *(float *)(particle + 12);
        growth = 2.1000000000000000000000e+05f - size;
        growth = growth * 7.0000000298023223876953e-02f;
        size = size + growth;
        *(float *)(particle + 12) = size;
        particle[8] = particle[8] + 1;
    }
}

/* Tests the halfword at offset 10 through a helper; on zero it stores a scaled int at offset 4 and a 210000.0f-scaled interpolation of two floats at offset 12, otherwise calls a second helper. */
void part_update_size_tween(char *particle)
{
    if (func_00282978_12((short *)(particle + 10)) != 0) {
        func_002B9180_19(particle);
    } else {
        struct T *tween = (struct T *)(particle + 32);
        float progress = func_00283CE0_5(*(short *)(particle + 10)) * tween->e;

        *(int *)(particle + 4) = func_00283D38_6(tween->d, tween->c, progress);
        *(float *)(particle + 12) = ((tween->a - tween->b) * progress + tween->b) * 210000.0f;
    }
}

/* Move a particle while tweening its size and alpha, then apply gravity. */
void part_update_size_alpha_tween(char *particle)
{
    char *motion = particle + 32;
    Vec16_F9a4b4d8b v;
    float progress;
    int alpha;

    particle[8] += (unsigned char)motion[10];
    if (*(short *)(motion + 8) - *(short *)(particle + 10) < 6) {
        progress = (float)(*(short *)(motion + 8) - *(short *)(particle + 10)) * 0.2f;
        *(float *)(particle + 12) = *(float *)(motion + 4) +
            ((*(float *)motion + *(float *)(motion + 4)) * 0.5f - *(float *)(motion + 4)) * progress;
        {
            int c2 = (unsigned char)motion[11] >> 1;
            int c = (unsigned char)motion[11];
            alpha = FloatToInt((float)c + (float)(c2 - c) * progress);
        }
    } else {
        progress = func_00283CE0_2(*(short *)(motion + 8) - 6);
        progress = (float)*(short *)(particle + 10) / progress;
        *(float *)(particle + 12) = *(float *)motion +
            ((*(float *)motion + *(float *)(motion + 4)) * 0.5f - *(float *)motion) * progress;
        alpha = FloatToInt((float)((unsigned char)motion[11] >> 1) * progress);
    }
    *(int *)(particle + 4) = (alpha << 24) | (*(int *)(particle + 4) & 0xffffff);
    particle_copy_xyz(v.f, (float *)(motion + 12));
    FastVecAdd(particle + 16, particle + 16, (char *)&v);
    *(float *)(motion + 20) -= *(float *)(motion + 24);
    if (*(float *)(particle + 28) != 0) {
        if (*(float *)(particle + 28) == 2.0f)
            func_00300190_2(particle + 16, particle + 16);
        *(float *)(particle + 28) = 2.0f;
    }
    if (*(float *)(particle + 16) < 2 || *(float *)(particle + 16) > 1021 ||
        *(float *)(particle + 20) < 2 || *(float *)(particle + 20) > 1021 ||
        *(float *)(particle + 24) < 2 || *(float *)(particle + 24) > 1021) {
        part_kill(particle);
        return;
    }
    if (FastDecTimer((short *)(particle + 10)))
        part_kill(particle);
}

extern void anim_sample_key_track(float, float, void *, int *, float *, void *);

extern int coll_process_hit(float, void *, int, int, int);

extern float IntToFloat(int);

extern int gfx_pack_color_floats(float, float, float, float);

#ifndef RAC2_T_VEC16_F5621621C
#define RAC2_T_VEC16_F5621621C
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_F5621621c;
#endif

extern void moby_queue_knockback_for_nodes(void *a0, Vec16_F5621621c *src, int *p, int n, int t0, int t1, int t2, int t3, float f1, float f2, float f3);

extern int D_001BF000[];

/* Updates one object: it copies its vector into a local, adds the two motion
   floats and hands the result with the motion's third float to a helper, then
   bails out through the second helper when the halfword at offset 10 is
   taken. Otherwise it packs a colour from the halfword and pushes the object
   through a vector helper with the table at D_001BF000. The two words the
   first helper writes (n and f) are the retail's scratch out-parameters: it
   never reads them back. The words at offsets 0x20 and 0x34 are 32-bit in the
   object and the helpers take them as pointers, so they are cast on the way
   out. */
void part_update_trail_emitter(char *obj)
{
    char *motion = obj + 0x20;
    char *vec = obj + 0x10;
    V4_Fc3cb9262 local[2];
    int n;
    float f;
    int count;

    local[0] = *(V4_Fc3cb9262 *)(obj + 0x10);
    *(float *)(motion + 4) = *(float *)(motion + 4) + *(float *)(motion + 8);
    anim_sample_key_track(*(float *)(motion + 4), *(float *)(motion + 0xC),
                  (void *)*(int *)(obj + 0x20), &n, &f, vec);

    if (FastDecTimer((short *)(obj + 0xA)) != 0) {
        part_kill(obj);
        return;
    }

    {
        int index = *(short *)(obj + 0xA);

        if ((float)index < 7.5f)
            *(int *)(obj + 4) = gfx_pack_color_floats(0.7f, 0.7f, 0.7f,
                                             IntToFloat(index) * 0.0106666666f);
    }

    count = coll_process_hit(0.15f, vec, 16, *(int *)(motion + 0x14), 0);
    local[1] = *(V4_Fc3cb9262 *)(obj + 0x10);
    moby_queue_knockback_for_nodes((void *)*(int *)(motion + 0x14), (Vec16_F5621621c *)&local[1],
                   D_001BF000, count, 0, 0x810001, 2, 1, 2.0f, 1.0f, 1.0f);
}


/* Slows a particle, grows it, and dims its color until it disappears. */
void part_update_growing_dim(char *object)
{
    int count;
    int low;
    int high;

    F15a8b7f0_FUN_00282D30(object + 32, object + 32, 0.975f);
    F15a8b7f0_FUN_00282CC0(object + 16, object + 16, object + 32);
    *(float *)(object + 12) += 6300.0f;
    count = *(unsigned char *)(object + 4) - 4;
    if (count <= 0)
        F15a8b7f0_FUN_002B9180(object);
    else {
        low = (count << 8) | 0x60000000;
        high = (count << 16) | low;
        *(int *)(object + 4) = high | count;
    }
}

extern int FloatToInt(float);

/* A drifting spark: moves by its velocity, spins, slows its fall and fades over its last
   64 frames; it frees itself when the count runs out. */
void part_update_drifting_spark(char *particle)
{
    char *vel = particle + 0x20;

    FastVecAdd(particle + 0x10, particle + 0x10, vel);
    *(float *)(particle + 0xC) += 5880.0f;
    *(float *)(vel + 0x14) *= 0.98f;
    *(float *)(vel + 0x10) += *(float *)(vel + 0x14);
    particle[8] = FloatToInt(*(float *)(vel + 0x10));
    if (--*(short *)(particle + 0xA) <= 0)
        part_kill(particle);
    if (*(short *)(particle + 0xA) > 0x40)
        *(int *)(particle + 4) = ((0x80 - *(short *)(particle + 0xA)) << 24) | 0x808080;
    else
        *(int *)(particle + 4) = (*(short *)(particle + 0xA) << 24) | 0x808080;
}

/* func_002C2A88 uses the quadword-copy profile in 002C2A88-qcopy.c. */

/* Updates a three-step effect: a color flash, then a burst that makes sparks and pushes the player if close, then a fading ember. */
void part_update_burst_effect(char *particle) {
 char *motion=particle+32; SplitVector v; int i; float progress, total, speed;
 switch(*(unsigned char *)(motion+20)) {
 case 0: {
  float duration=func_00283CE0_2(*(unsigned char *)(motion+17));
  *(int *)(particle+4)=FastTweenColor(0xff4080ff,0,(duration-func_00283CE0_2(*(short *)(particle+10)))/duration);
  if(FastDecTimer((short *)(particle+10))) {
   if(*(unsigned char *)(motion+16)==1)part_kill(particle);
   else {*(unsigned char *)(motion+20)=1;*(short *)(particle+10)=*(unsigned char *)(motion+18);}
  }
  break; }
 case 1:
  for(i=0;i<*(unsigned char *)(motion+19);i++) {
   qcopy(&v,particle+16);
   vec_add_random_offset(&v,0.05f);
   speed=1.0f;
   if(*(short *)(particle+10)<10)speed=func_00283CE0_2(*(short *)(particle+10))*0.1f;
   part_spawn_debris(&v,2,*(unsigned char *)(motion+17),*(unsigned char *)(motion+18),*(unsigned char *)(motion+19),*(unsigned char *)(motion+21),*(int *)(motion+24),*(float *)(motion+28),speed);
  }
  if(FastDecTimer((short *)(particle+10)))part_kill(particle);
  { char *pos=g_hero_position; ParticleHero2C2C80 *hero;
  if(vec_distance_xy(particle+16,pos)<0.3f) {
   hero=(ParticleHero2C2C80 *)(pos-128);
   if(hero->height<*(float *)(particle+24)+1.2f) {
   FastVecSub(&v,pos,particle+16);
   vec_scale_to_length(&v,&v,1.0f);v.f[2]=1.0f;
   part_queue_impact_effect(hero->owner,*(int *)(motion+24),1,particle+16,&v,*(float *)(motion+28));
  }}
  }
  break;
 case 2:
  FastVecAdd(particle+16,particle+16,motion);
  total=func_00283CE0_2(*(unsigned char *)(motion+21));
  progress=(total-func_00283CE0_2(*(short *)(particle+10)))/total;
  *(int *)(particle+4)=FastTweenColor((*(unsigned char *)(motion+22)<<24)|0x4060,0x8fafff,progress);
  if(progress<0.6f)*(float *)(particle+12)+=9030.0f;else *(float *)(particle+12)-=16800.0f;
  particle[2]=D_001F2628[func_001163B0()&7];
  if((((particle-D_001B1D90[0])>>6)&1))particle[8]++;else particle[8]--;
  if(FastDecTimer((short *)(particle+10)))part_kill(particle);
  break;
 }
}




extern unsigned char *r1_func_00218928(int);
extern int r1_func_001FA898(float);
extern void r1_func_001F9BF0(void *, void *, void *);
extern char g_hero_position[];
extern unsigned char *r1_D_L00_001B2400[];


/* rac1-decomp src/overlays/shared/alpha_fade_particle_updates.c: func_002C2FD8 */
/* spawns particle type 0x3B from a position, colour index and flags */
/* Creates a fading particle at a position with a given size, color and lifetime. It can optionally follow the view. */
unsigned char *part_spawn_fading(float size, void *pos, int color, unsigned char frame, int color_index, int flag, int lifetime, int mode) {
    unsigned char *particle = r1_func_00218928(0x3B);
    if (particle != 0) {
        char *motion = (char *)particle + 0x20;
        *(int *)(motion + 0x10) = mode;
        if (mode == 1) {
            r1_func_001F9BF0(motion, pos, g_hero_position);
        }
        qcopy(particle + 0x10, pos);
        *(int *)(particle + 4) = color;
        particle[9] = r1_func_001FA898(1.0f) + 0x20;
        if (flag != 0) {
            particle[3] = 0x44;
        } else {
            particle[3] = 0x48;
        }
        particle[8] = frame;
        particle[1] = 0;
        *(float *)(particle + 0xC) = size * 210000.0f;
        particle[2] = *r1_D_L00_001B2400[color_index];
        *(short *)(particle + 0xA) = lifetime;
    }
    return particle;
}

extern void FastVecAdd(char *, char *, char *);

/* Keeps a particle at the view origin plus its offset in one mode, and removes it when its timer ends. */
void part_update_view_anchored(char *self)
{
    char *part = self + 0x20;
    if (*(int *)(part + 0x10) == 1)
        FastVecAdd(self + 0x10, g_hero_position, part);
    if (FastDecTimer((short *)(self + 0xA)) != 0)
        part_kill(self);
}

/* Creates a particle at POS moving by VEL; in mode 1 it also keeps its offset from the
   resident view origin. */
/* func_002C3150 uses the quadword-copy profile in 002C3150-qcopy.c. */

/* advances three floats of a sub-object by a resident offset triple, calls a three-pointer update, subtracts the offsets back out, rejects the result when any coordinate leaves the 2.0..1021.0 band, and otherwise rescales a 24-bit handle by the ratio of two helper lookups over a signed halfword index */
void part_update_size_fade(u8 *self)
{
    char *motion = (char *)self + 32;
    int color;
    float prev_time;

    if (*(int *)(motion + 28) == 1) {
        char *base = D_00189E20_18;
        *(float *)(self + 16) = *(float *)(base + 128) + *(float *)(motion + 16);
        *(float *)(self + 20) = *(float *)(base + 132) + *(float *)(motion + 20);
        *(float *)(self + 24) = *(float *)(base + 136) + *(float *)(motion + 24);
        func_00282CC0_19(self + 16, self + 16, motion);
        *(float *)(motion + 16) = *(float *)(self + 16) - *(float *)(base + 128);
        *(float *)(motion + 20) = *(float *)(self + 20) - *(float *)(base + 132);
        *(float *)(motion + 24) = *(float *)(self + 24) - *(float *)(base + 136);
    } else {
        func_00282CC0_19(self + 16, self + 16, motion);
    }

    if (*(float *)(self + 16) < 2.0f || *(float *)(self + 16) > 1021.0f
        || *(float *)(self + 20) < 2.0f || *(float *)(self + 20) > 1021.0f
        || *(float *)(self + 24) < 2.0f || *(float *)(self + 24) > 1021.0f) {
        func_002B9180_15(self);
        return;
    }

    if (func_00282978_11((char *)self + 10) != 0) {
        func_002B9180_15(self);
        return;
    }

    color = *(int *)(self + 4) & 0xFFFFFF;
    prev_time = func_00283CE0_4(*(short *)(self + 10) - 1);
    /* One statement: retail has no line label between the second call and the
       division, so no division padding (docs/build/compiler-notes.md). */
    *(int *)(self + 4) = func_00283D38_3(color, *(int *)(self + 4), prev_time / func_00283CE0_4(*(short *)(self + 10)));
}

/* func_002C3430 uses the hazard-label profile in 002C3430-fade.c. */


/* Fades a particle by a fixed step each frame, optionally stuck to another object, and removes it when fully faded. */
void part_update_step_fade(char *obj)
{
    char *sub = obj + 32;
    int w;
    int n;

    switch (*(unsigned char *)(sub + 2)) {
    case 2:
        *(float *)(obj + 16) = *(float *)(*(char **)(sub + 4) + 16) + *(float *)(sub + 16);
        *(float *)(obj + 20) = *(float *)(*(char **)(sub + 4) + 20) + *(float *)(sub + 20);
        *(float *)(obj + 24) = *(float *)(*(char **)(sub + 4) + 24) + *(float *)(sub + 24);
        break;
    case 1:
        goto tail;
    }
    w = *(int *)(obj + 4);
    n = (w >> 24);
    n = n - *(short *)(obj + 32);
    if (n <= 0) {
        Fccb147a4_FUN_002B9180(obj, sub);
        return;
    }
    *(int *)(obj + 4) = (w & 0xffffff) | (n << 24);
tail:
    if (*(unsigned char *)(sub + 3) != 0) {
        obj += 16;
        Fccb147a4_FUN_00300190(obj, obj);
    }
}


/* func_002C38E0 is in the -G8 sibling. */

/* Advances a spark, stops it on collision, and decays its RGBA channels. */
void UpdateCollidingSpark(char *particle) {
 float next_pos[4];char *motion;
 if(!particle)return;
 motion=particle+32;*(float *)(particle+12)+=-100.0f;
 FastVecAdd((char *)next_pos,particle+16,motion);
 if(*(float *)motion!=0 || *(float *)(motion+4)!=0 || *(float *)(motion+8)!=0){
 if(CollLine(particle+16,next_pos,2,particle,0)){*(U128 *)(particle+16)=*(U128 *)D_001BAFA0;vec_clear_128(motion);*(float *)(particle+12)+=*(float *)(particle+12);}
 else {*(U128 *)(particle+16)=*(U128 *)next_pos;if(*(float *)(motion+12)!=0)*(float *)(motion+8)+=*(float *)(motion+12);else *(float *)(motion+8)+=-0.0063f;}}
 if(*(float *)(motion+28)<=0 || FastDecTimer((short *)(particle+10)) || *(float *)(particle+12)<0 || next_pos[0]<0.01f || next_pos[1]<0.01f || next_pos[2]<0.01f){part_kill(particle);return;}
 *(float *)(motion+16)+=-0.01f;if(*(float *)(motion+16)<0)*(float *)(motion+16)=0;
 *(float *)(motion+20)+=-0.03001f;if(*(float *)(motion+20)<0)*(float *)(motion+20)=0;
 *(float *)(motion+24)+=-0.05f;if(*(float *)(motion+24)<0)*(float *)(motion+24)=0;
 if(*(float *)(motion+28)<0)*(float *)(motion+28)=0;
 *(int *)(particle+4)=gfx_pack_color_floats(*(float *)(motion+16),*(float *)(motion+20),*(float *)(motion+24),*(float *)(motion+28));particle[8]--;
}

/* func_002C3D80 uses the quadword-copy profile in 002C3D80-qcopy.c. */

/* Moves a particle, grows it, and drops its brightness one step each time its timer ticks. It is removed when fully faded. */
void part_update_growing_step_fade(char *particle)
{
    char *motion = particle + 32;

    Fa03721e9_FUN_00282CC0(particle + 16, particle + 16, motion);
    *(float *)(particle + 12) = *(float *)(particle + 12) + *(float *)(motion + 16);
    *(unsigned char *)(particle + 8) = *(unsigned char *)(particle + 8) + 1;
    if (--*(short *)(particle + 10) == 0) {
        *(unsigned int *)(particle + 4) = *(unsigned int *)(particle + 4) + 0xff000000;
        *(short *)(particle + 10) = 2;
    }
    if ((*(unsigned int *)(particle + 4) & 0xff000000) == 0)
        Fa03721e9_FUN_002B9180(particle);
}

/* func_002C3F88 uses the quadword-copy profile in 002C3F88-qcopy.c. */

/* Updates an attached spark and emits children; mode 1 orbits its owner.
 * The interleaved prototype preserves each EE argument register bank. */
void part_update_attached_spark_emitter(char *particle) {
 char *motion=particle+32; float v[4], w[4], rot[4], mat[16]; char *child;
 if(*(short *)(motion+28)==0) {
  if(moby_decrement_top_byte(particle+4,*(short *)(motion+26))) {part_kill(particle);return;}
  if(*(char **)(motion+12)) {
   v[0]=*(float *)(particle+32);v[1]=*(float *)(motion+4);v[2]=*(float *)(motion+8);
   FastVecScale(v,v,func_00283CE0_2(*(short *)(motion+24)));
   FastVecAdd(particle+16,*(char **)(motion+12)+16,(char *)v);
  }
  return;
 }
 if(FastDecTimer((short *)(particle+10)) || (*(short *)(particle+10)<10 && moby_decrement_top_byte(particle+4,16))) {part_kill(particle);return;}
 if(*(short *)(motion+28)==1)part_spawn_owned_spark(0,particle+16,0,0,10,0,*(signed char *)(particle+7),0);
 else {
  v[0]=*(float *)(motion);v[1]=*(float *)(motion+4);v[2]=*(float *)(motion+8);
  child=part_spawn_owned_spark(*(int *)(motion+12),particle+16,0,0,10,0,*(signed char *)(particle+7),v);
  if(child) *(short *)(child+56)=*(short *)(motion+24);
 }
 if(*(short *)(motion+28)==1) {
  qcopy(particle+16,*(char **)(motion+12)+16);
  v[0]=math_fast_sin_or_cos_a(*(float *)(motion+16))*2.25f;
  v[1]=math_fast_sin_or_cos_b(*(float *)(motion+16))*2.25f;
  v[2]=v[0]; v[0]=0;
  w[0]=math_fast_sin_or_cos_a(*(float *)(motion+20))*0.28f;
  w[1]=math_fast_sin_or_cos_b(*(float *)(motion+20))*0.28f;
  w[2]=w[0]; w[0]=0;
  vec_clear_128(rot);rot[1]=*(float *)(motion+16);
  euler_to_matrix(mat,rot);transform_vector(w,w,mat);
  FastVecAdd((char *)v,(char *)v,(char *)w);
  matrix_mul_vec3(v,v,*(char **)(motion+12)+192);
  FastVecAdd(particle+16,particle+16,(char *)v);
  *(float *)(motion+16)=FastAddRotations(*(float *)(motion+16),0.015998853370547295f);
  *(float *)(motion+20)=FastAddRotations(*(float *)(motion+20),0.07272206246852875f);
 }
}



/* Follows a selected attachment, randomizes its rotation, and fades by lifetime. */
extern float math_random_signed_float_range(float, float);
extern float IntToFloat(int);

void part_update_attached_rotating(char *object)
{
    char *motion = object + 0x20;
    int angle;
    float alpha;
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
        goto destroy;
    if (*(short *)(motion + 0x16) == 1) {
        qcopy(object + 0x10, *(char **)(*(char **)(motion + 0x1C) + 0x68) + 0xC0);
    } else if (*(short *)(motion + 0x16) == 3) {
        qcopy(object + 0x10, *(char **)(*(char **)(motion + 0x1C) + 0x68) + 0xD0);
    } else if (*(short *)(motion + 0x16) == 2) {
        qcopy(object + 0x10, *(char **)(*(char **)(motion + 0x1C) + 0x68) + 0x1E0);
    } else if (*(short *)(motion + 0x16) == 4) {
        float z = *(float *)(object + 0x18);
        qcopy(object + 0x10, *(char **)(motion + 0x1C) + 0x10);
        *(float *)(object + 0x18) = z + 0.2f;
    } else {
        FastVecAdd(object + 0x10, object + 0x10, motion);
    }
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f)
        goto destroy;
    angle = *(unsigned char *)(object + 8);
    angle += FloatToInt(math_random_signed_float_range(0.0f, 64.0f));
    if (angle > 255) angle -= 255;
    *(unsigned char *)(object + 8) = angle;
    if (FastDecTimer(object + 0xA)) {
destroy:
        part_kill(object);
        return;
    }
    alpha = IntToFloat(*(short *)(object + 0xA));
    {
        float scale = IntToFloat(*(short *)(motion + 0x14));
        alpha = alpha * *(float *)(motion + 0x10) * scale;
    }
    *(int *)(object + 4) = (FloatToInt(alpha) << 24) | *(int *)(motion + 0x18);
}

/* decrements a signed short counter and, at zero, rotates a 24-bit identifier beside it and reloads the counter; calls a helper when the identifier's top byte is clear */
void part_step_fade_timer(u8 *particle) {
    s16_F570cfb4b *timer_ptr = (s16_F570cfb4b *)(particle + 10);
    if (--*timer_ptr == 0) {
        *(s32 *)(particle + 4) += 0xff000000;
        *timer_ptr = 2;
    }
    if ((*(s32 *)(particle + 4) & 0xff000000) == 0) {
        func_002B9180_7(particle);
    }
}

/* Pulls toward a target, blends colour by distance, then advances through
 * three timed movement/fade phases. */
void part_update_attracted(char *particle) {
 char *motion=particle+32; float v[4],a[4],b[4];float distance;
 if(g_game_time[0]&1)particle[8]++;
 distance=fast_vec_dist(particle+16,D_00189F00);
 if(distance<5.0f && *(float *)(*(char **)(motion+24)+8)>0.0f) {
  FastVecSub(a,*(void **)(motion+24),particle+16);
  if(FastVecLength(a)>0.5f) {vec_scale_to_length(a,a,0.1f/distance);FastVecAdd(particle+16,particle+16,(char *)a);}
  else {vec_scale_to_length(a,a,0.005f);vec_pack_direction(a,(int *)(particle+36));}
 }
 distance=(2.5f-(distance-0.5f))*0.4f;
 if(distance>1.0f)distance=1.0f;else if(distance<0.0f)distance=0.0f;
 *(int *)(particle+4)=FastTweenColor(*(int *)(motion+8),*(int *)(motion+12),distance);
 if(*(short *)(motion+16)) {
  /* Retail writes zero to the hardware register at 0x10000000. */
  T0_COUNT=0;
  vec_decode_byte_color(v,motion);FastVecAdd(particle+16,particle+16,(char *)v);
  distance=func_00283CE0_2(*(short *)(particle+10))/func_00283CE0_2(*(short *)(motion+16));
  *(int *)(particle+4)=FastTweenColor(*(int *)(particle+4)&0xffffff,*(int *)(particle+4),1.0f-distance);
  if(FastDecTimer((short *)(particle+10))){*(short *)(motion+16)=0;*(short *)(particle+10)=*(short *)(motion+18);}
 } else if(*(short *)(motion+18)) {
  vec_decode_byte_color(a,motion);vec_decode_byte_color(b,motion+4);
  lerp_vector(v,b,a,func_00283CE0_2(*(short *)(particle+10))/func_00283CE0_2(*(short *)(motion+18)));
  FastVecAdd(particle+16,particle+16,(char *)v);
  if(FastDecTimer((short *)(particle+10))){*(short *)(motion+18)=0;*(short *)(particle+10)=*(short *)(motion+20);}
 } else {
  int color;
  vec_decode_byte_color(v,motion+4);FastVecAdd(particle+16,particle+16,(char *)v);
  color=*(int *)(particle+4)&0xffffff;
  *(int *)(particle+4)=FastTweenColor(color,*(int *)(particle+4),func_00283CE0_2(*(short *)(particle+10))/func_00283CE0_2(*(short *)(motion+20)));
  if(FastDecTimer((short *)(particle+10)))part_kill(particle);
 }
}


/* Spins a particle's frame and removes it when its size reaches zero. */
void part_update_spinning_frame(u8 *particle)
{
    f32 size = *(f32 *)(particle + 0x0C);
    *(u8 *)(particle + 0x08) = *(u8 *)(particle + 0x08) + *(u8 *)(particle + 0x38);
    if (size <= 0.0f) {
        *(f32 *)(particle + 0x0C) = 0.0f;
        part_kill(particle);
    }
}

/* func_002C4B50 is in 002BF6F0-c4b50.c. */

/* func_002C4D18 is in 002BF6F0-c4b50.c. */

/* Moves a particle with gravity and drag, keeps its size above a minimum while alive, and removes it when its timer ends. */
void part_update_dragged_falling(char *self)
{
    char *motion = self + 0x20;
    float len;
    float f;

    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + *(unsigned char *)(motion + 0x12);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(float *)(motion + 8) = *(float *)(motion + 8) - 3.0000000260770320892334e-03f;
    len = vec_length_xy(motion);
    /* Preserve both retail operations: floating-point rounding means subtracting
       and adding 1.0f cannot generally be simplified away. */
    f = len * 9.7000002861022949218750e-01f - 1.0f + 1.0f;
    f = f / len;
    *(float *)(self + 0x20) = *(float *)(self + 0x20) * f;
    *(float *)(motion + 4) = *(float *)(motion + 4) * f;
    if (FastDecTimer((short *)(self + 0xA)) == 0) {
        f = *(float *)(self + 0xC) + *(float *)(motion + 0x14) * 2.0f;
        *(float *)(self + 0xC) = f;
        if (f < 15000.0f)
            *(float *)(self + 0xC) = 15000.0f;
    } else {
        if (moby_decrement_top_byte(self + 4, *(int *)(motion + 0x1C)) != 0) {
            *(int *)(self + 0xC) = 0;
            part_kill(self);
        }
    }
}


extern float func_00283CE0_2(int v);
extern int func_00283CF0_6(float f);
extern void func_00282CC0_17(char *dst, char *src, char *vec);
extern int func_00282978_9(char *p);
extern void func_002B9180_13(char *self);


/* The particle update: the quad at 0x20 is copied to the stack, the value of
   the helper at 0xA is divided by the copy's fourth float, the two scaled
   results are packed into the word at 4 and the byte at 8. */
void part_update_scaled_color(char *self)
{
    V4_Fc3cb9262 vec;
    float divisor;
    float ratio;
    int packed;

    vec = *(V4_Fc3cb9262 *)(self + 0x20);
    divisor = ((float *)&vec)[3];
    ((float *)&vec)[3] = 0.0f;
    ratio = func_00283CE0_2(*(short *)(self + 0xA)) / divisor;
    packed = func_00283CF0_6(ratio * 38.0f);
    *(int *)(self + 4) = (packed << 24) | 0x808080;
    packed = func_00283CF0_6(ratio * 33.0f);
    *(char *)(self + 8) = (char)packed;
    func_00282CC0_17(self + 0x10, self + 0x10, (char *)&vec);
    if (func_00282978_9(self + 0xA) != 0) {
        func_002B9180_13(self);
    }
}

/* func_002C5120 is in 002BF6F0-c5120-g8.c. */


/* Shrinks and fades a particle each frame and removes it when it leaves the world or its timer ends. */
void part_update_shrinking_fade(Obj_F7cacd225 *particle)
{
    int fade_mode;

    if (particle->f16 < 2.0f || particle->f16 > 1021.0f ||
        particle->f20 < 2.0f || particle->f20 > 1021.0f ||
        particle->f24 < 2.0f || particle->f24 > 1021.0f ||
        F7cacd225_FUN_00282978(&particle->s10) != 0) {
        F7cacd225_FUN_002B9180((char *)particle);
        return;
    }
    fade_mode = particle->f32;
    if (fade_mode != 0) {
        particle->f12 = particle->f12 * 0.99f;
        particle->f4 = F7cacd225_FUN_00283D38(0x30FFFFFF, particle->f4, F7cacd225_FUN_00283CE0(particle->s10 - 1) / F7cacd225_FUN_00283CE0(particle->s10));
    } else {
        particle->f12 = particle->f12 * 0.95f;
        particle->f4 = F7cacd225_FUN_00283D38(0x603F1008, particle->f4, F7cacd225_FUN_00283CE0(particle->s10 - 1) / F7cacd225_FUN_00283CE0(particle->s10));
    }
}

/* func_002C56B0 uses the quadword-copy profile in 002C56B0-qcopy.c. */

/* Updates a two-step effect: first a burst that makes sparks and hits things nearby, then a fading ember. */
void part_update_burst_ember(char *particle) {
 char *motion=particle+32; SplitVector v; struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; short mask; float scale; int last; } c; int i; float progress,total,speed;
 switch(*(unsigned char *)(motion+20)) {
 case 0:
  for(i=0;i<*(unsigned char *)(motion+19);i++) {
   qcopy(&v,particle+16);
   vec_add_random_offset(&v,0.05f);
   speed=1.0f;
   if(*(short *)(particle+10)<10)speed=func_00283CE0_2(*(short *)(particle+10))*0.1f;
   part_spawn_debris_two_mode(&v,0,1,*(short *)(motion+16),*(unsigned char *)(motion+19),*(unsigned char *)(motion+21),*(int *)(motion+24),*(float *)(motion+28),speed);
  }
  if(FastDecTimer((short *)(particle+10)))part_kill(particle);
  vec_clear_128(&c);
  { ParticleHero2C58A8 *hero=(ParticleHero2C58A8 *)g_hero_state;
  c.owner=hero->owner;c.flags=0x10000;c.mode=2;c.mask=0x820;c.enabled=1;c.scale=1.0f;c.last=0; }
  if((g_game_time[0]+*(unsigned char *)(motion+23))%10==0)
   coll_process_hit(0.2f,particle+16,16,(int)c.owner,(int)&c);
  break;
 case 1:
  FastVecAdd(particle+16,particle+16,motion);
  total=func_00283CE0_2(*(unsigned char *)(motion+21));
  progress=(total-func_00283CE0_2(*(short *)(particle+10)))/total;
  *(int *)(particle+4)=FastTweenColor((*(unsigned char *)(motion+22)<<24)|0x4060,0x8fafff,progress);
  if(progress<0.6f)*(float *)(particle+12)+=9030.0f;else *(float *)(particle+12)-=16800.0f;
  particle[2]=D_001F2628[func_001163B0()&7];
  if((((particle-D_001B1D90[0])>>6)&1))particle[8]++;else particle[8]--;
  if(FastDecTimer((short *)(particle+10)))part_kill(particle);
  break;
 }
}


/* func_002C5B70 uses the quadword-copy profile in 002C5B70-qcopy.c. */

/* Adapted from RAC1 effect_particle_updates.c; measured against RAC2 retail. */
/* Updates a fading spark like the other splitting sparks but with lighter gravity. It splits, bounces and fades out. */
void part_update_split_spark_low_gravity(FadeSplitParticle *particle) {
    SplitVector new_vel, next_pos;
    FadeSplitCollision collision;
    FadeSplitMotion *motion = &particle->e;
    FadeSplitParticle *child;
    f32 spread, neg_spread, alpha, life_ratio;
    s32 hit;
    u8 flags;
    u8 *table;

    if (particle->hA != 0 && FastDecTimer(&particle->hA)) {
        motion->b18 |= 0x88;
        spread = particle->fC * 0.0000011111111462014378f;
        particle->fC *= 0.8f;
        neg_spread = -spread;
        func_00282D30_12((char *)&new_vel, (char *)motion, math_random_float_range(0.5f, 0.7f));
        next_pos.f[0] = particle->pos.f[0] + math_random_float_range(neg_spread, spread);
        next_pos.f[1] = particle->pos.f[1] + math_random_float_range(neg_spread, spread);
        next_pos.f[2] = particle->pos.f[2] + math_random_float_range(neg_spread, spread);
        new_vel.f[0] += math_random_float_range(-motion->v.f[0] * 0.2f, motion->v.f[0] * 0.2f);
        new_vel.f[1] += math_random_float_range(-motion->v.f[1] * 0.2f, motion->v.f[1] * 0.2f);
        new_vel.f[2] += math_random_float_range(-motion->v.f[2] * 0.2f, 0.0f);
        child = (FadeSplitParticle *)part_spawn_smoke_alt((char *)&next_pos, (char *)&new_vel, 0x88, motion->x1C);
        if (child) {
            child->hA = 2;
            child->fC = particle->fC;
        }
        func_00282D30_12((char *)motion, (char *)motion, math_random_float_range(0.5f, 0.7f));
        motion->v.f[0] += math_random_float_range(-motion->v.f[0] * 0.2f, motion->v.f[0] * 0.2f);
        motion->v.f[1] += math_random_float_range(-motion->v.f[1] * 0.2f, motion->v.f[1] * 0.2f);
        motion->v.f[2] += math_random_float_range(-motion->v.f[2] * 0.2f, 0.0f);
        particle->pos.f[0] += math_random_float_range(neg_spread, spread);
        particle->pos.f[1] += math_random_float_range(neg_spread, spread);
        particle->pos.f[2] += math_random_float_range(neg_spread, spread);
    }
    table = D_001F2688;
    { int index = particle->b2 - table[0];
    particle->b2 = table[(particle->hA + motion->h16 + index) & 7]; }
    FastVecAdd((char *)&new_vel, (char *)&particle->pos, (char *)motion);
    hit = 0;
    if (motion->h14 > 3) {
        FastVecSub(&next_pos, &particle->pos, motion);
    } else {
        next_pos.q = particle->pos.q;
    }
    func_00282D30_12((char *)&collision, (char *)&collision, 0.01f);
    flags = motion->b18;
    if (flags & 8) {
        if (!(particle->x4 & 0xFF000000)) goto kill;
        motion->b18 = flags | 8;
        if (!math_random_int_below(3)) hit = CollLine(&next_pos, &new_vel, 0, (void *)motion->x1C, 0) != 0;
    } else {
        collision.x10 = motion->x1C;
        collision.x1C = 1.0f;
        collision.v.q = motion->v.q;
        collision.x14 = 1;
        collision.x20 = 1;
        if (!math_random_int_below(3)) hit = CollLine(&next_pos, &new_vel, 0, (void *)motion->x1C, &collision) != 0;
    }
    if (hit) motion->b18 |= 8;
    else qcopy(&particle->pos, &new_vel);
    if (motion->b18 & 8) {
        motion->h16++;
        particle->fC -= 18055.5546875f;
        if (particle->fC <= 0.0f) {
        kill:
            part_kill(particle);
            return;
        }
    } else {
        particle->fC += 14444.4443359375f;
    }
    life_ratio = func_00283CE0_2(motion->h14);
    alpha = life_ratio * 0.000246913579758257f + 0.08f;
    if (alpha < 0.0f) alpha = 0.0f;
    if (0.08f < alpha) alpha = 0.08f;
    if (motion->b18 & 8) alpha /= (f32)motion->h16 * 0.142857149243355f + 1.0f;
    particle->x4 = (particle->x4 & 0xFFFFFF) | (FloatToInt(alpha * 256.0f) << 24);
    motion->v.f[2] += 0.0002f;
    if (motion->h14 > 25 || (motion->b18 & 8)) {
        motion->v.f[0] *= 0.95f;
        motion->v.f[1] *= 0.95f;
    }
    { u8 f2 = motion->b18;
    life_ratio = -1.0f;
    if (f2 & 1) life_ratio = 1.0f;
    if (f2 & 8) {
        motion->v.f[2] += 0.0002f;
        motion->x10 += life_ratio * (-0.01f) / func_00283CE0_2(motion->h16);
    } else {
        motion->x10 += life_ratio * (-0.01f);
    } }
    if (1.0f < motion->x10) motion->x10 -= 1.0f;
    if (motion->x10 < 0.0f) motion->x10 += 1.0f;
    particle->b8 = (s32)(motion->x10 * 256.0f);
}

/* func_002C6360 is in the -G8 sibling (its two globals are read through $gp). */

extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);

/* Pulses a particle's brightness in a wave over its lifetime and removes it when the timer ends. */
void part_update_pulsing_2(char *particle)
{
    float ratio;
    float wave;
    char *motion;

    if (particle == 0)
        return;
    motion = particle + 0x20;
    if (FastDecTimer((short *)(particle + 0x24)) != 0) {
        part_kill(particle);
        return;
    }
    ratio = IntToFloat(*(short *)(motion + 4)) / IntToFloat(*(short *)(motion + 6));
    wave = math_fast_sin_or_cos_b(ratio * 6.283186f);
    *(int *)(particle + 4) = (*(int *)(particle + 4) & 0x00FFFFFF)
                       + (FloatToInt(math_fabs(IntToFloat(*(int *)(motion + 0xC)) * wave)) << 24);
}

/* func_002C65A0 is in 002BF6F0-c65a0.c. */

/* If a probe call on a sub-object returns zero, folds a byte counter into the top byte of a packed word, rebuilds a 16-byte vector from two sub-records for a helper, then clamps a running float against a limit and accumulates two sub-record fields into the object. */
void part_update_spin_falling(char *obj)
{
    Vec16_F9a4b4d8b spin_vec;
    char *motion;
    char *pos_ptr;
    int packed;
    int spin;

    if (func_00282978_6(obj + 10) != 0) {
        func_002B9180_10(obj);
        return;
    }

    packed = *(int *)(obj + 4);
    motion = obj + 32;
    *(int *)(obj + 4) = (packed & 0x00ffffff) | (((packed >> 24) + *(unsigned char *)(motion + 20)) << 24);

    pos_ptr = obj + 16;
    spin_vec.f[0] = *(float *)(obj + 32);
    spin_vec.f[1] = *(float *)(motion + 4);
    spin_vec.f[2] = *(float *)(motion + 8);
    spin_vec.f[3] = 0.0f;
    func_00282CC0_21(pos_ptr, pos_ptr, (char *)&spin_vec);

    *(float *)(motion + 8) = *(float *)(motion + 8) - *(float *)(motion + 12);

    if (*(float *)(obj + 28) != 0.0f) {
        if (*(float *)(obj + 28) == 2.0f)
            func_00300190_2(pos_ptr, pos_ptr);
        *(float *)(obj + 28) = 2.0f;
    }
    spin = *(unsigned char *)(motion + 21);

    *(unsigned char *)(obj + 8) = *(unsigned char *)(obj + 8) + spin;
    *(float *)(obj + 12) += *(float *)(motion + 16);
}

typedef struct {
    int *colors;
    short *sizes;
    short *times;
    short last_index;
    short reserved0E;
    short lifetime;
    short reserved12;
    float scale;
} ParticleKeyframes;
extern int moby_forward_two_values_and_amount(int, int, float);

/* Moves a particle and steps through color and size keyframes over its lifetime. */
void part_update_keyframed(char *self)
{
    char *motion = self + 0x20;
    ParticleKeyframes *control = *(ParticleKeyframes **)(motion + 0x10);
    short elapsed;
    float duration, factor;
    func_00282D30_12(motion, motion, (control->scale - 1.0f) + 1.0f);
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    *(unsigned char *)(self + 8) += *(unsigned char *)(motion + 0x18);
    elapsed = control->lifetime - *(short *)(self + 0xA);
    if (control->times[*(short *)(motion + 0x14) + 1] < elapsed &&
        *(short *)(motion + 0x14) < control->last_index)
        ++*(short *)(motion + 0x14);
    duration = func_00283CE0_2(control->times[*(short *)(motion + 0x14) + 1] -
        control->times[*(short *)(motion + 0x14)]);
    factor = (float)(elapsed -
        control->times[*(short *)(motion + 0x14)]) / duration;
    *(int *)(self + 4) = moby_forward_two_values_and_amount(
        control->colors[*(short *)(motion + 0x14)],
        control->colors[*(short *)(motion + 0x14) + 1], factor);
    *(float *)(self + 0xC) =
        ((float)control->sizes[*(short *)(motion + 0x14)] +
         factor * (float)(control->sizes[*(short *)(motion + 0x14) + 1] - control->sizes[*(short *)(motion + 0x14)])) * 1000.0f;
    if (FastDecTimer((short *)(self + 0xA)))
        part_kill(self);
}

/* Follows a sound emitter's moby: fades its volume byte (the top byte of +4) up by 4
   toward the target while the moby is visible and active, else down by 4 to zero,
   then places the emitter at the moby (or at its joint, pulled 0.4 of the way toward
   the camera). A dead or dying moby (state 0xFE/0xFD) or none lets the emitter finish
   and frees it. */
typedef int TI128_2C6A08 __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x10];
    float pos[4];
    unsigned char state;
    unsigned char pad21[0x10];
    unsigned char visible;
    unsigned char pad32[2];
    unsigned short flags;
} EmitterMoby2C6A08;
typedef struct {
    EmitterMoby2C6A08 *moby;
    unsigned char pad4[2];
    short joint;
    unsigned char pad8[3];
    signed char target;
} EmitterRef2C6A08;
typedef struct {
    unsigned char pad0[4];
    int packed;
    unsigned char ticks;
    unsigned char pad9[7];
    float pos[4];
    EmitterRef2C6A08 ref;
} Emitter2C6A08;
extern float g_camera_eye_state[];
extern int moby_decrement_top_byte(void *, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Follows the particle's target (or one of its joints): the alpha fades towards the limit
   while the target is shown and out otherwise; a missing or dying target fades the particle
   out and frees it. The second read of the colour word is the retail copy kept by GCSE. */
void part_update_moby_following_emitter(Emitter2C6A08 *emitter)
{
    float joint[4];
    float toward[4];
    EmitterMoby2C6A08 *moby;
    int level;
    int target;
    EmitterRef2C6A08 *ref;

    if (emitter == 0)
        return;
    emitter->ticks++;
    ref = &emitter->ref;
    moby = ref->moby;
    if (moby == 0 || moby->state == 0xFE || moby->state == 0xFD) {
        if (moby_decrement_top_byte(&emitter->packed, 4) != 0)
            part_kill(emitter);
        return;
    }
    level = emitter->packed >> 24;
    target = ref->target;
    if (moby->visible != 0 && !(moby->flags & 2)) {
        if (level < target) {
            level += 4;
            if (target < level)
                level = target;
        }
    } else {
        level -= 4;
        if (level < 0)
            level = 0;
    }
    emitter->packed = (emitter->packed & 0xFFFFFF) | (level << 24);
    if (ref->joint == -1) {
        qcopy(emitter->pos, ref->moby->pos);
        return;
    }
    moby_transform_joint_to_world(ref->moby, ref->joint, joint);
    FastVecSub(toward, g_camera_eye_state, joint);
    vec_scale_to_length(toward, toward, 0.4f);
    FastVecAdd((char *)emitter->pos, (char *)joint, (char *)toward);
}


/* Creates a trail particle from a start point and a direction, with a short life and a size value. */
char *part_spawn_trail_2(void *origin, void *direction, int lifetime, float scale)
{
    V4_Fc3cb9262 vec;
    Particle6DD8 *particle;
    int fade;
    SplitVector *pos;

    particle = part_alloc(0x5A);
    if (particle != 0) {
        particle->x4 = 0x7FFFFFFF;
        particle->xC = 0x7FFFFFFF;
        fade = func_00283CF0_6(2.0f);
        particle->b9 = (char)(fade + 0x20);
        particle->b3 = 0x48;
        particle->b1 = 3;
        particle->b2 = *D_001F26A8;
        pos = &particle->v30;
        qcopy_nc(pos, direction);
        pos->f[3] = scale;
        qcopy_nc(&particle->v10, origin);
        vec_scale_to_length(&vec, pos, 0.9f);
        FastVecSub(&particle->v20, origin, &vec);
        particle->hA = lifetime;
        particle->v10.f[3] = 0.05f;
        particle->b8 = (char)(*(unsigned char *)&particle->hA - 0xF);
        particle->v20.f[3] = 2.0f;
    }
    return (char *)particle;
}


/* func_002C7050 is defined in 002BF6F0-trail-g8.c. */

extern int math_fast_float_d(short *);
/* Delay movement and the size/alpha tween until the secondary timer fires. */
void part_update_delayed_size_alpha(char *particle)
{
    char *motion = particle + 32;
    Vec16_F9a4b4d8b v;
    float progress;
    int elapsed, alpha;

    particle[8] += (unsigned char)motion[10];
    if (math_fast_float_d((short *)(motion + 24))) {
        elapsed = *(short *)(motion + 8) - *(short *)(particle + 10);
        if (elapsed < *(short *)(motion + 30)) {
            progress = (float)elapsed * 0.2f;
            *(float *)(particle + 12) = *(float *)(motion + 4) +
                ((*(float *)motion + *(float *)(motion + 4)) * 0.5f - *(float *)(motion + 4)) * progress;
            {
                int c2 = (unsigned char)motion[11] >> 1;
                int c = (unsigned char)motion[11];
                alpha = FloatToInt((float)c + (float)(c2 - c) * progress);
            }
        } else {
            progress = func_00283CE0_2(*(short *)(motion + 8) - 6);
            progress = (float)*(short *)(particle + 10) / progress;
            *(float *)(particle + 12) = *(float *)motion +
                ((*(float *)motion + *(float *)(motion + 4)) * 0.5f - *(float *)motion) * progress;
            alpha = FloatToInt((float)((unsigned char)motion[11] >> 1) * progress);
        }
        *(int *)(particle + 4) = (alpha << 24) | (*(int *)(particle + 4) & 0xffffff);
        particle_copy_xyz(v.f, (float *)(motion + 12));
        FastVecAdd(particle + 16, particle + 16, (char *)&v);
        if (*(float *)(particle + 16) < 2 || *(float *)(particle + 16) > 1021 ||
            *(float *)(particle + 20) < 2 || *(float *)(particle + 20) > 1021 ||
            *(float *)(particle + 24) < 2 || *(float *)(particle + 24) > 1021) {
            part_kill(particle);
            return;
        }
        if (FastDecTimer((short *)(particle + 10))) {
            part_kill(particle);
            return;
        }
    }
    if (*(float *)(particle + 28) != 0) {
        if (*(float *)(particle + 28) == 2.0f)
            func_00300190_2(particle + 16, particle + 16);
        *(float *)(particle + 28) = 2.0f;
    }
}

/* Grows a particle and lets it fall, fading its color, until its timer ends. */
void part_update_growing_falling(char *particle)
{
    V4_Fc3cb9262 buf;
    char *motion = particle + 32;
    float size;
    float growth;
    float fall_speed;

    growth = *(float *)(motion + 16) + 1.0000000474974513053894e-03f;
    fall_speed = *(float *)(motion + 8) - 3.0000000260770320892334e-03f;
    *(float *)(motion + 16) = growth;
    *(float *)(motion + 8) = fall_speed;
    size = *(float *)(motion + 20) * growth * 2.1000000000000000000000e+05f;
    buf = *(V4_Fc3cb9262 *)motion;
    *(float *)(particle + 12) = size;
    Fc3cb9262_FUN_00282CC0(particle + 16, particle + 16, (char *)&buf);
    *(int *)(particle + 4) = (Fc3cb9262_FUN_00283CF0((float)*(short *)(particle + 10)) << 24) | 0x00FFD2D2;
    *(unsigned char *)(particle + 8) = *(unsigned char *)(particle + 8) + *(unsigned char *)(motion + 24);
    if (Fc3cb9262_FUN_00282978(particle + 10) != 0)
        Fc3cb9262_FUN_002B9180(particle);
}
