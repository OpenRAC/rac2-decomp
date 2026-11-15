#include "common.h"

/* A unit of its own so that the call to func_L02_003D2488 goes through its symbol: USA v2.00
   has that function as assembly at an address of its own, and a call within one object can
   only reach the object's own copy. */

extern char D_L02_001BA500;
extern float func_00282E48(void *, void *);
extern int func_00283CF0(float);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_002A93B0(char *);
extern void *func_002A9640(char *, int, int);
extern void func_002B0ED8(char *, char *, int);
extern void func_L02_003D1998(char *);
extern int func_L02_003D1880(char *, void *);
extern void func_L02_003D1FA0(char *, int);
extern void func_L02_003D2390(char *);
extern void func_L02_003D2488(char *, int, int);

/* State 0 of the actor: fills its state record (a random heading of 10 to 30 degrees, either
   sign, then about twenty constants), queues func_L02_003D2390; then, while it is drawn, the
   per-frame part (the pulse test against D_L02_001BA500, the 0x15/0x10 animation switch,
   func_L02_003D2488 and func_L02_003D1998).
   Spelling: the signed heading is a variable of its own, set after the coin flip and stored
   first. Its pseudo then crosses no call, so sched1 ties its store to that call by an
   anti-dependence (priority 3) and the zero store at 0x2F4 goes first, as in retail; stored
   from `ang` itself, the two stores tie at priority 4 and the dying `ang` wins. The constant
   stores come out in an order of the scheduler's own (the statement order below is the
   measured one), and 0.017453294f, 1.5707965f and 0.52359885f are retail's bits. */
/* Sets up the armed enemy on its first frame, then each frame checks for hits, plays the death animation when its health runs out and runs its partner logic. */
void func_L02_003D10F0(char *self) {
    char *state = *(char **)(self + 0x68);
    float ang;
    float dir;
    char *foundTarget;

    if (*(unsigned char *)(self + 0x20) == 0) {
        *(char **)(state + 0x18) = state + 0x100;
        *(unsigned char *)(state + 0x48) = FloatToInt(15.0f);
        *(unsigned char *)(state + 0x4A) = FloatToInt(16.0f);
        ang = RandomFloatRange(10.0f, 30.0f) * 0.017453294f;
        if (RandomIntBelow(2) != 0)
            dir = -ang;
        else
            dir = ang;
        *(float *)(state + 0x2E8) = dir;
        *(unsigned char *)(state + 0x60) = 0x14;
        *(int *)(state + 0x98) = 7;
        *(float *)(state + 0x80) = 1.3f;
        *(float *)(state + 0x84) = 1.3f;
        *(unsigned char *)(state + 0x69) = 2;
        *(unsigned char *)(state + 0x1E9) = 3;
        *(float *)(state + 0x8C) = 0.4f;
        *(unsigned char *)(state + 0x1E6) = 5;
        *(float *)(state + 0x108) = 0.3f;
        *(unsigned char *)(state + 0x1E8) = 2;
        *(float *)(state + 0x1D4) = 0.5f;
        *(float *)(state + 0x100) = 1.0f;
        *(float *)(state + 0x104) = 0.2f;
        *(float *)(state + 0x10C) = 0.3f;
        *(float *)(state + 0x110) = 1.5707965f;
        *(float *)(state + 0x130) = 0.52359885f;
        *(short *)(state + 0x2F4) = 0;
        *(float *)(state + 0x134) = 0.01f;
        *(float *)(state + 0x12C) = 0.0055555557f;
        *(unsigned char *)(state + 0x28) = 3;
        *(unsigned char *)(state + 0x29) = 1;
        *(float *)(state + 0x30) = 0.75f;
        if (RandomIntBelow(2) == 0)
            *(unsigned short *)(self + 0x34) |= 0x8000;
        *(int *)(state + 0x2E4) = 0;
        ReleaseEnemyEffectRecord(self);
    }
    if (*(unsigned char *)(self + 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, &gCameraPosition_L02) < 24.0f) {
            UpdateMobyGroundCheck(self);
            *(unsigned char *)(self + 0x6F) = 0x16;
        }
        if (*(unsigned char *)(self + 0x31) != 0 && *(unsigned char *)(self + 0x20) >= 3) {
            *(float *)(state + 0xFC) = 1.0f;
            foundTarget = FindOwnedEffectSlot(self, 0x10000, 1);
            if (foundTarget != 0) {
                *(float *)(state + 0xFC) = 1.0f;
                if (IsHoldingObjectInAttackState(self, foundTarget) != 0) {
                    *(unsigned char *)(state + 0x60) = 0x13;
                    ApplyDamageToObject(self, state + 0x50, 1);
                    *(unsigned char *)(state + 0x60) = 0x14;
                    if (*(int *)(state + 0x2E4) != 0 && *(short *)(state + 0x2F4) == 0 &&
                        *(unsigned char *)(self + 0x31) != 0) {
                        SpawnDustParticlePairs(*(char **)(state + 0x2E4) + 0x10, 2);
                        *(short *)(state + 0x2F4) = 0x3C;
                    }
                } else {
                    ApplyDamageToObject(self, state + 0x50, 0);
                }
            } else {
                ApplyDamageToObject(self, state + 0x50, 0);
            }
            if (*(float *)(state + 0x20) <= 0.0f && *(unsigned char *)(self + 0x20) != 0x15) {
                SetMobyState(self, 0x15, 7);
                if (*(unsigned char *)(self + 0x43) != 0x10)
                    StartAnimationBlended(self, 0x10, 0, 0);
            }
            if (*(unsigned char *)(self + 0x20) >= 2 && *(unsigned char *)(state + 0x2E) == 2)
                DropHeldObjectAndReset(self, 1, 1);
            FindOrKeepPartner(self);
        }
    }
}
