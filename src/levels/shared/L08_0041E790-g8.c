#include "common.h"


extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);



extern int func_00278E78(void);
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
void func_L08_0041E790(char *moby, void *position, int count,
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
        cosPart = FastSinOrCosA(RandomFloatRange(-3.1415927410125732f,3.1415927410125732f));
        offset[0] = cosPart * RandomFloatRange(minRadius,maxRadius);
        sinPart = FastSinOrCosB(RandomFloatRange(-3.1415927410125732f,3.1415927410125732f));
        sinPart *= RandomFloatRange(minRadius,maxRadius);
        offset[1] = sinPart;
        offset[2] = 0;
        matrix_mul_vec3(offset,offset,moby+0xC0);
        speedRange = (speed * ((maxRadius-FastVecLength(offset))*0.01666666753590107f))/maxRadius;
        vec_scale_to_length(velocity,offset,RandomFloatRange(speedRange / D_L08_001B1B14,speedRange));
        qcopy(boost,vars);
        boost[2] *= D_L08_001B1B68;
        FastVecAdd(velocity,velocity,boost);
        {
            velocity[2] += RandomFloatRange(rise / D_L08_001B1B18,rise)*0.01666666753590107f;
        }
        qzero_nc(accel);
        FastVecAdd(offset,offset,position);
        offset[2] += D_L08_001B1B6C;
        velocity[3] = size;
        accel[3] = endSize;
        red = FloatToInt(RandomFloatRange(D_L08_001B1AE4,D_L08_001B1AE8));
        green = FloatToInt(RandomFloatRange(D_L08_001B1AEC,D_L08_001B1AF0));
        blue = FloatToInt(RandomFloatRange(D_L08_001B1AF4,D_L08_001B1AF8));
        particle = SpawnTrailParticle_002BAA28(offset,velocity,accel,colorStart,colorEnd,red,green,blue,-1);
        if (particle && (Rand() & 1)) particle[3] = 0x48;
    }
    }
}
