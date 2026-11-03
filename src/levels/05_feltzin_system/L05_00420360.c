#include "include_asm.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef int TI128 __attribute__((mode(TI)));

extern s32 func_003062A0(u8 *a0);
extern s32 func_0030CBA8(s32 a0);
extern void func_00326198(s32 a0, s32 a1);
extern void func_002FF9F8(s32 a0);
extern void func_0037B210(void);
extern void func_003404B8(void);
extern void func_00379F18(s32 a0);
extern u8 **func_00379EB8(void);
extern s32 func_00379EC8(void);
extern void func_0037B280(u8 *a0, s32 a1);
extern void func_0037CEE0(u8 *a0, u8 *a1, f32 f12);
extern void func_0037D608(u8 *a0, u8 *a1, f32 f12);
extern s32 func_00379860(u8 *a0);
extern void func_00379E60(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_0037B538(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_0037B3A0(u8 *a0);
extern s32 func_00332AF8(s32 a0, s32 a1);
extern u32 *func_00379CA0(u8 *a0);
extern void func_0037AEC0(u8 *a0, s32 a1);
extern void func_00379C68(u8 *a0, s32 a1);
extern u8 *func_0037B440(s32 a0);
extern void func_0037D210(u8 *a0);
extern void func_00306748(u8 *a0, u8 *a1, u8 *a2);
extern void func_003068F8(u8 *a0, u8 *a1, f32 f12);
extern void func_00329960(u8 *a0, u8 *a1, u8 *a2);
extern void func_003298C0(u8 *a0, u8 *a1, u8 *a2);
extern void func_L05_00420788(u8 *a0, s32 a1);
extern void func_L05_004209D8(u8 *a0, s32 a1);
extern void func_L05_0041FC60(u8 *a0);
extern void func_L05_004224C8(u8 *a0);
extern void func_L05_00422540(u8 *a0);

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

INCLUDE_ASM("asm/levels", func_L05_00420360);

/* func_L05_00420788 lives in L05_00420788-g8.c. */

/* func_L05_004209D8 lives in the -g8 sibling: its reset flag is reached through $gp. */

/* func_L05_00420A88 lives in L05_00420A88-g8.c. */



/* func_L05_00420FB0 lives in L05_00420FB0-g8.c. */

/* func_L05_00421100 lives in L05_00421100-g8.c. */

INCLUDE_ASM("asm/levels", func_L05_00421B98);


/* State 0 waits for func_00379860, then enters state 1. State 1 calls func_0037B538 and, when the
   +0x26C timer of its state expires, picks an entry of the object's id list and passes that object
   (this one when the list has fewer than two entries) to func_L05_00422540. */
void func_L05_00422380(u8 *arg0)
{
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    u8 *target;
    s32 i;
    s32 n;

    if (arg0[0x20] == 0) {
        arg0[0x30] = 0xFF;
        if (func_00379860(arg0) == 0)
            return;
        func_L05_004224C8(arg0);
        if (*(s32 *)(s1 + 0x264) == 0)
            return;
        func_00379E60(arg0, 0, 0, 0);
        return;
    }

    func_0037B538(arg0, 0, 1, 1);
    if (*(s32 *)(s1 + 0x264) == 0)
        return;
    if (func_003062A0(s1 + 0x26C) == 0)
        return;
    target = 0;
    n = func_0037B3A0(arg0);

    if (n >= 2) {
        s32 count = func_00332AF8(0, n - 1);
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
        func_L05_00422540(target);
    *(s32 *)(s1 + 0x26C) = 0x78;
}

void func_L05_004224C8(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);

    *(u16 *)(arg0 + 0x34) |= 0x100;
    arg0[0x20] = 1;
    *(s32 *)((u8 *)func_00379CA0(arg0) + 0x148) = 0xA;
    func_0037AEC0(arg0, 1);
    *(s32 *)(s1 + 0x26C) = 0;
    *(s32 *)(s1 + 0x268) = 0;
    *(f32 *)(s1 + 0x230) = 10.0f;
    func_00379C68(arg0, 0xFFFF);
}

/* func_L05_00422540 lives in L05_00422540-qcopy.c. */

/* shared native body of family 5a97ab89858c */
void func_L05_00433400(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
