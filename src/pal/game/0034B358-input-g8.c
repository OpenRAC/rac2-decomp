#include "include_asm.h"

extern char D_00138180[];
extern float D_001AE5F4 __attribute__((sda));
extern float func_00282C10(float);
extern float func_00283248(float, float);
#define RANGES (*(float (**)[2])(object + 0x144))

int func_PAL_0034B358(char *object)
{
    float x, y, magnitude, angle;
    char *pad;
    int oldSelection, i;
    unsigned int buttons;

    if (--*(int *)(object + 0x154) < 0)
        *(int *)(object + 0x154) = 0;
    if (*(int *)(object + 0x154) == 0) {
        pad = D_00138180;
        x = *(float *)(pad + 0x148);
        y = *(float *)(pad + 0x14C);
        magnitude = func_00282C10(x*x + y*y);
        if (magnitude != 0.0f) {
            x /= magnitude;
            y /= magnitude;
        }
        angle = func_00283248(x, y);
        i = 0;
        if (*(int *)(object + 0x150) == 0)
            *(int *)(object + 0x14C) = -1;
        oldSelection = *(int *)(object + 0x14C);
        if (magnitude > D_001AE5F4) {
            while (RANGES[i][0] != 0.0f || RANGES[i][1] != 0.0f) {
                if ((RANGES[i][0] < 0.0f) != (RANGES[i][1] >= 0.0f)) {
                    if (RANGES[i][0] <= angle && angle < RANGES[i][1]) {
                        *(int *)(object + 0x14C) = i;
                        *(int *)(object + 0x150) = 1;
                        break;
                    }
                } else if (RANGES[i][1] < 0.0f) {
                    if ((RANGES[i][0] <= angle && angle <= 3.15916f) ||
                        (-3.15916f <= angle && angle < RANGES[i][1])) {
                        *(int *)(object + 0x14C) = i;
                        *(int *)(object + 0x150) = 1;
                        break;
                    }
                } else {
                    if ((RANGES[i][0] <= angle && angle < 0.0f) ||
                        (0.0f <= angle && angle < RANGES[i][1])) {
                        *(int *)(object + 0x14C) = i;
                        *(int *)(object + 0x150) = 1;
                        break;
                    }
                }
                ++i;
            }
        } else {
            buttons = *(unsigned int *)(pad + 0x1C0);
            if (buttons & 0x1000) {
                *(int *)(object + 0x14C) = 3;
                *(int *)(object + 0x150) = 1;
            } else if (buttons & 0x4000) {
                *(int *)(object + 0x14C) = 1;
                *(int *)(object + 0x150) = 1;
            } else if (buttons & 0x8000) {
                *(int *)(object + 0x14C) = 2;
                *(int *)(object + 0x150) = 1;
            } else if (buttons & 0x2000) {
                *(int *)(object + 0x14C) = 0;
                *(int *)(object + 0x150) = 1;
            }
        }
        if (oldSelection != *(int *)(object + 0x14C))
            *(int *)(object + 0x154) = 8;
    }
    return *(int *)(object + 0x14C);
}
