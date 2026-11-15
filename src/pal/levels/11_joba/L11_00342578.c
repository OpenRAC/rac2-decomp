#include "include_asm.h"

#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern int func_PAL_L02_00335678(char *, char *, void *);

int func_PAL_L11_00342578(char *object, void *point)
{
    char *target = object + 0x10;
    float diff[4];

    FastVecSub(diff, point, target);
    return func_PAL_L02_00335678(object, target, diff);
}

