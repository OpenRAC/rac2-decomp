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

extern float ref_L16_00414038_141 __attribute__((sda));
extern float ref_L16_00414038_142 __attribute__((sda));
extern float ref_L16_00414038_143 __attribute__((sda));
extern float ref_L16_00414038_60 __attribute__((sda));
extern float ref_L16_00414038_61 __attribute__((sda));
extern float ref_L16_00414038_62 __attribute__((sda));
extern s32 ref_L16_00414038_63 __attribute__((sda));
extern u32 ref_L16_00414038_64 __attribute__((sda));
extern s32 ref_L16_00414038_65 __attribute__((sda));
extern s32 ref_L16_00414038_66 __attribute__((sda));
extern s32 ref_L16_00414038_67 __attribute__((sda));
extern float ref_L16_00414038_68 __attribute__((sda));
extern s32 ref_L16_00414038_69 __attribute__((sda));
extern s32 ref_L16_00414038_70 __attribute__((sda));
extern s32 ref_L16_00414038_71 __attribute__((sda));
extern s32 ref_L16_00414038_72 __attribute__((sda));
extern s32 ref_L16_00414038_73 __attribute__((sda));
extern s32 ref_L16_00414038_74 __attribute__((sda));
extern s32 ref_L16_00414038_75 __attribute__((sda));
extern s32 ref_L16_00414038_76 __attribute__((sda));
extern s32 ref_L16_00414038_77 __attribute__((sda));
extern s32 ref_L16_00414038_78 __attribute__((sda));
extern s32 ref_L16_00414038_79 __attribute__((sda));
extern s32 ref_L16_00414038_80 __attribute__((sda));
extern s32 ref_L16_00414038_81 __attribute__((sda));
extern s32 ref_L16_00414038_82 __attribute__((sda));
extern s32 ref_L16_00414038_83 __attribute__((sda));
extern s32 ref_L16_00414038_84 __attribute__((sda));
extern s32 ref_L16_00414038_85 __attribute__((sda));
extern s32 ref_L16_00414038_86 __attribute__((sda));
extern s32 ref_L16_00414038_87 __attribute__((sda));
extern float ref_L16_00414038_88 __attribute__((sda));
extern float ref_L16_00414038_89 __attribute__((sda));
extern float ref_L16_00414038_90 __attribute__((nosda));
extern float ref_L16_00414038_91[];

