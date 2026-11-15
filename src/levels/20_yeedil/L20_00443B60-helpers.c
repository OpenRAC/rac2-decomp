#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef union {
    TI128 v;
    struct { f32 x, y, z, w; } f;
} L20_V4;

extern float func_002A7878(float, float);
extern void func_002833F0(TI128 *, TI128 *);
extern void func_00283738(TI128 *, TI128 *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00283098(char *, char *, char *);
extern void func_00282D30(char *, char *, float);

/* Works out where the enemy fires from and how fast and in which direction the shot flies, with a bit of randomness. */
void func_L20_00443B60(char *moby, char *outPosition, char *outVelocity, float *aimAngle) {
    char *state = *(char **)(moby + 0x68);
    L20_V4 muzzle;
    L20_V4 throwBase;
    L20_V4 scratch;
    struct {
        TI128 angles;
        L20_V4 adjustment;
        TI128 basis[3];
    } transform;
    f32 randomValue;

    muzzle.v = 0;
    muzzle.f.x = 5.0f;
    scratch.v = 0;
    muzzle.f.z = 5.5f;
    randomValue = RandomFloatRange(-1.0f, 1.0f);
    scratch.f.y = randomValue;
    transform.adjustment.v = 0;
    throwBase.v = scratch.v;
    transform.adjustment.f.z = *(float *)(state + 0x298) * 0.5f;
    transform.angles = transform.adjustment.v;
    euler_rotation_basis(transform.basis, &transform.angles);
    multiply_matrix3x3(transform.basis, transform.basis, moby + 0xC0);
    FastVecAdd((char *)&muzzle, (char *)&muzzle, (char *)&throwBase);
    matrix_mul_vec3((char *)&muzzle, (char *)&muzzle, (char *)&transform.basis);
    FastVecAdd(outPosition, (char *)&muzzle, moby + 0x10);
    randomValue = RandomFloatRange(5.0f, 10.0f);
    throwBase.f.x = randomValue;
    randomValue = RandomFloatRange(4.0f, 6.0f);
    throwBase.f.z = randomValue;
    matrix_mul_vec3((char *)&scratch, (char *)&throwBase, (char *)&transform.basis);
    FastVecScale(outVelocity, (char *)&scratch, 0.016666668f);
    *aimAngle = *aimAngle * throwBase.f.y;
}
