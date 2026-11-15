#include "include_asm.h"
#include "names.h"

/* func_L22_003A3550 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern char *ref_L22_003A3550_00 __attribute__((sda));

extern int *D_L22_001FE940[];

extern char D_00189EA0[];

extern float func_002F3C40(char *, char *);

extern int func_002A77E0(int);

extern int func_L22_003A48F8(int);

extern void func_L22_003A2988(char *, float);

/* Picks a random lane point that is not close to the ship and returns it, pushed out by the given distance. */
int func_L22_003A3550(char *outPoint, int requireAllowed, float extra) {
    char *state = *(char **)(ref_L22_003A3550_00 + 0x68);
    char *slots = state + 0x2A0;
    float best = 45.0f;
    int found;
    int laneIndex;
    int j;
    int *lane;
    char *point;
    int pointIndex;

    for (;;) {
        found = 0;
        laneIndex = RandomIntBelow(0x20);
        lane = D_L22_001FE940[*(int *)(slots + (laneIndex << 2))];
        point = (char *)lane + 0x10;
        for (j = 0; j < *lane; j++) {
            if (func_002F3C40(gHeroPosition, point) < best) {
                found = 1;
                break;
            }
            point += 0x10;
        }
        if (found)
            continue;
        if (requireAllowed == 0)
            continue;
        if (IsKeyMissingFromList(laneIndex) == 0)
            continue;
        break;
    }
    pointIndex = RandomIntBelow(*lane - 1);
    *(TI128 *)outPoint = *(TI128 *)((char *)lane + pointIndex * 16 + 0x10);
    PushPointOutOfArena(outPoint, extra);
    return 1;
}
