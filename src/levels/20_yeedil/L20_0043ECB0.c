#include "common.h"

/* func_L20_0043F318 defined in L20_0043F318-g8.c. */

/* func_L20_0043F460 is defined in L20_0043ECB0-g8.c (it reaches a global through $gp). */

/* func_L20_0043F570 is defined in L20_0043F570-g8.c. */

/* func_L20_0043FC70 is defined in L20_0043F570-g8.c (it reaches data through $gp). */

/* func_L20_0043FFF0 is defined in L20_0043F570-g8.c (it reaches globals through $gp). */

/* func_L20_00440198 is defined in L20_00440198.c (its slot-table and func_002A7750 declarations conflict with this unit's). */

extern char *D_L20_001FBB20[];

extern int D_L20_001B2FB8 __attribute__((sda));

extern unsigned int D_L20_001B2F9C __attribute__((sda));

/* Counts the objects of a group whose state byte (object + 0x20) is neither 6 nor negative.
   D_L20_001FBB20 holds a list of 16-bit object ids per group; the low 15 bits of an id index
   the 0x100-byte object records at D_L20_001B2F9C, and the last id of a list has its top bit
   set. The guards on the group and its list come before the walk and again after each record,
   as in func_L20_0039E0A0. The bound D_L20_001B2FB8 does not change in the loop, so cc1 hoists
   its repeated test into a register known to be zero, which the loop still tests (retail's
   `daddu $t0,$zero,$zero` and `bnez $t0`). */
int func_L20_00440398(int group) {
    unsigned short *idList = (unsigned short *)D_L20_001FBB20[group];
    int count = 0;

    if ((group & 0xFF) == 0xFF) {
        goto end;
    }
    if (D_L20_001B2FB8 < group) {
        goto end;
    }
    if (idList == 0) {
        goto end;
    }
    for (;;) {
        char *object = (char *)D_L20_001B2F9C + ((*idList & 0x7FFF) << 8);

        if (object == 0) {
            goto end;
        }
        if (*(unsigned char *)(object + 0x20) != 6 && *(signed char *)(object + 0x20) >= 0) {
            count++;
        }
        idList++;
        if ((group & 0xFF) == 0xFF) {
            goto end;
        }
        if (D_L20_001B2FB8 < group) {
            goto end;
        }
        if (idList == 0) {
            goto end;
        }
        if (*(short *)(idList - 1) >= 0) {
            continue;
        }
        if (idList == (unsigned short *)D_L20_001FBB20[group]) {
            continue;
        }
        break;
    }
end:
    return count;
}

extern void func_002A7750(int, int, int);

/* Gets a moby ready for its next state: clears a counter, sets its hit value and flags, then switches to state 6. */
void func_L20_00440460(char *moby) {
    char *state = *(char **)(moby + 0x68);

    *(unsigned short *)(state + 0x178) = 0;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(int *)(moby + 0x98) = 0;
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
    SetMobyState(moby, 6, 3);
}
extern void func_00282CC0(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);
extern int func_00282948(char *);
extern void func_0029F338(char *);

/* Moves a piece of debris along its speed, pulls it down, draws an effect and removes it when its timer runs out. */
void func_L20_004404B8(char *moby) {
    char *q = moby + 0x10;
    char *state = *(char **)(moby + 0x68);

    FastVecAdd(q, q, state);
    *(float *)(state + 8) = *(float *)(state + 8) - *(float *)(state + 0x14);
    FastVecScale(state, state, *(float *)(state + 0x10));
    SweepCollisionFromObject(*(char **)(moby + 0xB8), q, 0x10001, 0,
                  *(float *)(state + 0x18), 3.0f, 1.0f, 1, 0);
    if (FastFloatHelperD(state + 0x1C) != 0) {
        MarkMobySpawned(moby);
    }
}

extern void func_0027DDC0(int, int, int, int);

/* Starts a screen-wide effect with fixed settings. */
void func_L20_00440570(void) {
    SetClearColorPacket(0, 0, 0, 0x80);
}

/* func_L20_00440598 is defined in L20_00440598-g8.c (it reaches data through $gp and needs -frac2-hazard-labels). */

/* func_L20_00441CB8 is defined in L20_00441CB8-g8.c. */

/* func_L20_004421A8 is defined in L20_004421A8-g8.c. */

