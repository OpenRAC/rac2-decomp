#include "include_asm.h"


typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int D_L08_001B9E04 __attribute__((nosda));

/* Same body as func_L04_00422D40, with this function's own callees. */
void func_L08_003F79E0(char *object) {
    char *state=*(char **)(object + 0x68);
    Vector point;
    point.q=0;
    D_L08_001B9E04=0;
    point.f[0]=7000000.0f;
    point.f[1]=5500000.0f;
    point.f[2]=9000000.0f;
    point.f[3]=1.0f;
    *(Quad *)(state+0x10)=point.q;
}
