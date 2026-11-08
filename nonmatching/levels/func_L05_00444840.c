/* 8 November 2026 (round 9, rank_for_schedule): base 736/736, 2 differing words (retained C, recorded flags). rank_for_schedule is identical in GCC 2.95/2.95.2/2.95.3 and EE 991111/991111b; SN 2.95.2 v2.73a makes the same tie choice where its output is comparable. Env probes (sched1/sched2/both): reg weight swapped/clamped/dropped/after class/positive-or-negative only, class dropped/reversed, dependent count reversed/dropped/data-only/clamped, LUID reversed, INSN_UID ties, no birthing boost: none improves any of the nine cluster targets; forced on, every variant changes 6-7124 of 8761 matched units. Hypothesis falsified. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 736/736, 2 rows (a1/a2 setup order before the second func_L05_00444D60 call). The three address loads tie on every scheduler key; no EE GCC build (991111a/-01/b-r4, SN 2.73a) reproduces retail's order from this C, so the source shape is still unknown. */
/* 7 November 2026, Antigravity worker (round 12, lessons 32 & 36 / scheduler analysis):
 * USA v1.01, check.py only: 736/736 bytes, 0/4 places, 2 non-relocation rows at +0x124/+0x128.
 * Profile: -O2 -G8 -ffunction-sections -freduce-all-givs.
 * Exhaustive scheduler and Haifa dependency audit confirms the exact mechanism and blocker:
 * 1. In calls.c:expand_call, arguments are emitted in parameter order (a0, a1, a2, a3).
 *    In sched1, insn 180 (a1: addiu $a1, $sp, 0x8) and insn 182 (a2: addiu $a2, $sp, 0xC)
 *    tie on priority (call priority + 1), weight (1: sets 1 reg, kills 0), class (3) and
 *    dependents (1: call_insn 186). Because of the complete tie, sched1 sorts by INSN_LUID,
 *    preserving emission order (a1 before a2).
 * 2. In sched2 (haifa-sched.c:rank_for_schedule), register pressure weight is inactive
 *    (reload_completed == 1). The tie-breaker is INSN_DEPEND count before INSN_LUID.
 * 3. Moving `i = 0;` outside the `do { ... } while(0)` group introduces an output dependence
 *    on hard register $a2 (insn 182 -> i = 0), boosting insn 182's dependent count from 1 to 2.
 *    This produces the EXACT retail sequence at the call (+0x124: addiu $a2, $sp, 0xC;
 *    +0x128: addiu $a1, $sp, 0x8; +0x12C: daddu $a3, $zero, $zero; 100% byte match).
 * 4. BUT NOTE_INSN_LOOP_BEG acts as an impenetrable sched2 barrier. Because `i = 0;` precedes
 *    the barrier while `range = 40;` is inside the group, `i = 0` is emitted at clock 19 and
 *    `range = 40` at clock 20, inverting retail lines 93-94 (+0x170 daddu $a2; +0x174 addiu $a3).
 * 5. Conversely, placing `range = 40;` before the barrier also gives $a3 an output dependence,
 *    boosting $a3 above $a1 in the call (yielding a2, a3, a1 instead of retail's a2, a1, a3),
 *    and causes loop.c to recognize the scan loop as reducible (swelling the function to 768 bytes).
 * 6. Lesson 32 probes: inline helper wrappers (project_coords), pointer temporaries (px, py),
 *    and expression forms (&target_x + 1) do not change actual argument emission order in expand_call
 *    nor reg_weight in sched1 (no pseudo dies at the move).
 * 7. Under the 6 November 2026 rules (no volatile, no inline asm, no #define aliases, no dead stores,
 *    no redundant reloads, no padding locals, no one-field struct wrappers), the a1/a2 tie cannot be
 *    broken in clean C. Retaining baseline 2-row near miss (736/736 bytes).
 */
