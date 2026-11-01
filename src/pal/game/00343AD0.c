#include "include_asm.h"

void func_00348138(int);
void func_00348138(int param_1);

void func_PAL_00343AD0(int param_1)
{
  func_00348138(param_1 + 0x238);
  return;
}


extern void func_00336320_6(char *);
extern void func_00336A78_7(char *);
extern void func_00341A48(char *);
extern void func_00341A68_1(char *);
extern void func_00341A88(char *);

/* Reads a word at +544 of the object; returns when it is zero, otherwise calls a repeated callee four times with the object and the objects at +152, +76 and +228, then one callee each with +464, the object, the object and the object. */
void func_PAL_00343C88(char *a0)
{
    if (*(int *)(a0 + 560) == 0)
        return;
    func_00336320_6(a0);
    func_00336320_6(a0 + 152);
    func_00336320_6(a0 + 76);
    func_00336320_6(a0 + 228);
    func_00336A78_7(a0 + 464);
    func_00341A48(a0);
    func_00341A68_1(a0);
    func_00341A88(a0);
}

char *func_PAL_00343CF8(char *p) {
    extern void func_00347EA0(void *);
    extern void func_003361A8(char *);
    func_00347EA0(p + 0x10);
    func_003361A8(p + 0xEC);
    func_003361A8(p + 0x138);
    return p;
}

