#include "include_asm.h"
#include "names.h"

typedef struct {
    unsigned char *text;
    int unk04;
    int id;
    int unk0C;
} SubtitleBoxEntry;
typedef struct {
    int state, timer, halfWidth, halfHeight, x, y, boxHalfWidth, boxHalfHeight;
    int entry, pending, selection, unk2C, enabled, wait;
    short flag38, flag3A;
    int countdown, offset, offsetTimer;
} SubtitleBoxState;
extern SubtitleBoxState g_subtitle_state;
extern SubtitleBoxEntry *g_subtitle_entries[] __attribute__((sda));
extern unsigned char g_is_pal_video[] __attribute__((sda));
#define SUBTITLE_SETTING (*(unsigned short *)&D_001A7B90[4])
#define SUBTITLE_BOX_SETTING (D_001A7B90[5])
extern void gfx_draw_rounded_box(int top, int bottom, int left, int right, int alpha, int color);
extern void level_set_rect_pal(int alpha, int color, float top, float bottom, float left, float right);
extern void FontSetWindow(unsigned short *, int, int, int, int, int, int, int, int);
extern void text_draw_window_medium(unsigned short *, unsigned long long, unsigned char *, int);
extern void func_PAL_0028A468(void);

void DrawSubtitleBox_pal(void)
{
    unsigned short layout[16];

    g_subtitle_state.offsetTimer--;
    if (g_subtitle_state.offsetTimer < 0)
        g_subtitle_state.offsetTimer = 0;
    if (g_subtitle_state.offsetTimer == 0)
        g_subtitle_state.offset = 0;
    if (!g_subtitle_state.state || !g_subtitle_state.enabled || !SUBTITLE_SETTING)
        return;

    switch (g_subtitle_state.state) {
    case 1: {
        int w, h, y, x, offset;

        if (SUBTITLE_BOX_SETTING) {
            h = 8;
            w = 8;
            g_subtitle_state.boxHalfWidth = w;
            g_subtitle_state.boxHalfHeight = h;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - h + offset, y + h + offset, x - w, x + w, 96, 0x60442D00);
            level_set_rect_pal(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.boxHalfWidth,
                          g_subtitle_state.x + g_subtitle_state.boxHalfWidth);
        } else {
            func_PAL_0028A468();
        }
        break;
    }
    case 2:
        func_PAL_0028A468();
        break;
    case 3: {
        int t, w, h, y, x, offset;

        if (SUBTITLE_BOX_SETTING) {
            /* The box grows from 32 to its full half extents over 8 frames. */
            t = g_subtitle_state.timer;
            if (t > 8)
                t = 8;
            if (t < 0)
                t = 0;
            w = 32 + (g_subtitle_state.halfWidth - 32) * t / 8;
            h = 32 + (g_subtitle_state.halfHeight - 32) * t / 8;
            g_subtitle_state.boxHalfWidth = w;
            g_subtitle_state.boxHalfHeight = h;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - h + offset, y + h + offset, x - w, x + w, 96, 0x60442D00);
            level_set_rect_pal(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.boxHalfWidth,
                          g_subtitle_state.x + g_subtitle_state.boxHalfWidth);
        } else {
            func_PAL_0028A468();
        }
        break;
    }
    case 4:
    case 5:
    case 6: {
        int t, w, h, y, x, offset;
        int color;
        unsigned char *text;

        if (SUBTITLE_BOX_SETTING) {
            h = g_subtitle_state.halfHeight;
            w = g_subtitle_state.halfWidth;
            g_subtitle_state.boxHalfWidth = w;
            g_subtitle_state.boxHalfHeight = h;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - h + offset, y + h + offset, x - w, x + w, 96, 0x60442D00);
            color = 0x80FFA888;
            level_set_rect_pal(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.boxHalfWidth,
                          g_subtitle_state.x + g_subtitle_state.boxHalfWidth);
            /* The text fades in (state 4) and out (state 6) over 4 frames. */
            t = g_subtitle_state.timer;
            if (t > 4)
                t = 4;
            if (t < 0)
                t = 0;
            if (g_subtitle_state.state == 4)
                color = (t << 29) | 0xFFA888;
            else if (g_subtitle_state.state == 6)
                color = ((4 - t) << 29) | 0xFFA888;
            text = g_subtitle_entries[0][g_subtitle_state.entry].text;
            FontSetWindow(layout, g_subtitle_state.offset + 240, g_subtitle_state.offset + 480, 44, 468, 256,
                          g_subtitle_state.y + g_subtitle_state.offset, 16, 3);
            text_draw_window_medium(layout, color, text, -1);
        } else {
            func_PAL_0028A468();
        }
        break;
    }
    case 7: {
        int t, w, h, y, x, offset, alpha;

        if (SUBTITLE_BOX_SETTING) {
            /* The box shrinks back to 8 and fades out over 8 frames. */
            t = g_subtitle_state.timer;
            if (t > 8)
                t = 8;
            if (t < 0)
                t = 0;
            h = g_subtitle_state.boxHalfHeight;
            w = g_subtitle_state.boxHalfWidth;
            w -= (w - 8) * t / 8;
            h -= (h - 8) * t / 8;
            alpha = (8 - t) * 12;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - h + offset, y + h + offset, x - w, x + w, alpha, 0x60442D00);
            level_set_rect_pal(alpha, 0x55F0C070,
                          g_subtitle_state.y - h + g_subtitle_state.offset,
                          g_subtitle_state.y + h + g_subtitle_state.offset,
                          g_subtitle_state.x - w, g_subtitle_state.x + w);
        } else {
            func_PAL_0028A468();
        }
        break;
    }
    }
}
