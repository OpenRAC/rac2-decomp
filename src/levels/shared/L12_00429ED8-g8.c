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

extern float D_L12_001B2318 __attribute__((sda));
extern float D_L12_001B231C __attribute__((sda));
extern float D_L12_001B22F8 __attribute__((sda));
extern s32 D_L12_001B22FC __attribute__((sda));
extern float D_L12_001B2300 __attribute__((sda));
extern float D_L12_001B22EC __attribute__((sda));
extern float D_L12_001B22F0 __attribute__((sda));
extern float D_L12_001B22F4 __attribute__((sda));
extern s32 D_L12_001B2304 __attribute__((sda));
extern u32 D_L23_001B1A5C __attribute__((sda));
extern s32 D_L12_001B2308 __attribute__((sda));
extern s32 D_L12_001B230C __attribute__((sda));
extern s32 D_L12_001B2310 __attribute__((sda));
extern float D_L12_001B2314 __attribute__((sda));
extern s32 D_L12_001B2320 __attribute__((sda));
extern s32 D_L12_001B2324 __attribute__((sda));
extern s32 D_L12_001B2330 __attribute__((sda));
extern s32 D_L12_001B2334 __attribute__((sda));
extern s32 D_L12_001B2338 __attribute__((sda));
extern s32 D_L12_001B233C __attribute__((sda));
extern s32 D_L12_001B2340 __attribute__((sda));
extern s32 D_L12_001B2344 __attribute__((sda));
extern s32 D_L12_001B2348 __attribute__((sda));
extern s32 D_L12_001B234C __attribute__((sda));
extern s32 D_L12_001B2350 __attribute__((sda));
extern s32 D_L12_001B2354 __attribute__((sda));
extern s32 D_L12_001B2358 __attribute__((sda));
extern s32 D_L12_001B2360 __attribute__((sda));
extern s32 D_L12_001B2364 __attribute__((sda));
extern s32 D_L12_001B2368 __attribute__((sda));
extern s32 D_L12_001B2370 __attribute__((sda));
extern s32 D_L12_001B2374 __attribute__((sda));
extern s32 D_L12_001B2378 __attribute__((sda));
extern float D_L12_001B2380 __attribute__((sda));
extern float D_L12_001B2384 __attribute__((sda));
extern float D_L12_001B238C __attribute__((nosda));
extern float D_L12_001B9E00[];

extern void func_L00_004181A8(L23Quad *);
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

