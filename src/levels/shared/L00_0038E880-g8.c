/* func_L00_0038E880: impact burst (shards, splash, ring and sparks).
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

extern BurstTemplate D_L00_002A26A0;
extern unsigned char D_00139568[];
extern BurstWeapon D_L00_00262570[];
extern char D_L00_001B8DC0[];
extern BurstCamera D_L00_001B8C80;
extern BurstParticles D_L00_001FE940;
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void *func_00308600(void *, void *, int, int, int);
extern float func_002A90F8(char *, char *);
extern void *func_002BF728(char *, char *, float, float);
extern int func_002E5DA0(int, int, void *, int);
extern float func_002A89A8(void *, int, float);
extern float func_002A8A20(void *);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_L00_0033AA40(void *, void *, unsigned int, float, float, int, float, int, int);
extern int func_L00_0031C998(int, int, float);
extern void *func_002BCB00(void *, void *, int, int, float, int, int, int, int, int);
extern void *func_00312B70(void *, void *, int, void *);
extern void func_0029F338(void *);

/* Makes the big burst when a shot lands: flying shards, splash, glowing sparks, sound and camera shake. Then removes the object. */
void func_L00_0038E880(char *object, BurstVector *velocity, BurstVector *normal)
{
    int *data = *(int **)(object + 0x68);
    BurstTemplate tmpl;
    BurstVector delta, projected, shard, random, drift, point;
    float scale, distance, height, ground;
    int shadeColor;
    BurstWeapon *weapon;
    char *pa, *pb, *pc, *pd, *pe, *pf;
    int *pg;
    int kind, z1, z2;

    tmpl = D_L00_002A26A0;
    scale = 1.0f + IntToFloat(((BurstWeapon *)(gItemSlotToRecord[12] * 224 + (int)gWeaponTable_L00))->enabled != 0);
    FastVecScale(velocity, velocity, scale);
    FastVecSub(&delta, gCameraPosition_L00, object + 0x10);
    distance = FastVecLength(&delta);
    pa = object;
    pb = object;
    pc = object;
    {
        int i;
        int lo = 60, hi = 120, none = 0;
        BurstVector *n1 = normal, *n2 = normal, *n3 = normal, *v1 = velocity;
        char *o1 = object;
        float s1 = scale;
        for (i = 9; i >= 0; --i) {
            int lifetime;
            random.q = 0;
            random.f[0] = RandomFloatRange(-1.0f, 1.0f);
            random.f[1] = RandomFloatRange(-1.0f, 1.0f);
            shard.q = random.q;
            vec_scale_to_length(&projected, n1, FastVecDot(&shard, n2));
            FastVecSub(&shard, &shard, &projected);
            vec_scale_to_length(&projected, n3, RandomFloatRange(0.0f, 1.0f));
            FastVecAdd(&shard, &shard, &projected);
            vec_scale_to_length(&shard, &shard, s1 * RandomFloatRange(3.5f, 6.5f) * (1.0f / 60.0f));
            FastVecAdd(&shard, &shard, v1);
            lifetime = RandomIntRange(lo, hi);
            weapon = &gWeaponTable_L00[gItemSlotToRecord[12]];
            SpawnSpinningDebrisMoby(o1 + 0x10, &shard, lifetime, none,
            weapon->enabled != 0);
        }
    }
    *(float *)(pa + 0x18) += 1.0f;
    height = GetGroundHeightAtPosition(pc + 0x10, (char *)&shard);
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
            drift.f[0] = RandomFloatRange(-1.0f, 1.0f);
            drift.f[1] = RandomFloatRange(-1.0f, 1.0f);
            drift.f[2] = RandomFloatRange(-0.5f, 2.0f);
            random.q = drift.q;
            vec_scale_to_length(&random, &random, s2 * RandomFloatRange(4.0f / 60.0f, 8.0f / 60.0f));
            SpawnBubbleParticle(o2 + 0x10, (char *)&random, RandomFloatRange(0.05f, 0.1f) * 210000.0f, h2);
        }
    }
    pg[0] = 0;
    pd[0xBC] = 0;
    PlaySoundFromClassBank(kind, z1, pe, z2);
    {
    short cr = 0x60;
    short cg = 0x60;
    short cb = 0x7F;
    int delay = 0;

    random.q = *(BurstQuad *)(pf + 0x10);
    random.f[2] += 3.5f;
    height = ProbeGroundHeightBelow(&random, 0, 0.5f);
    ground = GetGroundHeightUnderObject(&random);
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
                point.f[0] = RandomFloatRange(-0.012500001f, 0.012500001f);
                point.f[1] = RandomFloatRange(-0.012500001f, 0.012500001f);
                point.f[2] = RandomFloatRange(4.0f / 60.0f, 14.0f * (1.0f / 60.0f));
                drift.q = point.q;
                radius = RandomFloatRange(0.0f, 0.35f);
                half = 0.5f;
                angle = RandomAngle();
                point.f[0] = FastSinOrCosA(angle) * radius;
                point.f[1] = FastSinOrCosB(angle) * radius;
                point.f[2] = 0.0f;
                FastVecAdd(&point, &point, o3 + 0x10);
                radius *= 8.0f / 60.0f;
                point.f[2] = h3 + half;
                drift.f[2] -= radius;
                c1 = (alpha << 24) | (b1 << 16) | (g1 << 8);
                c2 = (b2 << 16) | (g2 << 8);
                SpawnDistanceFadedParticle(&point, &drift, delay, RandomFloatRange(0.25f, 1.0f), h4,
                c1 | r1, 1.0f / 180.0f, c2 | r2, on);
            }
        }
        shadeColor = (0x7F << 24) | (cb << 16) | (cg << 8);
        {
            int i;
            int count = 20, full = 0x7F000000, black = 0, lmin = 90, lmax = 150, one = 1, ntex = -1, zero = 0;
            char *o4 = object;
            int c4 = shadeColor;
            short r3 = cr;
            float h5 = height;
            for (i = 0; i < count; i++) {
                int color1, color2;
                float life;
                color1 = LerpIntegerFraction(full, c4 | r3, RandomFloatRange(0.25f, 1.0f));
                color2 = LerpIntegerFraction(black, ((cb / 2) << 16) | ((cg / 2) << 8) | (cr / 2), RandomFloatRange(0.5f, 1.0f));
                point.f[0] = RandomFloatRange(-3.0f, 3.0f);
                point.f[1] = RandomFloatRange(-3.0f, 3.0f);
                point.f[2] = RandomFloatRange(4.0f / 60.0f, 14.0f * (1.0f / 60.0f));
                vec_scale_to_length(&point, &point, RandomFloatRange(1.5f, 3.0f) * (1.0f / 60.0f));
                point.f[2] = RandomFloatRange(3.0f, 6.0f) * (1.0f / 60.0f);
                drift.q = *(BurstQuad *)(o4 + 0x10);
                drift.f[2] = h5;
                life = RandomFloatRange(31500.001953125f, 52500.0f);
                SpawnSparkParticle_002BCB00(&drift, &point, color1, color2, life, RandomIntRange(lmin, lmax),
                one, *D_L00_001FE940.texture, ntex, zero);
            }
        }
    }
    }
    {
        BurstCamera *camera = &D_L00_001B8C80;
        if (distance < 20.0f)
            camera->shake = 0.4f - distance * 0.0175f;
        else
            camera->shake = 0.050000011920928955f;
    }
    D_L00_001B8C80.duration = 25;
    D_L00_001B8C80.timer = 0;
    SpawnTemplateEffectMoby(&tmpl, object + 0x10, 0, 0);
    MarkMobySpawned(object);
}
