/* functional: high. Text/glyph drawing loop; the near-miss draft below differs from retail only in how often the control character is reloaded, which is a compiler detail. */
/* Near miss, NOT MATCHING and never linked (M36, 26 October 2026).
   Profile: -O2 -G32 -Wa,-G32 -ffunction-sections. us 0/28 (boot + 27 levels); us2/pal absent.
   The globals now take retail's forms: the palette is a 32-byte sda table (D_001A89B0[8], so
   `sw -0x6640($gp)` and `addiu a1, $gp, -0x6640` as retail), D_001B166C an incomplete array read
   [0] (retail lui/lw), D_001B1668 sda. 792/808 bytes at that point (the earlier -G0 draft was 804).
   Left: retail reloads the control character (lbu 0($s1)) at the loop top, in the palette arm,
   in the glyph arm and at the loop test; this C loads it once and keeps it in $a0. text[i]
   indexing instead of a walking pointer is neutral. Reopen with a source form whose character
   reads are distinct expressions to gcse.
*/

typedef unsigned char u8;
typedef unsigned long u64;
/* Font metrics are four bytes per glyph: atlas u/v, vertical offset, advance. */
extern int D_001B166C[];
extern int D_001B1668 __attribute__((sda));
extern int D_001A89B0[8] __attribute__((sda));
extern float func_00283CE0(int);
extern void func_0027E1A0(int u, int v, int width, int height,
                         unsigned int *colors, u64 texture,
                         float x, float y, float draw_width, float draw_height);

void func_0027F640(u64 color, u8 *text, int length, u64 texture, u8 *metrics,
                   float x, float y, float scale)
{
    unsigned int colors[4];
    float height, offset;
    int i;
    u8 *p;
    if (D_001B166C[0] == 0)
        D_001A89B0[0] = (int)color;
    i = 0;
    height = scale * 16.0f;
    if (length != 0 && text[0] != 0) {
        p = text;
        do {
            if ((unsigned int)(p[0] - 8) < 8) {
                if (D_001B1668 != 0) {
                    color &= 0xFF000000UL;
                    color |= D_001A89B0[p[0] - 8] & 0xFFFFFF;
                }
                goto next_character;
            }
            if (((signed char *)metrics)[p[0] * 4 + 3] != 0) {
                offset = func_00283CE0(((signed char *)metrics)[p[0] * 4 + 2]) * scale;
                if ((u8)(p[0] + 128) < 40) {
                    u8 *accent = &metrics[(p[0] + 64) * 4];
                    float dx = func_00283CE0(((signed char *)accent)[3]) * scale;
                    float dy = func_00283CE0(((signed char *)accent)[2]) * scale;
                    colors[2] = colors[1] = colors[0] = colors[3] = (int)color;
                    func_0027E1A0(accent[0], accent[1], 16, 16, colors, texture,
                                  x + dx, y + dy, height, height);
                }
                if (p[0] < 32) {
                    u64 sum = (color & 255) + ((color >> 8) & 255) + ((color >> 16) & 255);
                    int gray = (int)sum / 3;
                    int shade = (int)(color & 0xFF000000UL) + (gray << 16) + (gray << 8) + gray;
                    colors[2] = colors[1] = colors[0] = colors[3] = shade;
                    func_0027E1A0(metrics[p[0] * 4], metrics[p[0] * 4 + 1],
                                  24, 16, colors, texture,
                                  x, y + offset, scale * 24.0f, scale * 16.0f);
                } else if (p[0] > 32) {
                    colors[2] = colors[1] = colors[0] = colors[3] = (int)color;
                    func_0027E1A0(metrics[p[0] * 4], metrics[p[0] * 4 + 1],
                                  16, 16, colors, texture,
                                  x, y + offset, height, height);
                }
                x += func_00283CE0(((signed char *)metrics)[p[0] * 4 + 3]) * scale;
            }
next_character:
            i++;
            p++;
            if (i == length)
                break;
        } while (p[0] != 0);
    }
}
