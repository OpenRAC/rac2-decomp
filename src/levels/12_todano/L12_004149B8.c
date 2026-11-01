#include "common.h"

typedef struct {
    char pad0[0x110];
    s32 f110;             /* 0x110 */
    char pad114[0x10c];
    u32 f220;             /* 0x220 */
} Tab698;

typedef struct {
    char pad0[0x20];
    u8 f20;               /* 0x20 */
    char pad21[0x0f];
    u8 f30;               /* 0x30 */
    u16 f32;              /* 0x32 */
    char pad34[0xc4];
    f32 fF8;              /* 0xF8 */
} Obj390;

typedef struct {
    char pad00[0x20];
    u8 f20;                 /* 0x20 */
    char pad21[0x31 - 0x21];
    u8 f31;                 /* 0x31 */
    char pad32[0x34 - 0x32];
    u16 f34;                /* 0x34 */
    char pad36[0xAA - 0x36];
    s16 fAA;                /* 0xAA */
} Sub114B;

typedef struct {
    char pad00[0x2F0];
    Sub114B *f2F0[2];       /* 0x2F0 */
    Sub114B *f2F8;          /* 0x2F8 */
} Moby49B8;

typedef struct {
    char pad00[0x31];
    u8 f31;                 /* 0x31 */
    char pad32[0x68 - 0x32];
    Moby49B8 *f68;          /* 0x68 */
} Ent49B8;

extern int func_L02_002EF388(void *, void *, void *, void *, int);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, void *, int);

extern s32 *D_L12_001FEAC0[];

extern f32 func_002F2950(f32, f32);

extern void func_002A0F48(void *);

extern void func_00282F20(f32 *, void *, f32);


extern void func_L12_0041BED8(u8 *);

extern void func_326F10(void *, void *, s32, s32);

extern void func_L09_003F7788(void *, void *);

/* A pointer table of level-12 data, reached absolutely (out of the $gp window). */

/* func_L12_0041BDF8 is matched in L12_0041BDF8-rc2.c. */


/* Returns 1 as soon as one of the two bound sub-objects carries a live state word. */
s32 func_L12_0041BE60(u8 *a0)
{
    u8 *a1 = a0;
    u8 *s0;
    u8 **p;
    s32 i;

    if (a1 == 0)
        return 0;
    if (*(s16 *)(a1 + 0xAA) != 0xFAE)
        return 0;
    s0 = *(u8 **)(a1 + 0x68);
    func_L12_0041BED8(a1);
    p = (u8 **)(s0 + 8);
    for (i = 0; i < 2; i++, p++) {
        if (*p != 0) {
            if (*(s32 *)(*p + 0x98) != 0)
                return 1;
        }
    }
    return 0;
}

/* --- func_L12_0041A698 (52 B) ------------------------------------------------------ */

s32 func_L12_0041A698(u8 *self)
{
    Tab698 *n = *(Tab698 **)(self + 0x68);

    return (n->f220 ^ (u32)(*D_L12_001FEAC0[n->f110] - 1)) < 1;
}

/* --- func_L12_00416390 (88 B) ------------------------------------------------------ */

f32 func_L12_00416390(Obj390 *self)
{
    if (self->f20 == 0) {
        self->f20 = 1;
        self->f30 = 0x20;
        self->f32 = 0x20;
    }
    return self->fF8 = func_002F2950(self->fF8, 0.017453294f);
}

/* --- func_L12_0041BDA8 (68 B) ------------------------------------------------------ */

void func_L12_0041BDA8(u8 *a0)
{
    s32 i;
    u8 **p;

    if (a0 == 0)
        return;
    if (*(s16 *)(a0 + 0xAA) != 0xFAE)
        return;
    p = (u8 **)(*(u8 **)(a0 + 0x68) + 8);
    for (i = 1; i >= 0; i--, p++) {
        if (*p != 0)
            *(u32 *)(*p + 0x98) = 0;
    }
}

/* func_L12_0041BDF8 (104 B) and func_L12_0041BE60 (120 B): best attempt reaches every
   instruction but one — the retail keeps the incoming pointer in $a1 (a copy of $a0 at
   entry) and mine folds it onto $a0.  Left as markers; both attempts are in the wave's
   drafts/ directory. */

