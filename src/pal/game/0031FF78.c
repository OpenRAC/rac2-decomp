#include "include_asm.h"

extern void F5a19df7a_FUN_002FC560(unsigned int a, unsigned long b);
extern void F5a19df7a_FUN_0031E2A0(char *p);
extern void F5a19df7a_FUN_0031E560(char *p);
extern int F5a19df7a_FUN_002A7820(int a, int b);
extern float F5a19df7a_FUN_002A7940(void);
extern void F5a19df7a_FUN_0031EB00(char *a, int b, float e, char *c, float f, int d, int g);

void func_PAL_0031FF78(char *p)
{
    char *q;
    char *o;
    char *r;
    float v;
    float w;

    q = p + 16;
    o = *(char **)(p + 104);
    F5a19df7a_FUN_002FC560(0x47, 0x53001UL);
    F5a19df7a_FUN_0031E2A0(p);
    F5a19df7a_FUN_0031E560(p);

    v = *(float *)(o + 24);
    v = v * 0.5f;
    r = F5a19df7a_FUN_002A7820(80, 96);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x103080, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 3.00000011920928955078125e-01f;
    r = F5a19df7a_FUN_002A7820(80, 96);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0xFFFFFF, v, r, w, 49, 2);

    v = *(float *)(o + 24);
    v = v * 6.99999988079071044921875e-01f;
    r = F5a19df7a_FUN_002A7820(8, 22);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x803010, v, r, w, 11, 2);

    v = *(float *)(o + 24);
    v = v * 4.49999988079071044921875e-01f;
    r = F5a19df7a_FUN_002A7820(32, 64);
    w = F5a19df7a_FUN_002A7940();
    F5a19df7a_FUN_0031EB00(q, 0x803010, v, r, w, 11, 2);

    F5a19df7a_FUN_002FC560(0x47, 0x5360bUL);
}

