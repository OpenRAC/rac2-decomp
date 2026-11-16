#include "names.h"
/* func_PAL_L00_00391958: the PAL copy of func_L00_0038E880 (L00_0038E880-g8.c), the impact
 * burst (shards, splash, ring and sparks), with its frame counts and per-frame rates for 50 Hz.
 * The v1.01 notes:
 * Spill slots follow gcse's PRE hash-bucket order, S = (insns at gcse / 2) | 1;
 * retail's order of the &random/&shard reaching registers (0xC8/0xCC) needs
 * S = 253. The set-once constant locals and per-site copies of object, data,
 * normal, velocity, scale, height and the colour channels each add one insn at
 * gcse and leave the final code unchanged (cprop folds them).
 */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef union { BurstQuad q; float f[4]; } BurstVector;
typedef struct { BurstQuad q[5]; } BurstTemplate __attribute__((aligned(16)));
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xDB]; } BurstWeapon;
typedef struct { char pad[0x160]; float shake; int unused; int duration, timer; } BurstCamera;
typedef struct { char pad[0x2C]; unsigned char *texture; } BurstParticles;

extern BurstTemplate g_particle_packet_template;
extern unsigned char g_item_slot_to_record[];
extern BurstWeapon g_weapon_l00_table[];
extern char g_camera_l00_position[];
extern BurstCamera g_scalar_transition_state;
extern BurstParticles g_effect_definitions;
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern void *part_spawn_spinning_debris(void *, void *, int, int, int);
extern float coll_get_ground_height_at_position(char *, char *);
extern void *part_spawn_bubble(char *, char *, float, float);
extern int snd_play_from_class_bank(int, int, void *, int);
extern float coll_probe_ground_height_below(void *, int, float);
extern float coll_get_ground_height_under_object(void *);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void *SpawnDistanceFadedParticle(void *, void *, unsigned int, float, float, int, float, int, int);
extern int math_lerp_int_fraction(int, int, float);
extern void *part_spawn_spark(void *, void *, int, int, float, int, int, int, int, int);
extern void *moby_spawn_template_effect(void *, void *, int, void *);
extern void moby_mark_spawned(void *);

