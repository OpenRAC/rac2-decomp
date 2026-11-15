#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F3c9b60;
typedef struct { float value[4], phase[4], rate[4]; } SparkTimers;

extern const float D_L22_001AFF08 __attribute__((sda));
extern const float D_L22_001AFF10 __attribute__((sda));
extern s32 D_L22_001AFF50 __attribute__((sda));
extern const float D_L22_001AFF28 __attribute__((sda));
extern const float D_L22_001AFF48 __attribute__((sda));
extern s32 D_L22_001AFF40 __attribute__((sda));
extern const float D_L22_001AFF30 __attribute__((sda));
extern s32 D_L22_001AFF38 __attribute__((sda));
extern float D_L22_001AFF0C[];
extern float D_L22_001AFF14[];
extern float D_L22_001AFF2C[];
extern float D_L22_001AFF4C[];
extern s32 D_L22_001AFF44[];
extern float D_L22_001AFF34[];
extern s32 D_L22_001AFF3C[];

extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern void func_00283098(void *, void *, char *);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, char *);
extern s32 func_002A7820(s32, s32);
/* The EE preserves integer and FP argument order independently. */
extern void *func_002C3150(void *, void *, s32, float, u8, u8, s32);

/* Advance four spark timers, reroll expired ones, and randomly emit a particle. */
void func_L22_003C9B60(char *obj)
{
    V4_F3c9b60 aim, spark;
    SparkTimers *timers = (SparkTimers *)(*(char **)(obj + 0x68) + 0x10);
    int i = 0;
    s32 count = 3;
    float step, life;
    float angle, radius;
    s32 color, particleType;

    do {
        step = timers->phase[i] + timers->rate[i];
        timers->phase[i] = step;
        if (step >= 1.0f) {
            timers->phase[i] = 0.0f;
            timers->rate[i] = RandomFloatRange(D_L22_001AFF08, D_L22_001AFF0C[0]) * 0.016666668f;
            timers->value[i] = RandomFloatRange(D_L22_001AFF10, D_L22_001AFF14[0]);
        }
        count--;
        i++;
    } while (count >= 0);
    if (RandomIntBelow(D_L22_001AFF50) != 0) {
        qzero_nc(&spark);
        spark.f[2] = RandomFloatRange(D_L22_001AFF28, D_L22_001AFF2C[0]) * 0.016666668f;
        matrix_mul_vec3(&spark, &spark, obj + 0xC0);
        angle = RandomAngle();
        radius = RandomFloatRange(D_L22_001AFF48, D_L22_001AFF4C[0]);
        aim.f[0] = FastSinOrCosA(angle) * radius;
        aim.f[1] = FastSinOrCosB(angle) * radius;
        aim.f[2] = 0.0f;
        matrix_mul_vec3(&aim, &aim, obj + 0xC0);
        FastVecAdd(&aim, &aim, obj + 0x10);
        color = RandomIntRange(D_L22_001AFF40, D_L22_001AFF44[0]);
        life = RandomFloatRange(D_L22_001AFF30, D_L22_001AFF34[0]);
        if (RandomIntBelow(2) != 0)
            particleType = D_L22_001AFF38;
        else
            particleType = D_L22_001AFF3C[0];
        SpawnHeroRelativeParticle(&aim, &spark, particleType, life, color & 0xFF, RandomIntBelow(0xFF) & 0xFF, 0);
    }
}
