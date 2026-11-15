#include "common.h"

extern int func_L18_00303A58(u8 *, int, float);
extern u64 func_0027C878(int);
extern void func_0027F640(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_L18_00296510[];

/* Draws a line of text centered on the given x position. */
void func_L18_003044B8(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (DrawFixedText(text, length, scale) >> 1);
    fy = y;
    texture = GetEffectTextureDescriptor(3);
    FontPrintScaled(fx, fy, color, text, length, scale, texture, D_L18_00296510);
}
