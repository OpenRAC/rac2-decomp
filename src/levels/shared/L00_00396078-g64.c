#include "common.h"
typedef struct { float vertex[4][4]; int color[4]; float uv[8]; u64 primitive, texture, mode, flags; } BillboardPacket;
extern float g_flare_source_scale __attribute__((sda)), g_flare_axis_scale __attribute__((sda));
extern int g_flare_color_default __attribute__((sda)), g_flare_color_alt __attribute__((sda)), g_flare_l00_texture_id __attribute__((sda));
extern float g_flare_source_matrix[4][4] __attribute__((sda));
extern float g_arc_fade_scale MACRO_ADDR;
extern char g_camera_l00_position[];
extern float g_hero_state_block[4];
extern void FastVecScale(void *, void *, float), FastVecAdd(void *, void *, void *);
extern u64 GetEffectTextureDescriptor(s32);
extern s32 math_random_int_below(s32);
extern float IntToFloat(s32);
extern int FloatToInt(float);
extern void FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float), FastVecCross(void *, void *, void *);
extern void transform_vector(void *, void *, void *), draw_world_quad(void *, void *, int);
/* Builds a camera-facing quad around a point on the actor's local axis. */
void gfx_l00_draw_billboard_flare(char *actor) {
    BillboardPacket packet;
    float basis[4][4], transformed[4], axisOffset[4], difference[4];
    int color, i;
    float alpha;
    float *source;
    float *vertex;
    FastVecScale(axisOffset, actor + 0xD0, g_flare_axis_scale);
    FastVecAdd(basis[3], axisOffset, actor + 0x10);
    packet.texture = GetEffectTextureDescriptor(g_flare_l00_texture_id);
    packet.flags = 0x8000000048ULL;
    packet.mode = 0xFF9000000260ULL;
    packet.primitive = 0;
    packet.uv[0] = 0; packet.uv[1] = 0; packet.uv[2] = 0; packet.uv[3] = 1;
    packet.uv[4] = 1; packet.uv[5] = 0; packet.uv[6] = 1; packet.uv[7] = 1;
    if (math_random_int_below(4) == 0) color = g_flare_color_alt;
    else color = g_flare_color_default;
    alpha = IntToFloat(color >> 24);
    color = (color & 0xFFFFFF) | (FloatToInt(alpha * g_arc_fade_scale) << 24);
    packet.color[0] = packet.color[1] = packet.color[2] = packet.color[3] = color;
    FastVecSub(difference, g_camera_l00_position, basis[3]);
    vec_scale_to_length(basis[0], difference, 1.0f);
    FastVecCross(basis[1], basis[0], g_hero_state_block);
    vec_scale_to_length(basis[1], basis[1], -1.0f);
    FastVecCross(basis[2], basis[1], basis[0]);
    FastVecScale(difference, basis[0], 0.2f);
    FastVecAdd(basis[3], basis[3], difference);
    source = g_flare_source_matrix[0];
    vertex = packet.vertex[0];
    for (i = 3; i >= 0; i--) {
        FastVecScale(transformed, source, g_flare_source_scale);
        source += 4;
        transform_vector(vertex, transformed, basis);
        vertex += 4;
    }
    draw_world_quad(&packet, 0, 0);
}
