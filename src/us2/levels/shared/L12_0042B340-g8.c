/* func_US2_L12_0042B340, the v2.00 copy of func_L12_00429ED8 (levels 12 and 17), unchanged. */
#include "common.h"

extern float D_L12_001B22EC __attribute__((sda));
extern float D_L12_001B22F0 __attribute__((sda));
extern float D_L12_001B22F4 __attribute__((sda));
extern float D_L12_001B22F8 __attribute__((sda));
extern u32 D_L12_001B22FC __attribute__((sda));
extern float D_L12_001B2300 __attribute__((sda));
extern u32 D_L12_001B2304 __attribute__((sda));
extern u32 D_L12_001B2308 __attribute__((sda));
extern u32 D_L12_001B230C __attribute__((sda));
extern u32 D_L12_001B2310 __attribute__((sda));
extern float D_L12_001B2314 __attribute__((sda));
extern float D_L12_001B2318 __attribute__((sda));
extern float D_L12_001B231C __attribute__((sda));
extern u32 D_L12_001B2320 __attribute__((sda));
extern u32 D_L12_001B2324 __attribute__((sda));
extern u32 D_L12_001B2330 __attribute__((sda));
extern u32 D_L12_001B2334 __attribute__((sda));
extern u32 D_L12_001B2338 __attribute__((sda));
extern u32 D_L12_001B233C __attribute__((sda));
extern u32 D_L12_001B2340 __attribute__((sda));
extern u32 D_L12_001B2344 __attribute__((sda));
extern u32 D_L12_001B2348 __attribute__((sda));
extern u32 D_L12_001B234C __attribute__((sda));
extern u32 D_L12_001B2350 __attribute__((sda));
extern u32 D_L12_001B2354 __attribute__((sda));
extern u32 D_L12_001B2358 __attribute__((sda));
extern u32 D_L12_001B2360 __attribute__((sda));
extern u32 D_L12_001B2364 __attribute__((sda));
extern u32 D_L12_001B2368 __attribute__((sda));
extern u32 D_L12_001B2370 __attribute__((sda));
extern u32 D_L12_001B2374 __attribute__((sda));
extern u32 D_L12_001B2378 __attribute__((sda));
extern float D_L12_001B2380 __attribute__((sda));
extern float D_L12_001B2384 __attribute__((sda));
extern char D_L12_001B9E00[];
extern float D_L12_001B238C[];
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

void func_US2_L12_0042B340(int unused0, int unused1, int unused2, int unused3,
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
    gfx_init_quad_packet_state(&quad, D_L12_001B2320, 1, 0x80);
    vertices = quad.vertices[1];
    u = quad.tex.uv;
    v = quad.tex.uv + 1;
    quad.colors[1] = D_L12_001B233C << 24;
    quad.colors[1] |= D_L12_001B2338 << 16;
    quad.colors[1] |= D_L12_001B2334 << 8;
    quad.colors[1] |= D_L12_001B2330;
    quad.colors[3] = D_L12_001B234C << 24;
    quad.colors[3] |= D_L12_001B2348 << 16;
    quad.colors[3] |= D_L12_001B2344 << 8;
    quad.colors[3] |= D_L12_001B2340;
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
    FastVecSub(delta, obj + 0x10, D_L12_001B9E00);
    vec_scale_to_length(offset, state, -D_L12_001B2318);
    FastVecAdd(center, obj + 0x10, offset);
    FastVecCross(width, delta, offset);
    vec_scale_to_length(width, width, D_L12_001B22F8);
    vec_scale_to_length(base, state, D_L12_001B238C[0]);
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
    vec_scale_to_length(offset, state, -D_L12_001B231C);
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
    state->angle = FastAddRotations(state->angle, D_L12_001B2314 * 0.017453294f);
    gfx_init_quad_packet_state(&quad, D_L12_001B2324, 1, 0x80);
    quad.colors[1] = D_L12_001B2308 << 24;
    quad.colors[1] |= D_L12_001B2358 << 16;
    quad.colors[1] |= D_L12_001B2354 << 8;
    quad.colors[1] |= D_L12_001B2350;
    quad.colors[3] = D_L12_001B2368 << 16;
    quad.colors[3] |= D_L12_001B2364 << 8;
    quad.colors[3] |= D_L12_001B2360;
    quad.flags = 5;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L12_001B22EC);
    vec_scale_to_length(base, state, D_L12_001B238C[0]);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = D_L12_001B2308 << 24;
    quad.colors[1] |= D_L12_001B2358 << 16;
    quad.colors[1] |= D_L12_001B2354 << 8;
    quad.colors[1] |= D_L12_001B2350;
    quad.colors[3] = D_L12_001B2368 << 16;
    quad.colors[3] |= D_L12_001B2364 << 8;
    quad.colors[3] |= D_L12_001B2360;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L12_001B22F0);
    vec_scale_to_length(base, state, D_L12_001B2380);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = D_L12_001B2310 << 24;
    quad.colors[1] |= D_L12_001B2358 << 16;
    quad.colors[1] |= D_L12_001B2354 << 8;
    quad.colors[1] |= D_L12_001B2350;
    quad.colors[3] = D_L12_001B2368 << 16;
    quad.colors[3] |= D_L12_001B2364 << 8;
    quad.colors[3] |= D_L12_001B2360;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L12_001B22F4);
    vec_scale_to_length(base, state, D_L12_001B2380);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    quad.colors[1] = D_L12_001B230C << 24;
    quad.colors[1] |= D_L12_001B2378 << 16;
    quad.colors[1] |= D_L12_001B2374 << 8;
    quad.colors[1] |= D_L12_001B2370;
    quad.colors[3] = D_L12_001B2368 << 16;
    quad.colors[3] |= D_L12_001B2364 << 8;
    quad.colors[3] |= D_L12_001B2360;
    quad.colors[0] = quad.colors[1];
    quad.colors[2] = quad.colors[3];
    vec_scale_to_length(width, width, D_L12_001B22EC);
    vec_scale_to_length(base, state, D_L12_001B2384);
    FastVecAdd(base, obj + 0x10, base);
    FastVecAdd(quad.vertices[0], base, width);
    FastVecSub(vertices, base, width);
    vec_scale_to_length(offset, state, -0.6f);
    FastVecAdd(center, base, offset);
    FastVecAdd(center, center, offset);
    FastVecAdd(quad.vertices[2], center, width);
    FastVecSub(quad.vertices[3], center, width);
    draw_world_quad(&quad, 0, 0);
    gfx_draw_billboard_quad(obj + 0x10, D_L12_001B22FC, D_L12_001B2304, 1,
                   D_L12_001B2300, 0.08f, math_random_angle());
    glow = D_L12_001B2300;
    glow *= 0.4f;
    gfx_draw_billboard_quad(obj + 0x10, D_L12_001B22FC, 0x80808080, 1,
                   glow, 0.08f, math_random_angle());
}
