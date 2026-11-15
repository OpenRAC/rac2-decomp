#include "common.h"

extern char D_L07_001B9200[];
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern void math_random_planar_offset(float *, float);
extern void part_spawn_snow(float *, float *, s32, s32);

/* Scatter 200 particles around the camera target, then set the moby's position 4 ahead of it. */
void part_scatter_around_camera(u8 *moby)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 vel[4] __attribute__((aligned(16)));
    f32 ahead[4] __attribute__((aligned(16)));
    f32 *vars = *(f32 **)(moby + 0x68);
    s32 i;

    for (i = 0; i < 200; i++) {
        math_random_planar_offset(pos, 15.0f);
        pos[2] = math_random_float_range(-7.0f, 7.0f);
        FastVecAdd(pos, pos, D_L07_001B9200);
        FastVecScale(ahead, D_L07_001B9200 + 0x230, 4.0f);
        FastVecAdd(pos, ahead, pos);
        math_random_planar_offset(vel, vars[0] * 0.0166666675f);
        vel[2] = -(vars[1] * 0.0166666675f) * math_random_float_range(0.8f, 1.2f);
        part_spawn_snow(pos, vel, 0, 1);
    }
    FastVecScale(ahead, D_L07_001B9200 + 0x230, 4.0f);
    FastVecAdd(vars + 0x60 / 4, ahead, D_L07_001B9200);
}
