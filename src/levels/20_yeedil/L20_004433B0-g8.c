#include "common.h"

extern int func_L03_003CA138(char *);
extern unsigned int func_L20_00449AD8(char *);
extern int func_00312B58(char *);
extern float func_00282E80(void *, void *);
extern char *D_L20_001B2F9C;
extern unsigned short *D_L20_001FBB20[];
extern int D_L20_001B2FB8 __attribute__((sda));

/* Returns the object at state+0x238 unless func_L03_003CA138 or func_L20_00449AD8 rejects
   it; then the member of the group at state+0x218 nearest to this object (within 200,
   skipping those func_00312B58 accepts), or 0.  The loop is the group-iteration form used
   by func_00325DA0. */
/* Chooses a target for the enemy. It keeps its current one if that is still good, otherwise the nearest valid object of its group within 200 units. */
char *func_L20_004433B0(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *candidate = D_L20_001B2F9C + (*(int *)(state + 0x238) << 8);
    char *best;
    unsigned short *p;
    char *e;
    float closest;

    if (!IsMobyInState1_L03(candidate) && !GetMobyTargetedFlag(candidate)) {
        return candidate;
    }
    best = 0;
    closest = 200.0f;
    for (p = D_L20_001FBB20[*(int *)(state + 0x218)];
         (*(int *)(state + 0x218) & 0xFF) != 0xFF && *(int *)(state + 0x218) <= D_L20_001B2FB8 && p != 0 &&
         ((p != 0 && (short)p[-1] >= 0) || p == D_L20_001FBB20[*(int *)(state + 0x218)]);
         p++) {
        e = D_L20_001B2F9C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (!IsMobyInState6(e)) {
            float distance = vec_distance_xy(e + 0x10, object + 0x10);
            if (distance < closest) {
                closest = distance;
                best = e;
            }
        }
    }
    return best;
}
