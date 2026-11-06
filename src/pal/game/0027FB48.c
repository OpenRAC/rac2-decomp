#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern u64 func_0027C878(int);
extern void func_PAL_0027FB48(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_00263B50[];

/* Scaled FontPrint: the text is drawn at (x, y) with font texture 1. */
void func_PAL_0027FE88(float x, float y, u64 color, u8 *text, int length, float scale) {
    u64 texture;

    texture = func_0027C878(1);
    func_PAL_0027FB48(x, y, color, text, length, scale, texture, D_00263B50);
}
