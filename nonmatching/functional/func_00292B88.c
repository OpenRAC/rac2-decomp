/* functional: high. Near-miss draft that differs from retail in register allocation and scheduling only; fcheck SAME on all captured calls. */
/*
 * Near miss (M19, 2026-10-26): 804/804 bytes, about 23 differing lines.
 * Profile: -O2 -G0 -ffunction-sections. us: 0/28 placements.
 * D_001A72F4 and D_001A7304 are MACRO_ADDR (retail's lui/lw share one register).
 * Residual: $s3/$s4 swapped between filter and half_width (no statement order moves it),
 * and the GS words of the storage==0 arm scheduled differently. Queued on the permuter.
 */
typedef struct {
    int pixels;
    short width, height, storage, base, first, second;
} Texture_292B88;
extern int func_00282A18(int value);
#define MACRO_ADDR __attribute__((section(".sdata")))
extern int D_001A72F4 MACRO_ADDR;
extern int D_001A7304 MACRO_ADDR;
extern long D_001B19B0[];
extern long D_001B19C8[];

void func_00292B88(long *out, Texture_292B88 *texture,
                    int k, int filter, int address, int clamp, int mode)
{
    int width = texture->width >> 6;
    int half_width = texture->width >> 7;
    int log_width, log_height;
    int base, first, second, storage;
    if (width <= 0) width = 1;
    if (half_width <= 0) half_width = 1;
    log_width = func_00282A18(texture->width);
    log_height = func_00282A18(texture->height);
    base = texture->base + (D_001A72F4 >> 8);
    first = texture->first + (D_001A72F4 >> 8);
    second = texture->second + (D_001A72F4 >> 8);
    storage = texture->storage;
    if (mode >= 0) {
        if (!storage) {
            int pixels = ((texture->pixels << 2) + D_001A7304) >> 8;
            long format = ((long)log_width << 26) | 0x01b00000;
            long tex = pixels | ((long)width << 14);
            long flags = ((long)k << 32) | 0x20;
            long sampler = address | ((long)clamp << 2);
            tex |= format;
            sampler |= (long)mode << 24;
            flags |= (long)filter << 6;
            tex |= (long)log_height << 30;
            tex |= ((long)base << 37) | 0x400000000L;
            tex |= 0x8000000000000000UL;
            *out = flags; out += 2;
            *out = sampler; out += 2;
            *out = tex;
            out[2] = 0x40000400004000L;
        } else {
            long flags = ((long)filter << 6) | 0x20;
            long tex, other, sampler;
            flags |= (long)(storage - 1) << 2;
            flags |= (long)k << 32;
            tex = ((long)width << 14) | (((long)log_width << 26) | 0x01300000);
            sampler = address | ((long)clamp << 2);
            sampler |= (long)mode << 24;
            other = ((long)half_width << 14) | ((long)first << 20);
            other |= ((long)second << 40) | 0x400000000L;
            tex |= (long)log_height << 30;
            tex |= ((long)base << 37) | 0x400000000L;
            tex |= 0x8000000000000000UL;
            other |= 0x40000000000000L;
            *out = flags; out += 2;
            *out = sampler; out += 2;
            *out = tex;
            out[2] = other;
        }
    } else if (mode < -1) {
        long *fallback = D_001B19B0;
        if (mode == -3) fallback = D_001B19C8;
        out[0] = ((long)filter << 6) | (((long)k << 32) | 0x20);
        out += 2; *out = 5; out += 2;
        *out = fallback[0];
        out[2] = fallback[2];
    } else {
        out[0] = ((long)filter << 6) | (((long)k << 32) | 0x20);
        out += 2; *out = 5; out += 2;
        *out = 0x80000004CC007FFBL;
        out[2] = 0;
    }
}
