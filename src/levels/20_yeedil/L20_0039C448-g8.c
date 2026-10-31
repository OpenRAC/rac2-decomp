#include "include_asm.h"

/* This unit is built with -G8: every body here reaches a global through $gp.
   The markers below are the functions of L20_0039C448.c whose retail bodies access
   data through $gp; they are written in this file, which the build compiles with -G8. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;

/* 0x1AEFF0 + 0x39F0 : this symbol is written through $gp (gas emits the
 * gp-relative form because the store sits in the bc1f delay slot), so the
 * file has to be compiled with -G8 and the symbol marked sda. */
extern float D_L20_001B29E0 __attribute__((sda));

/* 0x1AEFF0 + 0x39F0 again, under a second name: gcc must not see the two
 * stores as one dead store, and gas expands this one to lui $at / swc1. */
extern float D_L20_001B29E0_1;

void func_L20_004095D0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    float v = *(float *)(state + 0xC) * 1.2f;

    D_L20_001B29E0 = v;
    if (v > 1.0f) {
        D_L20_001B29E0_1 = 1.0f;
    }
}

INCLUDE_ASM("asm/levels", func_L20_0039D680);

/* func_L20_0039E368 dispatches through the level's own jump table
   jtbl_002B4CA0 and reads D_L20_001AED04 and D_L20_001AED08 through
   $gp. The early exit has its own copy of case 5's tail, which
   cross-jumping merges after scheduling; with one shared label instead,
   the argument moves of case 5's func_0032DA58 call come out in another
   order. */
extern void func_002A7750(char *, int, int);
extern void func_L20_0039E5F0(char *);
extern void func_L20_0039E770(char *);
extern s32 func_002B3868(char *);
extern void func_002A7470(char *, s32, s32, s32);
extern void func_0029FCC0(char *, s32, char *);
extern void func_0029FC20(char *, s32, char *);
extern void func_00282F20(char *, char *, float);
extern void func_L09_003AE8C8(char *, char *, char *, s32, s32, float, float, float, float);
extern void func_00282CF0(char *, void *, char *);
extern void func_0032DA58(char *, char *, char *, float);
extern void func_002A6C58(char *, s32, s32);
extern void func_0029F338(char *);

extern int D_L20_001A8F00;
extern int D_L20_001BDCF0 __attribute__((nosda));
extern int D_L20_001B2AC8;
extern void *D_L20_001B9FC0[];
extern float D_L20_001AED04 __attribute__((sda));
extern float D_L20_001AED08 __attribute__((sda));

