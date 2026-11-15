#include "common.h"

extern f32 D_001AC1A0[4] __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Two puffs at the object's offset point, each with a small random drift and growth. */
/* Puffs out two small clouds of smoke from the ship. */
void ship_spawn_exhaust_puffs(char *object)
{
    f32 position[4] __attribute__((aligned(16)));
    f32 from[4] __attribute__((aligned(16)));
    f32 to[4] __attribute__((aligned(16)));
    int i;

    matrix_mul_vec3(position, D_001AC1A0, object + 0xC0);
    FastVecAdd(position, position, object + 0x10);
    for (i = 0; i < 2; i++) {
        from[0] = math_random_float_range(-0.008333334f, 0.008333334f);
        from[1] = math_random_float_range(-0.008333334f, 0.008333334f);
        from[2] = math_random_float_range(-0.008333334f, 0.008333334f);
        from[3] = math_random_float_range(0.6f, 0.8f);
        qcopy(to, from);
        to[3] = from[3] + math_random_float_range(0.1f, 0.2f);
        part_spawn_trail(position, from, to, 0x30C0C0C0, 0x20C0C0C0, 4, 0x10, math_random_int_below(0xC) + 8, 0x17);
    }
}
