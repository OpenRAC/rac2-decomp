/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, 29 October 2026: retained near miss, not linked.
 * Pinned -O2 -G8 -ffunction-sections, USA: 1044/1044 bytes, 0/1 places.
 * Best check: first mismatch +0x78; ten instructions differ after relocations:
 * eight case-0 packed-counter address registers and two effect argument moves.
 * MACRO_ADDR on the canonical actor-table pointer fixes the absolute load and
 * its complete burst-call schedule. The measured flags-record layout fixes
 * the flags address addition; Actor indexing fixes the rising child access.
 * A shifted integer offset plus the table address fixes cleanup allocation.
 * Block-local IDs fix terminal halfword registers. Splitting the case-0
 * pointer into a scalar fixes that case but swaps all four terminal pointer/
 * byte register pairs (22 residual instructions, first +0x24C). Named packed
 * values and integer terminal addresses tie that variant. FP-first and mixed
 * typed interleavings preserve the helper ABI but tie the final two setup
 * moves. Fifteen checker calls, including one rejected syntax trial, plus
 * one allocator diagnostic. No US2/PAL or linked check claimed for this body.
 * Reopen with original packed-counter pointer/value lifetimes or argument
 * evaluation evidence. Required declarations follow; use a dedicated -G8 unit.
 */
#include "common.h"

extern s32 func_L12_0041E8E8(u8 *);
extern void func_L12_0041E8F8(u8 *);
extern s32 func_00282948(s32 *);
extern void func_002A7750(u8 *, u8, s32);
extern void func_0029F338(void *);
extern u8 *func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32,
                          f32, f32, s32, s32, s32, void *);
extern void func_00282F20(f32 *, void *, f32);
extern void func_002B0A68(f32, f32, f32, f32, char *, s32, f32 *, u8);

/* level 12 data reached through $gp (small-data) */
extern int D_001A79F0 __attribute__((sda));
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C;
#define actorTable D_L12_001B2E9C
extern int D_L12_001B18F0 __attribute__((sda));

/* level 12 data reached absolutely: out of the $gp window */
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern u8 D_0019B4A8[];

typedef struct Actor {
    char pad00[0x18];
    f32 f18;              /* 0x18 */
    char pad1c[0x04];
    u8 f20;               /* 0x20 */
    char pad21[0x13];
    u16 f34;              /* 0x34 */
    char pad36[0x32];
    void *f68;            /* 0x68 */
    char pad6c[0x2c];
    u32 f98;              /* 0x98 */
    char pad9c[0x16];
    u16 fB2;              /* 0xB2 */
    char padB4[0x0c];
    char fC0[0x40];       /* 0xC0 */
} Actor;

typedef struct Node {
    s32 f0;               /* 0x00 */
    f32 f4;               /* 0x04 */
    f32 f8;               /* 0x08 */
    s32 fC;               /* 0x0C */
} Node;

void func_L12_004163E8(Actor *self)
{
    u8 *p;
    Node *s1 = self->f68;

    switch (self->f20) {

    case 0: {
        u16 f;

        self->f20 = 1;
        s1->f8 = self->f18;
        f = self->fB2;
        if (D_L12_0021EDF0.flags[(s16)f] != 0)
            goto Destroy;
        p = ((s16)f >> 1) + (D_001A79F0 << 10) + D_0019B4A8;
        {
            s32 bits = *p;
            if (f & 1) {
                if (((bits >> 4) & 7) != 0)
                    goto Destroy;
                return;
            } else {
                if ((bits & 7) == 0)
                    return;
                goto Destroy;
            }
        }

    }
    case 1:
        if (s1->f0 != -1) {
            if (func_L12_0041E8E8(actorTable + (s1->f0 << 8)) == 0)
                return;
        }
        self->f20 = 2;
        s1->fC = 0x50;
        return;

    case 4: {
        s32 index;
        s1->f4 = s1->f4 + 0.0013888889f;
        self->f18 = self->f18 + s1->f4;
        index = s1->f0;
        if (index != -1) {
            u8 *base = actorTable;
            ((Actor *)base)[index].f18 += s1->f4;
        }
        if (s1->f8 + 8.0f < self->f18)
            self->f20 = 5;
        return;

    }
    case 2:
        if (func_00282948(&s1->fC) != 0)
            return;
        func_002A7750((u8 *)self, 3, -1);
        s1->fC = D_L12_001B18F0;
        return;

    case 3: {
        u16 f;

        if (func_00282948(&s1->fC) != 0) {
        {
            u8 *t = (u8 *)D_L12_001B2E9C + (s1->f0 << 8);
            f32 local[4];

            func_0032C700(t + 0x10, 1, 0xE, 0xA, 0xF, 0xA, 0x14, 1,
                          2.0f, 20.0f, 1, 1, 0, 0);
            self->f98 = 0;
            self->f34 = (self->f34 | 0x41) & 0xEFFF;
            func_L12_0041E8F8(t);
            func_00282F20(local, self->fC0, -0.10000000894069672f);
            func_002B0A68(3.0f, 6.0f, 3.0f, 6.0f, (char *)self, 0x3F, local, 0xFF);
            {
                s32 index = s1->f0;
                u8 *base = actorTable;
                if (index != -1) {
                    Actor *child;
                    index <<= 8;
                    index += (s32)base;
                    child = (Actor *)index;
                    child->f34 &= 0xEFFF;
                    func_0029F338(base + (s1->f0 << 8));
                }
            }
        }
        f = self->fB2;
        if (f & 1) {
            p = ((s16)f >> 1) + (D_001A79F0 << 10) + D_0019B4A8;
            if (((*p >> 4) & 7) != 7)
                *p += 0x10;
        } else {
            p = ((s16)f >> 1) + (D_001A79F0 << 10) + D_0019B4A8;
            if ((*p & 7) != 7)
                *p += 1;
        }
Destroy:
        func_0029F338(self);
        } else if (s1->fC == D_L12_001B18F0 / 2) {
            if (s1->f0 != -1)
                ((Actor *)actorTable)[s1->f0].f20 = 4;
        }
        return;

    }
    case 5: {
        u16 f;

        f = self->fB2;
        if (f & 1) {
            p = ((s16)f >> 1) + (D_001A79F0 << 10) + D_0019B4A8;
            if (((*p >> 4) & 7) != 7)
                *p += 0x10;
        } else {
            p = ((s16)f >> 1) + (D_001A79F0 << 10) + D_0019B4A8;
            if ((*p & 7) != 7)
                *p += 1;
        }
        func_0029F338(self);
        return;
    }
    }

}
