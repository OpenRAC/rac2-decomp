#include "include_asm.h"
#include "names.h"

/* func_00289AA8, split from 00288D88.c: its jump table is this unit's only .rodata, and its
 * callee func_00289AA0 stays in 00288D88.c. Default -G0 profile, no cflags line. */

typedef struct {
    unsigned char *text;
    int unk04;
    int id;
    int unk0C;
} SubtitleBoxEntry;

/* The subtitle box state (func_00289020 seeds it: x 256, the half extents from the text). */
typedef struct {
    int state, timer, halfWidth, halfHeight, x, y, boxHalfWidth, boxHalfHeight;
    int entry, pending, selection, unk2C, enabled, wait;
    short flag38, flag3A;
    int countdown, offset, offsetTimer;
} SubtitleBoxState;

extern SubtitleBoxState g_subtitle_state;
extern SubtitleBoxEntry *g_subtitle_entries[] __attribute__((sda));

/* The settings block func_00298E08 copies. Retail reads its halfword at +4 and byte at +5 at
 * an offset from the block (lui and a tied %lo load, never moved into a delay slot). */
extern unsigned char g_is_pal_video[] __attribute__((sda));
#define SUBTITLE_SETTING (*(unsigned short *)&D_001A7B90[4])
#define SUBTITLE_BOX_SETTING (D_001A7B90[5])

extern void gfx_draw_rounded_box(int top, int bottom, int left, int right, int alpha, int color);
extern void level_set_rect(int alpha, int color, float top, float bottom, float left, float right);
extern void FontSetWindow(unsigned short *, int, int, int, int, int, int, int, int);
extern void text_draw_window_medium(unsigned short *, unsigned long long, unsigned char *, int);
extern void subtitle_empty_b(void);

/* Draws the subtitle box and its text, growing, showing and shrinking it by state. */
void DrawSubtitleBox(void)
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
        int halfW, halfH, posY, posX, offset;

        if (SUBTITLE_BOX_SETTING) {
            halfH = 8;
            halfW = 8;
            g_subtitle_state.boxHalfWidth = halfW;
            g_subtitle_state.boxHalfHeight = halfH;
            posY = g_subtitle_state.y;
            posX = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, 96, 0x60442D00);
            level_set_rect(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.boxHalfWidth,
                          g_subtitle_state.x + g_subtitle_state.boxHalfWidth);
        } else {
            subtitle_empty_b();
        }
        break;
    }
    case 2:
        subtitle_empty_b();
        break;
    case 3: {
        int progress, halfW, halfH, posY, posX, offset;

        if (SUBTITLE_BOX_SETTING) {
            /* The box grows from 32 to its full half extents over 8 frames. */
            progress = g_subtitle_state.timer;
            if (progress > 8)
                progress = 8;
            if (progress < 0)
                progress = 0;
            halfW = 32 + (g_subtitle_state.halfWidth - 32) * progress / 8;
            halfH = 32 + (g_subtitle_state.halfHeight - 32) * progress / 8;
            g_subtitle_state.boxHalfWidth = halfW;
            g_subtitle_state.boxHalfHeight = halfH;
            posY = g_subtitle_state.y;
            posX = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, 96, 0x60442D00);
            level_set_rect(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.boxHalfWidth,
                          g_subtitle_state.x + g_subtitle_state.boxHalfWidth);
        } else {
            subtitle_empty_b();
        }
        break;
    }
    case 4:
    case 5:
    case 6: {
        int progress, halfW, halfH, posY, posX, offset;
        int color;
        unsigned char *text;

        if (SUBTITLE_BOX_SETTING) {
            halfH = g_subtitle_state.halfHeight;
            halfW = g_subtitle_state.halfWidth;
            g_subtitle_state.boxHalfWidth = halfW;
            g_subtitle_state.boxHalfHeight = halfH;
            posY = g_subtitle_state.y;
            posX = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, 96, 0x60442D00);
            color = 0x80FFA888;
            level_set_rect(96, 0x55F0C070,
                          g_subtitle_state.y - g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.y + g_subtitle_state.boxHalfHeight + g_subtitle_state.offset,
                          g_subtitle_state.x - g_subtitle_state.boxHalfWidth,
                          g_subtitle_state.x + g_subtitle_state.boxHalfWidth);
            /* The text fades in (state 4) and out (state 6) over 4 frames. */
            progress = g_subtitle_state.timer;
            if (progress > 4)
                progress = 4;
            if (progress < 0)
                progress = 0;
            if (g_subtitle_state.state == 4)
                color = (progress << 29) | 0xFFA888;
            else if (g_subtitle_state.state == 6)
                color = ((4 - progress) << 29) | 0xFFA888;
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
        int progress, halfW, halfH, posY, posX, offset, alpha;

        if (SUBTITLE_BOX_SETTING) {
            /* The box shrinks back to 8 and fades out over 8 frames. */
            progress = g_subtitle_state.timer;
            if (progress > 8)
                progress = 8;
            if (progress < 0)
                progress = 0;
            halfH = g_subtitle_state.boxHalfHeight;
            halfW = g_subtitle_state.boxHalfWidth;
            halfW -= (halfW - 8) * progress / 8;
            halfH -= (halfH - 8) * progress / 8;
            alpha = (8 - progress) * 12;
            posY = g_subtitle_state.y;
            posX = g_subtitle_state.x;
            offset = g_subtitle_state.offset;
            gfx_draw_rounded_box(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, alpha, 0x60442D00);
            level_set_rect(alpha, 0x55F0C070,
                          g_subtitle_state.y - halfH + g_subtitle_state.offset,
                          g_subtitle_state.y + halfH + g_subtitle_state.offset,
                          g_subtitle_state.x - halfW, g_subtitle_state.x + halfW);
        } else {
            subtitle_empty_b();
        }
        break;
    }
    }
}