void func_L12_00429ED8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u8 *obj) {
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
    func_L00_004181A8(&q);
    func_00281DE8(&q, D_L12_001B2320, 1, 0x80);
    q.rgba[1] = D_L12_001B233C << 24;
    q.rgba[1] |= D_L12_001B2338 << 16;
    q.rgba[1] |= D_L12_001B2334 << 8;
    q.rgba[1] |= D_L12_001B2330;
    q.rgba[3] = D_L12_001B234C << 24;
    q.rgba[3] |= D_L12_001B2348 << 16;
    q.rgba[3] |= D_L12_001B2344 << 8;
    q.rgba[3] |= D_L12_001B2340;
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
    func_00282CF0(rel, (float *)(obj + 0x10), D_L12_001B9E00);
    func_00282F20(axis, vars->dir, -D_L12_001B2318);
    func_00282CC0(tip, (float *)(obj + 0x10), axis);
    func_00282DD8(side, rel, axis);
    func_00282F20(side, side, D_L12_001B22F8);
    func_00282F20(base, vars->dir, D_L12_001B238C);
    func_00282CC0(base, (float *)(obj + 0x10), base);
    func_00282CC0((float *)&q.corner[0], base, side);
    func_00282CF0((float *)&q.corner[1], base, side);
    func_00282CC0((float *)&q.corner[2], tip, side);
    func_00282CF0((float *)&q.corner[3], tip, side);
    func_00280B90(&q, 0, 0);

    q.rgba[0] = q.rgba[2];
    q.rgba[1] = q.rgba[3];
    q.rgba[3] = 0x202020;
    q.rgba[2] = 0x202020;
    qcopy(&q.corner[0], &q.corner[2]);
    qcopy(&q.corner[1], &q.corner[3]);
    func_00282CC0((float *)&q.corner[2], (float *)&q.corner[2], axis);
    func_00282CC0((float *)&q.corner[3], (float *)&q.corner[3], axis);
    func_00280B90(&q, 0, 0);

    func_00282F20(axis, vars->dir, -D_L12_001B231C);
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
    vars->spin = func_00283B98(vars->spin, D_L12_001B2314 * 0.017453294f);
    func_00281DE8(&q, D_L12_001B2324, 1, 0x80);
    q.d70 = 5;

    q.rgba[1] = D_L12_001B2308 << 24;
    q.rgba[1] |= D_L12_001B2358 << 16;
    q.rgba[1] |= D_L12_001B2354 << 8;
    q.rgba[1] |= D_L12_001B2350;
    q.rgba[3] = D_L12_001B2368 << 16;
    q.rgba[3] |= D_L12_001B2364 << 8;
    q.rgba[3] |= D_L12_001B2360;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    func_00282F20(side, side, D_L12_001B22EC);
    func_00282F20(base, vars->dir, D_L12_001B238C);
    func_00282CC0(base, (float *)(obj + 0x10), base);
    func_00282CC0((float *)&q.corner[0], base, side);
    func_00282CF0((float *)&q.corner[1], base, side);
    func_00282CC0(tip, base, axis);
    func_00282CC0(tip, tip, axis);
    func_00282CC0((float *)&q.corner[2], tip, side);
    func_00282CF0((float *)&q.corner[3], tip, side);
    func_00280B90(&q, 0, 0);

    q.rgba[1] = D_L12_001B2308 << 24;
    q.rgba[1] |= D_L12_001B2358 << 16;
    q.rgba[1] |= D_L12_001B2354 << 8;
    q.rgba[1] |= D_L12_001B2350;
    q.rgba[3] = D_L12_001B2368 << 16;
    q.rgba[3] |= D_L12_001B2364 << 8;
    q.rgba[3] |= D_L12_001B2360;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    func_00282F20(side, side, D_L12_001B22F0);
    func_00282F20(base, vars->dir, D_L12_001B2380);
    func_00282CC0(base, (float *)(obj + 0x10), base);
    func_00282CC0((float *)&q.corner[0], base, side);
    func_00282CF0((float *)&q.corner[1], base, side);
    func_00282CC0(tip, base, axis);
    func_00282CC0(tip, tip, axis);
    func_00282CC0((float *)&q.corner[2], tip, side);
    func_00282CF0((float *)&q.corner[3], tip, side);
    func_00280B90(&q, 0, 0);

    q.rgba[1] = D_L12_001B2310 << 24;
    q.rgba[1] |= D_L12_001B2358 << 16;
    q.rgba[1] |= D_L12_001B2354 << 8;
    q.rgba[1] |= D_L12_001B2350;
    q.rgba[3] = D_L12_001B2368 << 16;
    q.rgba[3] |= D_L12_001B2364 << 8;
    q.rgba[3] |= D_L12_001B2360;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    func_00282F20(side, side, D_L12_001B22F4);
    func_00282F20(base, vars->dir, D_L12_001B2380);
    func_00282CC0(base, (float *)(obj + 0x10), base);
    func_00282CC0((float *)&q.corner[0], base, side);
    func_00282CF0((float *)&q.corner[1], base, side);
    func_00282CC0(tip, base, axis);
    func_00282CC0(tip, tip, axis);
    func_00282CC0((float *)&q.corner[2], tip, side);
    func_00282CF0((float *)&q.corner[3], tip, side);
    func_00280B90(&q, 0, 0);

    q.rgba[1] = D_L12_001B230C << 24;
    q.rgba[1] |= D_L12_001B2378 << 16;
    q.rgba[1] |= D_L12_001B2374 << 8;
    q.rgba[1] |= D_L12_001B2370;
    q.rgba[3] = D_L12_001B2368 << 16;
    q.rgba[3] |= D_L12_001B2364 << 8;
    q.rgba[3] |= D_L12_001B2360;
    q.rgba[0] = q.rgba[1];
    q.rgba[2] = q.rgba[3];
    func_00282F20(side, side, D_L12_001B22EC);
    func_00282F20(base, vars->dir, D_L12_001B2384);
    func_00282CC0(base, (float *)(obj + 0x10), base);
    func_00282CC0((float *)&q.corner[0], base, side);
    func_00282CF0((float *)&q.corner[1], base, side);
    func_00282F20(axis, vars->dir, -0.6f);
    func_00282CC0(tip, base, axis);
    func_00282CC0(tip, tip, axis);
    func_00282CC0((float *)&q.corner[2], tip, side);
    func_00282CF0((float *)&q.corner[3], tip, side);
    func_00280B90(&q, 0, 0);

    func_00281EB8(obj + 0x10, D_L12_001B22FC, D_L12_001B2304, 1, D_L12_001B2300, 0.08f, func_002A7940());
    func_00281EB8(obj + 0x10, D_L12_001B22FC, 0x80808080, 1, D_L12_001B2300 * 0.4f, 0.08f, func_002A7940());
}