/* func_L20_004424A0 is defined in L20_004424A0-helpers-g8.c. */
/* func_L20_004424A0 reads four constants through $gp: its near miss is in
   nonmatching/levels/func_L20_004424A0.c and belongs in the -G8 sibling. */

/* func_L20_00442550 is defined in L20_00442550-g8.c. */

extern void func_002A8C28(char *, char *, int, int, float, float, float, int,
                          int);

extern float func_00282E80(char *, char *);

extern void func_002B50E0(char *, char *, float);

extern void func_L01_00321178(char *, char *);

/* Draws an effect at the moby, then moves it toward a target if it is close enough, or uses the other approach when it is far away. */
void func_L20_004427C8(char *moby, char *target, float speed) {
    char *state = *(char **)(moby + 0x68);

    SweepCollisionFromObject(moby, moby + 0x10, 0x04010000, 0,
                  *(float *)(state + 0x50) + 0.5f, 50.0f, 1.0f, 1, 0);
    if (vec_distance_xy(moby + 0x10, target) <= *(float *)(state + 0x84)) {
        StepMovementController(moby, target, speed);
    } else {
        TurnMobyTowardTarget(moby, target);
    }
}


/* func_L20_004429F0 is defined in L20_004429F0-g8.c. */

extern int func_002A7820(int, int);

extern int func_L20_004433B0(char *);

extern int func_002A77E0(int);

/* Picks the next behaviour state for an enemy based on what it did last, and remembers the choice. */
void func_L20_00442C10(char *moby) {
    char *state = *(char **)(moby + 0x68);
    int previousMode = *(int *)(state + 0x17F4);
    int result;

    if (previousMode == 2) goto other;
    if (previousMode >= 3) goto other;
    if (previousMode != 1) goto other;
    result = FindNearestGroupTarget(moby);
    *(int *)(state + 0x17FC) = result;
    if (result == 0) {
        SetMobyState(moby, 0xC, 4);
    } else {
        SetMobyState(moby, 4, 2);
    }
    goto done;
other:
    result = RandomIntBelow(2) + 2;
    *(int *)(state + 0x17F8) = result;
    *(int *)(state + 0x1810) = RandomIntRange(0xB4, 0x168);
    SetMobyState(moby, 3, 1);
done:
    *(int *)(state + 0x17F4) = *(unsigned char *)(moby + 0x95);
}

/* func_L20_00442CD8 is defined in L20_00442CD8-g8.c. */

/* func_L20_00442E68 is defined in L20_00442E68-g8.c (it reaches data through $gp). */

extern int func_002ABB78(char *);

extern void func_L02_003A6F78(char *);

extern void func_L20_00449A78(char *);

/* Runs the right extra update for a moby depending on what kind of moby it is. */
void func_L20_00442F30(char *moby) {
    if (IsMobyInSpecialClassRange(moby) != 0) {
        FinishObjectAndReleaseChild(moby);
    } else if (*(short *)(moby + 0xAA) == 0x12D3) {
        ResetMobyToIdle(moby);
    }
}

/* func_L20_00442F80 is defined in L20_00442F80-g8.c. */

/* func_L20_004431E0 is defined in L20_004431E0-g8.c (it reads D_L20_001B2FB8 through $gp and needs -frac2-keep-block-order). */
/* func_L20_004431E0 reads a global through $gp: its near miss is in
   nonmatching/levels/func_L20_004431E0.c and belongs in the -G8 sibling. */

extern unsigned int D_L20_001B2F9C __attribute__((sda));
extern int func_L03_003CA138(char *);
/* func_L20_004499E8 is defined in L20_004499E8-g8.c. */
extern int func_L20_00449AC8(char *);

extern void func_0039BDF0(char *, char *, int, int);

/* Sets up the linked child moby at the target and returns it, or returns nothing if it is busy. */
char *func_L20_00443328(char *moby, char *target) {
    char *state = *(char **)(moby + 0x68);
    unsigned int childAddr = D_L20_001B2F9C + (*(int *)(state + 0x238) << 8);

    if (func_L20_00449AC8((char *)childAddr) != 0) {
        StartMobyPathMovement((char *)childAddr, moby, target);
        func_0039BDF0((char *)childAddr, (char *)(childAddr + 0x10), 0x168, 0);
        return (char *)childAddr;
    }
    return 0;
}
/* func_L20_004433B0 is defined in L20_004433B0-g8.c (it reaches a global through $gp). */

extern int func_0033E808(char *, int);

