#include "names.h"
/* func_PAL_L12_004075B8, the PAL copy of func_L12_00402B48: the same C at 50 Hz (0.02f steps, the
   0-255 phase scaled by 5/6 so its range is 212). */
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
extern void *part_spawn_hero_relative(void *,void *,int,int,int,int,float);
extern float IntToFloat(int),math_fabs(float);
extern int FastTweenColor(int,int,float);
extern unsigned char *part_spawn_fading(void *,int,int,int,int,int,int,float);
extern void func_00282E70(void *,void *,void *);

void func_PAL_L12_004075B8(u8 *o) {
    float pos[4], v[4], delta[4], toward[4], step[4];
    int i, j;

    func_00282E70(pos, D_L12_001B1300, o + 0xC0);
    FastVecAdd(pos, pos, o + 0x10);
    if (!math_random_int_below(4)) {
        vec_random_direction(v, D_L12_001B12C4 * 0.020000001f,
                     D_L12_001B12C8 * 0.020000001f);
        part_spawn_hero_relative(pos, v, D_L12_001B12D8, D_L12_001B12D4,
                     (u8)math_random_int_below(255), 0, D_L12_001B12E0);
        for (j = 2; j >= 0; j--) {
            vec_random_direction(delta, D_L12_001B12CC * 0.020000001f,
                         D_L12_001B12D0 * 0.020000001f);
            FastVecAdd(v, v, delta);
            part_spawn_hero_relative(pos, v, D_L12_001B12DC, D_L12_001B12D4,
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
                212 - ((s32)((D_L12_001B29C8 + i * 20) & 255) * 5 + 2) / 6) * 0.004716981f));
        alpha = *(u8 *)&D_L12_001B29C8;
        if (i & 2) alpha *= 2;
        if (i & 1) alpha = 255 - alpha;
        part_spawn_fading(toward, color, (u8)alpha, D_L12_001B12FC,
                     D_L12_001B12F8, 2, 0,
                     (D_L12_001B12F0 + IntToFloat(i) * D_L12_001B12F4) *
                     (*(float *)(o + 0x2C) /
                      *(float *)(*(u8 **)(o + 0x24) + 0x24)));
        FastVecAdd(toward, toward, step);
    }
}
