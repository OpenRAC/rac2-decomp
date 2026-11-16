#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern float ref_L00_002E8F80_00[][4];
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Six sparks from the table, each placed by the object's matrices and given a
   small random drift; `height` lifts the drift's z. */
void part_spawn_object_sparks_pal(char *object, float height)
{
    float from[3] __attribute__((aligned(16)));
    float to[3] __attribute__((aligned(16)));
    float position[3] __attribute__((aligned(16)));
    int i;

    for (i = 0; i < 6; i++) {
        from[0] = math_random_float_range(-0.020000001f, 0.020000001f);
        from[1] = math_random_float_range(-0.020000001f, 0.020000001f);
        from[2] = height + math_random_float_range(-0.0050000004f, 0.0050000004f);
        from[3] = 0.4f;
        qcopy(to, from);
        to[3] = 0.6f;
        qcopy(position, ref_L00_002E8F80_00[i]);
        matrix_mul_vec3(position, position, object + 0xC0);
        FastVecAdd(position, position, object + 0x10);
        part_spawn_trail(position, from, to, 0x30F0F0F0, 0x14F0F0F0, 3, 3, math_random_int_below(3) + 3, 0x17);
    }
}
