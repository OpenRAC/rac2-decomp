#include "common.h"

INCLUDE_ASM("asm/levels", func_L12_0041E3E8);

s32 func_L12_0041E8E8(u8 *a0) {
    return *(u8 *)(a0 + 0x20) == 3;
}

extern int D_001A79F0 __attribute__((sda));
extern char D_0019B4A8[];
extern char D_00189EA0[];
extern void func_00282CF0(f32 *, const f32 *, const f32 *);
extern void func_002AFEB8(char *, char *, char *, char *, f32);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_002B0A68(void *, s32, void *, f32, f32, f32, f32, s32);

void func_L12_0041E8F8(u8 *a0) {
    u8 *self = a0;
    f32 buf[4];
    u16 f;

    func_00282CF0(buf, (f32 *)(self + 0x10), (f32 *)D_00189EA0);
    func_002AFEB8((char *)self, (char *)buf, (char *)buf, 0, 0.0f);
    func_00282F20(buf, buf, 0.10000000894069672f);
    func_002B0A68(self, 31, buf, 6.0f, 12.0f, 6.0f, 12.0f, 255);

    f = *(u16 *)(self + 0xB2);
    if (f & 1) {
        u8 *p = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *p;

        if (((c >> 4) & 7) != 7)
            *p = c + 0x10;
    } else {
        u8 *p = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *p;

        if ((c & 7) != 7)
            *p = c + 1;
    }
    func_002E5CF8(1, 0, self);
}

INCLUDE_ASM("asm/levels", func_L12_0041EA18);

/* func_L12_0041EDB8 is defined in L12_0041E3E8-split-g8.c (this unit keeps split addresses). */

/* func_L12_00420660 is defined in L12_0041E3E8-g8.c. */

/* func_L12_00420838 is defined in L12_00420838-flags-g8.c. */

INCLUDE_ASM("asm/levels", func_L12_00420950);

INCLUDE_ASM("asm/levels", func_L12_00420B78);

/* func_L12_00421110 is defined in L12_0041E3E8-g8.c. */

INCLUDE_ASM("asm/levels", func_L12_004212C0);

INCLUDE_ASM("asm/levels", func_L12_00424370);

typedef int L12_25070Quad __attribute__((mode(TI)));

extern s32 *D_L12_001FEAC0[];
extern s32 func_002761F8(void *from, void *to, s32 mode, void *self, s32 flags);

/* Picks the first point of the object's list (D_L12_001FEAC0, chosen by the state's +0x298)
   other than the current one (+0x2B0) that it can see: both ends are raised by 0.5, and a
   zero result from the sight test means clear. Returns that point's index, or the current
   one when none is clear. */
s32 func_L12_00425070(u8 *object)
{
    f32 from[4] __attribute__((aligned(16)));
    f32 to[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(object + 0x68);
    s32 *list = D_L12_001FEAC0[*(s32 *)(state + 0x298)];
    s32 i;

    qcopy(from, object + 0x10);
    from[2] += 0.5f;
    for (i = 0; i < list[0]; i++) {
        if (i == *(s32 *)(state + 0x2B0))
            continue;
        qcopy(to, (L12_25070Quad *)list + i + 1);
        to[2] += 0.5f;
        if (func_002761F8(from, to, 2, object, 0) == 0)
            return i;
    }
    return *(s32 *)(state + 0x2B0);
}

INCLUDE_ASM("asm/levels", func_L12_00425178);

extern s32 *D_L12_001FEAC0[];
extern char D_00189EA0[];
extern f32 func_00282C48(f32);
extern f32 func_00282E80(void *, void *);

void func_L12_00425348(u8 *a0) {
    u8 *state = *(u8 **)(a0 + 0x68);
    s32 i = *(s32 *)(state + 0x2B4) + 1;
    u32 *entry = D_L12_001FEAC0[*(s32 *)(state + 0x298)];

    while (i < *(s32 *)entry) {
        if (func_00282C48(*(f32 *)((u8 *)entry + (i * 16 + 0x18)) - *(f32 *)((u8 *)entry + 0x18)) < 2.0f) {
            if (func_00282E80(D_00189EA0, (u8 *)entry + (i * 16 + 0x10)) < 6.0f)
                *(s32 *)(state + 0x2B4) = i;
        }
        i++;
    }
}

extern int func_00282948(void *);
extern s32 func_002A7820(s32, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern s32 D_L12_001B20C0 __attribute__((sda));

extern u8 D_001395DB;
extern int func_002ACBC8(void *, int);
extern void func_L12_0031E1D0(u8 *, s32, s32);

void func_L12_004254A8(u8 *arg0) {
    u8 *s0 = arg0;
    s32 *v;

    if (*(u8 *)(s0 + 0x20) == 0) {
        v = *(s32 **)(s0 + 0x68);
        if (*v != -1) {
            if (func_002ACBC8(D_00189EA0, *v) != 0) {
                D_001395DB = 1;
                func_L12_0031E1D0(s0, 1, -1);
            }
        }
    }
}

INCLUDE_ASM("asm/levels", func_L12_004285A8);

INCLUDE_ASM("asm/levels", func_L12_004293A0);

INCLUDE_ASM("asm/levels", func_L12_00429610);

/* func_L12_00429868 is defined in L12_0041E3E8-g8.c. */
