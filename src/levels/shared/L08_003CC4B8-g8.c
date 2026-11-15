#include "common.h"


typedef int TI128 __attribute__((mode(TI)));

/* Tuning words read by func_L08_003CC4B8. */
extern float D_L08_001AFEEC __attribute__((sda));
extern float D_L08_001AFEF0 __attribute__((sda));
extern float D_L08_001AFEF4 __attribute__((sda));
extern float D_L08_001AFEF8 __attribute__((sda));
extern unsigned char D_L08_001AFEFC __attribute__((sda));
extern int D_L08_001AFF00 __attribute__((sda));
extern int D_L08_001AFF04 __attribute__((sda));
extern float D_L08_001AFF08 __attribute__((sda));
extern float D_L08_001AFF0C __attribute__((sda));
extern int D_L08_001AFF10 __attribute__((sda));
extern int D_L08_001AFF14 __attribute__((sda));
extern int D_L08_001AFF1C __attribute__((sda));
extern int D_L08_001AFF20 __attribute__((sda));
/* The frame counter: absolute loads, $gp in a delay slot. */
extern int D_L08_001B2508 MACRO_ADDR;
extern char D_L08_001B9B00[];

extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_random_int_below(int);
extern void vec_random_direction(void *, float, float);
extern void part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern unsigned char *part_spawn_fading(void *, int, unsigned char, int, int, int, int, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);

/* The parameter block of the shared spawn routines (func_L04_003A1A78 and its siblings). */
typedef struct {
    int kind;
    int count;
    void *table0;
    void *table1;
    void *small0;
    void *counts;
    void *table2;
    void *table3;
    void *small1;
    void *small2;
    void *owner;
    void *callback;
    void *callback2;
} L08SpawnBlock;

extern char g_hero_state[];
extern int D_L08_001B01B8[2] __attribute__((sda));
/* Kind 7 consumes seven halfwords; the full owner extent remains unknown. */
extern int D_L08_001B01D8 __attribute__((sda));
extern int D_L08_001B01DC __attribute__((sda));
extern void water_init_object(L08SpawnBlock *);

/* Runs the shared spawn routines for the object, unless the level's player (the entity at
   D_00189E20+0x1830, kind 0x45) is alive while the mode word at +0x2294 is 0x31. The count
   is the state's +0x10 plus an entry of D_L08_001B01B8 picked by +0x18 (1 when -1); state
   0 sets the object up first and then shares state 1's step, state 2 has its own. */

/* Gives a glowing object a trail of sparks and four glowing rings that pulse over time. */
/* After a one-in-four roll, spawns four particles from joint 0 whose velocity grows by a
   random step each time; then draws four rings between the moby and the point at
   D_L08_001B9B00, laid out as RAC1's update_gold_bolt_glow_rings lays out its rings: each
   ring's colour follows the frame counter, and its byte argument (the ring angle in RAC1)
   is the counter's low byte, doubled and/or inverted by the ring index. */
void gfx_draw_glowing_spark_rings(char *moby)
{
    TI128 joint, velocity, step, ring, ring_step;
    int spark_index;
    int ring_index;
    int angle_byte;
    float ring_age;
    float inverse255, half, base_size;
    int ring_color;

    moby_transform_joint_to_world(moby, 0, &joint);
    if (math_random_int_below(4) == 0) {
        vec_random_direction(&velocity, D_L08_001AFEEC * 0.016666668f, D_L08_001AFEF0 * 0.016666668f);
        angle_byte = D_L08_001AFEFC;
        part_spawn_hero_relative(&joint, &velocity, D_L08_001AFF00, angle_byte, math_random_int_below(255), 0, D_L08_001AFF08);
        for (spark_index = 2; spark_index >= 0; spark_index--) {
            vec_random_direction(&step, D_L08_001AFEF4 * 0.016666668f, D_L08_001AFEF8 * 0.016666668f);
            FastVecAdd(&velocity, &velocity, &step);
            angle_byte = D_L08_001AFEFC;
            part_spawn_hero_relative(&joint, &velocity, D_L08_001AFF04, angle_byte, math_random_int_below(255), 0, D_L08_001AFF0C);
        }
    }
    FastVecSub(&ring, D_L08_001B9B00, &joint);
    vec_scale_to_length(&ring, &ring, -0.3f);
    vec_scale_to_length(&ring_step, &ring, 0.1f);
    FastVecAdd(&ring, &ring, &joint);
    inverse255 = 0.003921569f;
    half = 0.5f;
    base_size = 3.0f;
    for (ring_index = 0; ring_index < 4; ring_index++) {
        ring_age = IntToFloat(0xFF - ((D_L08_001B2508 + ring_index * 20) & 0xFF));
        ring_color = FastTweenColor(D_L08_001AFF10, D_L08_001AFF14, math_fabs(half - ring_age * inverse255));
        angle_byte = D_L08_001B2508 & 0xFF;
        if (ring_index & 2)
            angle_byte = angle_byte * 2;
        if (ring_index & 1)
            angle_byte = 0xFF - angle_byte;
        part_spawn_fading(&ring, ring_color, angle_byte, D_L08_001AFF20, D_L08_001AFF1C, 2, 0,
                      (IntToFloat(ring_index) + base_size)
                          * (*(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24)));
        FastVecAdd(&ring, &ring, &ring_step);
    }
}
