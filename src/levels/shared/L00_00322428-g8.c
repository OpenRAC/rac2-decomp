#include "common.h"

extern float D_001A790C;
extern float D_001A7910;
extern float D_001A7914;
extern float D_001A7918;
extern float D_001A791C;
extern float D_001A7920;
extern int D_001A7924;
extern float D_001A7928;
extern int D_001A7B90;
extern float D_001A7918_gp SDATA(D_001A7918);
extern float D_001A7928_gp SDATA(D_001A7928);

/* Sets the frame timing constants for either the normal or the alternate timing mode. */
void func_L00_00322428(int mode) {
    if (mode == 0) {
        float one = 1.0f;
        float frame = 1.0f/60.0f;
        float square = 1.0f/3600.0f;
        float cube = 1.0f/216000.0f;
        D_001A7914 = one;
        D_001A791C = square;
        D_001A7920 = cube;
        D_001A7924 = 5;
        D_001A7928 = frame;
        gIsPalVideo = 0;
        D_001A790C = one;
        D_001A7910 = one;
        D_001A7918_gp = frame;
    } else {
        float inverse, frame, frame2, frame3, square, baseline, rate;
        int enabled;
        int ticks;
        rate = 1.2f;
        enabled = 1;
        square = 1.44f;
        ticks = 6;
        inverse = 0.83333337306976318359375f;
        frame = 0.02000000141561031341552734375f;
        frame2 = 0.00040000001899898052215576171875f;
        frame3 = 0.000008f;
        baseline = 0.02f;
        gIsPalVideo = enabled;
        D_001A790C = rate;
        D_001A7910 = square;
        D_001A7914 = inverse;
        D_001A7918 = frame;
        D_001A791C = frame2;
        D_001A7920 = frame3;
        D_001A7924 = ticks;
        D_001A7928_gp = baseline;
    }
}
