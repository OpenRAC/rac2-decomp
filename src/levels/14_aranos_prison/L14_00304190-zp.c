/* func_L14_00304190 and func_L14_00390EC0 need -frac2-zero-ti-por: each clears a stack
 * vector with a por and an sq.
 * In func_L14_00304190 the three sda globals are reached with -G0 macro instructions as in
 * retail: the count pointer is reloaded each iteration instead of keeping its address in a
 * saved register. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

typedef struct { int x, y; float z; } Record;
extern Record *D_L14_001B23D0 __attribute__((sda));
extern char *D_L14_001B2B20 __attribute__((sda));
extern char D_L14_001B2B50[] __attribute__((sda));
extern float D_L14_001B9730[];
extern Record D_L14_00284690[];
extern Record D_L14_00284708[];
extern float func_00282DB0(void *, void *);
extern void func_00283388(void *);
extern void func_002E3478(int);
extern void func_002E3940(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002830C0(void *, void *, void *);

/* The rotation rows are a 64-byte .lit table, read-only data. */
typedef struct { TI128 row[4]; } Matrix64 __attribute__((aligned(16)));
extern const Matrix64 D_L14_001AEE10;

void func_L14_00304190(void) {
    Vector axis;
    Record *dst = D_L14_00284708;
    float scale;
    int i;
    axis.q = 0;
    axis.f[0] = 1.0f;
    D_L14_001B23D0 = dst;
    scale = func_00282DB0(D_L14_001B9730, &axis);
    {
        Record *src = D_L14_00284690;
        int copyIndex;
        for (copyIndex = 0; copyIndex < 10; copyIndex++)
            dst[copyIndex].z = src[copyIndex].z * -scale;
    }
    for (i = 0; i < *(short *)(D_L14_001B2B20 + 6); i++) {
        if (i >= 10)
            func_00283388(D_L14_001B2B50);
        else
            func_002E3478(i);
        func_002E3940(i);
    }
}

void func_L14_00390EC0(Vector *output, char *transform, float yScale, float zScale, float angle) {
    Vector axis;
    Matrix64 rows;
    int i;
    axis.q = 0;
    axis.f[0] = 1.0f;
    axis.f[3] = 1.0f;
    rows.row[0] = D_L14_001AEE10.row[0];
    rows.row[1] = D_L14_001AEE10.row[1];
    rows.row[2] = D_L14_001AEE10.row[2];
    rows.row[3] = D_L14_001AEE10.row[3];
    for (i = 0; i < 4; i++) {
        qcopy(&output[i], &rows.row[i]);
        output[i].f[1] *= yScale;
        output[i].f[2] *= zScale;
        if (angle != 0.0f) {
            func_002ACEC0(&output[i], &output[i], &axis, angle);
            output[i].f[3] = 1.0f;
        }
        func_002830C0(&output[i], &output[i], transform);
    }
}