extern int func_003BA3F8(char *);

extern int func_L20_00449AD8(char *);

/* Tells whether a moby is a valid thing for this enemy to target. */
int func_L20_00443508(char *moby, char *candidate) {
    char *state = *(char **)(moby + 0x68);
    short classId;

    if (func_0033E808(candidate + 0x10, *(int *)(state + 0x220)) == 0) {
        goto ret0;
    }
    classId = *(short *)(candidate + 0xAA);
    if (classId < 0x1FF) {
        goto ret0;
    }
    if (classId < 0x201) {
        goto other;
    }
    if (classId != 0x12D3) {
        goto ret0;
    }
    if (func_L20_00449AC8(candidate) != 0) {
        goto ret0;
    }
    if (GetMobyTargetedFlag(candidate) != 0) {
        goto ret0;
    }
    return 1;
other:
    return func_003BA3F8(candidate) == 0;
ret0:
    return 0;
}

/* func_L20_004435A0 is in L20_004435A0-g8.c. */

/* func_L20_00443790 is defined in L20_00443790-helpers-g8.c. */

typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;

extern void func_00283098(void *, void *, void *);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);

/* Moves and spins a piece of debris, pulls it down, and removes it when its timer runs out. */
void func_L20_00443908(char *moby) {
    char *state = *(char **)(moby + 0x68);
    Vec4 v[6];

    FastVecAdd(moby + 0x10, moby + 0x10, state);
    *(float *)(state + 8) = *(float *)(state + 8) - *(float *)(state + 0x20);
    v[2].q = 0;
    v[2].f[2] = 0.5f;
    matrix_mul_vec3(&v[0], &v[2], moby + 0xC0);
    quaternion_to_rotation_basis(state + 0x10, &v[3]);
    multiply_matrix3x3(moby + 0xC0, &v[3], moby + 0xC0);
    matrix_mul_vec3(&v[1], &v[2], moby + 0xC0);
    FastVecSub(&v[2], &v[0], &v[1]);
    FastVecAdd(moby + 0x10, moby + 0x10, (char *)&v[2]);
    if (FastFloatHelperD(state + 0x24) != 0) {
        MarkMobySpawned(moby);
    }
}

/* func_L20_00443A10 lives in L20_00443A10-g8.c. */

/* func_L20_00443B60 is defined in L20_00443B60-helpers.c. */

extern void func_L20_00443B60(char *, char *, char *, float *);
extern u8 *func_L20_00440198(int, const float *, const float *, float);

/* Finds the group member to activate along the enemy aim and returns it. */
u8 *func_L20_00443CF0(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 origin;
    TI128 direction;
    float spread;

    spread = 1.0471977f;
    ComputeShotLaunch(moby, (char *)&origin, (char *)&direction, &spread);
    return ActivateGroupMemberAt(*(int *)(state + 0x21C), (float *)&origin, (float *)&direction, spread);
}

extern char *func_L20_00449FD0(char *, char *, char *, float, int, float);

/* Fires a new projectile along the enemy aim with a random lifetime. */
char *func_L20_00443D58(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 origin;
    TI128 direction;
    float spread;
    float spreadCopy;
    int lifetime;

    spread = 1.0471977f;
    ComputeShotLaunch(moby, (char *)&origin, (char *)&direction, &spread);
    spreadCopy = spread;
    lifetime = RandomIntRange(0x12C, 0x258);
    return SpawnYeedilProjectile_L20_2(moby, (char *)&origin, (char *)&direction, spreadCopy, lifetime, (float)*(unsigned char *)(state + 0x36));
}

/* func_L20_00443DF0 is defined in L20_00443DF0.c (it needs -frac2-hazard-labels). */

/* func_L20_00444018 is defined in L20_00444088-g8.c (it needs this unit's -fno-schedule-insns). */

/* func_L20_00444088 is defined in L20_00444088-g8.c (it reaches a global through
   $gp and needs its own -fno-schedule-insns). */


/* func_L20_00444138 is defined in L20_00444138-g8.c (it reads a global through $gp and
   needs its own -mno-split-addresses). */

/* func_L20_004441D8 is defined in L20_004441D8-g8.c (it reaches globals through $gp and
   needs -frac2-sticky-volatile-refs). */

/* func_L20_004448A8 is defined in L20_004448A8-g8.c (it needs the -G8 profile with split addresses). */

extern float func_00283248(float, float);

