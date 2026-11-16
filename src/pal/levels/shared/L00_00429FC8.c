#include "include_asm.h"

#include "common.h"
extern char *g_follow_camera_object;
extern char *g_follow_camera_object;

/* Stores one float and two scaled by an arcsecond-sized constant into the block at +32. */
void cam_set_turn_limits_pal(float value, float low, float high)
{
    char *camera = g_follow_camera_object;

    if (*(short *)(camera + 134) == 0) {
        char *vars = *(char **)(camera + 112);
        char *limits = vars + 32;

        *(float *)(limits + 44) = value;
        *(float *)(limits + 52) = low * 6.981318e-06f;
        *(float *)(limits + 56) = high * 6.981318e-06f;
    }
}

