/* 6 November 2026, round 10: best compliant form (no dead test) is 744/752 bytes, 0/8 USA,
 * 81 differing words by aligned diff; listing below. Same profile as round 9 (-fno-gcse).
 * Each of the four 203.0f roundings is `t = scale * k + half; do { y = t; } while (0);`
 * (the func_L02_003FE768 idiom), and a 45+50-run hill-climb ordered the constants.
 * Why $s1 stays out: in the 752 form, $s1 holds `active` (1) for the helper's compares;
 * the empty conditionals survive to reload (flow1 deletes only the dead `scaled = 1.0f`)
 * and jump2 deletes them after allocation. That same branch is also the block boundary that
 * keeps id a pseudo in $a0 (retail's early `daddu $a0,$v0`) and puts the call arguments after
 * each rounding. Post-reload, only jump2 removes real uses (reload_cse_simplify_set never
 * turns a register into a constant; noop-set deletion needs $s1 already set), so a $s1 save
 * with no use needs an empty or identical-arm conditional. No compliant shape found.
 * Left (compliant): no $s1 save (obj in $s1, frame offsets), id combined into `a0 = v0`
 * (late daddu), k/zero in f21/f22 (retail f22/f21), argument order, 23.0f roundings.
 * No gain: groups around the lookups or the whole rounding (95-98), a group inside the helper
 * (756 bytes), groups on the 23.0f/373.0f roundings (756, alignment nops), `text` reused for id,
 * a field pointer `obj + 0x20` set first, declaration orders.
 */
/* Round 10 compliant listing (744/752):

static __inline__ int menu_coord(float scale, float value, float half)
{
    return (int)(scale * value + half);
}

void func_L02_003C43F0(char *obj) {
    char *text;
    int state;
    char *id;
    int y, entry;
    float one, zero, half, k, t;

    half = 0.5f;
    entry = 0x8710;
    zero = 0.0f;
    id = func_00336D50(D_L02_001A904C + entry, 0x70);
    k = 203.0f;
    t = D_L02_001B3E04 * k + half;
    do { y = t; } while (0);
    one = 1.0f;
    func_00300A00(id, 0x60442D00, 258.0f, (float)y, one, one, zero);
    id = func_00336D50(D_L02_001A904C + entry, 0x6F);
    t = D_L02_001B3E04 * k + half;
    do { y = t; } while (0);
    func_00300A00(id, 0x60442D00, 258.0f, (float)y, one, one, zero);
    id = func_00336D50(D_L02_001A904C + entry, 0x71);
    t = D_L02_001B3E04 * k + half;
    do { y = t; } while (0);
    func_00300A00(id, 0x55F0C070, 258.0f, (float)y, one, one, zero);
    id = func_00336D50(D_L02_001A904C + entry, 0x72);
    t = D_L02_001B3E04 * k + half;
    do { y = t; } while (0);
    func_00300A00(id, 0x55F0C070, 258.0f, (float)y, one, one, zero);
    func_002FC560(0x47, 0x5360BUL);
    state = *(unsigned char *)(obj + 0x20);
    if (state == 7) {
        text = func_00288FB8(0x2F5C);
        func_0027FBD8(254, menu_coord(D_L02_001B3E04, 23.0f, half), 0x88FFFFFF, text, -1);
    } else if (state != 8 && state != 5) {
        text = func_00288FB8(0x2F5B);
        func_0027FBD8(262, menu_coord(D_L02_001B3E04, 23.0f, half), 0x88FFFFFF, text, -1);
    }
    text = func_00288FB8(0x2F5A);
    func_0027FBD8(254, menu_coord(D_L02_001B3E04, 373.0f, 0.5f), 0x88FFFFFF, text, -1);
}

*/
/* 6 November 2026, Codex (stopped at its usage limit): without the inadmissible dead-test helpers the best compliant form is 744/752 bytes, 0/8; it lacks retail's unused $s1 save/restore, and rounding and argument scheduling differ. Typed argument interleavings and constant-initialisation orders did not help. */
/* 6 November 2026, round 9: best body below (752/752, 0/8 USA, ~9 words, was ~19).
 * Same profile, plus -fno-gcse (as round 4 used):
 *   -O2 -G8 -fno-expensive-optimizations -ffunction-sections -fno-builtin -fno-gcse
 * New: the two 23.0f roundings use menu_coord2, whose dead test reads `scaled` in its
 * second block. That makes the scale/product chain a global pseudo, so local-alloc gives
 * 23.0 $f0 first and the chain $f1, as retail. Both 23.0f roundings now match.
 * Left:
 *  - fourth draw: retail has mov.s $f14,$f20 first and mov.s $f15,$f14 in the delay
 *    slot. reload_cse makes f15 = f14 only for a constant 1.0 source when it knows
 *    f20 = 1.0, but the helper labels clear its table. A copy `s = one` is folded by
 *    cse/cse2 (a do/while(0) group around it does not survive cse2 and adds a nop);
 *    `s = one` before the helper gives s = $f14 but the copy lands in the first block.
 *  - 373.0f rounding: retail loads 373 before the scale (sched2 tie on insn order).
 *    Scale not as the first helper parameter gives that order but swaps $f0/$f2.
 * No gain: no-helper draws with do/while(0) groups (~100 words), 16 parameter orders
 * for the 373.0f helper, a 60-run hill-climb over declarations and setup order.
 */