void func_L20_0039E368(char *arg0)
{
    char bufA[0x10];
    char bufB[0x40];
    char bufC[0x10];
    char *state;

    state = *(char **)(arg0 + 0x68);
    func_L20_0039E5F0(arg0);
    if (D_L20_001A8F00 == 2 && D_L20_001BDCF0 >= 5) {
        func_0029F338(arg0);
        return;
    }
    switch (*(u8 *)(arg0 + 0x20)) {
    case 2:
        if (func_002B3868(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 0)
            func_002A7470(arg0, 0, 0, 0xA);
        if (*(u8 *)(arg0 + 0x31) != 0 && *(u16 *)(arg0 + 0x96) >= 0xB5)
            func_002A7750(arg0, 3, -1);
        break;
    case 3:
        if (func_002B3868(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 1)
            func_002A7470(arg0, 1, 0, 0xF);
        if ((D_L20_001B2AC8 & 0xF) == (((int)arg0 >> 8) & 0xF)) {
            func_0029FCC0(arg0, 2, bufA);
            func_0029FC20(arg0, 2, bufB);
            func_00282F20(bufC, bufB, D_L20_001AED04 * 0.016666668f);
            func_L09_003AE8C8(bufA, arg0, bufC, 1, 1, (float)*(u8 *)(state + 0x34),
                              D_L20_001AED08, 1.0f, 1.0f);
        }
        if (*(u8 *)(arg0 + 0x31) == 0 || *(u16 *)(arg0 + 0x96) >= 0xB5)
            func_002A7750(arg0, 2, -1);
        break;
    case 4:
        if (func_002B3868(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 2)
            func_002A7470(arg0, 2, 0, 0xA);
        if (*(u8 *)(arg0 + 0x60) & 0x2)
            func_002A7750(arg0, 2, -1);
        break;
    case 5:
        func_00282CF0(bufA, D_L20_001B9FC0, arg0 + 0x10);
        func_00282F20(bufA, bufA, 1.0f);
        func_0032DA58(arg0, arg0 + 0x10, bufA, 0.0f);
        func_002A6C58(arg0, 0, 3);
        func_0029F338(arg0);
        return;
    default:
        break;
    case 1:
        return;
    }
    func_L20_0039E770(arg0);
}

extern char *D_L20_001FBB20[];

extern int D_L20_001B2FB8;

extern char *D_L20_001B2F9C;

extern char *D_L20_001B308C __attribute__((sda));

extern void func_0032F5B0(void *, int, int);

void func_L20_0039E890(int arg0, float arg1) {
    char *s1 = D_L20_001FBB20[arg0];
    int s4 = arg0 & 0xFF;
    float f20 = arg1;

    if (s4 == 0xFF) {
        goto end;
    }
    if (D_L20_001B2FB8 < arg0) {
        goto end;
    }
    if (s1 == 0) {
        goto end;
    }
    for (;;) {
        char *s0 = (char *)D_L20_001B2F9C + ((*(u16 *)s1 & 0x7FFF) << 8);

        if (s0 == 0) {
            goto end;
        }
        if (*(u8 *)(s0 + 0x20) == 1) {
            u16 v0 = *(u16 *)(s0 + 0x34);
            char *a3 = *(char **)(s0 + 0x24);

            v0 = (u16)((v0 & 0xFFBE) | 0x1000);
            *(u16 *)(s0 + 0x34) = v0;
            *(int *)(s0 + 0x98) = *(int *)(a3 + 0x10);
            func_0032F5B0(s0, 2, -1);
            if (0.0f < f20) {
                char *v1 = *(char **)(s0 + 0x68);

                *(f32 *)((char *)D_L20_001B308C + 0x38 + (*(int *)(v1 + 0x84) << 7)) = f20;
            }
        }
        s1 += 2;
        if ((arg0 & 0xFF) == 0xFF) {
            goto end;
        }
        if (D_L20_001B2FB8 < arg0) {
            goto end;
        }
        if (s1 == 0) {
            return;
        }
        if (*(s16 *)(s1 - 2) >= 0) {
            continue;
        }
        if (s1 == D_L20_001FBB20[arg0]) {
            continue;
        }
        break;
    }
end:
    return;
}

/* func_L20_0039E9F8 is defined in L20_0039E9F8-g8.c (it reaches D_L20_001B308C by absolute address and needs -mno-split-addresses). */

/* func_L20_0039ED78 reads D_L20_001AEDA8 and D_L20_001AED90 through
   $gp. Each branch makes its own func_00283D38 call; cross-jumping
   merges the two identical call tails, which puts the 0.5f add in the
   jal delay slot as in the retail. */
extern int func_00282948(void *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(float, int, int);
extern float func_00283CE0(int);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L20_0039F230(char *);

extern int D_L20_001AEDA8 __attribute__((sda));
extern int D_L20_001AED90 __attribute__((sda));
extern int D_L20_001AED94;
extern int D_L20_001AED98;
extern int D_L20_001AED9C;

void func_L20_0039ED78(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (func_00282948(state) != 0) {
        func_0029F338(arg0);
    } else {
        f32 x = *(f32 *)(state + 0x8);
        f32 r, s;
        int v, w, lo, hi;

        if (*(int *)(state + 0xC) != 0) {
            r = func_00283B98(x, (f32)D_L20_001AEDA8 * 0.0002908882452f);
            *(f32 *)(state + 0x8) = r;
            s = func_00283198(r);
            v = func_00283D38(s * 0.5f + 0.5f, D_L20_001AED90, D_L20_001AED94);
        } else {
            r = func_00283B98(x, (f32)D_L20_001AEDA8 * 0.0002908882452f);
            *(f32 *)(state + 0x8) = r;
            s = func_00283198(r);
            v = func_00283D38(s * s * 0.5f + 0.5f, D_L20_001AED98, D_L20_001AED9C);
        }
        w = func_00283D38(0.15f, *(int *)(state + 0x10) | *(int *)(state + 0x4), v);
        lo = w & 0xFFFFFF;
        hi = w & 0xFF000000;
        *(int *)(state + 0x10) = hi;
        *(int *)(state + 0x4) = lo;
        *(f32 *)(state + 0x14) = func_00283CE0(hi >> 24) * 0.00390625f;
        func_L00_002E6CF0(func_L20_0039F230, arg0);
    }
}

/* func_L20_003A0320 is in L20_003A0320-g8.c, where its independent
   address materializations use -mno-split-addresses. */

/* func_L20_003BFEB8 reads -0x7600($gp); its near miss is in
   nonmatching/levels/func_L20_003BFEB8.c and belongs in a -G8 unit
   of its own, built with -fno-schedule-insns2. */
INCLUDE_ASM("asm/levels", func_L20_003BFEB8);

/* func_L20_003C0048 is defined in L20_003C0048-g8.c. */

/* func_L20_00408D98 is defined in L20_00408D98-g8.c (its switch owns .rodata). */

INCLUDE_ASM("asm/levels", func_L20_00438F98);

/* func_L20_004395B0 reads three floats through $gp; its near miss is in
   nonmatching/levels/func_L20_004395B0.c and belongs in this -G8 unit. */
/* func_L20_004395B0 is defined in L20_004395B0-g8.c (it reads three floats through $gp and uses common.h qcopy, whose typedefs clash with this unit's). */
