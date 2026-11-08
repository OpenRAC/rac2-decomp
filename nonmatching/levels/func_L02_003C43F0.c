/* 8 November 2026 (Sonnet round, prototype audit, lesson 47): func_0027FBD8 is declared void but src/game/0027F980.c returns int. Corrected: 3 rows before and after, no change. Other callees differ only in char */
/* 8 November 2026 (Sonnet round 2, s13, ~15 check.py runs + 25 min permuter -j2, no gain): retained C re-measured 3 words. New: all three 373 calls written out per path (no shared tail) 62 words; two-step `scaled = scale*value; scaled += half` in the helper 3; draw-4 rounding after `s = one` 11; first draw through its own float `u` or inline 5. Permuter from the retained C: no score below base 140. */
/* 8 November 2026 (Sonnet round): re-measured 3 words. New: a dead `scaled != zero` in draw 4's rounding via menu_coord2 keeps k/zero in f22/f21 but gives 11 words (s0/s1 swap, v0/v1) and the f15/f16 swap stays; zero live into label_y (8th ref) keeps k/zero but the f15/f16 swap also stays, so zero liveness is not the cause. Permuter 25 min -j2: best 35 passes zero as the 0.5 half (semantic change), inadmissible. */
/* 8 November 2026 (compiler matrix, scratch only): retained C compiled with 10 EE cc1 builds at the same flags (-frac2-* dropped for non-local builds), our as: local 991111; decomp.me 2.9-ee-991111a, 991111-01, 991111b (= SN SDK 2.4's 991111); Sony 2.96-ee-001003-1; SN 2.95.2 v2.73a/v2.74, 2.95.3 v1.07/v1.14/v1.36 (no 990721 build available). No build gives retail's +0x1A8..+0x1B4 order: SN 2.95.x and 2.96-ee keep our tie choice (752-764 bytes); stock 991111 is 816 bytes and different. Not a compiler-build difference. */
/* 8 November 2026 (round 12, ~14 check.py runs, retained C and flags): no semantics-preserving way found; retained C stays 752/752, 3 words.
 * Retail's state-7 branch has no 0.0 argument (254, y, 0x88FFFFFF, text, -1) and its add.s uses f23 (half), so the only
 * invisible place for `zero` there is menu_coord2's dead compare: `scaled != none` with zero passed (same value as 0.0f).
 * Effect (lreg dump): zero (base 5 refs / 140 insns, priority .071) becomes 7 refs / 206 (.068, both branches) or 6 / 178
 * (.067, state 7 only, else literal); k is 5 / 144 (.069), so global-alloc swaps k/zero into f21/f22: 13 words. With zero
 * live there, draw 4 becomes f15, ori, jal, f16 (ori right, f15/f16 swapped). zero needs len < ~201 or an 8th ref;
 * `scaled != none && result != 0` reaches 202 but changes code (78 words). No change: dead `scaled = none` (deleted
 * before counting), zero/k set order (sched1 moves the sets), helper parameter order. */
