#include "common.h"

/* Adapted from RAC1 draw_beam_anchor_camera_facing_quads (OpenRAC, GPL-3.0). */
typedef struct { float f[4]; } __attribute__((aligned(16))) Vec;
typedef struct { float u, v; } UV;
typedef struct { Vec vertex[4]; u32 color[4]; UV uv[4]; u64 primitive, texture, mode, flags; } Packet;
extern u64 GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), FastVecCross(void *, void *, void *), transform_vector(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float), FastVecScale(void *, void *, float), draw_world_quad(void *, int, int);
extern float math_random_signed_float_range(float, float);
extern Vec g_camera_eye_state, D_0018A0E0;
extern Vec D_001AF060[4] __attribute__((sda));
extern float D_001AF0A0[8] __attribute__((sda));
/* V is the suffix view of the interleaved UV table. */
extern float D_001AF0A4[] MACRO_ADDR;
extern u32 D_001AF0C0 __attribute__((sda));
extern u32 D_001AF008 __attribute__((sda));
extern float D_001AF0C8 __attribute__((sda));
extern float D_001AF0CC __attribute__((sda));
extern int g_current_map_index, g_current_game_mode;
extern Vec D_001C1490[], D_001C14E0[];
/* Draws two camera-facing glow squares at the end of the beam (level-specific version). */
void beam_draw_anchor_glow_level(char *moby) {
    Packet quad;
    Vec basis[4];
    Vec *vars = *(Vec **)(moby + 0x68);
    float size;
    int i;
    if (g_current_map_index == 1 && g_current_game_mode == 2) vars = D_001C1490;
    if (g_current_map_index == 20 && g_current_game_mode == 2) vars = D_001C14E0;
    quad.texture = GetEffectTextureDescriptor(11);
    quad.flags = 0x8000000048ULL;
    quad.mode = 0xFF9000000260ULL;
    quad.primitive = 0;
    FastVecSub(&basis[3], &g_camera_eye_state, vars);
    vec_scale_to_length(&basis[3], &basis[3], 0.3f);
    FastVecAdd(&basis[3], &basis[3], vars);
    basis[3].f[3] = 1.0f;
    FastVecSub(&basis[0], &g_camera_eye_state, &basis[3]);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecCross(&basis[1], &basis[0], &D_0018A0E0);
    vec_scale_to_length(&basis[1], &basis[1], -1.0f);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    quad.color[3] = D_001AF0C0;
    quad.color[2] = D_001AF0C0;
    quad.color[1] = D_001AF0C0;
    quad.color[0] = D_001AF0C0;
    size = D_001AF0C8 + math_random_signed_float_range(0.0f, 0.025f);
    for (i = 0; i < 4; i++) {
        FastVecScale(&quad.vertex[i], &D_001AF060[i], size);
        transform_vector(&quad.vertex[i], &quad.vertex[i], &basis[0]);
        quad.uv[i].u = D_001AF0A0[2 * i];
        quad.uv[i].v = D_001AF0A4[2 * i];
    }
    draw_world_quad(&quad, 0, 0);
    quad.color[3] = D_001AF008;
    quad.color[2] = D_001AF008;
    quad.color[1] = D_001AF008;
    quad.color[0] = D_001AF008;
    size = D_001AF0CC + math_random_signed_float_range(0.0f, 0.05f);
    for (i = 0; i < 4; i++) {
        FastVecScale(&quad.vertex[i], &D_001AF060[i], size);
        transform_vector(&quad.vertex[i], &quad.vertex[i], &basis[0]);
        quad.uv[i].u = D_001AF0A0[2 * i];
        quad.uv[i].v = D_001AF0A4[2 * i];
    }
    draw_world_quad(&quad, 0, 0);
}
