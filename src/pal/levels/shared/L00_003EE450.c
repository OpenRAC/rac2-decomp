#include "include_asm.h"
#include "names.h"

extern int g_game_l00_mode __attribute__((sda));
extern void gfx_set_clamped_view_distance(float value);
extern float math_fabs(float value);

/* Slides an object back and forth along one axis and shrinks it near both ends (PAL: 50 Hz speed). */
void sweeping_scale_update_pal(char *moby)
{
    float pos;
    float distance;
    float near_dist;
    float fade_in;
    float scale;
    int *model;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x32) = 0xAF0;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned char *)(moby + 0x20) = 1;
        gfx_set_clamped_view_distance(3000.0f);
    }
    if (*(unsigned char *)(moby + 0x20) != 1)
        return;
    if (g_game_l00_mode == 2)
        return;

    pos = *(float *)(moby + 0x14);
    pos = pos - 2.0000002f;
    *(float *)(moby + 0x14) = pos;
    distance = math_fabs(pos);

    near_dist = 3000.0f - distance;
    fade_in = 750.0f - near_dist;
    scale = 1.0f - fade_in * (1.0f / 750.0f);
    if (scale > 3.0f)
        scale = 3.0f;
    if (scale < 0.0f)
        scale = 0.0f;

    model = *(int **)(moby + 0x24);
    *(float *)(moby + 0x2C) = *(float *)((char *)model + 0x24) * scale;
    if (*(float *)(moby + 0x14) <= -3000.0f)
        *(float *)(moby + 0x14) = 3000.0f;
}


