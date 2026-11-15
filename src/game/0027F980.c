#include "names.h"
typedef unsigned char u8;
typedef unsigned long u64;
extern int func_0027F178(u8 *, int);
extern int func_0027F198(u8 *, int);
extern int func_0027F1B8(u8 *, int);
extern u64 func_0027C878(int);
extern void func_0027F2A8(int, int, u64, u8 *, int, u64, u8 *);
extern u8 D_00263B50[];
extern u8 D_00263EF0[];
extern u8 D_00264290[];

/* Draws right-aligned text ending at x, in the small font. */
void func_0027F980(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= MeasureTextWidthSmallFont(text, length);
    font = GetEffectTextureDescriptor(1);
    DrawTextLine(x, y, style, text, length, font, D_00263B50);
}

/* Draws right-aligned text ending at x, in the medium font. */
void func_0027FA10(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= MeasureTextWidthMediumFont(text, length);
    font = GetEffectTextureDescriptor(2);
    DrawTextLine(x, y, style, text, length, font, D_00263EF0);
}

/* Draws text centered on x in the small font and returns where it starts. */
int func_0027FAA8(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= MeasureTextWidthSmallFont(text, length) >> 1;
    font = GetEffectTextureDescriptor(1);
    DrawTextLine(x, y, style, text, length, font, D_00263B50);
    return x;
}

/* Draws text centered on x in the medium font and returns where it starts. */
int func_0027FB40(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= MeasureTextWidthMediumFont(text, length) >> 1;
    font = GetEffectTextureDescriptor(2);
    DrawTextLine(x, y, style, text, length, font, D_00263EF0);
    return x;
}

/* Draws text centered on x in the large font and returns where it starts. */
int func_0027FBD8(int x, int y, u64 style, u8 *text, int length)
{
    u64 font;
    x -= MeasureTextWidthLargeFont(text, length) >> 1;
    font = GetEffectTextureDescriptor(3);
    DrawTextLine(x, y, style, text, length, font, D_00264290);
    return x;
}
