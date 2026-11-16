#include "include_asm.h"
#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern int g_burst_count __attribute__((sda));
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fabs(float);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern char *bouncing_debris_create(void *, void *, void *);

/* Spawns a bounded set of random vectors outside the central rectangle. */
/* Spawns random bursts around the object, skipping a box in the middle. */
void part_spawn_random_bursts_outside_box(char *object)
{
    float position[4];
    float random[4];
    float direction[4];
    int i;
    float scale;
    for (i = 0; i < g_burst_count; ++i) {
        *(Quadword *)random = 0;
        random[0] = math_random_signed_float_range(0.0f, 26.0f);
        random[1] = math_random_signed_float_range(0.0f, 8.0f);
        random[2] = math_random_float_range(0.0f, 30.0f);
        *(Quadword *)position = *(Quadword *)random;
        if (math_fabs(position[0]) < 9.0f && math_fabs(position[2]) < 25.0f)
            continue;
        scale = *(float *)(object + 44) / *(float *)(*(char **)(object + 36) + 36);
        FastVecScale(position, position, scale);
        matrix_mul_vec3(position, position, object + 192);
        FastVecAdd(position, position, object + 16);
        *(Quadword *)direction = 0;
        direction[0] = math_random_angle();
        direction[1] = math_random_angle();
        direction[2] = math_random_angle();
        *(Quadword *)random = *(Quadword *)direction;
        bouncing_debris_create(object, position, random);
    }
}

