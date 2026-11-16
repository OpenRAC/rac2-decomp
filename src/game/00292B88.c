#include "common.h"

/* RAC1 loaders.c build_indexed_resident_render_packet supplies the fields and
   the packet layout; this game adds the direct-storage arm. */
typedef struct {
    int pixels;
    short width, height, storage, base, first, second;
} Texture_292B88;
extern int log2dim(int value);
extern int g_vram_clut_third MACRO_ADDR;
extern int g_vram_pixel_base MACRO_ADDR;
extern long g_fallback_render_packet[];
extern long D_001B19C8_1[];

/* Fills the four A+D words of a texture's material from its header: a TEX1
   word (the filter and K), the mode word, then TEX0 and the MIP addresses. A
   negative mode has no texture words: -2 and -3 take a fallback table, -1 a
   fixed word and 0. In the direct-storage arm the filter bits are computed
   first and the tex_address constant is ORed in its own statement: that order
   gives the filter its live range and the words their retail registers. */
void build_indexed_resident_render_packet(long *out, Texture_292B88 *texture,
                    int k, int filter, int address, int clamp, int mode)
{
    int width = texture->width >> 6;
    int half_width = texture->width >> 7;
    int log_width, log_height;
    int base, first, second, storage;
    if (width <= 0) width = 1;
    if (half_width <= 0) half_width = 1;
    log_width = log2dim(texture->width);
    log_height = log2dim(texture->height);
    base = texture->base + (g_vram_clut_third >> 8);
    first = texture->first + (g_vram_clut_third >> 8);
    second = texture->second + (g_vram_clut_third >> 8);
    storage = texture->storage;
    if (mode >= 0) {
        if (!storage) {
            int pixels;
            long format, tex, sampler, flags, tex_address, filter_bits, high;
            pixels = texture->pixels;
            pixels = (g_vram_pixel_base + (pixels << 2)) >> 8;
            filter_bits = (long)filter << 6;
            high = ((long)k << 32) | 0x20;
            flags = filter_bits | high;
            sampler = address | ((long)clamp << 2) | ((long)mode << 24);
            format = ((long)log_width << 26) | 0x01b00000;
            tex = pixels | ((long)width << 14);
            tex |= format;
            tex |= (long)log_height << 30;
            tex_address = (long)base << 37;
            tex_address |= 0x400000000L;
            tex |= tex_address;
            *out = flags; out += 2;
            *out = sampler; out += 2;
            tex |= 0x8000000000000000UL;
            *out = tex;
            out[2] = 0x40000400004000L;
        } else {
            long flags = ((long)filter << 6) | 0x20;
            long control = ((long)(storage - 1) << 2) | flags;
            long format, tex, tex_address, other, other_address;
            control |= (long)k << 32;
            *out = control; out += 2;
            *out = address | ((long)clamp << 2) | ((long)mode << 24); out += 2;
            format = ((long)log_width << 26) | 0x01300000;
            tex = (((long)width << 14) | format) | ((long)log_height << 30);
            tex_address = 0x400000000L | ((long)base << 37);
            other = ((long)half_width << 14) | ((long)first << 20);
            other_address = ((long)second << 40) | 0x400000000L;
            other |= other_address;
            tex |= tex_address;
            tex |= 0x8000000000000000UL;
            other |= 0x40000000000000L;
            *out = tex;
            out[2] = other;
        }
    } else if (mode < -1) {
        long *fallback = g_fallback_render_packet;
        if (mode == -3) fallback = D_001B19C8_1;
        {
            long v = (long)filter << 6;
            long u = ((long)k << 32) | 0x20;
            *out = v | u;
        }
        out += 2; *out = 5; out += 2;
        *out = fallback[0];
        out[2] = fallback[2];
    } else {
        {
            long v = (long)filter << 6;
            long u = ((long)k << 32) | 0x20;
            *out = v | u;
        }
        out += 2; *out = 5; out += 2;
        *out = 0x80000004CC007FFBL;
        out[2] = 0;
    }
}
