#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; float f[0x980]; char *ptr[0x980]; TI128 q[0x260]; } Hero;
extern Hero D_00189E20;
typedef union { unsigned char b[0x400]; short h[0x200]; int i[0x100]; float f[0x100]; char *p[0x100]; TI128 q[0x40]; } Blk;
extern Blk D_0018BE30;
extern Blk D_00139568;
typedef struct {
    unsigned char pad0[4];
    unsigned char b4;
    unsigned char pad5[0x6B];
    float f70;
    unsigned char pad74[0x6C];
} ClassEntry;
extern ClassEntry D_L00_00262570[];
extern Blk D_L00_001BF200;
extern Blk D_L00_001FE940;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FE9F4[];
extern float D_L00_001B1008 __attribute__((sda));
extern float D_L00_001B1000 __attribute__((sda));
extern int D_L00_001B0FE4 __attribute__((sda));
extern int D_L00_001B0FEC __attribute__((sda));
extern int D_L00_001B0FF0 __attribute__((sda));
extern int D_L00_001B0FE8 __attribute__((sda));
extern int D_L00_001B0FF4 __attribute__((sda));
extern int D_L00_001B19C8 __attribute__((sda));

extern void func_002AFFD8(void *, void *, int);
extern void func_0029FCC0(int, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DF0(void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002AB1F0(void *);
extern int func_00282948(void *);
extern void func_00291450(int);
extern void func_0029F338(void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_002761F8(void *, void *, int, int, void *);
extern void func_L00_0040CCA0(void *, int, int);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern char *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void func_L00_0040B398(void *);
extern void ref_L00_0040BA30_00(void (*)(void *), void *);
extern void func_L00_0040C7D8(void *);

typedef struct {
    float v[4];
    char *owner;
    int flags;
    signed char b18;
    signed char b19;
    unsigned short h1A;
    float f1C;
    int f20;
} Hit;

typedef struct BeamVars {
    char pad00[0xC];
    struct BeamMoby *target;
    int timer;
    int pad14;
    int effect;
    int enabled;
    char pad20[0x10];
    float end[4];
    float aim[4];
    float dir[4];
    float left[4];
    float right[4];
} BeamVars;

typedef struct BeamMoby {
    char pad00[0x10];
    float pos[4];
    unsigned char state;
    char pad21[0x13];
    unsigned short flags;
    char pad36[0x32];
    BeamVars *vars;
    char pad6c[0x3E];
    unsigned short oClass;
} BeamMoby;

/* Per-frame update for the Clank Zapper beam (moby class 3800, Clank Zapper). It fires the beam from the hero, hurts what it hits, shows sparks and a light, then removes itself when the timer ends. */
void func_L00_0040BA30(BeamMoby *self)
{
    float oldPos[4];
    float upVec[4];
    float startPos[4];
    float beamDir[4];
    float pointA[4];
    float pointB[4];
    Hit hit;
    BeamVars *vars = self->vars;
    float angle;
    float tilt;
    int i;
    int j;
    int m;
    BeamMoby *lockedTarget;
    float leftFrac1, rightFrac1, size, leftFrac2, rightFrac2, sparkSize, leftFrac3, rightFrac3, handSize;
    int spin;
    int heroNode;
    ClassEntry *weaponTable;

    qcopy(oldPos, self->pos);
    ComputeViewDirection(self->pos, upVec, 1);
    heroNode = gHeroState.i[0x1314 / 4];
    TransformMobyJointToWorld(heroNode, 6, vars->left);
    TransformMobyJointToWorld(heroNode, 7, vars->right);
    qcopy(startPos, self->pos);
    FastVecSub(beamDir, vars->end, &gHeroState.b[0x2010]);
    vec_scale_to_length(beamDir, beamDir, 1.0f);
    angle = FastMatrixHelperA(*(float *)(gHeroState.ptr[0x18D0 / 4] + 0x10) - gHeroState.f[0x80 / 4],
                        *(float *)(gHeroState.ptr[0x18D0 / 4] + 0x14) - gHeroState.f[0x84 / 4]);
    if (angle < 1.5707964897155762f)
        tilt = RandomFloatRange(0.0f, -0.7853982448577881f);
    else
        tilt = RandomFloatRange(0.0f, 0.7853982448577881f);
    qcopy(vars->aim, &D_0018BE30);
    vars->aim[2] -= D_L00_001B1008;
    FastVecSub(vars->aim, vars->aim, &D_0018BE30);
    ApplyAxisRotationToQuaternion(vars->aim, vars->aim, beamDir, tilt);
    FastVecAdd(vars->aim, &D_0018BE30, vars->aim);
    lockedTarget = vars->target;
    if (lockedTarget != 0) {
        if (lockedTarget->state == 0xFE) {
            vars->target = 0;
        } else if (lockedTarget->state == 0xFD) {
            vars->target = 0;
        } else {
            FastVecSub(pointA, lockedTarget->pos, self->pos);
            if (FastVecLength(pointA) != 0.0f) {
                char *target = GetMobyPrivateValue0(vars->target);
                if (target != 0) {
                    FastVecScale(pointB, upVec, *(float *)(target + 0x10));
                    FastVecAdd(pointA, pointA, pointB);
                    FastVecLength(pointA);
                }
            } else {
                vars->target = 0;
            }
        }
    }
    angle = FastDiffRots(FastMatrixHelperA(*(float *)(gHeroState.ptr[0x18D0 / 4] + 0x10) - gHeroState.f[0x80 / 4],
                                      *(float *)(gHeroState.ptr[0x18D0 / 4] + 0x14) - gHeroState.f[0x84 / 4]),
                        gHeroState.f[0x98 / 4]);
    switch (self->state) {
    case 0:
        /* Each arm repeats its whole setup; the compiler cross-jumps the shared tails away. */
        weaponTable = gWeaponTable_L00;
        if (weaponTable[gItemSlotToRecord.b[9]].b4 != 0) {
            hit.flags = 0x110000;
            hit.owner = (char *)self;
            hit.f20 = 1;
            hit.f1C = weaponTable[gItemSlotToRecord.b[0x49]].f70;
            qcopy(hit.v, vars->dir);
            vec_scale_to_length(&hit, &hit, 0.2f);
            hit.b18 = 1;
            hit.b19 = 1;
            hit.v[3] = 5627.9248046875f;
            hit.h1A = self->oClass;
        } else {
            hit.flags = 0x10000;
            hit.owner = (char *)self;
            hit.f20 = 1;
            hit.f1C = weaponTable[gItemSlotToRecord.b[9]].f70;
            qcopy(hit.v, vars->dir);
            vec_scale_to_length(&hit, &hit, 0.2f);
            hit.b18 = 1;
            hit.b19 = 1;
            hit.v[3] = 5627.9248046875f;
            hit.h1A = self->oClass;
        }
        if (D_L00_001B1000 * 0.01745329424738884f < angle) {
            if (vars->enabled == 0)
                { MarkMobySpawned(self); return; }
            if (CollLine(&D_0018BE30, vars->end, 0, D_0018BE30.i[0x280 / 4], &hit) == 0)
                { MarkMobySpawned(self); return; }
            if (gCollisionResult.i[0x1C / 4] > 0)
                { MarkMobySpawned(self); return; }
            if (gCollisionResult.p[0x18 / 4] == 0)
                SpawnSmokeAndSparks(&gCollisionResult.b[0x20], 0xF, 1);
            else if (*(int *)(gCollisionResult.p[0x18 / 4] + 0x98) != 0)
                SpawnSmokeAndSparks(&gCollisionResult.b[0x20], 0xA, 1);
            PlaySoundFromClassBank(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = D_L00_001B0FE4;
        } else {
            if (CollLine(&D_0018BE30, vars->end, 0, D_0018BE30.i[0x280 / 4], &hit) == 0)
                { MarkMobySpawned(self); return; }
            if (gCollisionResult.i[0x1C / 4] > 0)
                { MarkMobySpawned(self); return; }
            if (gCollisionResult.p[0x18 / 4] == 0)
                SpawnSmokeAndSparks(&gCollisionResult.b[0x20], 0xF, 0);
            else if (*(int *)(gCollisionResult.p[0x18 / 4] + 0x98) != 0)
                SpawnSmokeAndSparks(&gCollisionResult.b[0x20], 0xA, 0);
            PlaySoundFromClassBank(0x15, 0, self, 0);
            self->state = 1;
            self->flags |= 0x41;
            vars->timer = D_L00_001B0FE4;
        }
        FastVecSub(pointA, vars->end, &D_0018BE30);
        vec_scale_to_length(pointA, pointA, FastVecLength(pointA) * 0.5f);
        FastVecAdd(pointA, &D_0018BE30, pointA);
        if (D_L00_001B1000 * 0.01745329424738884f < angle) {
            if (vars->enabled == 0)
                goto bounds;
            vars->effect = AllocateEffectSlot_L00_2(pointA, 10.0f, 0.0f, 1.0f, 0.1f, 0.1f);
        } else {
            vars->effect = AllocateEffectSlot_L00_2(pointA, 10.0f, 0.0f, 0.1f, 1.0f, 0.1f);
        }
        break;
    case 1:
        if (FastFloatHelperD(&vars->timer) != 0) {
            vars->target = 0;
            if (vars->effect != -1)
                FreePointLight(vars->effect);
            MarkMobySpawned(self);
            return;
        }
        if (D_L00_001B1000 * 0.01745329424738884f < angle) {
            if (vars->enabled != 0) {
                for (i = 0; i < 10; i++) {
                    char *part;
                    leftFrac1 = RandomFloatRange(0.0f, 1.0f);
                    FastVecSub(pointA, vars->end, vars->left);
                    vec_scale_to_length(pointA, pointA, leftFrac1 * FastVecLength(pointA));
                    FastVecAdd(pointA, vars->left, pointA);
                    rightFrac1 = RandomFloatRange(0.0f, 1.0f);
                    FastVecSub(pointB, vars->end, vars->right);
                    vec_scale_to_length(pointB, pointB, rightFrac1 * FastVecLength(pointB));
                    FastVecAdd(pointB, vars->right, pointB);
                    spin = RandomIntBelow(0xFF);
                    size = RandomFloatRange(0.35f, 0.5f);
                    part = SpawnGravityFadeParticle(pointA, D_L00_001A8F20, D_L00_001B0FEC, D_L00_001B0FF0, spin, 0x30, 0,
                                      size * 210000.0f, size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (D_L00_001FE940.p[0x184 / 4])[7];
                    part = SpawnGravityFadeParticle(pointB, D_L00_001A8F20, D_L00_001B0FEC, D_L00_001B0FF0, spin, 0x30, 0,
                                      size * 210000.0f, size * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (D_L00_001FE940.p[0x184 / 4])[7];
                }
                for (j = 0; j < 20; j++) {
                    char *part;
                    leftFrac2 = RandomFloatRange(0.0f, 1.0f);
                    FastVecSub(pointA, vars->end, vars->left);
                    vec_scale_to_length(pointA, pointA, leftFrac2 * FastVecLength(pointA));
                    FastVecAdd(pointA, vars->left, pointA);
                    rightFrac2 = RandomFloatRange(0.0f, 1.0f);
                    FastVecSub(pointB, vars->end, vars->right);
                    vec_scale_to_length(pointB, pointB, rightFrac2 * FastVecLength(pointB));
                    FastVecAdd(pointB, vars->right, pointB);
                    spin = RandomIntBelow(0xFF);
                    sparkSize = RandomFloatRange(0.2f, 0.35f);
                    pointA[0] += RandomSignedFloatRange(0.0f, 0.02f);
                    pointA[1] += RandomSignedFloatRange(0.0f, 0.02f);
                    pointA[2] += RandomSignedFloatRange(0.0f, 0.02f);
                    part = SpawnGravityFadeParticle(pointA, D_L00_001A8F20, D_L00_001B0FE8, D_L00_001B0FF4, spin, 0x30, 0,
                                      sparkSize * 210000.0f, sparkSize * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                    sparkSize *= 0.5f;
                    part = SpawnGravityFadeParticle(pointA, D_L00_001A8F20, D_L00_001B0FE8, 0x808080, spin, 0x30, 0,
                                      sparkSize * 210000.0f, sparkSize * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                    pointB[0] += RandomSignedFloatRange(0.0f, 0.02f);
                    pointB[1] += RandomSignedFloatRange(0.0f, 0.02f);
                    pointB[2] += RandomSignedFloatRange(0.0f, 0.02f);
                    part = SpawnGravityFadeParticle(pointB, D_L00_001A8F20, D_L00_001B0FE8, D_L00_001B0FF4, spin, 0x30, 0,
                                      sparkSize * 210000.0f, sparkSize * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                    sparkSize *= 0.5f;
                    part = SpawnGravityFadeParticle(pointB, D_L00_001A8F20, D_L00_001B0FE8, 0x808080, spin, 0x30, 0,
                                      sparkSize * 210000.0f, sparkSize * 42000.0f, 0.0f, 0);
                    if (part != 0)
                        part[2] = (D_L00_001FE940.p[0x184 / 4])[6];
                }
                if (vars->target != 0 && gFrameCounter_L00 % 5 == 0) {
                    char *part;
                    leftFrac3 = RandomFloatRange(0.0f, 1.0f);
                    FastVecSub(pointA, vars->end, vars->left);
                    vec_scale_to_length(pointA, pointA, leftFrac3 * FastVecLength(pointA));
                    FastVecAdd(pointA, vars->left, pointA);
                    rightFrac3 = RandomFloatRange(0.0f, 1.0f);
                    FastVecSub(pointB, vars->end, vars->right);
                    vec_scale_to_length(pointB, pointB, rightFrac3 * FastVecLength(pointB));
                    FastVecAdd(pointB, vars->right, pointB);
                    part = SpawnGravityFadeParticle(pointA, D_L00_001A8F20, 0x1E, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (part != 0)
                        part[2] = *D_L00_001FE9F4[0];
                    part = SpawnGravityFadeParticle(pointB, D_L00_001A8F20, 0x1E, 0x202080, 0, 0x40, 0,
                                      2100.0f, 126000.0078125f, 0.0f, 0);
                    if (part != 0)
                        part[2] = *D_L00_001FE9F4[0];
                }
            }
        } else {
            for (m = 0; m < 10; m++) {
                char *part;
                handSize = RandomFloatRange(0.25f, 0.4f) * 210000.0f;
                part = SpawnGravityFadeParticle(&gHeroState.b[0x2010], D_L00_001A8F20, 2, 0x108010, 2, 0x7F, 0x10,
                                  handSize, handSize, 0.0f, 0);
                if (part != 0)
                    part[2] = *D_L00_001FE940.p[0x64 / 4];
                part = SpawnGravityFadeParticle(&gHeroState.b[0x2010], D_L00_001A8F20, 2, 0x208020, -1, 0x7F, 0x10,
                                  handSize, handSize, 0.0f, 0);
                if (part != 0)
                    part[2] = *D_L00_001FE940.p[0x64 / 4];
            }
        }
        UpdateLightningStrands(self);
        ref_L00_0040BA30_00(DrawBeamSegmentsOrRibbons, self);
        break;
    }
bounds:
    if (self->pos[0] < 2.0f || self->pos[0] > 1021.0f ||
        self->pos[1] < 2.0f || self->pos[1] > 1021.0f ||
        self->pos[2] < 2.0f || self->pos[2] > 1021.0f)
        MarkMobySpawned(self);
}
