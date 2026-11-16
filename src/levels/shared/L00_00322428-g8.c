#include "common.h"

extern float g_frame_rate_scale;
extern float g_frame_scale_square;
extern float g_frame_scale_inverse;
extern float g_frame_delta;
extern float g_frame_delta_square;
extern float g_frame_delta_cube;
extern int g_frame_tick_count;
extern float g_frame_delta_scale;
extern int g_is_pal_video;
extern float D_001A7918_gp SDATA(D_001A7918);
extern float D_001A7928_gp SDATA(D_001A7928);

/* Sets the frame timing constants for either the normal or the alternate timing mode. */
void SetFrameTimingMode(int mode) {
    if (mode == 0) {
        float one = 1.0f;
        float frame = 1.0f/60.0f;
        float square = 1.0f/3600.0f;
        float cube = 1.0f/216000.0f;
        g_frame_scale_inverse = one;
        g_frame_delta_square = square;
        g_frame_delta_cube = cube;
        g_frame_tick_count = 5;
        g_frame_delta_scale = frame;
        g_is_pal_video = 0;
        g_frame_rate_scale = one;
        g_frame_scale_square = one;
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
        g_is_pal_video = enabled;
        g_frame_rate_scale = rate;
        g_frame_scale_square = square;
        g_frame_scale_inverse = inverse;
        g_frame_delta = frame;
        g_frame_delta_square = frame2;
        g_frame_delta_cube = frame3;
        g_frame_tick_count = ticks;
        D_001A7928_gp = baseline;
    }
}
