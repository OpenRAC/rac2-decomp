#include "names.h"
/* Turns a hue angle into a fully bright packed colour with the given alpha. */
unsigned int gfx_hue_to_packed_color(float angle, int alpha)
{
    float sector = angle * 0.1591549367f * 6.0f;
    int index = (int)sector;
    unsigned int rising, falling, color;

    sector -= index;
    rising = (int)(sector * 255.0f);
    falling = (int)((1.0f - sector) * 255.0f);
    switch (index) {
    case 0:
        color = (rising << 8) | 255;
        break;
    case 1:
        color = falling | 0xff00;
        break;
    case 2:
        color = (rising << 16) | 0xff00;
        break;
    case 3:
        color = (falling << 8) | 0xff0000;
        break;
    case 4:
        color = rising | 0xff0000;
        break;
    case 5:
        color = (falling << 16) | 255;
        break;
    default:
        color = 0;
        break;
    }
    return ((unsigned int)alpha << 24) | color;
}
