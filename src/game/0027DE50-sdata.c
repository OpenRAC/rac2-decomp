#include "common.h"

extern unsigned char *g_dma_packet_cursor __attribute__((sda));
extern u64 g_rect_header_packet[2];
extern u64 g_rect_vertex_header_packet[2];
extern int g_screen_offset_y __attribute__((sda));
extern int g_screen_offset_x __attribute__((sda));

/* Draws a flat colour rectangle on the screen. */
void gfx_draw_colored_rectangle(int x0, int x1, int y0, int y1, u64 color)
{
    unsigned char *current, *next;
    const u64 coordinate_mask = 0xFFFFF000000000ULL;
    *(u32 *)(g_dma_packet_cursor + 0) = 0x10000005;
    *(u32 *)(g_dma_packet_cursor + 4) = 0;
    *(u32 *)(g_dma_packet_cursor + 8) = 0;
    *(u32 *)(g_dma_packet_cursor + 0xC) = 0x50000005;
    {
        unsigned char *header_base = g_dma_packet_cursor;
        unsigned char *header = header_base + 0x10;
        g_dma_packet_cursor = header;
        qcopy(header, g_rect_header_packet);
        *(s16 *)(header_base + 0x10) = -32767;
    }
    {
        unsigned char *color_base = g_dma_packet_cursor;
        unsigned char *color_packet = color_base + 0x10;
        g_dma_packet_cursor = color_packet;
        *(u64 *)(color_base + 0x10) = 0x144;
        *(u64 *)(color_packet + 8) = color;
    }
    {
        unsigned char *vertex_base = g_dma_packet_cursor;
        unsigned char *vertex_header = vertex_base + 0x10;
        g_dma_packet_cursor = vertex_header;
        qcopy(vertex_header, g_rect_vertex_header_packet);
        *(s16 *)(vertex_base + 0x10) = -32764;
    }
    x0 <<= 4;
    x1 <<= 4;
    y0 <<= 4;
    y1 <<= 4;
    {
        int x = x0 + g_screen_offset_y;
        int y = y0 + g_screen_offset_x;
        current = g_dma_packet_cursor;
        next = current + 0x10;
        g_dma_packet_cursor = next;
        *(u64 *)(current + 0x10) = (u64)(y - 8) |
                                  ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x0 + g_screen_offset_y;
        int y = y1 + g_screen_offset_x;
        *(u64 *)(next + 8) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x1 + g_screen_offset_y;
        int y = y0 + g_screen_offset_x;
        *(u64 *)(next + 0x10) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    {
        int x = x1 + g_screen_offset_y;
        int y = y1 + g_screen_offset_x;
        *(u64 *)(next + 0x18) = (u64)(y - 8) | ((u64)(x - 8) << 16) | coordinate_mask;
    }
    g_dma_packet_cursor = g_dma_packet_cursor + 0x20;
}
