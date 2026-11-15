#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; } Hero;
extern u8 g_hero_state[];
extern float vec_distance_xy(void *, void *);
extern float ApproachValue(float *, float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* Sets the hero's movement speed targets for the current state and eases the current speeds toward them. */
void hero_l18_update_speed_targets(void) {
    int mode;
    int anim_state;
    float dist;

    if (((Hero *)g_hero_state)->b[0x22B4] == 0 || ((Hero *)g_hero_state)->b[0x22B4] == 4) {
        ((Hero *)g_hero_state)->f[0x258 / 4] = 0.8f;
        ((Hero *)g_hero_state)->f[0x25C / 4] = 0.7f;
        ((Hero *)g_hero_state)->f[0x260 / 4] = 0.45f;
    }

    mode = ((Hero *)g_hero_state)->i[0x229C / 4];
    if (mode == 4) {
        if (((Hero *)g_hero_state)->h[0x4AC / 2] < ((Hero *)g_hero_state)->i[0x1B8 / 4]) {
            if (((Hero *)g_hero_state)->b[0x49E] == 0) {
                ((Hero *)g_hero_state)->f[0x25C / 4] = ((Hero *)g_hero_state)->f[0x4B8 / 4];
            }
        }
    } else {
        anim_state = ((Hero *)g_hero_state)->i[0x2294 / 4];
        if (anim_state == 6) {
            ((Hero *)g_hero_state)->f[0x25C / 4] = 0.5f;
        } else if (anim_state == 4) {
            ((Hero *)g_hero_state)->f[0x258 / 4] = 0.35000002384185791f;
        } else if ((u32)(mode - 0x11) < 2) {
            ((Hero *)g_hero_state)->i[0x258 / 4] = 0;
            ((Hero *)g_hero_state)->i[0x25C / 4] = 0;
        } else if (((Hero *)g_hero_state)->b[0x1492] != 0 && ((Hero *)g_hero_state)->i[0x340 / 4] != 0) {
            ((Hero *)g_hero_state)->f[0x258 / 4] = 0.8f;
            ((Hero *)g_hero_state)->f[0x25C / 4] = 0.9f;
        } else if (((Hero *)g_hero_state)->i[0x2294 / 4] == 0x7C) {
            ((Hero *)g_hero_state)->f[0x260 / 4] = 0.8f;
        }
    }

    if (((Hero *)g_hero_state)->b[0x287] == 0)
        goto slow;
    if (((Hero *)g_hero_state)->i[0x22A4 / 4] == 0x12)
        goto slow;
    if (((Hero *)g_hero_state)->i[0x22B0 / 4] == 0x12)
        goto slow;
    if (((Hero *)g_hero_state)->b[0x22B4] == 0) {
        if (((Hero *)g_hero_state)->f[0x254 / 4] < 0.53f)
            goto slow;
    }
    if (((Hero *)g_hero_state)->i[0x229C / 4] == 0x11)
        goto slow;
    if (((Hero *)g_hero_state)->b[0x1494] != 0)
        goto slow;

    dist = vec_distance_xy(g_hero_state + 0x240, g_hero_state + 0x80);
    if (dist > ((Hero *)g_hero_state)->f[0x264 / 4] * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *channels = g_hero_state + 0x250;
        float step = 0.02f;
        ApproachValue((float *)channels, ((Hero *)g_hero_state)->f[0x258 / 4], step);
        ApproachValue((float *)(channels + 4), ((Hero *)g_hero_state)->f[0x25C / 4], step);
        math_spring_float_to_goal(
            (float *)(channels + 0x14),
            (float *)(channels + 0x18),
            ((Hero *)g_hero_state)->f[0x260 / 4],
            step,
            0.3f,
            0.06666667f);
    }
}
