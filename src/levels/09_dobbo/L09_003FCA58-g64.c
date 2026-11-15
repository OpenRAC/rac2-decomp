#include "common.h"

/* Draws two jittered, camera-facing glow quads and their larger outer layers.
 * The four-vector corner table is a measured 64-byte GP-relative object. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } GlowVector;
typedef struct {
    GlowVector vertex[4];
    unsigned color[4];
    float uv[4][2];
    unsigned long long flags, texture, mode, blend;
} GlowPacket;
extern GlowVector D_L09_00255F40[][4], D_L09_00256410[], D_L09_001B1150[4] __attribute__((sda));
extern GlowVector D_L09_001B9A00[], D_0018A0E0[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern unsigned long long func_0027C878(int);
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern int func_L02_002F1658(void);
extern void func_00280B90(void *, int, int);

/* Draws the flickering glow at both ends of a beam, each with a bright core and a larger soft halo. */
void func_L09_003FCA58(void *unused, int slot, int alpha)
{
    GlowPacket packet;
    GlowVector basis[3], position, jitter;
    unsigned color = ((alpha * 255 / 100) << 24) | 0xFFFFFF;
    float scale;
    int i;
    GlowVector *corner, *vertex;
    qcopy(&position, &D_L09_00255F40[slot][0]);
    position.f[3] = 1.0f;
    FastVecSub(&basis[0], D_L09_001B9A00, &position);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecCross(&basis[1], &basis[0], D_0018A0E0);
    vec_scale_to_length(&basis[1], &basis[1], -1.0f);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    packet.texture = GetEffectTextureDescriptor(11);
    packet.blend = 0xFF00000044ULL;
    packet.mode = 0xFF9000000260ULL;
    packet.flags = 5;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    packet.uv[0][0] = 0; packet.uv[0][1] = 0; packet.uv[1][0] = 0; packet.uv[1][1] = 1;
    packet.uv[2][0] = 1; packet.uv[2][1] = 0; packet.uv[3][0] = 1; packet.uv[3][1] = 1;
    scale = RandomFloatRange(0.3f, 0.325f);
    if (!IsResidentFlagClear())
        scale = 0.3125f;
    jitter.f[0] = RandomSignedFloatRange(0, 0.05f);
    jitter.f[1] = RandomSignedFloatRange(0, 0.05f);
    jitter.f[2] = RandomSignedFloatRange(0, 0.05f);
    if (!IsResidentFlagClear()) {
        jitter.f[0] = 0.025f;
        jitter.f[1] = 0.025f;
        jitter.f[2] = 0.025f;
    }
    for (i = 0; i < 4; i++) {
        FastVecScale(&packet.vertex[i], &D_L09_001B1150[i], scale);
        transform_vector(&packet.vertex[i], &packet.vertex[i], basis);
        FastVecAdd(&packet.vertex[i], &packet.vertex[i], &jitter);
    }
    draw_world_quad(&packet, 0, 0);
    alpha = (alpha * 96 / 100) << 24;
    packet.blend = 0xFF00000048ULL;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = alpha | 0xFFAF10;
    {
        int j;
        vertex = packet.vertex;
        for (corner = D_L09_001B1150, j = 3; j >= 0; j--) {
            FastVecScale(vertex, corner, scale * 3.0f);
            corner++;
            transform_vector(vertex, vertex, basis);
            vertex++;
        }
    }
    draw_world_quad(&packet, 0, 0);
    qcopy(&position, &D_L09_00256410[slot]);
    FastVecSub(&basis[0], D_L09_001B9A00, &position);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecCross(&basis[1], &basis[0], D_0018A0E0);
    vec_scale_to_length(&basis[1], &basis[1], -1.0f);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    scale = RandomFloatRange(0.3f, 0.325f);
    if (!IsResidentFlagClear())
        scale = 0.3125f;
    packet.blend = 0xFF00000044ULL;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    {
        int j;
        corner = D_L09_001B1150;
        vertex = packet.vertex;
        for (j = 3; j >= 0; j--) {
            FastVecScale(vertex, corner, scale);
            corner++;
            transform_vector(vertex, vertex, basis);
            FastVecAdd(vertex, vertex, &jitter);
            vertex++;
        }
    }
    draw_world_quad(&packet, 0, 0);
    packet.blend = 0xFF00000048ULL;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = alpha | 0xFFAF10;
    {
        int j;
        vertex = packet.vertex;
        for (corner = D_L09_001B1150, j = 3; j >= 0; j--) {
            FastVecScale(vertex, corner, scale * 3.0f);
            corner++;
            transform_vector(vertex, vertex, basis);
            vertex++;
        }
    }
    draw_world_quad(&packet, 0, 0);
}
