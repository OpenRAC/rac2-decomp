#include "common.h"

extern int moby_is_first_state(char *);
extern unsigned int moby_get_targeted_flag(char *);
extern int moby_is_state_six(char *);
extern float vec_distance_xy(void *, void *);
extern char *D_L20_001B2F9C;
extern unsigned short *D_L20_001FBB20[];
extern int D_L20_001B2FB8 __attribute__((sda));

/* Returns the object at state+0x238 unless func_L03_003CA138 or func_L20_00449AD8 rejects
   it; then the member of the group at state+0x218 nearest to this object (within 200,
   skipping those func_00312B58 accepts), or 0.  The loop is the group-iteration form used
   by func_00325DA0. */
/* Chooses a target for the enemy. It keeps its current one if that is still good, otherwise the nearest valid object of its group within 200 units. */
char *yeedil_boss_find_group_target(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *candidate = D_L20_001B2F9C + (*(int *)(state + 0x238) << 8);
    char *best;
    unsigned short *p;
    char *e;
    float closest;

    if (!moby_is_first_state(candidate) && !moby_get_targeted_flag(candidate)) {
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
        if (!moby_is_state_six(e)) {
            float distance = vec_distance_xy(e + 0x10, object + 0x10);
            if (distance < closest) {
                closest = distance;
                best = e;
            }
        }
    }
    return best;
}
