#include "common.h"
extern void vec_scale_to_length(void *,void *,float),FastVecAdd(void *,void *,void *);
extern int math_random_int_below(int);
extern u8 D_L12_001B9E00[];
extern void FastVecSub(void *,void *,void *),matrix_mul_vec3(void *,void *,void *);
extern float D_L12_001B12C4 __attribute__((sda)),D_L12_001B12C8 __attribute__((sda)),D_L12_001B12CC __attribute__((sda)),D_L12_001B12D0 __attribute__((sda));
extern u8 D_L12_001B12D4 __attribute__((sda));
extern int D_L12_001B12D8 __attribute__((sda)),D_L12_001B12DC __attribute__((sda));
extern float D_L12_001B12E0 __attribute__((sda)),D_L12_001B12E4 __attribute__((sda));
extern int D_L12_001B12E8 __attribute__((sda)),D_L12_001B12EC __attribute__((sda));
extern float D_L12_001B12F0 __attribute__((sda)),D_L12_001B12F4 __attribute__((sda));
extern int D_L12_001B12F8 __attribute__((sda)),D_L12_001B12FC __attribute__((sda));
extern float D_L12_001B1300[4] __attribute__((sda));
extern int D_L12_001B29C8 MACRO_ADDR;
extern void vec_random_direction(void *,float,float);
extern void part_spawn_hero_relative(void *,void *,int,int,int,int,float);
extern float IntToFloat(int),math_fabs(float);
extern int FastTweenColor(int,int,float);
extern void part_spawn_fading(void *,int,int,int,int,int,int,float);
extern void func_00282E70(void *,void *,void *);

/* Draws a trail of sparks and four fading glowing dots that lead toward the hero. */
void gfx_draw_sparkle_trail_to_hero(u8 *moby) {
    float pos[4], velocity[4], delta[4], toward[4], step[4];
    int i, j;

    func_00282E70(pos, D_L12_001B1300, moby + 0xC0);
    FastVecAdd(pos, pos, moby + 0x10);
    if (!math_random_int_below(4)) {
        vec_random_direction(velocity, D_L12_001B12C4 * 0.0166666675f,
                     D_L12_001B12C8 * 0.0166666675f);
        part_spawn_hero_relative(pos, velocity, D_L12_001B12D8, D_L12_001B12D4,
                     (u8)math_random_int_below(255), 0, D_L12_001B12E0);
        for (j = 2; j >= 0; j--) {
            vec_random_direction(delta, D_L12_001B12CC * 0.0166666675f,
                         D_L12_001B12D0 * 0.0166666675f);
            FastVecAdd(velocity, velocity, delta);
            part_spawn_hero_relative(pos, velocity, D_L12_001B12DC, D_L12_001B12D4,
                         (u8)math_random_int_below(255), 0, D_L12_001B12E4);
        }
    }
    FastVecSub(toward, D_L12_001B9E00, pos);
    vec_scale_to_length(toward, toward, -0.3f);
    vec_scale_to_length(step, toward, 0.1f);
    FastVecAdd(toward, toward, pos);
    for (i = 0; i < 4; i++) {
        int color, alpha;

        color = FastTweenColor(D_L12_001B12E8, D_L12_001B12EC,
            math_fabs(0.5f - IntToFloat(
                255 - ((D_L12_001B29C8 + i * 20) & 255)) * 0.00392156886f));
        alpha = *(u8 *)&D_L12_001B29C8;
        if (i & 2) alpha *= 2;
        if (i & 1) alpha = 255 - alpha;
        part_spawn_fading(toward, color, (u8)alpha, D_L12_001B12FC,
                     D_L12_001B12F8, 2, 0,
                     (D_L12_001B12F0 + IntToFloat(i) * D_L12_001B12F4) *
                     (*(float *)(moby + 0x2C) /
                      *(float *)(*(u8 **)(moby + 0x24) + 0x24)));
        FastVecAdd(toward, toward, step);
    }
}
