#include "include_asm.h"
#include "common.h"
typedef int EffectVectorWord __attribute__((mode(TI)));
typedef union { float v[4]; EffectVectorWord word; } EffectVector;
typedef struct {
    u8 pad[0x70];
    long f70;
    long f78;
    long f80;
    long f88;
} QuadPacket;
typedef union {
    QuadPacket header;
    struct {
        EffectVector vertex[4];
        u32 color[4];
        float uv[8];
        long control[4];
    } fields;
} EffectPacket;
#define VERTEX(p, i) (&(p).fields.vertex[i])
#define COLORS(p) ((p).fields.color)
#define UV(p) ((p).fields.uv)
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00283198(float);
extern void func_00281DE8(QuadPacket *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00280B90(void *, void *, int);
extern char D_L00_001B8DC0[];
extern float D_L00_001B0BB8 __attribute__((sda));
extern float D_L00_001B0BBC __attribute__((sda));
extern float D_L00_001B0BC0 __attribute__((sda));
extern float D_L00_001B0BC4 __attribute__((sda));
extern u32 D_L00_001B0BC8 __attribute__((sda));
extern u32 D_L00_001B0BCC __attribute__((sda));
extern u32 D_L00_001B0BD0 __attribute__((sda));
extern u32 D_L00_001B0BD4 __attribute__((sda));
extern u32 D_L00_001B0BD8 __attribute__((sda));

/* Draw three bands of the emitter's camera-facing ribbon. */

void func_L00_003FCDB0(char *object) {
    EffectPacket packet;
    EffectVector camera_delta;
    EffectVector segment;
    EffectVector midpoint;
    EffectVector normal;
    char *state = *(char **)(object + 0x68);
    char *position;
    float life;
    float alpha;
    int i;
    float *uv;
    u32 color;

    life = IntToFloat(*(int *)(state + 0x38)) * *(float *)(state + 0x3C);
    InitQuadPacketState(&packet.header, 23, 0, 0x80);
    alpha = life * 128.0f;
    COLORS(packet)[0] = COLORS(packet)[1] = COLORS(packet)[2] = COLORS(packet)[3] =
        D_L00_001B0BC8 | ((u32)FloatToInt(alpha) << 24);
    COLORS(packet)[2] = COLORS(packet)[3] =
        D_L00_001B0BCC | ((u32)FloatToInt(alpha) << 24);
    UV(packet)[0] = 0.0f; UV(packet)[1] = 0.0f; UV(packet)[2] = 0.0f; UV(packet)[3] = 1.0f;
    UV(packet)[4] = 1.0f; UV(packet)[5] = 0.0f; UV(packet)[6] = 1.0f; UV(packet)[7] = 1.0f;
    for (i = 0; i < 4; i++) {
        UV(packet)[i * 2] -= *(float *)(state + 0x30);
        if (UV(packet)[i * 2] <= 7.0f) UV(packet)[i * 2] += 7.0f;
    }
    *(float *)(state + 0x30) -= 0.1f;
    if (*(float *)(state + 0x30) <= 4.0f) *(float *)(state + 0x30) += 4.0f;
    position = object + 0x10;
    FastVecSub(&camera_delta, position, gCameraPosition_L00);
    FastVecSub(&segment, state + 0x50, position);
    FastVecScale(&segment, &segment, 0.5f);
    FastVecAdd(&midpoint, position, &segment);
    FastVecCross(&normal, &camera_delta, &segment);
    vec_scale_to_length(&normal, &normal, D_L00_001B0BB8);
    FastVecAdd(VERTEX(packet,0), position, &normal);
    FastVecSub(VERTEX(packet,1), position, &normal);
    vec_scale_to_length(&normal, &normal, D_L00_001B0BBC);
    FastVecAdd(VERTEX(packet,2), &midpoint, &normal);
    FastVecSub(VERTEX(packet,3), &midpoint, &normal);
    draw_world_quad(&packet, 0, 0);
    COLORS(packet)[0] = COLORS(packet)[2];
    COLORS(packet)[1] = COLORS(packet)[3];
    COLORS(packet)[3] = D_L00_001B0BD0;
    COLORS(packet)[2] = D_L00_001B0BD0;
    *(EffectVectorWord *)VERTEX(packet,0) = *(EffectVectorWord *)VERTEX(packet,2);
    *(EffectVectorWord *)VERTEX(packet,1) = *(EffectVectorWord *)VERTEX(packet,3);
    FastVecAdd(VERTEX(packet,2), VERTEX(packet,2), &segment);
    FastVecAdd(VERTEX(packet,3), VERTEX(packet,3), &segment);
    draw_world_quad(&packet, 0, 0);
    InitQuadPacketState(&packet.header, 14, 1, 0x80);
    color = D_L00_001B0BD4 | ((u32)FloatToInt(life * 64.0f) << 24);
    COLORS(packet)[0] = COLORS(packet)[1] = color;
    COLORS(packet)[3] = D_L00_001B0BD8;
    COLORS(packet)[2] = D_L00_001B0BD8;
    UV(packet)[0] = 0.0f;
    UV(packet)[1] = 0.0f;
    UV(packet)[2] = 0.0f;
    UV(packet)[3] = 1.0f;
    UV(packet)[4] = 1.0f;
    UV(packet)[5] = 0.0f;
    UV(packet)[6] = 1.0f;
    UV(packet)[7] = 1.0f;

    vec_scale_to_length(&normal, &normal, D_L00_001B0BC0);
    FastVecAdd(VERTEX(packet,0), position, &normal);
    FastVecSub(VERTEX(packet,1), position, &normal);
    FastVecAdd(&midpoint, position, &segment);
    FastVecAdd(&midpoint, &midpoint, &segment);
    vec_scale_to_length(&normal, &normal, D_L00_001B0BC4);
    FastVecAdd(VERTEX(packet,2), &midpoint, &normal);
    FastVecSub(VERTEX(packet,3), &midpoint, &normal);
    draw_world_quad(&packet, 0, 0);
}
