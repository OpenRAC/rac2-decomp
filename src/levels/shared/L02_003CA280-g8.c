#include "common.h"

typedef unsigned long long U64;
typedef int TI128 __attribute__((mode(TI)));
struct Vertex { float x, y, z, w; };
struct Packet { struct Vertex vertices[4]; int colors[4]; float uv[8]; U64 tag, texture, mode, state; };
/* The effect's tuning block: a member at its start is read as an absolute macro load. */
struct Tuning {
    float rates[2];
    float speed[2];
    int alpha[2];
    int colors[2];
    float sizes[2];
    float spin[2];
    int texture;
    int blend[2];
    int pad;
    float uvs[8];
    float pad2[2];
    struct Vertex vertices[4];
    int fade[3];
};
extern struct Tuning g_glow_effect_params[] __attribute__((sda));
extern float g_scratch_floats[];
extern float g_effect_scale_offset __attribute__((sda)), g_effect_depth_scale __attribute__((sda));
extern int g_effect_fade_color __attribute__((sda));
extern struct Vertex g_effect_quad_vertices[] SDATA(D_L02_001B0020);
extern float g_effect_quad_us[] SDATA(D_L02_001AFFF8);
extern float g_effect_quad_vs[] __attribute__((sda));
extern int g_effect_l02_texture_id __attribute__((sda)), g_effect_state_a __attribute__((sda)), g_effect_state_b __attribute__((sda));
extern void euler_to_matrix(void *, void *), FastVecScale(void *, void *, float), draw_world_quad(void *, void *, int);
extern int FastTweenColor(int, int, float);
extern U64 GetEffectTextureDescriptor(int);

/* Draws the effect's quad twice, scaled by the two timers and faded through three colours. */
void DrawEffectQuad(char *obj)
{
    struct Packet packet;
    float matrix[16] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    char *data;
    float a, b, c;
    int color, i;
    float *us, *vs;
    *(TI128 *)temp = 0;
    temp[2] = g_scratch_floats[0];
    data = *(char **)(obj + 0x68);
    *(TI128 *)angles = *(TI128 *)temp;
    euler_to_matrix(matrix, angles);
    a = *(float *)(data + 8);
    b = (1.0f - a) * g_effect_scale_offset + 1.0f;
    c = g_effect_depth_scale * *(float *)(data + 12);
    a += c;
    b += c;
    FastVecScale(matrix, matrix, a);
    FastVecScale(matrix + 4, matrix + 4, a);
    FastVecScale(matrix + 8, matrix + 8, b);
    qcopy(matrix + 12, obj + 0x10);
    matrix[14] -= g_effect_depth_scale * *(float *)(data + 12) * 0.5f;
    matrix[15] = 1.0f;
    if (*(float *)(data + 8) < 1.0f)
        color = FastTweenColor(g_effect_fade_color, g_glow_effect_params[0].fade[1], *(float *)(data + 8));
    else
        color = FastTweenColor(g_glow_effect_params[0].fade[1], g_glow_effect_params[0].fade[2], *(float *)(data + 12));
    us = packet.uv;
    vs = packet.uv + 1;
    for (i = 0; i < 4; i++) {
        packet.colors[i] = color;
        us[i * 2] = g_effect_quad_us[i * 2];
        vs[i * 2] = g_effect_quad_vs[i * 2];
        qcopy(&packet.vertices[i], &g_effect_quad_vertices[i]);
    }
    packet.texture = GetEffectTextureDescriptor(g_effect_l02_texture_id);
    packet.mode = 0xFF9000000260ULL;
    packet.tag = 5;
    packet.state = ((U64)g_effect_state_a << 2) | ((U64)g_effect_state_b << 6) | 0x8000000000ULL;
    draw_world_quad(&packet, matrix, 1);
    draw_world_quad(&packet, matrix, 1);
}
