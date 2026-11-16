#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_snivelak_fire_speed_min __attribute__((sda));
extern float g_snivelak_fire_speed_max;
extern u32 g_snivelak_fire_big_param_a __attribute__((sda));
extern u32 g_snivelak_fire_big_param_b;
extern u32 g_snivelak_fire_mid_param_a;
extern u32 g_snivelak_fire_mid_param_b;
extern u32 g_snivelak_fire_small_param_a;
extern u32 g_snivelak_fire_small_param_b;
extern u32 g_snivelak_fire_big_end_param __attribute__((sda));
extern u32 g_snivelak_fire_mid_end_param;
extern u32 g_snivelak_fire_small_end_param;
extern s32 g_frame_l16_counter;

extern void moby_transform_joint_to_world(char *, int, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern char *part_spawn_scaling(void *, void *, u32, s32, s32, s32, s32, s32);

/* The burst of func_L02_00401D38, from the object's two attachment points (func_0029FCC0)
   instead of a fixed pair of vectors. */
/* Emits a small burst of fire particles from the object's two attach points. */
void snivelak_emit_fire_burst(char *moby) {
    float position[4];
    float velocity[4];
    float fall[4];
    s32 i;
    float speed;
    float rate = 0.016666668f;

    for (i = 0; i < 2; i++) {
        *(TI128 *)fall = 0;
        speed = math_random_float_range(g_snivelak_fire_speed_min, g_snivelak_fire_speed_max);
        fall[2] = -(speed * rate);
        *(TI128 *)velocity = *(TI128 *)fall;
        moby_transform_joint_to_world(moby, i, position);
        if (g_frame_l16_counter & 1) {
            part_spawn_scaling(position, velocity, g_snivelak_fire_big_param_a, g_snivelak_fire_big_param_b, math_random_int_range(0x12, 0x16), g_snivelak_fire_big_end_param, -10, 1);
        } else {
            part_spawn_scaling(position, velocity, g_snivelak_fire_mid_param_a, g_snivelak_fire_mid_param_b, math_random_int_range(0x14, 0x18), g_snivelak_fire_mid_end_param, -10, 1);
        }
        part_spawn_scaling(position, velocity, g_snivelak_fire_small_param_a, g_snivelak_fire_small_param_b, math_random_int_range(0xA, 0xF), g_snivelak_fire_small_end_param, -10, 1);
    }
}
