#include "common.h"

/* -g is the file's reason to exist: its line labels give the second division below the two nops
   retail has in front of it, so the first division must stay on one line with its multiply. */

typedef struct {
    float pos[4][4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long tag[4];
} WavyLinkStrip;
extern unsigned long func_0027C878(int);
extern void func_0029FCC0(void *, int, void *);
extern float func_00282DF0(void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00283C28(float);
extern void func_00280B90(void *, int, int);
extern char D_L01_001B94C0[];
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* Draws a wavy textured strip from the moby at data + 0x14 to this one, a quad per 0.2 units,
   with its width perpendicular to the view from D_L01_001B94C0. */
void func_L01_0038EF40(char *moby)
{
    WavyLinkStrip strip;
    float start[4] __attribute__((aligned(16)));
    float current[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    float wave[4] __attribute__((aligned(16)));
    float view[4] __attribute__((aligned(16)));
    float width[4] __attribute__((aligned(16)));
    char *data;
    float distance, progress, step, phase, factor, timewave;
    float thickness = 0.05f;
    if (!moby) return;
    data = *(char **)(moby + 0x68);
    if (!data) return;
    strip.tag[1] = GetEffectTextureDescriptor(15);
    strip.color[0] = strip.color[1] = strip.color[2] = strip.color[3] = 0x80808080;
    strip.tag[2] = 0xFF9000000260UL;
    strip.tag[0] = 5;
    strip.tag[3] = 0xFF00000044UL;
    strip.uv[0][0] = 0; strip.uv[0][1] = 0;
    strip.uv[1][0] = 1; strip.uv[1][1] = 0;
    strip.uv[2][0] = 0; strip.uv[2][1] = 1;
    strip.uv[3][0] = 1; strip.uv[3][1] = 1;
    TransformMobyJointToWorld(moby, 0, origin);
    qcopy(start, *(char **)(data + 0x14) + 0x10);
    qcopy(current, start);
    FastVecSub(direction, origin, start);
    progress = 0;
    distance = FastVecLength(direction);
    qcopy(wave, direction);
    wave[2] -= 0.1f;
    FastVecCross(side, direction, wave);
    FastVecCross(up, direction, side);
    qcopy(strip.pos[0], start);
    qcopy(strip.pos[2], start);
    strip.pos[0][2] -= thickness;
    strip.pos[2][2] += thickness;
    factor = FastSinOrCosA(FastFloatHelperG(*(float *)(data + 0x18)));
    while (progress < distance) {
        step = 0.2f;
        if (distance - progress < step) step = distance - progress;
        progress += step;
        phase = 3.1415927f; phase = progress * phase; timewave = FastSinOrCosB(phase / distance);
        thickness = phase / *(float *)(data + 0x1C);
        thickness = FastFloatHelperG(thickness);
        thickness = FastSinOrCosB(thickness);
        thickness *= timewave;
        thickness *= factor;
        thickness *= *(float *)(data + 0x20);
        vec_scale_to_length(direction, direction, step);
        FastVecAdd(current, current, direction);
        qcopy(strip.pos[1], current);
        qcopy(strip.pos[3], current);
        FastVecSub(view, D_L01_001B94C0, current);
        FastVecCross(width, view, direction);
        vec_scale_to_length(width, width, 0.05f);
        FastVecAdd(strip.pos[1], strip.pos[1], width);
        FastVecSub(strip.pos[3], strip.pos[3], width);
        vec_scale_to_length(wave, side, thickness);
        FastVecAdd(strip.pos[1], strip.pos[1], wave);
        FastVecAdd(strip.pos[3], strip.pos[3], wave);
        draw_world_quad(&strip, 0, 1);
        qcopy(start, current);
        qcopy(strip.pos[0], strip.pos[1]);
        qcopy(strip.pos[2], strip.pos[3]);
    }
}

