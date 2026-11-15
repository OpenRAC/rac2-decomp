#include "common.h"

extern unsigned char D_L30_001B1810 __attribute__((sda));
extern unsigned char D_L30_001B1811 __attribute__((sda));
extern unsigned char D_L30_001B1812 __attribute__((sda));
extern unsigned char D_L30_001B1813 __attribute__((sda));
extern unsigned char D_L30_001B1814 __attribute__((sda));
extern unsigned char D_L30_001B1815 __attribute__((sda));
extern unsigned char D_L30_001B1816 __attribute__((sda));
extern unsigned char D_L30_001B1817 __attribute__((sda));
extern unsigned char D_L30_001B1818 __attribute__((sda));
extern unsigned char D_L30_001B1819 __attribute__((sda));
extern unsigned char D_L30_001B181A __attribute__((sda));
extern unsigned char D_L30_001B181B __attribute__((sda));
extern unsigned char D_L30_001B181C __attribute__((sda));
extern int D_L30_001B1760 __attribute__((sda));
extern int D_L30_001B1764 __attribute__((sda));
extern int D_L30_001B1768 __attribute__((sda));
extern int D_L30_001B176C __attribute__((sda));
extern int D_L30_001B1780 __attribute__((sda));
extern int D_L30_001B1784 __attribute__((sda));
extern float D_L30_001B1788 __attribute__((sda));
extern float D_L30_001B178C __attribute__((sda));
extern float D_L30_001B1790 __attribute__((sda));
extern float D_L30_001B1794 __attribute__((sda));
extern float D_L30_001B1798 __attribute__((sda));
extern float D_L30_001B16F4 __attribute__((sda));
/* Palette pointer storage, accessed through its word-pointer view as in RAC1 HUDs. */
extern unsigned char D_L30_001B1808[4] __attribute__((sda));
extern int D_L30_001B2848 __attribute__((sda));

typedef struct {
    char pad[0x183C];
    float current;
    float maximum;
} GaugeState;

extern GaugeState g_hero_state;
extern int g_screen_height;
extern unsigned D_L30_0025CEB0[];
extern void gfx_append_vectors_to_packet(int, int, unsigned long, int, unsigned long);
extern unsigned long GetEffectTextureDescriptor(int);
extern int FloatToInt(float);
extern float FastVecLength(void *), math_fabs(float), FastAddRotations(float, float);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long, unsigned long);
/* The EE assigns integer and float arguments to independent register banks. */
extern void AppendRotatedSpriteQuad(float, float, float, float, float,
                              int, int, unsigned long, int, int, int, int, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, unsigned long, int, int);

static __inline__ unsigned long PackGaugeFlag(unsigned long flags,
                                              unsigned char value, int shift)
{
    return flags | ((unsigned long)value << shift);
}

/* Draws the museum status gauge and updates its swizzled palette. */
/* Draws the museum status gauge on the screen. */
void DrawMuseumStatusGauge(char *obj) {
    char *s = *(char **)(obj + 0x68);
    unsigned long tex;
    float scale = 0.017453294f, delta, absdelta, angle;
    int n, lo, hi, i, j;

    unsigned long flags, mode;
    flags = D_L30_001B1815;
    flags = PackGaugeFlag(flags, D_L30_001B1816, 1);
    flags = PackGaugeFlag(flags, D_L30_001B1817, 4);
    flags = PackGaugeFlag(flags, D_L30_001B1818, 12);
    flags = PackGaugeFlag(flags, D_L30_001B1819, 14);
    flags = PackGaugeFlag(flags, D_L30_001B181A, 15);
    mode = D_L30_001B1810;
    mode = PackGaugeFlag(mode, D_L30_001B1811, 2);
    flags = PackGaugeFlag(flags, D_L30_001B181B, 16);
    mode = PackGaugeFlag(mode, D_L30_001B1812, 4);
    mode = PackGaugeFlag(mode, D_L30_001B1813, 6);
    gfx_append_vectors_to_packet(2, 0x47, flags | ((unsigned long)D_L30_001B181C << 17),
            0x42, mode | ((unsigned long)D_L30_001B1814 << 32));
    tex = GetEffectTextureDescriptor(D_L30_001B1764 + *(int *)(s + 0x64));
    DrawTexturedQuad(FloatToInt(D_L30_001B1798), g_screen_height - 80,
           64, 64, 0, 0, 64, 64, D_L30_001B1760, tex);
    tex = GetEffectTextureDescriptor(D_L30_001B1768 + *(int *)(s + 0x64));
    DrawTexturedQuad(FloatToInt(D_L30_001B1798) + 64, g_screen_height - 80,
           64, 64, 0, 0, 64, 64, D_L30_001B1760, tex);
    tex = GetEffectTextureDescriptor(D_L30_001B176C + *(int *)(s + 0x64));
    angle = D_L30_001B1788 * (FastVecLength(s) * scale);
    angle /= D_L30_001B16F4 * 0.016666668f;
    angle = FastAddRotations(angle, D_L30_001B178C * scale);
    AppendRotatedSpriteQuad(D_L30_001B1798 + 32.0f, (float)(g_screen_height - 48),
           32.0f, 32.0f, angle, 32, 32, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    absdelta = D_L30_001B1790 * (math_fabs(*(float *)(s + 0x5C)) * scale);
    angle = FastAddRotations(D_L30_001B1794 * scale, absdelta);
    AppendRotatedSpriteQuad(D_L30_001B1798 + 64.0f + 32.0f, (float)(g_screen_height - 48),
           32.0f, 32.0f, angle, 32, 32, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    delta = g_hero_state.current - *(float *)(s + 0x94);
    delta *= 0.2f;
    absdelta = math_fabs(delta);
    if (absdelta > 1.0f) {
        delta /= absdelta;
    }
    *(float *)(s + 0x94) += delta;
    n = FloatToInt(*(float *)(s + 0x94) * 251.0f / g_hero_state.maximum) + 2;
    if (n > 253) {
        n = 253;
    }
    if (n < 2) {
        n = 2;
    }
    lo = *(int *)(s + 0x98) <= n ? *(int *)(s + 0x98) : n;
    hi = *(int *)(s + 0x98) < n ? n : *(int *)(s + 0x98);
    for (i = lo; i <= hi; i++) {
        j = (i & 0xE7) | ((i & 16) >> 1) | ((i & 8) << 1);
        if (i < n) {
            (*(unsigned **)&D_L30_001B1808)[j] = D_L30_0025CEB0[j];
        } else {
            (*(unsigned **)&D_L30_001B1808)[j] = 0x80000000;
        }
    }
    tex = GetEffectTextureDescriptor(*(int *)(s + 0x64) + D_L30_001B1780);
    DrawTexturedQuad(368, g_screen_height - 144, 128, 128, 0, 0, 128, 128, 0x70808080, tex);
    tex = GetEffectTextureDescriptor(*(int *)(s + 0x64) + D_L30_001B1784);
    DrawTexturedQuad(368, g_screen_height - 144, 128, 128, 0, 0, 128, 128, 0x70808080, tex);
    *(int *)(s + 0x98) = n;
    if (g_hero_state.current < g_hero_state.maximum * 0.1f && ((D_L30_001B2848 / 90) & 1)) {
        text_draw_centered_medium(256, 370, 0x80000080, GetLocalizedString(0x1149), 100);
    }
    gfx_append_vectors_to_packet(2, 0x47, 0x5340B, 0x42, 0x8000000044UL);
}
