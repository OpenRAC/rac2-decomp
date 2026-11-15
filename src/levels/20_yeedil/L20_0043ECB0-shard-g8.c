#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { char pad[0x80]; Vec position; char pad90[0x40]; Vec top; } PlayerView;
typedef struct {
    Vec velocity;
    Vec trail[3];
    float radius, angle, targetRadius, targetZ, radiusSpeed, spin, zSpeed, baseZ, pad60;
    int timer;
    int reverse;
    int *clock;
    float scale;
} ShardState;
extern PlayerView D_00189E20;
typedef struct { char pad[0xF0]; float rot[3]; } Moby;
extern int D_L20_001A8F00, D_L20_001C0418[];
extern int D_L20_001B2AC8;
extern float D_L20_001B1F9C __attribute__((sda)), D_L20_001B1FA0 __attribute__((sda));
extern float D_L20_001B1FA4 __attribute__((sda)), D_L20_001B1FA8 __attribute__((sda));
extern float D_L20_001B1FAC __attribute__((sda)), D_L20_001B1FB0 __attribute__((sda));
extern float D_L20_001B1FB4 __attribute__((sda)), D_L20_001B1FB8 __attribute__((sda));
extern char D_L20_001B9FC0[];
extern void func_0029F338(void *);
extern float func_002AA548(float *, float *, float, float, float, float);
extern float func_002AA2E8(float *, float, float);
extern float func_00283180(float), func_00283198(float), func_00282C48(float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float);
extern float func_00283B98(float, float), func_00283248(float, float), func_00283C80(float, float);
extern float func_002A7878(float, float), func_00282E20(void *), func_00282DF0(void *);
extern int func_00282948(void *), func_00282C30(int);
extern void func_002A7750(void *, int, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_002A8C28(void *, void *, float, float, int, float, int, int, int);
extern void func_0032DA58(void *, void *, void *, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L20_0043F460(char *), func_L20_0043F510(void *);

/* Updates moby class 4509: a glowing shard that circles in place, then flies at the player, and breaks with sparks when it hits something. */
void func_L20_0043ECB0(unsigned char *moby)
{
    Vec old, delta, target;
    float speed;
    ShardState *shard = *(ShardState **)(moby + 0x68);

    if (D_L20_001A8F00 == 2) {
        MarkMobySpawned(moby);
        return;
    }
    qcopy(old, moby + 0x10);
    switch (moby[0x20]) {
    case 0:
        StepValueTowardTarget(&shard->radius, &shard->radiusSpeed, shard->targetRadius, D_L20_001B1F9C * 0.00027777778f, D_L20_001B1F9C * 0.00027777778f, D_L20_001B1FA0 * 0.016666668f);
        ((float *)(moby + 0x10))[0] = FastSinOrCosA(shard->angle) * shard->radius;
        ((float *)(moby + 0x10))[1] = FastSinOrCosB(shard->angle) * shard->radius;
        ((float *)(moby + 0x10))[2] = 0.0f;
        FastVecAdd(moby + 0x10, moby + 0x10, *(char **)(moby + 0xB8) + 0x10);
        ((float *)(moby + 0x10))[2] = old[2];
        if (FloatAbs(shard->radius - shard->targetRadius) < 0.5f) {
            speed = D_L20_001B1FA4 * 0.00029088825f;
            if (shard->reverse == 0)
                speed = -speed;
            ApproachValue(&shard->spin, speed, D_L20_001B1FA8 * 4.8481376e-06f);
            shard->angle = FastAddRotations(shard->angle, shard->spin);
            StepValueTowardTarget((float *)(moby + 0x18), &shard->zSpeed, shard->targetZ, D_L20_001B1FAC * 0.00027777778f, D_L20_001B1FAC * 0.00027777778f, D_L20_001B1FB0 * 0.016666668f);
            if (FloatAbs(((float *)(moby + 0x10))[2] - shard->targetZ) < 0.1f)
                shard->targetZ = shard->baseZ + RandomFloatRange(3.0f, 8.0f);
        }
        if (FastFloatHelperD(&shard->timer)
            && FastDiffRots(((Moby *)moby)->rot[2], FastMatrixHelperA(gHeroState.position[0] - ((float *)(moby + 0x10))[0], gHeroState.position[1] - ((float *)(moby + 0x10))[1])) < 0.62831855f) {
            FastVecSub(shard->velocity, moby + 0x10, old);
            shard->velocity[2] = 0.0f;
            SetMobyState(moby, 1, -1);
        } else if (subtract_integer_with_clamp(*shard->clock - D_L20_001B2AC8) >= 6) {
            FastVecSub(shard->velocity, moby + 0x10, old);
            shard->velocity[2] = 0.0f;
            SetMobyState(moby, 2, -1);
        }
        break;
    case 1:
        {
            float rate;

            { float zRate = D_L20_001B1FB0 * 0.016666668f; StepValueTowardTarget((float *)(moby + 0x18), &shard->zSpeed, shard->baseZ + 1.0f, D_L20_001B1FAC * 0.00027777778f, D_L20_001B1FAC * 0.00027777778f, zRate); }
            rate = D_L20_001B1FB8 * 0.016666668f;
            FastVecSub(target, gHeroState.top, moby + 0x10);
            target[2] = 0.0f;
            vec_scale_to_length(target, target, rate);
            FastVecSub(delta, target, shard->velocity);
            vec_scale_to_length(delta, delta, D_L20_001B1FB4 * 0.00027777778f);
            FastVecAdd(shard->velocity, shard->velocity, delta);
            vec_scale_to_length(shard->velocity, shard->velocity, rate);
            FastVecAdd(moby + 0x10, moby + 0x10, shard->velocity);
            if (FastDiffRots(((Moby *)moby)->rot[2], FastMatrixHelperA(gHeroState.position[0] - ((float *)(moby + 0x10))[0], gHeroState.position[1] - ((float *)(moby + 0x10))[1])) > 1.5707964f)
                SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        {
            float length = FastVecLength(shard->velocity);

            ApproachValue(&length, D_L20_001B1FB8 * 0.016666668f, 0.0027777778f);
            vec_scale_to_length(shard->velocity, shard->velocity, length);
            FastVecAdd(moby + 0x10, moby + 0x10, shard->velocity);
            if (moby[0x31] == 0) {
                MarkMobySpawned(moby);
                return;
            }
        }
        break;
    }
    FastVecSub(delta, moby + 0x10, old);
    ((Moby *)moby)->rot[2] = FastMatrixHelperA(delta[0], delta[1]);
    ((Moby *)moby)->rot[1] = -FastMatrixHelperA(vec_length_xy(delta), delta[2]);
    ((Moby *)moby)->rot[0] = FastAddRotations(((Moby *)moby)->rot[0], 0.052359887f);
    if ((D_L20_001B2AC8 & 3) == (((int)moby >> 8) & 3)) {
        int i;

        for (i = 2; i > 0; i--)
            qcopy(shard->trail[i], shard->trail[i - 1]);
        qcopy(shard->trail[0], moby + 0x10);
    }
    if (CollLine(old, moby + 0x10, 0, *(void **)(moby + 0xB8), 0)) {
        if (D_L20_001C0418[0]) {
            FastVecSub(target, D_L20_001B9FC0, moby + 0x10);
            vec_scale_to_length(target, target, 1.0f);
            SweepCollisionFromObject(*(void **)(moby + 0xB8), moby + 0x10, 2.0f, shard->scale, 0x10001, 1.0f, 0, 1, 0);
            SpawnBlastEffectMoby(moby, moby + 0x10, target, 0.0f);
        } else {
            SpawnExplosion(moby + 0x10, 0, 10, 20, 20, 20, 45, 0, 0.75f, 20.0f, 1, 0, 0, 0);
        }
        PlayMobySound(0, 0, moby);
        MarkMobySpawned(moby);
        return;
    }
    if (moby[0x31])
        SpawnShardParticle(moby);
    AddDrawCallbackToList3(AddMobyGlowTrail, moby);
}
