/* functional: high. Reads, writes and calls in retail order; colour arithmetic done in 64-bit as retail does. */
typedef int s32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long u64;

extern void func_002FC560(unsigned int, unsigned long);
extern void func_0027E018(int, int, int, int, int, int, int, int, u64, u64);
extern int D_001B166C;
extern int D_001A89B0[] __attribute__((sda));
extern int D_001B1668 __attribute__((sda));

void func_0027F2A8(int x, int y, u64 style, u8 *text, int length, u64 font, u8 *tab)
{
    int n = 0;

    if (D_001B166C == 0)
        D_001A89B0[0] = (int)style;
    func_002FC560(0x47, 0x33001);
    if (length != 0 && *text != 0) {
        do {
            u32 c = *text;
            if (c - 8 < 8) {
                if (D_001B1668 != 0)
                    style = (style & 0xFF000000) | (D_001A89B0[c - 8] & 0xFFFFFF);
            } else if (((signed char *)tab)[c * 4 + 3] != 0) {
                if ((u8)(c + 0x80) < 0x28) {
                    u8 *e = tab + (c + 0x40) * 4;
                    func_0027E018(x + (signed char)e[3], y + (signed char)e[2], 16, 16, e[0], e[1], 16, 16, style, font);
                }
                c = *text;
                if (c < 0x20) {
                    int g = ((int)(style & 0xFF) + (int)((style >> 8) & 0xFF) + (int)((style >> 16) & 0xFF)) / 3;
                    u8 *e = tab + *text * 4;
                    func_0027E018(x, y + (signed char)e[2], 24, 16, e[0], e[1], 24, 16,
                                  g + ((int)(style & 0xFF000000) + (g << 16) + (g << 8)), font);
                } else if (c > 0x20) {
                    u8 *e = tab + c * 4;
                    func_0027E018(x, y + (signed char)e[2], 16, 16, e[0], e[1], 16, 16, style, font);
                }
                x += ((signed char *)tab)[*text * 4 + 3];
            }
            n++;
            text++;
        } while (n != length && *text != 0);
    }
}
