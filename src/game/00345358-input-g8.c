#include "names.h"
/* Stick or d-pad selection among direction ranges: the stick's angle is looked up in the
   [start, end) table at +0x144 (a range may wrap through +/-pi or through zero), the d-pad picks
   entries 3, 1, 2 or 0. +0x14C is the selection, +0x150 keeps it while the stick is released and
   +0x154 is a 10-frame repeat delay. Reading the table field at each use gives retail's copy of
   the first table pointer. Its own unit: the nops before the divisions need -g. */
extern char D_00138180[];
extern float D_001AE5F4 __attribute__((sda));
extern float func_00282C10(float);
extern float func_00283248(float, float);

#define RANGES (*(float (**)[2])(object + 0x144))

int func_00349190(char *object)
{
    float x, y, magnitude, angle;
    char *pad;
    int oldSelection, i;
    unsigned int buttons;

    if (--*(int *)(object + 0x154) < 0)
        *(int *)(object + 0x154) = 0;
    if (*(int *)(object + 0x154) == 0) {
        pad = gPadState;
        x = *(float *)(pad + 0x148);
        y = *(float *)(pad + 0x14C);
        magnitude = square_root(x*x + y*y);
        if (magnitude != 0.0f) {
            x /= magnitude;
            y /= magnitude;
        }
        angle = FastMatrixHelperA(x, y);
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
            *(int *)(object + 0x154) = 10;
    }
    return *(int *)(object + 0x14C);
}
