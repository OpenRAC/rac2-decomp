/* 8 November 2026 (Sonnet round): re-measured 1248/1248, 0/28; the three residues are unchanged (beqz/b vs bnez/b at +0x2B4554, $v1 reuse at +0x2B48A4, PRE slot order). 25 min permuter (-j2, base 2510): best 1610 only lost the TI type (not honest); no usable candidate. */
/* 8 November 2026 (named-local slot order, the func_00281A08 technique): not tried here; besides the nine PRE slots this function keeps two non-slot residues (the beqz/b player test and the $v1 reuse), so a slot fix alone cannot match it. The technique only moves a value earlier than the PRE registers (see func_L00_0038E880). */
/* 8 November 2026 (gcse table size): the five EE cc1 builds here (ours, 991111a, 991111-01, 991111b-r4, SN 2.95.2 273a) give the same PRE table size on this source, so the sizing rule is shared. Forced sizes 11..401: no size gives 0 (best 43: 21 diffs; ours 119: 42), so the table size alone does not close it. */
/* Claude Opus 5.5, 8 November 2026; retained near miss (supersedes the header below).
 * Current check: 1248/1248 bytes, 0/28 places; profile -O2 -G0 -ffunction-sections.
 * Changes from the 29 October draft: qcopy_nc for the first snapshot (its destination is only
 * read after later calls) lets reload reuse $a0 for self, as retail does; `angles[1] >
 * limit[1]` gives retail's load order in the second clamp. Remaining: (1) the player-state
 * test is `beqz -> player; b decay` where retail has `bnez -> decay; b player`; (2) at
 * 0x002B48A4 retail reuses $v1 (work) for func_00283098's a1, we reload it; (3) the nine
 * PRE address spills at 0xC8-0xE8 are in another order.
 * (3) cause, from -dG/-dg dumps: the spills are gcse PRE reaching registers, made in hash
 * bucket order ((regno + offset) mod N, N = insns/2 | 1; here N = 119, self = r84,
 * sway = r85) and given slots in pseudo order. No N fits retail's slot order with
 * sway = r85: the sway base in those addresses must be a pseudo of about r114-r128
 * (made around the active path), and self about r112-r127 if N stays near 119. Inline
 * helpers do not help (gcse cprop folds the parm copies back to r84/r85).
 * Measured: -frac2-qcopy(-barrier) with plain TI copies ties (same three residues);
 * `target || (player test)` with an inner target test gives retail's bnez/b pair but cse's
 * jump threading puts the player block first and jump2 cross-jumps the two calls; an
 * inline tail helper with an `active` flag keeps the flag test (285 diff lines).
 * Round 2 (8 November 2026): every goto/if/else spelling of the player test either keeps
 * `beqz -> player; b decay` or ends the tests with `b player` over the target block, and
 * then jump.c's "if (foo) bar; else break;" swap (jump.c:1900; needs LABEL_NUSES == 1 on
 * the target label and `b` to the next label) moves the target block first (95 lines).
 * -fno-thread-jumps does not change that. A block-scoped or inline copy of sway does not
 * give a later base pseudo, because gcse cprop puts r85 back before PRE.
 */
/* GPT-6.1 Sol high, 29 October 2026, task v0788; retained near miss.
 * Best current-toolchain check: 1252/1248 bytes, 0/28 USA v1.01 places.
 * Profile: -O2 -G0 -ffunction-sections, isolated source unit. No linked match.
 * Required types and declarations are included below; common.h supplies qcopy.
 *
 * Improvements over the previous 1240-byte TI-only draft: use approved qcopy
 * for the two external snapshots and offset-to-work transfer, but retain the
 * ordinary TI work-to-angles assignment (retail uses stack offsets there).
 * Give the kick loop its own counter: reusing i makes GCC keep the main-loop
 * counter in s4 and push in s5; separate counters recover push in s4, the
 * spilled main-loop counter at sp+0xC4, and the main loop's saved registers.
 * Explicit target/player labels retain both initial vector-subtraction calls.
 *
 * Remaining differences: the first snapshot makes qcopy reload self from its
 * stack home rather than retain a0; the player-state test branches directly
 * to the player call instead of decay; address spill slots C8..EC are ordered
 * differently; and the delta-pointer update reloads its spill after the store
 * at boot 0x002B47C4, adding one word. The post-loop body is shifted by four.
 * The frame is retail's 0x140 and all scratch extents/offsets are preserved.
 *
 * Measured alternatives: reversed inner target test reaches 1248 bytes with
 * the old shared counter, but lays out the player call first and retains the
 * wrong loop allocation. A separate counter makes that form 1252. Combining
 * stack arrays into a struct ties that result. Explicit delta-pointer induction
 * changes spill order but retains the extra reload. A scalar wave temporary
 * ties this retained body. A precomputed rotation pointer worsens the prologue.
 * Flattening the negative player test changes block order; -fno-thread-jumps
 * with separate counters emits 1268 bytes; -fno-gcse on this draft emits 948.
 * Do not use the 1248-byte -fstrict-aliasing result: TI casts over float arrays
 * let that profile incorrectly propagate the prior zero into the angle copy.
 * Reopen with evidence for the original pointer declarations/alias contract
 * and conditional layout; further fixed-offset-copy work is unnecessary.
 */

