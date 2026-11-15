#include "common.h"
extern short *D_001B1890;
extern u32 *D_001B1894;
extern char *g_dma_packet_cursor;
extern char D_001AC830[];
extern char *ref_L00_002FA150_00 MACRO_ADDR;
extern int g_screen_offset_x, g_screen_offset_y, D_001B187C;
extern u64 GetFrameTexture(int);
/* Draws a picture on the screen with a different colour at each corner. */
void hud_draw_sprite_gradient(int texture, int x, int y, int width, int height, int *colors)
{
    short *pair = (short *)((texture << 2) + (u32)D_001B1890);
    u8 *entry = (u8 *)((u32)D_001B1894 + (pair[1] << 3));
    int tex_width = 1 << entry[6];
    int tex_height = 1 << entry[7];
    char *old_cursor, *packet;
    u64 texture_word;
    *(int *)g_dma_packet_cursor = 0x10000008;
    *(int *)(g_dma_packet_cursor + 4) = 0;
    *(int *)(g_dma_packet_cursor + 8) = 0;
    *(int *)(g_dma_packet_cursor + 12) = 0x50000008;
    old_cursor = g_dma_packet_cursor;
    g_dma_packet_cursor = old_cursor + 16;
    qcopy(g_dma_packet_cursor, D_001AC830);
    packet = old_cursor + 32;
    ref_L00_002FA150_00 = packet;
    texture_word = GetFrameTexture(texture);
    *(u64 *)packet = texture_word;
    *(u64 *)(packet+8) = 0x15c;
    *(s64 *)(packet+16) = colors[0];
    *(u64 *)(packet+24) = 0;
    *(s64 *)(packet+32) = ((x<<4)+g_screen_offset_x-8) | ((s64)((y<<4)+g_screen_offset_y-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(packet+40) = colors[1];
    *(s64 *)(packet+48) = tex_width<<4;
    *(s64 *)(packet+56) = (((x+width)<<4)+g_screen_offset_x-8) | ((s64)((y<<4)+g_screen_offset_y-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(packet+64) = colors[2];
    *(s64 *)(packet+72) = tex_height<<20;
    *(s64 *)(packet+80) = ((x<<4)+g_screen_offset_x-8) | ((s64)(((y+height)<<4)+g_screen_offset_y-8)<<16) | ((s64)D_001B187C<<32);
    *(s64 *)(packet+88) = colors[3];
    *(s64 *)(packet+96) = (tex_height<<20)+(tex_width<<4);
    *(s64 *)(packet+104) = (((x+width)<<4)+g_screen_offset_x-8) | ((s64)(((y+height)<<4)+g_screen_offset_y-8)<<16) | ((s64)D_001B187C<<32);
    g_dma_packet_cursor += 0x70;
}
