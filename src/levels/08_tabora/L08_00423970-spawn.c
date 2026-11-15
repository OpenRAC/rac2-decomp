#include "common.h"
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastVecLength(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

static __inline__ void vzero(float *v) {
    qzero(v);
}

/* The same dust burst as func_L08_00422190, except that a moby in state 5 hands the particles
   part of its own motion: 0.8 of the vector at vars + 0xD0 joins their velocity and 0.4 of
   that becomes their acceleration. */
/* Sprays a ring of dust puffs around a point, carrying some of the creature's own motion. */
void part_spawn_dust_burst_motion(char *moby, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4], motion[4];
    int fadeIn, hold, fadeOut;
    char *particle;
    char *vars = *(char **)(moby + 0x68);

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * math_random_float_range(minRadius, maxRadius);
            y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
            y *= math_random_float_range(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, moby + 0xC0);
            {
                float range = speed * ((maxRadius - FastVecLength(offset)) * 0.01666666753590107f) / maxRadius;
                vec_scale_to_length(velocity, offset, math_random_float_range(range * 0.25f, range));
            }
            velocity[2] += math_random_float_range(rise * 0.25f, rise) * 0.01666666753590107f;
            if (*(u8 *)(moby + 0x20) == 5) {
                qcopy(motion, vars + 0xD0);
                motion[2] = 0;
                FastVecScale(motion, vars + 0xD0, 0.8f);
                FastVecAdd(velocity, velocity, motion);
                FastVecScale(accel, motion, 0.4f);
            } else {
                vzero(accel);
            }
            FastVecAdd(offset, offset, position);
            offset[2] += -0.75f;
            velocity[3] = size;
            accel[3] = endSize;
            fadeIn = FloatToInt(math_random_float_range(15.0f, 25.0f));
            hold = FloatToInt(math_random_float_range(20.0f, 40.0f));
            fadeOut = FloatToInt(math_random_float_range(50.0f, 70.0f));
            particle = part_spawn_trail(offset, velocity, accel, 0x70204050, 0x7F7F7F, fadeIn, hold, fadeOut, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}
