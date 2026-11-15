#include "include_asm.h"
#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct { float vertex[4][4]; u32 color[4]; float uv[8]; u64 primitive, texture, mode, flags; } GlowQuad;
extern float g_camera_l18_position[4];
extern float D_L18_001AA250[][4] __attribute__((sda));
extern float D_L18_001B06C8 __attribute__((sda));
extern float D_L18_001B06A0 __attribute__((sda));
extern float D_L18_001B06CC[] __attribute__((sda));
extern float D_L18_001B06D0[] __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern u64 GetEffectTextureDescriptor(s32);
extern void draw_world_quad(void *, void *, s32);
/* Draws a glowing flat square that always faces the camera at the object effect point. */
void gfx_draw_glow_quad(u8 *object)
{
    float basis[4][4], up[4], offset[4];
    GlowQuad packet;
    u8 *state = *(u8 **)(object + 0x68);
    float *source;
    float *vertex;
    s32 i;
    *(VectorBits *)up = 0;
    up[2] = 1.0f;
    up[3] = 1.0f;
    *(VectorBits *)basis[3] = *(VectorBits *)(state + 0x90);
    FastVecSub(basis[0], g_camera_l18_position, basis[3]);
    vec_scale_to_length(basis[0], basis[0], 1.0f);
    FastVecCross(basis[1], basis[0], up);
    vec_scale_to_length(basis[1], basis[1], 1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);
    vec_scale_to_length(basis[0], basis[0], D_L18_001B06C8);
    vec_scale_to_length(basis[1], basis[1], D_L18_001B06CC[0]);
    vec_scale_to_length(basis[2], basis[2], D_L18_001B06D0[0]);
    FastVecScale(offset, basis[0], D_L18_001B06A0);
    FastVecAdd(basis[3], basis[3], offset);
    packet.flags = 0x8000000048ULL;
    packet.mode = 0xFF9000000260ULL;
    packet.primitive = 5;
    packet.uv[0] = 0;
    packet.uv[1] = 0;
    packet.uv[2] = 0;
    packet.uv[3] = 1;
    packet.uv[4] = 1;
    packet.uv[5] = 0;
    packet.uv[6] = 1;
    packet.uv[7] = 1.0f;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = *(u32 *)(state + 0xC4);
    source = D_L18_001AA250[0];
    for (i = 3, vertex = packet.vertex[0]; i >= 0; i--) {
        FastVecScale(vertex, source, *(float *)(state + 0xC0));
        source += 4;
        transform_vector(vertex, vertex, basis);
        vertex += 4;
    }
    packet.texture = GetEffectTextureDescriptor(11);
    draw_world_quad(&packet, 0, 0);
    packet.texture = GetEffectTextureDescriptor(6);
    draw_world_quad(&packet, 0, 0);
}
