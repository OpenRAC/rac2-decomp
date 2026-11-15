#include "include_asm.h"
#include "names.h"

extern void func_002E37B0(void);

extern void func_002E3548(void);

extern void func_002E3820(void);

extern void func_002FC560(unsigned int, unsigned long);

extern void func_L02_00363D78(void);

extern int D_001A79F0;

extern int D_001A72E0;

extern char D_L02_00280A10[];

extern int D_L02_001B33D0;

/* func_L02_003CB090 needs a $gp member and an absolute one; the measured
   92-of-96-byte candidate is recorded in nonmatching/levels/func_L02_003CB090.c
   (residue: branch-likely + which register gets the absolute address). */

extern int func_002ACBC8(void *point, int index);

extern void func_00282CF0(float *out, const float *a, const float *b);

extern void func_00283098(float *out, const float *a, const float *b);

extern void func_L02_002DCEA0(int a0, float a1);

extern void func_L00_002B9D60(int a0, int a1, int a2, int a3);

extern char D_00189EA0[];

extern char D_L02_001BA500[];

extern char *D_L02_001B368C;

extern float D_L02_001B2FE0 __attribute__((sda));


/* Runs the level's background update each frame: the sky when the game state is 2, the normal backdrop otherwise. */
void func_L02_00300738(void) {
    ResetResidentTable();
    D_L02_001B33D0 = (int)D_L02_00280A10;

    if (gCurrentMapIndex == 2)
        UpdateSkyEffects();
    else
        UpdateAllViewTransforms();
    LinkRenderPacketChain();
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x4E, 0x01000000 | (D_001A72E0 >> 13));
}

/* Flags the actor's target when its record is on screen, and refreshes it afterwards. */
void func_L02_003D02F0(char *self) {
    char *state = *(char **)(self + 0x68);
    float offset[4];

    if (*(int *)(state + 0xDC) == 0) {
        if (IsPointInCuboid(gHeroPosition, *(int *)(state + 0xC4)) != 0) {
            FastVecSub(offset, (float *)gCameraPosition_L02,
                          (float *)(D_L02_001B368C + (*(int *)(state + 0xC4) << 7) + 0x30));
            matrix_mul_vec3(offset, offset, (float *)(D_L02_001B368C + (*(int *)(state + 0xC4) << 7) + 0x40));
            if (offset[0] > 0.0f) {
                *(int *)(state + 0xDC) = 1;
                StartTimedCountdown(1, 10.0f);
            }
        }
    } else {
        if (D_L02_001B2FE0 >= 1.0f) {
            ResetHeroPositionAndDirection((int)gHeroPosition,
                              (int)(D_L02_001B368C + (*(int *)(state + 0xC4) << 7) + 0x70), 0, 1);
            *(short *)(gHeroPosition + 0x160) = 10;
        }
    }
}

extern unsigned short *D_L02_001FC060[];

extern unsigned char *D_L02_001B359C;

/* Answers 1 when the object's group holds an armed 0x9CA entity (class byte 6, state word
   +0x2F6 == 1) that is not being freed (state byte 0xFE or 0xFD). */
int func_L02_003D18D8(unsigned char *self) {
    unsigned short *groupList;
    unsigned short *entry;
    unsigned char *entity;

    if (self[0x21] == 0xFF)
        return 0;
    groupList = gEntityGroupLists[self[0x21]];
    if (groupList == 0)
        return 0;
    entry = groupList;
    do {
        entity = gMobyPool_L02 + ((*entry & 0x7FFF) << 8);
        if (entity != 0 && entity[0x20] != 0xFE && entity[0x20] != 0xFD && *(short *)(entity + 0xAA) == 0x9CA /* moby class 2506 */ &&
            entity[0x95] == 6 && *(short *)(*(unsigned char **)(entity + 0x68) + 0x2F6) == 1)
            return 1;
    } while (*(short *)entry++ >= 0);
    return 0;
}

extern int D_L02_001B35B8 __attribute__((sda));

extern int func_002B3BA8(char *, int, float, float, int, int);

extern int func_L02_003FC0D0(int, short);

