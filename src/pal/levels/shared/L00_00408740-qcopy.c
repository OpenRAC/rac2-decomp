#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CC0(char *a, int *b, char *c);
extern void func_00300190(char *a, char *b);
extern void func_002FEE70(int a, int *b, int c);
extern int func_00282948(char *a);
extern void ref_L00_00403D58_00(void (*f)(char *), char *arg);
extern void func_L00_00404168(char *arg);
extern void func_PAL_L00_00408978(char *arg, void *p);
extern void func_002FEE50(int a);
extern void func_0029F338(char *arg);
extern void func_0029F338(char *arg);
extern TI128 D_L00_001BF220;

void func_PAL_L00_00408740(char *arg)
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
        func_00282CC0(p, o, p);
        func_00300190(p, p);
        func_002FEE70(o[7], o, 0);
        func_PAL_L00_00408978(arg, &tmp);
        if (func_00282948((char *)o + 16) != 0)
            arg[32] = 2;
        break;
    case 2:
        func_002FEE50(o[7]);
        func_0029F338(arg);
        return;
    default:
        break;
    }
    ref_L00_00403D58_00(func_L00_00404168, arg);
}
