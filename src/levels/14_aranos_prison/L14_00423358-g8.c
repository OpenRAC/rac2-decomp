#include "common.h"

extern int func_002B3868(void *);
extern int func_002A77E0(int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_002B60B0(void *, float, float, float, float);
extern int func_L14_00423CD0(void *, void *, int, void *, int, float);
extern void func_L14_00423DC0(void *, void *);
extern int func_L14_00423E50(void *);
extern int func_L09_0033E690(void *, int, float);
extern float func_00282E80(void *, void *);
extern int func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, float, float);
extern unsigned long func_002B1C20(void *, void *);
extern void func_002A6C58(void *, int, int);
extern void func_0029F338(void *);

extern char *D_L14_001B259C;
extern char *D_L14_001B268C;
extern int D_L14_001B16B4 __attribute__((sda));
extern int D_L14_001B16B8 __attribute__((sda));
extern int D_L14_001B16BC __attribute__((sda));
extern char D_00189EA0[];

/* Updates the actor's animation, movement phases and hit response. */
void func_L14_00423358(char *self)
{
    char *state = *(char **)(self + 0x68);
    float target[4];
    unsigned long flags;
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        break;
    case 1:
        if (SetFirstPendingFlag(self)) {
            if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 1)
                StartAnimationBlended(self, RandomIntBelow(2) + 1, 0, 10);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(self)) {
            float a = *(float *)(state + 0x720);
            float b = *(float *)(state + 0x724);
            SetControllerSpeedLimits(self, (a + a) * 0.00027777778450399637f,
                a * 0.01666666753590107f, (b + b) * 4.848137450608192e-06f,
                b * 0.0002908882452175021f);
            if (*(unsigned char *)(self + 0x43) != RandomIntBelow(4) + 6)
                StartAnimationBlended(self, RandomIntBelow(4) + 6, 0, 10);
            *(short *)(state + 0x770) = 0;
        } else if (AdvanceAlongPath_L14(self, state + 0x700, *(int *)(state + 0x730), state + 0x770, 0, 2.0f)) {
            SetMobyState(self, 2, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(self)) {
            if (*(unsigned char *)(self + 0x43) != 1)
                StartAnimationBlended(self, 1, 0, 10);
            *(unsigned char *)(self + 0xBC) = 0;
            *(unsigned short *)(self + 0x96) = RandomIntBelow(D_L14_001B16B4 >> 1);
        } else {
            qcopy_nc(target, (void *)((*(int *)(state + 0x748) << 8) + (unsigned int)gMobyPool_L14 + 0x10));
            target[2] += 0.3f;
            AimActorAtTarget(self, gMobyPool_L14 + (*(int *)(state + 0x748) << 8) + 0x10);
            if (*(unsigned char *)(self + 0xBC) == 0 && *(unsigned short *)(self + 0x96) > D_L14_001B16B4) {
                *(unsigned short *)(self + 0x96) = RandomIntBelow(D_L14_001B16B4 >> 1);
                if (RandomIntBelow(5) != 0 && *(unsigned char *)(self + 0x43) != 5)
                    StartAnimationBlended(self, 5, 0, 10);
            }
            if (*(unsigned char *)(self + 0xBC) == 1 && (*(unsigned char *)(self + 0x60) & 2))
                SetMobyState(self, 2, -1);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(self)) {
            switch (*(unsigned char *)(self + 0xBC) = RandomIntBelow(2)) {
            case 0:
                if (*(unsigned char *)(self + 0x43) != 4)
                    StartAnimationBlended(self, 4, 0, 10);
                break;
            case 1:
                if (*(unsigned char *)(self + 0x43) != 3)
                    StartAnimationBlended(self, 3, 0, 10);
                break;
            }
        }
        if (*(int *)(state + 0x764) != -1)
            AimActorAtTarget(self, D_L14_001B268C + (*(int *)(state + 0x764) << 7) + 0x30);
        if (*(unsigned char *)(self + 0x60) & 2)
            SetMobyState(self, 5, 2);
        break;
    case 5:
        if (SetFirstPendingFlag(self)) {
            *(unsigned char *)(self + 0xBC) = 0;
            if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 10)
                StartAnimationBlended(self, RandomIntBelow(2) + 10, 0, 10);
        } else {
            if (*(unsigned char *)(self + 0xBC) == 0 && (*(unsigned char *)(self + 0x60) & 2)) {
                if (*(int *)(state + 0x734) != -1) {
                    float a, b;
                    *(unsigned char *)(self + 0xBC) = 1;
                    a = *(float *)(state + 0x728);
                    b = *(float *)(state + 0x72C);
                    SetControllerSpeedLimits(self, (a + a) * 0.00027777778450399637f,
                        a * 0.01666666753590107f, (b + b) * 4.848137450608192e-06f,
                        b * 0.0002908882452175021f);
                    if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 14)
                        StartAnimationBlended(self, RandomIntBelow(2) + 14, 0, 10);
                    *(short *)(state + 0x770) = MeasureMobyAgainstPathEntry(self + 0x10, *(int *)(state + 0x734), 0.0f);
                } else {
                    *(unsigned char *)(self + 0xBC) = 2;
                }
            } else if (*(unsigned char *)(self + 0xBC) == 1) {
                AdvanceAlongPath_L14(self, state + 0x700, *(int *)(state + 0x734), state + 0x770, *(short *)(state + 0x77C), 1.0f);
                if (*(unsigned short *)(self + 0x96) % D_L14_001B16B8 == 0 && RandomIntBelow(D_L14_001B16BC) == 0) {
                    *(unsigned char *)(self + 0xBC) = 2;
                    if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 12)
                        StartAnimationBlended(self, RandomIntBelow(2) + 12, 0, 10);
                }
            } else if (*(unsigned char *)(self + 0xBC) == 2 && (*(unsigned char *)(self + 0x60) & 2)) {
                if (HasActiveNonTouristInGroup(self))
                    SetMobyState(self, 5, -1);
                else
                    SetMobyState(self, 1, -1);
            }
        }
        break;
    case 6:
        if (SetFirstPendingFlag(self)) {
            *(unsigned char *)(self + 0xBC) = 0;
            if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 10)
                StartAnimationBlended(self, RandomIntBelow(2) + 10, 0, 10);
        } else {
            if (*(unsigned char *)(self + 0xBC) == 0 && (*(unsigned char *)(self + 0x60) & 2)) {
                float a, b;
                *(unsigned char *)(self + 0xBC) = 1;
                a = *(float *)(state + 0x728);
                b = *(float *)(state + 0x72C);
                SetControllerSpeedLimits(self, (a + a) * 0.00027777778450399637f,
                    a * 0.01666666753590107f, (b + b) * 4.848137450608192e-06f,
                    b * 0.0002908882452175021f);
                if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 14)
                    StartAnimationBlended(self, RandomIntBelow(2) + 14, 0, 10);
            } else if (*(unsigned char *)(self + 0xBC) == 1) {
                qcopy(state + 0x700, gHeroPosition);
                if (vec_distance_xy(self + 0x10, state + 0x700) < *(float *)(state + 0x74C) && *(unsigned char *)(self + 0x31)) {
                    *(unsigned char *)(self + 0xBC) = 2;
                    if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 12)
                        StartAnimationBlended(self, RandomIntBelow(2) + 12, 0, 10);
                }
            } else if (*(unsigned char *)(self + 0xBC) == 2 && (*(unsigned char *)(self + 0x60) & 2)) {
                SetMobyState(self, 6, -1);
            }
        }
        break;
    case 7:
        if (SetFirstPendingFlag(self)) {
            if (*(unsigned char *)(self + 0x43) != RandomIntBelow(2) + 14)
                StartAnimationBlended(self, RandomIntBelow(2) + 14, 0, 10);
        }
        ComputeRegionRouteHeading(self + 0x10, state + 0x710, state + 0x768, state + 0x200,
            *(int *)(state + 0x750), state + 0x75C, state + 0x760, 0.0f, 0.4f);
        qcopy(state + 0x700, state + 0x710);
        *(short *)(state + 0x77A) = 1;
        if (vec_distance_xy(self + 0x10, state + 0x710) < 0.2f)
            SetMobyState(self, 1, 1);
        break;
    case 8:
        flags = DispatchActionByKind(self, state + 0x60);
        if ((*(unsigned char *)(self + 0x42) == 0x12 && RandomIntBelow(30) == 0) || ((flags & 1UL) == 1UL)) {
            SetDeathBits(self, 0, 3);
            MarkMobySpawned(self);
        } else if ((flags & 2UL) == 2UL) {
            SetMobyState(self, *(unsigned char *)(self + 0x94), 2);
        }
        break;
    }
}
