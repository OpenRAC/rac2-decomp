#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;

/* func_L09_002AFC90 is defined in L09_002AFC90-flags.c. */

extern u8 D_00189E20[];

extern float func_00282E80(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);

/* The level's runtime block: the three channel floats are set from the mode
   word, the two state words and the mode byte, then the aim check decides
   whether the channels are ramped towards their targets or the distance to
   the target is measured. */
/* Slowly moves the player's three blend values toward targets that depend on the current action. */
void func_L09_002B5CE8(void) {
    int a3;
    int v1;
    float r;

    if (gHeroState[0x22B4] == 0) {
        *(float *)(gHeroState + 0x258) = 0.8f;
        *(float *)(gHeroState + 0x25C) = 0.7f;
        *(float *)(gHeroState + 0x260) = 0.45f;
    }

    a3 = *(int *)(gHeroState + 0x229C);
    if (a3 == 4) {
        if (*(short *)(gHeroState + 0x4AC) < *(int *)(gHeroState + 0x1B8)) {
            if (gHeroState[0x49E] == 0) {
                *(float *)(gHeroState + 0x25C) = *(float *)(gHeroState + 0x4B8);
            }
        }
    } else {
        v1 = *(int *)(gHeroState + 0x2294);
        if (v1 == 6) {
            *(float *)(gHeroState + 0x25C) = 0.5f;
        } else if (v1 == 4) {
            *(float *)(gHeroState + 0x258) = 0.35000002384185791f;
        } else if ((u32)(a3 - 0x11) < 2) {
            *(int *)(gHeroState + 0x258) = 0;
            *(int *)(gHeroState + 0x25C) = 0;
        } else if (v1 == 0x7C) {
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

    r = vec_distance_xy(gHeroState + 0x240, gHeroState + 0x80);
    if (r > *(float *)(gHeroState + 0x264) * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *p = gHeroState + 0x250;
        u8 *s = p - 0x250;
        float step = 0.02f;
        ApproachValue((float *)p, *(float *)(s + 0x258), step);
        ApproachValue((float *)(p + 4), *(float *)(s + 0x25C), step);
        SpringFloatToGoal(
            (float *)(p + 0x14),
            (float *)(p + 0x18),
            *(float *)(s + 0x260),
            step,
            0.3f,
            0.06666667f);
    }
}

