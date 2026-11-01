#include "include_asm.h"

extern void func_003361A8(void *p);
extern void func_00336968(void *p);

/* func_00338F58 is matched in 00338F58.c. */

/* Initialises eight sub-objects at byte offsets 8, 84, 160, 236 (step 76) and 312, 384, 456, 528 (step 72) of the argument with two different helpers and returns the argument. */
void *func_PAL_0033AEF8(char *a0)
{
    func_003361A8(a0 + 8);
    func_003361A8(a0 + 84);
    func_003361A8(a0 + 160);
    func_003361A8(a0 + 236);
    func_00336968(a0 + 312);
    func_00336968(a0 + 400);
    func_00336968(a0 + 488);
    func_00336968(a0 + 576);
    return a0;
}


INCLUDE_ASM("asm/pal/game", func_PAL_0033AF68);

INCLUDE_ASM("asm/pal/game", func_PAL_0033B218);

extern void func_00336320(char *a);
extern void func_PAL_00338770(char *a);

/* early-returns when a 32-bit field is zero, otherwise calls one helper four times and another three times with fixed byte offsets off the argument pointer. */
void func_PAL_0033B4B8(char *a0)
{
    if (*(int *)(a0 + 728) == 0)
        return;
    func_00336320(a0 + 8);
    func_00336320(a0 + 84);
    func_00336320(a0 + 160);
    func_00336320(a0 + 236);
    func_PAL_00338770(a0 + 312);
    func_PAL_00338770(a0 + 400);
    func_PAL_00338770(a0 + 488);
}



typedef int s32;
typedef unsigned char u8;

void func_PAL_0033B688(u8 *a0) {s32 v=1;*(s32 *)(a0+0x330)=v;}

extern void func_0033AE18(unsigned char *owner, int value);

void func_PAL_0033B698(unsigned char *owner, int value)
{
    func_0033AE18(owner + 8, value);
}

/* Measured target: byte-identical across all 27 levels. */
void func_PAL_0033B6B8(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x328) = a1; }

extern int func_00288FB8_3(int);
extern void func_0033B050(char *, int, int, int);
extern void func_0033B0A8(char *, float);

/* Calls a one-argument helper three times with three fixed small integers, passes the three results and a pointer plus 8 to a four-argument helper, calls a two-argument helper with the same address and 0.0f, then clears the word at offset 764. */
void func_PAL_0033B6C0(char *p)
{
    int first = func_00288FB8_3(2991);
    int second = func_00288FB8_3(2989);

    func_0033B050(p + 8, first, second, func_00288FB8_3(2912));
    func_0033B0A8(p + 8, 0.0f);
    *(int *)(p + 812) = 0;
}



extern void func_L00_0042BAD0_1(char *object);
extern void func_L00_0042C290_1(char *object);

/* calls two one-argument functions on a sequence of sub-objects of the argument (four at 8..236 stride 76, nine at 312..888 stride 72) and returns the argument */
char *func_PAL_0033B960(char *object)
{
    func_L00_0042BAD0_1(object + 8);
    func_L00_0042BAD0_1(object + 84);
    func_L00_0042BAD0_1(object + 160);
    func_L00_0042BAD0_1(object + 236);
    func_L00_0042C290_1(object + 312);
    func_L00_0042C290_1(object + 400);
    func_L00_0042C290_1(object + 488);
    func_L00_0042C290_1(object + 576);
    func_L00_0042C290_1(object + 664);
    func_L00_0042C290_1(object + 752);
    func_L00_0042C290_1(object + 840);
    func_L00_0042C290_1(object + 928);
    func_L00_0042C290_1(object + 1016);
    return object;
}

INCLUDE_ASM("asm/pal/game", func_PAL_0033BE50);

extern void F8ad956d6_FUN_00336320(char *target);
extern void F8ad956d6_FUN_002FC560(int marker, int code);
extern void F8ad956d6_FUN_00295F60(int first, int second);
extern void F8ad956d6_FUN_002DAF68(char *target);
extern void F8ad956d6_FUN_00336A78(char *target);

void func_PAL_0033C308(char *object)
{
    char *s0 = object;

    if (*(int *)(s0 + 1168) == 0)
        return;
    F8ad956d6_FUN_00336320(s0 + 8);
    F8ad956d6_FUN_00336320(s0 + 84);
    F8ad956d6_FUN_002FC560(66, 68);
    F8ad956d6_FUN_002FC560(71, 11);
    F8ad956d6_FUN_00295F60(0, 1);
    F8ad956d6_FUN_002DAF68(0);
    F8ad956d6_FUN_00336320(s0 + 160);
    F8ad956d6_FUN_00336320(s0 + 236);
    F8ad956d6_FUN_00336A78(s0 + 312);
    F8ad956d6_FUN_00336A78(s0 + 400);
    F8ad956d6_FUN_00336A78(s0 + 488);
    F8ad956d6_FUN_00336A78(s0 + 576);
    F8ad956d6_FUN_00336A78(s0 + 664);
    F8ad956d6_FUN_00336A78(s0 + 752);
    F8ad956d6_FUN_00336A78(s0 + 840);
    F8ad956d6_FUN_00336A78(s0 + 928);
    F8ad956d6_FUN_00336A78(s0 + 1016);
}

