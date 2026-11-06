#include "include_asm.h"

/* func_US2_0027B858, the v2.00 copy of func_0027B2F8: the same C without the fA0 and fA4 stores. */
extern float func_00283CE0(int);
extern void func_0027AB40(void);
extern void func_00279FF0(void);

/* Partial view of the shared screen/render state. */
typedef struct {
    char pad[0xA0];
    float fA0, fA4;
    char gap[8];
    float fB0;
    char gapB4[0x14C];
    float f200, f204, f208, f20C;
    char gap210[8];
    float f218, f21C;
    char gap220[8];
    float f228, f22C;
} ScreenState;
extern ScreenState D_001B9040;

typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern ScreenExtent D_001A7340 __attribute__((sda));
typedef struct { char pad[0x150]; short width, height; } ScreenDimensions;
extern ScreenDimensions D_001A6480;

void func_US2_0027B858(int width, int height, float scale, float a, float b, float c, float d)
{
    ScreenState *context = &D_001B9040;
    int halfW = width >> 1;
    int halfH = height >> 1;
    float halfHeight;
    D_001A7340.width = width;
    D_001A7340.height = height;
    D_001A7340.half_width = halfW;
    D_001A7340.half_height = halfH;
    D_001A7340.left = (2048 - halfW) << 4;
    D_001A7340.top = (2048 - halfH) << 4;
    D_001A7340.right = (halfW + 2048) << 4;
    D_001A7340.bottom = (halfH + 2048) << 4;
    context->fB0 = scale;
    context->f200 = func_00283CE0(width) * 0.5f;
    halfHeight = func_00283CE0(height) * 0.5f;
    context->f204 = halfHeight;
    context->f208 = context->f200 * 4.0f;
    context->f20C = halfHeight * 4.0f;
    context->f218 = a;
    context->f21C = b;
    context->f228 = c;
    context->f22C = d;
    func_0027AB40();
}

/* func_US2_0027B988, the v2.00 copy of func_0027A9F0: the fA0 and fA4 stores go, and a call replaces the last four. */
void func_US2_0027B988(void)
{
    ScreenDimensions *dimensions = &D_001A6480;
    ScreenState *view = &D_001B9040;
    short width = dimensions->width;
    short height = dimensions->height;
    int half_width = width >> 1;
    int half_height = height >> 1;
    float half_height_f;

    D_001A7340.width = width;
    D_001A7340.height = height;
    D_001A7340.half_width = half_width;
    D_001A7340.half_height = half_height;
    D_001A7340.left = (2048 - half_width) << 4;
    D_001A7340.top = (2048 - half_height) << 4;
    D_001A7340.right = (half_width + 2048) << 4;
    D_001A7340.bottom = (half_height + 2048) << 4;

    view->fB0 = 0.62f;
    view->f200 = func_00283CE0(width) * 0.5f;
    half_height_f = func_00283CE0(dimensions->height) * 0.5f;
    view->f204 = half_height_f;
    view->f208 = view->f200 * 4.0f;
    view->f20C = half_height_f * 4.0f;
    func_00279FF0();
}
