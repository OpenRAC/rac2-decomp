#include "names.h"
/* Refresh the two tuning factors, or zero them on the two states that ask for it.
   The factors are two adjacent floats: the second is written as element 1 of the first's
   small-data array, which keeps its store out of the return's delay slot. */
extern char g_trail_slice_state[];
extern float g_scene_tuning_floats[] __attribute__((sda));

void todano_refresh_scene_tuning(void)
{
    char *p = g_trail_slice_state;

    if (*(int *)(p + 0x58) != 0) {
        g_scene_tuning_floats[0] = 0.1f;
        g_scene_tuning_floats[1] = 0.02f;
        return;
    }
    if ((unsigned int)(*(int *)(p + 0x30) - 3) < 2) {
        g_scene_tuning_floats[0] = 0.0f;
        g_scene_tuning_floats[1] = 0.0f;
    }
}
