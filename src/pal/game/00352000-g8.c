#include "include_asm.h"
#include "names.h"
typedef unsigned long long u64;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned char u8;
extern int g_vram_display_address;
extern int g_movie_buffer_base;
extern void BuildFrameDmaChain(void *, int);

/* FMV GS packet builder: one 0x40-byte header record, then a 0x60-byte record per
   (row, column), then the closing A_B word pair at the end of the run. */
void mpeg_build_frame_packet_pal(void *packet, int texture_addr, int height, int width, int buffer_index)
{
    u8 *cursor = (u8 *)packet;
    int rows = height >> 4;
    int cols = width >> 4;
    int row, col;
    u64 tag_00, tag_10, tag_18, tag_28, tag_38, tag_40;
    u32 buffer_offset, buffer_addr;

    *(u64 *)(cursor + 0x00) = 0x10000003;
    *(u64 *)(cursor + 0x08) = 0;
    *(u64 *)(cursor + 0x10) = 0x1000000000000002ULL;
    *(u64 *)(cursor + 0x18) = 0xE;
    *(u64 *)(cursor + 0x20) = ((ll)g_vram_display_address >> 8) << 32 | 0x8000000000000LL;
    *(u64 *)(cursor + 0x28) = 0x50;
    *(u64 *)(cursor + 0x30) = 0x1000000010ULL;
    *(u64 *)(cursor + 0x38) = 0x52;

    cursor += 0x40;
    for (row = 0; row < rows; row++) {
        for (col = 0; col < cols; col++) {
            tag_00 = 0x10000004;
            tag_10 = 0x1000000000000002ULL;
            tag_18 = 0xE;
            tag_28 = 0x51;
            tag_38 = 0x53;
            tag_40 = 0x0800000000000040ULL;
            *(u64 *)(cursor + 0x00) = tag_00;
            *(u64 *)(cursor + 0x08) = 0;
            *(u64 *)(cursor + 0x10) = tag_10;
            *(u64 *)(cursor + 0x18) = tag_18;
            *(u64 *)(cursor + 0x20) = (((u64)(row << 4)) << 32) | (((u64)(col << 4)) << 48);
            *(u64 *)(cursor + 0x28) = tag_28;
            *(u64 *)(cursor + 0x30) = 0;
            *(u64 *)(cursor + 0x38) = tag_38;
            *(u64 *)(cursor + 0x40) = tag_40;
            *(u64 *)(cursor + 0x48) = 0;
            *(u32 *)(cursor + 0x50) = 0x30000040;
            *(u32 *)(cursor + 0x54) = texture_addr & 0x0FFFFFFF;
            *(u64 *)(cursor + 0x58) = 0;
            texture_addr += 0x400;
            cursor += 0x60;
        }
    }

    *(u32 *)(cursor + 0x00) = 0x20000000;
    buffer_offset = (buffer_index << 14) + 0x1C81C0;
    buffer_addr = g_movie_buffer_base + buffer_offset;
    *(u32 *)(cursor + 0x0C) = 0;
    *(u32 *)(cursor + 0x08) = 0;
    *(u32 *)(cursor + 0x04) = buffer_addr;
    BuildFrameDmaChain((void *)(u32)(g_movie_buffer_base + buffer_offset), 1);
}
