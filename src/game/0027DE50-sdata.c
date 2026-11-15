#include "common.h"

extern unsigned char *D_001B22A8 __attribute__((sda));
extern u64 D_001AC7E0[2];
extern u64 D_001AC7F0[2];
extern int D_001A7354 __attribute__((sda));
extern int D_001A7350 __attribute__((sda));

/* Appends a GS rectangle primitive for the given coordinates and colour to the current packet buffer. */
void func_0027DE50(int x0, int x1, int y0, int y1, u64 color)
{
    unsigned char *current, *next;
    const u64 coordinate_mask = 0xFFFFF000000000ULL;
    *(u32 *)(D_001B22A8 + 0) = 0x10000005;
    *(u32 *)(D_001B22A8 + 4) = 0;
    *(u32 *)(D_001B22A8 + 8) = 0;
    *(u32 *)(D_001B22A8 + 0xC) = 0x50000005;
    {
        unsigned char *header_base = D_001B22A8;
        unsigned char *header = header_base + 0x10;
        D_001B22A8 = header;
        qcopy(header, D_001AC7E0);
        *(s16 *)(header_base + 0x10) = -32767;
    }
    {
        unsigned char *color_base = D_001B22A8;
        unsigned char *color_packet = color_base + 0x10;
        D_001B22A8 = color_packet;
        *(u64 *)(color_base + 0x10) = 0x144;
        *(u64 *)(color_packet + 8) = color;
    }
    {
        unsigned char *vertex_base = D_001B22A8;
        unsigned char *vertex_header = vertex_base + 0x10;
        D_001B22A8 = vertex_header;
        qcopy(vertex_header, D_001AC7F0);
        *(s16 *)(vertex_base + 0x10) = -32764;
    }
    x0 <<= 4;
    x1 <<= 4;
    y0 <<= 4;
    y1 <<= 4;
    {
        int x = x0 + D_001A7354;
        int y = y0 + D_001A7350;
        current = D_001B22A8;
        next = current + 0x10;
        D_001B22A8 = next;
        *(u64 *)(current + 0x10) = (u64)(y - 8) |
                                  ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x0 + D_001A7354;
        int y = y1 + D_001A7350;
        *(u64 *)(next + 8) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x1 + D_001A7354;
        int y = y0 + D_001A7350;
        *(u64 *)(next + 0x10) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x1 + D_001A7354;
        int y = y1 + D_001A7350;
        *(u64 *)(next + 0x18) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    D_001B22A8 = D_001B22A8 + 0x20;
}
