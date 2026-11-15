#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F417550;

extern s32 D_L05_001B0F58 __attribute__((sda));
extern s32 D_L05_001B0F68 __attribute__((sda));
extern s32 D_L05_001B0F78 __attribute__((sda));

extern void func_00283098(void *, void *, char *);
extern void func_00282CC0(void *, void *, char *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void func_L00_0033C0D0(char *, void *, void *, void *, s32);

/* Spawns three trail marks at the object's tail. */
void func_L05_00417550(char *object)
{
    V4_F417550 dir, drift, tail, mark1, mark2, mark3;
    float driftScale;

    dir.q = 0;
    dir.f[0] = -0.503f;
    dir.f[3] = 1.0f;
    drift.q = 0;
    matrix_mul_vec3(&tail, &dir, object + 0xC0);
    FastVecAdd(&tail, &tail, object + 0x10);
    driftScale = 0.4f;
    tail.w[3] = 0;
    qcopy(&mark1, &tail);
    qcopy(&mark2, &tail);
    qcopy(&mark3, &tail);
    AddRandomOffsetToVector(&tail, 0.1f);
    AddRandomOffsetToVector(&mark1, 0.1f);
    AddRandomOffsetToVector(&mark2, 0.1f);
    AddRandomOffsetToVector(&mark3, 0.1f);
    drift.f[0] = -(RandomFloatRange(30.0f, 40.0f) * 0.016666668f) * driftScale;
    SpawnObjectRelativeParticle(object, &mark1, &drift, &D_L05_001B0F58, 1);
    drift.f[0] = -(RandomFloatRange(30.0f, 40.0f) * 0.016666668f) * driftScale;
    SpawnObjectRelativeParticle(object, &mark2, &drift, &D_L05_001B0F68, 1);
    drift.f[0] = -(RandomFloatRange(30.0f, 40.0f) * 0.016666668f) * driftScale;
    SpawnObjectRelativeParticle(object, &mark3, &drift, &D_L05_001B0F78, 1);
}
