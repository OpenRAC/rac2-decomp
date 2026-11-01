#include "include_asm.h"

extern int func_00341E90(char *);

int func_PAL_00343EC0(char *object) { int index = func_00341E90(object); return *(int *)(object + 0xE8) + index * 20; }

extern void func_00348068(unsigned char *owner, float *records);

void func_PAL_00343F18(unsigned char *owner, float *records)
{
    func_00348068(owner + 0x10, records);
    *(float **)(owner + 0xE8) = records;
}

extern char *func_00347F80(char *, int);
extern void func_003480F0(char *, float, float);

long func_PAL_00343F50(char *object, int arg)
{
    char *child = object + 0x10;
    func_00347F80(child, arg);
    func_003480F0(child, (*(float **)object)[0], (*(float **)object)[1]);
    return 0;
}

