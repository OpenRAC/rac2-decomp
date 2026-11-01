#include "include_asm.h"





extern void Fd1c2476b_FUN_00336320(char *p);
extern void Fd1c2476b_FUN_00336A78(char *p);
extern void Fd1c2476b_FUN_003462A8(char *p);
extern void Fd1c2476b_FUN_003463C8(char *p);
extern void Fd1c2476b_FUN_003464D0(char *p);

/* func_00345F70 is built from 00345358-layout-g8.c. */

/* func_003462A8 is built from 00345358-descriptor-g8.c for small-data access. */

/* func_003463C8 and func_003464D0 are built from 00345358-g8.c for small-data access. */


void func_PAL_00348728(char *a0)
{
    if (*(int *)(a0 + 1272) == 0)
        return;
    Fd1c2476b_FUN_00336320(a0);
    Fd1c2476b_FUN_00336320(a0 + 76);
    Fd1c2476b_FUN_00336320(a0 + 152);
    Fd1c2476b_FUN_00336320(a0 + 228);
    Fd1c2476b_FUN_00336A78(a0 + 456);
    Fd1c2476b_FUN_003462A8(a0);
    Fd1c2476b_FUN_003463C8(a0);
    Fd1c2476b_FUN_003464D0(a0);
    Fd1c2476b_FUN_00336320(a0 + 380);
    Fd1c2476b_FUN_00336A78(a0 + 784);
    Fd1c2476b_FUN_00336A78(a0 + 696);
    Fd1c2476b_FUN_00336A78(a0 + 872);
    Fd1c2476b_FUN_00336A78(a0 + 960);
    Fd1c2476b_FUN_00336A78(a0 + 1048);
}


extern void F5a9e4f98_FUN_003361A8(char *p);
extern void F5a9e4f98_FUN_003363D0(char *p);
extern void F5a9e4f98_FUN_00336968(char *p);
extern void F5a9e4f98_FUN_003366D0(char *p);

void *func_PAL_003487C8(char *p)
{
    F5a9e4f98_FUN_003361A8(p);
    F5a9e4f98_FUN_003361A8(p + 0x4c);
    F5a9e4f98_FUN_003361A8(p + 0x98);
    F5a9e4f98_FUN_003361A8(p + 0xe4);
    F5a9e4f98_FUN_003361A8(p + 0x130);
    F5a9e4f98_FUN_003361A8(p + 0x17c);
    F5a9e4f98_FUN_003363D0(p + 0x1c8);
    F5a9e4f98_FUN_00336968(p + 0x210);
    F5a9e4f98_FUN_00336968(p + 0x268);
    F5a9e4f98_FUN_00336968(p + 0x2C0);
    F5a9e4f98_FUN_00336968(p + 0x318);
    F5a9e4f98_FUN_00336968(p + 0x370);
    F5a9e4f98_FUN_003366D0(p + 0x3C8);
    F5a9e4f98_FUN_003361A8(p + 0x404);
    F5a9e4f98_FUN_003361A8(p + 0x450);
    F5a9e4f98_FUN_003361A8(p + 0x49C);

    return p;
}


INCLUDE_ASM("asm/pal/game", func_PAL_00348868);

INCLUDE_ASM("asm/pal/game", func_PAL_00348DF8);

extern float *func_00335E10(char *);
typedef unsigned char u8;
extern void func_00335E38(char *, float, float, float, float);
typedef struct { int x; int y; } MenuLabelOffset;
typedef struct { short a, b, c, id, e; } MenuGridEntry;
extern MenuGridEntry D_00259F58[];
extern u8 D_001A7AF8[] __attribute__((section(".sdata")));
extern u8 D_001A7A80[] __attribute__((section(".sdata")));
extern MenuLabelOffset ref_003472B8_00;
extern void func_00335E68(void *, int);
extern void func_00335E68(void *, int);

void func_PAL_00349450(char *obj)
{
    MenuLabelOffset pad;
    char *a;
    char *b;
    float x, y, x2, y2;
    u8 *flags;
    int bits;
    int index = D_00259F58[*(int *)(obj + 0x574) + *(int *)(obj + 0x578) * 4].id;

    if (D_001A7AF8[index] == 0)
        return;
    a = obj + 0x318;
    pad = ref_003472B8_00;
    flags = &D_001A7A80[index];
    b = obj + 0x370;
    bits = flags[0] & 4;
    func_00335E68(a, (flags[0] & 1) | (bits != 0));
    {
        int b2 = flags[0] & 0x10;
        func_00335E68(b, b2 != 0);
    }
    x = (*(float **)(obj + 0x4E8))[0] + func_00335E10(a)[0] + (float)pad.x;
    y = (*(float **)(obj + 0x4E8))[1] + func_00335E10(a)[1] + (float)pad.y;
    func_00335E38(a, x, y, 0.0f, 0.0f);
    x2 = (*(float **)(obj + 0x4E8))[0] + func_00335E10(b)[0] + (float)pad.x;
    y2 = (*(float **)(obj + 0x4E8))[1] + func_00335E10(b)[1] + (float)pad.y;
    func_00335E38(b, x2, y2, 0.0f, 0.0f);
}


INCLUDE_ASM("asm/pal/game", func_PAL_00349600);

INCLUDE_ASM("asm/pal/game", func_PAL_00349AB8);