/* 6 November 2026, decomp-permuter (40 min, 3 threads, --stack-diffs, retail-byte scorer): no candidate beat the base score 20 (2 rows); best rule-compliant result is the retained C. Setup: /tmp/claude-1000/-home-lynder063-rac2-decomp/lead/work/perm. */
/* 6 November 2026 (round 11c, prototype audit): every declared callee agrees with its matched C or the established asm prototype (func_L05_00444D60 is void in src/levels/shared/L05_00428350.c:327; func_002AB1F0, func_00282C30, func_00283CE0, func_00282E48, func_002761F8 results are all read). No void/int correction exists for the a1/a2 tie; not rerun. */
/* 6 November 2026, lead (round 11b): loop-structure probes all stay a1-then-a2 in cc1 -S: exclusion scan as an inline helper, the whole candidate filter as an inline helper, a next-candidate helper returning the cursor, a pointer-walk exclusion, break/goto-next exclusion forms, for/for(;;) outer loops, pos = object + 0x10 at the loop top, and all 12 -frac2-* switches plus 12 scheduler/cse flags. -dL shows loop.c (scan_loop, loop_has_call) substitutes both &target temporaries into the a1/a2 moves in every form. With -fno-schedule-insns and -fno-schedule-insns2 the order is still a1, a2, so both schedulers tie (same priority, weight, class and 7 dependents) and keep the expand order. A pseudo a2 = P that dies there would win sched1 on weight, but local-alloc only replaces P by sp+12 when REG_N_REFS is 2, and flow weights refs by loop depth (P counts 4 inside the loop), so P keeps a register. */
/* 6 November 2026, lead (round 11): target-before-source and target_y-before-target_x declarations and a (u8 *) object cast tie at 2 rows; `i = 0` folded into the call's last argument gives 142. */
/* 6 November 2026 (round 11, Codex): baseline reconfirmed with check.py:
 * 736/736 bytes, USA v1.01 0/4 places, exactly two non-relocation instruction
 * differences at +0x124/+0x128. No source/profile improvement retained.
 * New lifetime/API probes: inline screen_delta(const int *, const int *) for
 * either/both axes stays at two rows. Reusing an int pointer for the parameter
 * read, excluded-entry read, projected coordinate and subsequent rule/class
 * reads never fixes the argument order (2-153 rows, 728-744 bytes); reading y
 * through that pointer also changes the two coordinate-load scheduling rows.
 * Assigning the actual zero call argument to the scan index changes allocation
 * throughout the body; assigning it to range or the exclusion index stays at
 * two rows. Storing real coordinate differences back into the output locals
 * adds one store per axis (744/752 bytes), so it is not an improvement.
 * Unsigned coordinate storage with explicit signed subtraction stays at two
 * rows. Aggregate projection helpers and named union views do not fix the
 * order; returning y by value from an inline projection wrapper also changes
 * allocation substantially. All underlying projection calls keep the matched
 * definition's (position, int *x, int *y, int offset) interface: reversing its
 * pointer arguments would change behavior and is not a scheduling remedy.
 * Seventy source variants checked, no hill climb or forbidden steering forms.
 * Best C below is unchanged; no linked build run (lead owns builds).
 */
/* 6 November 2026 (round 10, Antigravity worker): USA v1.01, check.py only: 736/736 bytes, 0/4 places,
 * exactly 2 differing rows (+0x124 and +0x128). Profile: -O2 -G8 -ffunction-sections -freduce-all-givs.
 * Haifa scheduler ready-list trace confirms the root mechanism:
 * In calls.c:expand_call, arguments are emitted in order (a0, a1, a2, a3). In sched1, insn 180 (a1)
 * and insn 182 (a2) both have latency 1, weight 1, and 1 dependent (call_insn 186).
 * In sched2, ready list tie-break uses INSN_LUID(tmp) - INSN_LUID(tmp2), preserving a1 before a2.
 * When `i = 0;` is outside the phony do { ... } while(0) group (Case 2), hard register $a2 is set in block 18,
 * giving insn 182 an output dependence that boosts a2 over a1 (matching retail lines 74-75: addiu a2,sp,12;
 * addiu a1,sp,8; daddu a3,zero,zero 100% byte-for-byte). But because NOTE_INSN_LOOP_BEG acts as a sched2
 * barrier, i = 0 is emitted at clock 19 and range = 40 at clock 20, swapping retail lines 93-94 (a2 before a3).
 * When both range = 40 and i = 0 are outside the group, loop.c classifies the group as a real loop and
 * strength-reduces D_L05_002B87F0[i] (114 diffs).
 * Baseline C below retains retail lines 93-94 (addiu a3,zero,0x28; daddu a2,zero,zero); remaining diff is
 * solely +0x124 (mine a1, retail a2) and +0x128 (mine a2, retail a1).
 */
