#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { Vec pos[4]; u32 color[4]; float uv[4][2]; u64 gs[4]; } Quad;
extern u64 func_0027C878(int);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern u32 func_00283D38(u32, u32, float);
extern void func_00280B90(Quad *, int, int);
extern char *D_L11_001FF580[] NOT_SDA;
extern s32 D_L11_001B18D4[] __attribute__((sda));
extern s32 D_L11_001B18D8[] __attribute__((sda));
extern s32 D_L11_001B18DC[] __attribute__((sda));
extern s32 D_L11_001B18E0[] __attribute__((sda));
extern s32 D_L11_001B18E4[] __attribute__((sda));
extern s32 D_L11_001B18A0 __attribute__((sda));
extern float D_L11_001B18CC[] __attribute__((sda));
extern s32 D_L11_001B18D0 __attribute__((sda));
extern s32 D_L11_001B1890 __attribute__((sda));
extern s32 D_L11_001B188C __attribute__((sda));
extern s32 D_L11_001B1894 __attribute__((sda));
extern s32 D_L11_001B1898 __attribute__((sda));
extern s32 D_L11_001B189C __attribute__((sda));
extern float D_L11_001B18F4[] __attribute__((sda));
extern float D_L11_001B18B4[] __attribute__((sda));
extern float D_L11_001B18BC[] __attribute__((sda));
extern float D_L11_001B18C4[] __attribute__((sda));
extern float D_L11_001B18FC __attribute__((sda));
extern float D_L11_001B187C __attribute__((sda));
extern float D_L11_001B18F0 __attribute__((sda));
extern float D_L11_001B18E8 __attribute__((sda));
extern float D_L11_001B18F8 __attribute__((sda));
extern s32 D_L11_001B18A8[2] __attribute__((sda));
extern float D_L11_001B18B0[4][2] __attribute__((sda));
/* Draws the ribbon along the stored points, with two scrolling texture layers. */
void func_L11_004465F8(char *moby) {
    Quad quad;
    u32 mask;
    int i, j;
    int next_i;
    float *pos1, *pos2, *pos3;
    char *state = *(char **)(moby + 0x68);
    char *points;
    float height;
    float depth;
    if (*(float *)(state + 0x1BC) < D_L11_001B18FC) return;
    quad.gs[1] = GetEffectTextureDescriptor(D_L11_001B18A0);
    pos1 = quad.pos[1];
    pos2 = quad.pos[2];
    pos3 = quad.pos[3];
    quad.gs[2] = 0xFF9000000260ULL;
    quad.gs[0] = D_L11_001B18D0 | ((u64)D_L11_001B18D4[0] << 2);
    quad.gs[0] |= (u64)D_L11_001B18D8[0] << 4;
    quad.gs[0] |= (u64)D_L11_001B18DC[0] << 14;
    quad.gs[0] |= (u64)D_L11_001B18E0[0] << 24;
    quad.gs[0] |= (u64)D_L11_001B18E4[0] << 34;
    quad.gs[3] = D_L11_001B188C | ((u64)D_L11_001B1890 << 2);
    quad.gs[3] |= (u64)D_L11_001B1894 << 4;
    quad.gs[3] |= (u64)D_L11_001B1898 << 6;
    quad.gs[3] |= (u64)D_L11_001B189C << 32;
    height = D_L11_001B18F4[0] + (D_L11_001B18F0 - D_L11_001B18F4[0]) *
        (*(float *)(state + 0x1BC) / D_L11_001B187C);
    points = D_L11_001FF580[*(int *)(state + 0x1C8)];
    for (i = 0; i < *(int *)points - 1; i = next_i) {
        mask = 0xFFFFFF;
        qcopy(quad.pos[0], points + (i * 16 + 0x20));
        depth = D_L11_001B18E8;
        quad.pos[0][2] -= depth;
        qcopy(pos1, points + (i * 16 + 0x10));
        quad.pos[1][2] -= depth;
        qcopy(pos2, points + (i * 16 + 0x20));
        quad.pos[2][2] += height + D_L11_001B18F8 * FastSinOrCosA(FastFloatHelperG(quad.pos[0][1]));
        qcopy(pos3, points + (i * 16 + 0x10));
        next_i = i + 1;
        quad.pos[3][2] += height + D_L11_001B18F8 * FastSinOrCosA(FastFloatHelperG(quad.pos[1][1]));
        quad.uv[0][1] = D_L11_001B18B4[0];
        quad.uv[1][1] = D_L11_001B18BC[0];
        quad.uv[2][1] = D_L11_001B18C4[0];
        quad.uv[3][1] = D_L11_001B18CC[0];
        for (j = 0; j < 4; j++) {
            int index = FloatToInt(quad.uv[j][1] + 0.2f);
            float alpha;
            u32 texColor;
            quad.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xD8);
            alpha = FastSinOrCosB(*(float *)(state + 0xD0) * 3.1415927410125732f);
            texColor = D_L11_001B18A8[index];
            quad.color[j] = FastTweenColor(texColor & mask, texColor, alpha);
        }
        draw_world_quad(&quad, 0, 0);
        for (j = 0; j < 4; j++) {
            int index = FloatToInt(quad.uv[j][1] + 0.2f);
            float alpha;
            u32 texColor;
            quad.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xDC);
            alpha = FastSinOrCosB(*(float *)(state + 0xD4) * 3.1415927410125732f);
            texColor = D_L11_001B18A8[index];
            quad.color[j] = FastTweenColor(texColor & 0xFFFFFF, texColor, alpha);
        }
        draw_world_quad(&quad, 0, 0);
    }
    qcopy(quad.pos[0], points + 0x10);
    depth = D_L11_001B18E8;
    quad.pos[0][2] -= depth;
    qcopy(pos1, points + (*(int *)points * 16));
    quad.pos[1][2] -= depth;
    qcopy(pos2, points + 0x10);
    quad.pos[2][2] += height + D_L11_001B18F8 * FastSinOrCosA(FastFloatHelperG(quad.pos[0][1]));
    qcopy(pos3, points + (*(int *)points * 16));
    quad.pos[3][2] += height + D_L11_001B18F8 * FastSinOrCosA(FastFloatHelperG(quad.pos[1][1]));
    quad.uv[0][1] = D_L11_001B18B4[0];
    quad.uv[1][1] = D_L11_001B18BC[0];
    quad.uv[2][1] = D_L11_001B18C4[0];
    quad.uv[3][1] = D_L11_001B18CC[0];
    for (j = 0; j < 4; j++) {
        int index = FloatToInt(quad.uv[j][1] + 0.2f);
        float alpha;
        u32 texColor;
        quad.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xD8);
        alpha = FastSinOrCosB(*(float *)(state + 0xD0) * 3.1415927410125732f);
        texColor = D_L11_001B18A8[index];
        quad.color[j] = FastTweenColor(texColor & 0xFFFFFF, texColor, alpha);
    }
    draw_world_quad(&quad, 0, 0);
    for (j = 0; j < 4; j++) {
        int index = FloatToInt(quad.uv[j][1] + 0.2f);
        float alpha;
        u32 texColor;
        quad.uv[j][0] = D_L11_001B18B0[j][0] + *(float *)(state + 0xDC);
        alpha = FastSinOrCosB(*(float *)(state + 0xD4) * 3.1415927410125732f);
        texColor = D_L11_001B18A8[index];
        quad.color[j] = FastTweenColor(texColor & 0xFFFFFF, texColor, alpha);
    }
    draw_world_quad(&quad, 0, 0);
}
