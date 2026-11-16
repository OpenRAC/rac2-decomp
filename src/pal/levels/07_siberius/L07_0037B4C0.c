#include "include_asm.h"



#include "common.h"
extern char g_hero_position_block[];
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern void math_random_planar_offset(float *, float);
extern char *part_spawn_snow_pal(float *, float *, s32, s32);

/* Scatter 200 particles around the camera target, then set the moby's position 4 ahead of it. */
void part_scatter_around_camera_pal(u8 *moby)
{
    f32 spawn_pos[4] __attribute__((aligned(16)));
    f32 spawn_vel[4] __attribute__((aligned(16)));
    f32 ahead[4] __attribute__((aligned(16)));
    f32 *vars = *(f32 **)(moby + 0x68);
    s32 i;

    for (i = 0; i < 200; i++) {
        math_random_planar_offset(spawn_pos, 15.0f);
        spawn_pos[2] = math_random_float_range(-7.0f, 7.0f);
        FastVecAdd(spawn_pos, spawn_pos, g_hero_position_block);
        FastVecScale(ahead, g_hero_position_block + 0x230, 4.0f);
        FastVecAdd(spawn_pos, ahead, spawn_pos);
        math_random_planar_offset(spawn_vel, vars[0] * 0.020000001f);
        spawn_vel[2] = -(vars[1] * 0.020000001f) * math_random_float_range(0.8f, 1.2f);
        part_spawn_snow_pal(spawn_pos, spawn_vel, 0, 1);
    }
    FastVecScale(ahead, g_hero_position_block + 0x230, 4.0f);
    FastVecAdd(vars + 0x60 / 4, ahead, g_hero_position_block);
}

