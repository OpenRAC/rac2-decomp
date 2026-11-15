#include "common.h"

extern unsigned char *D_001B22A8 __attribute__((sda));
extern u64 D_001AC7E0[2];
extern u64 D_001AC7F0[2];
extern int D_001A7354 __attribute__((sda));
extern int D_001A7350 __attribute__((sda));

/* Draws a flat colour rectangle on the screen. */
void func_0027DE50(int x0, int x1, int y0, int y1, u64 color)
{
    unsigned char *current, *next;
    const u64 coordinate_mask = 0xFFFFF000000000ULL;
    *(u32 *)(gDmaPacketCursor + 0) = 0x10000005;
    *(u32 *)(gDmaPacketCursor + 4) = 0;
    *(u32 *)(gDmaPacketCursor + 8) = 0;
    *(u32 *)(gDmaPacketCursor + 0xC) = 0x50000005;
    {
        unsigned char *header_base = gDmaPacketCursor;
        unsigned char *header = header_base + 0x10;
        gDmaPacketCursor = header;
        qcopy(header, D_001AC7E0);
        *(s16 *)(header_base + 0x10) = -32767;
    }
    {
        unsigned char *color_base = gDmaPacketCursor;
        unsigned char *color_packet = color_base + 0x10;
        gDmaPacketCursor = color_packet;
        *(u64 *)(color_base + 0x10) = 0x144;
        *(u64 *)(color_packet + 8) = color;
    }
    {
        unsigned char *vertex_base = gDmaPacketCursor;
        unsigned char *vertex_header = vertex_base + 0x10;
        gDmaPacketCursor = vertex_header;
        qcopy(vertex_header, D_001AC7F0);
        *(s16 *)(vertex_base + 0x10) = -32764;
    }
    x0 <<= 4;
    x1 <<= 4;
    y0 <<= 4;
    y1 <<= 4;
    {
        int x = x0 + gScreenOffsetY;
        int y = y0 + gScreenOffsetX;
        current = gDmaPacketCursor;
        next = current + 0x10;
        gDmaPacketCursor = next;
        *(u64 *)(current + 0x10) = (u64)(y - 8) |
                                  ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x0 + gScreenOffsetY;
        int y = y1 + gScreenOffsetX;
        *(u64 *)(next + 8) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x1 + gScreenOffsetY;
        int y = y0 + gScreenOffsetX;
        *(u64 *)(next + 0x10) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x1 + gScreenOffsetY;
        int y = y1 + gScreenOffsetX;
        *(u64 *)(next + 0x18) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    gDmaPacketCursor = gDmaPacketCursor + 0x20;
}