#include "common.h"

typedef int Vec128_2B44C0 __attribute__((mode(TI)));

typedef struct {
    Vec128_2B44C0 anchor;
    Vec128_2B44C0 offset;
    Vec128_2B44C0 rotation;
    float position[3];
    float velocity[3];
    float spring[3];
    float damping[3];
    float limit[3];
    float scale[3];
    float kick[3];
    float phase[3];
    float speed[3];
    float amplitude[3];
    int unused;
    int timer;
} Sway_2B44C0;

typedef struct {
    char pad0[0x80];
    Vec128_2B44C0 position;
    char pad1[0x33C - 0x90];
    char *target;
    int state;
} Player_2B44C0;

extern Player_2B44C0 D_00189E20;
extern void func_00115484(void *, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AFDD8(char *, void *, void *, void *);
extern int func_00282948(void *);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002B0158(char *, void *, void *, float);
extern char *func_002AD0B0(char *);
extern void func_002AD6F0(char *, void *, void *, void *);

void func_002B44C0(char *self, Sway_2B44C0 *sway, float *target)
{
    float old_position[4];
    float old_rotation[4];
    float push[4];
    float delta[4];
    float angles[4];
    float work[4];
    float matrix[12];
    float moved[4];
    float shift[4];
    float step[4];
    char *body;
    float roll;
    int i;
    int kick_axis;

    qcopy_nc(old_position, self + 0x10);
    qcopy(old_rotation, self + 0xF0);
    func_00115484(push, 0, 16);
    if (target != 0)
        goto target_delta;
    if (D_00189E20.target == self && D_00189E20.state >= 2)
        goto player_delta;
    goto decay;
target_delta:
    func_00282CF0(delta, target, self + 0x10);
    goto active;
player_delta:
    func_00282CF0(delta, &D_00189E20.position, self + 0x10);
active:
    func_002AFDD8(self, delta, delta, 0);
    func_00282CF0(delta, delta, &sway->offset);
    push[0] = -delta[1] * sway->scale[0];
    push[1] = delta[0] * sway->scale[1];
    push[2] = -sway->scale[2];
    if (sway->timer == 0) {
        for (kick_axis = 0; kick_axis < 3; kick_axis++)
            sway->velocity[kick_axis] += push[kick_axis] * sway->kick[kick_axis];
        sway->timer = 10;
    }
    goto update;
decay:
    func_00282948(&sway->timer);
update:
    for (i = 0; i < 3; i++) {
        sway->velocity[i] += sway->spring[i] * (push[i] - sway->position[i]);
        sway->velocity[i] -= sway->damping[i] * sway->velocity[i];
        sway->position[i] += sway->velocity[i];
        sway->phase[i] = func_00283B98(sway->phase[i], sway->speed[i]);
        delta[i] = sway->amplitude[i] * func_00283198(sway->phase[i]);
    }
    *(Vec128_2B44C0 *)work = 0;
    work[0] = sway->position[0] + delta[0];
    work[1] = sway->position[1] + delta[1];
    *(Vec128_2B44C0 *)angles = *(Vec128_2B44C0 *)work;
    if (sway->limit[0] < angles[0])
        angles[0] = sway->limit[0];
    else if (angles[0] < -sway->limit[0])
        angles[0] = -sway->limit[0];
    if (angles[1] > sway->limit[1])
        angles[1] = sway->limit[1];
    else if (angles[1] < -sway->limit[1])
        angles[1] = -sway->limit[1];
    func_002833F0(matrix, angles);
    func_002833F0(self + 0xC0, &sway->rotation);
    func_00283738(self + 0xC0, self + 0xC0, matrix);
    qcopy(work, &sway->offset);
    work[2] += delta[2];
    func_00283098(moved, work, self + 0xC0);
    func_00282CC0(moved, moved, self + 0x10);
    func_00282CF0(shift, &sway->anchor, moved);
    func_00282CC0(self + 0x10, self + 0x10, shift);
    roll = -sway->position[2];
    if (sway->limit[2] < roll)
        roll = sway->limit[2];
    else if (roll < -sway->limit[2])
        roll = -sway->limit[2];
    func_002B0158(self, self + 0x10, self + 0x10, roll);
    body = func_002AD0B0(self);
    if (body != 0) {
        func_00282CF0(step, self + 0x10, old_position);
        func_002AD6F0(body, step, old_rotation, self + 0xF0);
    }
}
