#include "include_asm.h"
#include "names.h"


typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int g_far_target_flag __attribute__((nosda));

/* Same body as func_L04_00422D40, with this function's own callees. */
/* Puts the object's target point at a fixed spot far away and clears a level flag. */
void moby_set_far_target_point(char *object) {
    char *state=*(char **)(object + 0x68);
    Vector point;
    point.q=0;
    g_far_target_flag=0;
    point.f[0]=7000000.0f;
    point.f[1]=5500000.0f;
    point.f[2]=9000000.0f;
    point.f[3]=1.0f;
    *(Quad *)(state+0x10)=point.q;
}
