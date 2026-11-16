#include "include_asm.h"

#include "common.h"
extern void path_sample_position(char *, int, float *, float *, int, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_random_float_range(float, float);
extern float g_bob_l06_amplitude __attribute__((sda));

/* Advance a moving object's path and keep its spacing from the next object. */
void update_path_moby_spacing_pal(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    char *next;
    float phase, path_position;
    int length;
    path_sample_position(*(char **)(state + 0x30), *(int *)(state + 0x40),
                 (float *)(moby + 0x10), (float *)(moby + 0xF0), 0, *(float *)(state + 0x10));
    phase = FastAddRotations(*(float *)(state + 0x4C), *(float *)(state + 0x50));
    *(float *)(state + 0x4C) = phase;
    *(float *)(moby + 0x18) += g_bob_l06_amplitude * math_fast_sin_or_cos_b(phase);
    length = **(int **)(state + 0x30);
    path_position = *(float *)(state + 0x10) + *(float *)(state + 0x14);
    *(float *)(state + 0x10) = path_position;
    if ((float)length <= path_position)
        *(float *)(state + 0x10) = path_position - (float)length;
    if (*(float *)(state + 0x14) > *(float *)(state + 0x38))
        *(float *)(state + 0x14) -= *(float *)(state + 0x18);
    else
        *(float *)(state + 0x14) += *(float *)(state + 0x18);
    next = *(char **)(state + 0x34);
    if (next && next != moby) {
        char *other = *(char **)(next + 0x68);
        float next_speed;
        float gap = *(float *)(other + 0x10) - *(float *)(state + 0x10);
        float own_speed;
        if (gap < 0.0f)
            gap += (float)**(int **)(state + 0x30);
        next_speed = *(float *)(other + 0x38);
        own_speed = *(float *)(state + 0x38);
        if (next_speed < own_speed) {
            float difference = own_speed - next_speed;
            float deceleration = *(float *)(state + 0x18);
            float next_margin = *(float *)(other + 0x1C);
            float own_margin = *(float *)(state + 0x1C);
            deceleration += deceleration;
            /* The shared source line preserves the measured debug-label padding. */
            difference *= difference; if (gap < difference / deceleration + next_margin + own_margin) {
                *(float *)(other + 0x38) = own_speed;
                *(float *)(state + 0x38) = next_speed;
            }
        }
        if (*(unsigned char *)(*(char **)(state + 0x34) + 0x20) == 2 &&
            gap < *(float *)(state + 0x1C) * 3.0f) {
            *(float *)(state + 0x5C) = *(float *)(state + 0x38);
            *(int *)(state + 0x38) = 0;
        }
        if (*(unsigned char *)(*(char **)(state + 0x34) + 0x20) == 3) {
            *(float *)(state + 0x38) = *(float *)(state + 0x5C);
            *(char **)(state + 0x34) = *(char **)(other + 0x34);
        }
        if (*(float *)(state + 0x38) != 0.0f)
            return;
        if (*(float *)(other + 0x38) == 0.0f)
            return;
        *(float *)(state + 0x38) = *(float *)(other + 0x38);
    } else {
        float random = math_random_float_range(*(float *)(state + 8), *(float *)(state + 0xC));
        *(float *)(state + 0x38) = (*(float *)(state + 0x60) * (0.020000001f)) * random;
    }
}
