#include "common.h"

extern void func_00300190(void *, void *);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
typedef struct EffectParticle {
    unsigned char prefix[10];
    short life;
    unsigned char gap[20];
} EffectParticle;
typedef struct EffectParticleExtension {
    int color, mode;
    short spin;
    unsigned char alpha, life;
} EffectParticleExtension;
extern EffectParticle *func_002BDCE8(void *, float, float, float, int, void *, float, unsigned, int);
extern float D_L00_001A8F20[4] MACRO_ADDR;


extern void func_002AFFD8(void *, void *, int);
extern void func_L00_003252A8(void *, void *, int);
extern void func_002FEE70(int, void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0031D670(void *, void *, void *, float);
extern int func_002FE9D0(void *);
extern int func_00300540(int);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_0032D758(void *, int, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_003FF530(void *);
extern void func_002A9288(void *, float);
extern float func_00282DB0(void *, void *);
extern unsigned char D_0013958D[];
typedef struct EffectPlayer {
    unsigned char prefix[0x70];
    float scale;
    unsigned char suffix[0x6C];
} EffectPlayer;
extern EffectPlayer D_L00_00262570[];
extern void *D_0018C0B0[];
extern void *D_L00_001C3280[];
extern int D_L00_001A8FF0[] MACRO_ADDR, D_L00_001A8FF4[] MACRO_ADDR;
extern float D_L00_001B0C20 __attribute__((sda));
extern float D_L00_001B0C28 __attribute__((sda));
extern float D_L00_001B0C30 __attribute__((sda));
extern float D_L00_001B0C34 __attribute__((sda));
extern float D_L00_001B0C3C __attribute__((sda));
extern float D_L00_001B0C40 __attribute__((sda));
extern int D_L00_001B0C44 __attribute__((sda));
extern char D_L00_001BF230[];
extern unsigned char D_L00_001B0C48[8] NOT_SDA;

typedef int EffectQuad __attribute__((mode(TI)));
typedef union EffectVector { EffectQuad quad; float f[4]; } EffectVector;
typedef struct EffectState {
    EffectVector velocity, axis;
    int timer, bounces, trail, charged, rotation;
} EffectState;
typedef struct SweepQuery {
    EffectVector start, end, delta;
    void *owner;
    int *params;
    int mode;
    float radius, scale, extra;
    int field48, field4c, field50, hit, field58;
    float tolerance;
} SweepQuery;
typedef struct HitQuery {
    float pos[3], radius;
    void *owner;
    unsigned flags;
    unsigned char type, active;
    unsigned short classId;
    float scale;
    int enabled;
} HitQuery;

typedef struct EffectWorkspace {
    EffectVector normal, old;
    union { EffectVector point; int excluded[2]; } params;
    EffectVector tmp;
    SweepQuery query;
    HitQuery hit;
    EffectVector offset, step;
} EffectWorkspace;

/* Per-frame update of a bouncing weapon shot: it flies, bounces off walls, hurts what it hits and bursts into fragments. */
void func_L00_003FEEA0(char *self)
{
    EffectState *shot = *(EffectState **)(self + 0x68);
    EffectWorkspace work;
    int i, result, kind, swept;
    float radius, extra, speed, scale;
    float fadeRadius;
    int remaining;
    void **targets;
    ComputeViewDirection(self + 0x10, work.normal.f, 1);
    TransformVectorOrCopy(self + 0x10, self + 0x10);
    switch ((unsigned char)self[0x20]) {
    case 0:
        qcopy(work.old.f, self + 0x10);
        FastVecAdd(self + 0x10, self + 0x10, shot);
        SteerEffectDirection(shot->rotation, shot, 0);
        AddObjectDirectionScaled(self + 0x10, shot, 0.004055555909872055f);
        FastFloatHelperD(&shot->trail);
        if (shot->trail) {
            for (i = 0; i < 3; i++) {
                int id;
                EffectParticle *r;
                float x;
                float f;
                float third = 0.33329999446868896f;
                float one = 1.0f;
                *(EffectQuad *)work.tmp.f = *(EffectQuad *)(self + 0x10);
                LerpVector4(work.params.point.f, work.old.f, work.tmp.f, IntToFloat(i) * third);
                id = RandomIntBelow(6);
                if (RandomIntBelow(2)) {
                    id = -id;
                }
                x = (float)shot->trail / IntToFloat(50) * 65000.0f + 10000.0f;
                r = SpawnSpinningSparkParticle(work.params.point.f, 0.025f, one, one, id, D_L00_001A8F20, x, 0x80808080, 1);
                if (r) {
                    short life = 50;
                    EffectParticleExtension *extension = (EffectParticleExtension *)(r + 1);
                    r->life = life;
                    extension->mode = 2;
                    extension->alpha = 127;
                    { int l = r->life & 0xFF; extension->life = l; }
                }
            }
        }
        __builtin_memcpy(work.params.excluded, D_L00_001B0C48, 8);
        extra = 1.5f;
        if ((float)shot->bounces == 3.0f) {
            extra = 0.0f;
        }
        radius = D_L00_001B0C30;
        if (shot->charged) {
            radius = D_L00_001B0C3C;
        }
        qcopy(work.query.start.f, work.old.f);
        qcopy(work.query.end.f, self + 0x10);
        qcopy(work.query.delta.f, shot);
        work.query.params = work.params.excluded;
        work.query.owner = self;
        work.query.mode = 2;
        work.query.radius = radius;
        work.query.scale = (D_L00_001B0C20 - 1.0f) + 1.0f;
        work.query.extra = extra;
        work.query.field48 = 0;
        work.query.field4c = 0;
        work.query.field58 = 0;
        swept = CollideSweptSphere(&work.query);
        kind = GetWeaponGroup(work.query.hit);
        if (swept > 0 && (unsigned)(kind - 1) < 2) {
            SpawnShotFragments(self);
            MarkMobySpawned(self);
            return;
        }
        qcopy(self + 0x10, work.query.end.f);
        qcopy(shot, work.query.delta.f);
        RotateVectorByQuaternion(self + 0xC0, self + 0xC0, shot->axis.f);
        RotateVectorByQuaternion(self + 0xD0, self + 0xD0, shot->axis.f);
        RotateVectorByQuaternion(self + 0xE0, self + 0xE0, shot->axis.f);
        work.hit.owner = self;
        work.hit.flags = 0x830000;
        { EffectPlayer *pl = &gWeaponTable_L00[D_0013958D[0]]; work.hit.scale = pl->scale; }
        work.hit.enabled = 1;
        qcopy(work.hit.pos, shot);
        vec_scale_to_length(work.hit.pos, work.hit.pos, 1.0f);
        work.hit.type = 3;
        work.hit.radius = 5627.9248046875f;
        work.hit.classId = *(unsigned short *)(self + 0xAA);
        work.hit.active = 1;
        result = ProcessCollisionHit(self + 0x10, 1, gHeroMoby_0018C0B0[0], &work.hit, radius + 0.1f);
        if (result) {
            if (shot->charged) {
                if (result > 0) {
                    targets = gAreaHitTargets;
                    remaining = result;
                    do {
                        StartAttachedEffect(*targets, 0x4C, *(void **)(self + 0xB8));
                        targets++;
                    } while (--remaining);
                }
            } else {
                if (result > 0) {
                    targets = gAreaHitTargets;
                    remaining = result;
                    do {
                        StartAttachedEffect(*targets, 0x25, *(void **)(self + 0xB8));
                        targets++;
                    } while (--remaining);
                }
            }
            SpawnShotFragments(self);
            MarkMobySpawned(self);
            return;
        }
        if (swept > 0) {
            qcopy(work.tmp.f, shot);
            work.tmp.f[2] = 0;
            FastVecCross(work.tmp.f, work.tmp.f, work.normal.f);
            vec_scale_to_length(work.tmp.f, work.tmp.f, 1.0f);
            BuildAxisAngleQuaternion(shot->axis.f, work.tmp.f, RandomFloatRange(0.05235988646745682f, 0.10471977293491364f));
            PlayMobySound(1, 0, self);
            shot->bounces += 1;
            if (shot->bounces >= 4) {
                qcopy(self + 0x10, D_L00_001BF230);
                self[0x20] = 1;
                shot->timer = D_L00_001B0C44;
                speed = D_L00_001B0C28 * 0.05235988646745682f;
                if (shot->charged) {
                    speed *= D_L00_001B0C34;
                }
                ForwardObjectPositionCall(self, work.offset.f, 1);
                scale = FastVecDot(work.offset.f, shot);
                FastVecScale(work.step.f, work.offset.f, scale);
                FastVecSub(shot, shot, work.step.f);
                vec_scale_to_length(shot, shot, speed);
                qcopy(shot->axis.f, work.tmp.f);
                shot->axis.f[3] = 0.05235988646745682f;
            }
        }
        break;
    case 1:
        FastVecAdd(self + 0x10, self + 0x10, shot);
        BuildAxisAngleQuaternion(work.old.f, shot->axis.f, shot->axis.f[3]);
        RotateVectorByQuaternion(self + 0xC0, self + 0xC0, work.old.f);
        RotateVectorByQuaternion(self + 0xD0, self + 0xD0, work.old.f);
        RotateVectorByQuaternion(self + 0xE0, self + 0xE0, work.old.f);
        scale = (D_L00_001B0C40 - 1.0f) + 1.0f;
        shot->axis.f[3] *= scale;
        FastVecScale(shot, shot, scale);
        if (FastFloatHelperD(&shot->timer)) {
            SpawnShotFragments(self);
            MarkMobySpawned(self);
            return;
        }
        break;
    }
    fadeRadius = D_L00_001B0C28;
    if (shot->charged) {
        fadeRadius *= D_L00_001B0C34;
    }
    if (D_L00_001A8FF0[0] == 0 && D_L00_001A8FF4[0] == 0) {
        QueueGroundShadow(self, fadeRadius);
    }
}
