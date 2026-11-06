#include "include_asm.h"

/* func_PAL_L14_003E8FB8, the PAL copy of func_L14_003E4BA0: the same C, where the reloaded key
   counter is the key word, read whole and scaled to 50 Hz. The walks also pair up differently:
   retail keeps the first in $a2 and the other two in $a1, so the first has its own pointer and
   the other two share one. */

extern unsigned short *D_L14_001FB060[];
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern int D_L14_001B25B8 __attribute__((sda));
extern int func_002B3868(char *self);
extern int func_00282978(char *p);
extern void func_PAL_L14_003E92D8(char *self);
extern void func_L14_003E5030(char *self);
extern void func_PAL_L14_003E9570(char *self);
extern void func_L14_003E5190(char *self);
extern void func_L14_003E51B0(char *self);
extern void func_PAL_L14_003E96D8(char *self);

/* The key state of an object that steers a group (+0x14 the current key, +0x16 the key index,
   +0x34 the key word). The last walk stores through this struct, as in the template: loop.c can
   then hoist the two level globals and the constants out of that loop. */
typedef struct {
    unsigned char pad[0x14];
    unsigned short cur;
    unsigned short index;
} L14Key;

void func_PAL_L14_003E8FB8(unsigned char *self)
{
    unsigned char *state = *(unsigned char **)(self + 0x68);
    unsigned short *p;
    unsigned short *q;
    unsigned char *e;

    switch (self[0x20]) {
    case 0:
        for (p = D_L14_001FB060[self[0x21]];
             self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[self[0x21]]);
             p++) {
            e = D_L14_001B259C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0xB19) {
                unsigned char *d = *(unsigned char **)(e + 0x68);

                *(unsigned short *)(d + 0x40) = *(unsigned short *)(state + 0x40);
                *(unsigned short *)(d + 0x42) = *(unsigned short *)(state + 0x42);
                *(unsigned short *)(d + 0x44) = *(unsigned short *)(state + 0x44);
                *(unsigned short *)(d + 0x46) = *(unsigned short *)(state + 0x46);
                *(unsigned short *)(d + 0x48) = *(unsigned short *)(state + 0x48);
                *(unsigned short *)(d + 0x4A) = *(unsigned short *)(state + 0x4A);
            }
        }
        func_L14_003E5030((char *)self);
        break;
    case 2:
        if (func_002B3868((char *)self) != 0) {
            func_PAL_L14_003E96D8((char *)self);
            func_L14_003E5190((char *)self);
        }
        break;
    case 1:
        if (func_002B3868((char *)self) != 0)
            func_L14_003E51B0((char *)self);
        func_PAL_L14_003E92D8((char *)self);
        break;
    }
    if (*(int *)(state + 0x34) != 0) {
        if (func_00282978((char *)(state + 0x14)) != 0) {
            *(unsigned short *)(state + 0x14) = (*(int *)(state + 0x34) * 5 + 2) / 6;
            for (q = D_L14_001FB060[self[0x21]];
                 self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && q != 0 &&
                 ((q != 0 && (short)q[-1] >= 0) || q == D_L14_001FB060[self[0x21]]);
                 q++) {
                e = D_L14_001B259C + ((*q & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(short *)(e + 0xAA) == 0xB19)
                    *(unsigned short *)(*(unsigned char **)(e + 0x68) + 0x16) = 0;
            }
        }
        for (q = D_L14_001FB060[self[0x21]];
             self[0x21] != 0xFF && self[0x21] <= D_L14_001B25B8 && q != 0 &&
             ((q != 0 && (short)q[-1] >= 0) || q == D_L14_001FB060[self[0x21]]);
             q++) {
            e = D_L14_001B259C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0xB19)
                ((L14Key *)*(unsigned char **)(e + 0x68))->cur = ((L14Key *)state)->cur;
        }
    }
    func_PAL_L14_003E9570((char *)self);
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L14_003E92D8);
