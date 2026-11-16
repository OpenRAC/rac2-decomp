#include "common.h"

/* func_L08_0032F898 sits in its own unit: it needs common.h's quadword helpers, which the
   parent file L08_002D90C8.c does not include. */

/* The fields of the resident block at D_00189E20 this function reads. */
typedef struct {
    char head[0x2290];
    char *selected;
    int mode;
    int pad;
    int state;
} SelectState;

extern SelectState g_hero_state;
/* A moby index list (count in element 0) and the moby array base: retail reads both
   through the absolute macro form, and the count through $gp in one delay slot. */
extern short g_active_moby_indices[] __attribute__((sda));
extern char *g_moby_array[] __attribute__((sda));

extern int func_L08_0032E920(void *, int, int, int, int);
extern float vec_distance_xy(void *, void *);

/* Picks the listed moby of class 0xCB, 0x76C or 0xEB0 in state 3 nearest to input+0x10
   and closer than `minimum`; one at or beyond `limit` must also pass func_L08_0032E920.
   The starting candidate is the pointer at D_00189E20+0x2290, dropped (result 2) when the
   state word is 0x18, the mode word is 0x6F, or the point at D_00189E20+0x80 fails
   func_L08_0032E920 and lies beyond `limit`. Writes the choice, its position, its +0xF0
   vector and two more vectors to `out` (or clears them) and returns 0 (none), 1 (a
   listed moby) or 2 (the starting candidate dropped). */
/* Finds the closest decoy or sheep target near a point so the hero can lock on to it, and fills in the target data. Returns 0 for no target, 1 for a new target, 2 for dropping the current one. */
int SelectNearestListedMoby(char *center, char *out_data, int plane_list_index, int corner_box_index, int face_box_index, int edge_box_index, float minimum, float limit)
{
    char *selected = g_hero_state.selected;
    int result = 0;
    int i;

    if (g_hero_state.state == 0x18 || g_hero_state.mode == 0x6F) {
        selected = 0;
        result = 2;
    } else if (!func_L08_0032E920((char *)&g_hero_state + 0x80, plane_list_index, corner_box_index, face_box_index, edge_box_index)) {
        if (limit < vec_distance_xy(center + 0x10, (char *)&g_hero_state + 0x80)) {
            selected = 0;
            result = 2;
        }
    }
    for (i = 1; i <= g_active_moby_indices[0]; i++) {
        char *object = g_moby_array[0] + (g_active_moby_indices[i] << 8);
        if (object && (*(short *)(object + 0xAA) == MOBY_CLASS_DECOY || *(short *)(object + 0xAA) == 0x76C /* moby class 1900 */ ||
                       *(short *)(object + 0xAA) == MOBY_CLASS_DARK_SHEEP) &&
            *(unsigned char *)(object + 0x20) != 0xFE && *(unsigned char *)(object + 0x20) != 0xFD &&
            *(unsigned char *)(object + 0x20) == 3) {
            float distance = vec_distance_xy(center + 0x10, object + 0x10);
            int valid = 1;
            if (minimum <= distance)
                valid = 0;
            else if (!(distance < limit)) {
                if (!func_L08_0032E920(object + 0x10, plane_list_index, corner_box_index, face_box_index, edge_box_index))
                    valid = 0;
            }
            if (valid) {
                selected = object;
                result = 1;
                minimum = distance;
            }
        }
    }
    if (selected) {
        *(char **)(out_data + 0x40) = selected;
        qcopy(out_data, selected + 0x10);
        qcopy(out_data + 0x10, selected + 0xF0);
        if (selected == g_hero_state.selected) {
            qcopy(out_data + 0x20, (char *)&g_hero_state + 0xD0);
            qcopy(out_data + 0x30, (char *)&g_hero_state + 0xE0);
        } else {
            qcopy(out_data + 0x30, out_data);
            *(float *)(out_data + 0x38) += 0.6f;
            qcopy(out_data + 0x20, out_data + 0x30);
        }
    } else {
        *(int *)(out_data + 0x40) = 0;
        qzero(out_data);
        qzero(out_data + 0x10);
        qzero(out_data + 0x30);
        qzero(out_data + 0x20);
    }
    *(int *)(out_data + 0x44) = result;
    return result;
}
