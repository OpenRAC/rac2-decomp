#include "include_asm.h"
#include "common.h"

/* Quadword copies and clears, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

INCLUDE_ASM("asm/levels", func_L07_003F4578);

extern u8 D_L07_001B31AF __attribute__((sda));

void func_L07_0040FC50(void)
{
    u8 *p;
    s32 i;

    for (i = 15, p = &D_L07_001B31AF; i >= 0; i--) {
        *p = 0;
        p--;
    }
}

/* func_L07_003F4970 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_003F4B08 is defined in L07_003F4B08-copy.c. */

/* func_L07_003F4C18 is defined in L07_003F4C18-copy.c. */

INCLUDE_ASM("asm/levels", func_L07_003F4CC0);

INCLUDE_ASM("asm/levels", func_L07_003F59C0);

INCLUDE_ASM("asm/levels", func_L07_003F5B50);

/* func_L07_003F6328 is defined in L07_003F6328.c. */

extern void func_3109C8(u8 *a, s32 b, s32 c);

extern f32 func_2E49C8(f32 a, f32 b);

extern f32 func_2E5360(f32 a, f32 b);

extern f32 D_L07_00189E20[];

extern void func_L07_003F68F0(u8 *a0, f32 x);

void func_L07_003F6528(u8 *a0)
{
    u8 *s0;
    f32 r;

    func_3109C8(a0, 2, -1);
    s0 = *(u8 **)(a0 + 0x68);
    *(u8 *)(a0 + 0x7F) = 0;
    *(f32 *)(s0 + 0x20) = (f32)*(s16 *)(s0 + 0x24);
    r = func_2E5360(func_2E49C8(D_L07_00189E20[0x20] - *(f32 *)(a0 + 0x10),
                                D_L07_00189E20[0x21] - *(f32 *)(a0 + 0x14)),
                    *(f32 *)(s0 + 0x60));
    if (r > 0.0f) {
        *(f32 *)(s0 + 0x54) = -1.5707964f;
    } else {
        *(f32 *)(s0 + 0x54) = 1.5707964f;
    }
    func_L07_003F68F0(a0, 0.0f);
}

