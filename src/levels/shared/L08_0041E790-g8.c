#include "common.h"


extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);



extern int GetCollHitMaterial(void);
extern int D_L08_001B1ADC SDATA(D_L08_001B1ADC);
extern int D_L08_001B1AE0 SDATA(D_L08_001B1AE0);
extern int D_L08_001B1B74 SDATA(D_L08_001B1B74);
extern int D_L08_001B1B78 SDATA(D_L08_001B1B78);
extern float D_L08_001B1B14 SDATA(D_L08_001B1B14);
extern float D_L08_001B1B18 SDATA(D_L08_001B1B18);
extern float D_L08_001B1B68 SDATA(D_L08_001B1B68);
extern float D_L08_001B1B6C SDATA(D_L08_001B1B6C);
extern float D_L08_001B1AE4 SDATA(D_L08_001B1AE4);
extern float D_L08_001B1AE8 SDATA(D_L08_001B1AE8);
extern float D_L08_001B1AEC SDATA(D_L08_001B1AEC);
extern float D_L08_001B1AF0 SDATA(D_L08_001B1AF0);
extern float D_L08_001B1AF4 SDATA(D_L08_001B1AF4);
extern float D_L08_001B1AF8 SDATA(D_L08_001B1AF8);

/* Spawns a burst of small particles that fly outward from a point in a ring, rising and
   shrinking as they go. */
void part_spawn_ring(char *moby, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4], boost[4];
    char *vars = *(char **)(moby + 0x68);
    int colorStart = D_L08_001B1ADC;
    int colorEnd = D_L08_001B1AE0;
    if (!GetCollHitMaterial()) {
        colorStart = D_L08_001B1B74;
        colorEnd = D_L08_001B1B78;
    }
    { int i;
    for (i = 0; i < count; i++) {
        int red,green,blue;
        char *particle;
        float cosPart,sinPart,speedRange;
        cosPart = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f,3.1415927410125732f));
        offset[0] = cosPart * math_random_float_range(minRadius,maxRadius);
        sinPart = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f,3.1415927410125732f));
        sinPart *= math_random_float_range(minRadius,maxRadius);
        offset[1] = sinPart;
        offset[2] = 0;
        matrix_mul_vec3(offset,offset,moby+0xC0);
        speedRange = (speed * ((maxRadius-FastVecLength(offset))*0.01666666753590107f))/maxRadius;
        vec_scale_to_length(velocity,offset,math_random_float_range(speedRange / D_L08_001B1B14,speedRange));
        qcopy(boost,vars);
        boost[2] *= D_L08_001B1B68;
        FastVecAdd(velocity,velocity,boost);
        {
            velocity[2] += math_random_float_range(rise / D_L08_001B1B18,rise)*0.01666666753590107f;
        }
        qzero_nc(accel);
        FastVecAdd(offset,offset,position);
        offset[2] += D_L08_001B1B6C;
        velocity[3] = size;
        accel[3] = endSize;
        red = FloatToInt(math_random_float_range(D_L08_001B1AE4,D_L08_001B1AE8));
        green = FloatToInt(math_random_float_range(D_L08_001B1AEC,D_L08_001B1AF0));
        blue = FloatToInt(math_random_float_range(D_L08_001B1AF4,D_L08_001B1AF8));
        particle = part_spawn_trail(offset,velocity,accel,colorStart,colorEnd,red,green,blue,-1);
        if (particle && (func_001163B0() & 1)) particle[3] = 0x48;
    }
    }
}
