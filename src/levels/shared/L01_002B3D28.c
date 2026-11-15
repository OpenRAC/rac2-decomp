#include "common.h"

extern u8 D_00189E20[];
extern float func_00282E80(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);

/* Sets the target values for the hero's three blend channels from what the hero is doing, then eases the channels toward those targets. */
void func_L01_002B3D28(void) {
    int previousState;
    int heroState;
    float dist;

    if (gHeroState[0x22B4] == 0) {
        *(float *)(gHeroState + 0x258) = 0.8f;
        *(float *)(gHeroState + 0x25C) = 0.7f;
        *(float *)(gHeroState + 0x260) = 0.45f;
    }

    previousState = *(int *)(gHeroState + 0x229C);
    if (previousState == 4) {
        if (*(short *)(gHeroState + 0x4AC) < *(int *)(gHeroState + 0x1B8)) {
            if (gHeroState[0x49E] == 0) {
                *(float *)(gHeroState + 0x25C) = *(float *)(gHeroState + 0x4B8);
            }
        }
    } else {
        heroState = *(int *)(gHeroState + 0x2294);
        if (heroState == 6) {
            *(float *)(gHeroState + 0x25C) = 0.5f;
        } else if (heroState == 4) {
            *(float *)(gHeroState + 0x258) = 0.35000002384185791f;
        } else if (heroState == 0x7C) {
            *(float *)(gHeroState + 0x260) = 0.8f;
        }
    }

    if (gHeroState[0x287] == 0)
        goto slow;
    if (*(int *)(gHeroState + 0x22A4) == 0x12)
        goto slow;
    if (*(int *)(gHeroState + 0x22B0) == 0x12)
        goto slow;
    if (gHeroState[0x22B4] == 0) {
        if (*(float *)(gHeroState + 0x254) < 0.53f)
            goto slow;
    }
    if (*(int *)(gHeroState + 0x229C) == 0x11)
        goto slow;
    if (gHeroState[0x1494] != 0)
        goto slow;

    dist = vec_distance_xy(gHeroState + 0x240, gHeroState + 0x80);
    if (dist > *(float *)(gHeroState + 0x264) * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *channels = gHeroState + 0x250;
        u8 *heroBase = channels - 0x250;
        float step = 0.02f;
        ApproachValue((float *)channels, *(float *)(heroBase + 0x258), step);
        ApproachValue((float *)(channels + 4), *(float *)(heroBase + 0x25C), step);
        SpringFloatToGoal(
            (float *)(channels + 0x14),
            (float *)(channels + 0x18),
            *(float *)(heroBase + 0x260),
            step,
            0.3f,
            0.06666667f);
    }
}
