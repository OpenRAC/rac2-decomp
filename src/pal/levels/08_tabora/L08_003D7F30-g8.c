#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* Tuning words read by func_PAL_L08_003D7F30. */
extern float g_seesaw_spark_speed_min __attribute__((sda));
extern float g_seesaw_spark_speed_max __attribute__((sda));
extern float g_seesaw_step_speed_min __attribute__((sda));
extern float g_seesaw_step_speed_max __attribute__((sda));
extern unsigned char g_seesaw_spark_angle_byte __attribute__((sda));
extern int g_seesaw_spark_color_a __attribute__((sda));
extern int g_seesaw_spark_color_b __attribute__((sda));
extern float g_seesaw_spark_size_a __attribute__((sda));
extern float g_seesaw_spark_size_b __attribute__((sda));
extern int g_seesaw_ring_color_start __attribute__((sda));
extern int g_seesaw_ring_color_end __attribute__((sda));
extern int g_seesaw_ring_fade_param __attribute__((sda));
extern int g_seesaw_ring_size_param __attribute__((sda));
/* The frame counter: absolute loads, $gp in a delay slot. */
extern int g_frame_l08_counter MACRO_ADDR;
extern char g_hero_position_vec[];

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
        vec_random_direction(&velocity, g_seesaw_spark_speed_min * 0.020000001f, g_seesaw_spark_speed_max * 0.020000001f);
        b = g_seesaw_spark_angle_byte;
        part_spawn_hero_relative(&joint, &velocity, g_seesaw_spark_color_a, b, math_random_int_below(255), 0, g_seesaw_spark_size_a);
        for (count = 2; count >= 0; count--) {
            vec_random_direction(&step, g_seesaw_step_speed_min * 0.020000001f, g_seesaw_step_speed_max * 0.020000001f);
            FastVecAdd(&velocity, &velocity, &step);
            b = g_seesaw_spark_angle_byte;
            part_spawn_hero_relative(&joint, &velocity, g_seesaw_spark_color_b, b, math_random_int_below(255), 0, g_seesaw_spark_size_b);
        }
    }
    FastVecSub(&ring, g_hero_position_vec, &joint);
    vec_scale_to_length(&ring, &ring, -0.3f);
    vec_scale_to_length(&ring_step, &ring, 0.1f);
    FastVecAdd(&ring, &ring, &joint);
    for (k = 0; k < 4; k++) {
        spacing = 20;
        frame = g_frame_l08_counter;
        t = IntToFloat(((s32)0xFF * 5 + 2) / 6
                          - ((s32)((frame + k * spacing) & 0xFF) * 5 + 2) / 6);
        color = FastTweenColor(g_seesaw_ring_color_start, g_seesaw_ring_color_end, math_fabs(0.5f - t * 0.004716981f));
        b = g_frame_l08_counter & 0xFF;
        if (k & 2)
            b = b * 2;
        if (k & 1)
            b = 0xFF - b;
        part_spawn_fading(&ring, color, b, g_seesaw_ring_size_param, g_seesaw_ring_fade_param, 2, 0,
                      (IntToFloat(k) + 3.0f)
                          * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        FastVecAdd(&ring, &ring, &ring_step);
    }
}
