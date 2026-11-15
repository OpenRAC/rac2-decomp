#include "common.h"
typedef unsigned int DebrisQuad __attribute__((mode(TI)));
typedef union { DebrisQuad q; float f[4]; } DebrisVector;
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
/* EE integer and floating-point argument banks retain their measured order. */
extern void SpawnTintedEffects(void *, void *, float, int, int, void *, float, float, unsigned int, float, int);
/* Throws a number of debris pieces outward in a ring around the object. */
void debris_spawn_ring(unsigned char *moby, int count, float low, float high, float radius, float speed)
{
    DebrisVector position;
    DebrisVector velocity;
    float angle;
    position.q = 0;
    velocity.q = 0;
    if (count > 0) {
        int remaining = count;
        do {
            angle = math_random_float_range(-3.1415927f, 3.1415927f);
            position.f[0] = radius * math_fast_sin_or_cos_a(angle);
            position.f[1] = radius * math_fast_sin_or_cos_b(angle);
            position.f[2] = math_random_float_range(0.0f, 1.0f);
            vec_scale_to_length(&velocity, &position, math_random_float_range(speed * 0.75f, speed * 1.25f));
            position.f[2] = math_random_float_range(low, high);
            FastVecAdd(&position, moby + 0x10, &position);
            SpawnTintedEffects(moby, &position, 0.0f, 1, 1, &velocity, 0.0f, 1.0f, 0x80402000, 3.5f, 0);
        } while (--remaining);
    }
}
