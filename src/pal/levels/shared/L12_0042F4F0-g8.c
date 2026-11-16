#include "names.h"
/* func_PAL_L12_0042F4F0, the PAL copy of func_L12_00429ED8 (levels 12 and 17). */
#include "common.h"

extern float g_laser_beam_width_a __attribute__((sda));
extern float g_laser_beam_width_b __attribute__((sda));
extern float g_laser_beam_width_c __attribute__((sda));
extern float g_laser_beam_width_d __attribute__((sda));
extern u32 g_laser_billboard_texture __attribute__((sda));
extern float g_laser_glow_size __attribute__((sda));
extern u32 g_laser_billboard_color __attribute__((sda));
extern u32 g_laser_alpha_a __attribute__((sda));
extern u32 g_laser_alpha_b __attribute__((sda));
extern u32 g_laser_alpha_c __attribute__((sda));
extern float g_laser_spin_degrees __attribute__((sda));
extern float g_laser_offset_a __attribute__((sda));
extern float g_laser_offset_b __attribute__((sda));
extern u32 g_laser_quad_state_a __attribute__((sda));
extern u32 g_laser_quad_state_b __attribute__((sda));
extern u32 g_laser_color_a_red __attribute__((sda));
extern u32 g_laser_color_a_green __attribute__((sda));
extern u32 g_laser_color_a_blue __attribute__((sda));
extern u32 g_laser_color_a_alpha __attribute__((sda));
extern u32 g_laser_color_b_red __attribute__((sda));
extern u32 g_laser_color_b_green __attribute__((sda));
extern u32 g_laser_color_b_blue __attribute__((sda));
extern u32 g_laser_color_b_alpha __attribute__((sda));
extern u32 g_laser_color_c_red __attribute__((sda));
extern u32 g_laser_color_c_green __attribute__((sda));
extern u32 g_laser_color_c_blue __attribute__((sda));
extern u32 g_laser_color_d_red __attribute__((sda));
extern u32 g_laser_color_d_green __attribute__((sda));
extern u32 g_laser_color_d_blue __attribute__((sda));
extern u32 g_laser_color_e_red __attribute__((sda));
extern u32 g_laser_color_e_green __attribute__((sda));
extern u32 g_laser_color_e_blue __attribute__((sda));
extern float g_laser_base_length_a __attribute__((sda));
extern float g_laser_base_length_b __attribute__((sda));
extern char g_hero_prev_position[];
extern float g_laser_base_length_c[];
extern void ref_L12_00429ED8_00(void *);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void draw_world_quad(void *, int, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);

typedef struct {
    float vertices[4][4];
    u32 colors[4];
    union { float uv[8]; u32 bits[8]; } tex;
    u64 flags;
    char pad[0x18];
} RenderQuad;

typedef struct {
    float direction[4];
    float pad10[3];
    float angle;
    float pad20[2];
    float scroll;
} BeamState;

