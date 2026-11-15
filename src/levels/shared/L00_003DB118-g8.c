#include "include_asm.h"
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[112]; float scale; char tail[108]; } TableEntry;
typedef struct {
    char state[24];
    char *object;
    unsigned int detail;
    Vec position;
    Vec unk30;
    Vec normal;
} CollisionResult;
typedef struct {
    Vec pos;
    char pad10[8];
    unsigned char kind;
    unsigned char flag;
    unsigned short type;
    char pad1c[4];
    int count;
    char pad24[12];
} HitInfo;

extern unsigned char D_00139585 __attribute__((nosda));
extern char g_weapon_l00_table[];
extern CollisionResult g_collision_result;
extern struct { Vec position; Vec unk; Vec normal; } D_L00_001BF220;
extern Vec D_L00_001BF240;
extern char *g_hero_moby __attribute__((nosda));
extern float D_L00_001B03E4 __attribute__((sda));
extern float D_L00_001A8F20;

extern void vec_transform_or_copy(void *, void *);
extern void part_steer_effect_direction(int, void *, int);
extern void table_clear_entry_flag(int);
extern void vec_add_object_direction_scaled(void *a, void *b, float c);
extern void FastVecAdd(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float FastAddRotations(float, float);
extern void vec_clear_128(void *);
extern void euler_rotation_basis(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern int math_random_int_range(int, int);
extern void FastVecScale(void *, void *, float);
extern int func_001163B0(void);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void part_spawn_white_flash(void *, void *, int, float);
extern int math_fast_float_d(void *);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(char *, void *);
extern void StartAttachedEffect(void *, int, int);
extern void EmitRingAndDirectionalParticles(char *, int, void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern unsigned char *part_spawn_accelerated_puff(void *, void *, void *, float, int, int);
extern void gfx_draw_directional_sprite(char *, int, float, int, int, int, char *, float);
extern int math_random_int_below(int);
extern u8 *SpawnSpinningSparkParticle(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern int FloatToInt(float);
extern void effect_clear_finished_entry(char *);
extern int save_is_record_value(int, int);
extern void ref_L00_003DB118_00(void *, void *);
extern void part_l00_update_burst_effect();
extern void moby_mark_spawned(void *);

/* Flies a glowing projectile with a trail, hurts what it touches, then bursts into sparks. */
void UpdateCollidingTrailProjectile(char *self)
{
    Vec ray;
    Vec scale3;
    Vec push;
    char *timer;
    char *pv;
    int i;
    u8 *p;

    pv = *(char **)(self + 0x68);
    if (*(unsigned char *)(self + 0x20) != 0) {
        char *trail = pv + 0x10;
        vec_transform_or_copy(self + 0x10, self + 0x10);
        for (i = 3; i >= 0; i--) {
            vec_transform_or_copy(trail, trail);
            trail += 0x10;
        }
    }
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        for (i = 0; i < 4; i++) {
            qcopy(pv + 0x10 + i * 0x10, self + 0x10);
        }
        *(unsigned char *)(self + 0x20) = 1;
    case 1:
        {
        float a30[4] __attribute__((aligned(16)));
        float a40[4] __attribute__((aligned(16)));
        HitInfo hit;
        float spark[4] __attribute__((aligned(16)));
        ray.q = *(Quad *)(self + 0x10);
        timer = pv + 0x60;
        part_steer_effect_direction(*(int *)(pv + 0x78), pv, 0);
        FastVecAdd(self + 0x10, self + 0x10, pv);
        vec_add_object_direction_scaled(self + 0x10, pv, D_L00_001B03E4 * 0.00027777778f);
        for (i = 3; i > 0; i--) {
            lerp_vector(pv + 0x10 + i * 0x10, pv + 0x10 + i * 0x10, pv + i * 0x10, 0.2f);
        }
        *(Quad *)(pv + 0x10) = *(Quad *)(self + 0x10);
        *(float *)(pv + 0x64) = FastAddRotations(*(float *)(pv + 0x64), *(float *)(pv + 0x68));
        vec_clear_128(&scale3);
        scale3.f[1] = *(float *)(pv + 0x64) * 0.5f;
        scale3.f[0] = *(float *)(pv + 0x64) * 0.25f;
        scale3.f[2] = *(float *)(pv + 0x64) * 0.375f;
        euler_rotation_basis(self + 0xC0, &scale3);
        *(float *)(self + 0xC0) = *(float *)(self + 0xC0) * 0.4f * (math_fast_sin_or_cos_b(*(float *)(pv + 0x64)) + 2.0f);
        *(float *)(self + 0xD4) = *(float *)(self + 0xD4) * 0.5f * (math_fast_sin_or_cos_a(*(float *)(pv + 0x64)) + 2.0f);
        *(float *)(self + 0xE8) = *(float *)(self + 0xE8) * 0.75f * (math_fast_sin_or_cos_b(*(float *)(pv + 0x64)) + 2.0f);
        {
            int c = math_random_int_range(0x7F, 0xFF);
            *(int *)(self + 0x78) = ((c << 16) + (c << 8) + c) | 0x7F000000;
        }
        FastVecScale(&push, pv, -0.125f);
        if (func_001163B0() % 10 == 0) {
            vec_clear_128(a40);
            a30[0] = *(float *)(self + 0x10) + math_random_float_range(-0.15f, 0.15f);
            a30[1] = *(float *)(self + 0x14) + math_random_float_range(-0.15f, 0.15f);
            a30[2] = *(float *)(self + 0x18) + math_random_float_range(-0.15f, 0.15f);
            a40[0] = math_random_float_range(-0.025f, 0.025f);
            a40[1] = math_random_float_range(-0.025f, 0.025f);
            a40[2] = math_random_float_range(0.0f, 0.025f);
            vec_scale_to_length(a40, a40, 0.05f);
            part_spawn_white_flash(a30, a40, 0, -1.0f);
        }
        if (math_fast_float_d(timer) != 0) goto kill;
        {
        int collision;
        if (CollLine(&ray, self + 0x10, 0, self, 0) != 0)
            collision = 1;
        else
            collision = coll_test_point(self + 0x10, 0, self, 0.05f) != 0;
        if (collision) {
            CollisionResult *col = &g_collision_result;
            char *obj = col->object;
            if (obj != 0) {
                char *hero;
                if ((*(long long *)(obj + 0x30) & ((long long)0xA000 << 31)) && obj != (hero = g_hero_moby)
                    && *(short *)(obj + 0xAA) != MOBY_CLASS_LAVA_GUN) {
                    FastVecSub(a30, obj + 0x10, hero + 0x10);
                    vec_scale_to_length(a30, a30, 1.0f);
                    vec_scale_to_length(&hit, &hit, 0.116666675f);
                    make_hit_descriptor(&hit, self, 0x910000, a30, ((TableEntry *)g_weapon_l00_table)[D_00139585].scale);
                    {
                    Quad hitPosition = *(Quad *)a30;
                    hit.kind = 5;
                    hit.pos.q = hitPosition;
                    hit.pos.f[3] = 5627.925f;
                    hit.count = 1;
                    hit.flag = 1;
                    hit.type = *(unsigned short *)(col->object + 0xAA);
                    QueueMobyImpact(col->object, &hit);
                    }
                    StartAttachedEffect(col->object, 0x3F, *(int *)(self + 0xB8));
                    *(Quad *)a40 = *(Quad *)(col->object + 0x10);
                    a40[2] = a40[2] + 5.0f;
                    *(Quad *)a30 = *(Quad *)a40;
                    a30[2] = a30[2] - 10.0f;
                    *(Quad *)(self + 0x10) = col->position.q;
                    *(unsigned char *)(self + 0x20) = 2;
                    *(unsigned short *)(self + 0x34) |= 0x41;
                    *(Quad *)(pv + 0x50) = col->normal.q;
                    *(int *)(pv + 0x7C) = 1;
                    for (i = 0; i < 3; i++) {
                        vec_scale_to_length(spark, &D_L00_001BF240, math_random_float_range(0.16666667f, 0.33333334f));
                        spark[0] += math_random_float_range(-0.15f, 0.15f);
                        spark[1] += math_random_float_range(-0.15f, 0.15f);
                        spark[2] += math_random_float_range(-0.15f, 0.15f);
                        vec_scale_to_length(spark, spark, math_random_float_range(0.033333335f, 0.10000001f));
                        part_spawn_white_flash(self + 0x10, spark, 0, -1.0f);
                    }
                } else {
                    *(Quad *)(self + 0x10) = D_L00_001BF220.position.q;
                    *(unsigned char *)(self + 0x20) = 2;
                    *(unsigned short *)(self + 0x34) |= 0x41;
                    *(Quad *)(pv + 0x50) = D_L00_001BF220.normal.q;
                    for (i = 0; i < 6; i++) {
                        vec_scale_to_length(a30, &D_L00_001BF240, math_random_float_range(0.16666667f, 0.33333334f));
                        a30[0] += math_random_float_range(-0.15f, 0.15f);
                        a30[1] += math_random_float_range(-0.15f, 0.15f);
                        a30[2] += math_random_float_range(-0.15f, 0.15f);
                        vec_scale_to_length(a30, a30, math_random_float_range(0.033333335f, 0.10000001f));
                        part_spawn_white_flash(self + 0x10, a30, 0, -1.0f);
                    }
                }
            } else {
                *(Quad *)(self + 0x10) = col->position.q;
                *(unsigned char *)(self + 0x20) = 2;
                *(unsigned short *)(self + 0x34) |= 0x41;
                *(Quad *)(pv + 0x50) = col->normal.q;
                for (i = 0; i < 6; i++) {
                    vec_scale_to_length(a30, &D_L00_001BF240, math_random_float_range(0.16666667f, 0.33333334f));
                    a30[0] += math_random_float_range(-0.15f, 0.15f);
                    a30[1] += math_random_float_range(-0.15f, 0.15f);
                    a30[2] += math_random_float_range(-0.15f, 0.15f);
                    vec_scale_to_length(a30, a30, math_random_float_range(0.033333335f, 0.10000001f));
                    part_spawn_white_flash(self + 0x10, a30, 0, -1.0f);
                }
            }
            *(int *)(pv + 0x60) = 15;
            EmitRingAndDirectionalParticles(self, 15, self + 0x10, &D_L00_001BF240, 0.083333336f);
        }
        }
        }
        break;
    case 2:
        {
            int pick[2];
            float a40[4] __attribute__((aligned(16)));
            HitInfo hit;
            pick[0] = 0x44;
            pick[1] = 0x48;
            vec_scale_to_length(a40, pv, 2.0f);
            FastVecAdd(a40, a40, self + 0x10);
            FastVecCross(&hit, self + 0x10, a40);
            vec_scale_to_length(&hit, &hit, 1.0f);
            math_apply_axis_rotation_to_quat(&hit, &hit, pv, math_random_angle());
            part_spawn_accelerated_puff(self + 0x10, pv, &hit, math_random_float_range(0.008333334f, 0.050000004f), pick[func_001163B0() % 2], math_random_int_range(0x1E, 0x32));
            gfx_draw_directional_sprite(self + 0x10, 0x103080, math_random_float_range(0.75f, 1.2f), math_random_int_range(0x3F, 0x5F), 0xB, 2, pv, math_random_angle());
            gfx_draw_directional_sprite(self + 0x10, 0x103080, math_random_float_range(0.75f, 1.2f) * 0.75f, math_random_int_range(0x4F, 0x6F), 0xB, 2, pv, math_random_angle());
            gfx_draw_directional_sprite(self + 0x10, 0x103080, math_random_float_range(0.75f, 1.2f) * 0.5f, math_random_int_range(0x5F, 0x7F), 0xB, 2, pv, math_random_angle());
            if (math_fast_float_d(pv + 0x60) != 0) goto kill;
            if (*(int *)(pv + 0x7C) == 0) {
                for (i = 3; i > 0; i--) {
                    lerp_vector(pv + 0x10 + i * 0x10, pv + 0x10 + i * 0x10, pv + i * 0x10, 0.2f);
                }
            } else {
                for (i = 3; i > 0; i--) {
                    lerp_vector(pv + 0x10 + i * 0x10, pv + 0x10 + i * 0x10, pv + i * 0x10, 0.5f);
                }
            }
            *(Quad *)(pv + 0x10) = *(Quad *)(self + 0x10);
            *(float *)(self + 0x2C) = *(float *)(self + 0x2C) + 0.0005f;
        }
        break;
    }
    if (*(unsigned char *)(self + 0x20) == 1) {
        for (i = 0; i < 4; i++) {
            int n = math_random_int_below(5);
            p = SpawnSpinningSparkParticle(self + 0x10, 0.2f, 1.0f, 0.9f, math_random_int_below(2) ? -n : n, &D_L00_001A8F20, 210000.0f, 0x7F204080, 1);
            if (p) {
                u8 *t = p + 0x20;
                *(unsigned short *)(p + 0xA) = 5;
                p[9] = FloatToInt(4.0f) + 0x40;
                *(int *)(t + 4) = 2;
                t[0xA] = 0x30;
                t[0xB] = p[0xA];
            }
        }
        for (i = 0; i < 3; i++) {
            int n = math_random_int_below(3);
            p = SpawnSpinningSparkParticle(self + 0x10, 0.05f, 1.0f, 0.9f, math_random_int_below(2) ? -n : n, &D_L00_001A8F20, 157500.0f, 0x7F4080FF, 1);
            if (p) {
                u8 *t = p + 0x20;
                *(unsigned short *)(p + 0xA) = 2;
                p[9] = FloatToInt(4.0f) + 0x40;
                *(int *)(t + 4) = 2;
                t[0xA] = 0x40;
                t[0xB] = p[0xA];
            }
        }
        for (i = 0; i < 2; i++) {
            int n = math_random_int_below(3);
            p = SpawnSpinningSparkParticle(self + 0x10, 0.05f, 1.0f, 0.9f, math_random_int_below(2) ? -n : n, &D_L00_001A8F20, 105000.0f, 0x7FFFFFFF, 1);
            if (p) {
                u8 *t = p + 0x20;
                *(unsigned short *)(p + 0xA) = 2;
                p[9] = FloatToInt(4.0f) + 0x40;
                *(int *)(t + 4) = 2;
                t[0xA] = 0x60;
                t[0xB] = p[0xA];
            }
        }
    }
    effect_clear_finished_entry(self);
    if (save_is_record_value(*(int *)(pv + 0x74), *(int *)(pv + 0x70)) == 0) {
kill:
        table_clear_entry_flag(*(int *)(pv + 0x78));
        moby_mark_spawned(self);
    } else {
        ref_L00_003DB118_00(part_l00_update_burst_effect, self);
    }
}
