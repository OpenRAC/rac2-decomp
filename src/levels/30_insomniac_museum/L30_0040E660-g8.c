#include "names.h"
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_beam_quads_glows_alt(void *, float, int, int, int, float, float, int, void *);
extern float g_dust_puff_scale_a __attribute__((sda));
extern float g_dust_puff_scale_b __attribute__((sda));
extern int g_dust_puff_param_a __attribute__((sda));
extern int g_dust_puff_param_b __attribute__((sda));
extern int g_dust_puff_color_a __attribute__((sda));
extern int g_dust_puff_color_b __attribute__((sda));

/* Spawns two puffs of dust at the object's position, each with a random size. */
void part_spawn_dust_puff_pair_alt(char *obj) {
    gfx_draw_beam_quads_glows_alt(obj + 0x10, g_dust_puff_scale_a * *(float *)(obj + 0x2C), g_dust_puff_param_a, math_random_int_range(0x5F, 0x6F), g_dust_puff_color_a, math_random_angle(), 1.0f, 2, obj);
    gfx_draw_beam_quads_glows_alt(obj + 0x10, g_dust_puff_scale_a * *(float *)(obj + 0x2C) * g_dust_puff_scale_b, g_dust_puff_param_b, math_random_int_range(0x6F, 0x7F), g_dust_puff_color_b, math_random_angle(), 1.0f, 2, obj);
}
