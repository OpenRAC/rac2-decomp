#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* Tuning words read by func_PAL_L08_003D7F30. */
extern float D_L08_001B0338 __attribute__((sda));
extern float D_L08_001B033C __attribute__((sda));
extern float D_L08_001B0340 __attribute__((sda));
extern float D_L08_001B0344 __attribute__((sda));
extern unsigned char D_L08_001B0348 __attribute__((sda));
extern int D_L08_001B034C __attribute__((sda));
extern int D_L08_001B0350 __attribute__((sda));
extern float D_L08_001B0354 __attribute__((sda));
extern float D_L08_001B0358 __attribute__((sda));
extern int D_L08_001B035C __attribute__((sda));
extern int D_L08_001B0360 __attribute__((sda));
extern int D_L08_001B0368 __attribute__((sda));
extern int D_L08_001B036C __attribute__((sda));
/* The frame counter: absolute loads, $gp in a delay slot. */
extern int D_L08_001B2508 MACRO_ADDR;
extern char D_L08_001B9B00[];

extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_random_int_below(int);
extern void vec_random_direction(void *, float, float);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern unsigned char *part_spawn_fading(void *, int, unsigned char, int, int, int, int, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);

/* func_PAL_L08_003D7F30, the PAL copy of func_L08_003D3EF8: the same C, where 1/60 becomes
   0.02 and the ring colour's frame phase takes the 50 Hz scale, so its 255 becomes 212 and
   1/255 becomes 1/212. The ring constants stay in the loop here: the scale makes it too long
   for loop.c to hoist them. Only the spacing, a local whose life spans the frame load, leaves. */
void func_PAL_L08_003D7F30(char *obj)
{
    TI128 joint, velocity, step, ring, ring_step;
    int count;
    int k;
    int spacing;
    int frame;
    int b;
    float t;
    int color;

    moby_transform_joint_to_world(obj, 0, &joint);
    if (math_random_int_below(4) == 0) {
        vec_random_direction(&velocity, D_L08_001B0338 * 0.020000001f, D_L08_001B033C * 0.020000001f);
        b = D_L08_001B0348;
        part_spawn_hero_relative(&joint, &velocity, D_L08_001B034C, b, math_random_int_below(255), 0, D_L08_001B0354);
        for (count = 2; count >= 0; count--) {
            vec_random_direction(&step, D_L08_001B0340 * 0.020000001f, D_L08_001B0344 * 0.020000001f);
            FastVecAdd(&velocity, &velocity, &step);
            b = D_L08_001B0348;
            part_spawn_hero_relative(&joint, &velocity, D_L08_001B0350, b, math_random_int_below(255), 0, D_L08_001B0358);
        }
    }
    FastVecSub(&ring, D_L08_001B9B00, &joint);
    vec_scale_to_length(&ring, &ring, -0.3f);
    vec_scale_to_length(&ring_step, &ring, 0.1f);
    FastVecAdd(&ring, &ring, &joint);
    for (k = 0; k < 4; k++) {
        spacing = 20;
        frame = D_L08_001B2508;
        t = IntToFloat(((s32)0xFF * 5 + 2) / 6
                          - ((s32)((frame + k * spacing) & 0xFF) * 5 + 2) / 6);
        color = FastTweenColor(D_L08_001B035C, D_L08_001B0360, math_fabs(0.5f - t * 0.004716981f));
        b = D_L08_001B2508 & 0xFF;
        if (k & 2)
            b = b * 2;
        if (k & 1)
            b = 0xFF - b;
        part_spawn_fading(&ring, color, b, D_L08_001B036C, D_L08_001B0368, 2, 0,
                      (IntToFloat(k) + 3.0f)
                          * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        FastVecAdd(&ring, &ring, &ring_step);
    }
}
