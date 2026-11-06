#include "include_asm.h"

extern char *func_00288FB8(int);
extern void func_PAL_0033CF78(void *, char *, char *, char *);
extern void func_PAL_0033CD50(char *p);
extern void func_0033B018(char *p, float x, float y);
extern void func_002E5E58(int a, int b, int c);
extern void func_0027AB40(void);
extern unsigned char D_001A7BB1;

/* func_PAL_0033E160, the PAL copy of func_0033C2D8: the same C, with the three-string setup added. */
int func_PAL_0033E160(char *object, int mask)
{
    float *v;
    char *child;
    char *text, *second;

    child = object + 8;
    text = func_00288FB8(0x10FC);
    second = func_00288FB8(0xB5F);
    func_PAL_0033CF78(child, text, second, func_00288FB8(0xB60));
    func_PAL_0033CD50(child);
    v = *(float **)(object + 0x2DC);
    func_0033B018(child, v[0], v[1]);
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2D8) == 0) {
        D_001A7BB1 = D_001A7BB1 == 0;
        func_002E5E58(4, 0, 0);
        func_0027AB40();
    }
    return (mask >> 6) & 1;
}
