#include "include_asm.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern s32 func_00282948(u8 *a0);
extern s32 func_0030CBA8(s32 a0);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern s32 func_L00_00367720(u8 *a0);
extern void func_L05_00379E60(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_L05_0037B538(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_L05_0037B3A0(u8 *a0);
extern s32 func_002A7820(s32 a0, s32 a1);
extern u32 *func_00379CA0(u8 *a0);
extern u8 *func_0037B440(s32 a0);
extern void func_PAL_L05_00427CF8(u8 *a0);
extern void func_PAL_L05_00427D70(u8 *a0);
extern s32 D_001B1364 __attribute__((sda));
extern s32 D_001B13E4 __attribute__((sda));
extern u8 D_L05_00221D10[];
extern u8 D_L05_001B3550[];
extern s32 D_L05_001B2048;
extern u8 *D_001B2614;
extern u8 D_L05_001B1354[];
extern u8 D_L05_001B1358[];
extern u8 D_L05_001B135C[];
extern u8 D_L05_001495B8[];
extern u8 *D_L05_0020B220[];
extern u32 D_L05_001FB220[];
extern u8 *D_L05_001B251C[] __attribute__((sda));
extern s32 D_001B1350 __attribute__((sda));

/* State 0 waits for func_L00_00367720, then enters state 1. State 1 calls func_L05_0037B538 and, when the
   +0x26C timer of its state expires, picks an entry of the object's id list and passes that object
   (this one when the list has fewer than two entries) to func_PAL_L05_00427D70. */
void func_PAL_L05_00427BB0(u8 *arg0)
{
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    u8 *target;
    s32 i;
    s32 n;

    if (arg0[0x20] == 0) {
        arg0[0x30] = 0xFF;
        if (func_L00_00367720(arg0) == 0)
            return;
        func_PAL_L05_00427CF8(arg0);
        if (*(s32 *)(s1 + 0x264) == 0)
            return;
        func_L05_00379E60(arg0, 0, 0, 0);
        return;
    }

    func_L05_0037B538(arg0, 0, 1, 1);
    if (*(s32 *)(s1 + 0x264) == 0)
        return;
    if (func_00282948(s1 + 0x26C) == 0)
        return;
    target = 0;
    n = func_L05_0037B3A0(arg0);

    if (n >= 2) {
        s32 count = func_002A7820(0, n - 1);
        u16 *p = (u16 *)D_L05_001FB220[arg0[0x21]];
        u16 v;
        i = 0;
        do {
            v = *p;
            n = v & 0x7FFF;
            if (i == count)
                goto found;
            i++;
            p++;
        } while ((s16)v >= 0);
        goto done;
found:
        target = D_L05_001B251C[0] + (n << 8);
    } else {
        target = arg0;
    }
done:
    if (target != 0)
        func_PAL_L05_00427D70(target);
    *(s32 *)(s1 + 0x26C) = 0x64;
}
