#include "common.h"
extern int func_00283CF0(float);
extern void func_002FC560(unsigned int reg, unsigned long value);
extern void func_0027DE50(int a, int b, int c, int d, unsigned long e);
extern short D_001A6480[];

void func_L00_00409480(char *arg)
{
    int *o = *(int **)(arg + 104);
    short *t;
    int c;
    int rgba;

    c = 128 - FloatToInt((float)(o[2] * 2));
    rgba = c << 24;
    rgba |= c << 16;
    rgba |= c << 8;
    rgba |= c;
    VU1_addGSregister(66, 72);
    t = D_001A6480;
    func_0027DE50(0, t[0xA9], 0, t[0xA8], rgba);
    func_0027DE50(0, t[0xA9], 0, t[0xA8], rgba);
    func_0027DE50(0, t[0xA9], 0, t[0xA8], rgba);
    func_0027DE50(0, t[0xA9], 0, t[0xA8], rgba);
}
