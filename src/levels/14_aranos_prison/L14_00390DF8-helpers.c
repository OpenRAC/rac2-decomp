#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern char D_0018A0E0[];
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);

void func_L14_00390DF8(char *output, char *first, char *second) {
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
