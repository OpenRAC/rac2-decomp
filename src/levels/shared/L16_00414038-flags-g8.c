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
void func_L16_00414038(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u8 *obj) {
    L23Quad q;
    float vrel[4] __attribute__((aligned(16)));
    float vaxis[4] __attribute__((aligned(16)));
    float vtip[4] __attribute__((aligned(16)));
    float vside[4] __attribute__((aligned(16)));
    float vbase[4] __attribute__((aligned(16)));
    float t[2];
    float *rel;
    float *axis;
    float *tip;
    float *side;
    float *base;
    L23BeamVars *vars;
    float angle;
    float s;
    float c;
    int i;
    int j;

    vars = *(L23BeamVars **)(obj + 0x68);
    ref_L16_00414038_00(&q);
    func_00281DE8(&q, ref_L16_00414038_69, 1, 0x80);
    q.rgba[1] = ref_L16_00414038_74 << 24;
    q.rgba[1] |= ref_L16_00414038_73 << 16;
    q.rgba[1] |= ref_L16_00414038_72 << 8;
    q.rgba[1] |= ref_L16_00414038_71;
    q.rgba[3] = ref_L16_00414038_78 << 24;
    q.rgba[3] |= ref_L16_00414038_77 << 16;
    q.rgba[3] |= ref_L16_00414038_76 << 8;
    q.rgba[3] |= ref_L16_00414038_75;
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
    FastVecSub(rel, (float *)(obj + 0x10), ref_L16_00414038_91);
    vec_scale_to_length(axis, vars->dir, -ref_L16_00414038_141);
    FastVecAdd(tip, (float *)(obj + 0x10), axis);
    FastVecCross(side, rel, axis);
    vec_scale_to_length(side, side, ref_L16_00414038_142);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_90);
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

    vec_scale_to_length(axis, vars->dir, -4.0f);
    q.uv[0][0] = 0.0f;
    q.uv[0][1] = 0.0f;
    q.uv[1][0] = 0.0f;
    q.uv[1][1] = 1.0f;
    q.uv[2][0] = 1.0f;
    q.uv[2][1] = 0.0f;
    q.uv[3][0] = 1.0f;
    q.uv[3][1] = 1.0f;
    angle = vars->spin;
    s = func_00283180(angle);
    c = func_00283198(angle);
    for (j = 0; j < 4; j++) {
        t[0] = q.uv[j][0] - 0.5f;
        t[1] = q.uv[j][1] - 0.5f;
        q.uv[j][0] = t[0] * s - t[1] * c;
        q.uv[j][1] = t[0] * c + t[1] * s;
        q.uv[j][0] += 0.5f;
        q.uv[j][1] += 0.5f;
    }
    vars->spin = FastAddRotations(vars->spin, ref_L16_00414038_68 * 0.017453294f);
    func_00281DE8(&q, ref_L16_00414038_70, 1, 0x80);
    q.d70 = 5;

    q.rgba[1] = ref_L16_00414038_65 << 24;
    q.rgba[1] |= ref_L16_00414038_81 << 16;
    q.rgba[1] |= ref_L16_00414038_80 << 8;
    q.rgba[1] |= ref_L16_00414038_79;
    q.rgba[3] = ref_L16_00414038_84 << 16;
    q.rgba[3] |= ref_L16_00414038_83 << 8;
    q.rgba[3] |= ref_L16_00414038_82;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_60);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_90);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = ref_L16_00414038_65 << 24;
    q.rgba[1] |= ref_L16_00414038_81 << 16;
    q.rgba[1] |= ref_L16_00414038_80 << 8;
    q.rgba[1] |= ref_L16_00414038_79;
    q.rgba[3] = ref_L16_00414038_84 << 16;
    q.rgba[3] |= ref_L16_00414038_83 << 8;
    q.rgba[3] |= ref_L16_00414038_82;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_61);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_88);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = ref_L16_00414038_67 << 24;
    q.rgba[1] |= ref_L16_00414038_81 << 16;
    q.rgba[1] |= ref_L16_00414038_80 << 8;
    q.rgba[1] |= ref_L16_00414038_79;
    q.rgba[3] = ref_L16_00414038_84 << 16;
    q.rgba[3] |= ref_L16_00414038_83 << 8;
    q.rgba[3] |= ref_L16_00414038_82;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_62);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_88);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    q.rgba[1] = ref_L16_00414038_66 << 24;
    q.rgba[1] |= 0xFFFFFF;
    q.rgba[3] = ref_L16_00414038_84 << 16;
    q.rgba[3] |= ref_L16_00414038_83 << 8;
    q.rgba[3] |= ref_L16_00414038_82;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    vec_scale_to_length(side, side, ref_L16_00414038_60);
    vec_scale_to_length(base, vars->dir, ref_L16_00414038_89);
    FastVecAdd(base, (float *)(obj + 0x10), base);
    FastVecAdd((float *)&q.corner[0], base, side);
    FastVecSub((float *)&q.corner[1], base, side);
    vec_scale_to_length(axis, vars->dir, -0.6f);
    FastVecAdd(tip, base, axis);
    FastVecAdd(tip, tip, axis);
    FastVecAdd((float *)&q.corner[2], tip, side);
    FastVecSub((float *)&q.corner[3], tip, side);
    draw_world_quad(&q, 0, 0);

    func_00281EB8(obj + 0x10, ref_L16_00414038_63, ref_L16_00414038_64, 1, ref_L16_00414038_143, 0.08f, func_002A7940());
    func_00281EB8(obj + 0x10, ref_L16_00414038_63, 0x80808080, 1, ref_L16_00414038_143 * 0.4f, 0.08f, func_002A7940());
}
