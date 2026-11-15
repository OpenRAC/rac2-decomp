#include "include_asm.h"
#include "names.h"

/* func_L00_00403D58 and func_L00_00404DD8 are a unit of their own: both need the opt-in
   quadword-copy profile and its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier,
   config/cflags.txt), which give retail's grouped `lq`/`sq` with register addresses and
   keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CC0(char *a, int *b, char *c);
extern void func_00300190(char *a, char *b);
extern void func_002FEE70(int a, int *b, int c);
extern int func_00282948(char *a);
/* The callback dispatcher differs from the catalogue pairing in four levels. */
extern void ref_L00_00403D58_00(void (*f)(char *), char *arg);
extern void func_L00_00404168(char *arg);
extern void func_L00_00403F90(char *arg, void *p);
extern void func_002FEE50(int a);
extern void func_0029F338(char *arg);

/* Per-frame update of a flying shot: it moves along its velocity until a timer ends, then removes itself. */
void func_L00_00403D58(char *arg)
{
    int *o = *(int **)(arg + 104);
    unsigned char state = *(unsigned char *)(arg + 32);
    TI128 tmp;
    char *p;

    switch (state) {
    case 0:
        arg[32] = 1;
    case 1:
        p = arg + 16;
        *(TI128 *)&tmp = *(TI128 *)p;
        FastVecAdd(p, o, p);
        TransformVectorOrCopy(p, p);
        SteerEffectDirection(o[7], o, 0);
        ResolveSheepShotHit(arg, &tmp);
        if (FastFloatHelperD((char *)o + 16) != 0)
            arg[32] = 2;
        break;
    case 2:
        ClearEntryFlag(o[7]);
        MarkMobySpawned(arg);
        return;
    default:
        break;
    }
    ref_L00_00403D58_00(UpdateSmokySparkEffect, arg);
}

extern void func_002E5DA0(int a, int b, void *c, int d);
extern int func_002761F8(void *a, void *b, int c, void *d, int e);
extern void func_0029F338(char *arg);
extern TI128 D_L00_001BF220;

/* Removes the object if it leaves the map; if it hits something it snaps to a saved spot, plays a sound and enters its end state. */
void func_L00_00404DD8(char *arg, void *a1)
{
    char *p;

    if (*(float *)(arg + 16) < 2.0f || *(float *)(arg + 16) > 1021.0f ||
        *(float *)(arg + 20) < 2.0f || *(float *)(arg + 20) > 1021.0f ||
        *(float *)(arg + 24) < 2.0f || *(float *)(arg + 24) > 1021.0f) {
        MarkMobySpawned(arg);
        return;
    }
    p = arg + 16;
    if (CollLine(a1, p, 0, arg, 0) != 0) {
        *(TI128 *)p = D_L00_001BF220;
        arg[32] = 2;
        PlaySoundFromClassBank(5, 0, arg, 3705);
    }
}
