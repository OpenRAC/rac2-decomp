#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char *CreateMoby(int);
extern void set_identity_rotation_rows(void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern void FastVecCross(void *, const void *, const void *);
extern unsigned int D_L20_001AEDA0[] __attribute__((sda));
extern float D_L20_001AED40 __attribute__((sda));
extern int D_L20_001B3870[] __attribute__((sda));
extern int D_L20_001B3890[] __attribute__((sda));
extern short D_L20_001B38B0[] __attribute__((sda));
extern float D_L20_001B3904[] __attribute__((sda));
extern Vector D_L20_00234880[8][25];
extern Vector D_L20_00235500[8];

unsigned char *func_PAL_L20_003A1E38(unsigned char *owner, const Vector *position) {
    unsigned char *object = CreateMoby(0x1316);
    unsigned char *state;
    Vector *x, *y, *z;
    int i, j, k;
    if (object) {
        qcopy(object + 0x10, position);
        set_identity_rotation_rows(object + 0xC0);
        state = *(unsigned char **)(object + 0x68);
        object[0x30] = 255;
        *(unsigned char **)(object + 0xB8) = owner;
        *(int *)state = 4;
        *(unsigned int *)(state + 4) = D_L20_001AEDA0[0] & 0xFFFFFF;
        *(int *)(state + 0x10) = 0;
        *(int *)(state + 0x14) = 0;
        for (i = 7; i >= 0; --i) D_L20_001B3870[i] = 0;
        x = (Vector *)(object + 0xC0);
        z = (Vector *)(object + 0xE0);
        y = (Vector *)(object + 0xD0);
        vec_scale_to_length(&D_L20_00234880[0][0], x, D_L20_001AED40);
        D_L20_00235500[0].q = z->q;
        vec_scale_to_length(&D_L20_00234880[1][0], y, D_L20_001AED40);
        D_L20_00235500[1].q = x->q;
        vec_scale_to_length(&D_L20_00234880[2][0], z, D_L20_001AED40);
        D_L20_00235500[2].q = y->q;
        FastVecAdd(&D_L20_00234880[3][0], x, z);
        vec_scale_to_length(&D_L20_00234880[3][0], &D_L20_00234880[3][0], D_L20_001AED40);
        FastVecCross(&D_L20_00235500[3], &D_L20_00234880[3][0], y);
        vec_scale_to_length(&D_L20_00235500[3], &D_L20_00235500[3], 1.0f);
        FastVecAdd(&D_L20_00234880[4][0], x, y);
        vec_scale_to_length(&D_L20_00234880[4][0], &D_L20_00234880[4][0], D_L20_001AED40);
        FastVecCross(&D_L20_00235500[4], &D_L20_00234880[4][0], z);
        vec_scale_to_length(&D_L20_00235500[4], &D_L20_00235500[4], 1.0f);
        FastVecSub(&D_L20_00234880[5][0], y, z);
        vec_scale_to_length(&D_L20_00234880[5][0], &D_L20_00234880[5][0], D_L20_001AED40);
        FastVecCross(&D_L20_00235500[5], &D_L20_00234880[5][0], x);
        vec_scale_to_length(&D_L20_00235500[5], &D_L20_00235500[5], 1.0f);
        FastVecSub(&D_L20_00234880[6][0], x, z);
        vec_scale_to_length(&D_L20_00234880[6][0], &D_L20_00234880[6][0], D_L20_001AED40);
        FastVecCross(&D_L20_00235500[6], &D_L20_00234880[6][0], y);
        vec_scale_to_length(&D_L20_00235500[6], &D_L20_00235500[6], 1.0f);
        FastVecSub(&D_L20_00234880[7][0], x, y);
        vec_scale_to_length(&D_L20_00234880[7][0], &D_L20_00234880[7][0], D_L20_001AED40);
        FastVecCross(&D_L20_00235500[7], &D_L20_00234880[7][0], z);
        vec_scale_to_length(&D_L20_00235500[7], &D_L20_00235500[7], 1.0f);
        for (j = 7; j >= 0; --j) D_L20_001B3890[j] = 0;
        for (k = 9; k >= 0; --k) D_L20_001B38B0[k] = 0;
        D_L20_001B3904[0] = 1.0f;
    }
    return object;
}
