#include "include_asm.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
#define P(p,o) (*(char **)((char *)(p)+(o)))

extern int D_L04_001B9984 __attribute__((nosda));
/* Puts the lens flare's light source at a far-away point in the sky. */
void func_L04_00422D40(char *object) {
    char *state=P(object,0x68);
    Vector point;
    point.q=0;
    D_L04_001B9984=0;
    point.f[0]=80000.0f;
    point.f[1]=-70000.0f;
    point.f[2]=140000.0f;
    point.f[3]=1.0f;
    *(Quad *)(state+0x30)=point.q;
}
