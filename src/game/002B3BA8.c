#include "include_asm.h"
/* Picks the aim target: the indexed one, or the nearest candidate of four kinds (player,
 * two moby lists and a table) within range, and records it in the aim block. */
#include "common.h"

extern int D_001A8CA0 __attribute__((sda));
extern int func_002B3B20(char *p, char *q, float f12, float f13);
extern float func_002B38C8(char *object, char *target);

typedef int Vec128_2B3BA8 __attribute__((mode(TI)));

typedef struct {
    Vec128_2B3BA8 position;
    char *target;
    int found;
    int unused;
    int kind;
} Aim_2B3BA8;

typedef struct {
    char pad0[0xD0];
    Vec128_2B3BA8 position;
    char pad1[0x2290 - 0xE0];
    char *moby;
    int state;
} Player_2B3BA8;

extern Player_2B3BA8 D_00189E20;
extern int D_001A8BB0 __attribute__((sda));
extern short D_001B1CB0[2] __attribute__((sda));
extern short D_001B1CF0[2] __attribute__((sda));
extern char *D_001B1B5C __attribute__((sda));
extern int D_001A8CD4 __attribute__((sda));
extern char *D_001C13E8[];
extern char *func_002B39A0(char *, int, int *);
extern float *func_002AB1F0(char *);
extern void func_002AFD88(char *, char *, float, float, float);

/* Picks what the object should aim at: a chosen target, or the best-rated one among the player, decoys, other objects in a table and a fourth group, and records it. */
int func_002B3BA8(char *self, int index, Vec128_2B3BA8 *point, int force, float range, float height)
{
    float origin[4] __attribute__((aligned(16)));
    int kind;
    Aim_2B3BA8 *aim;
    char *best;
    char *mob;
    float best_distance;
    int best_kind;
    int i;

    if ((*(unsigned short *)(self + 0x34) & 0x20) == 0)
        return 0;
    aim = *(Aim_2B3BA8 **)(*(char **)(self + 0x68) + 0xC);
    if (point != 0)
        *(Vec128_2B3BA8 *)origin = *point;
    else
        *(Vec128_2B3BA8 *)origin = *(Vec128_2B3BA8 *)(self + 0x10);
    aim->target = gHeroState.moby;
    qcopy(&aim->position, &gHeroState.position);
    aim->kind = 0;
    aim->found = 0;
    if (force == 0) {
        if (gCurrentGameMode != 0)
            return 0;
        if (gHeroState.state == 0x6F)
            return 0;
    }
    if (index != -1) {
        mob = PickBestLinkedTarget(self, index, &kind);
        if (mob != 0) {
            aim->target = mob;
            aim->found = 1;
            aim->kind = kind;
            if (mob != gHeroState.moby) {
                float *info;
                qcopy(&aim->position, mob + 0x10);
                info = GetMobyPrivateValue0(mob);
                if (info != 0) {
                    if (D_001A8CA0 == 0)
                        *(float *)((char *)aim + 8) += info[4];
                    else
                        AddTransformedPointToVector(mob, (char *)aim, 0.0f, 0.0f, info[4]);
                }
            }
        }
        return aim->found;
    } else {
        best_distance = 9999999.0f;
        best = 0;
        best_kind = 0;
        mob = gHeroState.moby;
        if (IsTargetWithinRangeAndHeight(mob, (char *)origin, range, height)) {
            float distance = RateAimTarget(self, mob);
            if (distance < best_distance) {
                best = mob;
                best_distance = distance;
                best_kind = 1;
            }
        }
        for (i = 1; i <= D_001B1CB0[0]; i++) {
            mob = D_001B1B5C + (D_001B1CB0[i] << 8);
            if (mob != 0 && *(short *)(mob + 0xAA) == 0xCB /* Decoy */
                && *(unsigned char *)(mob + 0x20) != 0xFE
                && *(unsigned char *)(mob + 0x20) != 0xFD
                && *(unsigned char *)(mob + 0x20) == 3
                && IsTargetWithinRangeAndHeight(mob, (char *)origin, range, height)) {
                float distance = RateAimTarget(self, mob);
                if (distance < best_distance) {
                    best = mob;
                    best_distance = distance;
                    best_kind = 2;
                }
            }
        }
        for (i = 0; i < D_001A8CD4; i++) {
            mob = D_001C13E8[i];
            if (IsTargetWithinRangeAndHeight(mob, (char *)origin, range, height)) {
                float distance = RateAimTarget(self, mob);
                if (distance < best_distance) {
                    best = mob;
                    best_distance = distance;
                    best_kind = 3;
                }
            }
        }
        for (i = 1; i <= D_001B1CF0[0]; i++) {
            mob = D_001B1B5C + (D_001B1CF0[i] << 8);
            if (mob != 0 && *(short *)(mob + 0xAA) == 0xEB0 /* Dark Sheep */
                && *(unsigned char *)(mob + 0x20) != 0xFE
                && *(unsigned char *)(mob + 0x20) != 0xFD
                && IsTargetWithinRangeAndHeight(mob, (char *)origin, range, height)) {
                float distance = RateAimTarget(self, mob);
                if (distance < best_distance) {
                    best = mob;
                    best_distance = distance;
                    best_kind = 4;
                }
            }
        }
        if (best != 0) {
            aim->kind = best_kind;
            aim->found = 1;
            aim->target = best;
            if (best == gHeroState.moby) {
                qcopy(&aim->position, &gHeroState.position);
            } else {
                float *info;
                qcopy(&aim->position, best + 0x10);
                info = GetMobyPrivateValue0(best);
                if (info != 0) {
                    if (D_001A8CA0 != 0)
                        AddTransformedPointToVector(best, (char *)aim, 0.0f, 0.0f, info[4]);
                    else
                        *(float *)((char *)aim + 8) += info[4];
                }
            }
        }
    }
    return aim->found;
}