extern float func_00283BE0(float, float);

/* Works out how far an enemy must turn to face a point and stores it, limited to about 60 degrees. */
void func_L20_00444AA8(char *moby, float *targetPos) {
    char *state = *(char **)(moby + 0x68);
    float angle;

    angle = FastMatrixHelperA(targetPos[0] - *(float *)(moby + 0x10),
                      targetPos[1] - *(float *)(moby + 0x14));
    angle = fast_subtract_rotations(angle, *(float *)(moby + 0xF8));
    if (angle > 1.0471977f) {
        angle = 1.0471977f;
    } else if (angle < -1.0471977f) {
        angle = -1.0471977f;
    }
    *(float *)(state + 0x2B8) = angle;
}

/* func_L20_00444B48 is defined in L20_00444B48-g8.c. */

extern void func_L00_002E6EF8(void (*)(void), int);

/* Puts a moby into state 18 and queues the screen effect. */
void func_L20_00444C68(int moby) {
    SetMobyState(moby, 0x12, -1);
    AddDrawCallbackToList3(StartScreenEffect, moby);
}

/* func_L20_00444CA8 is defined in L20_00444CA8.c. */

/* func_L20_004450D8 is defined in L20_004450D8-g8.c (it reads a global through $gp). */

/* func_L20_004451C0 is defined in L20_004451C0-g16.c (it reaches two 16-byte vectors through $gp). */

/* The level's own jump table (the label of the data blob at 0x002B5960). */
extern void *jtbl_002B5960[];

extern int func_002B3868(char *);

extern int func_002B38B8(char *);

extern void func_002AA548(char *, char *, float, float, float, float);

extern int func_002E5CF8(int, int, char *);

