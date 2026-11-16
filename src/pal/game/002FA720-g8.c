#include "common.h"

/* func_PAL_002FA720, the PAL copy of func_002F97A0: the same C, where the 0x80..0xa7 test is taken
   before the colours are stored, its arm comes first, and the grey arm masks `tint` in place. */
typedef unsigned int Quad_002F9198 __attribute__((mode(TI), aligned(16)));
typedef struct { int state; char pad4[0x24]; char *moby; char pad2C[0x24]; int mode; char pad54[0xC]; int restore; char pad64[0x7C]; Quad_002F9198 saved; } Shop_002F9198;
extern Shop_002F9198 g_vendor_menu_state;

/* One font glyph: its texture cell, its top offset and its advance. */
typedef struct { u8 u, v; signed char top, adv; } Glyph_002F97A0;

extern Glyph_002F97A0 g_font_glyphs_medium[];
extern u64 GetEffectTextureDescriptor(int);
extern float IntToFloat(int);
extern void EmitTexturedRectangle(float, float, float, float, int, int, int, int, u32 *, u64);

/* Prints up to `limit` characters of `text` from (x, y) at `scale`, in the large font, fading
   each glyph's left and right edges out with their distance from the screen centre (215 on
   the second screen layout, 256 elsewhere, three quarters as fast). Characters 0x80..0xa7
   draw their entry 0x40 later; control characters below 0x20 draw a grey 24-pixel sprite. */
void draw_large_text_edge_faded_pal(u64 color, u8 *text, int limit, float x, float y, float scale)
{
    u32 colors[4];
    u32 gray[4];
    Glyph_002F97A0 *glyphs;
    Shop_002F9198 *shop = &g_vendor_menu_state;
    Glyph_002F97A0 *accent;
    u64 texture;
    int count = 0;
    float size;
    float top;
    float dx;
    float dy;
    double dist;
    int left;
    int right;
    int shade;
    int tint;
    u32 base_color;
    u8 *cursor;
    int accented;

    texture = GetEffectTextureDescriptor(2);
    size = scale * 16.0f;
    glyphs = g_font_glyphs_medium;
    color &= 0xFFFFFF;
    if (limit == 0 || *text == 0)
        return;
    cursor = text;
    do {
        if (glyphs[*cursor].adv != 0) {
            top = IntToFloat(glyphs[*cursor].top) * scale;
            if (shop->mode == 2) {
                dist = 215.0f - x;
                if (dist < 0)
                    dist = -dist;
                left = 0x80 - (int)dist;
                dist = 215.0f - (x + size);
                if (dist < 0)
                    dist = -dist;
                right = 0x80 - (int)dist;
            } else {
                dist = 256.0f - x;
                if (dist < 0)
                    dist = -dist;
                left = 0x80 - (int)(dist * 0.75);
                dist = 256.0f - (x + size);
                if (dist < 0)
                    dist = -dist;
                right = 0x80 - (int)(dist * 0.75);
            }
            if (left < 0)
                left = 0;
            base_color = color;
            if (right < 0)
                right = 0;
            accented = (u8)(*cursor + 0x80) < 0x28;
            left <<= 24;
            right <<= 24;
            colors[0] = left | base_color;
            colors[1] = right | base_color;
            colors[2] = left | base_color;
            colors[3] = right | base_color;
            if (accented) {
                accent = (Glyph_002F97A0 *)((((u8)*cursor + 0x40) << 2) + (int)glyphs);
                dx = IntToFloat(accent->adv) * scale;
                dy = IntToFloat(accent->top) * scale;
                EmitTexturedRectangle(x + dx, y + dy, size, size, accent->u, accent->v, 16, 16, colors, texture);
            }
            if (*cursor < 0x20) {
                tint = colors[0];
                base_color = tint;
                shade = (base_color & 0xFF) + ((base_color >> 8) & 0xFF) + ((base_color >> 16) & 0xFF);
                shade /= 3;
                tint &= 0xFF000000;
                tint += shade << 16;
                tint += shade << 8;
                shade += tint;
                gray[0] = shade;
                gray[1] = shade;
                gray[2] = shade;
                gray[3] = shade;
                EmitTexturedRectangle(x, y + top, scale * 24.0f, scale * 16.0f, glyphs[*cursor].u,
                              glyphs[*cursor].v, 24, 16, gray, texture);
            } else if ((u8)*cursor > 0x20) {
                EmitTexturedRectangle(x, y + top, size, size, glyphs[*cursor].u, glyphs[*cursor].v, 16, 16,
                              colors, texture);
            }
            x += IntToFloat(glyphs[*cursor].adv) * scale;
        }
        count++;
        if (count == limit)
            break;
        cursor++;
    } while (*cursor != 0);
}
