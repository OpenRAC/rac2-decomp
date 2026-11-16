#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;

extern u8 g_hero_state[];

extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* func_PAL_L09_002B5C80, the PAL copy of func_L09_002B5CE8: the same C, where the
   ramp step 0.02f becomes 0.024f and the last call's 0.02f, 0.3f and 0.06666667f become
   0.028800001f, 0.43200004f and 0.080000006f. */

/* The level's runtime block: the three channel floats are set from the mode
   word, the two state words and the mode byte, then the aim check decides
   whether the channels are ramped towards their targets or the distance to
   the target is measured. */
void hero_l09_update_blend_channels_pal(void) {
    int mode;
    int hero_state_id;
    float distance;

    if (g_hero_state[0x22B4] == 0) {
        *(float *)(g_hero_state + 0x258) = 0.8f;
        *(float *)(g_hero_state + 0x25C) = 0.7f;
        *(float *)(g_hero_state + 0x260) = 0.45f;
    }

    mode = *(int *)(g_hero_state + 0x229C);
    if (mode == 4) {
        if (*(short *)(g_hero_state + 0x4AC) < *(int *)(g_hero_state + 0x1B8)) {
            if (g_hero_state[0x49E] == 0) {
                *(float *)(g_hero_state + 0x25C) = *(float *)(g_hero_state + 0x4B8);
            }
        }
    } else {
        hero_state_id = *(int *)(g_hero_state + 0x2294);
        if (hero_state_id == 6) {
            *(float *)(g_hero_state + 0x25C) = 0.5f;
        } else if (hero_state_id == 4) {
            *(float *)(g_hero_state + 0x258) = 0.35000002384185791f;
        } else if ((u32)(mode - 0x11) < 2) {
            *(int *)(g_hero_state + 0x258) = 0;
            *(int *)(g_hero_state + 0x25C) = 0;
        } else if (hero_state_id == 0x7C) {
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

    distance = vec_distance_xy(g_hero_state + 0x240, g_hero_state + 0x80);
    if (distance > *(float *)(g_hero_state + 0x264) * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *channels = g_hero_state + 0x250;
        u8 *runtime = channels - 0x250;
        float step = 0.024f;
        ApproachValue((float *)channels, *(float *)(runtime + 0x258), step);
        ApproachValue((float *)(channels + 4), *(float *)(runtime + 0x25C), step);
        math_spring_float_to_goal(
            (float *)(channels + 0x14),
            (float *)(channels + 0x18),
            *(float *)(runtime + 0x260),
            0.028800001f,
            0.43200004f,
            0.080000006f);
    }
}