extern float func_00282E80(void *, void *);

/* Pairs the actor with a partner: keeps the one it already has (state +0x2E0, mode +0x2F6),
   or picks the nearest free 0x9CA entity of its group and links the two.
   The early exit writes its own `+0x2F6 = 0` (jump2's cross-jumping merges it with the last
   one, which gives retail's `b` to that store); a `goto` to the shared store instead leaves
   `state` one reference short, and global.c then gives `self` the lower saved register. The
   two early stores are in the reverse of retail's order (the scheduler swaps them). */
void func_L02_003D1998(char *self) {
    char *state = *(char **)(self + 0x68);
    unsigned char *partner;
    unsigned short *entry;
    unsigned char *entity;
    unsigned char *nearestEntity;
    float nearestDist;

    if (*(unsigned char *)(self + 0x20) < 4) {
        *(short *)(state + 0x2F6) = 0;
        *(int *)(state + 0x2E0) = 0;
        return;
    }
    if (*(short *)(state + 0x2F6) == 1) {
        *(short *)(state + 0x2FA) =
            SelectAimTarget_002B3BA8(self, *(int *)(state + 0x2F0), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x2E0) = *(int *)(state + 0x200);
    } else if (TakeEnemyQuota(*(int *)(self + 0xB8), *(short *)(self + 0xAA)) != 0) {
        *(short *)(state + 0x2F6) = 1;
        *(short *)(state + 0x2FA) =
            SelectAimTarget_002B3BA8(self, *(int *)(state + 0x2F0), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x2E0) = *(int *)(state + 0x200);
    } else if (*(short *)(state + 0x2F6) == 2 && *(char **)(state + 0x2E0) != 0) {
        char *partnerState;

        partner = *(unsigned char **)(state + 0x2E0);
        partnerState = *(char **)(partner + 0x68);
        if (partner[0x20] != 0xFE) {
            if (partner[0x20] != 0xFD) {
                if (partner[0x95] != 0) {
                    if (partner[0x95] != 1 && *(short *)(partnerState + 0x2F6) == 2 &&
                        *(char **)(partnerState + 0x2E0) == self) {
                        *(short *)(state + 0x2FA) = 2;
                        *(short *)(partnerState + 0x2FA) = 2;
                        return;
                    }
                }
            }
        }
        *(int *)(state + 0x2E0) = 0;
        *(short *)(state + 0x2F6) = 0;
    } else {
        nearestDist = 1000.0f;
        nearestEntity = 0;
        for (entry = gEntityGroupLists[*(unsigned char *)(self + 0x21)];
             *(unsigned char *)(self + 0x21) != 0xFF &&
             *(unsigned char *)(self + 0x21) <= D_L02_001B35B8 && entry != 0 &&
             ((entry != 0 && (short)entry[-1] >= 0) ||
              entry == gEntityGroupLists[*(unsigned char *)(self + 0x21)]);
             entry++) {
            entity = gMobyPool_L02 + ((*entry & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (entity[0x20] != 0xFE) {
                if (entity[0x20] != 0xFD && entity != (unsigned char *)self && entity[0x20] >= 3 &&
                    *(short *)(entity + 0xAA) == 0x9CA /* moby class 2506 */ &&
                    *(short *)(*(char **)(entity + 0x68) + 0x2F6) == 0) {
                    if (vec_distance_xy(self + 0x10, entity + 0x10) < nearestDist) {
                        nearestEntity = entity;
                        nearestDist = vec_distance_xy(self + 0x10, entity + 0x10);
                    }
                }
            }
        }
        if (nearestEntity != 0) {
            char *bestState;

            *(unsigned char **)(state + 0x2E0) = nearestEntity;
            *(short *)(state + 0x2F6) = 2;
            *(short *)(state + 0x2FA) = 2;
            bestState = *(char **)(nearestEntity + 0x68);
            *(short *)(bestState + 0x2F6) = 2;
            *(char **)(bestState + 0x2E0) = self;
            *(short *)(bestState + 0x2FA) = 2;
        } else {
            *(short *)(state + 0x2F6) = 0;
        }
    }
}
