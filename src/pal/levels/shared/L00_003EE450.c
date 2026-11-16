#include "include_asm.h"
#include "names.h"

extern int g_game_l00_mode __attribute__((sda));
extern void gfx_set_clamped_view_distance(float value);
extern float math_fabs(float value);

void func_PAL_L00_003EE6E0(char *p)
{
    float v;
    float x;
    float a;
    float b;
    float c;
    int *q;

    if (*(unsigned char *)(p + 0x20) == 0) {
        *(unsigned short *)(p + 0x32) = 0xAF0;
        *(unsigned char *)(p + 0x30) = 0xFF;
        *(unsigned char *)(p + 0x20) = 1;
        gfx_set_clamped_view_distance(3000.0f);
    }
    if (*(unsigned char *)(p + 0x20) != 1)
        return;
    if (g_game_l00_mode == 2)
        return;

    v = *(float *)(p + 0x14);
    v = v - 2.0000002f;
    *(float *)(p + 0x14) = v;
    x = math_fabs(v);

    a = 3000.0f - x;
    b = 750.0f - a;
    c = 1.0f - b * (1.0f / 750.0f);
    if (c > 3.0f)
        c = 3.0f;
    if (c < 0.0f)
        c = 0.0f;

    q = *(int **)(p + 0x24);
    *(float *)(p + 0x2C) = *(float *)((char *)q + 0x24) * c;
    if (*(float *)(p + 0x14) <= -3000.0f)
        *(float *)(p + 0x14) = 3000.0f;
}