void func_PAL_L00_00391958(char *object, BurstVector *velocity, BurstVector *normal)
{
    int *data = *(int **)(object + 0x68);
    BurstTemplate tmpl;
    BurstVector delta, projected, shard, random, drift, point;
    float scale, distance, height, ground;
    int c;
    BurstWeapon *w;
    char *pa, *pb, *pc, *pd, *pe, *pf;
    int *pg;
    int kind, z1, z2;

    tmpl = g_particle_packet_template;
    scale = 1.0f + IntToFloat(((BurstWeapon *)(g_item_slot_to_record[12] * 224 + (int)g_weapon_l00_table))->enabled != 0);
    FastVecScale(velocity, velocity, scale);
    FastVecSub(&delta, g_camera_l00_position, object + 0x10);
    distance = FastVecLength(&delta);
    pa = object;
    pb = object;
    pc = object;
    {
        int i;
        int lo = 50, hi = 100, none = 0;
        BurstVector *n1 = normal, *n2 = normal, *n3 = normal, *v1 = velocity;
        char *o1 = object;
        float s1 = scale;
        for (i = 9; i >= 0; --i) {
            int lifetime;
            random.q = 0;
            random.f[0] = math_random_float_range(-1.0f, 1.0f);
            random.f[1] = math_random_float_range(-1.0f, 1.0f);
            shard.q = random.q;
            vec_scale_to_length(&projected, n1, FastVecDot(&shard, n2));
            FastVecSub(&shard, &shard, &projected);
            vec_scale_to_length(&projected, n3, math_random_float_range(0.0f, 1.0f));
            FastVecAdd(&shard, &shard, &projected);
            vec_scale_to_length(&shard, &shard, s1 * math_random_float_range(3.5f, 6.5f) * 0.020000001f);
            FastVecAdd(&shard, &shard, v1);
            lifetime = math_random_int_range(lo, hi);
            w = &g_weapon_l00_table[g_item_slot_to_record[12]];
            part_spawn_spinning_debris(o1 + 0x10, &shard, lifetime, none,
            w->enabled != 0);
        }
    }
    *(float *)(pa + 0x18) += 1.0f;
    height = coll_get_ground_height_at_position(pc + 0x10, (char *)&shard);
    *(float *)(pb + 0x18) -= 1.0f;
    pd = object;
    pe = object;
    pf = object;
    pg = data;
    kind = 22;
    z1 = 0;
    z2 = 0;
    {
        int i;
        char *o2 = object;
        float h2 = height, s2 = scale;
        for (i = 149; i >= 0; --i) {
            drift.q = 0;
            drift.f[0] = math_random_float_range(-1.0f, 1.0f);
            drift.f[1] = math_random_float_range(-1.0f, 1.0f);
            drift.f[2] = math_random_float_range(-0.5f, 2.0f);
            random.q = drift.q;
            vec_scale_to_length(&random, &random, s2 * math_random_float_range(0.080000006f, 0.16000001f));
            part_spawn_bubble(o2 + 0x10, (char *)&random, math_random_float_range(0.05f, 0.1f) * 210000.0f, h2);
        }
    }
    pg[0] = 0;
    pd[0xBC] = 0;
    snd_play_from_class_bank(kind, z1, pe, z2);
    {
    short cr = 0x60;
    short cg = 0x60;
    short cb = 0x7F;
    int delay = 0;

    random.q = *(BurstQuad *)(pf + 0x10);
    random.f[2] += 3.5f;
    height = coll_probe_ground_height_below(&random, 0, 0.5f);
    ground = coll_get_ground_height_under_object(&random);
    if (height != ground && height - ground < 1.2f) {
        {
            int i;
            int count = 100, alpha = 0x16, on = 1;
            char *o3 = object;
            float h3 = height, h4 = height;
            short b1 = cb, b2 = cb, g1 = cg, g2 = cg, r1 = cr, r2 = cr;
            for (i = 0; i < count; i++) {
                float radius, angle, half;
                int c1, c2;
                point.q = 0;
                point.f[0] = math_random_float_range(-0.015000001f, 0.015000001f);
                point.f[1] = math_random_float_range(-0.015000001f, 0.015000001f);
                point.f[2] = math_random_float_range(0.080000006f, 0.28000003f);
                drift.q = point.q;
                radius = math_random_float_range(0.0f, 0.35f);
                half = 0.5f;
                angle = math_random_angle();
                point.f[0] = math_fast_sin_or_cos_a(angle) * radius;
                point.f[1] = math_fast_sin_or_cos_b(angle) * radius;
                point.f[2] = 0.0f;
                FastVecAdd(&point, &point, o3 + 0x10);
                radius *= 0.16000001f;
                point.f[2] = h3 + half;
                drift.f[2] -= radius;
                c1 = (alpha << 24) | (b1 << 16) | (g1 << 8);
                c2 = (b2 << 16) | (g2 << 8);
                SpawnDistanceFadedParticle(&point, &drift, delay, math_random_float_range(0.25f, 1.0f), h4,
                c1 | r1, 0.008f, c2 | r2, on);
            }
        }
        c = (0x7F << 24) | (cb << 16) | (cg << 8);
        {
            int i;
            int count = 20, full = 0x7F000000, black = 0, lmin = 75, lmax = 125, one = 1, ntex = -1, zero = 0;
            char *o4 = object;
            int c4 = c;
            short r3 = cr;
            float h5 = height;
            for (i = 0; i < count; i++) {
                int color1, color2;
                float life;
                color1 = math_lerp_int_fraction(full, c4 | r3, math_random_float_range(0.25f, 1.0f));
                color2 = math_lerp_int_fraction(black, ((cb / 2) << 16) | ((cg / 2) << 8) | (cr / 2), math_random_float_range(0.5f, 1.0f));
                point.f[0] = math_random_float_range(-3.0f, 3.0f);
                point.f[1] = math_random_float_range(-3.0f, 3.0f);
                point.f[2] = math_random_float_range(0.080000006f, 0.28000003f);
                vec_scale_to_length(&point, &point, math_random_float_range(1.5f, 3.0f) * 0.020000001f);
                point.f[2] = math_random_float_range(3.0f, 6.0f) * 0.020000001f;
                drift.q = *(BurstQuad *)(o4 + 0x10);
                drift.f[2] = h5;
                life = math_random_float_range(31500.001953125f, 52500.0f);
                part_spawn_spark(&drift, &point, color1, color2, life, math_random_int_range(lmin, lmax),
                one, *g_effect_definitions.texture, ntex, zero);
            }
        }
    }
    }
    {
        BurstCamera *camera = &g_scalar_transition_state;
        if (distance < 20.0f)
            camera->shake = 0.4f - distance * 0.0175f;
        else
            camera->shake = 0.050000011920928955f;
    }
    g_scalar_transition_state.duration = 21;
    g_scalar_transition_state.timer = 0;
    moby_spawn_template_effect(&tmpl, object + 0x10, 0, 0);
    moby_mark_spawned(object);
}
