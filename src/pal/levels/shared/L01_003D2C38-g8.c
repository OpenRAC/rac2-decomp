#include "common.h"

extern void vec_random_direction(void *, float, float);
extern int math_random_int_below(int);
extern void part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);
extern void part_spawn_fading(void *, int, int, int, int, int, int, float);
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

/* func_PAL_L01_003D2C38, the PAL copy of func_L01_003CEB00: the same C, where 1/60 becomes 1/50 and the
   ring phase takes the 50 Hz scale, so its range 255 becomes 212. */
/* Spawns sparkles and four pulsing rings between the moby and camera. */
void func_PAL_L01_003D2C38(char *m)
{
    float pos[4], v[4], jitter[4], dir[4], step[4];
    int i, c, n;
    int alpha;
    qcopy(pos, m + 0x10);
    if (math_random_int_below(4) == 0) {
        vec_random_direction(v, D_L01_001B0458 * 0.020000001f, D_L01_001B045C * 0.020000001f);
        alpha = D_L01_001B0468;
        n = math_random_int_below(255);
        part_spawn_hero_relative(pos, v, D_L01_001B046C, alpha, n & 255, 0, D_L01_001B0474);
        for (i = 2; i >= 0; i--) {
            int trailAlpha;
            vec_random_direction(jitter, D_L01_001B0460 * 0.020000001f, D_L01_001B0464 * 0.020000001f);
            FastVecAdd(v, v, jitter);
            trailAlpha = D_L01_001B0468;
            n = math_random_int_below(255);
            part_spawn_hero_relative(pos, v, D_L01_001B0470, trailAlpha, n & 255, 0, D_L01_001B0478);
        }
    }
    FastVecSub(dir, &D_L01_001B94C0, pos);
    vec_scale_to_length(dir, dir, -0.3f);
    vec_scale_to_length(step, dir, 0.1f);
    FastVecAdd(dir, dir, pos);
    for (i = 0; i < 4; i++) {
        int ringAlpha;
        unsigned char finalAlpha;
        float t = IntToFloat(212 - ((s32)((ref_L01_003CEB00_0 + i * 20) & 255) * 5 + 2) / 6);
        c = FastTweenColor(D_L01_001B047C, D_L01_001B0480, math_fabs(0.5f - t * (1.0f / 212.0f)));
        ringAlpha = *(unsigned char *)&D_L01_001B2088;
        if (i & 2)
            ringAlpha = ringAlpha * 2;
        if (i & 1)
            ringAlpha = 255 - ringAlpha;
        finalAlpha = ringAlpha;
        t = IntToFloat(i);
        part_spawn_fading(dir, c, finalAlpha, D_L01_001B0490, D_L01_001B048C, 2, 0,
          (D_L01_001B0484 + t * D_L01_001B0488) * (*(float *)(m + 0x2C) / *(float *)(*(char **)(m + 0x24) + 0x24)));
        FastVecAdd(dir, dir, step);
    }
}
