#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_V4_002AE8C0
#define RAC2_T_V4_002AE8C0
typedef int V4_002AE8C0 __attribute__((mode(TI)));
#endif

extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern int func_002A7EA0(char *, char *, float *, int, float, float, float, float);
extern float func_002A89A8(char *, int, float);
extern float func_002AA150(float, float, float);
extern void func_002AA800(float *, int, float, float);
extern int func_00282978(char *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float, float);
extern float func_00282E80(char *, char *);

/* The hero's world position is the 0x80 field of the resident block at D_00189E20;
   the address the retail body forms for it (0x189EA0) is this field's address. */
typedef struct {
    char reserved_000[0x80];
    float pos[4];
} GameState_189E20;

extern GameState_189E20 D_00189E20;

/* Runs the timer state, then integrates a copied position vector through two sine helpers
   and applies the result to the object's 0x24 field, either from the target position or from
   the hero position. The unit needs -frac2-qcopy -frac2-qcopy-barrier so the 16-byte copy
   reaches addiu/lq/sq, and -g for the two nops in front of the division. */
void func_002AE8C0(char *objectPtr, char *statePtr, float speed, float slopeLimit)
{
    char *obj = objectPtr;
    char *st = statePtr;
    V4_002AE8C0 *pos;
    float nextPos[4];
    float distance;
    float limit;
    int moveResult;

    if (*(short *)(st + 0x28) == 0) {
        *(float *)(st + 0x24) = *(float *)(st + 0x24) + RandomSignedFloatRange(0.78539824f, 2.6179941f);
        *(short *)(st + 0x2A) = RandomIntRange(*(short *)(st + 0x2C), *(short *)(st + 0x2E));
        *(short *)(st + 0x28) = 1;
    } else {
        StepAngleTowardTarget((float *)(obj + 0xF8), 0, *(float *)(st + 0x24), *(float *)(st + 0x18));
        if (FastDecTimer(st + 0x2A) != 0)
            *(short *)(st + 0x28) = 0;
    }
    pos = (V4_002AE8C0 *)(obj + 0x10);
    *(V4_002AE8C0 *)nextPos = *pos;
    nextPos[0] = nextPos[0] + FastSinOrCosA(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    nextPos[1] = nextPos[1] + FastSinOrCosB(*(float *)(obj + 0xF8)) * *(float *)(st + 0x14);
    moveResult = MoveOverGround(obj, (char *)pos, nextPos, 0, speed, *(float *)(st + 0x10), slopeLimit, 0.52359885f);
    *(float *)(obj + 0x18) = ProbeGroundHeightBelow((char *)pos, 0, 0.5f);
    distance = vec_distance_xy((char *)pos, st);
    if (moveResult == 0 || *(float *)(st + 0x1C) < distance) {
        *(float *)(st + 0x24) = FastMatrixHelperA(*(float *)(st + 0x0) - *(float *)(obj + 0x10),
                                              *(float *)(st + 0x4) - *(float *)(obj + 0x14));
        *(short *)(st + 0x2A) = RandomIntRange(30, 90);
        *(short *)(st + 0x28) = 1;
    } else {
        float ratio;

        distance = vec_distance_xy((char *)pos, gHeroState.pos);
        limit = *(float *)(st + 0x20);
        if (distance < limit) {
            ratio = distance / limit;
            *(float *)(st + 0x24) = MoveAngleTowardTarget(*(float *)(st + 0x24),
                    FastMatrixHelperA(*(float *)(obj + 0x10) - gHeroState.pos[0],
                                  *(float *)(obj + 0x14) - gHeroState.pos[1]), ratio);
        }
    }
}
