#include "include_asm.h"

typedef signed int s32;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;
extern s32 func_00342228(u8 *a0, s32 a1);
extern f32 func_0030FE40(f32 x, f32 y);
extern f32 func_0030F3A0(f32 x);
extern f32 func_0030F3B8(f32 x);
extern u8 D_L04_00254E10[];
typedef struct RankState {
    u8 pad0[0xA2];
    u8 rank;
    u8 count;
    u8 padA4[0x11C - 0xA4];
    f32 progress;
    s32 f120;
    s32 f124;
    u8 pad128[0x160 - 0x128];
    s32 lap;
    u8 pad164[0x1E4 - 0x164];
    s32 slots[21];
    u8 pad238[0x244 - 0x238];
    s32 f244;
} RankState;
typedef struct RankObject {
    u8 pad0[0x20];
    u8 active;
    u8 pad21[0x68 - 0x21];
    RankState *state;
    u8 pad6c[0x100 - 0x6c];
} RankObject;
extern RankObject *D_L04_001B24DC __attribute__((sda));
extern f32 func_L04_00410788(RankObject *, RankState *, s32 *, s32 *, s32, s32);
/* func_L04_00415E28 is a near miss: nonmatching/levels/func_L04_00415E28.c */

/* func_L04_00415EA8 is a near miss: nonmatching/levels/func_L04_00415EA8.c */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
typedef struct {
    f32 start[4];
    u8 pad10[0x80 - 0x10];
    f32 origin[4];
    u8 pad90[0x100 - 0x90];
    f32 dir[4];
    f32 *from;
    f32 *to;
    s16 h118;
    u8 pad11A[0x128 - 0x11A];
    s16 h128;
    u8 pad12A[0x138 - 0x12A];
    s32 i138;
    s32 i13C;
    u32 color;
    s32 active;
    u8 *owner;
    u8 pad14C[0x150 - 0x14C];
} L04_5EE8Bolt;
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283698(void *, void *);

void func_PAL_L04_0041A660(u8 *owner, f32 *pos, f32 *to, f32 *from)
{
    f32 d[4] __attribute__((aligned(16)));
    f32 m[16] __attribute__((aligned(16)));
    L04_5EE8Bolt *b;
    s32 i;

    for (i = 0; i < 140; i++) {
        b = &((L04_5EE8Bolt *)D_L04_00254E10)[i];
        if (b->active == 0) {
            b->active = 1;
            func_00282CC0(d, from, pos);
            func_00282CC0(b->start, d, to);
            func_00283698(m, owner + 0xC0);
            func_002830C0(b->dir, pos, m);
            qcopy(b->origin, pos);
            b->to = to;
            b->i138 = 1;
            b->from = from;
            b->i13C = 0x19;
            b->owner = owner;
            b->color = 0x80858585;
            b->h128 = 0;
            b->h118 = 0;
            return;
        }
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0041A790);


INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0041AF28);

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0041B5C0);

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0041B850);

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0041BC68);


INCLUDE_ASM("asm/pal/levels", func_PAL_L04_0041D788);
