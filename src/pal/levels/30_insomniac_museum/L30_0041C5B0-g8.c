/* func_PAL_L30_0041C5B0, the PAL copy of func_L30_00417120: the same C. */
#include "common.h"

extern float D_L30_001B1F10 __attribute__((sda));
extern float D_L30_001B1F14 __attribute__((sda));
extern float D_L30_001B1F18 __attribute__((sda));
extern float D_L30_001B1F1C __attribute__((sda));
extern u32 D_L30_001B1F20 __attribute__((sda));
extern float D_L30_001B1F24 __attribute__((sda));
extern u32 D_L30_001B1F28 __attribute__((sda));
extern u32 D_L30_001B1F2C __attribute__((sda));
extern u32 D_L30_001B1F30 __attribute__((sda));
extern u32 D_L30_001B1F34 __attribute__((sda));
extern float D_L30_001B1F38 __attribute__((sda));
extern float D_L30_001B1F3C __attribute__((sda));
extern float D_L30_001B1F40 __attribute__((sda));
extern u32 D_L30_001B1F44 __attribute__((sda));
extern u32 D_L30_001B1F48 __attribute__((sda));
extern u32 D_L30_001B1F54 __attribute__((sda));
extern u32 D_L30_001B1F58 __attribute__((sda));
extern u32 D_L30_001B1F5C __attribute__((sda));
extern u32 D_L30_001B1F60 __attribute__((sda));
extern u32 D_L30_001B1F64 __attribute__((sda));
extern u32 D_L30_001B1F68 __attribute__((sda));
extern u32 D_L30_001B1F6C __attribute__((sda));
extern u32 D_L30_001B1F70 __attribute__((sda));
extern u32 D_L30_001B1F74 __attribute__((sda));
extern u32 D_L30_001B1F78 __attribute__((sda));
extern u32 D_L30_001B1F7C __attribute__((sda));
extern u32 D_L30_001B1F84 __attribute__((sda));
extern u32 D_L30_001B1F88 __attribute__((sda));
extern u32 D_L30_001B1F8C __attribute__((sda));
extern u32 D_L30_001B1F94 __attribute__((sda));
extern u32 D_L30_001B1F98 __attribute__((sda));
extern u32 D_L30_001B1F9C __attribute__((sda));
extern float D_L30_001B1FA4 __attribute__((sda));
extern float D_L30_001B1FA8 __attribute__((sda));
extern char D_L30_001B9DC0[];
extern float D_L30_001B1FB0[];
extern void part_reset_quad_record_c(void *);
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

void func_PAL_L30_0041C5B0(int unused0, int unused1, int unused2, int unused3,
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
    part_reset_quad_record_c(&quad);
    gfx_init_quad_packet_state(&quad, D_L30_001B1F44, 1, 0x80);
    vertices = quad.vertices[1];
    u = quad.tex.uv;
    v = quad.tex.uv + 1;
    quad.colors[1] = D_L30_001B1F60 << 24;
    quad.colors[1] |= D_L30_001B1F5C << 16;
    quad.colors[1] |= D_L30_001B1F58 << 8;
    quad.colors[1] |= D_L30_001B1F54;
    quad.colors[3] = D_L30_001B1F70 << 24;
    quad.colors[3] |= D_L30_001B1F6C << 16;
    quad.colors[3] |= D_L30_001B1F68 << 8;
    quad.colors[3] |= D_L30_001B1F64;
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
    FastVecSub(delta, obj + 0x10, D_L30_001B9DC0);
    vec_scale_to_length(offset, state, -D_L30_001B1F3C);
    FastVecAdd(center, obj + 0x10, offset);
    FastVecCross(width, delta, offset);
    vec_scale_to_length(width, width, D_L30_001B1F1C);
    vec_scale_to_length(base, state, D_L30_001B1FB0[0]);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[0] = quad.colors[2];
    quad.colors[1] = quad.colors[3];
    quad.colors[2] = quad.colors[3] = 0x801010;
    qcopy(quad.vertices[0], quad.vertices[2]);
    qcopy(vertices, quad.vertices[3]);
    FastVecAdd(quad.vertices[2], quad.vertices[2], offset);
    FastVecAdd(quad.vertices[3], quad.vertices[3], offset);
    draw_world_quad(&quad, 0, 0);
    vec_scale_to_length(offset, state, -D_L30_001B1F40);
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
    state->angle = FastAddRotations(state->angle, D_L30_001B1F38 * 0.017453294f);
    gfx_init_quad_packet_state(&quad, D_L30_001B1F48, 1, 0x80);
    quad.colors[1] = D_L30_001B1F2C << 24;
    quad.colors[1] |= D_L30_001B1F7C << 16;
    quad.colors[1] |= D_L30_001B1F78 << 8;
    quad.colors[1] |= D_L30_001B1F74;
    quad.colors[3] = D_L30_001B1F8C << 16;
    quad.colors[3] |= D_L30_001B1F88 << 8;
    quad.colors[3] |= D_L30_001B1F84;
    quad.flags = 5;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L30_001B1F10);
    vec_scale_to_length(base, state, D_L30_001B1FB0[0]);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = D_L30_001B1F2C << 24;
    quad.colors[1] |= D_L30_001B1F7C << 16;
    quad.colors[1] |= D_L30_001B1F78 << 8;
    quad.colors[1] |= D_L30_001B1F74;
    quad.colors[3] = D_L30_001B1F8C << 16;
    quad.colors[3] |= D_L30_001B1F88 << 8;
    quad.colors[3] |= D_L30_001B1F84;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L30_001B1F14);
    vec_scale_to_length(base, state, D_L30_001B1FA4);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = D_L30_001B1F34 << 24;
    quad.colors[1] |= D_L30_001B1F7C << 16;
    quad.colors[1] |= D_L30_001B1F78 << 8;
    quad.colors[1] |= D_L30_001B1F74;
    quad.colors[3] = D_L30_001B1F8C << 16;
    quad.colors[3] |= D_L30_001B1F88 << 8;
    quad.colors[3] |= D_L30_001B1F84;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L30_001B1F18);
    vec_scale_to_length(base, state, D_L30_001B1FA4);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = D_L30_001B1F30 << 24;
    quad.colors[1] |= D_L30_001B1F9C << 16;
    quad.colors[1] |= D_L30_001B1F98 << 8;
    quad.colors[1] |= D_L30_001B1F94;
    quad.colors[3] = D_L30_001B1F8C << 16;
    quad.colors[3] |= D_L30_001B1F88 << 8;
    quad.colors[3] |= D_L30_001B1F84;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L30_001B1F10);
    vec_scale_to_length(base, state, D_L30_001B1FA8);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    vec_scale_to_length(offset, state, -0.6f);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    gfx_draw_billboard_quad(obj + 0x10, D_L30_001B1F20, D_L30_001B1F28, 1,
                   D_L30_001B1F24, 0.08f, math_random_angle());
    glow = D_L30_001B1F24;
    glow *= 0.4f;
    gfx_draw_billboard_quad(obj + 0x10, D_L30_001B1F20, 0x80808080, 1,
                   glow, 0.08f, math_random_angle());
}
