/* 5 November 2026: pointer-local (124 bytes), early-return (128) and guarded-loop (144) spellings are all further from 132 than the base form below. */
/* 2 November 2026: the signed 32-bit index/result form remains 132/132 bytes, 0/28 US placements. An unsigned index changes the retail signed bound test; a 64-bit result expands to 140 bytes without preserving the required zero copy. Neither is retained. The entry zero-copy/CSE constraint remains; do not repeat width probes without new compiler evidence. */
/*
 * func_002F7320 (boot 0x002F7320, 132 bytes, 28 places).
 * Tier: control flow solved, allocation open.
 * Best check.py: 132/132 bytes, 0/28 places, 18 of 33 rows differ; every
 * differing row is a register number, plus one zero-copy instruction.
 *
 * Solved here (do not rework):
 * - The plain indexed while is the original shape.  jump1 duplicates the exit
 *   test before the loop, cse1 folds `i < 56` there, thread_jumps sends the
 *   first test straight past the found-block test, and strength reduction
 *   makes T[i] the two-step base (la; += 16) with the increment first in the
 *   loop, which reorg steals for the bnel slot.
 *
 * Still differs: retail has `daddu a3,t1,zero` (i = result) where this has
 * `daddu a3,zero,zero`.  With that copy alive, result = 0 has a dependent, so
 * sched1 puts it ahead of the argument copies, result conflicts with hard a0,
 * and allocation becomes retail's: a0 value, a3 i, t0 base, t1 result,
 * t2 field, t3 reach.  A probe with an opaque (forbidden) asm zero confirmed
 * those registers.
 *
 * Why the copy is hard: cse folds it (const 0 costs less than a pseudo), and
 * reload_cse will not swap a cheap CONST_INT for a register.  Yet retail's
 * first load and base have no shift, so `i` must be known to be 0 by cse2.
 * The copy therefore needs either i = literal-T[0] code plus a label that
 * flushes cse through cse2, or a zero cse cannot see that combine folds.
 *
 * Declarations needed: Func_002F7320Row and ref_L00_002F7320_00, below.
 */
typedef struct {
    int key;
    int values[3];
} Func_002F7320Row;

extern Func_002F7320Row ref_L00_002F7320_00[];

int func_002F7320(int value, int key, int field)
{
    int result = 0;
    int i = result;

    while (ref_L00_002F7320_00[i].key != 0 && i < 56 && key != ref_L00_002F7320_00[i].key)
        i++;
    if (ref_L00_002F7320_00[i].key != 0)
        result = value == ref_L00_002F7320_00[i].values[field];
    return result;
}
