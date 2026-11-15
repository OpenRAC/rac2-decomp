#include "common.h"

/* Draw six beam quads and two endpoint glows from the object's beam state.
 * The object pointer occupies the sixth integer argument slot. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 corner[4];
    s32 rgba[4];
    float uv[4][2];
    s64 d70;
    s64 d78;
    s64 d80;
    s64 d88;
} L23Quad;

/* the beam's own variables (the object's +0x68 block) */
typedef struct {
    float dir[4] __attribute__((aligned(16)));
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

extern float D_L23_001B1A4C __attribute__((sda));
extern float D_L23_001B1A50 __attribute__((sda));
extern float D_L23_001B1A54 __attribute__((sda));
extern s32 D_L23_001B1A58 __attribute__((sda));
extern u32 D_L23_001B1A5C __attribute__((sda));
extern s32 D_L23_001B1A60 __attribute__((sda));
extern s32 D_L23_001B1A64 __attribute__((sda));
extern s32 D_L23_001B1A68 __attribute__((sda));
extern float D_L23_001B1A6C __attribute__((sda));
extern s32 D_L23_001B1A70 __attribute__((sda));
extern s32 D_L23_001B1A74 __attribute__((sda));
extern s32 D_L23_001B1A80 __attribute__((sda));
extern s32 D_L23_001B1A84 __attribute__((sda));
extern s32 D_L23_001B1A88 __attribute__((sda));
extern s32 D_L23_001B1A8C __attribute__((sda));
extern s32 D_L23_001B1A90 __attribute__((sda));
extern s32 D_L23_001B1A94 __attribute__((sda));
extern s32 D_L23_001B1A98 __attribute__((sda));
extern s32 D_L23_001B1A9C __attribute__((sda));
extern s32 D_L23_001B1AA0 __attribute__((sda));
extern s32 D_L23_001B1AA4 __attribute__((sda));
extern s32 D_L23_001B1AA8 __attribute__((sda));
extern s32 D_L23_001B1AB0 __attribute__((sda));
extern s32 D_L23_001B1AB4 __attribute__((sda));
extern s32 D_L23_001B1AB8 __attribute__((sda));
extern s32 D_L23_001B1AC0 __attribute__((sda));
extern s32 D_L23_001B1AC4 __attribute__((sda));
extern s32 D_L23_001B1AC8 __attribute__((sda));
extern float D_L23_001B1AD0 __attribute__((sda));
extern float D_L23_001B1AD4 __attribute__((sda));
extern float D_L23_001B1AE0 __attribute__((nosda));
extern float g_camera_l23_position[];

extern void effect_reset_record(L23Quad *);
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

/* Draws a glowing beam with scrolling texture and a bright spot at its end. */
void gfx_l23_draw_glowing_beam(s32 unused0, s32 unused1, s32 unused2, s32 unused3, s32 unused4, u8 *obj) {
    L23Quad q;
    float vrel[4] __attribute__((aligned(16)));
    float vaxis[4] __attribute__((aligned(16)));
    float vtip[4] __attribute__((aligned(16)));
    float vside[4] __attribute__((aligned(16)));
    float vbase[4] __attribute__((aligned(16)));
    float uvOffset[2];
    float *rel;
    float *axis;
    float *tip;
    float *side;
    float *base;
    L23BeamVars *vars;
    float angle;
    float sinAngle;
    float cosAngle;
    int i;
    int j;

    vars = *(L23BeamVars **)(obj + 0x68);
    effect_reset_record(&q);
    gfx_init_quad_packet_state(&q, D_L23_001B1A70, 1, 0x80);
    q.rgba[1] = D_L23_001B1A8C << 24;
    q.rgba[1] |= D_L23_001B1A88 << 16;
    q.rgba[1] |= D_L23_001B1A84 << 8;
    q.rgba[1] |= D_L23_001B1A80;
    q.rgba[3] = D_L23_001B1A9C << 24;
    q.rgba[3] |= D_L23_001B1A98 << 16;
    q.rgba[3] |= D_L23_001B1A94 << 8;
    q.rgba[3] |= D_L23_001B1A90;
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
    FastVecSub(rel, (float *)(obj + 0x10), g_camera_l23_position);
    vec_scale_to_length(axis, vars->dir, -vars->len);
    FastVecAdd(tip, (float *)(obj + 0x10), axis);
    FastVecCross(side, rel, axis);
    vec_scale_to_length(side, side, vars->width);
    vec_scale_to_length(base, vars->dir, D_L23_001B1AE0);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[0] = q.rgba[2];
    q.rgba[1] = q.rgba[3];
    q.rgba[3] = 0x801010;
    q.rgba[2] = 0x801010;
    qcopy(&q.corner[0], &q.corner[2]);
    qcopy(&q.corner[1], &q.corner[3]);
    FastVecAdd((float *)&q.corner[2], (float *)&q.corner[2], axis);
    FastVecAdd((float *)&q.corner[3], (float *)&q.corner[3], axis);
    draw_world_quad(&q, 0, 0);

    vec_scale_to_length(axis, vars->dir, -vars->back);
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
    vars->spin = FastAddRotations(vars->spin, D_L23_001B1A6C * 0.017453294f);
    gfx_init_quad_packet_state(&q, D_L23_001B1A74, 1, 0x80);
    q.d70 = 5;

    q.rgba[1] = D_L23_001B1A60 << 24;
    q.rgba[1] |= D_L23_001B1AA8 << 16;
    q.rgba[1] |= D_L23_001B1AA4 << 8;
    q.rgba[1] |= D_L23_001B1AA0;
    q.rgba[3] = D_L23_001B1AB8 << 16;
    q.rgba[3] |= D_L23_001B1AB4 << 8;
    q.rgba[3] |= D_L23_001B1AB0;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1A4C);
    vec_scale_to_length(base, vars->dir, D_L23_001B1AE0);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = D_L23_001B1A60 << 24;
    q.rgba[1] |= D_L23_001B1AA8 << 16;
    q.rgba[1] |= D_L23_001B1AA4 << 8;
    q.rgba[1] |= D_L23_001B1AA0;
    q.rgba[3] = D_L23_001B1AB8 << 16;
    q.rgba[3] |= D_L23_001B1AB4 << 8;
    q.rgba[3] |= D_L23_001B1AB0;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1A50);
    vec_scale_to_length(base, vars->dir, D_L23_001B1AD0);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = D_L23_001B1A68 << 24;
    q.rgba[1] |= D_L23_001B1AA8 << 16;
    q.rgba[1] |= D_L23_001B1AA4 << 8;
    q.rgba[1] |= D_L23_001B1AA0;
    q.rgba[3] = D_L23_001B1AB8 << 16;
    q.rgba[3] |= D_L23_001B1AB4 << 8;
    q.rgba[3] |= D_L23_001B1AB0;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1A54);
    vec_scale_to_length(base, vars->dir, D_L23_001B1AD0);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = D_L23_001B1A64 << 24;
    q.rgba[1] |= D_L23_001B1AC8 << 16;
    q.rgba[1] |= D_L23_001B1AC4 << 8;
    q.rgba[1] |= D_L23_001B1AC0;
    q.rgba[3] = D_L23_001B1AB8 << 16;
    q.rgba[3] |= D_L23_001B1AB4 << 8;
    q.rgba[3] |= D_L23_001B1AB0;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, D_L23_001B1A4C);
    vec_scale_to_length(base, vars->dir, D_L23_001B1AD4);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    vec_scale_to_length(axis, vars->dir, -0.6f);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    gfx_draw_billboard_quad(obj + 0x10, D_L23_001B1A58, D_L23_001B1A5C, 1, vars->glow, 0.08f, math_random_angle());
    gfx_draw_billboard_quad(obj + 0x10, D_L23_001B1A58, 0x80808080, 1, vars->glow * 0.4f, 0.08f, math_random_angle());
}
