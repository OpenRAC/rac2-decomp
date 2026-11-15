#include "common.h"

extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, int, char *, float);
extern void func_002A7750(char *, int, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282C88(void *);
extern float func_002A7878(float, float);
extern void func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *func_002A9640(char *, int, int);
extern void func_002A8C28(void *, void *, float, int, float, float, int, int, int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_0029F338(char *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L11_0045FEF8(void);
extern float D_L11_001B22C8 __attribute__((sda));
extern int D_L11_001B22C0 __attribute__((sda));
extern char *D_L11_001C0D18 NOT_SDA;
extern int D_0018C0B4 NOT_SDA;

/* Updates a thrown projectile moby: it flies forward leaving a particle trail, then explodes on hitting something, running out of range, or when the level changes. Moby class 3707. */
void func_L11_0045FA68(char *moby)
{
    float next[4], velocity[4], zero[4];
    char *vars = *(char **)(moby + 0x68);
    char *target;
    float spreadA, spreadB;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), *(float *)(vars + 0x20) * 0.7f);
        *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), *(float *)(vars + 0x20) * 0.5f);
        *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), *(float *)(vars + 0x20));
        FastVecAdd(next, moby + 0x10, vars);
        if (TestPointAgainstCollision(next, 0, moby, D_L11_001B22C8) &&
            D_L11_001C0D18 && D_L11_001C0D18 != *(char **)(vars + 0x10)) {
            SetMobyState(moby, 1, -1);
            return;
        }
        qcopy(moby + 0x10, next);
        FastVecScale(velocity, vars, -0.5f);
        ClearVector128(zero);
        spreadA = RandomFloatRange(2.5f, 3.0f) * 210000.0f;
        spreadB = RandomFloatRange(0.2f, 0.4f) * 210000.0f;
        SpawnGravityFadeParticle(moby + 0x10, velocity, 15, D_L11_001B22C0, 3, 80, 0, spreadA, spreadB, 0.0f, 0);
        if (*(float *)(vars + 0x24) < *(float *)(moby + 0x18) && *(float *)(vars + 0x24) > 0.0f)
            SetMobyState(moby, 2, -1);
        target = FindOwnedEffectSlot(moby, 0x10000, 0);
        if (target) {
            *(float *)(vars + 0x14) -= *(float *)(target + 0x2C);
            if (*(float *)(vars + 0x14) <= 0.0f) SetMobyState(moby, 1, -1);
        }
        if (D_0018C0B4 == 111) SetMobyState(moby, 2, -1);
        break;
    case 1:
        SweepCollisionFromObject(moby, moby + 0x10, 3.0f, 0x10001, *(float *)(vars + 0x18), 1.0f, 0, 1, 0);
        SpawnExplosion(moby + 0x10, 1, 2, 2, 5, 10, 2, 1, 3.0f, 0.0f, 0, 1, 0, 0);
        MarkMobySpawned(moby);
        return;
    case 2:
        SpawnExplosion(moby + 0x10, 0, 10, 2, 10, 5, 2, 1, 2.0f, 0.0f, 0, 1, 0, 0);
        MarkMobySpawned(moby);
        return;
    }
    AddDrawCallbackToList3(SpawnTwoGlowEffects, moby);
}
