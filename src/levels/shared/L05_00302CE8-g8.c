#include "common.h"

/* One glyph entry of the font metric table: texture position, baseline offset, advance. */
typedef struct {
    u8 u, v;
    s8 y, advance;
} L05Glyph;

extern u32 D_L05_001A8D00[8] SDATA(D_L05_001A8D00);
extern int D_L05_001B2028 __attribute__((sda));
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, u64, u64);

/* Word-wrapping FontPrint: draws text inside the box (x, y, width, height), moving a word
 * that would cross the right edge to the next 16-pixel line, and returns the height used.
 * Bytes 8..15 select a palette color, as in FontPrint (func_0027F2A8). */
int FontPrintWrapped(int x, int y, int width, int height, u64 color, u8 *text, int count,
                      u64 texture, L05Glyph *font)
{
    int cursorX = x, index = 0, cursorY = y, scan;
    u8 *word;
    float startX, wordWidth;
    u8 character;

    D_L05_001A8D00[0] = (s32)color;
    if (count && *text) {
        while (cursorY + 16 <= y + height) {
            /* Measure the word that starts here. */
            wordWidth = 0.0f;
            scan = index;
            word = text + index;
            startX = cursorX;
            while (scan != count && text[scan] != 32 && text[scan] >= 16) {
                wordWidth += font[text[scan]].advance;
                ++scan;
            }
            if ((float)(x + width) < startX + wordWidth) {
                if (*word != 32 && *word >= 16)
                    --index;
                cursorX = x;
                cursorY += 16;
            } else if (*word >= 8 && *word < 16) {
                if (D_L05_001B2028) {
                    color &= 0xFF000000ULL;
                    color |= D_L05_001A8D00[*word - 8] & 0xFFFFFF;
                }
            } else {
                character = *word;
                if (font[character].advance != 0) {
                    /* Characters 0x80..0xA7 also draw their glyph 0x40 entries above. */
                    if ((u8)(character + 128) < 40) {
                        int glyphIndex = *word + 64;
                        DrawTexturedQuad(cursorX + font[glyphIndex].advance, cursorY + font[glyphIndex].y,
                                      16, 16, font[glyphIndex].u, font[glyphIndex].v, 16, 16,
                                      color, texture);
                    }
                    if (*word < 32) {
                        DrawTexturedQuad(cursorX, cursorY + font[*word].y, 24, 16, font[*word].u,
                                      font[*word].v, 24, 16, color, texture);
                    } else if (*word > 32) {
                        DrawTexturedQuad(cursorX, cursorY + font[*word].y, 16, 16, font[*word].u,
                                      font[*word].v, 16, 16, color, texture);
                    }
                    cursorX += font[*word].advance;
                }
            }
            ++index;
            if (index == count || text[index] == 0)
                break;
        }
    }
    return cursorY - y + 16;
}
