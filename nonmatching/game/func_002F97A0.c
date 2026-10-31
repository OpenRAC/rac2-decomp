/* func_002F97A0 - 1052 bytes, boot and all 27 levels. Draws up to `length`
   characters in the small font (glyph table D_00263EF0): each glyph's left and right
   corners fade with the distance from the screen centre, computed in double
   (215.0 in shop mode 2 of D_0021F240, else 256.0 scaled by 0.75); characters below
   0x20 first get a 24x16 grey cell, 0x80..0xA7 take an accent glyph 0x40 further on.

   Attempt, 31 October 2026: 1052/1052 bytes, 0/28 USA places (tools/check.py), in
   place of the marker in src/game/002F5220.c (-O2 -G8); func_002F9198 and
   func_002F9778 still pass there. Everything outside the colour block matches.
   In that block (0x002F999C..0x002F9A74) retail keeps the right alpha in a0 and the
   left colour in a1, truncates the colour after the two clamps and computes the grey
   sum in t2; cc1 uses a2/a1, truncates the colour before the clamps and sums in v1.
   Measured steps: 1044 with 216.0, an int colour and one text pointer; 1052 (110
   differing lines) with 215.0, a 64-bit colour, unsigned corner colours and a signed
   division; 97 with p set in the loop; 86 with the grey sum in steps; 66 with the
   floats first in func_0027E1A0's prototype (it is still assembly); 59 with the
   accent index as offset + base and the loop as `if (length == 0 || *text == 0)`
   then do/while.
   Tried without change: the clamps swapped or as ternaries, a `small` test computed
   before the corner stores, the colour or'd without the int cast or through an int
   rgb local, the grey sum reversed or with shade last. */

/* A glyph of the small font: its texture cell, its vertical offset and its advance. */
typedef struct {
    unsigned char u;
    unsigned char v;
    signed char top;
    signed char advance;
} Glyph_002F97A0;

extern Glyph_002F97A0 D_00263EF0[];
extern unsigned long long func_0027C878(int);
extern float func_00283CE0(int);
extern void func_0027E1A0(float, float, float, float, int, int, int, int, int *, unsigned long long);

/* Draws up to `length` characters of `text` in the small font, fading each glyph's left
 * and right edges with its distance from the centre of the screen. */
void func_002F97A0(float x, float y, float scale, unsigned long long color, unsigned char *text, int length)
{
    unsigned char *p;
    int corners[4];
    int grey[4];
    unsigned long long texture = func_0027C878(2);
    float cell = scale * 16.0f;
    Glyph_002F97A0 *font = D_00263EF0;
    int drawn = 0;

    color &= 0xFFFFFF;
    if (length == 0 || *text == 0)
        return;
    p = text;
    do {
        if (font[*p].advance != 0) {
            float top = func_00283CE0(font[*p].top) * scale;
            int left;
            int right;
            unsigned int leftColor;
            unsigned int rightColor;
            int shade;
            int tint;

            if (D_0021F240.mode == 2) {
                left = 128 - (int)__builtin_fabs((double)(215.0f - x));
                right = 128 - (int)__builtin_fabs((double)(215.0f - (x + cell)));
            } else {
                left = 128 - (int)(__builtin_fabs((double)(256.0f - x)) * 0.75);
                right = 128 - (int)(__builtin_fabs((double)(256.0f - (x + cell))) * 0.75);
            }
            if (left < 0)
                left = 0;
            if (right < 0)
                right = 0;
            leftColor = (left << 24) | (int)color;
            rightColor = (right << 24) | (int)color;
            corners[0] = leftColor;
            corners[1] = rightColor;
            corners[2] = leftColor;
            corners[3] = rightColor;
            if (*p < 0x20) {
                shade = (int)((leftColor & 0xFF) + ((leftColor >> 8) & 0xFF) + ((leftColor >> 16) & 0xFF)) / 3;
                tint = (leftColor & 0xFF000000) + (shade << 16);
                tint += shade << 8;
                tint = shade + tint;
                grey[0] = tint;
                grey[1] = tint;
                grey[2] = tint;
                grey[3] = tint;
                func_0027E1A0(x, y + top, scale * 24.0f, scale * 16.0f,
                              font[*p].u, font[*p].v, 24, 16, grey, texture);
            }
            if ((unsigned char)(*p + 0x80) < 0x28) {
                int index = *p + 0x40;
                Glyph_002F97A0 *accent = (Glyph_002F97A0 *)(index * sizeof(Glyph_002F97A0) + (int)font);
                float dx = func_00283CE0(accent->advance) * scale;
                float dy = func_00283CE0(accent->top) * scale;
                func_0027E1A0(x + dx, y + dy, cell, cell, accent->u, accent->v, 16, 16, corners, texture);
            } else if (*p > 0x20) {
                func_0027E1A0(x, y + top, cell, cell,
                              font[*p].u, font[*p].v, 16, 16, corners, texture);
            }
            x += func_00283CE0(font[*p].advance) * scale;
        }
        if (++drawn == length)
            return;
    } while (*++p != 0);
}
