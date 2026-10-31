/* func_L14_00304190 needs -frac2-zero-ti-por: it clears its stack vector with a por and an sq.
 * The three sda globals are reached with -G0 macro instructions as in retail: the count
 * pointer is reloaded each iteration instead of keeping its address in a saved register. */
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
