#include "common.h"


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

extern float ref_L16_00405818_41 __attribute__((sda));
extern float ref_L16_00405818_42 __attribute__((sda));
extern float ref_L16_00405818_43 __attribute__((sda));
extern float ref_L16_00405818_10 __attribute__((sda));
extern float ref_L16_00405818_11 __attribute__((sda));
extern float ref_L16_00405818_12 __attribute__((sda));
extern s32 ref_L16_00405818_13 __attribute__((sda));
extern u32 ref_L16_00405818_14 __attribute__((sda));
extern s32 ref_L16_00405818_15 __attribute__((sda));
extern s32 ref_L16_00405818_16 __attribute__((sda));
extern s32 ref_L16_00405818_17 __attribute__((sda));
extern float ref_L16_00405818_18 __attribute__((sda));
extern s32 ref_L16_00405818_05 __attribute__((sda));
extern s32 ref_L16_00405818_19 __attribute__((sda));
extern s32 ref_L16_00405818_20 __attribute__((sda));
extern s32 ref_L16_00405818_21 __attribute__((sda));
extern s32 ref_L16_00405818_22 __attribute__((sda));
extern s32 ref_L16_00405818_23 __attribute__((sda));
extern s32 ref_L16_00405818_24 __attribute__((sda));
extern s32 ref_L16_00405818_25 __attribute__((sda));
extern s32 ref_L16_00405818_26 __attribute__((sda));
extern s32 ref_L16_00405818_27 __attribute__((sda));
extern s32 ref_L16_00405818_28 __attribute__((sda));
extern s32 ref_L16_00405818_29 __attribute__((sda));
extern s32 ref_L16_00405818_30 __attribute__((sda));
extern s32 ref_L16_00405818_31 __attribute__((sda));
extern s32 ref_L16_00405818_32 __attribute__((sda));
extern s32 ref_L16_00405818_33 __attribute__((sda));
extern s32 ref_L16_00405818_34 __attribute__((sda));
extern s32 ref_L16_00405818_35 __attribute__((sda));
extern s32 ref_L16_00405818_36 __attribute__((sda));
extern float ref_L16_00405818_37 __attribute__((sda));
extern float ref_L16_00405818_38 __attribute__((sda));
extern float ref_L16_00405818_39 __attribute__((nosda));
extern float ref_L16_00405818_40[];

extern void part_reset_quad_record_b(L23Quad *);
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


