#include "include_asm.h"
#include "names.h"

/* func_US2_0027B858, the v2.00 copy of func_0027B2F8: the same C without the fA0 and fA4 stores. */
extern float IntToFloat(int);
extern void UpdateViewContext(void);
extern void gfx_apply_display_config(void);

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
extern ScreenState g_view_params;

typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern ScreenExtent g_screen_width __attribute__((sda));
typedef struct { char pad[0x150]; short width, height; } ScreenDimensions;
extern ScreenDimensions g_screen_adjust_offsets;

void func_US2_0027B858(int width, int height, float scale, float a, float b, float c, float d)
{
    ScreenState *context = &g_view_params;
    int halfW = width >> 1;
    int halfH = height >> 1;
    float halfHeight;
    g_screen_width.width = width;
    g_screen_width.height = height;
    g_screen_width.half_width = halfW;
    g_screen_width.half_height = halfH;
    g_screen_width.left = (2048 - halfW) << 4;
    g_screen_width.top = (2048 - halfH) << 4;
    g_screen_width.right = (halfW + 2048) << 4;
    g_screen_width.bottom = (halfH + 2048) << 4;
    context->fB0 = scale;
    context->f200 = IntToFloat(width) * 0.5f;
    halfHeight = IntToFloat(height) * 0.5f;
    context->f204 = halfHeight;
    context->f208 = context->f200 * 4.0f;
    context->f20C = halfHeight * 4.0f;
    context->f218 = a;
    context->f21C = b;
    context->f228 = c;
    context->f22C = d;
    UpdateViewContext();
}

/* func_US2_0027B988, the v2.00 copy of func_0027A9F0: the fA0 and fA4 stores go, and a call replaces the last four. */
void func_US2_0027B988(void)
{
    ScreenDimensions *dimensions = &g_screen_adjust_offsets;
    ScreenState *view = &g_view_params;
    short width = dimensions->width;
    short height = dimensions->height;
    int half_width = width >> 1;
    int half_height = height >> 1;
    float half_height_f;

    g_screen_width.width = width;
    g_screen_width.height = height;
    g_screen_width.half_width = half_width;
    g_screen_width.half_height = half_height;
    g_screen_width.left = (2048 - half_width) << 4;
    g_screen_width.top = (2048 - half_height) << 4;
    g_screen_width.right = (half_width + 2048) << 4;
    g_screen_width.bottom = (half_height + 2048) << 4;

    view->fB0 = 0.62f;
    view->f200 = IntToFloat(width) * 0.5f;
    half_height_f = IntToFloat(dimensions->height) * 0.5f;
    view->f204 = half_height_f;
    view->f208 = view->f200 * 4.0f;
    view->f20C = half_height_f * 4.0f;
    gfx_apply_display_config();
}
