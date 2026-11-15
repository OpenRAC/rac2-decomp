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

extern SubtitleBoxState D_00254E78;
extern SubtitleBoxEntry *D_001B1840[] __attribute__((sda));

/* The settings block func_00298E08 copies. Retail reads its halfword at +4 and byte at +5 at
 * an offset from the block (lui and a tied %lo load, never moved into a delay slot). */
extern unsigned char D_001A7B90[] __attribute__((sda));
#define SUBTITLE_SETTING (*(unsigned short *)&D_001A7B90[4])
#define SUBTITLE_BOX_SETTING (D_001A7B90[5])

extern void func_0027EB88(int top, int bottom, int left, int right, int alpha, int color);
extern void func_0029B658(int alpha, int color, float top, float bottom, float left, float right);
extern void func_002802E0(unsigned short *, int, int, int, int, int, int, int, int);
extern void func_00280200(unsigned short *, unsigned long long, unsigned char *, int);
extern void func_00289AA0(void);

/* Draws the subtitle box and its text, growing, showing and shrinking it by state. */
void func_00289AA8(void)
{
    unsigned short layout[16];

    gSubtitleState.offsetTimer--;
    if (gSubtitleState.offsetTimer < 0)
        gSubtitleState.offsetTimer = 0;
    if (gSubtitleState.offsetTimer == 0)
        gSubtitleState.offset = 0;
    if (!gSubtitleState.state || !gSubtitleState.enabled || !SUBTITLE_SETTING)
        return;

    switch (gSubtitleState.state) {
    case 1: {
        int halfW, halfH, posY, posX, offset;

        if (SUBTITLE_BOX_SETTING) {
            halfH = 8;
            halfW = 8;
            gSubtitleState.boxHalfWidth = halfW;
            gSubtitleState.boxHalfHeight = halfH;
            posY = gSubtitleState.y;
            posX = gSubtitleState.x;
            offset = gSubtitleState.offset;
            DrawRoundedBox(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, 96, 0x60442D00);
            SetLevelObjectRect(96, 0x55F0C070,
                          gSubtitleState.y - gSubtitleState.boxHalfHeight + gSubtitleState.offset,
                          gSubtitleState.y + gSubtitleState.boxHalfHeight + gSubtitleState.offset,
                          gSubtitleState.x - gSubtitleState.boxHalfWidth,
                          gSubtitleState.x + gSubtitleState.boxHalfWidth);
        } else {
            EmptySubtitleStubB();
        }
        break;
    }
    case 2:
        EmptySubtitleStubB();
        break;
    case 3: {
        int progress, halfW, halfH, posY, posX, offset;

        if (SUBTITLE_BOX_SETTING) {
            /* The box grows from 32 to its full half extents over 8 frames. */
            progress = gSubtitleState.timer;
            if (progress > 8)
                progress = 8;
            if (progress < 0)
                progress = 0;
            halfW = 32 + (gSubtitleState.halfWidth - 32) * progress / 8;
            halfH = 32 + (gSubtitleState.halfHeight - 32) * progress / 8;
            gSubtitleState.boxHalfWidth = halfW;
            gSubtitleState.boxHalfHeight = halfH;
            posY = gSubtitleState.y;
            posX = gSubtitleState.x;
            offset = gSubtitleState.offset;
            DrawRoundedBox(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, 96, 0x60442D00);
            SetLevelObjectRect(96, 0x55F0C070,
                          gSubtitleState.y - gSubtitleState.boxHalfHeight + gSubtitleState.offset,
                          gSubtitleState.y + gSubtitleState.boxHalfHeight + gSubtitleState.offset,
                          gSubtitleState.x - gSubtitleState.boxHalfWidth,
                          gSubtitleState.x + gSubtitleState.boxHalfWidth);
        } else {
            EmptySubtitleStubB();
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
            halfH = gSubtitleState.halfHeight;
            halfW = gSubtitleState.halfWidth;
            gSubtitleState.boxHalfWidth = halfW;
            gSubtitleState.boxHalfHeight = halfH;
            posY = gSubtitleState.y;
            posX = gSubtitleState.x;
            offset = gSubtitleState.offset;
            DrawRoundedBox(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, 96, 0x60442D00);
            color = 0x80FFA888;
            SetLevelObjectRect(96, 0x55F0C070,
                          gSubtitleState.y - gSubtitleState.boxHalfHeight + gSubtitleState.offset,
                          gSubtitleState.y + gSubtitleState.boxHalfHeight + gSubtitleState.offset,
                          gSubtitleState.x - gSubtitleState.boxHalfWidth,
                          gSubtitleState.x + gSubtitleState.boxHalfWidth);
            /* The text fades in (state 4) and out (state 6) over 4 frames. */
            progress = gSubtitleState.timer;
            if (progress > 4)
                progress = 4;
            if (progress < 0)
                progress = 0;
            if (gSubtitleState.state == 4)
                color = (progress << 29) | 0xFFA888;
            else if (gSubtitleState.state == 6)
                color = ((4 - progress) << 29) | 0xFFA888;
            text = gSubtitleEntries[0][gSubtitleState.entry].text;
            FontSetWindow(layout, gSubtitleState.offset + 240, gSubtitleState.offset + 480, 44, 468, 256,
                          gSubtitleState.y + gSubtitleState.offset, 16, 3);
            DrawTextWindowMediumFont(layout, color, text, -1);
        } else {
            EmptySubtitleStubB();
        }
        break;
    }
    case 7: {
        int progress, halfW, halfH, posY, posX, offset, alpha;

        if (SUBTITLE_BOX_SETTING) {
            /* The box shrinks back to 8 and fades out over 8 frames. */
            progress = gSubtitleState.timer;
            if (progress > 8)
                progress = 8;
            if (progress < 0)
                progress = 0;
            halfH = gSubtitleState.boxHalfHeight;
            halfW = gSubtitleState.boxHalfWidth;
            halfW -= (halfW - 8) * progress / 8;
            halfH -= (halfH - 8) * progress / 8;
            alpha = (8 - progress) * 12;
            posY = gSubtitleState.y;
            posX = gSubtitleState.x;
            offset = gSubtitleState.offset;
            DrawRoundedBox(posY - halfH + offset, posY + halfH + offset, posX - halfW, posX + halfW, alpha, 0x60442D00);
            SetLevelObjectRect(alpha, 0x55F0C070,
                          gSubtitleState.y - halfH + gSubtitleState.offset,
                          gSubtitleState.y + halfH + gSubtitleState.offset,
                          gSubtitleState.x - halfW, gSubtitleState.x + halfW);
        } else {
            EmptySubtitleStubB();
        }
        break;
    }
    }
}
