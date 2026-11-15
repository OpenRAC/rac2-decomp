#include "common.h"

typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;
extern char D_L00_001A8F20[] MACRO_ADDR;
extern char D_L00_001B9000[];
extern int func_00283CF0(float);
extern void func_00281DE8(void *, int, int, int);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(char *, int, int);

/* Debug line labels reproduce the measured assembler division padding. */
void func_L00_00419668(char *object)
{
    RenderPacket packet;
    Vector step, a, b, c, d, center, temp;
    char *state = *(char **)(object + 0x68);
    int count = *(int *)(state + 0x20);
    int i = 0;
    float delta, divisor;
    packet.color[3] = 0x08404040;
    packet.color[2] = 0x08404040;
    packet.color[1] = 0x08404040;
    packet.color[0] = 0x08404040;
    *(int *)&packet.uv[0][0] = 0;
    *(int *)&packet.uv[0][1] = 0;
    *(int *)&packet.uv[1][0] = 0;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    *(int *)&packet.uv[2][1] = 0;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    func_00281DE8(&packet, *(int *)(state + 0x48), 1, 0x80);
    packet.f70 = 0;
    VU1_addGSregister(0x42, 0x8000000048ULL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260ULL);
    VU1_addGSregister(0x47, 0x513F1);
    FastVecSub(&a, D_L00_001A8F20, D_L00_001B9000);
    FastVecSub(&a, &a, D_L00_001B9000 + 0x10);
    FastVecSub(&b, D_L00_001B9000 + 0x10, D_L00_001B9000);
    FastVecSub(&c, D_L00_001B9000, D_L00_001B9000 + 0x10);
    FastVecAdd(&d, D_L00_001B9000, D_L00_001B9000 + 0x10);
    FastVecSub(&center, D_L00_001B9000 - 0x240, state);
    vec_scale_to_length(&center, &center, 0.75f);
    FastVecAdd(&center, state, &center);
    FastVecScale(&temp, &a, *(float *)(state + 0xC));
    FastVecAdd(&packet.vertex[0], &temp, &center);
    FastVecScale(&temp, &b, *(float *)(state + 0xC));
    FastVecAdd(&packet.vertex[1], &temp, &center);
    FastVecScale(&temp, &c, *(float *)(state + 0xC));
    FastVecAdd(&packet.vertex[2], &temp, &center);
    FastVecScale(&temp, &d, *(float *)(state + 0xC));
    FastVecAdd(&packet.vertex[3], &temp, &center);
    divisor = count - 1;
    delta = (*(float *)(state + 0x1C) - *(float *)(state + 0xC)) / divisor;
    FastVecSub(&step, state + 0x10, state);
    FastVecScale(&step, &step, 1.0f / divisor);
    FastVecScale(&temp, &a, delta);
    FastVecAdd(&a, &temp, &step);
    FastVecScale(&temp, &b, delta);
    FastVecAdd(&b, &temp, &step);
    FastVecScale(&temp, &c, delta);
    FastVecAdd(&c, &temp, &step);
    FastVecScale(&temp, &d, delta);
    FastVecAdd(&d, &temp, &step);
    for (; i < count; i++) {
        int alpha;
        unsigned int color;
        FastVecAdd(&packet.vertex[0], &packet.vertex[0], &a);
        FastVecAdd(&packet.vertex[1], &packet.vertex[1], &b);
        FastVecAdd(&packet.vertex[2], &packet.vertex[2], &c);
        FastVecAdd(&packet.vertex[3], &packet.vertex[3], &d);
        alpha = FloatToInt((float)*(int *)(state + 0x2C) * (float)(count - i) / (float)count);
        if (alpha > 255) alpha = 255;
        else if (alpha < 0) alpha = 0;
        color = *(unsigned int *)(state + 0x40) + (alpha << 24);
        packet.color[3] = color;
        packet.color[2] = color;
        packet.color[1] = color;
        packet.color[0] = color;
        if (alpha > 0) draw_world_quad((char *)&packet, 0, 0);
    }
}
