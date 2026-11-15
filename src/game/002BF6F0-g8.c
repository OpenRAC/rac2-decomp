#include "names.h"
extern int func_00282978(short *);
extern void func_00282CC0_17(char *, char *, char *);
extern void func_002B9180(void *);
extern unsigned char *D_001F2608[];
extern float D_001AA384 __attribute__((sda));
extern float D_L00_001AA708 __attribute__((sda));
extern float D_L00_001AA704 __attribute__((sda));
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern void func_002C19D8(char *, int, int, float, float);
extern void func_002BFB38(char *, char *, int, int);

#ifndef RAC2_T_V4_G8
#define RAC2_T_V4_G8
typedef int V4_G8 __attribute__((mode(TI)));
#endif

/* Moves a spinning particle, makes it swell at one point of its flicker cycle, and removes it when it sinks too low. */
void func_002C1FC0(char *self)
{
    char *state = self + 32;
    if (FastDecTimer((short *)(self + 10)))
        *(float *)(state + 8) -= *(float *)(state + 24);
    func_00282CC0_17(self + 16, self + 16, state);
    self[8] = (unsigned char)self[8] + *(unsigned char *)(state + 20);
    if ((unsigned char)self[2] == D_001F2608[0][0])
        *(float *)(self + 12) += D_001AA384 * 3500.000244140625f;
    if (*(float *)(self + 24) < *(float *)(state + 16))
        KillParticle(self);
}

extern float D_001AA380 __attribute__((sda));

/* Moves a particle inside a fixed box and fades it out in steps. It disappears when it leaves the box or has faded away. */
void func_002C1B38(char *self)
{
    char *motion = self + 0x20;
    func_00282CC0_17(self + 0x10, self + 0x10, motion);
    if (*(float *)(self + 0x10) < 2.0f || *(float *)(self + 0x10) > 1021.0f ||
        *(float *)(self + 0x14) < 2.0f || *(float *)(self + 0x14) > 1021.0f ||
        *(float *)(self + 0x18) < 2.0f || *(float *)(self + 0x18) > 1021.0f) {
        KillParticle(self);
        return;
    }
    *(float *)(self + 0x0C) += *(float *)(motion + 0x10);
    *(unsigned char *)(self + 8) += 1;
    if (*(float **)(motion + 0x14))
        *(float *)(self + 0x18) = **(float **)(motion + 0x14) + D_001AA380;
    if (--*(short *)(self + 0xA) == 0) {
        *(int *)(self + 4) -= 0x01000000;
        *(short *)(self + 0xA) = 4;
    }
    if ((*(unsigned int *)(self + 4) & 0xFF000000) == 0)
        KillParticle(self);
}

extern int D_001AA39C __attribute__((sda));
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern void func_002BCB00(char *, char *, int, int, int, int, int, int, int, float);

/* Moves a falling particle. When it hits the floor it breaks into smaller particles that fly off and then disappears. */
void func_002C38E0(char *self)
{
    char *motion = self + 0x20;
    char *position;
    int ttl;
    if (FastDecTimer((short *)(self + 0xA)))
        *(float *)(motion + 8) -= *(float *)(motion + 0x14);
    position = self + 0x10;
    func_00282CC0_17(position, position, motion);
    *(unsigned char *)(self + 8) += 2;
    if (*(float *)(self + 0x18) < *(float *)(motion + 0x10)) {
        if (RandomIntBelow(D_001AA39C - 1) == 0) {
            *(float *)(self + 0x18) = *(float *)(motion + 0x10);
            *(float *)(self + 0x20) *= RandomFloatRange(1.0f, 3.5f);
            *(float *)(motion + 4) *= RandomFloatRange(1.0f, 3.5f);
            *(float *)(motion + 8) *= RandomFloatRange(-1.0f, -1.5f);
            ttl = RandomIntRange(60, 120);
            SpawnSparkParticle_002BCB00(position, motion, *(int *)(self + 4), *(int *)(motion + 0x18),
                ttl, 0, *(unsigned char *)(self + 2), *(unsigned char *)(self + 3), 0,
                *(float *)(self + 0xC) * 0.5f);
        } else {
            *(float *)(self + 0x18) = *(float *)(motion + 0x10);
            *(float *)(self + 0x20) += RandomFloatRange(-5.0f, 5.0f) * 0.016666668f;
            *(float *)(motion + 4) += RandomFloatRange(-5.0f, 5.0f) * 0.016666668f;
            *(float *)(motion + 8) *= RandomFloatRange(-0.5f, -1.0f);
            ttl = RandomIntRange(30, 60);
            SpawnSparkParticle_002BCB00(position, motion, *(int *)(self + 4), *(int *)(motion + 0x18),
                ttl, 0, *(unsigned char *)(self + 2), *(unsigned char *)(self + 3), 0,
                *(float *)(self + 0xC) * 0.25f);
        }
        KillParticle(self);
    }
}

/* Advances one object: the two motion floats grow and are stored back, the
   object's vector is copied out and its fourth word cleared, the colour and
   the counter byte are rebuilt, and the object is finally handed to the
   helper twice when the motion is below the limit. */
void func_002C6360(char *self)
{
    char *particle = self;
    char *motion = self + 0x20;
    char *position = self + 0x10;
    V4_G8 velocityCopy;
    float value;
    float pull;
    float newZ;
    float growth;

    value = RandomFloatRange(-D_L00_001AA708, D_L00_001AA708);
    pull = D_L00_001AA704 + value;
    growth = *(float *)(motion + 0x10) + 0.0075f;
    newZ = *(float *)(motion + 8) - pull;
    value = *(float *)(motion + 0x14) * growth * 210000.0f;
    *(float *)(motion + 0x10) = growth;
    *(float *)(motion + 8) = newZ;
    velocityCopy = *(V4_G8 *)(particle + 0x20);
    *(float *)(particle + 0xC) = value;
    ((int *)&velocityCopy)[3] = 0;
    IntToFloat(*(short *)(particle + 0xA));
    *(unsigned int *)(particle + 4) = 0x55503020;
    *(unsigned char *)(particle + 8) = *(unsigned char *)(particle + 8) + *(unsigned char *)(motion + 0x1A);
    func_00282CC0_17(position, position, (char *)&velocityCopy);
    if (*(float *)(particle + 0x18) <= *(float *)(motion + 0x1C)) {
        if (RandomIntBelow(6) == 1)
            SpawnDriftingParticle_002C19D8(position, 0, -1, 0.4f, 210000.0f * 0.15f);
    }
    if (RandomIntBelow(6) == 1) {
        if (*(short *)(motion + 0x18) >= 0x32)
            SpawnSparkParticle_002BFB38(particle + 0x10, (char *)&velocityCopy, 1, 0x14);
    }
    *(unsigned short *)(motion + 0x18) = *(unsigned short *)(motion + 0x18) + 1;
    if (FastDecTimer((short *)(particle + 0xA)) != 0)
        KillParticle(particle);
}
