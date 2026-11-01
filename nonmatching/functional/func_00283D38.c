/* functional: high. Plain floats in place of VU0 macro code and MMI byte packing. */
#include "common.h"

/* ColorLerpPacked: each byte of a towards b by t, truncated. */
int func_00283D38(int a, int b, float t)
{
    float keep = 1.0f - t;
    unsigned int out = 0;
    int i;

    for (i = 0; i < 4; i++) {
        float from = (float)((a >> (i * 8)) & 0xFF);
        float to = (float)((b >> (i * 8)) & 0xFF);
        float mix = from * keep + to * t;
        out |= ((unsigned int)(int)mix & 0xFF) << (i * 8);
    }
    return (int)out;
}
