#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
#define P(p,o) (*(char **)((char *)(p)+(o)))

extern int g_lens_flare_light_position_flag __attribute__((nosda));
/* Puts the lens flare's light source at a far-away point in the sky. */
void lens_flare_reset_light_position(char *object) {
    char *state=P(object,0x68);
    Vector point;
    point.q=0;
    g_lens_flare_light_position_flag=0;
    point.f[0]=80000.0f;
    point.f[1]=-70000.0f;
    point.f[2]=140000.0f;
    point.f[3]=1.0f;
    *(Quad *)(state+0x30)=point.q;
}
