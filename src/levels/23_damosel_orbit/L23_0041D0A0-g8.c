#include "include_asm.h"
#include "names.h"

/* func_L23_0041D0A0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern char *D_L23_001B1484 __attribute__((sda));

extern int *D_L23_001FF300[];

extern char D_00189EA0[];

extern float func_00282E48(char *, char *);

extern int func_002A77E0(int);

extern int func_L23_00419CA0(int);

extern void func_L23_00418650(char *, float);

/* Picks a random path point that is far enough from the hero and stores it as a spawn position. */
int func_L23_0041D0A0(char *outPos, int onlyAllowed, float heightOffset) {
    char *state = *(char **)(gMothershipBossMoby + 0x68);
    char *slots = state + 0x230;
    float best = 45.0f;
    int found;
    int slotIndex;
    int j;
    int *list;
    char *p;
    int pointIndex;

    for (;;) {
        found = 0;
        slotIndex = RandomIntBelow(0x2F);
        list = gPathLists[*(int *)(slots + (slotIndex << 2))];
        p = (char *)list + 0x10;
        for (j = 0; j < *list; j++) {
            if (fast_vec_dist(gHeroPosition, p) < best) {
                found = 1;
                break;
            }
            p += 0x10;
        }
        if (found)
            continue;
        if (onlyAllowed == 0)
            continue;
        if (IsValueNotInSlotTable(slotIndex) == 0)
            continue;
        break;
    }
    pointIndex = RandomIntBelow(*list - 1);
    *(TI128 *)outPos = *(TI128 *)((char *)list + pointIndex * 16 + 0x10);
    ProjectPointOntoPlanetSurface(outPos, heightOffset);
    return 1;
}
