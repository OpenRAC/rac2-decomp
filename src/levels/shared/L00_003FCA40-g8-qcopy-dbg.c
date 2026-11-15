#include "common.h"

typedef int Quad_3fca40 __attribute__((mode(TI)));

/* The allocator, the two vector helpers and the int-to-float helper the retail calls;
   each sits at another address in the other levels, so the level's own copies are named
   here with the address they have in level 00. */
extern void *func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);

extern int D_L00_001B0BB4 __attribute__((sda));

/* The bodies the retail calls reach, at 0x3FD178, 0x2E6EF8 and 0x3FCDB0 in level 00. */
extern void ref_L00_003FCA40_00(void *);
extern void ref_L00_003FCA40_01(void *, void *);
extern void ref_L00_003FCA40_02(void);

/* The allocator hands out a 0xD9C-byte object; the object is set up (flag halfword, three
   header bytes), the second argument's vector is copied into it, the object is normalised
   twice and added to the first argument, and the level's own copy of SpawnParticleTrailBurst runs
   on it. */
char *func_L00_003FCA40(char *a0, char *a1, Quad_3fca40 *a2, int a3)
{
    Quad_3fca40 local;
    char *obj;
    char *obj10;
    int *p;
    char *q;
    int g;
    float f;

    obj = (char *)CreateMoby(0xD9C);
    if (obj != 0) {
        *(unsigned char *)(obj + 0x30) = 0xFF;
        p = *(int **)(obj + 0x68);
        *(unsigned short *)(obj + 0x32) = 0xFF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned short *)(obj + 0x34) |= 0x41;
        *(unsigned char *)(obj + 0x20) = 0;
        q = (char *)p + 0x20;
        obj10 = obj + 0x10;
        vec_scale_to_length(q, a1, 0.33333334f);
        *(Quad_3fca40 *)obj10 = *a2;
        vec_scale_to_length(&local, q, -0.25f);
        FastVecAdd((char *)p + 0x50, a0, &local);
        g = (int)D_L00_001B0BB4;
        *(int *)((char *)p + 0x38) = g;
        f = IntToFloat(g);
        *(int *)((char *)p + 0x34) = a3;
        *(float *)((char *)p + 0x3C) = 1.0f / f;
        ref_L00_003FCA40_00(obj10);
        ref_L00_003FCA40_01(ref_L00_003FCA40_02, obj);
    }
    return obj;
}
