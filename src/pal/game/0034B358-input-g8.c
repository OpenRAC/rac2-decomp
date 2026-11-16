#include "include_asm.h"
#include "names.h"

extern char g_pad_state[];
extern float g_list_menu_input_threshold __attribute__((sda));
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
#define RANGES (*(float (**)[2])(object + 0x144))

/* Picks the selected direction from the stick angle (or the d-pad when the stick is idle), with a short delay between changes, and returns it. (PAL) */
int UpdateDirectionSelection_pal(char *object)
{
    float x, y, magnitude, angle;
    char *pad;
    int old_selection, i;
    unsigned int buttons;

    if (--*(int *)(object + 0x154) < 0)
        *(int *)(object + 0x154) = 0;
    if (*(int *)(object + 0x154) == 0) {
        pad = g_pad_state;
        x = *(float *)(pad + 0x148);
        y = *(float *)(pad + 0x14C);
        magnitude = square_root(x*x + y*y);
        if (magnitude != 0.0f) {
            x /= magnitude;
            y /= magnitude;
        }
        angle = mat_fast_helper_a(x, y);
        i = 0;
        if (*(int *)(object + 0x150) == 0)
            *(int *)(object + 0x14C) = -1;
        old_selection = *(int *)(object + 0x14C);
        if (magnitude > g_list_menu_input_threshold) {
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
        if (old_selection != *(int *)(object + 0x14C))
            *(int *)(object + 0x154) = 8;
    }
    return *(int *)(object + 0x14C);
}
