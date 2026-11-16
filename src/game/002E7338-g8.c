#include "common.h"


typedef struct { float f[4]; } EffectRow;
typedef struct {
    float positions[4][4];
    unsigned int colors[4];
    float uv[4][2];
    unsigned long long reserved, texture, state, primitive;
} EffectQuad;
extern unsigned int g_equipment_bits MACRO_ADDR;
extern int g_glow_quad_counts[2] __attribute__((sda));
extern EffectRow *g_glow_quad_tables[2] __attribute__((sda));
extern EffectRow corner_template[4] SDATA(D_001AC050);
typedef struct { float u, v; } EffectUV;
extern EffectUV uv_gp[4] SDATA(D_001ABFF0);
extern EffectUV uv_absolute[] __asm__("D_001ABFF0") MACRO_ADDR;
extern unsigned long GetEffectTextureDescriptor(int);
extern void FastVecScale(void *, void *, float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void draw_world_quad(void *, int, int);

/* Draws glowing quads around an object, fading in with its effect strength. */
void part_draw_glow_quads(unsigned char *object)
{
    EffectQuad quad;
    EffectRow position;
    EffectRow *table;
    int count;
    int i, j;
    unsigned int baseColor;
    int variant = (g_equipment_bits >> 4) & 1;
    table = g_glow_quad_tables[variant];
    count = g_glow_quad_counts[variant];
    quad.texture = GetEffectTextureDescriptor(5);
    quad.state = 0xFF9000000260ULL;
    quad.primitive = 0x8000000048ULL;
    quad.reserved = 0;
    {
        const unsigned char *vSource = (const unsigned char *)uv_absolute;
        unsigned char *vDest = (unsigned char *)&quad + 0x54;
        unsigned char *uDest = (unsigned char *)&quad + 0x50;
        const unsigned char *uSource = (const unsigned char *)uv_gp;
        int k;
        for (k = 0; k < 4; k++) {
            *(float *)uDest = *(const float *)(uSource + k * 8);
            *(float *)vDest = *(const float *)(vSource + k * 8 + 4);
            uDest += 8;
            vDest += 8;
        }
    }
    FastVecScale(&position, object, 0.0009765625f);
    for (i = 0; i < count; i++) {
        int alpha = object[0xBC];
        unsigned int color;
        float scale;
        if (*(short *)(object + 0xB2)) alpha += math_random_int_below(*(short *)(object + 0xB2));
        baseColor = 0x2058B0;
        scale = IntToFloat(alpha) * 0.025f * table[i].f[3];
        color = ((unsigned int)alpha << 24) | baseColor;
        for (j = 0; j < 4; j++) {
            quad.colors[j] = color;
            FastVecScale(quad.positions[j], &corner_template[j], scale);
            FastVecAdd(quad.positions[j], quad.positions[j], &table[i]);
            matrix_mul_vec3(quad.positions[j], quad.positions[j], object + 0xC0);
            FastVecAdd(quad.positions[j], quad.positions[j], &position);
        }
        draw_world_quad(&quad, 0, 0);
    }
}
