/* 31 October 2026: exact (28 of 28 places) with `float scale = 329.0f;` held in a local AND
 * the func_0027FAA8 call wrapped in a non-empty `do { ... } while (0);`, whose loop notes keep
 * the argument setup after func_00288FB8 in retail's order and put 329.0f in $f2. Either change
 * alone gives 0/28. Not landed: that wrapper is the open maintainer question in
 * docs/MATCHING-BLOCKERS.md ("A non-empty do { ... } while (0) as a block barrier"), the same
 * shape as func_0033A520's rounding of D_001B23A4 * 300. If the wrapper is accepted, this
 * function lands with it.
 */
/* Maintainer ABI correction, 29 October 2026: the qualified EE compiler
 * measures sizeof(long) == sizeof(long long) == 8 and sizeof(void *) == 4.
 * The PR #365 trials narrowing the style argument to u32 used a false
 * interface. Their sizes are not a valid ABI-preserving improvement.
 * Restore the earlier wide-argument candidate; no new match is claimed.
 */
/* func_002D53F0 (140 bytes, 28 places), M16: 140/140 under -O2 -G0 in its own unit.
 * D_001B23A4 declared MACRO_ADDR gives retail's one absolute `lwc1 $f0,D_001B23A4` through
 * $at at retail's position (this replaces the old -mno-split-addresses note); the callees
 * take their real prototypes (func_0027FAA8 (int, int, u64, u8 *, int) as defined in
 * 0027F980.c, func_00288FB8 returning the text pointer). Left (9 lines, registers and
 * order only): 329.0f in $f1 / 0.5f in $f2 where retail has $f2 / $f1, and the a1/a3/a2
 * setup order after func_00288FB8. Constant locals, a split product, the text as a local,
 * the sibling units' -fno-expensive-optimizations -fno-builtin profile, -G8 and sda forms
 * leave both. In the permuter queue. */
#include "common.h"

extern float D_001B23A4 MACRO_ADDR;
extern void func_0027C540(long);
extern void func_0029C530(void);
extern unsigned char *func_00288FB8(int);
extern void func_0027C660(void);
extern int func_0027FAA8(int, int, u64, unsigned char *, int);

int func_002D53F0(void)
{
    int y;

    func_0027C540(0);
    func_0029C530();
    y = (int)(D_001B23A4 * 329.0f + 0.5f);
    func_0027FAA8(0x1A6, y, 0x80F0F0F0ULL, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
