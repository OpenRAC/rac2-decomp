#include "include_asm.h"
typedef unsigned char u8;
typedef unsigned long u64;
typedef int s32;
extern void func_002FC560(unsigned int,unsigned long);
/* Adapted from RAC1 draw.c func_001F6668_r (GPL-3.0), the FontPrint counterpart. */
struct Glyph_F6668 { u8 u,v; signed char top,adv; };
extern int D_001B166C;
extern int D_001B1668 __attribute__((sda));
extern int D_001A89B0[8] __attribute__((sda));
extern float func_00283CE0(int);
extern void func_0027E1A0(float x, float y, float draw_width, float draw_height,
                         int u, int v, int width, int height,
                         unsigned int *colors, u64 texture);

/* func_PAL_0027FB48, the PAL copy of func_0027F640: the same C, with the func_002FC560 call that
   USA's func_0027F2A8 makes before its loop. */
void func_PAL_0027FB48(float x, float y, u64 color, u8 *text, s32 character_limit, float scale,
                   u64 texture, u8 *metrics) {
    struct Glyph_F6668 *glyphs = (struct Glyph_F6668 *)metrics;
    unsigned int colors[4];
    s32 character_count;
    u8 *cursor;
    struct Glyph_F6668 *overlay_glyph;
    float height, offset, dx, dy;

    if (D_001B166C == 0) {
        D_001A89B0[0] = color;
    }
    func_002FC560(0x47, 0x33001);
    character_count = 0;
    height = scale * 16.0f;
    if (character_limit == 0 || *text == 0) {
        return;
    }
    cursor = text;
    do {
        if ((u8)(*cursor - 8) < 8) {
            if (D_001B1668 != 0) {
                color &= 0xFF000000;
                color |= D_001A89B0[*cursor - 8] & 0xFFFFFF;
            }
        } else {
            if (glyphs[*cursor].adv != 0) {
                offset = func_00283CE0(glyphs[*cursor].top) * scale;
                if ((u8)(*cursor + 0x80) < 0x28) {
                    overlay_glyph = (struct Glyph_F6668 *)(((*cursor + 0x40) << 2) + (s32)glyphs);
                    dx = func_00283CE0(overlay_glyph->adv) * scale;
                    dy = func_00283CE0(overlay_glyph->top) * scale;
                    colors[0] = color;
                    colors[1] = color;
                    colors[2] = color;
                    colors[3] = color;
                    func_0027E1A0(x + dx, y + dy, height, height,
                                  overlay_glyph->u, overlay_glyph->v, 16, 16, colors, texture);
                }
                if (*cursor < 0x20) {
                    s32 gray_value = (color & 0xFF) + ((color >> 8) & 0xFF) + ((color >> 16) & 0xFF);
                    s32 gray_color;
                    gray_value /= 3;
                    gray_color = (s32)(color & 0xFF000000);
                    gray_color += gray_value << 16;
                    gray_color += gray_value << 8;
                    gray_value += gray_color;
                    colors[0] = gray_value;
                    colors[1] = gray_value;
                    colors[2] = gray_value;
                    colors[3] = gray_value;
                    func_0027E1A0(x, y + offset, scale * 24.0f, scale * 16.0f,
                                  glyphs[*cursor].u, glyphs[*cursor].v, 24, 16, colors, texture);
                } else if (*cursor > 0x20) {
                    colors[0] = color;
                    colors[1] = color;
                    colors[2] = color;
                    colors[3] = color;
                    func_0027E1A0(x, y + offset, height, height,
                                  glyphs[*cursor].u, glyphs[*cursor].v, 16, 16, colors, texture);
                }
                x += func_00283CE0(glyphs[*cursor].adv) * scale;
            }
        }
        character_count++;
        if (character_count == character_limit) {
            break;
        }
        cursor++;
    } while (*cursor != 0);
}
