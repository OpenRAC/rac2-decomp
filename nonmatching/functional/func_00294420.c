/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_00294420 - 456 bytes. Tier: Opus 5.5 xhigh (task v1752), 31 October 2026.
 *
 * Best check.py result: 468/456 bytes, 0/28 places. Every instruction equals retail
 * except for three extra nops before the second back-branch at retail +0x140 (and the
 * two branch offsets they shift), in the default profile (-O2 -G0 -ffunction-sections).
 * Allocation, scheduling, the loops and the movz chains are all solved by this wording.
 *
 * What differs: retail's `while (i == a || i == b) i++` loop closes with two back-branches
 * to one label: 5 nops, beql, addiu, beql, addiu. The retail assembler counts words, so
 * the second branch is already 9 words from its label and stays unpadded. The compiler's
 * post-delay-slot imitation, mips_r5900_pad_loops, does not add its own nops to its
 * counter: the second branch counts 4 words and gets 3 nops. The label's address fixes
 * its count, so no wording changes this; only a counted insn that emits nothing could
 * (an empty asm, which the rules forbid).
 *
 * Unblock: a transformer adding the nops the pass emits to its counter `n`, so that it
 * counts words as the assembler does; then requalify with tools/build.py all --strict.
 * This is the only short two-back-branch loop in the 28 retail programs, by a scan of every
 * catalogued function (other padded loops, such as nests, could change; the build shows it).
 * Ruled out: the sdk profile. Its pass forgets the label after a branch, but it uses
 * 16-byte save slots and a sibling call, 448/456 bytes with a different frame.
 *
 * Declarations: the file's Table1_00294420, Table2_00294420 and Fee2b87d1_ names, as in 00291758.c.
 */
#include "include_asm.h"

struct Slot_00294420 { int w; int rest[4]; };
struct Table1_00294420 { char pad[19264]; struct Slot_00294420 slots[48]; };
struct Table2_00294420 { char pad[52]; int slots[4]; };
extern struct Table1_00294420 Fee2b87d1_D_0014B540;
extern struct Table2_00294420 Fee2b87d1_D_00152CD0;
extern int func_00294630(int);
extern void func_00294398(int, int);

typedef struct { char pad[20]; int value; char rest[200]; } CacheRecord;
extern CacheRecord D_00239BA0[];
extern unsigned char D_00139568[];
typedef struct { char pad[0x22C8]; int cur; char pad2[0x22E4 - 0x22CC]; int primary; } CacheHero;
extern CacheHero D_00189E20;
extern short D_001A63AC;
extern int D_001A7398 __attribute__((sda));
extern int D_001A7A04 __attribute__((sda));

void func_00294420(int value)
{
    int a, b, i, sa, sb;

    if (func_00294630(value))
        return;
    if (D_001A63AC)
        return;
    i = 0;
    {
        CacheHero *hero = &D_00189E20;
        int p = hero->primary;
        int q = D_001A7398;
        CacheRecord *rec = &D_00239BA0[D_00139568[p]];
        CacheRecord *rec2 = &D_00239BA0[D_00139568[q]];

        a = rec->value;
        b = rec2->value;
    }
    if (b == a) {
        CacheRecord *rec = &D_00239BA0[D_00139568[D_001A7A04]];

        b = rec->value;
    }
    sb = -1;
    if (a == value)
        a = -1;
    if (b == value)
        b = -1;
    sa = -1;
    for (; i < 3; i++) {
        struct Table2_00294420 *cache = &Fee2b87d1_D_00152CD0;
        int v = Fee2b87d1_D_0014B540.slots[cache->slots[i]].w;

        if (a == v)
            sa = i;
        if (b == v)
            sb = i;
    }
    for (i = 0; i == sa || i == sb; i++)
        ;
    {
        CacheHero *hero = &D_00189E20;
        int cur = hero->cur;

        if (cur) {
            struct Table2_00294420 *cache = &Fee2b87d1_D_00152CD0;
            int k = cache->slots[i];

            if (k != -1) {
                struct Table1_00294420 *toc = &Fee2b87d1_D_0014B540;
                CacheRecord *rec = &D_00239BA0[D_00139568[cur]];

                if (rec->value == toc->slots[k].w)
                    hero->cur = 0;
            }
        }
    }
    func_00294398(value, i);
}
