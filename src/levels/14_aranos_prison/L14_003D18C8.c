/* Damps an angular delta and applies its complete three-row rotation matrix.
 * AAA00 has an ignored float result; its typed EE bank interleaving preserves
 * every argument. The separate basis pointer follows its actual lifetime.
 * Native ports must reconcile the shared callee declarations consistently.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern float func_002B04E0(char *, float *, char *);
extern float func_002AAA00(float *, float, float *, int, float, float, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern float func_00282C48(float);

float func_L14_003D18C8(char *object, char *state, TI128 *input, char *transform) {
    /* Rotation construction writes three full rows after the local vector. */
    struct { Vector vector; TI128 matrix[3]; float damping; } work;
    TI128 *rotation;
    char *basis;
    float value;
    work.vector.q = *input;
    value = func_002B04E0(object, work.vector.f, transform);
    work.damping = 0.0f;
    func_002AAA00(&work.damping, value, (float *)(state + 0xB4), 0,
                 *(float *)(state + 0x14), *(float *)(state + 0x18), 3.141592653589793f);
    qzero(&work.vector);
    work.vector.f[2] = *(float *)(state + 0xB4);
    rotation = work.matrix;
    euler_rotation_basis(rotation, &work.vector);
    basis = object + 0xC0;
    multiply_matrix3x3(basis, basis, rotation);
    value = func_00282C48(value);
    return value - func_00282C48(*(float *)(state + 0xB4));
}
