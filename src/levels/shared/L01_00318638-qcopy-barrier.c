#include "include_asm.h"
#include "names.h"


typedef int V4_002AE8C0 __attribute__((mode(TI)));
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern int func_L01_00321178(char *, float *);
extern float func_002A89A8(char *, int, float);
extern float func_002AA150(float, float, float);
extern void func_002AA800(float *, int, float, float);
extern int func_00282978(char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00282E80(char *, char *);
typedef struct {
    char reserved_000[0x80];
    float pos[4];
} GameState_189E20;
extern GameState_189E20 D_00189E20;

/* Hand-adapted from func_002AE8C0. */
/* Moves a wandering enemy: picks a new heading when its timer runs out, turns away from walls and edges, and turns away from the hero when close. */
void func_L01_00318638(char *obj, char *wander, char *context)
{
    char *selfPos;
    float probePoint[4];
    float amount;

    int blocked;

    if (*(short *)(wander + 0x28) == 0) {
        *(float *)(wander + 0x24) = *(float *)(wander + 0x24) + RandomSignedFloatRange(0.78539824f, 2.6179941f);
        *(short *)(wander + 0x2A) = RandomIntRange(*(short *)(wander + 0x2C), *(short *)(wander + 0x2E));
        *(short *)(wander + 0x28) = 1;
    } else {
        StepAngleTowardTarget((float *)(obj + 0xF8), 0, *(float *)(wander + 0x24), *(float *)(wander + 0x18));
        if (FastDecTimer(wander + 0x2A) != 0)
            *(short *)(wander + 0x28) = 0;
    }
    selfPos = obj + 0x10;
    *(V4_002AE8C0 *)probePoint = *(V4_002AE8C0 *)selfPos;
    amount = *(float *)(context + 0x28);
    *(float *)(context + 0x28) = *(float *)(wander + 0x14);
    probePoint[0] = probePoint[0] + FastSinOrCosA(*(float *)(obj + 0xF8)) * 2.0f;
    probePoint[1] = probePoint[1] + FastSinOrCosB(*(float *)(obj + 0xF8)) * 2.0f;
    *(float *)(context + 0x28) = amount;
    blocked = TurnMobyTowardTarget(obj, probePoint);
    *(float *)(obj + 0x18) = ProbeGroundHeightBelow(selfPos, 0, 0.5f);
    amount = vec_distance_xy(selfPos, wander);
    if (blocked != 0 || *(float *)(wander + 0x1C) < amount) {
        *(float *)(wander + 0x24) = FastMatrixHelperA(*(float *)(wander + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(wander + 0x4) - *(float *)(obj + 0x14));
        *(short *)(wander + 0x2A) = RandomIntRange(30, 90);
        *(short *)(wander + 0x28) = 1;
    } else {
        float limit;

        amount = vec_distance_xy(selfPos, gHeroState.pos);
        limit = *(float *)(wander + 0x20);
        if (amount < limit) {
            amount = amount / limit;
            *(float *)(wander + 0x24) = MoveAngleTowardTarget(*(float *)(wander + 0x24),
                    FastMatrixHelperA(*(float *)(obj + 0x10) - gHeroState.pos[0],
                                  *(float *)(obj + 0x14) - gHeroState.pos[1]), amount);
        }
    }
}