/* 6 November 2026 (round 10c): still 2 rows. Why no group placement can work:
 * in sched2, rank_for_schedule breaks the a1/a2/a3 tie by INSN_DEPEND count.
 * A loop-note barrier insn depends on every earlier insn (all args +1), and a
 * pre-barrier set of a2 (i = 0) or a3 (range = 40) adds one more to that arg
 * only. Retail's a2, a1, a3 with a3=40 before a2=0 needs a2 alone boosted
 * while range = 40 is emitted first, which the barrier forbids; so retail's
 * a2-first came from sched1 (LUID order), where all three args tie (same
 * weight, priority and 7 dependents; dumped). Only an unsubstituted
 * a2 = P with P dying (weight 0) would put a2 first. Tried (about 40
 * compiles): i = 0 before the call, after the call, after dx, as the
 * group's first statement (4 rows); range = 40 alone in a group; both
 * outside (106-130); for/while/do(1)/inverted-test scans inside the group
 * (3-113); range = 40 as the -1 exit arm (54); groups around the call, dx or
 * dy (4-24); exclusion and second scan reusing i (2-27); a pos local for
 * object + 0x10 at four places or assigned in the argument (28-129); goto
 * outer loop (ori args, 176). A py set in both exclusion arms gives
 * a2 = P but swaps the target stack slots (6 rows) and is not clean C. */
/* 6 November 2026, lead: with -freduce-all-givs (2 rows: a1/a2 setup order before the second func_L05_00444D60 call; retail's first call keeps a1-then-a2): no change from int[2]/struct/shared int[4] target locals, pointer temporaries for either argument, a 150-step hill-climb over the 16 local declarations. */
/* 6 November 2026 (round 6), USA v1.01, check.py only: 736/736 bytes, 0/4
 * places, 7 differing rows. Profile: -O2 -G8 -ffunction-sections (the
 * -fno-rerun-loop-opt switch is no longer needed).
 * What fixed the loop shapes: each rule scan is a goto loop inside a
 * do { ... } while (0) group whose first insn is a real assignment
 * (range = 40 / j = 0). That group is "phony" to loop.c, so there is no
 * strength reduction and no base hoist; its loop note still aligns the scan
 * label and weights the scan refs. A separate index per scan (i, j) and a
 * separate exclusion index n give retail's a0/a1/a2 and v0/v1/a0 choices.
 * The -1 exit is a goto past the group and the found arm a break, so jump1
 * keeps the found code as the fall-through and reorg emits bnel. The two
 * frame-counter reads use sda array aliases (lui/lw on one register).
 * Remaining: (1) prologue stores s7 early: the cursor init (addiu s7) is in
 * the prologue block; retail has it after the first null test. Guarded
 * do-while forms move it but leave an extra copy (v1 -> s7).
 * (2) second D_L05_00444D60 call sets a1 before a2 (retail a2 first);
 * `i = 0;` outside the group fixes this but then i = 0 is scheduled before
 * range = 40. Round 6b: a scalar alias of the list's first word for the
 * guard read removes the copy and fixes the prologue, but cursor then
 * outranks the hoisted 12 (s6/s7 swap, 17 rows); pos assigned in the call
 * arguments swaps s0/s1. Tried and rejected this round: for/while(1) scans (loop.c SR),
 * label inside a group with outside back-edge, then-first arms (jump1 moves
 * the found arm), indexed outer loop (giv not reduced), local scope or
 * declaration order of the grid outputs, sched/gcse flag sweeps.
 * 6 November 2026 (round 7): this C plus the standard -freduce-all-givs
 * gives 2 rows (only the a1/a2 order): loop.c then reduces the outer
 * `*cursor` giv (benefit 0, "not worth while" without the flag) and puts the
 * cursor init in the preheader after the null test, as retail does. No unit
 * uses that flag yet. Without it, an index over a local copy of the list
 * (`cursor = D; while ((object = cursor[k]) != 0) ... k++`) is reduced too,
 * but leaves a copy (v1 -> s7): 7 rows. a1/a2 in sched2: an arg move wins
 * the tie when a later insn in the block before the group's loop note sets
 * its register (i = 0 in a2 -> a2 first; range = 40 in a3 -> a3 first; both
 * -> a2, a3, a1). Retail needs a2 alone boosted but range = 40 before i = 0,
 * which no group start tried allows (group at call, dx, dy, pos, exclusion
 * check or kind: 6-110 rows). Also no help: -fmove-all-movables,
 * -malign-loops=2, -fno-strength-reduce, for(;;) scans, label-first groups
 * (rotated or multiple entry), table pointer local, int target[2], px/py.
 * 6 November 2026 (round 9), still 2 rows with -freduce-all-givs. Why the
 * tie: loop.c (scan_loop, loop_has_call) substitutes both single-use
 * &target_x/&target_y temporaries into the a1/a2 loads. Both loads then
 * have equal priority, weight 1 and one dependent, so sched1 keeps the
 * source order (a1 first) and sched2 copies it. Retail's addiu (not the ori
 * that combine makes, as in the first call) means a2 was also a frame-address
 * equivalent. To put a2 first, its load must be "a2 = P" with P dying there
 * (sched1 weight 0) and P later replaced by sp+12 (update_equiv_regs or
 * reload). That needs a REG_EQUAL note on P's set, and cse only adds one
 * when the address was already seen in the same extended block. Tried
 * (about 55 compiles): py = &target_y at 7 places in the loop, with and
 * without -fmove-all-movables (4-149 rows; py gets a register and its addiu
 * moves early). Also tried: a py reused for both calls (combine makes
 * ori, 7 rows), py - 1 for a1 (hoisted, 69 rows), py read again after the
 * call (cse folds it, 2-4 rows), an inline grid_position wrapper (2), and
 * 11 single -f flags (2-114).
 */
