#include "common.h"

extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_324168(s32 a0, s32 a1);
extern void func_30D710(s32 a0, s32 a1);
extern void func_32C010();
extern void func_32C328(char *a0, char *a1, s32 a2);
extern void *func_31DD78(char *a0, s32 a1, s32 a2);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern void func_311758(void *a0);
extern void func_L03_003D11E0(char *a0);
extern void func_31B920(char *a0, s32 a1, s32 a2);
extern f32  func_31BAE8(f32 a0, f32 a1);
extern f32  func_2F0000(f32 a0, f32 a1);
extern char D_L03_00188660[];
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern void func_2EEFE0(char *a0, char *a1, void *a2);
extern u8  *D_L03_001B2A1C;
extern f32  D_00189E20_19;
extern u8   D_001395BF;
extern void func_2BEE78(char *a0, char *a1, s32 a2, s32 a3);
extern void func_2B8300(s32 a0, s32 a1, char *a2);
extern void func_43B870(s32 a0);
extern void func_32F140(s32 a0, s32 a1);
extern char D_00189E20_11[];
extern u8   D_001395C0;
extern u8   D_001A7AFA;
extern u8   D_001A7B32;
extern u8   D_001A7AFB;
extern u8   D_001A7B33;
extern u8   D_001A7AFC;
extern u8   D_001A7B34;
extern void func_2B8510(s32 a0);
extern void func_313378(s32 a0);
extern void func_359FD0(char *a0, char *a1);
extern void func_30D710(s32 a0, s32 a1);
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ char position[0x10];
    /* 0x20 */ unsigned char state;
    /* 0x21 */ char pad21[0xB];
    /* 0x2C */ float scale;
    /* 0x30 */ unsigned char alpha;
    /* 0x31 */ char pad31;
    /* 0x32 */ unsigned short alpha2;
    /* 0x34 */ char pad34[0x34];
    /* 0x68 */ void *vars;
    /* 0x6C */ char pad6C[0x4C];
    /* 0xB8 */ int owner;
} L03SpawnObject;

typedef struct {
    /* 0x00 */ char a[0x10];
    /* 0x10 */ char b[0x10];
    /* 0x20 */ char pad20[0x44];
    /* 0x64 */ float v[3];
    /* 0x70 */ int kind;
    /* 0x74 */ char pad74;
    /* 0x75 */ unsigned char c;
    /* 0x76 */ unsigned char d;
    /* 0x77 */ unsigned char e;
    /* 0x78 */ unsigned char e2;
} L03SpawnState;




/* func_L03_003C6208 is defined in L03_003C6208-g8.c. */

INCLUDE_ASM("asm/levels", func_L03_003C6A28);

/* func_L03_003C6E50 is defined in L03_003C6E50-g8.c. */

INCLUDE_ASM("asm/levels", func_L03_003C7018);

/* func_L03_003C72A8 is defined in L03_003C72A8-g8.c. */

void func_L03_003C7A40(char *a0)
{
    char *v1 = *(char **)(a0 + 0x68);

    *(u16 *)(v1 + 0x106) = 0;
    *(s32 *)(v1 + 0x100) = 0;
    *(u16 *)(a0 + 0x34) |= 0x400;
    func_002A7750(a0, 2, -1);
    *(s32 *)(a0 + 0x9C) = 0;
}

void func_L03_003C7A88(char *a0)
{
    char *v0 = *(char **)(a0 + 0x68);

    *(u16 *)(v0 + 0x106) = 1;
    *(s32 *)(a0 + 0x9C) = 1;
}

/* func_L03_003C7AA0 is matched in its own unit, src/levels/03_endako/L03_003C7AA0-qcopy.c (-frac2-qcopy). */

INCLUDE_ASM("asm/levels", func_L03_003C7AC0);

/* func_L03_003C7E20 is matched in its own unit, src/levels/03_endako/L03_003C7E20-g8.c (-G8). */

/* Builds the object's mode record: the private block gets the mode at +0xA0,
   the mode record is made from the caller's +0x10 and the object is released.
   The mode is kept in $v0 across the call, so the store lands in the call's
   delay slot. */
void func_L03_003C85F8(char *a0, s32 a1)
{
    char buf[0x10];
    char *s1 = *(char **)(a0 + 0x68);

    *(s32 *)(s1 + 0xA0) = a1;
    func_312898(a1, 2, buf);
    func_2EEFE0(s1 + 0x90, a0 + 0x10, buf);
    func_31B920(a0, 2, -1);
}

/* func_L03_003C8660 is matched in its own unit, src/levels/03_endako/L03_003C8660-qcopy.c (-frac2-qcopy). */

/* func_L03_003C8698 is defined in L03_003C8698.c. */

/* func_L03_003CA938 lives in the -G8 sibling L03_00399230-g8.c. */


/* func_L03_003CAD78 is defined in L03_003CAD78-g8.c. */

/* func_L03_003CB398 is defined in L03_003CB398-g8.c. */

/* func_L03_003CBC40 is defined in L03_003CBC40-g8.c. */

/* Picks the actor's next motion slot: case 0 draws a random turn rate, case 1
   re-checks the 0x70-stride table entry before refreshing the aim. */
