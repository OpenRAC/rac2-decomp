#include "common.h"


typedef int V4 __attribute__((mode(TI)));
extern float coll_probe_ground_height_below(void *a0, int a1, float f12);
extern int GetCollHitMaterial(void);
extern void vec_add_random_offset(float *v, float f);
extern float level_get_water_height(void);
extern float math_random_float_range(float a, float b);
extern int math_random_int_below(int a);
extern void part_spawn_drifting(char *a0, int a1, int a2, float f12, float f13);
extern float FastVecLength(void *a0);
extern f32 D_L01_001AFE18[];

/* Same body as func_L01_003B4480, with this function's own callees. */
/* Makes bubbles while the object moves and spawns a splash when it is fast enough. */
void part_spawn_moving_bubbles(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float bubble_pos[4];
    float size;
    int i;

    coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *obj_pos = moby + 0x10;
        u8 *velocity_vec = state + 0x190;
        i = 0;
        while (i >= 0) {
            *(V4 *)bubble_pos = *(V4 *)obj_pos;
            vec_add_random_offset(bubble_pos, 0.1f);
            bubble_pos[2] = level_get_water_height();
            size = math_random_float_range(0.2f, 2.0f);
            part_spawn_drifting((char *)bubble_pos, (int)D_L01_001AFE18,
                          (int)((((u32)math_random_int_below(6) + 0x14) << 24) | 0x5060), size, 10000.0f);
            i--;
        }
        if (0.0333333333f < FastVecLength(velocity_vec))
            part_spawn_water_splash_bubbles(moby, 3, 10, 1);
    }
}
