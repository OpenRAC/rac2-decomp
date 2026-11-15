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
void yeedil_boss_compute_shot_launch(char *moby, char *out_position, char *out_velocity, float *aim_angle) {
    char *state = *(char **)(moby + 0x68);
    L20_V4 muzzle;
    L20_V4 throw_base;
    L20_V4 scratch;
    struct {
        TI128 angles;
        L20_V4 adjustment;
        TI128 basis[3];
    } transform;
    f32 random_value;

    muzzle.v = 0;
    muzzle.f.x = 5.0f;
    scratch.v = 0;
    muzzle.f.z = 5.5f;
    random_value = math_random_float_range(-1.0f, 1.0f);
    scratch.f.y = random_value;
    transform.adjustment.v = 0;
    throw_base.v = scratch.v;
    transform.adjustment.f.z = *(float *)(state + 0x298) * 0.5f;
    transform.angles = transform.adjustment.v;
    euler_rotation_basis(transform.basis, &transform.angles);
    multiply_matrix3x3(transform.basis, transform.basis, moby + 0xC0);
    FastVecAdd((char *)&muzzle, (char *)&muzzle, (char *)&throw_base);
    matrix_mul_vec3((char *)&muzzle, (char *)&muzzle, (char *)&transform.basis);
    FastVecAdd(out_position, (char *)&muzzle, moby + 0x10);
    random_value = math_random_float_range(5.0f, 10.0f);
    throw_base.f.x = random_value;
    random_value = math_random_float_range(4.0f, 6.0f);
    throw_base.f.z = random_value;
    matrix_mul_vec3((char *)&scratch, (char *)&throw_base, (char *)&transform.basis);
    FastVecScale(out_velocity, (char *)&scratch, 0.016666668f);
    *aim_angle = *aim_angle * throw_base.f.y;
}
