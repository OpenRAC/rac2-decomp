/* functional: high. From the near miss, read against the assembly: same reads, calls (with retail's soft-double distance maths as C doubles) and draws in the same order; the glyph entry 0x40 later is indexed instead of formed from a 32-bit pointer sum. */

/* One font glyph: its texture cell, its top offset and its advance. */
typedef struct { unsigned char u, v; signed char top, adv; } Glyph_002F97A0;

extern Glyph_002F97A0 D_00263EF0[];
extern char D_0021F240[];          /* +0x50: the screen layout */
extern unsigned long func_0027C878(int);
extern float func_00283CE0(int);
extern void func_0027E1A0(float, float, float, float, int, int, int, int, unsigned int *, unsigned long);

/* Prints up to `limit` characters of `text` from (x, y) at `scale`, in the large font, fading
   each glyph's left and right edges out with their distance from the screen centre (215 on
   the second screen layout, 256 elsewhere, three quarters as fast). Characters 0x80..0xa7
   draw their entry 0x40 later; control characters below 0x20 draw a grey 24-pixel sprite. */
void func_002F97A0(unsigned long color, unsigned char *text, int limit, float x, float y, float scale)
{
    unsigned int colors[4];
    unsigned int gray[4];
    Glyph_002F97A0 *glyphs;
    Glyph_002F97A0 *g;
    unsigned long texture;
    int count = 0;
    float size;
    float top;
    float dx;
    float dy;
    double d;
    int left;
    int right;
    int shade;
    unsigned int tint;
    unsigned char *cursor;
    unsigned int c;

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
            if (*(int *)(D_0021F240 + 80) == 2) {
                d = (double)(215.0f - x);
                if (d < 0)
                    d = 0 - d;
                left = 128 - (int)d;
                d = (double)(215.0f - (x + size));
                if (d < 0)
                    d = 0 - d;
                right = 128 - (int)d;
            } else {
                d = (double)(256.0f - x);
                if (d < 0)
                    d = 0 - d;
                left = 128 - (int)(d * 0.75);
                d = (double)(256.0f - (x + size));
                if (d < 0)
                    d = 0 - d;
                right = 128 - (int)(d * 0.75);
            }
            if (left < 0)
                left = 0;
            if (right < 0)
                right = 0;
            c = (unsigned int)color;
            colors[3] = (unsigned int)right << 24 | c;
            colors[0] = (unsigned int)left << 24 | c;
            colors[1] = (unsigned int)right << 24 | c;
            colors[2] = (unsigned int)left << 24 | c;
            if (*cursor < 0x20) {
                c = colors[0];
                shade = (int)((c & 0xFF) + ((c >> 8) & 0xFF) + ((c >> 16) & 0xFF)) / 3;
                tint = c & 0xFF000000u;
                tint += (unsigned int)shade << 16;
                tint += (unsigned int)shade << 8;
                tint += (unsigned int)shade;
                gray[3] = tint;
                gray[0] = tint;
                gray[1] = tint;
                gray[2] = tint;
                func_0027E1A0(x, y + top, scale * 24.0f, scale * 16.0f, glyphs[*cursor].u,
                              glyphs[*cursor].v, 24, 16, gray, texture);
            }
            if ((unsigned char)(*cursor + 0x80) < 0x28) {
                g = &glyphs[*cursor + 0x40];
                dx = func_00283CE0(g->adv) * scale;
                dy = func_00283CE0(g->top) * scale;
                func_0027E1A0(x + dx, y + dy, size, size, g->u, g->v, 16, 16, colors, texture);
            } else if (*cursor > 0x20) {
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
