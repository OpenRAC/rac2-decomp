#include "names.h"
/* func_PAL_L02_003C91F0, the PAL copy of func_L02_003C5438: the same C, where scale (u32)a3; wrap (u32)a1 (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_ground_effect(void *, u32, u32, f32, f32, u32, s32, void *, f32, s32);
extern char g_zero_l02_vector[] __attribute__((sda));

/* Spawn one particle and, when both secondary parameters are set, its opposite. */
void spawn_opposed_particles_pal(void *position, void *ticks_a, void *color_a, void *ticks_b, void *color_b)
{
    TI128 v;
    float size;
    float zero = 0.0f;
    int spin_sign;

    v = *(TI128 *)position;
    size = math_random_float_range(2.0f, 4.0f);
    spin_sign = math_random_int_below(2);
    if (spin_sign == 0)
        spin_sign--;
    part_spawn_ground_effect(&v, (((int)((u32)ticks_a) * 5 + 2) / 6), (u32)color_a, size * 0.3f, size, 0, spin_sign, g_zero_l02_vector, zero, 0);
    if (ticks_b != 0 && color_b != 0)
        part_spawn_ground_effect(&v, (((int)((u32)ticks_b) * 5 + 2) / 6), (u32)color_b, size * 0.04f, size * 0.4f, 1, -spin_sign, g_zero_l02_vector, zero, 0);
}
