#include "common.h"
struct EffectQuad { float position[4][4]; u32 color[4]; float uv[4][2]; u64 clear, texture, giftag, flags; };
extern float g_hero_l11_state_block[];
extern int g_glow_flare_disabled __attribute__((sda));
extern u32 g_glow_flare_sprite_a __attribute__((sda));
extern u32 g_glow_flare_sprite_b __attribute__((sda));
extern float g_glow_flare_size_a __attribute__((sda));
extern float g_glow_flare_size_b __attribute__((sda));
extern int g_glow_flare_color_a __attribute__((sda));
extern int g_glow_flare_color_b __attribute__((sda));
extern float g_glow_flare_distance __attribute__((sda));
extern void ref_L11_004507B0_00(char *);
extern long long GetEffectTextureDescriptor(int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(char *, float *);
extern void euler_to_matrix(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_l11_scale_four(char *, float);
extern void draw_world_quad(void *, void *, int);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_draw_billboard_quad(void *, u32, int, int, float, float, float);

/* Draws one glowing sprite at a position, facing the camera, and adds light flares behind it. */
void part_draw_glow_sprite_flares(void *position, u32 color, float size, int alpha, float roll, int texture, int flags, float offset, void *owner) {
    struct EffectQuad quad;
    float matrix[16], rotation[4], toward[4], light[4];
    char *object = owner;
    char *vars = *(char **)(object + 0x68);
    float *point = position;
    
    u32 packed_color;
    ref_L11_004507B0_00((char *)&quad);
    quad.texture = GetEffectTextureDescriptor(texture);
    quad.giftag = 0xFF9000000260ULL;
    quad.flags = ((u64)flags << 2) | 0x8000000040ULL;
    packed_color = color + (alpha << 24);
    quad.color[3] = packed_color;
    quad.color[2] = packed_color;
    quad.color[1] = packed_color;
    quad.color[0] = packed_color;
    quad.clear = 0;
    
    rotation[3] = 0.0f;
    rotation[2] = mat_fast_helper_a(g_hero_l11_state_block[0x50] - point[0], g_hero_l11_state_block[0x51] - point[1]);
    rotation[1] = -mat_fast_helper_a(vec_distance_xy(position, g_hero_l11_state_block + 0x50), g_hero_l11_state_block[0x52] - point[2]);
    rotation[0] = roll;
    euler_to_matrix(matrix, rotation);
    FastVecSub(toward, g_hero_l11_state_block + 0x50, position);
    vec_scale_to_length(toward, toward, offset);
    matrix[12] = point[0] + toward[0];
    matrix[13] = point[1] + toward[1];
    matrix[14] = point[2] + toward[2];
    matrix[15] = 1.0f;
    vec_l11_scale_four((char *)&quad, size);
    draw_world_quad(&quad, matrix, 0);
    if (g_glow_flare_disabled == 0) {
        vec_scale_to_length(light, vars, g_glow_flare_distance);
        FastVecAdd(light, object + 0x10, light);
        gfx_draw_billboard_quad(light, g_glow_flare_sprite_a, g_glow_flare_color_a, 1, g_glow_flare_size_a, 0.08f, 0.0f);
        vec_scale_to_length(light, vars, -0.03f);
        FastVecAdd(light, object + 0x10, light);
        gfx_draw_billboard_quad(light, g_glow_flare_sprite_b, g_glow_flare_color_b, 1, g_glow_flare_size_b, 0.08f, 0.0f);
    }
}
