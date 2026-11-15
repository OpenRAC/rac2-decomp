/* func_002ED6B0 in its own unit, so that its call to func_002ED870 (C in 002ED578.c)
   is a plain external call. */
#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned char u8;
extern int func_002ED688(unsigned char *);
typedef struct { float lim; char pad[0x2c]; float v[4]; char pad2[0x40]; } Rec128;
/* Retail loads this pointer with the assembler's lui/lw macro (lui into the destination). */
extern Rec128 *D_001B1C54[] __attribute__((sda));
extern int D_00214F90[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_00283028(void *, void *, void *);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
/* The three floats come before the last int ($f14 is set before $t2 at every call). */
extern void func_002C2210(void *, unsigned int, unsigned int, unsigned int, s32, float *, float, float, float, s32);
extern unsigned int func_002ED870(void);
extern int func_002EE6A8();

/* Keeps a follower object inside its allowed range of its target. When its counter
   reaches 7 it resets the counter and throws out a burst of 20 sparks. */
void func_002ED6B0(u8 *owner)
{
    u8 *vars;
    float offset[4] __attribute__((aligned(16)));
    float sparkVel[4] __attribute__((aligned(16)));
    float radius;
    float dist;
    float maxDist;
    int i;
    Rec128 *tuning;
    float *tuneVec;

    vars = (u8 *)GetMobyMotionData(owner);
    if (vars != 0 && !GetSceneStateWord() && GetFollowerState(owner) != 2) {
        tuning = &D_001B1C54[0][D_00214F90[0]];
        tuneVec = tuning->v;
        FastVecSub(offset, owner + 0x10, tuneVec);
        dist = FastVecLength(offset);
        radius = *(float *)(owner + 0xC) * 0.00097656f;
        dist = dist + radius;
        maxDist = tuning->lim;
        if (maxDist < dist) {
            vec_scale_to_length(offset, offset, maxDist - radius);
            FastVecAdd(owner + 0x10, offset, tuneVec);
        }
        if (*(int *)(vars + 0x15C) >= 7) {
            FastVectorNormalize(vars + 0x90, vars + 0x90, vars + 0xD0);
            *(int *)(vars + 0x15C) = 0;
            for (i = 0x13; i >= 0; i--) {
                float randA = RandomAngle();
                float randB = RandomAngle();
                BuildSphericalOffset(sparkVel, 0.16666667f, randA, randB);
                SpawnGroundEffectParticle(owner + 0x10, 0x3C, 0x4000FF7F, 0, 2, sparkVel, 0.2f, 1.25f, 0.0f, 0);
            }
        }
    }
}
