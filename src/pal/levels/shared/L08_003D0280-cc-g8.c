#include "names.h"
/* func_PAL_L08_003D0280, the PAL copy of func_L08_003CC4B8: the same C, where 0.016666668f becomes
   0.020000001f and the ring colour's 0xFF becomes its 50 Hz scale, 0xD4 = (0xFF * 5 + 2) / 6, with
   the counter scaled the same way and 1/255 becoming 1/212. The longer loop keeps its float
   constants and 0xFF inside; the 20 in a local keeps k * 20 a reduced counter. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* Tuning words read by func_PAL_L08_003D0280. */
extern float g_spark_velocity_min __attribute__((sda));
extern float g_spark_velocity_max __attribute__((sda));
extern float g_spark_step_min __attribute__((sda));
extern float g_spark_step_max __attribute__((sda));
extern unsigned char g_spark_angle_byte __attribute__((sda));
extern int g_spark_hero_type_a __attribute__((sda));
extern int g_spark_hero_type_b __attribute__((sda));
extern float g_spark_hero_scale_a __attribute__((sda));
extern float g_spark_hero_scale_b __attribute__((sda));
extern int g_spark_ring_color_a __attribute__((sda));
extern int g_spark_ring_color_b __attribute__((sda));
extern int g_spark_fade_param __attribute__((sda));
extern int g_spark_ring_particle_param __attribute__((sda));
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

/* After a one-in-four roll, spawns four particles from joint 0 whose velocity grows by a
   random step each time; then draws four rings between the moby and the point at
   D_L08_001B9B00, laid out as RAC1's update_gold_bolt_glow_rings lays out its rings: each
   ring's colour follows the frame counter, and its byte argument (the ring angle in RAC1)
   is the counter's low byte, doubled and/or inverted by the ring index. */
void gfx_draw_glowing_spark_rings_pal(char *obj)
{
    TI128 joint, velocity, step, ring, ring_step;
    int count;
    int k;
    int spacing = 20;
    int b;
    float t;
    int color;

    moby_transform_joint_to_world(obj, 0, &joint);
    if (math_random_int_below(4) == 0) {
        vec_random_direction(&velocity, g_spark_velocity_min * 0.020000001f, g_spark_velocity_max * 0.020000001f);
        b = g_spark_angle_byte;
        part_spawn_hero_relative(&joint, &velocity, g_spark_hero_type_a, b, math_random_int_below(255), 0, g_spark_hero_scale_a);
        for (count = 2; count >= 0; count--) {
            vec_random_direction(&step, g_spark_step_min * 0.020000001f, g_spark_step_max * 0.020000001f);
            FastVecAdd(&velocity, &velocity, &step);
            b = g_spark_angle_byte;
            part_spawn_hero_relative(&joint, &velocity, g_spark_hero_type_b, b, math_random_int_below(255), 0, g_spark_hero_scale_b);
        }
    }
    FastVecSub(&ring, g_hero_position_vec, &joint);
    vec_scale_to_length(&ring, &ring, -0.3f);
    vec_scale_to_length(&ring_step, &ring, 0.1f);
    FastVecAdd(&ring, &ring, &joint);
    for (k = 0; k < 4; k++) {
        t = IntToFloat(0xD4 - (((g_frame_l08_counter + k * spacing) & 0xFF) * 5 + 2) / 6);
        color = FastTweenColor(g_spark_ring_color_a, g_spark_ring_color_b, math_fabs(0.5f - t * 0.004716981f));
        b = g_frame_l08_counter & 0xFF;
        if (k & 2)
            b = b * 2;
        if (k & 1)
            b = 0xFF - b;
        part_spawn_fading(&ring, color, b, g_spark_ring_particle_param, g_spark_fade_param, 2, 0,
                      (IntToFloat(k) + 3.0f)
                          * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        FastVecAdd(&ring, &ring, &ring_step);
    }
}
