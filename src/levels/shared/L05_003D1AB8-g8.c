#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void func_L00_0033C0D0(void *, void *, void *, void *, int);
extern float D_L05_001AFC60[] SDATA(D_L05_001AFC60);
extern float D_L05_001AFC70[] SDATA(D_L05_001AFC70);
extern float D_L05_001AFC80[] SDATA(D_L05_001AFC80);

/* For each of two points in the object's frame, either side of it in Y, makes three copies of the
   point and passes each to func_L00_0033C0D0 with a random speed. */
/* Leaves exhaust trail marks at two points on either side of the object. */
void func_L05_003D1AB8(char *obj)
{
    float a[4] __attribute__((aligned(16)));
    float speed[4] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    float p1[4] __attribute__((aligned(16)));
    float p2[4] __attribute__((aligned(16)));
    float p3[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float factor;
    float y;

    *(TI128 *)a = 0;
    a[0] = -0.21f;
    a[1] = 0.061f;
    *(TI128 *)speed = 0;
    a[2] = 0.045f;
    a[3] = 1.0f;
    matrix_mul_vec3(p, a, obj + 0xC0);
    factor = 0.4f;
    FastVecAdd(p, p, obj + 0x10);
    p[3] = 0;
    qcopy(p1, p);
    qcopy(p2, p);
    qcopy(p3, p);
    AddRandomOffsetToVector(p, 0.1f);
    AddRandomOffsetToVector(p1, 0.1f);
    AddRandomOffsetToVector(p2, 0.1f);
    AddRandomOffsetToVector(p3, 0.1f);
    speed[0] = -(RandomFloatRange(30.0f, 40.0f) * (1.0f / 60.0f)) * factor;
    SpawnObjectRelativeParticle(obj, p1, speed, D_L05_001AFC60, 1);
    speed[0] = -(RandomFloatRange(30.0f, 40.0f) * (1.0f / 60.0f)) * factor;
    SpawnObjectRelativeParticle(obj, p2, speed, D_L05_001AFC70, 1);
    speed[0] = -(RandomFloatRange(30.0f, 40.0f) * (1.0f / 60.0f)) * factor;
    SpawnObjectRelativeParticle(obj, p3, speed, D_L05_001AFC80, 1);
    y = -0.061f;
    *(TI128 *)b = 0;
    b[0] = -0.21f;
    b[1] = y;
    b[2] = 0.045f;
    b[3] = 1.0f;
    matrix_mul_vec3(p, b, obj + 0xC0);
    FastVecAdd(p, p, obj + 0x10);
    p[3] = 0;
    qcopy(p1, p);
    qcopy(p2, p);
    qcopy(p3, p);
    AddRandomOffsetToVector(p, 0.1f);
    AddRandomOffsetToVector(p1, 0.1f);
    AddRandomOffsetToVector(p2, 0.1f);
    AddRandomOffsetToVector(p3, 0.1f);
    speed[0] = -(RandomFloatRange(30.0f, 40.0f) * (1.0f / 60.0f)) * factor;
    SpawnObjectRelativeParticle(obj, p1, speed, D_L05_001AFC60, 1);
    speed[0] = -(RandomFloatRange(30.0f, 40.0f) * (1.0f / 60.0f)) * factor;
    SpawnObjectRelativeParticle(obj, p2, speed, D_L05_001AFC70, 1);
    speed[0] = -(RandomFloatRange(30.0f, 40.0f) * (1.0f / 60.0f)) * factor;
    SpawnObjectRelativeParticle(obj, p3, speed, D_L05_001AFC80, 1);
}
