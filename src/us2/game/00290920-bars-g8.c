#include "names.h"
/* func_US2_00290920 (1,404 bytes): the USA v2.00 copy of func_002900B8
 * (src/game/002900B8-bars-g8.c), the HUD panel with two scale bars and three text rows. v2.00
 * also draws it while D_001A9004 is 2, whatever the subtitle state. Built with the v1.01
 * unit's flags (config/cflags.txt); the hud_coord dead-test helper is allowed by owner ruling
 * (7 November 2026).
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
extern void *table_find_by_id(char *, int);
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

int func_US2_00290920(void)
{
    float saved;
    float pulse;
    float scale;
    float zero;
    float y;
    char *text;
    int first;
    int second;
    int one;
    float half;

    if (D_001A8CFC[0] != 0 && ((g_subtitle_state.active == 0 && g_subtitle_state.unk24 == -1) || g_gauge_popup_mode == 2)) {
        one = 1;
        half = 0.5f;
        saved = D_001B9040.opacity;
        D_001B9040.opacity = 0.62f;
        UpdateViewContext();
        pulse = IntToFloat(g_gauge_popup_blend) * 0.1f;
        first = FastTweenColor(0x442D00, 0x60442D00, pulse);
        second = FastTweenColor(0xF0C070, 0x55F0C070, pulse);
        text = table_find_by_id(D_001A8CFC[0] + 0x8710, 0xA6);
        y = (float)label_y(text, 206.0f, D_001B23A4[0], half, one);
        scale = 1.0f;
        zero = 0.0f;
        gfx_draw_scaled_object_two_axes(text, first, 484.0f, y, scale, scale, zero);
        text = table_find_by_id(D_001A8CFC[0] + 0x8710, 0xA7);
        gfx_draw_scaled_object_two_axes(text, second, 484.0f, (float)label_y(text, 206.0f, D_001B23A4[0], half, one), 1.0f, 1.0f, 0.0f);
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

                color1 = FastTweenColor(g_gauge_popup_color_a & 0xFFFFFF, g_gauge_popup_color_a, pulse);
                color2 = FastTweenColor(g_gauge_popup_color_b & 0xFFFFFF, g_gauge_popup_color_b, pulse);
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

            color = FastTweenColor(g_gauge_popup_color_a & 0xFFFFFF, g_gauge_popup_color_a, pulse);
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
        D_001B9040.opacity = saved;
        UpdateViewContext();
    }
    return D_001A8D40;
}
