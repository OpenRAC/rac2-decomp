#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { Vec pos[4]; u32 color[4]; float uv[4][2]; u64 gs[4]; } Quad;
extern u64 GetEffectTextureDescriptor(int);
extern float math_fast_float_g(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern u32 FastTweenColor(u32, u32, float);
extern void draw_world_quad(Quad *, int, int);
extern char *g_path_l11_table[] NOT_SDA;
extern s32 g_quad_gs_lo_bits_b[] __attribute__((sda));
extern s32 g_quad_gs_lo_bits_c[] __attribute__((sda));
extern s32 g_quad_gs_lo_bits_d[] __attribute__((sda));
extern s32 g_quad_gs_lo_bits_e[] __attribute__((sda));
extern s32 g_quad_gs_lo_bits_f[] __attribute__((sda));
extern s32 g_effect_l11_texture_id __attribute__((sda));
extern float g_quad_uv_v_corner_d[] __attribute__((sda));
extern s32 g_quad_gs_lo_bits_a __attribute__((sda));
extern s32 g_effect_quad_gs_bits_b __attribute__((sda));
extern s32 g_effect_quad_gs_bits_a __attribute__((sda));
extern s32 g_effect_quad_gs_bits_c __attribute__((sda));
extern s32 g_effect_quad_gs_bits_d __attribute__((sda));
extern s32 g_effect_quad_gs_bits_e __attribute__((sda));
extern float g_quad_height_min[] __attribute__((sda));
extern float g_quad_uv_v_corner_a[] __attribute__((sda));
extern float g_quad_uv_v_corner_b[] __attribute__((sda));
extern float g_quad_uv_v_corner_c[] __attribute__((sda));
extern float g_quad_min_progress __attribute__((sda));
extern float g_ribbon_scale_target_a __attribute__((sda));
extern float g_quad_height_max __attribute__((sda));
extern float g_quad_l11_depth __attribute__((sda));
extern float g_quad_wave_amplitude __attribute__((sda));
extern s32 g_effect_tex_color_table[2] __attribute__((sda));
extern float g_quad_uv_corner_table[4][2] __attribute__((sda));
/* Draws the ribbon along the stored points, with two scrolling texture layers. */
void DrawPointLoopRibbon(char *moby) {
    Quad quad;
    u32 mask;
    int i, j;
    int next_i;
    float *pos1, *pos2, *pos3;
    char *state = *(char **)(moby + 0x68);
    char *points;
    float height;
    float depth;
    if (*(float *)(state + 0x1BC) < g_quad_min_progress) return;
    quad.gs[1] = GetEffectTextureDescriptor(g_effect_l11_texture_id);
    pos1 = quad.pos[1];
    pos2 = quad.pos[2];
    pos3 = quad.pos[3];
    quad.gs[2] = 0xFF9000000260ULL;
    quad.gs[0] = g_quad_gs_lo_bits_a | ((u64)g_quad_gs_lo_bits_b[0] << 2);
    quad.gs[0] |= (u64)g_quad_gs_lo_bits_c[0] << 4;
    quad.gs[0] |= (u64)g_quad_gs_lo_bits_d[0] << 14;
    quad.gs[0] |= (u64)g_quad_gs_lo_bits_e[0] << 24;
    quad.gs[0] |= (u64)g_quad_gs_lo_bits_f[0] << 34;
    quad.gs[3] = g_effect_quad_gs_bits_a | ((u64)g_effect_quad_gs_bits_b << 2);
    quad.gs[3] |= (u64)g_effect_quad_gs_bits_c << 4;
    quad.gs[3] |= (u64)g_effect_quad_gs_bits_d << 6;
    quad.gs[3] |= (u64)g_effect_quad_gs_bits_e << 32;
    height = g_quad_height_min[0] + (g_quad_height_max - g_quad_height_min[0]) *
        (*(float *)(state + 0x1BC) / g_ribbon_scale_target_a);
    points = g_path_l11_table[*(int *)(state + 0x1C8)];
    for (i = 0; i < *(int *)points - 1; i = next_i) {
        mask = 0xFFFFFF;
        qcopy(quad.pos[0], points + (i * 16 + 0x20));
        depth = g_quad_l11_depth;
        quad.pos[0][2] -= depth;
        qcopy(pos1, points + (i * 16 + 0x10));
        quad.pos[1][2] -= depth;
        qcopy(pos2, points + (i * 16 + 0x20));
        quad.pos[2][2] += height + g_quad_wave_amplitude * math_fast_sin_or_cos_a(math_fast_float_g(quad.pos[0][1]));
        qcopy(pos3, points + (i * 16 + 0x10));
        next_i = i + 1;
        quad.pos[3][2] += height + g_quad_wave_amplitude * math_fast_sin_or_cos_a(math_fast_float_g(quad.pos[1][1]));
        quad.uv[0][1] = g_quad_uv_v_corner_a[0];
        quad.uv[1][1] = g_quad_uv_v_corner_b[0];
        quad.uv[2][1] = g_quad_uv_v_corner_c[0];
        quad.uv[3][1] = g_quad_uv_v_corner_d[0];
        for (j = 0; j < 4; j++) {
            int index = FloatToInt(quad.uv[j][1] + 0.2f);
            float alpha;
            u32 tex_color;
            quad.uv[j][0] = g_quad_uv_corner_table[j][0] + *(float *)(state + 0xD8);
            alpha = math_fast_sin_or_cos_b(*(float *)(state + 0xD0) * 3.1415927410125732f);
            tex_color = g_effect_tex_color_table[index];
            quad.color[j] = FastTweenColor(tex_color & mask, tex_color, alpha);
        }
        draw_world_quad(&quad, 0, 0);
        for (j = 0; j < 4; j++) {
            int index = FloatToInt(quad.uv[j][1] + 0.2f);
            float alpha;
            u32 tex_color;
            quad.uv[j][0] = g_quad_uv_corner_table[j][0] + *(float *)(state + 0xDC);
            alpha = math_fast_sin_or_cos_b(*(float *)(state + 0xD4) * 3.1415927410125732f);
            tex_color = g_effect_tex_color_table[index];
            quad.color[j] = FastTweenColor(tex_color & 0xFFFFFF, tex_color, alpha);
        }
        draw_world_quad(&quad, 0, 0);
    }
    qcopy(quad.pos[0], points + 0x10);
    depth = g_quad_l11_depth;
    quad.pos[0][2] -= depth;
    qcopy(pos1, points + (*(int *)points * 16));
    quad.pos[1][2] -= depth;
    qcopy(pos2, points + 0x10);
    quad.pos[2][2] += height + g_quad_wave_amplitude * math_fast_sin_or_cos_a(math_fast_float_g(quad.pos[0][1]));
    qcopy(pos3, points + (*(int *)points * 16));
    quad.pos[3][2] += height + g_quad_wave_amplitude * math_fast_sin_or_cos_a(math_fast_float_g(quad.pos[1][1]));
    quad.uv[0][1] = g_quad_uv_v_corner_a[0];
    quad.uv[1][1] = g_quad_uv_v_corner_b[0];
    quad.uv[2][1] = g_quad_uv_v_corner_c[0];
    quad.uv[3][1] = g_quad_uv_v_corner_d[0];
    for (j = 0; j < 4; j++) {
        int index = FloatToInt(quad.uv[j][1] + 0.2f);
        float alpha;
        u32 tex_color;
        quad.uv[j][0] = g_quad_uv_corner_table[j][0] + *(float *)(state + 0xD8);
        alpha = math_fast_sin_or_cos_b(*(float *)(state + 0xD0) * 3.1415927410125732f);
        tex_color = g_effect_tex_color_table[index];
        quad.color[j] = FastTweenColor(tex_color & 0xFFFFFF, tex_color, alpha);
    }
    draw_world_quad(&quad, 0, 0);
    for (j = 0; j < 4; j++) {
        int index = FloatToInt(quad.uv[j][1] + 0.2f);
        float alpha;
        u32 tex_color;
        quad.uv[j][0] = g_quad_uv_corner_table[j][0] + *(float *)(state + 0xDC);
        alpha = math_fast_sin_or_cos_b(*(float *)(state + 0xD4) * 3.1415927410125732f);
        tex_color = g_effect_tex_color_table[index];
        quad.color[j] = FastTweenColor(tex_color & 0xFFFFFF, tex_color, alpha);
    }
    draw_world_quad(&quad, 0, 0);
}
