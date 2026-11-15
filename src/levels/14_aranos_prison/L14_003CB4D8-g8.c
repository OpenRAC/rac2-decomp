#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern float D_L14_001AFF0C __attribute__((sda));
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Applies the swing angle to the object: turns its rotation, moves it around its pivot point and carries along anything riding on it. */
void func_L14_003CB4D8(char *object) {
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
    initial.f[2] = D_L14_001AFF0C;
    world.q = initial.q;
    matrix_mul_vec3(&world, &world, matrix);
    FastVecAdd(&world, &world, object);
    FastVecSub(&delta, vars + 0x70, &world);
    FastVecAdd(object, object, &delta);
    CombineTransformsAndStore(vars + 0x20, &delta, &rotation, angles);
}
