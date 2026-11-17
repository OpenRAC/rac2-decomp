#include "include_asm.h"
#include "names.h"

typedef struct {
    unsigned char *text;
    int unk04;
    int id;
    int unk0C;
} SubtitleBoxEntry;
typedef struct {
    int state, timer, half_width, half_height, x, y, box_half_width, box_half_height;
    int entry, pending, selection, unk2C, enabled, wait;
    short flag38, flag3A;
    int countdown, offset, offset_timer;
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
extern void subtitle_empty_b(void);

/* Draws the subtitle box and its text, growing, fading and shrinking it by state (PAL: level_set_rect_pal draws the border). */
void DrawSubtitleBox_pal(void)
{
    unsigned short layout[16];

    g_subtitle_state.offset_timer--;
    if (g_subtitle_state.offset_timer < 0)
        g_subtitle_state.offset_timer = 0;
    if (g_subtitle_state.offset_timer == 0)
        g_subtitle_state.offset = 0;
    if (!g_subtitle_state.state || !g_subtitle_state.enabled || !SUBTITLE_SETTING)
        return;

    switch (g_subtitle_state.state) {
    case 1: {
        int width, height, y, x, offset;

        if (SUBTITLE_BOX_SETTING) {
            height = 8;
            width = 8;
            g_subtitle_state.box_half_width = width;
            g_subtitle_state.box_half_height = height;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - height + offset, y + height + offset, x - width, x + width, 96, 0x60442D00);
            level_set_rect_pal(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.box_half_height + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.box_half_height + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.box_half_width,
                          g_subtitle_state.x + g_subtitle_state.box_half_width);
        } else {
            subtitle_empty_b();
        }
        break;
    }
    case 2:
        subtitle_empty_b();
        break;
    case 3: {
        int frames, width, height, y, x, offset;

        if (SUBTITLE_BOX_SETTING) {
            /* The box grows from 32 to its full half extents over 8 frames. */
            frames = g_subtitle_state.timer;
            if (frames > 8)
                frames = 8;
            if (frames < 0)
                frames = 0;
            width = 32 + (g_subtitle_state.half_width - 32) * frames / 8;
            height = 32 + (g_subtitle_state.half_height - 32) * frames / 8;
            g_subtitle_state.box_half_width = width;
            g_subtitle_state.box_half_height = height;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - height + offset, y + height + offset, x - width, x + width, 96, 0x60442D00);
            level_set_rect_pal(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.box_half_height + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.box_half_height + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.box_half_width,
                          g_subtitle_state.x + g_subtitle_state.box_half_width);
        } else {
            subtitle_empty_b();
        }
        break;
    }
    case 4:
    case 5:
    case 6: {
        int frames, width, height, y, x, offset;
        int color;
        unsigned char *text;

        if (SUBTITLE_BOX_SETTING) {
            height = g_subtitle_state.half_height;
            width = g_subtitle_state.half_width;
            g_subtitle_state.box_half_width = width;
            g_subtitle_state.box_half_height = height;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - height + offset, y + height + offset, x - width, x + width, 96, 0x60442D00);
            color = 0x80FFA888;
            level_set_rect_pal(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.box_half_height + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.box_half_height + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.box_half_width,
                          g_subtitle_state.x + g_subtitle_state.box_half_width);
            /* The text fades in (state 4) and out (state 6) over 4 frames. */
            frames = g_subtitle_state.timer;
            if (frames > 4)
                frames = 4;
            if (frames < 0)
                frames = 0;
            if (g_subtitle_state.state == 4)
                color = (frames << 29) | 0xFFA888;
            else if (g_subtitle_state.state == 6)
                color = ((4 - frames) << 29) | 0xFFA888;
            text = g_subtitle_entries[0][g_subtitle_state.entry].text;
            FontSetWindow(layout, g_subtitle_state.offset + 240, g_subtitle_state.offset + 480, 44, 468, 256,
                          g_subtitle_state.y + g_subtitle_state.offset, 16, 3);
            text_draw_window_medium(layout, color, text, -1);
        } else {
            subtitle_empty_b();
        }
        break;
    }
    case 7: {
        int frames, width, height, y, x, offset, alpha;

        if (SUBTITLE_BOX_SETTING) {
            /* The box shrinks back to 8 and fades out over 8 frames. */
            frames = g_subtitle_state.timer;
            if (frames > 8)
                frames = 8;
            if (frames < 0)
                frames = 0;
            height = g_subtitle_state.box_half_height;
            width = g_subtitle_state.box_half_width;
            width -= (width - 8) * frames / 8;
            height -= (height - 8) * frames / 8;
            alpha = (8 - frames) * 12;
            y = g_subtitle_state.y;
            x = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(y - height + offset, y + height + offset, x - width, x + width, alpha, 0x60442D00);
            level_set_rect_pal(alpha, 0x55F0C070,
                          g_subtitle_state.y - height + g_subtitle_state.offset,
                          g_subtitle_state.y + height + g_subtitle_state.offset,
                          g_subtitle_state.x - width, g_subtitle_state.x + width);
        } else {
            subtitle_empty_b();
        }
        break;
    }
    }
}