extern u16 *D_L07_001FAD60[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *D_L07_001B22DC[] __attribute__((sda));
extern s32 D_L07_001B22F8[] __attribute__((sda));

extern s32 func_002A77E0(s32 n);

extern s32 func_00282948(s32 *counter);

/* Picks at random one of the group's entities that are in state 1: counts them, draws an index
   below the count, then walks the list again stepping the index down (func_00282948) until it
   runs out. Returns 0 when there is none. */
u8 *func_L07_003F65E8(s32 group)
{
    u16 *p;
    u16 *q;
    u8 *e;
    s32 n = 0;
    s32 k;

    for (p = D_L07_001FAD60[group];
         (group & 0xFF) != 0xFF && group <= D_L07_001B22F8[0] && p != 0 &&
         ((s16)p[-1] >= 0 || p == D_L07_001FAD60[group]);
         p++) {
        e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 1)
            n++;
    }
    if (n == 0)
        return 0;
    k = func_002A77E0(n);
    for (q = D_L07_001FAD60[group];
         (group & 0xFF) != 0xFF && group <= D_L07_001B22F8[0] && q != 0 &&
         ((s16)q[-1] >= 0 || q == D_L07_001FAD60[group]);
         q++) {
        e = D_L07_001B22DC[0] + ((*q & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 1 && func_00282948(&k) != 0)
            return e;
    }
    return 0;
}

/* func_L07_003F67B8 is defined in L07_003F67B8-copy.c. */

/* func_L07_003F68F0 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_003F6960 is defined in L07_003F4578-g8.c. */

INCLUDE_ASM("asm/levels", func_L07_003F6C40);

/* func_L07_003F6CF0 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_003F6DC0 is defined in L07_003F6DC0-copy.c. */

INCLUDE_ASM("asm/levels", func_L07_003F7048);

/* An entity node: the flag word at 0x34, the counter at 0x98, two children. */
typedef struct SibNode SibNode;

struct SibNode {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    SibNode *f68;
    u8 rest68[0x98 - 0x6C];
    s32 f98;
    u8 rest9c[0x410 - 0x9C];
    SibNode *f410;
    SibNode *f414;
};

void func_L07_003F78F8(SibNode *a0)
{
    SibNode *p = a0->f68;

    a0->flags34 = (a0->flags34 | 0x41) & 0xEFFF;
    a0->f98 = 0;
    p->f410->flags34 |= 0x41;
    p->f410->flags34 &= 0xEFFF;
    p->f410->f98 = 0;
    p->f414->flags34 |= 0x41;
    p->f414->flags34 &= 0xEFFF;
    p->f414->f98 = 0;
}

INCLUDE_ASM("asm/levels", func_L07_003F7968);

u8 *func_L07_003F7BE0(u8 *a0)
{
    return *(u8 **)(*(u8 **)(a0 + 0x68) + 0x420);
}

INCLUDE_ASM("asm/levels", func_L07_003F7BF0);

extern void func_002A93B0(u8 *a);

extern void func_002A0F48(u8 *a);

extern void func_0029FC20(u8 *a, s32 b, void *c);

extern void func_00283678(u8 *a, void *b);

/* func_L07_003F8010 is defined in L07_003F8010-copy.c. */

INCLUDE_ASM("asm/levels", func_L07_003F80B8);

INCLUDE_ASM("asm/levels", func_L07_003F8430);

/* func_L07_003F8780 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

extern void func_00282CF0(u8 *a, u8 *b, u8 *c);

extern void func_002AFDD8(u8 *a, u8 *b, u8 *c, s32 d);

/* func_L07_003F8828 is defined in L07_003F8828-copy.c. */

extern void func_00283098(u8 *a, u8 *b, u8 *c);

extern void func_00282CC0(u8 *a, u8 *b, u8 *c);

/* func_L07_003F8898 is defined in L07_003F8898-copy.c. */


/* func_L07_003F8AB0 is defined in L07_003F4578-qcopy.c (this unit needs the grouped quadword copy). */

extern void func_L07_003F43E0(u8 *a, u8 *b, void *c, void *d, f32 e);


extern u8 *func_L07_003F6B88(u8 *a);

extern void func_L07_003F6C40(u8 *a, u8 *b, void *c, f32 d);

/* One 128-byte record, its float field read by the measured index. */
typedef struct {
    u8 pad38[0x38];
    f32 f38;
    u8 rest[128 - 0x3C];
} SibRec128;

extern SibRec128 *D_L07_001B23CC;


INCLUDE_ASM("asm/levels", func_L07_003F8D90);

extern void func_002A7470(u8 *a0, s32 a1, s32 a2, s32 a3);

void func_L07_003F9028(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u32 *)(p + 0x420) == 0) {
        if (*(u8 *)(a0 + 0x43) != 2) {
            func_002A7470(a0, 2, 0, 10);
        }
        return;
    }
    if (*(u8 *)(a0 + 0x43) != 8) {
        func_002A7470(a0, 8, 0, 10);
    }
}

void func_L07_003F9088(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u32 *)(p + 0x420) == 0) {
        if (*(u8 *)(a0 + 0x43) != 3) {
            func_002A7470(a0, 3, 0, 10);
        }
        return;
    }
    if (*(u8 *)(a0 + 0x43) != 9) {
        func_002A7470(a0, 9, 0, 10);
    }
}

extern u8 D_001A7BD0 __attribute__((sda));

extern void func_L01_003C91C8(u8 *a0);

void func_L07_003FF618(u8 *a0)
{
    if (D_001A7BD0 != 0) {
        *(u16 *)(a0 + 0x34) |= 0x2;
        return;
    }
    func_L01_003C91C8(a0);
}

INCLUDE_ASM("asm/levels", func_L07_004080E0);

extern void func_310D80(void *a, f32 b, f32 c);

extern f32 func_2E4280(f32 a);

extern f32 func_310B30(f32 a, f32 b);

extern void func_31AFD8(void *a, void *b, f32 c, f32 d, f32 e);

extern void func_335848(void *a, void *b, s32 c);

/* The two shared level floats; `sda` gives the retail's `lui %hi ; swc1 %lo($at)` form. */
extern f32 D_L07_001AA698 __attribute__((sda));

extern f32 D_L07_001B3198 __attribute__((sda));

