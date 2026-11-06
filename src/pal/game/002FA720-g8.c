#include "common.h"

/* func_PAL_002FA720, the PAL copy of func_002F97A0: the same C, where the 0x80..0xa7 test is taken
   before the colours are stored, its arm comes first, and the grey arm masks `tint` in place. */
typedef unsigned int Quad_002F9198 __attribute__((mode(TI), aligned(16)));
typedef struct { int state; char pad4[0x24]; char *moby; char pad2C[0x24]; int mode; char pad54[0xC]; int restore; char pad64[0x7C]; Quad_002F9198 saved; } Shop_002F9198;
extern Shop_002F9198 D_0021F240;

/* One font glyph: its texture cell, its top offset and its advance. */
typedef struct { u8 u, v; signed char top, adv; } Glyph_002F97A0;

extern Glyph_002F97A0 D_00263EF0[];
extern u64 func_0027C878(int);
extern float func_00283CE0(int);
extern void func_0027E1A0(float, float, float, float, int, int, int, int, u32 *, u64);

/* Prints up to `limit` characters of `text` from (x, y) at `scale`, in the large font, fading
   each glyph's left and right edges out with their distance from the screen centre (215 on
   the second screen layout, 256 elsewhere, three quarters as fast). Characters 0x80..0xa7
   draw their entry 0x40 later; control characters below 0x20 draw a grey 24-pixel sprite. */
void func_PAL_002FA720(u64 color, u8 *text, int limit, float x, float y, float scale)
{
    u32 colors[4];
    u32 gray[4];
    Glyph_002F97A0 *glyphs;
    Shop_002F9198 *shop = &D_0021F240;
    Glyph_002F97A0 *g;
    u64 texture;
    int count = 0;
    float size;
    float top;
    float dx;
    float dy;
    double d;
    int left;
    int right;
    int shade;
    int tint;
    u32 c;
    u8 *cursor;
    int accented;

    texture = func_0027C878(2);
    size = scale * 16.0f;
    glyphs = D_00263EF0;
    color &= 0xFFFFFF;
    if (limit == 0 || *text == 0)
        return;
    cursor = text;
    do {
        if (glyphs[*cursor].adv != 0) {
            top = func_00283CE0(glyphs[*cursor].top) * scale;
            if (shop->mode == 2) {
                d = 215.0f - x;
                if (d < 0)
                    d = -d;
                left = 0x80 - (int)d;
                d = 215.0f - (x + size);
                if (d < 0)
                    d = -d;
                right = 0x80 - (int)d;
            } else {
                d = 256.0f - x;
                if (d < 0)
                    d = -d;
                left = 0x80 - (int)(d * 0.75);
                d = 256.0f - (x + size);
                if (d < 0)
                    d = -d;
                right = 0x80 - (int)(d * 0.75);
            }
            if (left < 0)
                left = 0;
            c = color;
            if (right < 0)
                right = 0;
            accented = (u8)(*cursor + 0x80) < 0x28;
            left <<= 24;
            right <<= 24;
            colors[0] = left | c;
            colors[1] = right | c;
            colors[2] = left | c;
            colors[3] = right | c;
            if (accented) {
                g = (Glyph_002F97A0 *)((((u8)*cursor + 0x40) << 2) + (int)glyphs);
                dx = func_00283CE0(g->adv) * scale;
                dy = func_00283CE0(g->top) * scale;
                func_0027E1A0(x + dx, y + dy, size, size, g->u, g->v, 16, 16, colors, texture);
            }
            if (*cursor < 0x20) {
                tint = colors[0];
                c = tint;
                shade = (c & 0xFF) + ((c >> 8) & 0xFF) + ((c >> 16) & 0xFF);
                shade /= 3;
                tint &= 0xFF000000;
                tint += shade << 16;
                tint += shade << 8;
                shade += tint;
                gray[0] = shade;
                gray[1] = shade;
                gray[2] = shade;
                gray[3] = shade;
                func_0027E1A0(x, y + top, scale * 24.0f, scale * 16.0f, glyphs[*cursor].u,
                              glyphs[*cursor].v, 24, 16, gray, texture);
            } else if ((u8)*cursor > 0x20) {
                func_0027E1A0(x, y + top, size, size, glyphs[*cursor].u, glyphs[*cursor].v, 16, 16,
                              colors, texture);
            }
            x += func_00283CE0(glyphs[*cursor].adv) * scale;
        }
        count++;
        if (count == limit)
            break;
        cursor++;
    } while (*cursor != 0);
}
