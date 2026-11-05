#include "common.h"


typedef struct { float f[4]; } EffectRow;
typedef struct {
    float positions[4][4];
    unsigned int colors[4];
    float uv[4][2];
    unsigned long long reserved, texture, state, primitive;
} EffectQuad;
extern unsigned int D_001A7AF0 MACRO_ADDR;
extern int D_001AC040[2] __attribute__((sda));
extern EffectRow *D_001AC048[2] __attribute__((sda));
extern EffectRow corner_template[4] SDATA(D_001AC050);
typedef struct { float u, v; } EffectUV;
extern EffectUV uv_gp[4] SDATA(D_001ABFF0);
extern EffectUV uv_absolute[] __asm__("D_001ABFF0") MACRO_ADDR;
extern unsigned long func_0027C878(int);
extern void func_00282D30(void *, void *, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00280B90(void *, int, int);

void func_002E7338(unsigned char *object)
{
    EffectQuad quad;
    EffectRow position;
    EffectRow *table;
    int count;
    int i, j;
    unsigned int baseColor;
    int variant = (D_001A7AF0 >> 4) & 1;
    table = D_001AC048[variant];
    count = D_001AC040[variant];
    quad.texture = func_0027C878(5);
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
    func_00282D30(&position, object, 0.0009765625f);
    for (i = 0; i < count; i++) {
        int c = object[0xBC];
        unsigned int color;
        float scale;
        if (*(short *)(object + 0xB2)) c += func_002A77E0(*(short *)(object + 0xB2));
        baseColor = 0x2058B0;
        scale = func_00283CE0(c) * 0.025f * table[i].f[3];
        color = ((unsigned int)c << 24) | baseColor;
        for (j = 0; j < 4; j++) {
            quad.colors[j] = color;
            func_00282D30(quad.positions[j], &corner_template[j], scale);
            func_00282CC0(quad.positions[j], quad.positions[j], &table[i]);
            func_00283098(quad.positions[j], quad.positions[j], object + 0xC0);
            func_00282CC0(quad.positions[j], quad.positions[j], &position);
        }
        func_00280B90(&quad, 0, 0);
    }
}
