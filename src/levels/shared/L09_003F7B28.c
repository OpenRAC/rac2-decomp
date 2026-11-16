#include "names.h"
/* func_L09_003F7B28 (292 bytes; 09_dobbo, 12_todano, 20_yeedil). The direction word that
 * retail builds in $t0 (-1, or 1 when the frame's index is below its end) is the fifth integer
 * argument of func_L09_0033E8B0, as in func_L09_0033E8B0_1's callers. The frame's index and end
 * are re-read, not cached, and the -1 the result is compared with is a literal. */
#include "include_asm.h"
#include "names.h"

typedef unsigned int u32;

extern u32 g_path_l09_table[];

extern int func_L09_0033E8B0_2(char *object, int index, void *out, int a, int b, float f);

extern int path_get_entry_id(int index);

extern float mat_fast_helper_a(float x, float y);

extern float math_approach_target_with_direction_mode(void *, void *, int, float, float, float, float);

/* Steps the run's frame to the next entry of the level's table and hands the
   distance from the object to that entry's point to the stage. */
/* Walks the enemy along its path to the next point and turns it to face along the way. */
int enemy_walk_to_next_path_point(char *object, int index)
{
    char *frame = *(char **)(object + 0x68);
    int ret = 1;
    int dir = -1;
    int step;
    int next;
    short idx;
    float dist;

    if (*(short *)(frame + 0x1C8) < *(short *)(frame + 0x1CA))
        dir = ret;
    next = func_L09_0033E8B0_2(object, index, object + 0x10, *(short *)(frame + 0x1C8), dir,
                              *(float *)(frame + 0x128));
    idx = (short)next;
    *(short *)(frame + 0x1C8) = next;
    if (idx != -1) {
        if (idx != *(short *)(frame + 0x1CA))
            ret = 0;
    }
    step = idx + 1;
    if (path_get_entry_id(index) < step) {
        float *rec = (float *)(g_path_l09_table[index] + step * 16);

        dist = mat_fast_helper_a(rec[4] - *(float *)(object + 0x10),
                             rec[5] - *(float *)(object + 0x14));
    } else {
        dist = mat_fast_helper_a(*(float *)(frame + 0x1F0) - *(float *)(object + 0x10),
                             *(float *)(frame + 0x1F4) - *(float *)(object + 0x14));
    }
    math_approach_target_with_direction_mode(object + 0xF8, frame + 0x1B4, 0, dist, *(float *)(frame + 0x114), *(float *)(frame + 0x118),
                  *(float *)(frame + 0x11C));
    return ret;
}
