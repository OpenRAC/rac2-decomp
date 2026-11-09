#include "include_asm.h"

extern int func_00336A40(void *);
extern unsigned long func_0027C878(int);
extern void func_PAL_0027FB48(float x, float y, unsigned long color, char *text, int characterLimit,
        float scale, unsigned long texture, char *metrics);
extern float func_PAL_00280358(char *text, int length, int maxWidth, float minScale);

/* func_PAL_00338770, the PAL copy of func_00336A78: the same C, with the text first shrunk to
   fit its maximum width by func_PAL_00280358 and moved by what the scale gave up. */
void func_PAL_00338770(char *o)
{
    float yOffset = 0.0f;
    float x;
    float y;
    int width;
    unsigned long texture;
    int color;
    char *position;
    char *scale;

    if (*(int *)(o + 0x48) != 0) {
        **(float **)(o + 4) = func_PAL_00280358(*(char **)(o + 0x40), -1, *(int *)(o + 0x4C), *(float *)(o + 0x50));
        yOffset = 3.0f - (**(float **)(o + 4) - *(float *)(o + 0x50)) * 10.0f;
    }
    if (*(float *)(*(char **)(o + 16)) == 0.0f) {
        return;
    }
    if (*(int *)(o + 64) == 0) {
        return;
    }
    width = func_00336A40(o);
    x = *(float *)(*(char **)(o));
    switch (*(int *)(o + 68)) {
    case 0:
        break;
    case 1:
        x = x - (float)(width >> 1);
        break;
    case 2:
        x = x - (float)width;
        break;
    }
    position = *(char **)(o);
    scale = *(char **)(o + 4);
    color = *(int *)(*(char **)(o + 12));
    y = *(float *)(position + 4) + yOffset;
    texture = func_0027C878(*(int *)(o + 56));
    func_PAL_0027FB48(x, y, color, *(char **)(o + 64), width, *(float *)(scale), texture,
            *(char **)(o + 52));
}
