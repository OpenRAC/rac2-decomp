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
extern char D_L00_00262570[];
extern CollisionResult D_L00_001BF200;
extern struct { Vec position; Vec unk; Vec normal; } D_L00_001BF220;
extern Vec D_L00_001BF240;
extern char *D_0018C0B0 __attribute__((nosda));
extern float D_L00_001B03E4 __attribute__((sda));
extern float D_L00_001A8F20;

extern void func_00300190(void *, void *);
extern void func_002FEE70(int, void *, int);
extern void func_002FEE50(int);
extern void func_002FE880(void *a, void *b, float c);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern float func_00283B98(float, float);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern float func_00283198(float);
extern float func_00283180(float);
extern int func_002A7820(int, int);
extern void func_00282D30(void *, void *, float);
extern int func_001163B0(void);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_002BE278(void *, void *, int, float);
extern int func_00282948(void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(char *, void *);
extern void func_0032D758(void *, int, int);
extern void func_L00_003DC3E0(char *, int, void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_002A7940(void);
extern void func_002ACEC0(void *, void *, void *, float);
extern unsigned char *func_L00_00340CF8(void *, void *, void *, float, int, int);
extern void func_L00_003DCAC8(char *, int, float, int, int, int, char *, float);
extern int func_002A77E0(int);
extern u8 *func_002BDCE8(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern int func_00283CF0(float);
extern void func_L00_003DC2D0(char *);
extern int func_002B4038(int, int);
extern void ref_L00_003DB118_00(void *, void *);
extern void func_L00_003DC640();
extern void func_0029F338(void *);

/* Flies a glowing projectile with a trail, hurts what it touches, then bursts into sparks. */
void func_L00_003DB118(char *self)
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
        TransformVectorOrCopy(self + 0x10, self + 0x10);
        for (i = 3; i >= 0; i--) {
            TransformVectorOrCopy(trail, trail);
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
        SteerEffectDirection(*(int *)(pv + 0x78), pv, 0);
        FastVecAdd(self + 0x10, self + 0x10, pv);
        AddObjectDirectionScaled(self + 0x10, pv, D_L00_001B03E4 * 0.00027777778f);
        for (i = 3; i > 0; i--) {
            lerp_vector(pv + 0x10 + i * 0x10, pv + 0x10 + i * 0x10, pv + i * 0x10, 0.2f);
        }
        *(Quad *)(pv + 0x10) = *(Quad *)(self + 0x10);
        *(float *)(pv + 0x64) = FastAddRotations(*(float *)(pv + 0x64), *(float *)(pv + 0x68));
        ClearVector128(&scale3);
        scale3.f[1] = *(float *)(pv + 0x64) * 0.5f;
        scale3.f[0] = *(float *)(pv + 0x64) * 0.25f;
        scale3.f[2] = *(float *)(pv + 0x64) * 0.375f;
        euler_rotation_basis(self + 0xC0, &scale3);
        *(float *)(self + 0xC0) = *(float *)(self + 0xC0) * 0.4f * (FastSinOrCosB(*(float *)(pv + 0x64)) + 2.0f);
        *(float *)(self + 0xD4) = *(float *)(self + 0xD4) * 0.5f * (FastSinOrCosA(*(float *)(pv + 0x64)) + 2.0f);
        *(float *)(self + 0xE8) = *(float *)(self + 0xE8) * 0.75f * (FastSinOrCosB(*(float *)(pv + 0x64)) + 2.0f);
        {
            int c = RandomIntRange(0x7F, 0xFF);
            *(int *)(self + 0x78) = ((c << 16) + (c << 8) + c) | 0x7F000000;
        }
        FastVecScale(&push, pv, -0.125f);
        if (Rand() % 10 == 0) {
            ClearVector128(a40);
            a30[0] = *(float *)(self + 0x10) + RandomFloatRange(-0.15f, 0.15f);
            a30[1] = *(float *)(self + 0x14) + RandomFloatRange(-0.15f, 0.15f);
            a30[2] = *(float *)(self + 0x18) + RandomFloatRange(-0.15f, 0.15f);
            a40[0] = RandomFloatRange(-0.025f, 0.025f);
            a40[1] = RandomFloatRange(-0.025f, 0.025f);
            a40[2] = RandomFloatRange(0.0f, 0.025f);
            vec_scale_to_length(a40, a40, 0.05f);
            SpawnWhiteFlashParticle(a30, a40, 0, -1.0f);
        }
        if (FastFloatHelperD(timer) != 0) goto kill;
        {
        int collision;
        if (CollLine(&ray, self + 0x10, 0, self, 0) != 0)
            collision = 1;
        else
            collision = TestPointAgainstCollision(self + 0x10, 0, self, 0.05f) != 0;
        if (collision) {
            CollisionResult *col = &gCollisionResult;
            char *obj = col->object;
            if (obj != 0) {
                char *hero;
                if ((*(long long *)(obj + 0x30) & ((long long)0xA000 << 31)) && obj != (hero = gHeroMoby_0018C0B0)
                    && *(short *)(obj + 0xAA) != 0x5C9 /* Lava Gun */) {
                    FastVecSub(a30, obj + 0x10, hero + 0x10);
                    vec_scale_to_length(a30, a30, 1.0f);
                    vec_scale_to_length(&hit, &hit, 0.116666675f);
                    make_hit_descriptor(&hit, self, 0x910000, a30, ((TableEntry *)gWeaponTable_L00)[D_00139585].scale);
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
                        vec_scale_to_length(spark, &D_L00_001BF240, RandomFloatRange(0.16666667f, 0.33333334f));
                        spark[0] += RandomFloatRange(-0.15f, 0.15f);
                        spark[1] += RandomFloatRange(-0.15f, 0.15f);
                        spark[2] += RandomFloatRange(-0.15f, 0.15f);
                        vec_scale_to_length(spark, spark, RandomFloatRange(0.033333335f, 0.10000001f));
                        SpawnWhiteFlashParticle(self + 0x10, spark, 0, -1.0f);
                    }
                } else {
                    *(Quad *)(self + 0x10) = D_L00_001BF220.position.q;
                    *(unsigned char *)(self + 0x20) = 2;
                    *(unsigned short *)(self + 0x34) |= 0x41;
                    *(Quad *)(pv + 0x50) = D_L00_001BF220.normal.q;
                    for (i = 0; i < 6; i++) {
                        vec_scale_to_length(a30, &D_L00_001BF240, RandomFloatRange(0.16666667f, 0.33333334f));
                        a30[0] += RandomFloatRange(-0.15f, 0.15f);
                        a30[1] += RandomFloatRange(-0.15f, 0.15f);
                        a30[2] += RandomFloatRange(-0.15f, 0.15f);
                        vec_scale_to_length(a30, a30, RandomFloatRange(0.033333335f, 0.10000001f));
                        SpawnWhiteFlashParticle(self + 0x10, a30, 0, -1.0f);
                    }
                }
            } else {
                *(Quad *)(self + 0x10) = col->position.q;
                *(unsigned char *)(self + 0x20) = 2;
                *(unsigned short *)(self + 0x34) |= 0x41;
                *(Quad *)(pv + 0x50) = col->normal.q;
                for (i = 0; i < 6; i++) {
                    vec_scale_to_length(a30, &D_L00_001BF240, RandomFloatRange(0.16666667f, 0.33333334f));
                    a30[0] += RandomFloatRange(-0.15f, 0.15f);
                    a30[1] += RandomFloatRange(-0.15f, 0.15f);
                    a30[2] += RandomFloatRange(-0.15f, 0.15f);
                    vec_scale_to_length(a30, a30, RandomFloatRange(0.033333335f, 0.10000001f));
                    SpawnWhiteFlashParticle(self + 0x10, a30, 0, -1.0f);
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
            ApplyAxisRotationToQuaternion(&hit, &hit, pv, RandomAngle());
            SpawnAcceleratedPuffParticle(self + 0x10, pv, &hit, RandomFloatRange(0.008333334f, 0.050000004f), pick[Rand() % 2], RandomIntRange(0x1E, 0x32));
            DrawDirectionalSprite(self + 0x10, 0x103080, RandomFloatRange(0.75f, 1.2f), RandomIntRange(0x3F, 0x5F), 0xB, 2, pv, RandomAngle());
            DrawDirectionalSprite(self + 0x10, 0x103080, RandomFloatRange(0.75f, 1.2f) * 0.75f, RandomIntRange(0x4F, 0x6F), 0xB, 2, pv, RandomAngle());
            DrawDirectionalSprite(self + 0x10, 0x103080, RandomFloatRange(0.75f, 1.2f) * 0.5f, RandomIntRange(0x5F, 0x7F), 0xB, 2, pv, RandomAngle());
            if (FastFloatHelperD(pv + 0x60) != 0) goto kill;
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
            int n = RandomIntBelow(5);
            p = SpawnSpinningSparkParticle(self + 0x10, 0.2f, 1.0f, 0.9f, RandomIntBelow(2) ? -n : n, &D_L00_001A8F20, 210000.0f, 0x7F204080, 1);
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
            int n = RandomIntBelow(3);
            p = SpawnSpinningSparkParticle(self + 0x10, 0.05f, 1.0f, 0.9f, RandomIntBelow(2) ? -n : n, &D_L00_001A8F20, 157500.0f, 0x7F4080FF, 1);
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
            int n = RandomIntBelow(3);
            p = SpawnSpinningSparkParticle(self + 0x10, 0.05f, 1.0f, 0.9f, RandomIntBelow(2) ? -n : n, &D_L00_001A8F20, 105000.0f, 0x7FFFFFFF, 1);
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
    ClearFinishedTableEntry(self);
    if (IsSavedRecordValue(*(int *)(pv + 0x74), *(int *)(pv + 0x70)) == 0) {
kill:
        ClearEntryFlag(*(int *)(pv + 0x78));
        MarkMobySpawned(self);
    } else {
        ref_L00_003DB118_00(UpdateBurstEffect, self);
    }
}