extern void func_L11_0045FFB0(L23Quad *);
extern void func_00281DE8(L23Quad *, s32, s32, s32);
extern void func_00280B90(L23Quad *, void *, s32);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern void func_00282DD8(float *, float *, float *);
extern void func_00282F20(float *, float *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern float func_002A7940(void);
extern void func_00281EB8(u8 *, s32, u32, s32, float, float, float);


/* Same body as func_L23_00428490, with this function's own callees. */
extern void ref_L16_00414038_00(L23Quad *);
/* Draws a glowing beam as several scrolling, spinning quads plus two glows at the start. */
void func_L16_00414038(s32 unusedArg0, s32 unusedArg1, s32 unusedArg2, s32 unusedArg3, s32 unusedArg4, u8 *object) {
    L23Quad quad;
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

    vars = *(L23BeamVars **)(object + 0x68);
    ref_L16_00414038_00(&quad);
    InitQuadPacketState(&quad, ref_L16_00414038_69, 1, 0x80);
    quad.rgba[1] = ref_L16_00414038_74 << 24;
    quad.rgba[1] |= ref_L16_00414038_73 << 16;
    quad.rgba[1] |= ref_L16_00414038_72 << 8;
    quad.rgba[1] |= ref_L16_00414038_71;
    quad.rgba[3] = ref_L16_00414038_78 << 24;
    quad.rgba[3] |= ref_L16_00414038_77 << 16;
    quad.rgba[3] |= ref_L16_00414038_76 << 8;
    quad.rgba[3] |= ref_L16_00414038_75;
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
    FastVecSub(rel, (float *)(object + 0x10), ref_L16_00414038_91);
    vec_scale_to_length(axis, vars->dir, -ref_L16_00414038_141);
    FastVecAdd(tip, (float *)(object + 0x10), axis);
    FastVecCross(side, rel, axis);
    vec_scale_to_length(side, side, ref_L16_00414038_142);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_90);
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
    sinAngle = FastSinOrCosA(angle);
    cosAngle = FastSinOrCosB(angle);
    for (j = 0; j < 4; j++) {
        uvOffset[0] = quad.uv[j][0] - 0.5f;
        uvOffset[1] = quad.uv[j][1] - 0.5f;
        quad.uv[j][0] = uvOffset[0] * sinAngle - uvOffset[1] * cosAngle;
        quad.uv[j][1] = uvOffset[0] * cosAngle + uvOffset[1] * sinAngle;
        quad.uv[j][0] += 0.5f;
        quad.uv[j][1] += 0.5f;
    }
    vars->spin = FastAddRotations(vars->spin, ref_L16_00414038_68 * 0.017453294f);
    InitQuadPacketState(&quad, ref_L16_00414038_70, 1, 0x80);
    quad.d70 = 5;

    quad.rgba[1] = ref_L16_00414038_65 << 24;
    quad.rgba[1] |= ref_L16_00414038_81 << 16;
    quad.rgba[1] |= ref_L16_00414038_80 << 8;
    quad.rgba[1] |= ref_L16_00414038_79;
    quad.rgba[3] = ref_L16_00414038_84 << 16;
    quad.rgba[3] |= ref_L16_00414038_83 << 8;
    quad.rgba[3] |= ref_L16_00414038_82;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_60);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_90);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    quad.rgba[1] = ref_L16_00414038_65 << 24;
    quad.rgba[1] |= ref_L16_00414038_81 << 16;
    quad.rgba[1] |= ref_L16_00414038_80 << 8;
    quad.rgba[1] |= ref_L16_00414038_79;
    quad.rgba[3] = ref_L16_00414038_84 << 16;
    quad.rgba[3] |= ref_L16_00414038_83 << 8;
    quad.rgba[3] |= ref_L16_00414038_82;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_61);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_88);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    quad.rgba[1] = ref_L16_00414038_67 << 24;
    quad.rgba[1] |= ref_L16_00414038_81 << 16;
    quad.rgba[1] |= ref_L16_00414038_80 << 8;
    quad.rgba[1] |= ref_L16_00414038_79;
    quad.rgba[3] = ref_L16_00414038_84 << 16;
    quad.rgba[3] |= ref_L16_00414038_83 << 8;
    quad.rgba[3] |= ref_L16_00414038_82;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_62);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_88);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    quad.rgba[1] = ref_L16_00414038_66 << 24;
    quad.rgba[1] |= 0xFFFFFF;
    quad.rgba[3] = ref_L16_00414038_84 << 16;
    quad.rgba[3] |= ref_L16_00414038_83 << 8;
    quad.rgba[3] |= ref_L16_00414038_82;
    quad.rgba[0] = quad.rgba[1];
    quad.rgba[2] = quad.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_60);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_89);
    FastVecAdd(base, (float *)(object + 0x10), base);
    FastVecAdd((float *)&quad.corner[0], base, side);
    FastVecSub((float *)&quad.corner[1], base, side);
    vec_scale_to_length(axis, vars->dir, -0.6f);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&quad.corner[2], tip, side);
    FastVecSub((float *)&quad.corner[3], tip, side);
    draw_world_quad(&quad, 0, 0);

    DrawBillboardQuad_00281EB8(object + 0x10, ref_L16_00414038_63, ref_L16_00414038_64, 1, ref_L16_00414038_143, 0.08f, RandomAngle());
    DrawBillboardQuad_00281EB8(object + 0x10, ref_L16_00414038_63, 0x80808080, 1, ref_L16_00414038_143 * 0.4f, 0.08f, RandomAngle());
}
