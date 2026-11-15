#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef union { TI128 quad; float values[4]; } ResidentVector;
extern unsigned char D_00189E20[];
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

void func_L03_002ADC00(void)
{
    ResidentVector offset;
    TI128 matrix[4];
    unsigned char *resident = D_00189E20;
    if (*(short *)(resident + 0x6BC) != 0 && *(int *)(resident + 0x660) == 0) {
        *(float *)(*(unsigned char **)(resident + 0x2290) + 0xF4) = *(float *)(resident + 0x6B0);
        offset.quad = 0;
        offset.values[2] = 2.0f;
        euler_to_matrix(matrix, *(unsigned char **)(resident + 0x2290) + 0xF0);
        transform_vector(&offset, &offset, matrix);
        FastVecAdd(*(unsigned char **)(resident + 0x2290) + 0x10, resident + 0x80, &offset);
    }
}
