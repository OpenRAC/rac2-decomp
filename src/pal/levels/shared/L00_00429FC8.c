#include "include_asm.h"

#include "common.h"
extern char *g_follow_camera_object;
extern char *g_follow_camera_object;

/* Stores one float and two scaled by an arcsecond-sized constant into the block at +32. */
void cam_set_turn_limits_pal(float a, float b, float c)
{
    char *p = g_follow_camera_object;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 32;

        *(float *)(r + 44) = a;
        *(float *)(r + 52) = b * 6.981318e-06f;
        *(float *)(r + 56) = c * 6.981318e-06f;
    }
}

