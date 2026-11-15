#include "include_asm.h"
#include "common.h"

/* func_L19_002B0148 is defined in L19_002B0148-flags.c. */



typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; } Hero;
extern u8 D_00189E20[];
extern float func_00282E80(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);

/* Sets the hero's target speeds for walking and turning each frame and eases the speed values toward them. */
void func_L19_002B6278(void) {
    int phase;
    int movement;
    float distance;

    if (((Hero *)gHeroState)->b[0x22B4] == 0 || ((Hero *)gHeroState)->b[0x22B4] == 4) {
        ((Hero *)gHeroState)->f[0x258 / 4] = 0.8f;
        ((Hero *)gHeroState)->f[0x25C / 4] = 0.7f;
        ((Hero *)gHeroState)->f[0x260 / 4] = 0.45f;
    }

    phase = ((Hero *)gHeroState)->i[0x229C / 4];
    if (phase == 4) {
        if (((Hero *)gHeroState)->h[0x4AC / 2] < ((Hero *)gHeroState)->i[0x1B8 / 4]) {
            if (((Hero *)gHeroState)->b[0x49E] == 0) {
                ((Hero *)gHeroState)->f[0x25C / 4] = ((Hero *)gHeroState)->f[0x4B8 / 4];
            }
        }
    } else {
        movement = ((Hero *)gHeroState)->i[0x2294 / 4];
        if (movement == 6) {
            ((Hero *)gHeroState)->f[0x25C / 4] = 0.5f;
        } else if (movement == 4) {
            ((Hero *)gHeroState)->f[0x258 / 4] = 0.35000002384185791f;
        } else if ((u32)(phase - 0x11) < 2) {
            ((Hero *)gHeroState)->i[0x258 / 4] = 0;
            ((Hero *)gHeroState)->i[0x25C / 4] = 0;
        } else if (movement == 0x7C) {
            ((Hero *)gHeroState)->f[0x260 / 4] = 0.8f;
        }
    }

    if (((Hero *)gHeroState)->b[0x287] == 0)
        goto slow;
    if (((Hero *)gHeroState)->i[0x22A4 / 4] == 0x12)
        goto slow;
    if (((Hero *)gHeroState)->i[0x22B0 / 4] == 0x12)
        goto slow;
    if (((Hero *)gHeroState)->b[0x22B4] == 0) {
        if (((Hero *)gHeroState)->f[0x254 / 4] < 0.53f)
            goto slow;
    }
    if (((Hero *)gHeroState)->i[0x229C / 4] == 0x11)
        goto slow;
    if (((Hero *)gHeroState)->b[0x1494] != 0)
        goto slow;

    distance = vec_distance_xy(gHeroState + 0x240, gHeroState + 0x80);
    if (distance > ((Hero *)gHeroState)->f[0x264 / 4] * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *p = gHeroState + 0x250;
        float step = 0.02f;
        ApproachValue((float *)p, ((Hero *)gHeroState)->f[0x258 / 4], step);
        ApproachValue((float *)(p + 4), ((Hero *)gHeroState)->f[0x25C / 4], step);
        SpringFloatToGoal(
            (float *)(p + 0x14),
            (float *)(p + 0x18),
            ((Hero *)gHeroState)->f[0x260 / 4],
            step,
            0.3f,
            0.06666667f);
    }
}


/* func_L19_002B7820 is defined in L19_002A88C8-ground-g8.c. */
