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

/* Turns the object by a damped amount toward its wanted angle and returns how much turn is left. */
float func_L14_003D18C8(char *object, char *state, TI128 *input, char *transform) {
    /* Rotation construction writes three full rows after the local vector. */
    struct { Vector vector; TI128 matrix[3]; float damping; } scratch;
    TI128 *rotMatrix;
    char *objectBasis;
    float angleDelta;
    scratch.vector.q = *input;
    angleDelta = GetHeadingAngleOfVector(object, scratch.vector.f, transform);
    scratch.damping = 0.0f;
    ApproachTargetWithDirectionMode(&scratch.damping, angleDelta, (float *)(state + 0xB4), 0,
                 *(float *)(state + 0x14), *(float *)(state + 0x18), 3.141592653589793f);
    qzero(&scratch.vector);
    scratch.vector.f[2] = *(float *)(state + 0xB4);
    rotMatrix = scratch.matrix;
    euler_rotation_basis(rotMatrix, &scratch.vector);
    objectBasis = object + 0xC0;
    multiply_matrix3x3(objectBasis, objectBasis, rotMatrix);
    angleDelta = FloatAbs(angleDelta);
    return angleDelta - FloatAbs(*(float *)(state + 0xB4));
}
