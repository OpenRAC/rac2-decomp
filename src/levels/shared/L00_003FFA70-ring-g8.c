#include "include_asm.h"
#include "names.h"

/* Small-data ring renderer; the 16-byte clear takes one register (ti_one_gpr.py). */

typedef unsigned int RenderQuad __attribute__((mode(TI)));
typedef union { RenderQuad word; float v[4]; } RenderVector;
typedef struct { float x, y, z, w; } RenderVec __attribute__((aligned(16)));

/* The 144-byte quad packet func_00280B90 draws: four vertices, their colours,
   their UVs and four GS words. */
typedef struct {
    RenderVec vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long long tag[4];
} RenderPacket;

extern long long GetEffectTextureDescriptor(int);
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecCross(void *, const void *, const void *);
extern void FastVecScale(void *, const void *, float);
extern void transform_vector(void *, const void *, const void *);
extern void gfx_world_to_screen_unit(void *, float *, float *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_ease_out_quad(float);
extern float FastAddRotations(float, float);
extern void draw_world_quad(void *, void *, int);
extern RenderVec g_camera_l00_position;
extern int g_ring_effect_flag_bits_a __attribute__((sda));
extern int g_ring_effect_flag_bits_b __attribute__((sda));
extern int g_ring_effect_flag_bits_c __attribute__((sda));
extern int g_ring_effect_flag_bits_d __attribute__((sda));
extern int g_ring_effect_flag_bits_e __attribute__((sda));
extern int g_ring_effect_texture_id __attribute__((sda));
extern unsigned int g_ring_l00_effect_color __attribute__((sda));
extern float g_ring_effect_duration __attribute__((sda));
/* 48 quads of a flat ring of 98 vertices: per corner a vertex index and an
   index into the angle table, which holds an angle and its step. */
extern short g_ring_effect_face_indices[][4][2];
extern RenderVec g_ring_effect_vertices[];
extern float g_ring_effect_angles[][2];

/* Draws the object's ring facing the camera (D_L00_001B8DC0), scaled by its
   state's size, with each corner's UV taken from its screen position and
   pushed along a rotating angle; the push weakens as the size nears
   D_L00_001B0C94. Then advances every angle. */
void gfx_draw_ring_effect(char *object)
{
    RenderPacket packet;
    RenderVec matrix[4];
    RenderVector up;
    char *state;
    int face, corner, index, vtx;
    long long flags;
    float *u, *v, *uv;
    float delta, scale, c, s;

    state = *(char **)(object + 0x68);
    up.word = 0;
    up.v[2] = 1.0f;
    packet.tag[1] = GetEffectTextureDescriptor(g_ring_effect_texture_id);
    packet.tag[2] = 0xFF9000000260LL;
    flags = (long long)g_ring_effect_flag_bits_a;
    flags |= (long long)g_ring_effect_flag_bits_b << 2;
    flags |= (long long)g_ring_effect_flag_bits_c << 4;
    flags |= (long long)g_ring_effect_flag_bits_d << 6;
    flags |= (long long)g_ring_effect_flag_bits_e << 32;
    packet.tag[3] = flags;
    packet.tag[0] = 0;
    FastVecSub(&matrix[0], &g_camera_l00_position, object + 0x10);
    vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
    FastVecCross(&matrix[1], &matrix[0], &up);
    vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
    FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
    matrix[3].x = *(float *)(object + 0x10);
    matrix[3].y = *(float *)(object + 0x14);
    matrix[3].z = *(float *)(object + 0x18);
    matrix[3].w = 1.0f;
    packet.color[3] = g_ring_l00_effect_color;
    packet.color[2] = g_ring_l00_effect_color;
    packet.color[1] = g_ring_l00_effect_color;
    packet.color[0] = g_ring_l00_effect_color;
    uv = &packet.uv[0][0];
    for (face = 0; face < 48; face++) {
        v = &packet.uv[0][1];
        u = uv;
        for (corner = 0; corner < 4; corner++) {
            vtx = g_ring_effect_face_indices[face][corner][0];
            index = g_ring_effect_face_indices[face][corner][1];
            FastVecScale(&packet.vertex[corner], &g_ring_effect_vertices[vtx], *(float *)(state + 0x64) * 2.0f);
            transform_vector(&packet.vertex[corner], &packet.vertex[corner], matrix);
            gfx_world_to_screen_unit(&packet.vertex[corner], &packet.uv[corner][0], &packet.uv[corner][1]);
            c = math_fast_sin_or_cos_a(g_ring_effect_angles[index][0]);
            delta = c * math_ease_out_quad((1.0f - *(float *)(state + 0x64) / g_ring_effect_duration) * 0.0125f);
            *u += delta;
            s = math_fast_sin_or_cos_b(g_ring_effect_angles[index][0]);
            scale = math_ease_out_quad((1.0f - *(float *)(state + 0x64) / g_ring_effect_duration) * 0.0125f);
            delta = -s;
            delta *= scale;
            *v += delta;
            if (*u > 1.0f) *u = 1.0f;
            else if (*u < 0.0f) *u = 0.0f;
            if (*v > 1.0f) *v = 1.0f;
            else if (*v < 0.0f) *v = 0.0f;
            v += 2;
            u += 2;
        }
        draw_world_quad(&packet, 0, 0);
    }
    for (face = 0; face < 98; face++)
        g_ring_effect_angles[face][0] = FastAddRotations(g_ring_effect_angles[face][0], g_ring_effect_angles[face][1]);
}
