#include "common.h"

extern int moby_is_first_state(char *);
extern unsigned int moby_get_targeted_flag(char *);
extern int moby_is_state_six(char *);
extern float vec_distance_xy(void *, void *);
extern char *g_group_l20_member_table;
extern unsigned short *g_group_l20_id_lists[];
extern int g_group_count __attribute__((sda));

/* Returns the object at state+0x238 unless func_L03_003CA138 or func_L20_00449AD8 rejects
   it; then the member of the group at state+0x218 nearest to this object (within 200,
   skipping those func_00312B58 accepts), or 0.  The loop is the group-iteration form used
   by func_00325DA0. */
/* Chooses a target for the enemy. It keeps its current one if that is still good, otherwise the nearest valid object of its group within 200 units. */
char *yeedil_boss_find_group_target(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *candidate = g_group_l20_member_table + (*(int *)(state + 0x238) << 8);
    char *best;
    unsigned short *p;
    char *e;
    float closest;

    if (!moby_is_first_state(candidate) && !moby_get_targeted_flag(candidate)) {
        return candidate;
    }
    best = 0;
    closest = 200.0f;
    for (p = g_group_l20_id_lists[*(int *)(state + 0x218)];
         (*(int *)(state + 0x218) & 0xFF) != 0xFF && *(int *)(state + 0x218) <= g_group_count && p != 0 &&
         ((p != 0 && (short)p[-1] >= 0) || p == g_group_l20_id_lists[*(int *)(state + 0x218)]);
         p++) {
        e = g_group_l20_member_table + ((*p & 0x7FFF) << 8);
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
