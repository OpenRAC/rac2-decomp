#include "names.h"
/* func_002900B8 (1,388 bytes, 28 places): a HUD panel with two scale bars and three text rows.
 * Own unit: -O2 -G8 -fno-expensive-optimizations -ffunction-sections -frac2-keep-block-order
 * -frac2-cse2-keep-multi-set-reg -frac2-cse-arg-hard-reg -frac2-reload-cse-branch-to-next
 * (config/cflags.txt; docs/build/compiler-notes.md). Case 0 keeps the scale as in cases 1/2,
 * `s = 128.0f` before the upper bar's rounding, and edge/edge2 locals for the bar limits. The
 * hud_coord dead-test helper is allowed by owner ruling (7 November 2026). Owner standard of
 * 12 November 2026 for the switches (22 functions change when they are forced on).
 */
#include "common.h"

extern int g_gauge_popup_blend __attribute__((sda));
extern int g_gauge_popup_mode __attribute__((sda));
extern float g_gauge_popup_amount __attribute__((sda));
extern int g_gauge_popup_color_a __attribute__((sda));
extern int g_gauge_popup_color_b __attribute__((sda));

typedef struct {
    int active;
    int timer;
    char pad08[0x18];
    int entryIndex;
    int unk24;
} Subtitle_002900B8;

typedef struct {
    char pad[0xB0];
    float opacity;
} Hud_002900B8;

extern char *D_001A8CFC[] __attribute__((sda));
extern Subtitle_002900B8 g_subtitle_state;
extern Hud_002900B8 D_001B9040;
extern float D_001B23A4[] __attribute__((sda));
extern int D_001A8D40 __attribute__((sda));
extern void UpdateViewContext(void);
extern float IntToFloat(int);
extern int FastTweenColor(int, int, float);
extern char *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);

extern int D_001B23A0;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the gauge pop-up: a dark panel with scale bars filled up to the current amount. */
int gauge_popup_draw(void)
{
    float saved_opacity;
    float blend;
    float scale;
    float zero;
    float y;
    char *panel_texture;
    int back_color;
    int frame_color;
    int one;
    float half;

    if (D_001A8CFC[0] != 0 && g_subtitle_state.active == 0 && g_subtitle_state.unk24 == -1) {
        one = 1;
        half = 0.5f;
        saved_opacity = D_001B9040.opacity;
        D_001B9040.opacity = 0.62f;
        UpdateViewContext();
        blend = IntToFloat(g_gauge_popup_blend) * 0.1f;
        back_color = FastTweenColor(0x442D00, 0x60442D00, blend);
        frame_color = FastTweenColor(0xF0C070, 0x55F0C070, blend);
        panel_texture = table_find_by_id(D_001A8CFC[0] + 0x8710, 0xA6);
        y = (float)label_y(panel_texture, 206.0f, D_001B23A4[0], half, one);
        scale = 1.0f;
        zero = 0.0f;
        gfx_draw_scaled_object_two_axes(panel_texture, back_color, 484.0f, y, scale, scale, zero);
        panel_texture = table_find_by_id(D_001A8CFC[0] + 0x8710, 0xA7);
        gfx_draw_scaled_object_two_axes(panel_texture, frame_color, 484.0f, (float)label_y(panel_texture, 206.0f, D_001B23A4[0], half, one), 1.0f, 1.0f, 0.0f);
        switch (g_gauge_popup_mode) {
        case 0:
            if (zero <= g_gauge_popup_amount && g_gauge_popup_amount <= scale) {
                int color1;
                int color2;
                int top;
                int i;
                float step;
                float lower;
                float upper;
                float edge;
                float edge2;
                float s;

                color1 = FastTweenColor(g_gauge_popup_color_a & 0xFFFFFF, g_gauge_popup_color_a, blend);
                color2 = FastTweenColor(g_gauge_popup_color_b & 0xFFFFFF, g_gauge_popup_color_b, blend);
                s = D_001B23A4[0];
                top = hud_coord((float)(285 - (int)((scale - g_gauge_popup_amount) * 157.0f)), s, half, one);
                s = (float)hud_coord(128.0f, D_001B23A4[0], half, one);
                step = s * 0.25f;
                lower = (float)hud_coord(285.0f, D_001B23A4[0], half, one);
                edge = lower - step;
                upper = edge + scale;
                for (i = 0; i < 5; i++) {
                    scale = (float)top;
                    if (upper <= scale)
                        upper = scale;
                    gfx_draw_colored_rectangle((int)upper, (int)lower, 477, 489, color1);
                    lower -= step;
                    upper -= step;
                    if (lower <= scale)
                        break;
                }
                s = 128.0f;
                upper = (float)hud_coord(s, D_001B23A4[0], 0.5f, 1);
                edge2 = upper + step;
                lower = edge2 - 1.0f;
                for (i = 0; i < 5; i++) {
                                        if ((float)top <= lower)
                        lower = (float)top;
                    gfx_draw_colored_rectangle((int)upper, (int)lower, 476, 488, color2);
                    upper += step;
                    lower += step;
                    if ((float)top <= upper)
                        break;
                }
            }
            break;
        case 1:
        case 2: {
            int color;
            int top;
            int i;
            float step;
            float lower;
            float upper;
            float limit;
            float s;
            float edge;

            color = FastTweenColor(g_gauge_popup_color_a & 0xFFFFFF, g_gauge_popup_color_a, blend);
            s = D_001B23A4[0];
            top = hud_coord((float)(285 - (int)((1.0f - g_gauge_popup_amount) * 157.0f)), s, 0.5f, 1);
            s = (float)hud_coord(128.0f, D_001B23A4[0], 0.5f, 1);
            step = s * 0.25f;
            lower = (float)hud_coord(285.0f, D_001B23A4[0], 0.5f, 1);
            edge = lower - step;
            upper = edge + 1.0f;
            for (i = 0; i < 5; i++) {
                limit = (float)top;
                if (upper <= limit)
                    upper = limit;
                gfx_draw_colored_rectangle((int)upper, (int)lower, 476, 488, color);
                lower -= step;
                upper -= step;
                if (lower <= limit)
                    break;
            }
        }
        }
        D_001B9040.opacity = saved_opacity;
        UpdateViewContext();
    }
    return D_001A8D40;
}