#include "common.h"
extern void func_L05_00444D60(void *, int *, int *, int);
extern int func_002AB1F0(u8 *);
extern int func_00282C30(int);
extern float func_00283CE0(int);
extern float func_00282E48(void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern u8 *D_L05_001FB5E0[];
typedef struct { int object_class, screen_range; float world_range; } TargetRule;
extern TargetRule D_L05_002B87F0[];
extern float D_L05_001B1B1C_gp SDATA(D_L05_001B1B1C);
extern float D_L05_001B1B18_gp SDATA(D_L05_001B1B18);
extern int D_001A79F0[] __attribute__((sda));
extern float D_L05_001B96C0[];
extern int D_L05_001B2048[] __attribute__((sda));

static __inline__ int target_class(u8 *object)
{
    if (object && *(u8 **)(object + 0x24))
        return *(s16 *)(*(u8 **)(object + 0x24) + 0x46);
    return 0;
}

/* Grid outputs are four separate32-bit words. The rule table has real12-byte
 * rows terminated by class-1; neither rule nor object-list extent is invented.
 * The parameter accessor returns a32-bit target address, matching its C def. */
u8 *func_L05_00444840(void *position, u8 **excluded, u8 *current)
{
    int source_x, source_y, target_x, target_y;
    int i, kind, range;
    float dx, dy, distance;
    u8 **cursor, *object, *parameters;
    int state;
    int n, j;
    func_L05_00444D60(position, &source_x, &source_y, 0);
    cursor = D_L05_001FB5E0;
    while ((object = *cursor) != 0) {
        if (!object[0x31])
            goto next;
        parameters = (u8 *)func_002AB1F0(object);
        if (!parameters || *(float *)parameters <= 0.0f)
            goto next;
        kind = target_class(object);
        if (kind != 5 && kind != 15)
            goto next;
        if (excluded) {
            for (n = 0; excluded[n] && object != excluded[n]; n++) {}
            if (excluded[n])
                goto next;
        }
        func_L05_00444D60(object + 0x10, &target_x, &target_y, 0);
        dx = func_00283CE0(func_00282C30(target_x - source_x));
        dy = func_00283CE0(func_00282C30(target_y - source_y));
        do {
            range = 40;
            i = 0;
scan1:
            if (D_L05_002B87F0[i].object_class == -1)
                goto scan1_done;
            if (*(s16 *)(object + 0xAA) == D_L05_002B87F0[i].object_class) {
                range = D_L05_002B87F0[i].screen_range;
                break;
            }
            i++;
            goto scan1;
        } while (0);
scan1_done:
        if (!(dx < D_L05_001B1B1C_gp + (float)range) || !(dy < D_L05_001B1B1C_gp + (float)range))
            goto next;
        distance = D_L05_001B1B18_gp;
        do {
            j = 0;
            state = D_001A79F0[0];
scan2:
            if (D_L05_002B87F0[j].object_class == -1)
                goto scan2_done;
            if (D_L05_002B87F0[j].object_class == *(s16 *)(object + 0xAA)) {
                distance = D_L05_002B87F0[j].world_range;
                break;
            }
            j++;
            goto scan2;
        } while (0);
scan2_done:
        if (state != 20 && distance < func_00282E48(D_L05_001B96C0, object + 0x10))
            goto next;
        if (current && current == object && D_L05_001B2048[0] % 3 != 0)
            return object;
        if (!func_002761F8(D_L05_001B96C0, object + 0x10, 16, object, 0))
            return object;
next:
        cursor++;
    }
    return 0;
}
