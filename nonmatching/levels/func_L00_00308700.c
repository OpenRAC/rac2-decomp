/* 5 November 2026: 288/288, 0/27, only the swap block differs (pointer in v0, quads v1/a0; retail quads v0/v1, pointer a0). Fixes: miss block `Cache *c = &D; unsigned char **dp = &c->e[0].s.data; int off = best << 4; func_00297550(*(unsigned char **)((char *)dp + off), key, D.base, c->info); e0 = c->e; e = (Ent *)((char *)e0 + off); e->s.key = key;` (dp base keeps cse from merging the sums; new post-call pseudo e has no calls crossed, so sched1 keeps the add after the jal; a separate e0 avoids a flow (use) that took an issue slot), and `extern int D_001B18D8[] __attribute__((sda));` read as [0] for the tied lui a0/lw a0 tail. Swap: other-pointer qty (sll tied into addu) ties the two TI temps on local-alloc priority and wins on qty number; four swap wordings (pointer/two temps/base[i]/inline helper/struct copy) tie. */
/* 5 November 2026 (on the 288/288 dp/e0/sda form from the main-tree note): local-alloc QTY_CMP_PRI (floor_log2(refs)*refs*size/(death-birth), units of half insns) gives the swap qtys: two TI temps 1*2*2/4 = 1.0, pointer tied with the sll 2*5/10 = 1.0 (tie, wins on qty number), base hi+lo 12/14 = 0.857. Retail order needs temps > pointer > base, e.g. pointer life 11 units. `i <<= 4; other = base + i` (pointer untied) gives temps v0/v1 but base outranks the pointer (base a0, pointer a1) and moves i a2->a1 in the scan loop (28 rows); base hoisted above `if (i != 0)` is 71 rows. */
/* 5 November 2026: retained body is 276/288, 0/27. Retail keeps la D (s0) and best<<4 (s1) apart across the call (5 saves, %hi in s4; the loop nop is alignment from the extra save). Local Cache* c + off, char* p += off, c reassigned, do-while(0) around call or call+store, natural form with -frac2-gcse-unsplit-edges or -mno-split-addresses: cse always merges into one D+off (s0). */
/* 4 November 2026 current-RAC1 source trials; retained, not linked.
 * Three real RAC1 scan/swap/decode-phase trials give 272 or 276 bytes against 288, 0/27 USA
 * placements. The retained 276-byte owner-view form uses the complete cache representation for
 * age offsets and the measured entry array for data; it avoids stepping beyond a scalar field as
 * an int array. It preserves the miss return and selected-first swap without the donor's dummy
 * increment/decrement. Keeping separate table-base/index values across decode remains unresolved.
 * Older 296-byte measurements below are history.
 */
/* v2133 (Opus 5.5): still the closest draft (296/288, 0/27). Retail keeps
 * la D (s0, set in the miss block) and best<<4 (s1) across the call and adds
 * them base-first afterwards, so cse never knew the base was a constant.
 * Natural forms merge the pre- and post-call &D+best*16 (272). A top-level
 * Cache *c used on one side of the call gives unmerged sums and 5 saved regs
 * at 284, but the base is the prologue la kept live through the loop and the
 * post-call add order is swapped. Reassigning c after the call gives 272/276.
 * The swap quads sit in v1/a0 with the pointer in v0 (retail: v0/v1, a0), and
 * the tail's %hi goes to v0 (retail shares a0).
 */
/* GPT-6.1 Sol high, v0801: 296/288 bytes, 0/27 USA v1.01 places.
 * Default -O2 -G0 -ffunction-sections. Compared with the prior 272-byte draft,
 * the age-origin view plus grouping the data-word offset recovers the five
 * saved registers and the complete scan loop. The byte offset now survives
 * the call, but cc1 builds D+0x38 separately, costing two extra instructions.
 * The quadword swap still has pointer/value registers permuted. Grouped byte,
 * unsigned-address and word-index forms give identical 296-byte code.
 * Next: keep the original D base while preventing full selected-pointer CSE;
 * then resolve the swap's local allocator roles. No linked build was run.
 * Declarations below.
 */
#include "common.h"

typedef int Q128 __attribute__((mode(TI)));

typedef union {
    struct {
        int key;
        int age;
        unsigned char *data;
        int pad;
    } s;
    Q128 q;
} Ent_308700;

typedef struct {
    unsigned char *base;
    short *info;
    char pad8[0x28 - 8];
    int active;
    int pad2C;
    Ent_308700 e[8];
} Cache_308700;

extern Cache_308700 D_L00_001C93A0;
extern int D_001B18D8;
extern void func_00297550(unsigned char *, int, unsigned char *, short *);

int func_L00_00308700(int key)
{
    int found;
    int best;
    int i;

    if (D_L00_001C93A0.active == 0)
        return 0;
    found = 0;
    best = 0;
    for (i = 0; i < 8; ++i) {
        if (D_L00_001C93A0.e[i].s.key == key)
            break;
        if (D_L00_001C93A0.e[i].s.age < *(int *)((unsigned char *)&D_L00_001C93A0 + 0x34 + best * 16))
            best = i;
    }
    if (i == 8) {
        do {
            func_00297550(D_L00_001C93A0.e[best].s.data, key, D_L00_001C93A0.base, D_L00_001C93A0.info);
        } while (0);
        D_L00_001C93A0.e[best].s.key = key;
        i = best;
        found = 1;
    }
    if (i != 0) {
        Ent_308700 *base = D_L00_001C93A0.e;
        Ent_308700 *other = base + i;
        Q128 tmp = other->q;
        other->q = base->q;
        base->q = tmp;
    }
    D_L00_001C93A0.e[0].s.age = D_001B18D8;
    return found;
}
