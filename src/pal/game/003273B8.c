#include "include_asm.h"

#include "common.h"
typedef int TI128_00325C50 __attribute__((mode(TI)));
typedef union { TI128_00325C50 q; float f[4]; } Vec_00325C50;
extern void func_002833F0(void *, void *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_00283738(void *, void *, void *);
extern int func_002A77E0(int);
extern void func_PAL_00327028(void *, int, void *);

void func_PAL_003273B8(float angle, char *parent, char **children, int randomize, void *effect)
{
    char rotation[0x30] __attribute__((aligned(16)));
    Vec_00325C50 euler;
    Vec_00325C50 position;
    int i;

    euler.q = 0;
    euler.f[2] = angle;
    func_002833F0(rotation, &euler);
    for (i = 1; i >= 0; i--) {
        func_002AF1D0(parent, *children, (unsigned char)(*children)[0xBC], 0);
        func_00283738(*children + 0xC0, *children + 0xC0, rotation);
        if (randomize != 0 && func_002A77E0(6) == 0) {
            qcopy(&position, *children + 0x10);
            func_PAL_00327028(&position, 1, effect);
        }
        children++;
    }
}