extern unsigned char D_0019B2E8[];
extern int D_001A79F0 MACRO_ADDR;

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
/* Updates a platform that rises when a switch is pressed and plays a sound as it starts moving. */
void func_L20_00445738(char *moby) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(moby + 0x20);
    state = *(char **)(moby + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5960[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(moby + 0x10);
    SetMobyState(moby, 1, -1);
    goto out;
c1:
    if ((D_0019B2E8[((unsigned char *)moby)[0xB0] + gCurrentMapIndex * 16] & 0x80) == 0) {
        goto end;
    }
    SetMobyState(moby, 2, -1);
    goto out;
c2:
    if (SetFirstPendingFlag(moby) != 0) {
        *(int *)(state + 0x14) = 0;
        PlayMobySound(0, 0, moby);
    }
    StepValueTowardTarget(moby + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (IsThirdPendingFlagSet(moby) == 0) {
        goto end;
    }
    SetMobyState(moby, 4, -1);
    goto out;
c4:
    if (SetFirstPendingFlag(moby) != 0) {
        PlayMobySound(0, 0, moby);
        *(int *)(state + 0x14) = 0;
    }
    StepValueTowardTarget(moby + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

/* func_L20_00445890 is defined in L20_00445890-g8.c. */

/* The level's own jump table (the label of the data blob at 0x002B5980). */
extern void *jtbl_002B5980[];

extern int func_002B3868(char *);

extern int func_002B38B8(char *);

extern void func_002AA548(char *, char *, float, float, float, float);

extern unsigned char D_0019B2E8[];

/* The five behaviours the object's state byte selects; the table in the level's data
   holds the address of each. */
/* Updates a platform that rises when a switch is pressed, like the one above but silent. */
void func_L20_00446E70(char *moby) {
    static void * volatile tab[] = { &&c0, &&c1, &&c2, &&c3, &&c4 };
    char *state;
    unsigned char sel;

    sel = *(unsigned char *)(moby + 0x20);
    state = *(char **)(moby + 0x68);
    if (sel >= 5) {
        goto end;
    }
    goto *jtbl_002B5980[sel];
c0:
    *(float *)(state + 0x10) = *(float *)(moby + 0x10);
    SetMobyState(moby, 1, -1);
    goto out;
c1:
    if ((D_0019B2E8[((unsigned char *)moby)[0xB0] + *(int *)0x001A79F0 * 16] & 0x80) == 0) {
        goto end;
    }
    SetMobyState(moby, 2, -1);
    goto out;
c2:
    if (SetFirstPendingFlag(moby) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    StepValueTowardTarget(moby + 0x10, state + 0x14,
                  *(float *)(state + 0x10) - *(float *)(state + 0x0),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
c3:
    if (IsThirdPendingFlagSet(moby) == 0) {
        goto end;
    }
    SetMobyState(moby, 4, -1);
    goto out;
c4:
    if (SetFirstPendingFlag(moby) != 0) {
        *(int *)(state + 0x14) = 0;
    }
    StepValueTowardTarget(moby + 0x10, state + 0x14, *(float *)(state + 0x10),
                  *(float *)(state + 0x8), *(float *)(state + 0x8),
                  *(float *)(state + 0xC));
    goto out;
end:
out:
    return;
}

extern int func_L00_00324120(char *);
extern float func_00282C48(float);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_L14_003DE908(char *);
extern void func_002AD6F0(void *, void *, void *, void *);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot D_00188660[];
extern float D_00189EA4;

/* Updates an elevator that slides between two heights with a sound, and carries anything standing on it. */
void func_L20_00446FA8(char *moby) {
    Vec4 pos, rot, delta;
    char *state = *(char **)(moby + 0x68);
    qcopy(&pos, moby+0x10);
    qcopy(&rot, moby+0xF0);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(state+0x5C) |= 1;
        {
            float target=*(float *)(state+0x60);
            float start=*(float *)(moby+0x14);
            *(float *)(state+0x6C) = 0.0011666667f;
            *(float *)(state+0x64) = start;
            *(float *)(state+0x70) = (start+target)*0.5f;
        }
        if (*(int *)(state+0x78) == 0) *(int *)(state+0x74)=0;
        else *(int *)(state+0x74)=1;
        SetMobyState(moby,1,-1);
        break;
    case 1:
        if (IsThirdPendingFlagSet(moby)) {
            if (IsCurrentSelectedId(moby) || (*(float *)(moby+0x14)-*(float *)(state+0x70))*(D_00189EA4-*(float *)(state+0x70)) < 0.0f) {
                if (*(int *)(state+0x74)==0) SetMobyState(moby,2,-1);
                else SetMobyState(moby,3,-1);
                if (!IsVoicePlayingForOwner(moby,*(int *)(state+0x7C))) *(int *)(state+0x7C)=PlayMobySound(0,4,moby);
            }
        }
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) *(int *)(state+0x68)=0;
        if (FloatAbs(*(float *)(state+0x60)-*(float *)(moby+0x14)) < 0.03f) {
            int slotIndex=*(int *)(state+0x7C);
            if (slotIndex != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)gSoundState+slotIndex*0x70);
                if (slot->owner==moby && slot->active) StopSoundVoice(slotIndex);
            }
            *(int *)(state+0x7C)=-1;
            if (!IsObjectHitByPlayerOrAimRay(moby)) {
                *(int *)(state+0x74)=1;
                *(float *)(moby+0x14)=*(float *)(state+0x60);
                SetMobyState(moby,1,-1);
            }
        } else StepValueTowardTarget(moby+0x14,state+0x68,*(float *)(state+0x60),*(float *)(state+0x6C),*(float *)(state+0x6C),0.20000002f);
        break;
    case 3:
        if (SetFirstPendingFlag(moby)) *(int *)(state+0x68)=0;
        if (FloatAbs(*(float *)(moby+0x14)-*(float *)(state+0x64)) < 0.03f) {
            int slotIndex=*(int *)(state+0x7C);
            if (slotIndex != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)gSoundState+slotIndex*0x70);
                if (slot->owner==moby && slot->active) StopSoundVoice(slotIndex);
            }
            *(int *)(state+0x7C)=-1;
            if (!IsObjectHitByPlayerOrAimRay(moby)) {
                *(int *)(state+0x74)=0;
                *(float *)(moby+0x14)=*(float *)(state+0x64);
                SetMobyState(moby,1,-1);
            }
        } else StepValueTowardTarget(moby+0x14,state+0x68,*(float *)(state+0x64),*(float *)(state+0x6C),*(float *)(state+0x6C),0.20000002f);
        break;
    }
    FastVecSub(&delta,moby+0x10,&pos);
    CombineTransformsAndStore(state+0x20,&delta,&rot,moby+0xF0);
}

extern void func_L00_003294F0(char *, int);
extern void func_L20_00447640(char *);

