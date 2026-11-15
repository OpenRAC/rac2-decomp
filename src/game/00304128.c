#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef union { int q __attribute__((mode(TI))); float f[4]; } TI128;

extern int math_fast_float_d(void *);
extern void surface_grid_random_point(void *, void *);
extern float coll_get_distance_if_in_field(void *, float);
extern void part_spawn_size_changing(void *, void *, int, int, float, int, int, float, float, int, int);

/* The address the buffer is copied from; its value differs from program to program. */
extern char ref_00304128_00[];

/* Emit an effect at a sampled surface point while its timer is active. */
/* Spawns an effect at a random surface point each time the timer runs out. */
void surface_grid_spawn_effect(void *obj)
{
    void *state = *(void **)((char *)obj + 0x68);
    TI128 position;
    TI128 parameters;
    float distance;

    if (!(*(int *)((char *)state + 0x4C) & 8)) {
        if (math_fast_float_d((char *)state + 0x8C) != 0) {
            surface_grid_random_point(obj, &position);
            qcopy(&parameters, ref_00304128_00);
            parameters.f[2] = *(float *)((char *)state + 8);
            distance = coll_get_distance_if_in_field(&position, 4.0f);
            if (1.0f < distance)
                part_spawn_size_changing(&position, &parameters, *(int *)((char *)state + 0x80), 0x00808080,
                        *(float *)((char *)state + 0x78) * 210000.0f,
                        *(int *)((char *)state + 0x74), *(int *)((char *)state + 0x7C), 0.0f,
                        *(float *)((char *)state + 0x88), 0, 3);
            *(int *)((char *)state + 0x8C) = *(int *)((char *)state + 0x84);
        }
    }
}
