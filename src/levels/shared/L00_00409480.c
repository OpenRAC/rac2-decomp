#include "common.h"
extern int func_00283CF0(float);
extern void func_002FC560(unsigned int reg, unsigned long value);
extern void func_0027DE50(int a, int b, int c, int d, unsigned long e);
extern short D_001A6480[];

/* Draws a gray flash over the whole screen that fades out as time passes. */
void func_L00_00409480(char *arg)
{
    int *vars = *(int **)(arg + 104);
    short *display;
    int gray;
    int rgba;

    gray = 128 - FloatToInt((float)(vars[2] * 2));
    rgba = gray << 24;
    rgba |= gray << 16;
    rgba |= gray << 8;
    rgba |= gray;
    VU1_addGSregister(66, 72);
    display = gScreenAdjustOffsets;
    DrawColoredRectangle(0, display[0xA9], 0, display[0xA8], rgba);
    DrawColoredRectangle(0, display[0xA9], 0, display[0xA8], rgba);
    DrawColoredRectangle(0, display[0xA9], 0, display[0xA8], rgba);
    DrawColoredRectangle(0, display[0xA9], 0, display[0xA8], rgba);
}
