#include "common.h"
extern short *g_hud_texture_pair_table;
extern u32 *g_hud_group_entries_a;
extern char *g_dma_packet_cursor;
extern char g_hud_gradient_packet[];
extern char *ref_L00_002FA150_00 MACRO_ADDR;
extern int g_screen_offset_x, g_screen_offset_y, g_hud_sprite_color_word;
extern u64 GetFrameTexture(int);
/* Draws a picture on the screen with a different colour at each corner. */
void hud_draw_sprite_gradient(int texture, int x, int y, int width, int height, int *colors)
{
    short *pair = (short *)((texture << 2) + (u32)g_hud_texture_pair_table);
    u8 *entry = (u8 *)((u32)g_hud_group_entries_a + (pair[1] << 3));
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
    qcopy(g_dma_packet_cursor, g_hud_gradient_packet);
    packet = old_cursor + 32;
    ref_L00_002FA150_00 = packet;
    texture_word = GetFrameTexture(texture);
    *(u64 *)packet = texture_word;
    *(u64 *)(packet+8) = 0x15c;
    *(s64 *)(packet+16) = colors[0];
    *(u64 *)(packet+24) = 0;
    *(s64 *)(packet+32) = ((x<<4)+g_screen_offset_x-8) | ((s64)((y<<4)+g_screen_offset_y-8)<<16) | ((s64)g_hud_sprite_color_word<<32);
    *(s64 *)(packet+40) = colors[1];
    *(s64 *)(packet+48) = tex_width<<4;
    *(s64 *)(packet+56) = (((x+width)<<4)+g_screen_offset_x-8) | ((s64)((y<<4)+g_screen_offset_y-8)<<16) | ((s64)g_hud_sprite_color_word<<32);
    *(s64 *)(packet+64) = colors[2];
    *(s64 *)(packet+72) = tex_height<<20;
    *(s64 *)(packet+80) = ((x<<4)+g_screen_offset_x-8) | ((s64)(((y+height)<<4)+g_screen_offset_y-8)<<16) | ((s64)g_hud_sprite_color_word<<32);
    *(s64 *)(packet+88) = colors[3];
    *(s64 *)(packet+96) = (tex_height<<20)+(tex_width<<4);
    *(s64 *)(packet+104) = (((x+width)<<4)+g_screen_offset_x-8) | ((s64)(((y+height)<<4)+g_screen_offset_y-8)<<16) | ((s64)g_hud_sprite_color_word<<32);
    g_dma_packet_cursor += 0x70;
}
