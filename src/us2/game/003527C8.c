#include "include_asm.h"

typedef unsigned char u8;
extern char *D_001B23CC[] __attribute__((sda));
extern void func_00350918(void *);
extern void func_00351E48(u8 *);
extern void func_00351B20(void *);
extern char *D_001B23CC[] __attribute__((sda));
extern char *D_001B23CC[] __attribute__((sda));
extern char *D_001B23CC[] __attribute__((sda));

void func_US2_003527C8(unsigned char *object)
{
    char *base;
    func_00350918(object + 0x48);
    func_00351E48(D_001B23CC[0] + 0xD9168);
    func_00351B20(object);
    base = D_001B23CC[0];
    while (*(int *)(base + 0xD9174)) {
        if (func_003518D8(object) == 1) break;
        base = D_001B23CC[0];
    }
    func_003518E0(object, 3);
}

