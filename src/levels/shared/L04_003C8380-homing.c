#include "common.h"
typedef int QuadWord __attribute__((mode(TI)));
extern void *func_0029EFD0(void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(char *, char *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern int func_00282948(void *);
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } SweepProbe;
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern char D_L04_001BFAE0[];
extern char D_L04_001BFB00[];
extern char D_L04_001A8F20[];
extern void func_00283028(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, unsigned int, int, float);
extern void func_L04_00358868(void *, unsigned int, int, int, float);
extern unsigned char *func_L04_0035F3E0(void *, void *, int, float);
extern void func_L04_003F9C60(void *, int);
extern void func_0029F338(void *);
extern float func_002A7AA8(float, float, float, float, float);
extern char D_L04_001B0448[];
extern char D_L04_001B9680[];
extern char D_L04_001B98D0[];
extern float func_00282E80(void *, void *);
extern int func_00278E78(void);
extern float func_00283B98(float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
typedef struct __attribute__((packed, aligned(4))) { long a; int b; } TurnRecord;

/* Moves a homing shot with its trail of followers; breaks up on contact, on timeout or out of bounds. */
void func_L04_003F9718(unsigned char *moby)
{
    float prevPos[4];
    TurnRecord turn = *(TurnRecord *)D_L04_001B0448;
    SweepProbe probe;
    float delta[4], sparkDir[4], spark[4], velocity[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68), *particle;
    int i, trailIndex, shotAge;
    unsigned char **trail;
    float scale, length;
    qcopy(prevPos, (moby + 0x10));
    FastVecAdd(moby + 0x10, moby + 0x10, vars);
    if (*(float *)(moby + 0x10) < 0 || *(float *)(moby + 0x14) < 0 ||
        *(float *)(moby + 0x18) < 0 || 64.0f < vec_distance_xy(moby + 0x10, D_L04_001B9680)) {
        DestroyMobyEffectsWithBurst(moby, 0);
        MarkMobySpawned(moby);
        return;
    }
    probe.owner = *(void **)(vars + 0x18);
    probe.flags = 0x30000;
    probe.radius = 13;
    probe.active = 1;
    *(QuadWord *)probe.v = *(QuadWord *)vars;
    FastVectorNormalizeHelper(&probe, &probe, 1);
    probe.v[2] = 1;
    probe.v[3] = 5627.9248046875f;
    probe.mode = 1;
    probe.enabled = 1;
    probe.kind = *(unsigned short *)(moby + 0xAA);
    if (FastFloatHelperD(vars + 0x10)) {
        DestroyMobyEffectsWithBurst(moby, 0);
        MarkMobySpawned(moby);
        return;
    }
    if (CollLine(prevPos, moby + 0x10, 0, *(void **)(vars + 0x18), &probe)) {
        if (!GetCollHitMaterial()) {
            if (*(int *)(vars + 0x10) >= 4) *(int *)(vars + 0x10) = 3;
        } else {
            qcopy((moby + 0x10), D_L04_001BFAE0);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)sparkDir = 0;
                sparkDir[0] = RandomFloatRange(-1, 1);
                sparkDir[1] = RandomFloatRange(-1, 1);
                sparkDir[2] = RandomFloatRange(-1, 1);
                *(QuadWord *)delta = *(QuadWord *)sparkDir;
                FastVectorNormalize(sparkDir, vars, D_L04_001BFB00);
                vec_scale_to_length((char *)delta, (char *)delta, FastVecLength(sparkDir) * 0.5f);
                FastVecAdd(sparkDir, sparkDir, delta);
                vec_scale_to_length((char *)sparkDir, (char *)sparkDir, RandomFloatRange(0.050000004f, 0.10000001f));
                SpawnVelocityParticle(moby + 0x10, sparkDir, 0x7F2F4F6F, RandomIntRange(10, 15), 30000);
            }
            DestroyMobyEffectsWithBurst(moby, 0);
            MarkMobySpawned(moby);
            return;
        }
    }
    *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), ((float *)&turn)[1]);
    shotAge = *(int *)(vars + 0x14) - *(int *)(vars + 0x10);
    if (shotAge < 13) scale = (IntToFloat(shotAge) / IntToFloat(13)) * 0.15f;
    else scale = 0.15f;
    FastVecSub(delta, prevPos, moby + 0x10);
    vec_scale_to_length((char *)delta, (char *)delta, scale);
    qcopy(sparkDir, (moby + 0x10));
    { unsigned char *head = *(unsigned char **)(vars + 0x1C);
      if (head) qcopy(head + 0x10, sparkDir); }
    for (trailIndex = 0; trailIndex < 16; trailIndex++) {
        particle = ((unsigned char **)(vars + 0x20))[trailIndex];
        if (particle) {
            FastVecAdd(particle + 0x10, sparkDir, delta);
            qcopy(sparkDir, (particle + 0x10));
            *(float *)(particle + 0x10) += RandomSignedFloatRange(0, 0.075f);
            *(float *)(particle + 0x14) += RandomSignedFloatRange(0, 0.075f);
            *(float *)(particle + 0x18) += RandomSignedFloatRange(0, 0.075f);
            FastVecScale(delta, delta, 0.85f);
        }
    }
    if (RandomIntBelow(5) == 0) {
        FastVecCross(spark, delta, D_L04_001B98D0);
        ApplyAxisRotationToQuaternion(spark, spark, delta, RandomSignedFloatRange(0, 3.1415927f));
        length = FastVecLength(spark);
        if (length != 0) {
            FastVecScale(velocity, spark, RandomFloatRange(0.008333334f, 0.033333335f) / length);
            SpawnVelocityParticle(moby + 0x10, velocity, 0x7F2F4F6F, RandomIntRange(10, 15), 30000);
        }
    }
}
