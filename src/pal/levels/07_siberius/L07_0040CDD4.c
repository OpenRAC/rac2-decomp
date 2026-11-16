#include "include_asm.h"


#include "common.h"
extern u8 g_flag_block __attribute__((sda));
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 g_lift_state[];
extern u8 *g_moby_l07_array[] __attribute__((sda));
extern s32 g_entity_group_count[] __attribute__((sda));
extern s32 math_random_int_below(s32 n);
extern s32 math_fast_float_d(s32 *counter);
extern u8 *moby_find_active_in_group(u8 *a);
extern u8 g_moby_update_inhibit_flag __attribute__((sda));
extern void vec_random_direction(void *a, f32 b, f32 c);
extern f32 math_fabs(f32 a);
extern f32 math_random_float_range(f32 a, f32 b);
extern void vec_local_offset_to_world(void *a, void *b, f32 c, f32 d, f32 e);
extern char *part_spawn_drifting_2_pal(void *a, void *b, s32 c);
extern f32 g_spark_burst_scale __attribute__((sda));
extern f32 g_spark_burst_saved_value __attribute__((sda));
extern f32 func_2E4508(void *a, void *b);

/* Runs the object's own 200 steps: each step advances the shared record's third
   float, then the three angles are computed and handed to the shared passes. */
/* Throws 200 sparks out of the object in random directions. */
void part_l07_spawn_spark_burst_pal(u8 *moby)
{
    f32 position[4];
    f32 velocity[4];
    s32 i;
    f32 offset_z;
    f32 offset_y;
    f32 offset_x;

    g_spark_burst_saved_value = g_spark_burst_scale;
    g_spark_burst_scale = 0.99f;
    for (i = 0xC7; i >= 0; i--) {
        vec_random_direction(velocity, 0.020000001f, 0.28000003f);
        velocity[2] = math_fabs(velocity[2]) + 0.10000001f;
        offset_x = math_random_float_range(-5.0f, 5.0f);
        offset_y = math_random_float_range(-5.0f, 5.0f);
        offset_z = math_random_float_range(10.0f, 25.0f);
        vec_local_offset_to_world(moby, position, offset_x, offset_y, offset_z);
        part_spawn_drifting_2_pal(position, velocity, 0x190);
    }
}