/* ---------------------------------------------------------------------------------- */

/* the two bound sub-objects of the moby this driver walks */

/* Walks the moby's two sub-objects, re-arms each one's parent link and releases it. */
void func_L12_004149B8(Ent49B8 *a0)
{
    Moby49B8 *moby = a0->f68;
    Sub114B *head = moby->f2F8;
    s32 i;

    if (head == 0)
        return;
    if (head->fAA != 0x114B)
        return;
    if (head->f20 == 0xFE)
        return;
    if (head->f20 == 0xFD)
        return;
    for (i = 0; i < 2; i++) {
        if (moby->f2F0[i] != 0) {
            func_326F10(moby->f2F8, moby->f2F0[i], i, (i ^ 1) ? 0 : 6);
            if (a0->f31 != 0) {
                moby->f2F0[i]->f34 = moby->f2F0[i]->f34 & 0xFFFE;
                moby->f2F0[i]->f31 = 1;
            } else {
                moby->f2F0[i]->f34 = moby->f2F0[i]->f34 | 1;
                moby->f2F0[i]->f31 = 0;
            }
            func_L09_003F7788(a0, moby->f2F0[i]);
        }
    }
}


/* func_L12_00414C60 is in L12_00414C60-g8.c. */

/* func_L12_00414EB8 is in L12_004149B8-effects-g8.c. */

INCLUDE_ASM("asm/levels", func_L12_004163E8);

INCLUDE_ASM("asm/levels", func_L12_00417690);

/* func_L12_00417CA8 is in L12_00417CA8-g16.c. */

/* func_L12_00418418 is defined in L12_00418418-g8.c. */

/* func_L12_00418D20 is in L12_00418D20-g16.c. */

/* func_L12_004190A8 is in L12_004190A8-g8.c. */

/* func_L12_00419D68 is matched in its own unit, L12_00419D68.c. */

void func_L12_0041A5F8(u8 *self)
{
    u8 *dst = self + 0x10;
    u8 *n = *(u8 **)(self + 0x68);
    void *m;

    qcopy(dst, n + 0x210);
    *(f32 *)(self + 0xF8) = *(f32 *)(n + 0x21C);
    *(u32 *)(n + 0x224) = 0;
    *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) & 0xFFBE) | 0x1000;
    m = *(void **)(self + 0x24);
    *(u32 *)(self + 0x98) = *(u32 *)((u8 *)m + 0x10);
    func_L02_002EF388(self, dst, self + 0xF0, 0, 0);
    func_002A7750(self, 2, -1);
    if (*(u8 *)(self + 0x43) != 8)
        func_002A7470(self, 8, 0, 1);
}

/* func_L12_0041A790 is matched in L12_0041A790-g8.c. */

/* func_L12_0041AEF0 is in L12_0041AEF0-g8.c. */

/* func_L12_0041B2A8 is in L12_0041B2A8-g8.c. */

/* --- func_L12_0041BED8 (176 B) ----------------------------------------------------- */

void func_L12_0041BED8(u8 *self)
{
    u8 *s1 = *(u8 **)(self + 0x68);
    u8 **s0 = (u8 **)(s1 + 8);
    s32 i;

    for (i = 1; i >= 0; i--, s0++) {
        if (*s0 != 0) {
            f32 v = (*(f32 *)((u8 *)s0 + 0x2C) + *(f32 *)(s1 + 0x40) * 0.5f)
                    * 0.16666667f;
            f32 t;

            func_00282F20((f32 *)(*s0 + 0xD0), *s0 + 0xD0, v);
            func_002A0F48(*s0);
            t = *(f32 *)(*(u8 **)(*s0 + 0x24) + 0x3C);
            *(f32 *)(*s0 + 0xC) = t + t;
        }
    }
}


/* func_L12_0041CF10 is in L12_0041CF10-g8.c. */

/* func_L12_0041D3B0 is in L12_0041D3B0-g8.c. */

/* func_L12_0041D808 is in L12_0041D808-g8.c. */

/* func_L12_0041DDA8 is in L12_0041DDA8-g8.c. */
