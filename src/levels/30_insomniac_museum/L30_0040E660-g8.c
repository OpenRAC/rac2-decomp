#include "names.h"
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_beam_quads_glows_alt(void *, float, int, int, int, float, float, int, void *);
extern float D_001B197C __attribute__((sda));
extern float D_001B1980 __attribute__((sda));
extern int D_001B193C __attribute__((sda));
extern int D_001B1940 __attribute__((sda));
extern int D_001B1974 __attribute__((sda));
extern int D_001B1978 __attribute__((sda));

/* Spawns two puffs of dust at the object's position, each with a random size. */
void part_spawn_dust_puff_pair_alt(char *obj) {
    gfx_draw_beam_quads_glows_alt(obj + 0x10, D_001B197C * *(float *)(obj + 0x2C), D_001B193C, math_random_int_range(0x5F, 0x6F), D_001B1974, math_random_angle(), 1.0f, 2, obj);
    gfx_draw_beam_quads_glows_alt(obj + 0x10, D_001B197C * *(float *)(obj + 0x2C) * D_001B1980, D_001B1940, math_random_int_range(0x6F, 0x7F), D_001B1978, math_random_angle(), 1.0f, 2, obj);
}
