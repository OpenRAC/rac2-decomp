#include "include_asm.h"

#include "common.h"
typedef int Quad_3fca40 __attribute__((mode(TI)));
extern void *func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern int D_L00_001B0BB4 __attribute__((sda));
extern void ref_L00_003FCA40_00(void *);
extern void ref_L00_003FCA40_01(void *, void *);
extern void ref_L00_003FCA40_02(void);

/* The allocator hands out a 0xD9C-byte object; the object is set up (flag halfword, three
   header bytes), the second argument's vector is copied into it, the object is normalised
   twice and added to the first argument, and the level's own copy of func_L00_003FD178 runs
   on it. */
char *func_PAL_L00_004012A0(char *a0, char *a1, Quad_3fca40 *a2, int a3)
{
    Quad_3fca40 local;
    char *obj;
    char *obj10;
    int *p;
    char *q;
    int g;
    float f;

    obj = (char *)func_0029EFD0(0xD9C);
    if (obj != 0) {
        *(unsigned char *)(obj + 0x30) = 0xFF;
        p = *(int **)(obj + 0x68);
        *(unsigned short *)(obj + 0x32) = 0xFF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(unsigned short *)(obj + 0x34) |= 0x41;
        *(unsigned char *)(obj + 0x20) = 0;
        q = (char *)p + 0x20;
        obj10 = obj + 0x10;
        func_00282F20(q, a1, 0.40000004f);
        *(Quad_3fca40 *)obj10 = *a2;
        func_00282F20(&local, q, -0.25f);
        func_00282CC0((char *)p + 0x50, a0, &local);
        g = (int)((s32)(D_L00_001B0BB4) * 5 + 2) / 6;
        *(int *)((char *)p + 0x38) = g;
        f = func_00283CE0(g);
        *(int *)((char *)p + 0x34) = a3;
        *(float *)((char *)p + 0x3C) = 1.0f / f;
        ref_L00_003FCA40_00(obj10);
        ref_L00_003FCA40_01(ref_L00_003FCA40_02, obj);
    }
    return obj;
}
