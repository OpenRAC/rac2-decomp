#include "include_asm.h"





extern void Fd1c2476b_FUN_00336320(char *p);
extern void Fd1c2476b_FUN_00336A78(char *p);
extern void Fd1c2476b_FUN_003462A8(char *p);
extern void Fd1c2476b_FUN_003463C8(char *p);
extern void Fd1c2476b_FUN_003464D0(char *p);

/* func_00345F70 is built from 00345358-layout-g8.c. */

/* func_003462A8 is built from 00345358-descriptor-g8.c for small-data access. */

/* func_003463C8 and func_003464D0 are built from 00345358-g8.c for small-data access. */


void func_US2_00347550(char *a0)
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


extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);
extern void func_003363D0(char *p);
extern void func_00336968(char *p);
extern void func_003366D0(char *p);

extern void func_003361A8(char *p);

char *func_US2_003475F0(char *p)
{
    func_003361A8(p);
    func_003361A8(p + 76);
    func_003361A8(p + 152);
    func_003361A8(p + 228);
    func_003361A8(p + 304);
    func_003361A8(p + 380);
    func_003363D0(p + 456);
    func_00336968(p + 528);
    func_00336968(p + 616);
    func_00336968(p + 704);
    func_003366D0(p + 792);
    func_003361A8(p + 852);
    func_003361A8(p + 928);
    func_003361A8(p + 1004);
    return p;
}






INCLUDE_ASM("asm/us2/game", func_US2_00347680);

INCLUDE_ASM("asm/us2/game", func_US2_00347B88);

INCLUDE_ASM("asm/us2/game", func_US2_003481E0);

INCLUDE_ASM("asm/us2/game", func_US2_00348628);
