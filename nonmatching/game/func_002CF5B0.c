/* Closer B, 2026-11-01: 576/576, 10 words: declare status at function scope and use it for cost. That
 * gives retail's slot copy and 0x5A in a1. Left: base and status swapped (v1/a0, including the two early
 * status words at +0x60/+0x64), and item in v0 instead of a0 at +0x1D8/+0x1E4.
 * Why: base is single-block, so local-alloc takes v1 before global sees status. Retail's base must
 * lose v1 to status, so it is a global (live across blocks) or v1 is busy there. Its copy to s0 is
 * in beq's slot and s0 is read on both paths. Next: what makes base used in a second block.
 * local-alloc skips a pseudo with two deaths too. A local t reread at the retest gives 580 bytes.
 */
/*
 * v1665 (Claude Opus 5.5, xhigh, 30 October 2026): 576/576 bytes, 0/28 USA v1.01 places.
 * Profile: -O2 -G32 -Wa,-G32 -ffunction-sections; -O2 -G8 with or without
 * -fno-expensive-optimizations gives the same bytes. Build it as its own unit.
 *
 * Solved here: the buy test. Retail's re-test of cost != 0x5A survives because the source re-reads
 * the entry: thread_jumps runs before cse1, so with one `cost` pseudo on every test it threads the
 * first jump and cse folds the re-test away. Re-reading through a value-returning accessor keeps
 * the test, and gcse merges the loads. Computing the table address per site also produces retail's
 * PRE copy of the base into $s0. `(unsigned char)item` on an int keeps retail's andi; unsigned
 * char locals drop it (572 bytes).
 *
 * Still different, 12 words, register choice and the resulting order only:
 * - retail has the table base in $a0, 0x5A in $a1 and the copy in beq's delay slot. Here the base
 *   is local-allocated to $v1, which is free because it dies at the addu before cost is born; that
 *   lets cost share $v1, so 0x5A moves to $a0 and the copy cannot sink past the lbu.
 * - retail loads item into $a0; here it gets $v0.
 * Both need something that keeps the pseudo out of a free lower register, such as a conflict or a
 * preference from another allocno. Sharing the early `status` variable for cost moves the copy into
 * the slot and 0x5A into $a1, with base and cost swapped ($v1/$a0) and an extra andi (580 bytes).
 * Ties: -g, -fno-sched-interblock, -fno-sched-spec, and cost local or re-read at all three tests.
 * Worse: dropping MACRO_ADDR from the table hoists a saved register (596 bytes).
 */
#include "common.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;
typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;
typedef struct { unsigned char f0; unsigned char f1; unsigned char item; unsigned char cost; } ShopEntry;

extern SelectionCallback D_001F2840;
extern CallbackMenuState D_00138180;
extern int D_001AB9EC __attribute__((sda));
extern ShopEntry D_001ABCD0[] MACRO_ADDR;
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern unsigned char D_001A7A40[] MACRO_ADDR;
extern short D_001A7A10[4];
extern int func_002B0E90(void);
extern int func_002E5E58(int, unsigned int, void *);
extern void func_002923C0(int);

static __inline__ ShopEntry *shop_entry(int index)
{
    return &D_001ABCD0[index];
}

static __inline__ int shop_cost(int index)
{
    return shop_entry(index)->cost;
}

static __inline__ int shop_item(int index)
{
    return shop_entry(index)->item;
}

int func_002CF5B0(void)
{
    int result = 0;
    int status;
    int limit = func_002B0E90();
    int flags = D_00138180.flags;

    if (flags & 0x10) {
        int value;
        D_001AB9EC = 0;
        value = *(int *)(D_001F2840.source + 0xE0);
        if (value != 0)
            D_001F2840.value = value;
        else if (D_001F2840.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        D_001AB9EC = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            func_002E5E58(3, 0, 0);
            do {
                ShopEntry *table;
                if (--D_001AB9EC < 0)
                    D_001AB9EC = 11;
                table = D_001ABCD0;
                if (table[D_001AB9EC].cost != 100)
                    break;
            } while (1);
        } else if (flags & 0x4000) {
            int cur;
            ShopEntry *table;
            func_002E5E58(3, 0, 0);
            cur = D_001AB9EC;
            table = D_001ABCD0;
            do {
                if (++cur >= 12)
                    cur = 0;
            } while (table[cur].cost == 100);
            D_001AB9EC = cur;
        }
        if (D_00138180.flags & 0x40) {
            status = shop_cost(D_001AB9EC);
            if ((status != 0x5A && status <= limit)
                || (shop_cost(D_001AB9EC) == 0x5A && D_001A7A60[0] != 0)) {
                unsigned char *slot;
                func_002E5E58(4, 0, 0);
                slot = &D_001A7A40[shop_entry(D_001AB9EC)->item];
                if (*slot)
                    *slot = 0;
                else
                    *slot = 1;
                {
                    int item = shop_item(D_001AB9EC);
                    if (item == 9 || item == 10 || (unsigned char)item == 2 || (unsigned char)item == 11)
                        func_002923C0(D_001A7A10[4]);
                }
            } else
                func_002E5E58(5, 0, 0);
        }
    }
    return result;
}
