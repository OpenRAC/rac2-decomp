#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern char D_0018A0E0[];
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);

/* Builds a set of three axis vectors (a rotation basis) from two input vectors and a fixed direction. */
void mat_build_basis_from_vecs(char *output, char *first, char *second) {
    Vector direction;
    qcopy(&direction, D_0018A0E0);
    FastVecScale(&direction, &direction, -1.0f);
    qcopy(output + 0x30, first);
    qcopy(output, second);
    {
        float one = 1.0f;
        vec_scale_to_length(output, output, one);
        FastVecCross(output + 0x10, output, &direction);
        vec_scale_to_length(output + 0x10, output + 0x10, one);
        FastVecCross(output + 0x20, output + 0x10, output);
    }
}
