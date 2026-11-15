#include "common.h"

extern void func_002A7A00(void *, float, float);
extern int func_002A77E0(int);
extern void func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);
extern void func_002C2FD8(void *, int, int, int, int, int, int, float);
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float f[4]; } Vector;
extern Vector D_L01_001B94C0;
extern int D_L01_001B2088;
extern int ref_L01_003CEB00_0;
extern float D_L01_001B0458 __attribute__((sda));
extern float D_L01_001B045C __attribute__((sda));
extern float D_L01_001B0460 __attribute__((sda));
extern float D_L01_001B0464 __attribute__((sda));
extern unsigned char D_L01_001B0468 __attribute__((sda));
extern int D_L01_001B046C __attribute__((sda));
extern int D_L01_001B0470 __attribute__((sda));
extern float D_L01_001B0474 __attribute__((sda));
extern float D_L01_001B0478 __attribute__((sda));
extern int D_L01_001B047C __attribute__((sda));
extern int D_L01_001B0480 __attribute__((sda));
extern float D_L01_001B0484 __attribute__((sda));
extern float D_L01_001B0488 __attribute__((sda));
extern int D_L01_001B048C __attribute__((sda));
extern int D_L01_001B0490 __attribute__((sda));

/* Spawns sparkles and four pulsing rings between the moby and camera. */
void func_L01_003CEB00(char *m)
{
    float pos[4], v[4], jitter[4], dir[4], step[4];
    int i, c, n;
    int alpha;
    float colorScale;
    float midpoint;
    qcopy(pos, m + 0x10);
    if (func_002A77E0(4) == 0) {
        func_002A7A00(v, D_L01_001B0458 * (1.0f / 60.0f), D_L01_001B045C * (1.0f / 60.0f));
        alpha = D_L01_001B0468;
        n = func_002A77E0(255);
        func_002C3150(pos, v, D_L01_001B046C, alpha, n & 255, 0, D_L01_001B0474);
        for (i = 2; i >= 0; i--) {
            int trailAlpha;
            func_002A7A00(jitter, D_L01_001B0460 * (1.0f / 60.0f), D_L01_001B0464 * (1.0f / 60.0f));
            FastVecAdd(v, v, jitter);
            trailAlpha = D_L01_001B0468;
            n = func_002A77E0(255);
            func_002C3150(pos, v, D_L01_001B0470, trailAlpha, n & 255, 0, D_L01_001B0478);
        }
    }
    colorScale = 1.0f / 255.0f;
    FastVecSub(dir, &D_L01_001B94C0, pos);
    midpoint = 0.5f;
    vec_scale_to_length(dir, dir, -0.3f);
    vec_scale_to_length(step, dir, 0.1f);
    FastVecAdd(dir, dir, pos);
    for (i = 0; i < 4; i++) {
        int ringAlpha;
        unsigned char finalAlpha;
        float t = IntToFloat(255 - ((ref_L01_003CEB00_0 + i * 20) & 255));
        c = FastTweenColor(D_L01_001B047C, D_L01_001B0480, func_00282C48(midpoint - t * colorScale));
        ringAlpha = *(unsigned char *)&D_L01_001B2088;
        if (i & 2)
            ringAlpha = ringAlpha * 2;
        if (i & 1)
            ringAlpha = 255 - ringAlpha;
        finalAlpha = ringAlpha;
        t = IntToFloat(i);
        func_002C2FD8(dir, c, finalAlpha, D_L01_001B0490, D_L01_001B048C, 2, 0,
          (D_L01_001B0484 + t * D_L01_001B0488) * (*(float *)(m + 0x2C) / *(float *)(*(char **)(m + 0x24) + 0x24)));
        FastVecAdd(dir, dir, step);
    }
}
