#include "include_asm.h"

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
extern SubtitleBoxState D_00254E78;
extern SubtitleBoxEntry *D_001B1840[] __attribute__((sda));
extern unsigned char D_001A7B90[] __attribute__((sda));
#define SUBTITLE_SETTING (*(unsigned short *)&D_001A7B90[4])
#define SUBTITLE_BOX_SETTING (D_001A7B90[5])
extern void func_0027EB88(int top, int bottom, int left, int right, int alpha, int color);
extern void func_PAL_0029BFF0(int alpha, int color, float top, float bottom, float left, float right);
extern void func_002802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_00280200(unsigned short *, unsigned long long, unsigned char *, int);
extern void func_PAL_0028A468(void);

void func_PAL_0028A470(void)
{
    unsigned short layout[16];

    D_00254E78.offsetTimer--;
    if (D_00254E78.offsetTimer < 0)
        D_00254E78.offsetTimer = 0;
    if (D_00254E78.offsetTimer == 0)
        D_00254E78.offset = 0;
    if (!D_00254E78.state || !D_00254E78.enabled || !SUBTITLE_SETTING)
        return;

    switch (D_00254E78.state) {
    case 1: {
        int w, h, y, x, offset;

        if (SUBTITLE_BOX_SETTING) {
            h = 8;
            w = 8;
            D_00254E78.boxHalfWidth = w;
            D_00254E78.boxHalfHeight = h;
            y = D_00254E78.y;
            x = D_00254E78.x;
            offset = D_00254E78.offset;
            func_0027EB88(y - h + offset, y + h + offset, x - w, x + w, 96, 0x60442D00);
            func_PAL_0029BFF0(96, 0x55F0C070,
                          D_00254E78.y - D_00254E78.boxHalfHeight + D_00254E78.offset,
                          D_00254E78.y + D_00254E78.boxHalfHeight + D_00254E78.offset,
                          D_00254E78.x - D_00254E78.boxHalfWidth,
                          D_00254E78.x + D_00254E78.boxHalfWidth);
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
            t = D_00254E78.timer;
            if (t > 8)
                t = 8;
            if (t < 0)
                t = 0;
            w = 32 + (D_00254E78.halfWidth - 32) * t / 8;
            h = 32 + (D_00254E78.halfHeight - 32) * t / 8;
            D_00254E78.boxHalfWidth = w;
            D_00254E78.boxHalfHeight = h;
            y = D_00254E78.y;
            x = D_00254E78.x;
            offset = D_00254E78.offset;
            func_0027EB88(y - h + offset, y + h + offset, x - w, x + w, 96, 0x60442D00);
            func_PAL_0029BFF0(96, 0x55F0C070,
                          D_00254E78.y - D_00254E78.boxHalfHeight + D_00254E78.offset,
                          D_00254E78.y + D_00254E78.boxHalfHeight + D_00254E78.offset,
                          D_00254E78.x - D_00254E78.boxHalfWidth,
                          D_00254E78.x + D_00254E78.boxHalfWidth);
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
            h = D_00254E78.halfHeight;
            w = D_00254E78.halfWidth;
            D_00254E78.boxHalfWidth = w;
            D_00254E78.boxHalfHeight = h;
            y = D_00254E78.y;
            x = D_00254E78.x;
            offset = D_00254E78.offset;
            func_0027EB88(y - h + offset, y + h + offset, x - w, x + w, 96, 0x60442D00);
            color = 0x80FFA888;
            func_PAL_0029BFF0(96, 0x55F0C070,
                          D_00254E78.y - D_00254E78.boxHalfHeight + D_00254E78.offset,
                          D_00254E78.y + D_00254E78.boxHalfHeight + D_00254E78.offset,
                          D_00254E78.x - D_00254E78.boxHalfWidth,
                          D_00254E78.x + D_00254E78.boxHalfWidth);
            /* The text fades in (state 4) and out (state 6) over 4 frames. */
            t = D_00254E78.timer;
            if (t > 4)
                t = 4;
            if (t < 0)
                t = 0;
            if (D_00254E78.state == 4)
                color = (t << 29) | 0xFFA888;
            else if (D_00254E78.state == 6)
                color = ((4 - t) << 29) | 0xFFA888;
            text = D_001B1840[0][D_00254E78.entry].text;
            func_002802E0(layout, D_00254E78.offset + 240, D_00254E78.offset + 480, 44, 468, 256,
                          D_00254E78.y + D_00254E78.offset, 16, 3);
            func_00280200(layout, color, text, -1);
        } else {
            func_PAL_0028A468();
        }
        break;
    }
    case 7: {
        int t, w, h, y, x, offset, alpha;

        if (SUBTITLE_BOX_SETTING) {
            /* The box shrinks back to 8 and fades out over 8 frames. */
            t = D_00254E78.timer;
            if (t > 8)
                t = 8;
            if (t < 0)
                t = 0;
            h = D_00254E78.boxHalfHeight;
            w = D_00254E78.boxHalfWidth;
            w -= (w - 8) * t / 8;
            h -= (h - 8) * t / 8;
            alpha = (8 - t) * 12;
            y = D_00254E78.y;
            x = D_00254E78.x;
            offset = D_00254E78.offset;
            func_0027EB88(y - h + offset, y + h + offset, x - w, x + w, alpha, 0x60442D00);
            func_PAL_0029BFF0(alpha, 0x55F0C070,
                          D_00254E78.y - h + D_00254E78.offset,
                          D_00254E78.y + h + D_00254E78.offset,
                          D_00254E78.x - w, D_00254E78.x + w);
        } else {
            func_PAL_0028A468();
        }
        break;
    }
    }
}
