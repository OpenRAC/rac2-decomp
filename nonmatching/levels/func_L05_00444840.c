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
