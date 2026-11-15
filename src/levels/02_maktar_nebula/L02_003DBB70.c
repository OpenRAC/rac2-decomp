#include "include_asm.h"
#include "names.h"

/* func_L02_003DBB70 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern char *D_L02_001B359C[] __attribute__((sda));
extern void func_0029FCC0(void *, int, void *);
extern void func_002ACB48(float *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_00283CF0(float);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Throws bursts of green glitter particles out from a part of the actor,
   drifting outward and upward. */
void func_L02_003DBB70(char *actor, char *baseVel) {
    float startPos[4];
    float vel[4];
    float endVel[4];
    int burst;
    int i;
    float angle;
    float radius;
    float lift;
    int colorA;
    int colorB;

    for (burst = 0; burst < 30; burst++) {
        TransformMobyJointToWorld(gMobyPool_L02[0] + (*(int *)(*(char **)(actor + 0x68) + 0x244) << 8), 4, startPos);
        AddRandomOffsetToVector(startPos, 0.5f);
        startPos[2] += 0.25f;
        angle = RandomAngle();
        radius = RandomFloatRange(3.0f, 16.0f);
        lift = RandomFloatRange(3.0f, 12.0f);
        FastVecScale(vel, baseVel, RandomFloatRange(0.0f, 0.0f) * 0.016666668f);
        vel[0] += FastSinOrCosA(angle) * 0.016666668f * radius;
        vel[1] += FastSinOrCosB(angle) * 0.016666668f * radius;
        vel[2] += lift * 0.016666668f;
        *(TI128 *)endVel = *(TI128 *)vel;
        endVel[2] -= 0.33333334f;
        for (i = 0; i < 20; i++) {
            float scale = RandomFloatRange(0.5f, 1.5f);

            vel[3] = scale * 0.25f;
            endVel[3] = scale * 0.125f;
            AddRandomOffsetToVector(startPos, 0.25f);
            AddRandomOffsetToVector(endVel, 0.016666668f);
            colorA = FastTweenColor(0x80FF00EA, 0x80FF00EA, RandomFloatRange(0.0f, 1.0f));
            colorB = FastTweenColor(0x00FF0020, 0x00FF00AA, RandomFloatRange(0.0f, 1.0f));
            SpawnTrailParticle_002BAA28(startPos, vel, endVel, colorA, colorB, 20, 60, FloatToInt(RandomFloatRange(10.0f, 50.0f)), -1);
        }
    }
}
