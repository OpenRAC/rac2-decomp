#include "common.h"
extern short *D_001B1890;
extern u32 *D_001B1894;
extern char *D_001B22A8;
extern char D_001AC830[];
extern char *ref_L00_002FA150_00 MACRO_ADDR;
extern int D_001A7350, D_001A7354, D_001B187C;
extern u64 func_0028E640(int);
/* Draws a picture on the screen with a different colour at each corner. */
void func_0028EA58(int texture, int x, int y, int width, int height, int *colors)
{
    short *pair = (short *)((texture << 2) + (u32)D_001B1890);
    u8 *entry = (u8 *)((u32)D_001B1894 + (pair[1] << 3));
    int texWidth = 1 << entry[6];
    int texHeight = 1 << entry[7];
    char *oldCursor, *packet;
    u64 textureWord;
    *(int *)gDmaPacketCursor = 0x10000008;
    *(int *)(gDmaPacketCursor + 4) = 0;
    *(int *)(gDmaPacketCursor + 8) = 0;
    *(int *)(gDmaPacketCursor + 12) = 0x50000008;
    oldCursor = gDmaPacketCursor;
    gDmaPacketCursor = oldCursor + 16;
    qcopy(gDmaPacketCursor, D_001AC830);
    packet = oldCursor + 32;
    ref_L00_002FA150_00 = packet;
    textureWord = GetFrameTexture(texture);
    *(u64 *)packet = textureWord;
    *(u64 *)(packet+8) = 0x15c;
    *(s64 *)(packet+16) = colors[0];
    *(u64 *)(packet+24) = 0;
    *(s64 *)(packet+32) = ((x<<4)+gScreenOffsetX-8) | ((s64)((y<<4)+gScreenOffsetY-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(packet+40) = colors[1];
    *(s64 *)(packet+48) = texWidth<<4;
    *(s64 *)(packet+56) = (((x+width)<<4)+gScreenOffsetX-8) | ((s64)((y<<4)+gScreenOffsetY-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(packet+64) = colors[2];
    *(s64 *)(packet+72) = texHeight<<20;
    *(s64 *)(packet+80) = ((x<<4)+gScreenOffsetX-8) | ((s64)(((y+height)<<4)+gScreenOffsetY-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(packet+88) = colors[3];
    *(s64 *)(packet+96) = (texHeight<<20)+(texWidth<<4);
    *(s64 *)(packet+104) = (((x+width)<<4)+gScreenOffsetX-8) | ((s64)(((y+height)<<4)+gScreenOffsetY-8)<<16) | ((s64)D_001B187C<<32);
    gDmaPacketCursor += 0x70;
}
