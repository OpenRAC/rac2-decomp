#include "names.h"
/* func_0031D070 in its own unit: the saved position is a 16-byte lq/sq copy, and the
   loop count's decrement stays below it (-frac2-qcopy -frac2-qcopy-barrier). */
#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));

extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(float *, float, float, float);
extern float math_random_signed_float_range(float, float);
/* The three floats come before the last int: retail sets up $f14 before $t2 at every call
   (here, and in func_003258C0 and func_L03_003D0FC8). */
extern void part_spawn_ground_effect(float *, int, int, int, int, float *, float, float, float, int);

/* Throws `count` sparks from the position: each is a random direction and a random drift of
   the position itself, and goes out as a pair of particles, one of each sign. */
void part_spawn_spark_pairs(float *position, int count)
{
    float dir[4];
    float save[4];
    float f20;
    float f21;
    float f22;
    int sign;
    int i;
    float *sv;

    if (count > 0) {
        i = count;
        sv = save;
        do {
            f22 = math_random_float_range(0.1f, 0.25f);
            sign = math_random_int_below(2);
            if (sign == 0)
                sign = sign - 1;
            f21 = math_random_angle();
            f20 = math_random_float_range(0.349065899848938f, 1.5358898639678955f);
            vec_build_spherical_offset(dir, math_random_float_range(0.05f, 0.1f), f21, f20);
            *(Quad *)sv = *(Quad *)position;
            position[0] = position[0] + math_random_signed_float_range(0.0f, 0.15f);
            position[1] = position[1] + math_random_signed_float_range(0.0f, 0.15f);
            position[2] = position[2] + math_random_signed_float_range(0.0f, 0.15f);
            part_spawn_ground_effect(position, 0x1E, 0x7F207F7F, 0, sign, dir, f22 * 0.1f, f22, 0.006f, 0);
            part_spawn_ground_effect(position, 0x1E, 0x7F7F7F7F, 1, -sign, dir, f22 * 0.07f, f22 * 0.7f, 0.006f, 0);
        } while (--i != 0);
    }
}