/* 8 November 2026 (decomp-permuter round, 35 min, -j4, randomisation, retained C and flags): base score 140 (3 words); best 25 fixes the fourth draw's f16/ori/f15 order but only by passing 0.0 (the zero local, reused for 0.5 before the first menu_coord) as the state-7 23.0f text's half: a semantic change (add.s f23, not f21). With that text's half restored, back to the same 3 words; a second candidate (30) also changed values. Hint: keeping zero's register live into the state-7 branch gives retail's order. */
/* 8 November 2026, region donor (v101/m8h): func_L05_00421B98 (L05_00421B98-g8.c:87, same family L10/L15/L25) +0x304 compiles retail's draw-4 shape (f14=f20, f16, ori, jal, f15=f14) via HUD_SPRITE(..., fade, fade, 0.0f) with y inline. Tried here: y inline + (one, one, zero) / (s, s, zero) with s set before the fetch / block-local sprite and x: 5 words (f16, ori, jal right, but f15=f20 early and f14 in the slot); s after the fetch: 11; (one, s) / (s, one) inline: 764 bytes; (s, one) with y precomputed: 5; (one, one) precomputed: 5. Retained C stays at 3. */
/* 8 November 2026 (round 10, ~42 check.py runs, master compiler): retained C still 752/752, 3 words (+0x1A8/+0x1AC/+0x1B4).
 * sched1 dump (-dS -fsched-verbose): in draw 4's block the f15 move (f15 = s) carries s's REG_DEAD, so its register
 * weight is 0 and it ties the f16 move (zero dies, weight 0); the lower LUID (f15) wins, and the ori ends in the delay
 * slot. Retail's order (f16, ori, f15) needs the f15 move to keep weight 1 (source live on, or a constant), yet still be
 * `mov.s $f15,$f14`: reload_cse_simplify_set rewrites only constant/memory sources, and only while f20 = 1.0 is known
 * (no CODE_LABEL since its set), so a live source can never come out as f14.
 * Shown: menu_coord2 comparing `scaled != s` (or `one`) keeps s/one live: order becomes f16, ori, f15 as retail, but cse
 * folds the `s = one` copy, so f14/f15 both read $f20 and the f14 move goes late (7 words).
 * No gain: technique (a) plain fourth rounding (22), plus a colour do-while(0) (58), group around the rounding (69);
 * args (one, 1.0f) (60-83), `s = 1.0f` or a fresh `u` copy with (u, 1.0f) (60-65: lui/mtc1, f20 unknown after labels);
 * (s, s, 0.0f) (6); draws 2-4 plain y + colour groups + draw-4 (one, 1.0f) (80: k/zero f21/f22 swap, late daddu a0). */
