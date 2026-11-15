#include "include_asm.h"
#include "names.h"

typedef int Rac2TI128 __attribute__((mode(TI)));

extern int func_L11_00448D28(char *object);
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(char *object, float *src, char *third);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E48(void *, void *);
extern int func_002A77E0(int);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern char D_00189EA0[];

/* Picks the attack variant the actor plays against its target: the aim vector comes from the
   state's target record, or the shared default, and a close and well aimed target starts one
   of three attacks. */
int func_L11_00448AA8(char *object)
{
    char *state = *(char **)(object + 0x68);
    float targetPos[4];
    float offset[4];
    float angleToTarget;
    char *targetRecord;

    if (GroupHasThreeLiveObjects(object) != 0)
        return 0;
    targetRecord = *(char **)(state + 0x350);
    if (targetRecord != 0)
        *(Rac2TI128 *)targetPos = *(Rac2TI128 *)(targetRecord + 0x10);
    else
        *(Rac2TI128 *)targetPos = *(Rac2TI128 *)gHeroPosition;
    if (*(short *)(state + 0x36E) != 0) {
        FastVecSub(offset, targetPos, object + 0x10);
        angleToTarget = GetHeadingAngleOfVector(object, offset, state + 0x2F0);
    } else {
        angleToTarget = FastDiffRots(FastMatrixHelperA(targetPos[0] - *(float *)(object + 0x10), targetPos[1] - *(float *)(object + 0x14)),
                            *(float *)(object + 0xF8));
    }
    if (fast_vec_dist(object + 0x10, targetPos) < 4.0f) {
        if (angleToTarget < 0.26179942f) {
            if (RandomIntBelow(4) == 0) {
                SetMobyState(object, 0xC, 5);
                if (*(unsigned char *)(object + 0x43) != 7)
                    StartAnimationBlended(object, 7, 0, 0xA);
            } else if (*(int *)(state + 0x354) != 0) {
                SetMobyState(object, 0xE, 6);
                if (*(unsigned char *)(object + 0x43) != 9)
                    StartAnimationBlended(object, 9, 8, 0xF);
            } else {
                SetMobyState(object, 0xD, 6);
                if (*(unsigned char *)(object + 0x43) != 8)
                    StartAnimationBlended(object, 8, 8, 0xF);
            }
            return 1;
        }
    }
    return 0;
}
