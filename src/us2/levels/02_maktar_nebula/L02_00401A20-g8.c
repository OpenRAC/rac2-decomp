#include "include_asm.h"

typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;

extern u16 D_L02_001B14F8 __attribute__((sda));
extern s32 D_L02_001B14F0 __attribute__((sda));
extern s32 D_L02_001B14F4 __attribute__((sda));
extern s32 D_L02_001B14EC __attribute__((sda));
extern s32 D_L02_001B1500 __attribute__((sda));
extern s32 D_L02_001B1504 __attribute__((sda));
extern s32 D_L02_001B1508 __attribute__((sda));
extern short D_001A6480[];
extern float func_00283CE0(short);
extern void func_002FC560(int, long long);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern long long func_US2_0027CED8(int);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* func_US2_L02_00401A20, the USA v2.00 copy of func_L02_004002E0: the same C, where the height is
   clamped at 0 after it drops and the first colour is read after that clamp. */

/* Draws the transition overlay. The height at +0x124 of the object's state drops by D_L02_001B14F8;
   func_00283CE0 turns it into a ratio, which is divided by the screen height (D_001A6480[0xA9]) and
   squared, and scales the alpha byte of two colours. The first colour fills the screen
   D_L02_001B14F4 times under one blend mode; D_L02_001B14EC fills the band down to the height; a
   0x20 by 0x20 sprite (func_US2_0027CED8(0x10)) in the second colour is drawn over its lower edge,
   D_L02_001B1508 wider on each side and at most D_L02_001B1500 tall. Built with -g
   (config/cflags.txt): retail has two nops in front of the division, which the assembler puts after
   a line label, so the division is a statement of its own. */
void func_US2_L02_00401A20(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    s32 color;
    float f20;
    float height;
    long long id;
    s32 i;
    s32 h;
    s32 n;
    s32 m;
    short *screen;

    *(u16 *)(state + 0x124) -= D_L02_001B14F8;
    if (*(s16 *)(state + 0x124) < 0)
        *(s16 *)(state + 0x124) = 0;
    color = D_L02_001B14F0;
    f20 = func_00283CE0(*(u16 *)(state + 0x124));
    height = (float)D_001A6480[0xA9];
    f20 = f20 / height;
    f20 = f20 * f20;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(f20 * scale) << 24;
    }
    func_002FC560(0x42, 0x8000000049LL);
    for (i = 0; i < D_L02_001B14F4; i++)
        func_0028FC48(0, 0, D_001A6480[0xA8], D_001A6480[0xA9], color, 0);
    func_002FC560(0x42, 0x8000000044LL);
    screen = D_001A6480;
    func_0028FC48(0, 0, screen[0xA8], *(s16 *)(state + 0x124), D_L02_001B14EC, 0);
    id = func_US2_0027CED8(0x10);
    color = D_L02_001B1504;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(f20 * scale) << 24;
    }
    func_002FC560(0x42, 0x8000000048LL);
    h = *(s16 *)(state + 0x124);
    n = screen[0xA9] - h;
    if (D_L02_001B1500 < n)
        n = D_L02_001B1500;
    m = D_L02_001B1508;
    func_0027E018(-m, h - (n >> 1), screen[0xA8] + m * 2, n, 0, 0, 0x20, 0x20, color, id);
}
