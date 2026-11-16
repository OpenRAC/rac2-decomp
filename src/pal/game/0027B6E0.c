#include "include_asm.h"
#include "common.h"

/* func_PAL_0027B6E0, the PAL copy of func_0027B2F8: the same C, without the stores of 32.0f to fA0
   and 1048576.0f to fA4. */

extern float IntToFloat(int);
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
    int color[3];
} ScreenState;
extern ScreenState g_view_params;
extern void UpdateViewContext(void);

typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern ScreenExtent g_screen_width __attribute__((sda));

typedef struct { char pad[0x150]; short width, height; } ScreenDimensions;
extern ScreenDimensions g_screen_adjust_offsets;
extern void gfx_apply_display_config(void);

void gfx_configure_projection_pal(int width, int height, float proj_scale, float param_a, float param_b, float param_c, float param_d)
{
    ScreenState *view = &g_view_params;
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
    view->fB0 = proj_scale;
    view->f200 = IntToFloat(width) * 0.5f;
    half_height_f = IntToFloat(height) * 0.5f;
    view->f204 = half_height_f;
    view->f208 = view->f200 * 4.0f;
    view->f20C = half_height_f * 4.0f;
    view->f218 = param_a;
    view->f21C = param_b;
    view->f228 = param_c;
    view->f22C = param_d;
    UpdateViewContext();
}

/* func_PAL_0027B810, the PAL copy of func_0027A9F0: the same C, without the stores to fA0, fA4,
   f218, f21C, f228 and f22C, and with a call of func_00279FF0 at the end. */
void gfx_init_view_context_pal(void)
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