/* 6 November 2026, round 4: (752/752, 0/8 USA, ~19 words, was ~22).
 * Same profile as round 3. New: the helper takes the scale as its first parameter
 * (menu_coord(D_L02_001B3E04, value, half, active)); this fixes the 373.0f rounding's
 * FP registers. Left: the 23.0f roundings (retail 23 in f0, scale and product in f1),
 * and the fourth draw's f14/f15 (sched1 puts f15 = one first because `one` dies there;
 * retail keeps f14 first and reload makes f15 = f14). No change from: a second helper
 * for the 23.0f calls, `k = 23.0f` locals (worse), one/zero order, split mul/add,
 * expensive optimizations on (frame 0x50).
 * Also no gain: a separate `sy` local for f15 (copy or 1.0f, both worse), and a 150-run
 * hill-climb over the constant-assignment order.
 */
/* Near miss (opus-1, v1659): 744/752 bytes, 0/8 USA v1.01 places.
 * Profile: its own unit (e.g. L02_003C43F0-menu-g8.c) with
 *   -O2 -G8 -fno-expensive-optimizations -ffunction-sections -fno-builtin,
 * the profile of the matched sibling widget draws (src/game/002CDD88-g8.c, 002CFDA8-g8.c).
 * What this recovers: frame 0x40, s0 = 0x8710, the absolute macro loads of the registry
 * pointer and scale, and retail's FP allocation (f22 = 203, f23 = 0.5, f20 = 1.0,
 * f21 = 0.0) with 258.0 reloaded into $f12 before each call: without expensive
 * optimizations cse keeps the literal argument constants, so 1.0 and 0.0 are cached
 * only because they are locals, as in the siblings' `zero`.
 * What still differs:
 *  - retail saves $s1 and never uses it (obj is in $s2); here obj takes $s1 and the
 *    function is two words short (docs/MATCHING-BLOCKERS.md, "A register saved and never
 *    used"; func_00326A10 is the same family).
 *  - retail sets every call's constant arguments after the rounding chain
 *    (lwc1/mul/add/cvt/mfc1 v1/mtc1/cvt), as if a block boundary followed each
 *    (int)(scale * k + 0.5f); here both schedulers move them into the chain's stalls.
 *    A do { y = ...; } while (0) around each rounding, as a diagnostic only, gives that
 *    order and $v1 for the fix result (756 bytes); an inline rounding helper ties this
 *    source. -fno-schedule-insns does not help (sched2 still fills the stalls).
 * Callees and data are named by their catalogue/USA v1.01 level 02 addresses; the
 * registry lookup is the boot's func_00336D50 copy, the draws func_00300A00 and
 * func_0027FBD8.
 */
#include "common.h"

extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_002FC560(int, unsigned long);
extern char *func_00288FB8(int);
extern void func_0027FBD8(int, int, u64, char *, int);
extern char *D_L02_001A904C;
extern float D_L02_001B3E04;

extern int D_L02_001B3E00;

static __inline__ int menu_coord(float scale, float value, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L02_001B3E00 == active)
        scaled = 1.0f;
    return result;
}

static __inline__ int menu_coord2(float scale, float value, float half)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && scaled != 0.0f)
        scaled = 1.0f;
    return result;
}

void func_L02_003C43F0(char *obj) {
    char *text;
    int state;
    char *id;
    int y, on, entry;
    float one, zero, half, k;

    entry = 0x8710;
    k = 203.0f;
    half = 0.5f;
    on = 1;
    id = func_00336D50(D_L02_001A904C + entry, 0x70);
    y = menu_coord(D_L02_001B3E04, k, half, on);
    one = 1.0f;
    zero = 0.0f;
    func_00300A00(id, 0x60442D00, 258.0f, (float)y, one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x6F), 0x60442D00, 258.0f,
                  (float)menu_coord(D_L02_001B3E04, k, half, on), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x71), 0x55F0C070, 258.0f,
                  (float)menu_coord(D_L02_001B3E04, k, half, on), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x72), 0x55F0C070, 258.0f,
                  (float)menu_coord(D_L02_001B3E04, k, half, on), one, one, zero);
    func_002FC560(0x47, 0x5360BUL);
    state = *(unsigned char *)(obj + 0x20);
    if (state == 7) {
        text = func_00288FB8(0x2F5C);
        func_0027FBD8(254, menu_coord2(D_L02_001B3E04, 23.0f, half), 0x88FFFFFF, text, -1);
    } else if (state != 8 && state != 5) {
        text = func_00288FB8(0x2F5B);
        func_0027FBD8(262, menu_coord2(D_L02_001B3E04, 23.0f, half), 0x88FFFFFF, text, -1);
    }
    text = func_00288FB8(0x2F5A);
    func_0027FBD8(254, menu_coord(D_L02_001B3E04, 373.0f, 0.5f, 1), 0x88FFFFFF, text, -1);
}
