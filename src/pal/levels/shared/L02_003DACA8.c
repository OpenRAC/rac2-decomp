#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern unsigned char D_00188660[];
extern int D_L02_001B3FD8 __attribute__((sda));
extern void func_L02_003D6DF8(void *);
extern void func_L02_003D7040(void *);
extern void func_L02_003D7140(void *);
extern void func_L00_00323958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00283658(void *, void *);
extern void func_002AB6D8(float *, float *);
extern int func_002E5CF8(int, int, char *);
extern int func_002E59B0(int, int);
extern void func_002E59F8(int);
extern int func_00282948(void *);

/* The level's own sound-emitter update: the kind byte at +0x20 of the object picks the
   work, the shared emitter table at D_00188660 holds the listeners. */
void func_PAL_L02_003DACA8(char *a0)
{
    char *s1 = a0;
    char *s2;
    unsigned char buf[0x40];

    s2 = *(char **)(s1 + 0x68);
    func_L02_003D6DF8(a0);

    switch (*(unsigned char *)(s1 + 0x20)) {
    case 2:
        if (*(int *)(s2 + 0xBC) == 0)
            return;
        func_002A7750(s1, 3, -1);
        *(int *)(s2 + 0xB4) = D_L02_001B3FD8;
        break;
    case 1:
        func_L02_003D7140(s1);
        if (*(unsigned char *)(s1 + 0x31) != 0)
            func_L02_003D7040(s1);
        if (*(int *)(s2 + 0xBC) != 0)
            return;
        func_002A7750(s1, 4, -1);
        *(int *)(s2 + 0xB4) = D_L02_001B3FD8;
        break;
    case 3:
        func_00283738(s1 + 0xC0, s2 + 0x80, s1 + 0xC0);
        if (*(int *)(s2 + 0xB4) == D_L02_001B3FD8)
            func_002E5CF8(1, 0, s1);
        func_00283658(buf, s1 + 0xC0);
        func_002AB6D8((float *)buf, s1 + 0xF0);
        func_L00_00323958(s1, s2 + 0x30);
        func_L02_003D7140(s1);
        func_00282948(s2 + 0xB4);
        if (*(int *)(s2 + 0xB4) == 0)
            func_002A7750(s1, 1, -1);
        if (func_002E59B0((int)s1, *(short *)(s2 + 0xC0)) != 0)
            return;
        *(short *)(s2 + 0xC0) = func_002E5CF8(0, 4, s1);
        break;
    case 4:
        func_00283738(s1 + 0xC0, s2 + 0x80, s1 + 0xC0);
        func_00283658(buf, s1 + 0xC0);
        func_002AB6D8((float *)buf, s1 + 0xF0);
        func_L00_00323958(s1, s2 + 0x30);
        func_L02_003D7140(s1);
        func_00282948(s2 + 0xB4);
        if (*(int *)(s2 + 0xB4) != 0)
            return;
        if (*(short *)(s2 + 0xC0) != -1) {
            unsigned char *e = D_00188660 + *(short *)(s2 + 0xC0) * 0x70;

            if (*(int *)(e + 0x88) == (int)s1 && *(unsigned char *)(e + 0x74) != 0)
                func_002E59F8(*(short *)(s2 + 0xC0));
        }
        *(short *)(s2 + 0xC0) = -1;
        func_002A7750(s1, 2, -1);
        break;
    }
}

