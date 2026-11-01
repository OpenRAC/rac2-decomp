#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_0034D230);

INCLUDE_ASM("asm/pal/game", func_PAL_0034D238);

INCLUDE_ASM("asm/pal/game", func_PAL_0034D490);

extern int func_00335E20(unsigned char *field);

unsigned int func_PAL_0034EC30(unsigned char *owner)
{
    unsigned int address = (unsigned int)func_00335E20(owner + 0x378);
    return *(unsigned int *)address & 0xff000000u;
}


extern void func_00336920(char *, int, int);

void func_PAL_0034EC58(char *self, int mode)
{
    *(int *)(self + 0x15A4) = mode;
    switch (mode) {
    case 0:
        func_00336920(self + 0x2A0, 0x7567, 0);
        break;
    case 1:
        func_00336920(self + 0x2A0, 0xEAA2, 0);
        break;
    }
}


extern void F72a1dff5_FUN_00349AB8(char *p, int a);
extern void F72a1dff5_FUN_00349630(char *p, int a);
extern void F72a1dff5_FUN_00336920(char *p, void *b, int c);

void func_PAL_0034ECB0(char *p, void *a1, int a2)
{
    *(int *)(p + 0x1584) = a2;
    if (*(int *)(p + 0x1588) != 0) {
        *(int *)(p + 0x1588) = 0;
        F72a1dff5_FUN_00349AB8(p + 0xF3C, 0);
        F72a1dff5_FUN_00349AB8(p + 0xFD0, 0);
        F72a1dff5_FUN_00349AB8(p + 0x1064, 0);
        F72a1dff5_FUN_00349630(p + 0x10F8, 1);
        F72a1dff5_FUN_00349AB8(p + 0x1180, 0);
        F72a1dff5_FUN_00336920(p + 0x158, a1, 0);
    }
    if (*(int *)(p + 0x159C) != 0) {
        F72a1dff5_FUN_00336920(p + 0x158, a1, 0);
    }
}


typedef int s32;
extern void F01bd4546_FUN_00335E68(char *p, int v);
extern void F01bd4546_FUN_00349630(char *p, int v);
extern void F01bd4546_FUN_00349678(char *p, float v);

void func_PAL_0034ED50(char *self, int x)
{
    char *p1, *p2, *p3, *p4, *p5, *p6;

    *(s32 *)(self + 5524) = x;
    if (*(s32 *)(self + 5528) != 0) {
        *(s32 *)(self + 5528) = 0;
        F01bd4546_FUN_00335E68(self + 1496, 0);
        p1 = self + 3084;
        p2 = self + 3220;
        p3 = self + 3356;
        p4 = self + 3492;
        p5 = self + 3628;
        p6 = self + 3764;
        F01bd4546_FUN_00349630(p1, 1);
        F01bd4546_FUN_00349630(p2, 1);
        F01bd4546_FUN_00349630(p3, 1);
        F01bd4546_FUN_00349630(p4, 1);
        F01bd4546_FUN_00349630(p5, 1);
        F01bd4546_FUN_00349630(p6, 1);
        F01bd4546_FUN_00349678(p1, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(p2, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(p3, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(p4, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(p5, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(p6, *(s32 *)0x1A7C18 ? 0.14f : 0.116666675f);
    }
}


extern int func_PAL_002A9FA0(int, int, int, int, int);
extern void func_00335E68(void *, int);
extern int D_00138344;
extern int func_PAL_002A9FA0(int, int, int, int, int);
extern float *func_00336318(void *);
extern void func_00335E68(void *, int);

void func_PAL_0034EF38(char *object, int arg, float value)
{
    int *result;
    char *child;
    if (D_00138344 & 0xF000)
        func_PAL_002A9FA0(0, 0, 1, 0, 1);
    child = object + 0x5D8;
    result = (int *)func_00335E20((unsigned char *)child);
    *result = func_PAL_002A9FA0(0x60442D00, 0x70FFFEED, 20, 0, 0);
    *func_00336318(child) = value;
    func_00335E68(child, arg);
}


extern void F076896f4_FUN_00349AB8(void *, int);

void func_PAL_0034EFF0(int *self, int value)
{
    self[1379] = value;
    if (self[1380] != 0) {
        self[1380] = 0;
        F076896f4_FUN_00349AB8((char *)self + 4628, 0);
        F076896f4_FUN_00349AB8((char *)self + 4776, 0);
        F076896f4_FUN_00349AB8((char *)self + 4924, 0);
        F076896f4_FUN_00349AB8((char *)self + 5072, 0);
    }
}


INCLUDE_ASM("asm/pal/game", func_PAL_0034F050);

INCLUDE_ASM("asm/pal/game", func_PAL_0034F060);

INCLUDE_ASM("asm/pal/game", func_PAL_0034F068);

INCLUDE_ASM("asm/pal/game", func_PAL_0034FD60);

extern void func_003363D0(void *p);
extern void func_PAL_0034D238(void *p);
extern void func_003366D0(void *p);
extern void func_00337BD8(void *p);

/* walks 26 consecutive 72-byte records calling one leaf per record, then calls four more leaves on fixed offsets of the same object and returns the object pointer */
unsigned char *func_PAL_003501C8(unsigned char *a0)
{
    unsigned char *p;
    int i;

    for (i = 25, p = a0; i != -1; i--) {
        func_003363D0(p);
        p += 72;
    }
    func_003363D0(a0 + 1872);
    func_PAL_0034D238(a0 + 1952);
    func_003366D0(a0 + 7504);
    func_00337BD8(a0 + 7564);
    func_00337BD8(a0 + 8156);
    return a0;
}