/* Same body as func_L23_00428490, with this function's own callees. */
extern void ref_L16_00405818_00(L23Quad *);
/* Draws a glowing beam as several scrolling, spinning quads plus two glows at the start. */
void gfx_draw_beam_quads_glows(s32 unused_arg0, s32 unused_arg1, s32 unused_arg2, s32 unused_arg3, s32 unused_arg4, u8 *object) {
    L23Quad quad;
    float vrel[4] __attribute__((aligned(16)));
    float vaxis[4] __attribute__((aligned(16)));
    float vtip[4] __attribute__((aligned(16)));
    float vside[4] __attribute__((aligned(16)));
    float vbase[4] __attribute__((aligned(16)));
    float uv_offset[2];
    float *rel;
    float *axis;
    float *tip;
    float *side;
    float *base;
    L23BeamVars *vars;
    float angle;
    float sin_angle;
    float cos_angle;
    int i;
    int j;

    vars = *(L23BeamVars **)(object + 0x68);
    ref_L16_00405818_00(&quad);
    gfx_init_quad_packet_state(&quad, ref_L16_00405818_05, 1, 0x80);
    quad.rgba[1] = ref_L16_00405818_23 << 24;
    quad.rgba[1] |= ref_L16_00405818_22 << 16;
    quad.rgba[1] |= ref_L16_00405818_21 << 8;
    quad.rgba[1] |= ref_L16_00405818_20;
    quad.rgba[3] = ref_L16_00405818_27 << 24;
    quad.rgba[3] |= ref_L16_00405818_26 << 16;
    quad.rgba[3] |= ref_L16_00405818_25 << 8;
    quad.rgba[3] |= ref_L16_00405818_24;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    quad.uv[0][0] = 0.0f;
    quad.uv[0][1] = 0.0f;
    quad.uv[1][0] = 0.0f;
    quad.uv[1][1] = 1.0f;
    quad.uv[2][0] = 1.0f;
    quad.uv[2][1] = 0.0f;
    quad.uv[3][0] = 1.0f;
    quad.uv[3][1] = 1.0f;
    rel = vrel;
    axis = vaxis;
    tip = vtip;
    side = vside;
    base = vbase;
    for (i = 0; i < 4; i++) {
        quad.uv[i][0] -= vars->scroll;
        if (quad.uv[i][0] <= 7.0f) {
            quad.uv[i][0] += 7.0f;
        }
    }
    vars->scroll += 0.1f;
    if (vars->scroll >= 4.0f) {
        vars->scroll -= 4.0f;
    }
    FastVecSub(rel, (float *)(object + 0x10), ref_L16_00405818_40);
    vec_scale_to_length(axis, vars->dir, -ref_L16_00405818_41);
    FastVecAdd(tip, (float *)(object + 0x10), axis);
    FastVecCross(side, rel, axis);
    vec_scale_to_length(side, side, ref_L16_00405818_42);
    vec_scale_to_length(base, vars->dir, ref_L16_00405818_39);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    quad.rgba[0] = quad.rgba[2];
    quad.rgba[1] = quad.rgba[3];
    quad.rgba[3] = 0x801010;
    quad.rgba[2] = 0x801010;
    qcopy(&quad.corner[0], &quad.corner[2]);
    qcopy(&quad.corner[1], &quad.corner[3]);
    FastVecAdd((float *)&quad.corner[2], (float *)&quad.corner[2], axis);
    FastVecAdd((float *)&quad.corner[3], (float *)&quad.corner[3], axis);
    draw_world_quad(&quad, 0, 0);

    vec_scale_to_length(axis, vars->dir, -4.0f);
    quad.uv[0][0] = 0.0f;
    quad.uv[0][1] = 0.0f;
    quad.uv[1][0] = 0.0f;
    quad.uv[1][1] = 1.0f;
    quad.uv[2][0] = 1.0f;
    quad.uv[2][1] = 0.0f;
    quad.uv[3][0] = 1.0f;
    quad.uv[3][1] = 1.0f;
    angle = vars->spin;
    sin_angle = math_fast_sin_or_cos_a(angle);
    cos_angle = math_fast_sin_or_cos_b(angle);
    for (j = 0; j < 4; j++) {
        uv_offset[0] = quad.uv[j][0] - 0.5f;
        uv_offset[1] = quad.uv[j][1] - 0.5f;
        quad.uv[j][0] = uv_offset[0] * sin_angle - uv_offset[1] * cos_angle;
        quad.uv[j][1] = uv_offset[0] * cos_angle + uv_offset[1] * sin_angle;
        quad.uv[j][0] += 0.5f;
        quad.uv[j][1] += 0.5f;
    }
    vars->spin = FastAddRotations(vars->spin, ref_L16_00405818_18 * 0.017453294f);
    gfx_init_quad_packet_state(&quad, ref_L16_00405818_19, 1, 0x80);
    quad.d70 = 5;

    quad.rgba[1] = ref_L16_00405818_15 << 24;
    quad.rgba[1] |= ref_L16_00405818_30 << 16;
    quad.rgba[1] |= ref_L16_00405818_29 << 8;
    quad.rgba[1] |= ref_L16_00405818_28;
    quad.rgba[3] = ref_L16_00405818_33 << 16;
    quad.rgba[3] |= ref_L16_00405818_32 << 8;
    quad.rgba[3] |= ref_L16_00405818_31;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00405818_10);
    vec_scale_to_length(base, vars->dir, ref_L16_00405818_39);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    quad.rgba[1] = ref_L16_00405818_15 << 24;
    quad.rgba[1] |= ref_L16_00405818_30 << 16;
    quad.rgba[1] |= ref_L16_00405818_29 << 8;
    quad.rgba[1] |= ref_L16_00405818_28;
    quad.rgba[3] = ref_L16_00405818_33 << 16;
    quad.rgba[3] |= ref_L16_00405818_32 << 8;
    quad.rgba[3] |= ref_L16_00405818_31;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00405818_11);
    vec_scale_to_length(base, vars->dir, ref_L16_00405818_37);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    quad.rgba[1] = ref_L16_00405818_17 << 24;
    quad.rgba[1] |= ref_L16_00405818_30 << 16;
    quad.rgba[1] |= ref_L16_00405818_29 << 8;
    quad.rgba[1] |= ref_L16_00405818_28;
    quad.rgba[3] = ref_L16_00405818_33 << 16;
    quad.rgba[3] |= ref_L16_00405818_32 << 8;
    quad.rgba[3] |= ref_L16_00405818_31;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00405818_12);
    vec_scale_to_length(base, vars->dir, ref_L16_00405818_37);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    quad.rgba[1] = ref_L16_00405818_16 << 24;
    quad.rgba[1] |= ref_L16_00405818_36 << 16;
    quad.rgba[1] |= ref_L16_00405818_35 << 8;
    quad.rgba[1] |= ref_L16_00405818_34;
    quad.rgba[3] = ref_L16_00405818_33 << 16;
    quad.rgba[3] |= ref_L16_00405818_32 << 8;
    quad.rgba[3] |= ref_L16_00405818_31;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00405818_10);
    vec_scale_to_length(base, vars->dir, ref_L16_00405818_38);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    vec_scale_to_length(axis, vars->dir, -0.6f);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    gfx_draw_billboard_quad(object + 0x10, ref_L16_00405818_13, ref_L16_00405818_14, 1, ref_L16_00405818_43, 0.08f, math_random_angle());
    gfx_draw_billboard_quad(object + 0x10, ref_L16_00405818_13, 0x80808080, 1, ref_L16_00405818_43 * 0.4f, 0.08f, math_random_angle());
}
