#include "include_asm.h"


typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
extern u16 D_L11_001B1850 __attribute__((sda));
extern s32 D_L11_001B1848 __attribute__((sda));
extern s32 D_L11_001B184C __attribute__((sda));
extern s32 D_L11_001B1844 __attribute__((sda));
extern s32 D_L11_001B1858 __attribute__((sda));
extern s32 D_L11_001B185C __attribute__((sda));
extern s32 D_L11_001B1860 __attribute__((sda));
extern short D_001A6480[];
extern float func_00283CE0(short);
extern void func_002FC560(int, long long);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern long long func_0027C878(int);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Same body as func_L02_004002E0, with this function's own callees. */
void func_L11_00445B30(char *a0) {
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

    color = D_L11_001B1848;
    *(u16 *)(state + 0x1F4) -= D_L11_001B1850;
    f20 = func_00283CE0(*(u16 *)(state + 0x1F4));
    height = (float)D_001A6480[0xA9];
    f20 = f20 / height;
    f20 = f20 * f20;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(f20 * scale) << 24;
    }
    func_002FC560(0x42, 0x8000000049LL);
    for (i = 0; i < D_L11_001B184C; i++)
        func_0028FC48(0, 0, D_001A6480[0xA8], D_001A6480[0xA9], color, 0);
    func_002FC560(0x42, 0x8000000044LL);
    screen = D_001A6480;
    func_0028FC48(0, 0, screen[0xA8], *(s16 *)(state + 0x1F4), D_L11_001B1844, 0);
    id = func_0027C878(0x10);
    color = D_L11_001B185C;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(f20 * scale) << 24;
    }
    func_002FC560(0x42, 0x8000000048LL);
    h = *(s16 *)(state + 0x1F4);
    n = screen[0xA9] - h;
    if (D_L11_001B1858 < n)
        n = D_L11_001B1858;
    m = D_L11_001B1860;
    func_0027E018(-m, h - (n >> 1), screen[0xA8] + m * 2, n, 0, 0, 0x20, 0x20, color, id);
}
