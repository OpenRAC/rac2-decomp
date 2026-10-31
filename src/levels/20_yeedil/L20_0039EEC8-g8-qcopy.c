/* func_L20_0039EEC8 makes an object of class 0x1316 at `position` for `owner`, resets its
   rotation matrix and fills D_L20_00234880 and D_L20_00235500 from the matrix axes.
   - The object's position is copied with the qcopy helper; its volatile asm keeps the
     beqz delay slot filled from the return path (`daddu $v0,$s6,$zero`).
   - The matrix is reset through `object + 0xC0` and the three axis pointers are taken
     after the first clear loop: gcse then copies the call's argument (`addiu $a0` and
     `daddu $fp,$a0`).
   - The tables cleared by the three loops and the scalars D_L20_001AEDA0 and
     D_L20_001B3904 are incomplete `sda` arrays: the compiler emits `la`/`lw`/`sw` macros,
     which the assembler expands into absolute lui forms. The loop counters are separate.
   - The 6.0f scale D_L20_001AED40 is a sized `sda` float, read through $gp. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char *func_0029EFD0(int);
extern void func_00283360(void *);
extern void func_00282F20(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282DD8(void *, const void *, const void *);
extern unsigned int D_L20_001AEDA0[] __attribute__((sda));
extern float D_L20_001AED40 __attribute__((sda));
extern int D_L20_001B3870[] __attribute__((sda));
extern int D_L20_001B3890[] __attribute__((sda));
extern short D_L20_001B38B0[] __attribute__((sda));
extern float D_L20_001B3904[] __attribute__((sda));
extern Vector D_L20_00234880[8][25];
extern Vector D_L20_00235500[8];

unsigned char *func_L20_0039EEC8(unsigned char *owner, const Vector *position) {
    unsigned char *object = func_0029EFD0(0x1316);
    unsigned char *state;
    Vector *x, *y, *z;
    int i, j, k;
    if (object) {
        qcopy(object + 0x10, position);
        func_00283360(object + 0xC0);
        state = *(unsigned char **)(object + 0x68);
        object[0x30] = 255;
        *(unsigned char **)(object + 0xB8) = owner;
        *(int *)state = 5;
        *(unsigned int *)(state + 4) = D_L20_001AEDA0[0] & 0xFFFFFF;
        *(int *)(state + 0x10) = 0;
        *(int *)(state + 0x14) = 0;
        for (i = 7; i >= 0; --i) D_L20_001B3870[i] = 0;
        x = (Vector *)(object + 0xC0);
        z = (Vector *)(object + 0xE0);
        y = (Vector *)(object + 0xD0);
        func_00282F20(&D_L20_00234880[0][0], x, D_L20_001AED40);
        D_L20_00235500[0].q = z->q;
        func_00282F20(&D_L20_00234880[1][0], y, D_L20_001AED40);
        D_L20_00235500[1].q = x->q;
        func_00282F20(&D_L20_00234880[2][0], z, D_L20_001AED40);
        D_L20_00235500[2].q = y->q;
        func_00282CC0(&D_L20_00234880[3][0], x, z);
        func_00282F20(&D_L20_00234880[3][0], &D_L20_00234880[3][0], D_L20_001AED40);
        func_00282DD8(&D_L20_00235500[3], &D_L20_00234880[3][0], y);
        func_00282F20(&D_L20_00235500[3], &D_L20_00235500[3], 1.0f);
        func_00282CC0(&D_L20_00234880[4][0], x, y);
        func_00282F20(&D_L20_00234880[4][0], &D_L20_00234880[4][0], D_L20_001AED40);
        func_00282DD8(&D_L20_00235500[4], &D_L20_00234880[4][0], z);
        func_00282F20(&D_L20_00235500[4], &D_L20_00235500[4], 1.0f);
        func_00282CF0(&D_L20_00234880[5][0], y, z);
        func_00282F20(&D_L20_00234880[5][0], &D_L20_00234880[5][0], D_L20_001AED40);
        func_00282DD8(&D_L20_00235500[5], &D_L20_00234880[5][0], x);
        func_00282F20(&D_L20_00235500[5], &D_L20_00235500[5], 1.0f);
        func_00282CF0(&D_L20_00234880[6][0], x, z);
        func_00282F20(&D_L20_00234880[6][0], &D_L20_00234880[6][0], D_L20_001AED40);
        func_00282DD8(&D_L20_00235500[6], &D_L20_00234880[6][0], y);
        func_00282F20(&D_L20_00235500[6], &D_L20_00235500[6], 1.0f);
        func_00282CF0(&D_L20_00234880[7][0], x, y);
        func_00282F20(&D_L20_00234880[7][0], &D_L20_00234880[7][0], D_L20_001AED40);
        func_00282DD8(&D_L20_00235500[7], &D_L20_00234880[7][0], z);
        func_00282F20(&D_L20_00235500[7], &D_L20_00235500[7], 1.0f);
        for (j = 7; j >= 0; --j) D_L20_001B3890[j] = 0;
        for (k = 9; k >= 0; --k) D_L20_001B38B0[k] = 0;
        D_L20_001B3904[0] = 1.0f;
    }
    return object;
}