/* Updates a platform that rises, waits, drops and waits again in a repeating cycle. */
void func_L20_004473B0(char *moby) {
    char *state;
    TI128 pos, rot, delta;
    float accel;

    state = *(char **)(moby + 0x68);
    qcopy(&pos, moby + 0x10);
    qcopy(&rot, moby + 0xF0);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        qcopy(state + 0x60, moby + 0x10);
        *(int *)(state + 0x5C) |= 1;
        SetObjectFlagBit(moby, 1);
        SetMobyState((int)moby, 4, -1);
        break;
    case 1:
        if (SetFirstPendingFlag(moby) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x74);
        }
        if (FastFloatHelperD(state + 0x84) != 0) {
            SetMobyState((int)moby, 2, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68) + speed;
            accel = (speed * 4.0f) / (float)(duration * duration);
            StepValueTowardTarget(moby + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(moby) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x78);
        }
        if (FastFloatHelperD(state + 0x84) != 0) {
            SetMobyState((int)moby, 3, -1);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(moby) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x7C);
        }
        if (FastFloatHelperD(state + 0x84) != 0) {
            SetMobyState((int)moby, 4, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68);
            accel = (speed * 4.0f) / (float)(duration * duration);
            StepValueTowardTarget(moby + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(moby) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x80);
        }
        if (FastFloatHelperD(state + 0x84) != 0) {
            SetMobyState((int)moby, 1, -1);
        }
        break;
    }
    if (IsThirdPendingFlagSet(moby) == 0) {
        if (0.0f < *(float *)(state + 0x8C)) {
            DestroyGroupProtopets(moby);
            *(float *)(state + 0x8C) = -1000.0f;
        }
    }
    FastVecSub(&delta, moby + 0x10, &pos);
    CombineTransformsAndStore(state + 0x20, &delta, &rot, moby + 0xF0);
}

/* func_L20_00447640 is defined in L20_00447640-g8.c (it reads D_L20_001B2FB8 through $gp). */

/* func_L20_00447748 is defined in L20_00447748-g8.c. */

extern char D_L20_002AB980[];

extern void func_L04_003A21F8();

/* Starts the level effect with a fixed setting. */
void func_L20_00447908(void) {
    render_water_grids(D_L20_002AB980, 6);
}

/* func_L20_00447930 is defined in L20_00447930-g8.c (it reaches data through $gp). */

extern float func_00283B98(float, float);
extern int func_00277258(char *, int, char *, float);
extern float func_00282DB0(char *, char *);
extern void func_00282F20(char *, char *, float);
extern float func_00282DF0(char *);

extern char D_L20_001C0430[];

/* Moves, spins and bounces a piece of debris off walls, then fades it out and removes it. */
void func_L20_00448858(char *moby) {
    char *state = *(char **)(moby + 0x68);
    float velocityZ, speed;
    char bounce[0x10];

    velocityZ = *(float *)(state + 8);
    *(float *)(state + 8) = velocityZ - (velocityZ > 0.0f ? *(float *)(state + 0x20) * 4.0f : *(float *)(state + 0x20));

    FastVecAdd(moby + 0x10, moby + 0x10, state);
    *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), *(float *)(state + 0x10));
    *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), *(float *)(state + 0x14));
    *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), *(float *)(state + 0x18));

    if (TestPointAgainstCollision(moby + 0x10, 0, moby, 1.5f) != 0) {
        char *hitInfo = D_L20_001C0430;

        qcopy(moby + 0x10, hitInfo);
        if (FastVecDot(state, hitInfo + 0x10) < 0.0f) {
            vec_scale_to_length(hitInfo + 0x10, hitInfo + 0x10, 1.0f);
            speed = FastVecLength(state);
            FastVecScale(bounce, hitInfo + 0x10, -FastVecDot(state, hitInfo + 0x10) * 1.25f);
            FastVecAdd(state, state, bounce);
            vec_scale_to_length(state, state, speed * 0.5f);
        }
        *(int *)(state + 0x24) = 0;
        if ((unsigned char)moby[0x23] > 0x60) {
            moby[0x23] = 0x60;
        }
    }

    if (FastFloatHelperD(state + 0x24) != 0) {
        if ((unsigned char)moby[0x23] < 5) {
            MarkMobySpawned(moby);
        } else {
            moby[0x23] = moby[0x23] - 4;
        }
    }
}

/* func_L20_00448A18 is defined in L20_00448A18-helpers-g8.c. */
/* func_L20_00448A18 reaches four globals through $gp: its near miss is in
   nonmatching/levels/func_L20_00448A18.c and belongs in the -G8 sibling. */
