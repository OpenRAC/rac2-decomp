#include "common.h"

extern u8 g_hero_state[];
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* Sets the target values for the hero's three blend channels from what the hero is doing, then eases the channels toward those targets. */
void hero_l01_update_blend_channels(void) {
    int previous_state;
    int hero_state;
    float dist;

    if (g_hero_state[0x22B4] == 0) {
        *(float *)(g_hero_state + 0x258) = 0.8f;
        *(float *)(g_hero_state + 0x25C) = 0.7f;
        *(float *)(g_hero_state + 0x260) = 0.45f;
    }

    previous_state = *(int *)(g_hero_state + 0x229C);
    if (previous_state == 4) {
        if (*(short *)(g_hero_state + 0x4AC) < *(int *)(g_hero_state + 0x1B8)) {
            if (g_hero_state[0x49E] == 0) {
                *(float *)(g_hero_state + 0x25C) = *(float *)(g_hero_state + 0x4B8);
            }
        }
    } else {
        hero_state = *(int *)(g_hero_state + 0x2294);
        if (hero_state == 6) {
            *(float *)(g_hero_state + 0x25C) = 0.5f;
        } else if (hero_state == 4) {
            *(float *)(g_hero_state + 0x258) = 0.35000002384185791f;
        } else if (hero_state == 0x7C) {
            *(float *)(g_hero_state + 0x260) = 0.8f;
        }
    }

    if (g_hero_state[0x287] == 0)
        goto slow;
    if (*(int *)(g_hero_state + 0x22A4) == 0x12)
        goto slow;
    if (*(int *)(g_hero_state + 0x22B0) == 0x12)
        goto slow;
    if (g_hero_state[0x22B4] == 0) {
        if (*(float *)(g_hero_state + 0x254) < 0.53f)
            goto slow;
    }
    if (*(int *)(g_hero_state + 0x229C) == 0x11)
        goto slow;
    if (g_hero_state[0x1494] != 0)
        goto slow;

    dist = vec_distance_xy(g_hero_state + 0x240, g_hero_state + 0x80);
    if (dist > *(float *)(g_hero_state + 0x264) * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *channels = g_hero_state + 0x250;
        u8 *hero_base = channels - 0x250;
        float step = 0.02f;
        ApproachValue((float *)channels, *(float *)(hero_base + 0x258), step);
        ApproachValue((float *)(channels + 4), *(float *)(hero_base + 0x25C), step);
        math_spring_float_to_goal(
            (float *)(channels + 0x14),
            (float *)(channels + 0x18),
            *(float *)(hero_base + 0x260),
            step,
            0.3f,
            0.06666667f);
    }
}