void gfx_draw_laser_beam_pal(int unused0, int unused1, int unused2, int unused3,
                      int unused4, char *obj)
{
    RenderQuad quad;
    float delta[4], offset[4], center[4], width[4], base[4], temp[4];
    BeamState *state = *(BeamState **)(obj + 0x68);
    float *vertices;
    float *u;
    float *v;
    float angle, cosine, sine, glow;
    int i, j;
    ref_L12_00429ED8_00(&quad);
    gfx_init_quad_packet_state(&quad, g_laser_quad_state_a, 1, 0x80);
    vertices = quad.vertices[1];
    u = quad.tex.uv;
    v = quad.tex.uv + 1;
    quad.colors[1] = g_laser_color_a_alpha << 24;
    quad.colors[1] |= g_laser_color_a_blue << 16;
    quad.colors[1] |= g_laser_color_a_green << 8;
    quad.colors[1] |= g_laser_color_a_red;
    quad.colors[3] = g_laser_color_b_alpha << 24;
    quad.colors[3] |= g_laser_color_b_blue << 16;
    quad.colors[3] |= g_laser_color_b_green << 8;
    quad.colors[3] |= g_laser_color_b_red;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    quad.tex.bits[0] = 0;
    quad.tex.bits[1] = 0;
    quad.tex.bits[2] = 0;
    quad.tex.uv[3] = 1;
    quad.tex.uv[4] = 1;
    quad.tex.bits[5] = 0;
    quad.tex.uv[6] = 1;
    quad.tex.uv[7] = 1;
    {
        float *p = u;
        for (i = 3; i >= 0; i--) {
            *p -= state->scroll;
            if (*p <= 7.0f)
                *p += 7.0f;
            p += 2;
        }
    }
    state->scroll += 0.1f;
    if (state->scroll >= 4.0f)
        state->scroll -= 4.0f;
    FastVecSub(delta, obj + 0x10, g_hero_prev_position);
    vec_scale_to_length(offset, state, -g_laser_offset_a);
    FastVecAdd(center, obj + 0x10, offset);
    FastVecCross(width, delta, offset);
    vec_scale_to_length(width, width, g_laser_beam_width_d);
    vec_scale_to_length(base, state, g_laser_base_length_c[0]);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[0] = quad.colors[2];
    quad.colors[1] = quad.colors[3];
    quad.colors[2] = quad.colors[3] = 0x202020;
    qcopy(quad.vertices[0], quad.vertices[2]);
    qcopy(vertices, quad.vertices[3]);
    FastVecAdd(quad.vertices[2], quad.vertices[2], offset);
    FastVecAdd(quad.vertices[3], quad.vertices[3], offset);
    draw_world_quad(&quad, 0, 0);
    vec_scale_to_length(offset, state, -g_laser_offset_b);
    quad.tex.bits[0] = 0;
    quad.tex.bits[1] = 0;
    quad.tex.bits[2] = 0;
    quad.tex.uv[3] = 1;
    quad.tex.uv[4] = 1;
    quad.tex.bits[5] = 0;
    quad.tex.uv[6] = 1;
    quad.tex.uv[7] = 1;
    angle = state->angle;
    cosine = math_fast_sin_or_cos_a(angle);
    sine = math_fast_sin_or_cos_b(angle);
    {
        float *q = v;
        float *p = u;
        for (j = 3; j >= 0; j--) {
            temp[0] = *p - 0.5f;
            temp[1] = *q - 0.5f;
            *p = temp[0] * cosine - temp[1] * sine;
            *q = temp[0] * sine + temp[1] * cosine;
            *p += 0.5f;
            *q += 0.5f;
            p += 2;
            q += 2;
        }
    }
    state->angle = FastAddRotations(state->angle, g_laser_spin_degrees * 0.017453294f);
    gfx_init_quad_packet_state(&quad, g_laser_quad_state_b, 1, 0x80);
    quad.colors[1] = g_laser_alpha_a << 24;
    quad.colors[1] |= g_laser_color_c_blue << 16;
    quad.colors[1] |= g_laser_color_c_green << 8;
    quad.colors[1] |= g_laser_color_c_red;
    quad.colors[3] = g_laser_color_d_blue << 16;
    quad.colors[3] |= g_laser_color_d_green << 8;
    quad.colors[3] |= g_laser_color_d_red;
    quad.flags = 5;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, g_laser_beam_width_a);
    vec_scale_to_length(base, state, g_laser_base_length_c[0]);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = g_laser_alpha_a << 24;
    quad.colors[1] |= g_laser_color_c_blue << 16;
    quad.colors[1] |= g_laser_color_c_green << 8;
    quad.colors[1] |= g_laser_color_c_red;
    quad.colors[3] = g_laser_color_d_blue << 16;
    quad.colors[3] |= g_laser_color_d_green << 8;
    quad.colors[3] |= g_laser_color_d_red;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, g_laser_beam_width_b);
    vec_scale_to_length(base, state, g_laser_base_length_a);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = g_laser_alpha_c << 24;
    quad.colors[1] |= g_laser_color_c_blue << 16;
    quad.colors[1] |= g_laser_color_c_green << 8;
    quad.colors[1] |= g_laser_color_c_red;
    quad.colors[3] = g_laser_color_d_blue << 16;
    quad.colors[3] |= g_laser_color_d_green << 8;
    quad.colors[3] |= g_laser_color_d_red;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, g_laser_beam_width_c);
    vec_scale_to_length(base, state, g_laser_base_length_a);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = g_laser_alpha_b << 24;
    quad.colors[1] |= g_laser_color_e_blue << 16;
    quad.colors[1] |= g_laser_color_e_green << 8;
    quad.colors[1] |= g_laser_color_e_red;
    quad.colors[3] = g_laser_color_d_blue << 16;
    quad.colors[3] |= g_laser_color_d_green << 8;
    quad.colors[3] |= g_laser_color_d_red;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, g_laser_beam_width_a);
    vec_scale_to_length(base, state, g_laser_base_length_b);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    vec_scale_to_length(offset, state, -0.6f);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    gfx_draw_billboard_quad(obj + 0x10, g_laser_billboard_texture, g_laser_billboard_color, 1,
                   g_laser_glow_size, 0.08f, math_random_angle());
    glow = g_laser_glow_size;
    glow *= 0.4f;
    gfx_draw_billboard_quad(obj + 0x10, g_laser_billboard_texture, 0x80808080, 1,
                   glow, 0.08f, math_random_angle());
}
