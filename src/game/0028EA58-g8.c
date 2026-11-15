#include "common.h"
extern short *D_001B1890;
extern u32 *D_001B1894;
extern char *D_001B22A8;
extern char D_001AC830[];
extern char *ref_L00_002FA150_00 MACRO_ADDR;
extern int D_001A7350, D_001A7354, D_001B187C;
extern u64 func_0028E640(int);
/* Draws a textured rectangle for the given texture index at the given position and size with the four colours. */
void func_0028EA58(int texture, int x, int y, int width, int height, int *colors)
{
    short *pair = (short *)((texture << 2) + (u32)D_001B1890);
    u8 *entry = (u8 *)((u32)D_001B1894 + (pair[1] << 3));
    int w = 1 << entry[6];
    int h = 1 << entry[7];
    char *p, *q;
    u64 result;
    *(int *)D_001B22A8 = 0x10000008;
    *(int *)(D_001B22A8 + 4) = 0;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 12) = 0x50000008;
    p = D_001B22A8;
    D_001B22A8 = p + 16;
    qcopy(D_001B22A8, D_001AC830);
    q = p + 32;
    ref_L00_002FA150_00 = q;
    result = GetFrameTexture(texture);
    *(u64 *)q = result;
    *(u64 *)(q+8) = 0x15c;
    *(s64 *)(q+16) = colors[0];
    *(u64 *)(q+24) = 0;
    *(s64 *)(q+32) = ((x<<4)+D_001A7350-8) | ((s64)((y<<4)+D_001A7354-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(q+40) = colors[1];
    *(s64 *)(q+48) = w<<4;
    *(s64 *)(q+56) = (((x+width)<<4)+D_001A7350-8) | ((s64)((y<<4)+D_001A7354-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(q+64) = colors[2];
    *(s64 *)(q+72) = h<<20;
    *(s64 *)(q+80) = ((x<<4)+D_001A7350-8) | ((s64)(((y+height)<<4)+D_001A7354-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(q+88) = colors[3];
    *(s64 *)(q+96) = (h<<20)+(w<<4);
    *(s64 *)(q+104) = (((x+width)<<4)+D_001A7350-8) | ((s64)(((y+height)<<4)+D_001A7354-8)<<16) | ((s64)D_001B187C<<32);
    D_001B22A8 += 0x70;
}
