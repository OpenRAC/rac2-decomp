#include "include_asm.h"
#include "names.h"

/* func_002EE6A8: owner ABI/declaration review retained. */
extern int func_002ED688(unsigned char *owner);

#ifndef RAC2_T_V4_FB6552688
#define RAC2_T_V4_FB6552688
typedef int V4_Fb6552688 __attribute__((mode(TI)));
#endif

extern char *func_002ED688_1(char *);

extern void func_00282F20_10(V4_Fb6552688 *, char *, float);

extern void func_00282CC0_26(char *, V4_Fb6552688 *, char *);

extern void func_002EE988(char *);

/* Sets the follower's state number. */
void func_002EE678(unsigned char *owner, unsigned int value)
{
    unsigned int address = (unsigned int)GetMobyMotionData(owner);
    if (address != 0)
        *(unsigned int *)(address + 0x100u) = value;
}

/* Returns the follower's state number, or 0 if it has no data. */
unsigned int func_002EE6A8(unsigned char *owner)
{
    unsigned int address = (unsigned int)GetMobyMotionData(owner);
    if (address == 0)
        return 0;
    return *(unsigned int *)(address + 0x100u);
}


extern int func_002ACCA8(unsigned char *a, int b);
extern void func_002ED9C0(unsigned char *owner);
extern void func_002EE8B0(char *owner);
extern int D_00214F90[];

/* Checks if the follower touches one of the listed hazard spots; if so, it dies and switches to state 13. */
void func_002EE6E0(unsigned char *owner)
{
    int i;
    unsigned int state;

    if (D_00214F90[36] == 0)
        return;
    if (GetMobyMotionData(owner) == 0)
        return;
    state = GetFollowerState(owner);
    if (state == 0xB)
        return;
    if (state == 0xD)
        SetFollowerState(owner, 1);
    for (i = 0; i < D_00214F90[36]; i++) {
        if (IsPointInsideUnitSphereOfRecord(owner + 0x10, D_00214F90[39 + i])) {
            ReleaseMotionSlot(owner);
            SetFollowerState(owner, 0xD);
            StartFollowerPushFromTarget((char *)owner);
            break;
        }
    }
}

extern float func_002A7940(void);
extern float func_00283180(float owner);
extern float func_00283198(float owner);
extern float func_002A7878(float owner, float a1);
extern char *D_001B1C54 __attribute__((sda));

/* Gives the follower a random starting push, clamps it, and sets its life timer to 300. */
void func_002EE7B8(unsigned char *owner)
{
    char *object;
    char *table;
    float randX;
    float randY;

    object = (char *)GetMobyMotionData(owner);
    if (object == 0)
        return;
    table = D_001B1C54 + D_00214F90[0] * 128;
    randX = FastSinOrCosA(RandomAngle()) * RandomFloatRange(0.0f, *(float *)table);
    *(float *)(object + 0x60) = randX;
    randY = FastSinOrCosB(RandomAngle()) * RandomFloatRange(0.0f, *(float *)table);
    *(float *)(object + 0x68) = 0.0f;
    *(float *)(object + 0x64) = randY;
    func_00282CC0_26(object + 0x60, (V4_Fb6552688 *)(table + 0x30), object + 0x60);
    *(float *)(object + 0x68) = RandomFloatRange(-64.0f, 64.0f) + *(float *)((char *)owner + 0x18);
    ClampFollowerPushVector((char *)owner);
    *(int *)(object + 0x130) = 300;
}

/* Calls randX callee with the object, returns when it fails, otherwise fills randX 16-byte workspace from the object at +192 with 8.0f, hands it to randX second callee through +96, calls randX third, then stores 300 at +304. */
void func_002EE8B0(char *owner)
{
    V4_Fb6552688 pushVec;
    char *vars;

    vars = func_002ED688_1(owner);
    if (vars == 0)
        return;
    func_00282F20_10(&pushVec, owner + 192, 8.0f);
    func_00282CC0_26(vars + 96, &pushVec, owner + 16);
    ClampFollowerPushVector(owner);
    *(int *)(vars + 304) = 300;
}

/* func_002EE920 is matched in 002EE920.c (built with -frac2-qcopy). */

/* func_002EE988 is matched in 002EE988.c (built with -frac2-qcopy -frac2-qcopy-barrier). */
