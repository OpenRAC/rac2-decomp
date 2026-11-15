#include "common.h"

/* Adapted from RAC1 draw_beam_anchor_camera_facing_quads (OpenRAC, GPL-3.0). */
typedef struct { float f[4]; } __attribute__((aligned(16))) Vec;
typedef struct { float u, v; } UV;
typedef struct { Vec vertex[4]; u32 color[4]; UV uv[4]; u64 primitive, texture, mode, flags; } Packet;
extern u64 func_0027C878(int);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00282DD8(void *, void *, void *), func_002830C0(void *, void *, void *);
extern void func_00282F20(void *, void *, float), func_00282D30(void *, void *, float), func_00280B90(void *, int, int);
extern float func_002A78D8(float, float);
extern Vec D_001B5340, D_0018A0E0;
extern Vec D_001AEEA0[4] __attribute__((sda));
extern float D_001AEEE0[8] __attribute__((sda));
/* V is the suffix view of the interleaved UV table. */
extern float D_001AEEE4[] MACRO_ADDR;
extern u32 D_001AEF00 __attribute__((sda));
extern u32 D_001AEE58 __attribute__((sda));
extern float D_001AEF08 __attribute__((sda));
extern float D_001AEF0C __attribute__((sda));
/* Draws two camera-facing glow squares at the end of the beam. */
void func_0030C188(char *moby) {
    Packet quad;
    Vec basis[4];
    Vec *vars = *(Vec **)(moby + 0x68);
    float size;
    int i;
    quad.texture = GetEffectTextureDescriptor(11);
    quad.flags = 0x8000000048ULL;
    quad.mode = 0xFF9000000260ULL;
    quad.primitive = 0;
    FastVecSub(&basis[3], &gCameraState_001B5340, vars);
    vec_scale_to_length(&basis[3], &basis[3], 0.3f);
    FastVecAdd(&basis[3], &basis[3], vars);
    basis[3].f[3] = 1.0f;
    FastVecSub(&basis[0], &gCameraState_001B5340, &basis[3]);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecCross(&basis[1], &basis[0], &D_0018A0E0);
    vec_scale_to_length(&basis[1], &basis[1], -1.0f);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    quad.color[3] = D_001AEF00;
    quad.color[2] = D_001AEF00;
    quad.color[1] = D_001AEF00;
    quad.color[0] = D_001AEF00;
    size = D_001AEF08 + RandomSignedFloatRange(0.0f, 0.025f);
    for (i = 0; i < 4; i++) {
        FastVecScale(&quad.vertex[i], &D_001AEEA0[i], size);
        transform_vector(&quad.vertex[i], &quad.vertex[i], &basis[0]);
        quad.uv[i].u = D_001AEEE0[2 * i];
        quad.uv[i].v = D_001AEEE4[2 * i];
    }
    draw_world_quad(&quad, 0, 0);
    quad.color[3] = D_001AEE58;
    quad.color[2] = D_001AEE58;
    quad.color[1] = D_001AEE58;
    quad.color[0] = D_001AEE58;
    size = D_001AEF0C + RandomSignedFloatRange(0.0f, 0.05f);
    for (i = 0; i < 4; i++) {
        FastVecScale(&quad.vertex[i], &D_001AEEA0[i], size);
        transform_vector(&quad.vertex[i], &quad.vertex[i], &basis[0]);
        quad.uv[i].u = D_001AEEE0[2 * i];
        quad.uv[i].v = D_001AEEE4[2 * i];
    }
    draw_world_quad(&quad, 0, 0);
}
