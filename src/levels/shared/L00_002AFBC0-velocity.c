#include "common.h"

typedef int Quad __attribute__((mode(TI)));

typedef struct {
    u8 pad0[0xF0];
    float velocity[4];              /* 0xF0 */
    u8 pad100[0x140 - 0x100];
    float lastVelocity[4];          /* 0x140 */
    u8 pad150[0x174 - 0x150];
    float f174;
    float f178;
    u8 pad17C[0x190 - 0x17C];
    float targetDir[4];             /* 0x190 */
    float inputAngle;               /* 0x1A0 */
    u8 pad1A4[0x1B0 - 0x1A4];
    float inputSpeed;               /* 0x1B0 */
    float f1B4;
    u8 pad1B8[0x287 - 0x1B8];
    u8 f287;
    u8 pad288[0x34A - 0x288];
    s16 f34A;
    u8 pad34C[0x524 - 0x34C];
    s16 f524;
    u8 pad526[0xA60 - 0x526];
    float vecA60[4];
    u8 padA70[0x1454 - 0xA70];
    s16 f1454;
    u8 pad1456[0x2294 - 0x1456];
    s32 f2294;
    u8 pad2298[4];
    s32 f229C;
    u8 pad22A0[0x22C3 - 0x22A0];
    u8 moveMode;                    /* 0x22C3 */
} HeroVelocity;

extern HeroVelocity D_00189E20;

extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282E20(void *);
extern float func_L00_002D3A58(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D3BD8(void *, void *, float);
extern float func_L00_002B5590(void *);

/* Moves the hero's velocity toward the requested one, accelerating harder when reversing. */
void func_L00_002B6198(float rate)
{
    float wantedVel[4] __attribute__((aligned(16)));
    float targetCopy[4] __attribute__((aligned(16)));
    float flatVel[4] __attribute__((aligned(16)));
    float angle, speed, dot, wantedLen, currentLen;

    switch (gHeroState.moveMode) {
    case 0:
        angle = gHeroState.inputAngle;
        speed = gHeroState.inputSpeed;
        if (gHeroState.f229C == 4 && gHeroState.f524 && gHeroState.f287)
            speed = 0.0833333358f;
        if (gHeroState.f34A && gHeroState.f2294 == 14 && speed > 0.0166666675f)
            speed = 0.0166666675f;
        wantedVel[0] = FastSinOrCosA(angle) * speed;
        wantedVel[1] = FastSinOrCosB(angle) * speed;
        wantedVel[2] = gHeroState.velocity[2];
        dot = -(gHeroState.velocity[0] * wantedVel[0] + gHeroState.velocity[1] * wantedVel[1]);
        wantedLen = vec_length_xy(wantedVel);
        currentLen = vec_length_xy(gHeroState.velocity);
        if (wantedLen == 0.0f || currentLen == 0.0f) {
            dot = 0.0f;
        } else {
            dot /= wantedLen;
            dot /= currentLen;
        }
        dot += 1.0f;
        dot *= 1.5f;
        if (dot > 3.0f)
            dot = 3.0f;
        if (dot < 1.0f)
            dot = 1.0f;
        rate *= dot;
        FastVecSub(wantedVel, wantedVel, gHeroState.velocity);
        if (vec_length_xy(wantedVel) > rate)
            FastVectorNormalizeHelper(wantedVel, wantedVel, rate);
        FastVecAdd(gHeroState.velocity, gHeroState.velocity, wantedVel);
        qcopy(gHeroState.lastVelocity, gHeroState.velocity);
        *(Quad *)targetCopy = *(Quad *)gHeroState.vecA60;
        gHeroState.f1B4 = gHeroState.f178 - GetSpeedAlongHeroForward(targetCopy);
        if (gHeroState.f1454)
            gHeroState.f1B4 = gHeroState.f174;
        break;
    case 1:
    case 2:
        *(Quad *)targetCopy = *(Quad *)gHeroState.targetDir;
        speed = gHeroState.inputSpeed;
        SetViewSpaceHeight(wantedVel, targetCopy, 0.0f);
        vec_scale_to_length(wantedVel, wantedVel, speed);
        SetViewSpaceHeight(flatVel, gHeroState.velocity, 0.0f);
        dot = -FastVecDot(flatVel, wantedVel);
        wantedLen = GetViewSpaceVectorLength(wantedVel);
        currentLen = GetViewSpaceVectorLength(gHeroState.velocity);
        if (wantedLen == 0.0f || currentLen == 0.0f) {
            dot = 0.0f;
        } else {
            dot /= wantedLen;
            dot /= currentLen;
        }
        dot += 1.0f;
        dot *= 1.5f;
        if (dot > 3.0f)
            dot = 3.0f;
        if (dot < 1.0f)
            dot = 1.0f;
        rate *= dot;
        FastVecSub(wantedVel, wantedVel, gHeroState.velocity);
        SetViewSpaceHeight(wantedVel, wantedVel, 0.0f);
        if (GetViewSpaceVectorLength(wantedVel) > rate)
            SetViewSpaceVectorLength(wantedVel, wantedVel, rate);
        FastVecAdd(gHeroState.velocity, gHeroState.velocity, wantedVel);
        gHeroState.f1B4 = gHeroState.f178;
        if (gHeroState.f1454)
            gHeroState.f1B4 = gHeroState.f174;
        break;
    }
}
