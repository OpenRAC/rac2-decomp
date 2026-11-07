/* func_US2_0027CED8, the USA v2.00 copy of func_0027C878: the same C, where the entry has u8 width and
 * height at 0xC/0xD and an s16 format at 0xE, and the allocator stops past 0x3FF000. Measured notes:
 * - base is reused as the second upload pointer. That makes it global, so local-alloc serves height_bits
 *   before texel and retail's a2/a3 follow; base takes texel's register by preference, and count falls to t0.
 * - Assigning that pointer inside the store computes the destination address first (needed for v0/v1 there).
 * - (unsigned short)(w + h): zero_extend:HI loads that CSE does not merge with the SI load of shift.
 * - alpha_bit and sign_bit are set before the test: update_equiv_regs sinks them to their single uses.
 * - final is a fresh local live out of the block, so its `or` issues before the lui of the limit. */

#include "include_asm.h"

typedef unsigned long TextureBits;
typedef struct {
    TextureBits bits;
    unsigned short first_offset;
    unsigned short second_offset;
    unsigned char width_shift;
    unsigned char height_shift;
    short format;
} TextureEntry;


extern int D_001A72D0;
extern int D_001A72DC;
extern int D_001A72E0;
extern int D_001A72D8 __attribute__((sda));
extern TextureBits ref_0027C878_00 __attribute__((sda));
extern TextureBits ref_0027C878_01 __attribute__((sda));
extern int ref_0027C878_02 __attribute__((sda));
extern char *ref_0027C878_03;
extern char D_00138AD0[];
extern char D_00138DC0[];
extern TextureEntry ref_0027C878_04[];
extern int ref_0027C878_05;
extern char *ref_0027C878_06;
extern char ref_0027C878_07[];

/* Incremental descriptor construction follows RAC1 draw.c (GPL-3.0).
 * Resolve a cached texture descriptor, allocating VRAM and queuing its upload
 * when necessary. Negative identifiers select the render-target descriptors. */
