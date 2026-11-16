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
extern f32 g_water_l01_height[];

/* Same body as func_L01_003B4480, with this function's own callees. */
void part_spawn_moving_bubbles_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float pos[4];
    float size;
    int i;

    coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
    if (GetCollHitMaterial() != 3)
        return;
    {
        u8 *position = moby + 0x10;
        u8 *velocity = vars + 0x190;
        i = 0;
        while (i >= 0) {
            *(V4 *)pos = *(V4 *)position;
            vec_add_random_offset(pos, 0.1f);
            pos[2] = level_get_water_height_pal();
            size = math_random_float_range(0.2f, 2.0f);
            part_spawn_drifting((char *)pos, (int)g_water_l01_height,
                          (int)((((u32)math_random_int_below(6) + 0x14) << 24) | 0x5060), size, 1.2e+04f);
            i--;
        }
        if (0.040000003f < FastVecLength(velocity))
            part_spawn_water_splash_bubbles_pal(moby, 3, 10, 1);
    }
}
