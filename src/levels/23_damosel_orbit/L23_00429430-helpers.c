#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 corner[4];
    u32 rgba[4];
    float uv[4][2];
    s64 d70;
    s64 d78;
    s64 d80;
    s64 d88;
} L23Quad;

/* the beam's own variables (the object's +0x68 block) */
typedef struct {
    float dir[4];
    float pad10[3];
    float spin;
    float pad20[2];
    float scroll;
    s32 fade;
    float glow;
    float len;
    float back;
    float width;
} L23BeamVars;

extern float D_L23_001B1AF0 __attribute__((sda));
extern float D_L23_001B1AF4 __attribute__((sda));
extern float D_L23_001B1AF8 __attribute__((sda));
extern float D_L23_001B1AFC __attribute__((sda));
extern s32 D_L23_001B1B00 __attribute__((sda));
extern float D_L23_001B1B04 __attribute__((sda));
extern u32 D_L23_001B1B08 __attribute__((sda));
extern s32 D_L23_001B1B0C __attribute__((sda));
extern s32 D_L23_001B1B10 __attribute__((sda));
extern s32 D_L23_001B1B14 __attribute__((sda));
extern float D_L23_001B1B18 __attribute__((sda));
extern float D_L23_001B1B1C __attribute__((sda));
extern float D_L23_001B1B20 __attribute__((sda));
extern s32 D_L23_001B1B24 __attribute__((sda));
extern s32 D_L23_001B1B28 __attribute__((sda));
extern s32 D_L23_001B1B34 __attribute__((sda));
extern s32 D_L23_001B1B38 __attribute__((sda));
extern s32 D_L23_001B1B3C __attribute__((sda));
extern s32 D_L23_001B1B40 __attribute__((sda));
extern s32 D_L23_001B1B44 __attribute__((sda));
extern s32 D_L23_001B1B48 __attribute__((sda));
extern s32 D_L23_001B1B4C __attribute__((sda));
extern s32 D_L23_001B1B50 __attribute__((sda));
extern s32 D_L23_001B1B54 __attribute__((sda));
extern s32 D_L23_001B1B58 __attribute__((sda));
extern s32 D_L23_001B1B5C __attribute__((sda));
extern s32 D_L23_001B1B60 __attribute__((sda));
extern s32 D_L23_001B1B64 __attribute__((sda));
extern s32 D_L23_001B1B68 __attribute__((sda));
extern s32 D_L23_001B1B6C __attribute__((sda));
extern s32 D_L23_001B1B70 __attribute__((sda));
extern s32 D_L23_001B1B74 __attribute__((sda));
extern s32 D_L23_001B1B78 __attribute__((sda));
extern s32 D_L23_001B1B7C __attribute__((sda));
extern s32 D_L23_001B1B80 __attribute__((sda));
extern float D_L23_001B1B84 __attribute__((sda));
extern float D_L23_001B1B88 __attribute__((sda));
extern float D_L23_001B1B90 NOT_SDA;
extern float g_camera_l23_position[];