TextureBits func_US2_0027CED8(int id)
{
    if (id < 0) {
        if (id == -5)
            return (D_001A72E0 >> 8) | 0x27020000UL | (0xC800UL << 19);
        if (id == -8) {
            TextureBits frame = (D_001A72DC >> 8) | 0x25B20000UL;
            TextureBits palette = ((TextureBits)ref_0027C878_02 << 37) | (0xC800UL << 19);
            return frame | palette | (0x8000UL << 46);
        }
        if (id == -7)
            return (D_001A72D8 >> 8) | 0x24020000UL | (0xC800UL << 19);
        if (id == -6)
            return (D_001A72DC >> 8) | 0x24020000UL | (0xC800UL << 19);
        if ((unsigned int)(id + 2) < 2) {
            int base;
            TextureBits result;
            TextureBits frame;
            if (ref_0027C878_00 != 0)
                return ref_0027C878_00;
            base = (D_001A72D0 + 0x1FFF) & -0x2000;
            D_001A72D0 = base + 0x20000;
            frame = (base >> 13) | 0x02040000;
            result = (base >> 8) | 0x20210000UL | (0xC000UL << 19);
            *(int *)(ref_0027C878_03 + 0) = 0x10000003;
            *(int *)(ref_0027C878_03 + 4) = 0;
            *(int *)(ref_0027C878_03 + 8) = 0;
            *(int *)(ref_0027C878_03 + 12) = 0x50000003;
            *(int *)(ref_0027C878_03 + 16) = 0x8001;
            *(int *)(ref_0027C878_03 + 20) = 0x20000000;
            *(int *)(ref_0027C878_03 + 24) = 0xEE;
            *(int *)(ref_0027C878_03 + 28) = 0;
            *(TextureBits *)(ref_0027C878_03 + 32) = frame;
            *(int *)(ref_0027C878_03 + 40) = 0x4D;
            *(int *)(ref_0027C878_03 + 44) = 0;
            *(TextureBits *)(ref_0027C878_03 + 48) =
                (D_001A72DC >> 8) | 0x24020000UL | (0xC800UL << 19);
            *(int *)(ref_0027C878_03 + 56) = 7;
            *(int *)(ref_0027C878_03 + 60) = 0;
            *(int *)(ref_0027C878_03 + 64) = 0x3000002F;
            *(char **)(ref_0027C878_03 + 68) = D_00138AD0;
            *(int *)(ref_0027C878_03 + 72) = 0;
            *(int *)(ref_0027C878_03 + 76) = 0x5000002F;
            ref_0027C878_00 = result;
            ref_0027C878_03 += 80;
            return result;
        }
        if ((unsigned int)(id + 4) < 2) {
            int base;
            TextureBits result;
            TextureBits frame;
            if (ref_0027C878_01 != 0)
                return ref_0027C878_01;
            base = (D_001A72D0 + 0x1FFF) & -0x2000;
            D_001A72D0 = base + 0x2000;
            frame = (base >> 13) | 0x02010000;
            result = (base >> 8) | 0x18204000UL | (0xB000UL << 19);
            *(int *)(ref_0027C878_03 + 0) = 0x10000003;
            *(int *)(ref_0027C878_03 + 4) = 0;
            *(int *)(ref_0027C878_03 + 8) = 0;
            *(int *)(ref_0027C878_03 + 12) = 0x50000003;
            *(int *)(ref_0027C878_03 + 16) = 0x8002;
            *(int *)(ref_0027C878_03 + 20) = 0x10000000;
            *(int *)(ref_0027C878_03 + 24) = 0xEE;
            *(int *)(ref_0027C878_03 + 28) = 0;
            *(TextureBits *)(ref_0027C878_03 + 32) = frame;
            *(int *)(ref_0027C878_03 + 40) = 0x4D;
            *(int *)(ref_0027C878_03 + 44) = 0;
            *(TextureBits *)(ref_0027C878_03 + 48) =
                (D_001A72DC >> 8) | 0x24020000UL | (0xC800UL << 19);
            *(int *)(ref_0027C878_03 + 56) = 7;
            *(int *)(ref_0027C878_03 + 60) = 0;
            *(int *)(ref_0027C878_03 + 64) = 0x3000002F;
            *(char **)(ref_0027C878_03 + 68) = D_00138DC0;
            *(int *)(ref_0027C878_03 + 72) = 0;
            *(int *)(ref_0027C878_03 + 76) = 0x5000002F;
            ref_0027C878_01 = result;
            ref_0027C878_03 += 80;
            return result;
        }
    } else {
        TextureEntry *entry = &ref_0027C878_04[id];
        long alpha_bit = (TextureBits)1 << 34;
        long sign_bit = -9223372036854775807L - 1;
        if (entry->bits == 0) {
            int base = D_001A72D0;
            int shift = entry->width_shift - 6;
            int palette, texture, count, texel;
            long bits, final, width_bits, height_bits, palette_bits;
            if (shift < 0)
                shift = 0;
            palette = base >> 8;
            texel = base + 0x400;
            texture = texel >> 8;
            texel += 1 << (unsigned short)(entry->width_shift + entry->height_shift);
            D_001A72D0 = texel;
            bits = ((TextureBits)(1 << shift) << 14);
            bits |= texture;
            bits |= (long)entry->format << 20;
            width_bits = entry->width_shift;
            width_bits <<= 26;
            bits |= width_bits;
            height_bits = (TextureBits)entry->height_shift << 30;
            palette_bits = (TextureBits)palette << 37;
            palette_bits |= alpha_bit;
            bits |= height_bits;
            bits |= palette_bits;
            final = bits | sign_bit;
            entry->bits = final;
            if (texel > 0x3FF000)
                return final;
            count = ref_0027C878_05;
            if (count < 64) {
                char *upload = ref_0027C878_07 + (count << 4);
                *(unsigned int *)(upload + 0) = (unsigned int)(ref_0027C878_06 + (entry->second_offset << 4));
                *(short *)(upload + 6) = palette;
                *(short *)(upload + 4) = 0;
                *(unsigned int *)(ref_0027C878_07 + (count << 4) + 8) = base = (int)(ref_0027C878_06 + (entry->first_offset << 4));
                *(unsigned char *)(upload + 12) = entry->width_shift;
                *(unsigned char *)(upload + 13) = entry->height_shift;
                *(short *)(upload + 14) = texture;
                ref_0027C878_05 = count + 1;
            }
        }
    }
    return ref_0027C878_04[id].bits;
}