/* Runs the object's own 200 steps: each step advances the shared record's third
   float, then the three angles are computed and handed to the shared passes. */
void func_L07_00408338(u8 *a0)
{
    f32 v[4];
    f32 buf[4];
    s32 i;
    f32 f14;
    f32 f20;
    f32 f21;

    D_L07_001B3198 = D_L07_001AA698;
    D_L07_001AA698 = 0.99f;
    for (i = 0xC7; i >= 0; i--) {
        func_310D80(buf, 1.0f / 60.0f, 0.23333335f);
        buf[2] = func_2E4280(buf[2]) + 1.0f / 12.0f;
        f21 = func_310B30(-5.0f, 5.0f);
        f20 = func_310B30(-5.0f, 5.0f);
        f14 = func_310B30(10.0f, 25.0f);
        func_31AFD8(a0, v, f21, f20, f14);
        func_335848(v, buf, 0x1E0);
    }
}

INCLUDE_ASM("asm/levels", func_L07_0040E198);

INCLUDE_ASM("asm/levels", func_L07_0040E980);

INCLUDE_ASM("asm/levels", func_L07_0040EC08);


extern void func_338D68(void *a, s32 b, void *c, void *d, s32 e, f32 f);

extern f32 func_2E4508(void *a, void *b);

void func_L07_0040EFC8(s32 *a0, f32 *a1, f32 a, f32 b)
{
    f32 p2[4];
    f32 p1[4];
    f32 tmp[4];
    f32 d = a - b;
    f32 s;

    if (d < 0.0f)
        d = d + (f32)a0[0];
    s = a + b;
    if ((f32)a0[0] < s)
        s = s - (f32)a0[0];
    func_338D68(a0, 1, p1, tmp, 0, d);
    func_338D68(a0, 1, p2, tmp, 0, s);
    a1[2] = func_2E49C8(p1[0] - p2[0], p1[1] - p2[1]);
    a1[1] = -func_2E49C8(func_2E4508(p2, p1), p1[2] - p2[2]);
}

INCLUDE_ASM("asm/levels", func_L07_0040F0D0);

/* The object's state record up to its three group words (-1 means none). Indexing the array
   member is the spelling that gives retail's address arithmetic (the +0x94 base as a sum of its
   own, the group word read again inside the walk); a cast sum or a pointer variable does not. */
typedef struct {
    u8 pad[0x94];
    s32 groups[3];
} GroupState;

/* Walks the id list of each of the object's three groups, stopping at the first id with no
   entity; the walk itself does nothing. */
void func_L07_0040F598(u8 *a0)
{
    GroupState *state = *(GroupState **)(a0 + 0x68);
    s32 i;
    u16 *p;
    u8 *e;

    for (i = 0; i < 3; i++) {
        if (state->groups[i] == -1)
            continue;
        for (p = D_L07_001FAD60[state->groups[i]];
             (state->groups[i] & 0xFF) != 0xFF && state->groups[i] <= D_L07_001B22F8[0] && p != 0 &&
             ((s16)p[-1] >= 0 || p == D_L07_001FAD60[state->groups[i]]);
             p++) {
            e = D_L07_001B22DC[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
        }
    }
}

/* func_L07_0040F6B8 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */

/* func_L07_0040F760 is defined in L07_003F4578-g8.c (this unit has no $gp access for it). */


INCLUDE_ASM("asm/levels", func_L07_0040F8F8);

INCLUDE_ASM("asm/levels", func_L07_0040FA90);

INCLUDE_ASM("asm/levels", func_L07_0040FC88);

INCLUDE_ASM("asm/levels", func_L07_00410588);

extern void func_002833F0(u8 *a, u8 *b);

extern void func_L00_00323958(u8 *a, u8 *b);

void func_L07_004106B8(u8 *a0)
{
    u8 *s1 = *(u8 **)(a0 + 0x68);

    func_002833F0(a0 + 0xC0, a0 + 0xF0);
    func_L00_00323958(a0, s1 + 0x1B0);
}

INCLUDE_ASM("asm/levels", func_L07_00410700);

/* func_L07_00410930 is defined in L07_003F4578-g8.c (it takes the address of $gp data). */

INCLUDE_ASM("asm/levels", func_L07_00410C50);