void func_L03_003CBD70(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        func_31B920(s0, 1, -1);
        *(f32 *)(s1 + 4) = func_31BAE8(60.0f, 90.0f) * 0.000290888245f;
        *(s32 *)(s1 + 8) = -1;
        break;
    case 1: {
        s32 v = *(s32 *)s1;

        if (v != 0) {
            char *p = D_L03_00188660 + *(s32 *)(s1 + 8) * 0x70;

            if (*(char **)(p + 0x88) != s0 || *(u8 *)(p + 0x74) == 0)
                *(s32 *)(s1 + 8) = func_360A80(0, 4, s0);
        }
        *(f32 *)(s0 + 0xF8) = func_2F0000(*(f32 *)(s0 + 0xF8),
            *(f32 *)(s1 + 4));
        break;
    }
    }
}

/* func_L03_003CBE58 lives in the -G8 sibling L03_00399230-g8.c (it reads $gp-relative floats). */

/* func_L03_003CF0C0 is defined in L03_003CF0C0-g8.c. */

s32 func_L03_003CF7B8(u8 *a0)
{
    return (u8)(a0[0x20] - 2) < 3;
}

/* func_L03_003CF7C8 is in L03_003CF7C8.c. */

void func_L03_003CFB30(char *a0)
{
    char *moby = *(char **)(a0 + 0x68);

    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(moby + 0x5C) |= 1;
        func_32C010(a0, moby + 0x60, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        func_32C328(a0, moby + 0x60, 0);
        break;
    }
}

/* func_L03_003D0300 is defined in L03_003D0300-g8.c. */

void func_L03_003D1100(char *a0)
{
    char *a3 = *(char **)(a0 + 0x68);

    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(s32 *)(a3 + 0x5C) |= 8;
        func_002A7750(a0, 1, -1);
        break;
    case 1: {
        char *s1 = (char *)func_31DD78(a0, 0x10000, 0);
        s32 v;

        if (func_32AB10(a0) != 0
            || (s1 != 0 && (v = *(s32 *)(s1 + 0x20)) != 0
                && *(s16 *)(v + 0xAA) == 0xB1B)) {
            func_L03_003D11E0(a0);
            func_360A80(0, 0, a0);
            func_311758(a0);
        } else {
            *(u8 *)(a0 + 0xA8) = 0xFF;
        }
        break;
    }
    }
}

/* func_L03_003D11E0 is in L03_003D11E0-g8.c. */

/* func_L03_003D1548 is in L03_003D1548-g8.c. */

/* func_L03_003D19C8 is in L03_003D19C8-g8.c. */


void func_L03_003D1FB0(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);

    func_324168(*(s32 *)(s0 + 0x18), *(s32 *)(s0 + 0x1C));
    func_30D710(0, -1);
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x34) |= 0x41;
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x34) &= ~0x1000;
    *(s32 *)(*(s32 *)(s0 + 0x2C) + 0x98) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x96) = 0;
}

/* func_L03_003D2018 is defined in L03_003D2018.c. */

extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));

void func_L03_003D20F8(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    char *s2;
    void *p;

    func_2B8510(0);
    s2 = D_00189E20_11;
    *(u16 *)(s2 + 0x24FC) = 0;
    func_313378(*(u8 *)(s0 + 0xB0));
    D_001395C0 = 1;
    /* Resident bytes shared by all programs, written at their constant addresses
       (retail's lui $at,0x1A; sb form), as in 0033CB18.c. */
    *(u8 *)0x001A7B32 = 1;
    *(u8 *)0x001A7AFB = 1;
    *(u8 *)0x001A7B33 = 1;
    *(u8 *)0x001A7AFC = 1;
    *(u8 *)0x001A7B34 = 1;
    *(u8 *)0x001A7AFA = 1;
    func_2BEE78(s0 + 0x10, s0 + 0xF0, 0, 1);
    p = *(void **)(s1 + 0x2C);
    if (p != 0) {
        func_311758(p);
    }
    func_311758(D_L03_001B2A1C_tbl[0] + (*(s32 *)s1 << 8));
    *(s32 *)(s0 + 0x78) = 0x80468CDC;
    func_32F140(*(s32 *)(s1 + 0x24), -1);
    func_359FD0(s2 + 0x80, s2 + 0x90);
    func_30D710(0, -1);
}

/* func_L03_003D22C8 is defined in L03_00399230-g8.c. */

/* func_L03_003D2518 is defined in L03_003D2518.c. */


/* Spawns object class 0xB1B owned by `owner` and fills its 0x10E state record. */
extern void *func_0029EFD0(int);
extern void func_002A0F48(void *);

/* Spawns a kind-0xB1B object owned by OWNER at POSITION: opaque, a 0.015 rate, its state
   taking the two vectors, the three floats (in reverse order), a 0x10E word and the
   three bytes (the last twice). Returns the object, or 0. */
u8 *func_L03_003E18D8(char *owner, void *position, void *first, void *second,
                        u8 a, u8 b, u8 c, f32 x, f32 y, f32 z)
{
    u8 *object;
    u8 *state;

    object = func_0029EFD0(0xB1B);
    if (object != 0) {
        qcopy(object + 0x10, position);
        object[0x30] = *(u16 *)(object + 0x32) = 0xFF;
        *(f32 *)(object + 0x2C) = 0.015f;
        *(char **)(object + 0xB8) = owner;
        object[0x20] = 0;
        state = *(u8 **)(object + 0x68);
        qcopy(state, first);
        qcopy(state + 0x10, second);
        *(f32 *)(state + 0x64) = z;
        state[0x75] = a;
        state[0x76] = b;
        state[0x77] = c;
        state[0x78] = c;
        *(f32 *)(state + 0x68) = y;
        *(f32 *)(state + 0x6C) = x;
        *(s32 *)(state + 0x70) = 0x10E;
        func_002A0F48(object);
    }
    return object;
}

INCLUDE_ASM("asm/levels", func_L03_003E1C88);
