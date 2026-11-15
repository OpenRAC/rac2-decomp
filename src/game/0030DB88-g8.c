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
extern Vec D_001AF060[4] __attribute__((sda));
extern float D_001AF0A0[8] __attribute__((sda));
/* V is the suffix view of the interleaved UV table. */
extern float D_001AF0A4[] MACRO_ADDR;
extern u32 D_001AF0C0 __attribute__((sda));
extern u32 D_001AF008 __attribute__((sda));
extern float D_001AF0C8 __attribute__((sda));
extern float D_001AF0CC __attribute__((sda));
extern int D_001A79F0, D_001A8BB0;
extern Vec D_001C1490[], D_001C14E0[];
void func_0030DB88(char *obj) {
    Packet p;
    Vec matrix[4];
    Vec *state = *(Vec **)(obj + 0x68);
    float size;
    int i;
    if (D_001A79F0 == 1 && D_001A8BB0 == 2) state = D_001C1490;
    if (D_001A79F0 == 20 && D_001A8BB0 == 2) state = D_001C14E0;
    p.texture = GetEffectTextureDescriptor(11);
    p.flags = 0x8000000048ULL;
    p.mode = 0xFF9000000260ULL;
    p.primitive = 0;
    FastVecSub(&matrix[3], &D_001B5340, state);
    vec_scale_to_length(&matrix[3], &matrix[3], 0.3f);
    FastVecAdd(&matrix[3], &matrix[3], state);
    matrix[3].f[3] = 1.0f;
    FastVecSub(&matrix[0], &D_001B5340, &matrix[3]);
    vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
    FastVecCross(&matrix[1], &matrix[0], &D_0018A0E0);
    vec_scale_to_length(&matrix[1], &matrix[1], -1.0f);
    FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
    p.color[3] = D_001AF0C0;
    p.color[2] = D_001AF0C0;
    p.color[1] = D_001AF0C0;
    p.color[0] = D_001AF0C0;
    size = D_001AF0C8 + func_002A78D8(0.0f, 0.025f);
    for (i = 0; i < 4; i++) {
        FastVecScale(&p.vertex[i], &D_001AF060[i], size);
        transform_vector(&p.vertex[i], &p.vertex[i], &matrix[0]);
        p.uv[i].u = D_001AF0A0[2 * i];
        p.uv[i].v = D_001AF0A4[2 * i];
    }
    draw_world_quad(&p, 0, 0);
    p.color[3] = D_001AF008;
    p.color[2] = D_001AF008;
    p.color[1] = D_001AF008;
    p.color[0] = D_001AF008;
    size = D_001AF0CC + func_002A78D8(0.0f, 0.05f);
    for (i = 0; i < 4; i++) {
        FastVecScale(&p.vertex[i], &D_001AF060[i], size);
        transform_vector(&p.vertex[i], &p.vertex[i], &matrix[0]);
        p.uv[i].u = D_001AF0A0[2 * i];
        p.uv[i].v = D_001AF0A4[2 * i];
    }
    draw_world_quad(&p, 0, 0);
}
