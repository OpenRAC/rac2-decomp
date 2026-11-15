#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef union {
    TI128 v;
    struct { f32 x, y, z, w; } f;
} L20_V4;

extern float math_random_float_range(float, float);
extern void euler_rotation_basis(TI128 *, TI128 *);
extern void multiply_matrix3x3(TI128 *, TI128 *, char *);
extern void FastVecAdd(char *, char *, char *);
extern void matrix_mul_vec3(char *, char *, char *);
extern void FastVecScale(char *, char *, float);

/* Works out where the enemy fires from and how fast and in which direction the shot flies, with a bit of randomness. */
void yeedil_boss_compute_shot_launch(char *moby, char *outPosition, char *outVelocity, float *aimAngle) {
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
    randomValue = math_random_float_range(-1.0f, 1.0f);
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
    randomValue = math_random_float_range(5.0f, 10.0f);
    throwBase.f.x = randomValue;
    randomValue = math_random_float_range(4.0f, 6.0f);
    throwBase.f.z = randomValue;
    matrix_mul_vec3((char *)&scratch, (char *)&throwBase, (char *)&transform.basis);
    FastVecScale(outVelocity, (char *)&scratch, 0.016666668f);
    *aimAngle = *aimAngle * throwBase.f.y;
}
