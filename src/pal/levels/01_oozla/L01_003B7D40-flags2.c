#include "include_asm.h"

#include "common.h"
typedef int V4 __attribute__((mode(TI)));
extern float coll_probe_ground_height_below(void *a0, int a1, float f12);
extern int GetCollHitMaterial(void);
extern void vec_add_random_offset(float *v, float f);
extern float level_get_water_height_pal(void);
extern float math_random_float_range(float a, float b);
extern int math_random_int_below(int a);
extern void *part_spawn_drifting(char *a0, int a1, int a2, float f12, float f13);
extern float FastVecLength(void *a0);
extern void part_spawn_water_splash_effects_pal(void *a0, int a1, int a2, int a3);
extern f32 g_water_l01_height[];

/* Makes bubbles rise from the object when it is over water, and a splash when it is moving fast (PAL version). */
void swamp_beast_spawn_bubbles_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float bubble_pos[4];
    float value;
    int i;

    coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *moby_pos = moby + 0x10;
        u8 *state_vel = state + 0xE0;
        i = 0;
        while (i >= 0) {
            *(V4 *)bubble_pos = *(V4 *)moby_pos;
            vec_add_random_offset(bubble_pos, 0.15f);
            bubble_pos[2] = level_get_water_height_pal();
            value = math_random_float_range(0.3f, 2.5f);
            part_spawn_drifting((char *)bubble_pos, (int)g_water_l01_height,
                          (int)((((u32)math_random_int_below(6) + 0x14) << 24) | 0x5060), value, 13200.001f);
            i--;
        }
        value = 0.040000003f;
        if (value < FastVecLength(state_vel) || value < FastVecLength(state + 0x2F0))
            part_spawn_water_splash_effects_pal(moby, 3, 10, 1);
    }
}
