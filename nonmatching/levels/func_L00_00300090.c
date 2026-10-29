/* Retained bounded near miss, 2026-10-28: 736/744 bytes, six forms.
 * Ordinary C already emits all three retailSQ/LQ scalar spill pairs at10/20/30
 * across the logarithm calls. Do not introduce fakeTI scalar locals for these.
 * Real packet cursor advances restore the outputpointer role; snapshot LOD
 * distance, count-controlled relocation and packet-word staging improve the
 * body. Initial LOD float scheduling and several descriptor/packedfield GPR
 * roles still differ. -fno-strict-aliasing and -fno-regmove tie and are removed.
 * Reopen with a truthful LOD snapshot/packedfield expression lifetime witness.
 * Canonical no-argument void LOD setter and int logarithm helper match current
 * definitions. Full header16, row64, descriptor16 and command80 extents are
 * preserved; input metadata is captured before low64-bit word overwrites.
 * The full file-backed command retains its upper halves; no shortened packet
 * or fabricated zero stores represent those existing initialized bytes.
 */
#include "common.h"

struct FragmentHeader { int relative, count; float distance; int pages; };
struct FragmentRow {
    unsigned char unknown00[0x10];
    union { int relative; unsigned char *pointer; } commands;
    unsigned char unknown14[8]; unsigned short header_size;
    unsigned char unknown1e[10]; unsigned char count, unknown29[23];
};
struct TextureDescriptor { int unknown; short width, height, levels, page, block_a, block_b; };
extern struct FragmentRow *D_L00_001B24D0 __attribute__((sda));
/* Retail stores this pointer through GP but reads its ordinary address. */
extern struct FragmentRow *D_L00_001B24D0_gp SDATA(D_L00_001B24D0);
extern int D_L00_001B24D4 __attribute__((sda));
extern float D_L00_001B24DC __attribute__((sda));
extern float D_L00_001B24E0[3];
extern int D_L00_001C9358;
extern int D_001A72F4 __attribute__((sda));
extern void func_002EF080(void);
extern int func_00282A18(int);

/* Relocate64-byte rows, then patch the five low64-bit GS words of each real
 *80-byte command record. Existing upper halves remain loaded file data.
 * The texture descriptor is16 bytes, and each command's metadata is read
 * before its first overwrite. All packed shifts use unsigned64-bit values. */
void func_L00_00300090(struct FragmentHeader *header, struct TextureDescriptor *textures)
{
    struct FragmentRow *rows;
    int i, j;
    float distance;
    D_L00_001B24D4 = header->count;
    D_L00_001B24DC = header->distance;
    distance = D_L00_001B24DC;
    D_L00_001B24E0[0] = distance * 6.0f;
    D_L00_001C9358 = header->pages;
    D_L00_001B24E0[2] = distance + distance;
    D_L00_001B24E0[1] = distance * 4.0f;
    func_002EF080();
    rows = (struct FragmentRow *)((char *)header + header->relative);
    D_L00_001B24D0_gp = rows;
    i = D_L00_001B24D4;
    if (i > 0) {
        struct FragmentRow *row = rows;
        do {
            row->commands.pointer = (unsigned char *)rows + row->commands.relative;
            ++row;
        } while (--i);
    }
    for (i = 0; i < D_L00_001B24D4; ++i) {
        for (j = 0; j < D_L00_001B24D0[i].count; ++j) {
            struct FragmentRow *row = &D_L00_001B24D0[i];
            unsigned char *packet = row->commands.pointer + row->header_size + j*80;
            int index = *(int *)packet;
            struct TextureDescriptor *texture = &textures[index];
            int field10 = *(int *)(packet+0x10), field14 = *(int *)(packet+0x14);
            int field20 = *(int *)(packet+0x20), field24 = *(int *)(packet+0x24);
            int width = texture->width;
            int height_blocks = width >> 7, width_blocks = width >> 6;
            int log_width, log_height, page;
            u64 word0, word1, word2, word3;
            if (height_blocks <= 0) height_blocks = 1;
            if (width_blocks <= 0) width_blocks = 1;
            log_width = func_00282A18(width);
            log_height = func_00282A18(texture->height);
            page = D_001A72F4 >> 8;
            word0 = (u64)width_blocks << 14;
            word0 |= ((u64)log_width << 26) | 0x1300000ULL;
            word0 |= (u64)log_height << 30;
            word0 |= ((u64)(texture->page + page) << 37) | 0x400000000ULL;
            word0 |= 0x8000000000000000ULL;
            word1 = ((u64)field14 << 6) | 0x20;
            *(u64 *)packet = word0;
            packet += 0x10;
            word1 |= (u64)(texture->levels - 1) << 2;
            word1 |= (u64)field10 << 32;
            *(u64 *)packet = word1;
            packet += 0x10;
            word2 = (u64)field20 | ((u64)field24 << 2) | ((u64)index << 24);
            word3 = (u64)height_blocks << 14;
            word3 |= (u64)(texture->block_a + page) << 20;
            word3 |= ((u64)(texture->block_b + page) << 40) | 0x400000000ULL;
            *(u64 *)packet = word2;
            packet += 0x10;
            word3 |= 0x40000000000000ULL;
            *(u64 *)packet = word3;
            *(u64 *)(packet+0x10) = 0;
        }
    }
}
