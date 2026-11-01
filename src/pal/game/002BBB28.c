#include "include_asm.h"

#include "common.h"
extern float Fe617c30b_FUN_00283CE0(int a);
extern void Fe617c30b_FUN_00282D30(char *p, char *q, float f);
extern void Fe617c30b_FUN_00282CC0(char *p, char *q, char *r);
extern int Fe617c30b_FUN_002A9568(int a, int b, float f);
extern int Fe617c30b_FUN_00282978(char *p);
extern void Fe617c30b_FUN_002B9180(char *p);

/* func_002BAE50 is matched in its own unit, src/game/002BAE50.c (default flags). */

void func_PAL_002BBB28(char *a0)
{
    char *s0 = a0 + 32;
    int x;
    int u;
    int t;
    float f;

    x = *(int *)(s0 + 28);
    t = *(short *)(a0 + 10);
    u = *(short *)(s0 + 24) * (x - t) / x + *(short *)(s0 + 26);

    f = Fe617c30b_FUN_00283CE0(u) * 1000.0f;
    *(float *)(a0 + 12) = f;
    Fe617c30b_FUN_00282D30(s0, s0, 0.976f);
    Fe617c30b_FUN_00282CC0(a0 + 16, a0 + 16, s0);
    *(unsigned char *)(a0 + 8) = *(unsigned char *)(a0 + 8) + 1;
    f = Fe617c30b_FUN_00283CE0(*(int *)(s0 + 28));
    *(int *)(a0 + 4) = Fe617c30b_FUN_002A9568(*(int *)(s0 + 20), *(int *)(s0 + 16),
                               (float)*(short *)(a0 + 10) / f);
    if (Fe617c30b_FUN_00282978(a0 + 10) != 0)
        Fe617c30b_FUN_002B9180(a0);
}


extern void func_002B9180(char *);
extern s32 func_00282948(void *);
extern void func_00300190(char *, char *);

void func_PAL_002BBC10(u8 *a0)
{
    u8 *s0 = a0;
    u8 *s1 = a0 + 0x20;

    if (func_00282948((char *)s1) != 0) {
        func_002B9180((char *)s0);
        return;
    }
    {
        u8 *p = s0 + 0x10;

        func_00300190((char *)p, (char *)p);
    }
    *(f32 *)(s0 + 0xC) = *(f32 *)(s0 + 0xC) + *(f32 *)(s1 + 4);
    if (*(s32 *)(s1) < 5) {
        *(unsigned int *)(s0 + 4) = (*(unsigned int *)(s0 + 4) & 0xFFFFFF)
            | ((unsigned int)(*(s32 *)(s1) * 127 / 5) << 24);
    }
}


INCLUDE_ASM("asm/pal/game", func_PAL_002BBCC0);

extern int Fb77d67f1_FUN_00282948(char *p);
extern void Fb77d67f1_FUN_002B9180(char *p);

void func_PAL_002BC400(char *a0)
{
    char *p = a0 + 32;

    if (Fb77d67f1_FUN_00282948(p) != 0) {
        Fb77d67f1_FUN_002B9180(a0);
        return;
    }
    *(float *)(a0 + 12) = *(float *)(a0 + 12) + *(float *)(p + 4);
    if (*(int *)(a0 + 32) < 5)
        *(int *)(a0 + 4) = (*(int *)(a0 + 4) & 0xFFFFFF)
                         | ((*(int *)(a0 + 32) * 127 / 5) << 24);
}

