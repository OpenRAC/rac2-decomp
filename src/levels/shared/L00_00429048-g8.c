#include "common.h"

extern char *g_follow_camera_object[];
extern char *g_camera_def_table __attribute__((sda));
extern float g_hero_scalar_transition_value MACRO_ADDR;

/* Tells whether the camera trigger at this index is ready. Returns 1 when it is, otherwise it checks a camera state value. */
int cam_is_trigger_ready(int index)
{
    char *cam_state;

    if (*(short *)(g_follow_camera_object[0] + 0x86) != 0x13)
        return 1;
    cam_state = (char *)(*(int *)(*(int *)(*(char **)(g_camera_def_table + index * 32 + 0x1C) + 4) + 0x70) + 0x40);
    if (*(short *)(cam_state + 0x14) == 1 && g_hero_scalar_transition_value != 0.0f)
        return 1;
    return *(short *)(cam_state + 0x14) == 3;
}
