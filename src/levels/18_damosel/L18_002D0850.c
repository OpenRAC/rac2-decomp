#include "common.h"

typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; } Hero;
extern u8 D_00189E20[];
extern float func_00282E80(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern float func_002AA3A8(float *, float *, float, float, float, float);

void func_L18_002D0850(void) {
    int a3;
    int v1;
    float r;

    if (((Hero *)D_00189E20)->b[0x22B4] == 0 || ((Hero *)D_00189E20)->b[0x22B4] == 4) {
        ((Hero *)D_00189E20)->f[0x258 / 4] = 0.8f;
        ((Hero *)D_00189E20)->f[0x25C / 4] = 0.7f;
        ((Hero *)D_00189E20)->f[0x260 / 4] = 0.45f;
    }

    a3 = ((Hero *)D_00189E20)->i[0x229C / 4];
    if (a3 == 4) {
        if (((Hero *)D_00189E20)->h[0x4AC / 2] < ((Hero *)D_00189E20)->i[0x1B8 / 4]) {
            if (((Hero *)D_00189E20)->b[0x49E] == 0) {
                ((Hero *)D_00189E20)->f[0x25C / 4] = ((Hero *)D_00189E20)->f[0x4B8 / 4];
            }
        }
    } else {
        v1 = ((Hero *)D_00189E20)->i[0x2294 / 4];
        if (v1 == 6) {
            ((Hero *)D_00189E20)->f[0x25C / 4] = 0.5f;
        } else if (v1 == 4) {
            ((Hero *)D_00189E20)->f[0x258 / 4] = 0.35000002384185791f;
        } else if ((u32)(a3 - 0x11) < 2) {
            ((Hero *)D_00189E20)->i[0x258 / 4] = 0;
            ((Hero *)D_00189E20)->i[0x25C / 4] = 0;
        } else if (((Hero *)D_00189E20)->b[0x1492] != 0 && ((Hero *)D_00189E20)->i[0x340 / 4] != 0) {
            ((Hero *)D_00189E20)->f[0x258 / 4] = 0.8f;
            ((Hero *)D_00189E20)->f[0x25C / 4] = 0.9f;
        } else if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x7C) {
            ((Hero *)D_00189E20)->f[0x260 / 4] = 0.8f;
        }
    }

    if (((Hero *)D_00189E20)->b[0x287] == 0)
        goto slow;
    if (((Hero *)D_00189E20)->i[0x22A4 / 4] == 0x12)
        goto slow;
    if (((Hero *)D_00189E20)->i[0x22B0 / 4] == 0x12)
        goto slow;
    if (((Hero *)D_00189E20)->b[0x22B4] == 0) {
        if (((Hero *)D_00189E20)->f[0x254 / 4] < 0.53f)
            goto slow;
    }
    if (((Hero *)D_00189E20)->i[0x229C / 4] == 0x11)
        goto slow;
    if (((Hero *)D_00189E20)->b[0x1494] != 0)
        goto slow;

    r = vec_distance_xy(D_00189E20 + 0x240, D_00189E20 + 0x80);
    if (r > ((Hero *)D_00189E20)->f[0x264 / 4] * 0.5f)
        goto slow;
    return;

slow:
    {
        /* The channel block sits 0x250 into the runtime block; the block pointer
           is taken first and the runtime block is reached back from it. */
        u8 *p = D_00189E20 + 0x250;
        float step = 0.02f;
        ApproachValue((float *)p, ((Hero *)D_00189E20)->f[0x258 / 4], step);
        ApproachValue((float *)(p + 4), ((Hero *)D_00189E20)->f[0x25C / 4], step);
        func_002AA3A8(
            (float *)(p + 0x14),
            (float *)(p + 0x18),
            ((Hero *)D_00189E20)->f[0x260 / 4],
            step,
            0.3f,
            0.06666667f);
    }
}
