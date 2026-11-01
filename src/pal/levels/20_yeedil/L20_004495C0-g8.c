#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_PAL_L20_004495C0(char *, char *, char *, float *);
extern void func_PAL_L20_004508B0(char *, int, TI128 *, TI128 *);

void func_PAL_L20_00449A98(char *arg0) {
    TI128 v0;
    TI128 v1;
    TI128 *pa = &v0;
    TI128 *pb = &v1;
    char *state;
    float f;

    f = 0.78539824f;
    state = *(char **)(arg0 + 0x68);
    func_PAL_L20_004495C0(arg0, (char *)pa, (char *)pb, &f);
    func_PAL_L20_004508B0(arg0, *(int *)(state + 0x240), pa, pb);
}
