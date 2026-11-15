#include "common.h"
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

static __inline__ void vzero(float *v) {
    qzero(v);
}

/* The same dust burst as func_L08_00422190, except that a moby in state 5 hands the particles
   part of its own motion: 0.8 of the vector at vars + 0xD0 joins their velocity and 0.4 of
   that becomes their acceleration. */
/* Sprays a ring of dust puffs around a point, carrying some of the creature's own motion. */
void func_L08_00424FF8(char *moby, void *position, int count,
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
            x = FastSinOrCosA(RandomFloatRange(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * RandomFloatRange(minRadius, maxRadius);
            y = FastSinOrCosB(RandomFloatRange(-3.1415927410125732f, 3.1415927410125732f));
            y *= RandomFloatRange(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            matrix_mul_vec3(offset, offset, moby + 0xC0);
            {
                float range = speed * ((maxRadius - FastVecLength(offset)) * 0.01666666753590107f) / maxRadius;
                vec_scale_to_length(velocity, offset, RandomFloatRange(range * 0.25f, range));
            }
            velocity[2] += RandomFloatRange(rise * 0.25f, rise) * 0.01666666753590107f;
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
            fadeIn = FloatToInt(RandomFloatRange(15.0f, 25.0f));
            hold = FloatToInt(RandomFloatRange(20.0f, 40.0f));
            fadeOut = FloatToInt(RandomFloatRange(50.0f, 70.0f));
            particle = SpawnTrailParticle_002BAA28(offset, velocity, accel, 0x70204050, 0x7F7F7F, fadeIn, hold, fadeOut, -1);
            if (particle && (Rand() & 1))
                particle[3] = 0x48;
        }
    }
}