extern void effect_init_transform_record(L23Quad *);
extern void gfx_init_quad_packet_state(L23Quad *, s32, s32, s32);
extern void draw_world_quad(L23Quad *, void *, s32);
extern void FastVecAdd(float *, float *, float *);
extern void FastVecSub(float *, float *, float *);
extern void FastVecCross(float *, float *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(u8 *, s32, u32, s32, float, float, float);

/* Draws a fading glowing beam with scrolling texture and a bright spot at its end. */
void gfx_draw_fading_glowing_beam(s32 unused0, s32 unused1, s32 unused2, s32 unused3, s32 unused4, u8 *obj) {
    L23Quad q;
    float vrel[4];
    float vaxis[4];
    float vtip[4];
    float vside[4];
    float vbase[4];
    float uvOffset[2];
    float *rel;
    float *axis;
    float *tip;
    float *side;
    float *base;
    L23BeamVars *vars;
    u8 *pos;
    s32 fadeValue;
    float angle;
    float sinAngle;
    float cosAngle;
    int i;
    int j;

    vars = *(L23BeamVars **)(obj + 0x68);
    fadeValue = vars->fade;
    D_L23_001B1B40 = fadeValue * 4;
    if (D_L23_001B1B40 != 0) {
        D_L23_001B1B40--;
    }
    D_L23_001B1B50 = fadeValue * 2;
    D_L23_001B1B60 = fadeValue;
    D_L23_001B1B70 = fadeValue;
    D_L23_001B1B80 = fadeValue;
    effect_init_transform_record(&q);
    pos = obj + 0x10;
    gfx_init_quad_packet_state(&q, D_L23_001B1B24, 1, 0x80);
    q.rgba[1] = (u32)D_L23_001B1B40 << 24;
    q.rgba[1] |= (u32)D_L23_001B1B3C << 16;
    q.rgba[1] |= (u32)D_L23_001B1B38 << 8;
    q.rgba[1] |= D_L23_001B1B34;
    q.rgba[3] = (u32)D_L23_001B1B50 << 24;
    q.rgba[3] |= (u32)D_L23_001B1B4C << 16;
    q.rgba[3] |= (u32)D_L23_001B1B48 << 8;
    q.rgba[3] |= D_L23_001B1B44;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    q.uv[0][0] = 0.0f;
    q.uv[0][1] = 0.0f;
    q.uv[1][0] = 0.0f;
    q.uv[1][1] = 1.0f;
    q.uv[2][0] = 1.0f;
    q.uv[2][1] = 0.0f;
    q.uv[3][0] = 1.0f;
    q.uv[3][1] = 1.0f;
    rel = vrel;
    axis = vaxis;
    tip = vtip;
    side = vside;
    base = vbase;
    for (i = 0; i < 4; i++) {
        q.uv[i][0] -= vars->scroll;
        if (q.uv[i][0] <= 7.0f) {
            q.uv[i][0] += 7.0f;
        }
    }
    vars->scroll += 0.1f;
    if (vars->scroll >= 4.0f) {
        vars->scroll -= 4.0f;
    }
    FastVecSub(rel, (float *)pos, g_camera_l23_position);
    vec_scale_to_length(axis, vars->dir, -D_L23_001B1B1C);
    FastVecAdd(tip, (float *)pos, axis);
    FastVecCross(side, rel, axis);
    vec_scale_to_length(side, side, D_L23_001B1AFC);
    vec_scale_to_length(base, vars->dir, D_L23_001B1B90);
    FastVecAdd(base, (float *)pos, base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub(((float *)&q.corner[1]), base, side);
    FastVecAdd(((float *)&q.corner[2]), tip, side);
    FastVecSub(((float *)&q.corner[3]), tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[0] = q.rgba[2];
    q.rgba[1] = q.rgba[3];
    q.rgba[3] = 0x801010;
    q.rgba[2] = 0x801010;
    qcopy(&q.corner[0],&q.corner[2]);
    qcopy(&q.corner[1],&q.corner[3]);
    FastVecAdd(((float *)&q.corner[2]), ((float *)&q.corner[2]), axis);
    FastVecAdd(((float *)&q.corner[3]), ((float *)&q.corner[3]), axis);
    draw_world_quad(&q, 0, 0);

    vec_scale_to_length(axis, vars->dir, -D_L23_001B1B20);
    q.uv[0][0] = 0.0f;
    q.uv[0][1] = 0.0f;
    q.uv[1][0] = 0.0f;
    q.uv[1][1] = 1.0f;
    q.uv[2][0] = 1.0f;
    q.uv[2][1] = 0.0f;
    q.uv[3][0] = 1.0f;
    q.uv[3][1] = 1.0f;
    angle = vars->spin;
    sinAngle = math_fast_sin_or_cos_a(angle);
    cosAngle = math_fast_sin_or_cos_b(angle);
    for (j = 0; j < 4; j++) {
        uvOffset[0] = q.uv[j][0] - 0.5f;
        uvOffset[1] = q.uv[j][1] - 0.5f;
        q.uv[j][0] = uvOffset[0] * sinAngle - uvOffset[1] * cosAngle;
        q.uv[j][1] = uvOffset[0] * cosAngle + uvOffset[1] * sinAngle;
        q.uv[j][0] += 0.5f;
        q.uv[j][1] += 0.5f;
    }
    vars->spin = FastAddRotations(vars->spin, D_L23_001B1B18 * 0.017453294f);
    gfx_init_quad_packet_state(&q, D_L23_001B1B28, 1, 0x80);
    q.d70 = 5;

    q.rgba[1] = (u32)D_L23_001B1B0C << 24;
    q.rgba[1] |= (u32)D_L23_001B1B5C << 16;
    q.rgba[1] |= (u32)D_L23_001B1B58 << 8;
    q.rgba[1] |= D_L23_001B1B54;
    q.rgba[3] = (u32)D_L23_001B1B6C << 16;
    q.rgba[3] |= (u32)D_L23_001B1B68 << 8;
    q.rgba[3] |= D_L23_001B1B64;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1AF0);
    vec_scale_to_length(base, vars->dir, D_L23_001B1B90);
    FastVecAdd(base, (float *)pos, base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub(((float *)&q.corner[1]), base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd(((float *)&q.corner[2]), tip, side);
    FastVecSub(((float *)&q.corner[3]), tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = (u32)D_L23_001B1B0C << 24;
    q.rgba[1] |= (u32)D_L23_001B1B5C << 16;
    q.rgba[1] |= (u32)D_L23_001B1B58 << 8;
    q.rgba[1] |= D_L23_001B1B54;
    q.rgba[3] = (u32)D_L23_001B1B6C << 16;
    q.rgba[3] |= (u32)D_L23_001B1B68 << 8;
    q.rgba[3] |= D_L23_001B1B64;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1AF4);
    vec_scale_to_length(base, vars->dir, D_L23_001B1B84);
    FastVecAdd(base, (float *)pos, base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub(((float *)&q.corner[1]), base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd(((float *)&q.corner[2]), tip, side);
    FastVecSub(((float *)&q.corner[3]), tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = (u32)D_L23_001B1B14 << 24;
    q.rgba[1] |= (u32)D_L23_001B1B5C << 16;
    q.rgba[1] |= (u32)D_L23_001B1B58 << 8;
    q.rgba[1] |= D_L23_001B1B54;
    q.rgba[3] = (u32)D_L23_001B1B6C << 16;
    q.rgba[3] |= (u32)D_L23_001B1B68 << 8;
    q.rgba[3] |= D_L23_001B1B64;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1AF8);
    vec_scale_to_length(base, vars->dir, D_L23_001B1B84);
    FastVecAdd(base, (float *)pos, base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub(((float *)&q.corner[1]), base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd(((float *)&q.corner[2]), tip, side);
    FastVecSub(((float *)&q.corner[3]), tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = (u32)D_L23_001B1B10 << 24;
    q.rgba[1] |= (u32)D_L23_001B1B7C << 16;
    q.rgba[1] |= (u32)D_L23_001B1B78 << 8;
    q.rgba[1] |= D_L23_001B1B74;
    q.rgba[3] = (u32)D_L23_001B1B6C << 16;
    q.rgba[3] |= (u32)D_L23_001B1B68 << 8;
    q.rgba[3] |= D_L23_001B1B64;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1AF0);
    vec_scale_to_length(base, vars->dir, D_L23_001B1B88);
    FastVecAdd(base, (float *)pos, base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub(((float *)&q.corner[1]), base, side);
    vec_scale_to_length(axis, vars->dir, -0.6f);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd(((float *)&q.corner[2]), tip, side);
    FastVecSub(((float *)&q.corner[3]), tip, side);
    draw_world_quad(&q, 0, 0);

    gfx_draw_billboard_quad(pos, D_L23_001B1B00, D_L23_001B1B08, 1, D_L23_001B1B04, 0.08f, math_random_angle());
    gfx_draw_billboard_quad(pos, D_L23_001B1B00, 0x80808080, 1, D_L23_001B1B04 * 0.4f, 0.08f, math_random_angle());
}
