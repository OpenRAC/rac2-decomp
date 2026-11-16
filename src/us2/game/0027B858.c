#include "include_asm.h"
#include "names.h"

/* func_US2_0027B858, the v2.00 copy of func_0027B2F8: the same C without the unk_A0 and unk_A4 stores. */
extern float IntToFloat(int);
extern void UpdateViewContext(void);
extern void gfx_apply_display_config(void);

/* Partial view of the shared screen/render state. */
typedef struct {
    char pad[0xA0];
    float unk_A0, unk_A4;
    char gap[8];
    float projection_scale;
    char gapB4[0x14C];
    float center_x, center_y, center_x4, center_y4;
    char gap210[8];
    float unk_218, unk_21C;
    char gap220[8];
    float unk_228, unk_22C;
} ScreenState;
extern ScreenState g_view_params;

typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern ScreenExtent g_screen_width __attribute__((sda));
typedef struct { char pad[0x150]; short width, height; } ScreenDimensions;
extern ScreenDimensions g_screen_adjust_offsets;

/* Sets up the screen size and view limits from the given values, then applies them (USA v2.00). */
void gfx_configure_projection_us2(int width, int height, float scale, float limit_a, float limit_b, float limit_c, float limit_d)
{
    ScreenState *context = &g_view_params;
    int half_w = width >> 1;
    int half_h = height >> 1;
    float half_height_f;
    g_screen_width.width = width;
    g_screen_width.height = height;
    g_screen_width.half_width = half_w;
    g_screen_width.half_height = half_h;
    g_screen_width.left = (2048 - half_w) << 4;
    g_screen_width.top = (2048 - half_h) << 4;
    g_screen_width.right = (half_w + 2048) << 4;
    g_screen_width.bottom = (half_h + 2048) << 4;
    context->projection_scale = scale;
    context->center_x = IntToFloat(width) * 0.5f;
    half_height_f = IntToFloat(height) * 0.5f;
    context->center_y = half_height_f;
    context->center_x4 = context->center_x * 4.0f;
    context->center_y4 = half_height_f * 4.0f;
    context->unk_218 = limit_a;
    context->unk_21C = limit_b;
    context->unk_228 = limit_c;
    context->unk_22C = limit_d;
    UpdateViewContext();
}

/* func_US2_0027B988, the v2.00 copy of func_0027A9F0: the unk_A0 and unk_A4 stores go, and a call replaces the last four. */
/* Sets the default screen size and view limits from the display adjust offsets, then applies the display config. */
void gfx_init_view_context_us2(void)
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

    view->projection_scale = 0.62f;
    view->center_x = IntToFloat(width) * 0.5f;
    half_height_f = IntToFloat(dimensions->height) * 0.5f;
    view->center_y = half_height_f;
    view->center_x4 = view->center_x * 4.0f;
    view->center_y4 = half_height_f * 4.0f;
    gfx_apply_display_config();
}
