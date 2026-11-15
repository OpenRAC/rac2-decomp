#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char D_00189E20[];
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern unsigned char *func_00312D58(Vector *, float);
extern unsigned char *func_002C19D8(Vector *, float *, int, float, float);
extern unsigned char *func_002BFB38(Vector *, Vector *, int, int);

/* Emit ground dust and scattered debris around the resident player's position. */
void func_L00_002AABE0(int dust, int debris, int model) {
    Vector velocity;
    Vector position;
    float angle, radius, size;
    int kind, life;
    if (model) {
        unsigned char *origin = gHeroState + 0x80;
        velocity.q = *(Quadword *)origin;
        velocity.f[2] = *(float *)(origin + 0x2B0);
        SpawnScaledEffectMoby(&velocity, 2.25f);
    }
    if (dust > 0) {
        unsigned char *player = gHeroState;
        do {
            --dust;
            velocity.f[0] = *(float *)(player + 0x80) + RandomFloatRange(-0.3f, 0.3f);
            velocity.f[1] = *(float *)(player + 0x84) + RandomFloatRange(-0.3f, 0.3f);
            velocity.f[2] = *(float *)(player + 0x330);
            size = RandomFloatRange(0.3f, 0.6f);
            SpawnDriftingParticle_002C19D8(&velocity, (float *)(player + 0x330), -1, size, 5250.0f);
        } while (dust);
    }
    if (debris > 0) {
        int remaining = debris;
        unsigned char *player = gHeroState;
        do {
            --remaining;
            angle = RandomAngle();
            radius = RandomFloatRange(0.0f, 0.05000000447034836f);
            velocity.f[0] = FastSinOrCosA(angle) * radius;
            velocity.f[1] = FastSinOrCosB(angle) * radius;
            velocity.f[2] = RandomFloatRange(0.05000000447034836f, 0.13333334028720856f);
            position.f[0] = *(float *)(player + 0x80) + velocity.f[0] * 8.0f;
            position.f[1] = *(float *)(player + 0x84) + velocity.f[0] * 8.0f;
            position.f[2] = *(float *)(player + 0x330) - RandomFloatRange(0.0f, 0.2f);
            kind = RandomIntBelow(2);
            life = RandomIntRange(90, 120);
            SpawnSparkParticle_002BFB38(&position, &velocity, kind, life);
        } while (remaining);
    }
}
