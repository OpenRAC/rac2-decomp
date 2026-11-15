#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern int func_L00_00367720(void);
extern void func_L05_00417448(void *);
extern void func_L05_00379E60(int, int, int, int);
extern void func_L05_00417730(void *);
extern int func_002ED688(void *);
extern void func_002EE678(void *, unsigned int);
extern void func_002EE920(void *, void *);
extern int func_002EEB00(void *);
extern void func_L05_0037C160(void *);
extern void func_L05_0037B948(void *, int, float);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern int func_00282948(void *);
extern int func_002E5DA0(int, int, void *, int);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_L05_00417550(void *);
extern int D_L05_001B0F50 __attribute__((sda));
extern int D_L05_00221D48 NOT_SDA;
extern char *D_L05_001FE380[];
extern char *D_L05_001B251C MACRO_ADDR;
extern u8 D_00188660[];

typedef struct { u8 pad[0x11C]; int mode; } Movement;
/* Moves the object along a route of points each frame and restarts it from the route start
   when it is new. */
void func_L05_004170C8(u8 *actor)
{
    Vector direction, facing;
    u8 *state = *(u8 **)(actor + 0x68);
    u8 *movement;
    char *path;
    int one, mode;
    if (actor[0x20] == 0) {
        actor[0x30] = 0xFF;
        if (GetStoredPointerValue() == 0)
            return;
        InitEffectMobyFromTable(actor);
        if (*(int *)(state + 0x1B4) != 0)
            AppendLevelObject((int)actor, (int)func_L05_00417730, 0, 0);
        D_L05_001B0F50 = 0;
        return;
    }
    movement = (u8 *)GetMobyMotionData(actor);
    if (*(int *)(movement + 0x110) == 0)
        return;
    path = D_L05_001FE380[D_L05_00221D48];
    one = 1;
    SetFollowerState(actor, 11);
    if (*(int *)(state + 0x1B8) == 0) {
        *(int *)(state + 0x1B8) = one;
        *(int *)(state + 0x1BC) = one;
        qcopy(actor + 0x10, path + 0x10);
        *(int *)(state + 0x1BC) = 2;
        SetFollowerPushVector(actor, path + 0x20);
        FastVecSub(movement + 0x90, movement + 0x60, actor + 0x10);
        vec_scale_to_length(movement + 0x90, movement + 0x90, 1.0f);
        *(int *)(movement + 0x130) = 2000000;
    } else if (HasFollowerReachedTarget(actor) != 0) {
        int next = *(int *)(state + 0x1BC);
        if (next >= *(int *)path)
            D_L05_001B0F50 = one;
        else {
            *(int *)(state + 0x1BC) = next + 1;
            SetFollowerPushVector(actor, path + (next * 16 + 16));
            *(int *)(movement + 0x130) = 2000000;
        }
    }
    if (D_L05_001B0F50 == 0) {
        UpdateObjectMovementState(actor);
        CheckPlayerInViewAndRange(actor, 1, 32.0f);
    }
    mode = *(int *)(movement + 0x110);
    if (mode == 1) {
        if (*(int *)(state + 0x1B0) != -1) {
            u8 *other;
            ((Movement *)movement)->mode = mode;
            other = (u8 *)D_L05_001B251C + (*(int *)(state + 0x1B0) << 8);
            *(u8 **)(movement + 0x120) = other;
            if (fast_vec_dist(other + 0x10, actor + 0x10) < 15.0f) {
                float alignment;
                FastVecSub(&direction, actor + 0x10, *(u8 **)(movement + 0x120) + 0x10);
                vec_scale_to_length(&direction, &direction, 1.0f);
                vec_scale_to_length(&facing, *(u8 **)(movement + 0x120) + 0xC0, 1.0f);
                alignment = FastVecDot(&facing, &direction);
                if (alignment > 0.4f) {
                    if (FastFloatHelperD(state + 0x1C8) != 0) {
                        *(int *)(state + 0x1C4) = PlaySoundFromClassBank(14, 0, actor, 0xFBF);
                        *(int *)(state + 0x1C8) = FloatToInt(RandomFloatRange(180.0f, 240.0f));
                    }
                } else if (alignment < -0.4f && FastFloatHelperD(state + 0x1C8) != 0) {
                    PlaySoundFromClassBank(11, 0, actor, 0xFBF);
                    *(int *)(state + 0x1C8) = FloatToInt(RandomFloatRange(180.0f, 240.0f));
                }
            }
        }
        SpawnTailTrailMarks_L05(actor);
    }
    {
        u8 *sound = gSoundState + *(int *)(state + 0x1C0) * 0x70;
        if (*(u8 **)(sound + 0x88) != actor || sound[0x74] == 0)
            *(int *)(state + 0x1C0) = PlaySoundFromClassBank(0, 6, actor, 0xF82);
    }
}
