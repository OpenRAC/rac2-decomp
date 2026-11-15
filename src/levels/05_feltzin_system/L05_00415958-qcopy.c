#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F415958;

extern s32 D_L05_001B0EE8 __attribute__((sda));
extern s32 D_L05_001B0EF8 __attribute__((sda));
extern s32 D_L05_001B0F08 __attribute__((sda));

extern void func_00283098(void *, void *, char *);
extern void func_00282CC0(void *, void *, char *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void func_L00_0033C0D0(char *, void *, void *, void *, s32);

/* Spawns three trail marks at the object's tail: copies the aimed vector three times, shrinks each and releases it with a random sideways drift. */
void func_L05_00415958(char *obj)
{
    V4_F415958 dir, drift, tail, mark1, mark2, mark3;
    float k;

    dir.q = 0;
    dir.f[0] = -0.31f;
    dir.f[3] = 1.0f;
    drift.q = 0;
    matrix_mul_vec3(&tail, &dir, obj + 0xC0);
    FastVecAdd(&tail, &tail, obj + 0x10);
    k = 0.4f;
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    AddRandomOffsetToVector(&tail, 0.1f);
    AddRandomOffsetToVector(&mark1, 0.1f);
    AddRandomOffsetToVector(&mark2, 0.1f);
    AddRandomOffsetToVector(&mark3, 0.1f);
    drift.f[0] = -(RandomFloatRange(30.0f, 40.0f) * 0.016666668f) * k;
    SpawnObjectRelativeParticle(obj, &mark1, &drift, &D_L05_001B0EE8, 1);
    drift.f[0] = -(RandomFloatRange(30.0f, 40.0f) * 0.016666668f) * k;
    SpawnObjectRelativeParticle(obj, &mark2, &drift, &D_L05_001B0EF8, 1);
    drift.f[0] = -(RandomFloatRange(30.0f, 40.0f) * 0.016666668f) * k;
    SpawnObjectRelativeParticle(obj, &mark3, &drift, &D_L05_001B0F08, 1);
}