/* 8 November 2026 (round 9, rank_for_schedule): base 752/752, 3 differing words (retained C, recorded flags). rank_for_schedule is identical in GCC 2.95/2.95.2/2.95.3 and EE 991111/991111b; SN 2.95.2 v2.73a makes the same tie choice where its output is comparable. Env probes (sched1/sched2/both): reg weight swapped/clamped/dropped/after class/positive-or-negative only, class dropped/reversed, dependent count reversed/dropped/data-only/clamped, LUID reversed, INSN_UID ties, no birthing boost: none improves any of the nine cluster targets; forced on, every variant changes 6-7124 of 8761 matched units. Hypothesis falsified. */
/* 6 November 2026, Codex follow-up to round 14 (accepted label_y precedent):
 * Best retained source: 752/752 bytes, 0/8 USA v1.01 places, THREE real words.
 * Same own-unit profile: -O2 -G8 -fno-expensive-optimizations
 * -ffunction-sections -fno-builtin -fno-gcse. No linked build run.
 * New improvement: retain the owner-approved menu_coord/menu_coord2 helpers for
 * the four sprite draws and 23.0f text; use the exact accepted label_y helper
 * (L15_00431590-g8.c) with the text handle for the final 373.0f text. This fixes
 * all four 373/0.5 register differences without disturbing earlier allocation.
 * Remaining +0x1A8/+0x1AC/+0x1B4: fourth draw moves f15=f14 before f16=zero,
 * putting the color ori in the delay slot; retail delays f15=f14 instead.
 * The exact label_y at every site also gives 752/752 and seven real words:
 * it fixes 373 but changes the first two integer conversions v1 -> a1 (four
 * words), retaining the fourth draw's three scheduling differences.
 * New controls: actual conversion/draw/lookup statement groups, including
 * -malign-loops=2; separate result locals, reuse for state/FP coordinates,
 * equivalent fourth-draw constant arguments, and initial constant orders.
 * None improved three. The accepted screen_coord with zero offset at these
 * sites worsens the body; no real nonzero mode offset is evidenced here.
 * With the all-label_y source, -g, -fno-regmove, -fno-caller-saves,
 * -fno-sched-interblock, -fno-sched-spec and -frac2-hazard-labels tie seven;
 * disabling either scheduling pass worsens it. Label-free fourth rounding
 * and label_y only on draw four worsen the hybrid. No invalid hill-climb,
 * volatile, asm, symbol aliases, artificial locals or addresses retained.
 * Next useful input: a real fourth-draw source lifetime that keeps its f15
 * argument from carrying REG_DEAD, without losing its f14 canonical copy.
 */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 752/752, 7 words with the owner-allowed helper (373/0.5 FPR swap and the fourth draw's delay slot). */
/* 7 November 2026, round 14 (dead-test helper allowed by owner ruling, master precedent:
 * src/game/002D2188-g8.c): best body below, 752/752, 0/8 USA, 7 real words (was ~9).
 * Unit L02_003C43F0-menu-g8.c, same flags as round 9 (-fno-gcse).
 * New:
 *  - 373.0f call passes `on` (not 1): the li 1 leaves that block and sched2 now loads 373
 *    before the scale, as retail. Left: 373 in $f1, 0.5 in $f2 (retail $f2/$f1); local-alloc
 *    ties the two 2-ref qtys and the older (373) wins. No change from 6 helper parameter
 *    orders, value*scale, half + scale*value, menu_coord2 (31 words, unit-wide effects),
 *    the call written inside the arguments (48).
 *  - fourth draw: `s = one;` after the rounding, args (s, s), and s also used earlier
 *    (`s = (float)y;` for the first draw). cse make_regs_eqv keeps s canonical only when s
 *    lives outside the cse block, so the copy survives in the last block: retail's
 *    mov.s $f14,$f20 ... mov.s $f15,$f14 now appear. Left: sched2 puts f15 before f16/ori,
 *    so the delay slot gets the ori. Cause: REG_DEAD of s is on the f15 move (last use),
 *    sched1 prefers it and its LUID order carries to sched2. Retail's order needs f15 to
 *    carry no death, i.e. f15's source was the constant 1.0f, rewritten to $f14 by
 *    reload_cse_simplify_set. That works only with no CODE_LABEL between `one = 1.0f`
 *    (draw 1) and draw 4, so retail's draws 2-4 had no dead-test helper.
 *  - Tested that hybrid: draw 1 helper, draws 2-4 `t = scale * k + half; do { y = t; }
 *    while (0);`, draw 4 args (one, 1.0f): reload_cse does turn f15 into a register copy.
 *    $s1 = on needs on to have 4 refs (one 23.0f call through menu_coord with on);
 *    then 756 bytes, ~85 words (k/zero f21/f22 swapped by 0.6% priority, late
 *    daddu $a0 in draws 2-4, argument order, an extra nop, 23.0f registers). Not closed.
 * No gain: s = one before the helper (copy lands in the rounding block), args (s, one) or
 * (one, s), a `t = (float)y` local.
 */
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

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L02_003C43F0(char *obj) {
    char *text;
    int state;
    char *id;
    int y, on, entry;
    float one, zero, half, k, s;

    entry = 0x8710;
    k = 203.0f;
    half = 0.5f;
    on = 1;
    id = func_00336D50(D_L02_001A904C + entry, 0x70);
    y = menu_coord(D_L02_001B3E04, k, half, on);
    one = 1.0f;
    zero = 0.0f;
    s = (float)y;
    func_00300A00(id, 0x60442D00, 258.0f, s, one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x6F), 0x60442D00, 258.0f,
                  (float)menu_coord(D_L02_001B3E04, k, half, on), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x71), 0x55F0C070, 258.0f,
                  (float)menu_coord(D_L02_001B3E04, k, half, on), one, one, zero);
    id = func_00336D50(D_L02_001A904C + entry, 0x72);
    y = menu_coord(D_L02_001B3E04, k, half, on);
    s = one;
    func_00300A00(id, 0x55F0C070, 258.0f, (float)y, s, s, zero);
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
    func_0027FBD8(254, label_y(text, 373.0f, D_L02_001B3E04, 0.5f, 1), 0x88FFFFFF, text, -1);
}
