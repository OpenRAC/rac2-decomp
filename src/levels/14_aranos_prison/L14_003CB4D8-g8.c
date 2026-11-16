#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern float g_swing_offset __attribute__((sda));
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Applies the swing angle to the object: turns its rotation, moves it around its pivot point and carries along anything riding on it. */
void swing_apply_to_object(char *object) {
    Vector rotation, delta, world, initial;
    char *matrix;
    char *vars = *(char **)(object + 0x68);
    char *angles = object + 0xF0;
    qcopy(&rotation, angles);
    *(float *)(object + 0xF4) = *(float *)(vars + 0x80);
    matrix = object + 0xC0;
    euler_rotation_basis(matrix, angles);
    object += 0x10;
    initial.q = 0;
    initial.f[2] = g_swing_offset;
    world.q = initial.q;
    matrix_mul_vec3(&world, &world, matrix);
    FastVecAdd(&world, &world, object);
    FastVecSub(&delta, vars + 0x70, &world);
    FastVecAdd(object, object, &delta);
    mat_combine_and_store(vars + 0x20, &delta, &rotation, angles);
}
