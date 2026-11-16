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

extern float g_beam_l23_side_length_a __attribute__((sda));
extern float g_beam_l23_side_length_b __attribute__((sda));
extern float g_beam_l23_side_length_c __attribute__((sda));
extern s32 g_beam_glow_texture __attribute__((sda));
extern u32 g_beam_l23_glow_color __attribute__((sda));
extern s32 g_beam_rgba_a_alpha __attribute__((sda));
extern s32 g_beam_rgba_b_alpha __attribute__((sda));
extern s32 g_beam_rgba_c_alpha __attribute__((sda));
extern float g_beam_l23_spin_degrees __attribute__((sda));
extern s32 g_beam_l23_quad_texture_a __attribute__((sda));
extern s32 g_beam_l23_quad_texture_b __attribute__((sda));
extern s32 g_beam_rgba_d_red __attribute__((sda));
extern s32 g_beam_rgba_d_green __attribute__((sda));
extern s32 g_beam_rgba_d_blue __attribute__((sda));
extern s32 g_beam_rgba_d_alpha __attribute__((sda));
extern s32 g_beam_rgba_e_red __attribute__((sda));
extern s32 g_beam_rgba_e_green __attribute__((sda));
extern s32 g_beam_rgba_e_blue __attribute__((sda));
extern s32 g_beam_rgba_e_alpha __attribute__((sda));
extern s32 g_beam_rgba_f_red __attribute__((sda));
extern s32 g_beam_rgba_f_green __attribute__((sda));
extern s32 g_beam_rgba_f_blue __attribute__((sda));
extern s32 g_beam_rgba_g_red __attribute__((sda));
extern s32 g_beam_rgba_g_green __attribute__((sda));
extern s32 g_beam_rgba_g_blue __attribute__((sda));
extern s32 g_beam_rgba_h_red __attribute__((sda));
extern s32 g_beam_rgba_h_green __attribute__((sda));
extern s32 g_beam_rgba_h_blue __attribute__((sda));
extern float g_beam_l23_base_length_a __attribute__((sda));
extern float g_beam_l23_base_length_b __attribute__((sda));
extern float g_beam_base_length_c __attribute__((nosda));
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

    vars = *(L23BeamVars **)(obj + 0x68);
    effect_reset_record(&q);
    gfx_init_quad_packet_state(&q, g_beam_l23_quad_texture_a, 1, 0x80);
    q.rgba[1] = g_beam_rgba_d_alpha << 24;
    q.rgba[1] |= g_beam_rgba_d_blue << 16;
    q.rgba[1] |= g_beam_rgba_d_green << 8;
    q.rgba[1] |= g_beam_rgba_d_red;
    q.rgba[3] = g_beam_rgba_e_alpha << 24;
    q.rgba[3] |= g_beam_rgba_e_blue << 16;
    q.rgba[3] |= g_beam_rgba_e_green << 8;
    q.rgba[3] |= g_beam_rgba_e_red;
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
    vec_scale_to_length(base, vars->dir, g_beam_base_length_c);
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
    sin_angle = math_fast_sin_or_cos_a(angle);
    cos_angle = math_fast_sin_or_cos_b(angle);
    for (j = 0; j < 4; j++) {
        uv_offset[0] = q.uv[j][0] - 0.5f;
        uv_offset[1] = q.uv[j][1] - 0.5f;
        q.uv[j][0] = uv_offset[0] * sin_angle - uv_offset[1] * cos_angle;
        q.uv[j][1] = uv_offset[0] * cos_angle + uv_offset[1] * sin_angle;
        q.uv[j][0] += 0.5f;
        q.uv[j][1] += 0.5f;
    }
    vars->spin = FastAddRotations(vars->spin, g_beam_l23_spin_degrees * 0.017453294f);
    gfx_init_quad_packet_state(&q, g_beam_l23_quad_texture_b, 1, 0x80);
    q.d70 = 5;

    q.rgba[1] = g_beam_rgba_a_alpha << 24;
    q.rgba[1] |= g_beam_rgba_f_blue << 16;
    q.rgba[1] |= g_beam_rgba_f_green << 8;
    q.rgba[1] |= g_beam_rgba_f_red;
    q.rgba[3] = g_beam_rgba_g_blue << 16;
    q.rgba[3] |= g_beam_rgba_g_green << 8;
    q.rgba[3] |= g_beam_rgba_g_red;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, g_beam_l23_side_length_a);
    vec_scale_to_length(base, vars->dir, g_beam_base_length_c);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = g_beam_rgba_a_alpha << 24;
    q.rgba[1] |= g_beam_rgba_f_blue << 16;
    q.rgba[1] |= g_beam_rgba_f_green << 8;
    q.rgba[1] |= g_beam_rgba_f_red;
    q.rgba[3] = g_beam_rgba_g_blue << 16;
    q.rgba[3] |= g_beam_rgba_g_green << 8;
    q.rgba[3] |= g_beam_rgba_g_red;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, g_beam_l23_side_length_b);
    vec_scale_to_length(base, vars->dir, g_beam_l23_base_length_a);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = g_beam_rgba_c_alpha << 24;
    q.rgba[1] |= g_beam_rgba_f_blue << 16;
    q.rgba[1] |= g_beam_rgba_f_green << 8;
    q.rgba[1] |= g_beam_rgba_f_red;
    q.rgba[3] = g_beam_rgba_g_blue << 16;
    q.rgba[3] |= g_beam_rgba_g_green << 8;
    q.rgba[3] |= g_beam_rgba_g_red;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, g_beam_l23_side_length_c);
    vec_scale_to_length(base, vars->dir, g_beam_l23_base_length_a);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = g_beam_rgba_b_alpha << 24;
    q.rgba[1] |= g_beam_rgba_h_blue << 16;
    q.rgba[1] |= g_beam_rgba_h_green << 8;
    q.rgba[1] |= g_beam_rgba_h_red;
    q.rgba[3] = g_beam_rgba_g_blue << 16;
    q.rgba[3] |= g_beam_rgba_g_green << 8;
    q.rgba[3] |= g_beam_rgba_g_red;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, g_beam_l23_side_length_a);
    vec_scale_to_length(base, vars->dir, g_beam_l23_base_length_b);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    vec_scale_to_length(axis, vars->dir, -0.6f);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    gfx_draw_billboard_quad(obj + 0x10, g_beam_glow_texture, g_beam_l23_glow_color, 1, vars->glow, 0.08f, math_random_angle());
    gfx_draw_billboard_quad(obj + 0x10, g_beam_glow_texture, 0x80808080, 1, vars->glow * 0.4f, 0.08f, math_random_angle());
}
