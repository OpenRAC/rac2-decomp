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
extern GlowVector g_sound_slot_origins[][4], g_sound_slot_target_positions[], g_glow_corner_table[4] __attribute__((sda));
extern GlowVector g_camera_l09_position[], g_hero_state_block[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern unsigned long long GetEffectTextureDescriptor(int);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern int level_is_resident_flag_clear(void);
extern void draw_world_quad(void *, int, int);

/* Draws the flickering glow at both ends of a beam, each with a bright core and a larger soft halo. */
void DrawDobboPairedGlowQuads(void *unused, int slot, int alpha)
{
    GlowPacket packet;
    GlowVector basis[3], position, jitter;
    unsigned color = ((alpha * 255 / 100) << 24) | 0xFFFFFF;
    float scale;
    int i;
    GlowVector *corner, *vertex;
    qcopy(&position, &g_sound_slot_origins[slot][0]);
    position.f[3] = 1.0f;
    FastVecSub(&basis[0], g_camera_l09_position, &position);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecCross(&basis[1], &basis[0], g_hero_state_block);
    vec_scale_to_length(&basis[1], &basis[1], -1.0f);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    packet.texture = GetEffectTextureDescriptor(11);
    packet.blend = 0xFF00000044ULL;
    packet.mode = 0xFF9000000260ULL;
    packet.flags = 5;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    packet.uv[0][0] = 0; packet.uv[0][1] = 0; packet.uv[1][0] = 0; packet.uv[1][1] = 1;
    packet.uv[2][0] = 1; packet.uv[2][1] = 0; packet.uv[3][0] = 1; packet.uv[3][1] = 1;
    scale = math_random_float_range(0.3f, 0.325f);
    if (!level_is_resident_flag_clear())
        scale = 0.3125f;
    jitter.f[0] = math_random_signed_float_range(0, 0.05f);
    jitter.f[1] = math_random_signed_float_range(0, 0.05f);
    jitter.f[2] = math_random_signed_float_range(0, 0.05f);
    if (!level_is_resident_flag_clear()) {
        jitter.f[0] = 0.025f;
        jitter.f[1] = 0.025f;
        jitter.f[2] = 0.025f;
    }
    for (i = 0; i < 4; i++) {
        FastVecScale(&packet.vertex[i], &g_glow_corner_table[i], scale);
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
        for (corner = g_glow_corner_table, j = 3; j >= 0; j--) {
            FastVecScale(vertex, corner, scale * 3.0f);
            corner++;
            transform_vector(vertex, vertex, basis);
            vertex++;
        }
    }
    draw_world_quad(&packet, 0, 0);
    qcopy(&position, &g_sound_slot_target_positions[slot]);
    FastVecSub(&basis[0], g_camera_l09_position, &position);
    vec_scale_to_length(&basis[0], &basis[0], 1.0f);
    FastVecCross(&basis[1], &basis[0], g_hero_state_block);
    vec_scale_to_length(&basis[1], &basis[1], -1.0f);
    FastVecCross(&basis[2], &basis[1], &basis[0]);
    scale = math_random_float_range(0.3f, 0.325f);
    if (!level_is_resident_flag_clear())
        scale = 0.3125f;
    packet.blend = 0xFF00000044ULL;
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    {
        int j;
        corner = g_glow_corner_table;
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
        for (corner = g_glow_corner_table, j = 3; j >= 0; j--) {
            FastVecScale(vertex, corner, scale * 3.0f);
            corner++;
            transform_vector(vertex, vertex, basis);
            vertex++;
        }
    }
    draw_world_quad(&packet, 0, 0);
}
