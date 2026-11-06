/* 6 November 2026, round 10: no change (2 words), ~150 runs. Flags (-fno-sched-interblock,
 * -fno-schedule-insns 15, -fno-sched-spec, keep-block-order, gcse-unsplit-edges, zero-ti-por,
 * keep-block-zero-copy, sticky-volatile-refs, hazard-labels, move-all-movables): none better.
 * Cause of s7/fp without a group (greg dump): the gcse address pseudos for &position/&angles
 * tie at refs 4, live 520, so regno order gives position s7; a group must add one weighted
 * angles ref. Swapping the output copies fixes it (order wrong). Groups only around the anchor
 * func_002833F0 fix s7/fp and the last call, but any group start at line 71-73 moves the
 * rotation.f[1] store out of the spin jal slot, an end there puts object+0xc0 after the anchor
 * jal, and an end after func_00282D30(origin) (barrier on &offset) flips func_00283738 and
 * func_00282D30 arg order. Outer group to the end + inner 37-73: 5 rows (object+0xc0 only).
 * Groups on the output copies swap s5/s6 and add a nop. A pointer local for &angles, the
 * inverted parent test, and arm-copy order: worse. No nested-call form exists here (all
 * callees on this path are void). Keep the retained source below.
 */
/* 6 November 2026, round 9: no change (2 words). -frac2-sticky-volatile-refs: same 2 words.
 * Cause (sched dumps): the group's LOOP_END note makes the first insn after it (a0 = origin)
 * a barrier, so a1 and a2 tie and luid puts a1 first. With no barrier in that block the order
 * is retail's. Measured all group spans (start x end, 59 runs): ends before the last two calls
 * fix the last call but flip the func_00283738 or 2nd-last func_00282CC0 arg order (4-6 words);
 * end after the 2nd func_002833F0 needs object+0xc0 early (a `frame` local) and then leaves
 * func_00283738's a0/a1/a2 order (3 words). Defining origin only after the group (group uses
 * object+0x10) gives the last call retail's order (sched1 puts a2 before a1) but rebuilds a0 from
 * s3 and flips the 2nd-last call (4 words); recomputing origin with a live origin is 904-908 B.
 */
/* 6 November 2026, lead: last call func_00282CC0(origin, origin, &position): retail a0, a2, then a1 (= copy of a0) in the jal slot; ours a0, a1, a2-in-slot. The previous call already gets retail's a2-first order (a2 = s0). Spelling the second or first argument as object+0x10 grows to 904 B; a block-local dst copy ties. */
/* 6 November 2026, Codex follow-up: retained best source still 900/900 bytes,
 * 0/28 USA places, only +0x31c/+0x324 differ (last add's a1/a2 setup).
 * New pointer aliases for the position/origin at the group boundary and an
 * actual inline add helper reproduce those two differences. Computing the
 * origin again after the first add adds four bytes. Extending the large group
 * through the last add while grouping either the real angle-basis call or the
 * fallback angle copy disturbs allocation/scheduling. Grouping both optional
 * output copies adds four alignment bytes. A separate group around the last
 * add restores the old s7/fp swap. None improves the retained source below.
 * Reopen on the real last-call dependency, not another folded pointer alias.
 * No alternate-release checks or linked builds were run in this follow-up.
 */
/* 6 November 2026: one-pass group (docs/COMPILER-NOTES.md:54) from the parent-state test
 * through the first func_00282CC0, with an `origin = object + 0x10` local for the three
 * tail calls. Same profile and unit; 900/900 bytes, 0/28 USA places, 2 words left (was 8):
 * the group weights &angles above &position, so retail's s7/fp roles come out, and
 * `origin` keeps the address in s4 after the group. Left: the last func_00282CC0 sets
 * a1 (copy of a0) before a2 = &position; retail sets a2 first and puts the a1 copy in
 * the jal slot. The group's end splits that block. Measured worse: groups only around
 * the anchor func_002833F0 (7: first jal slot, object+0xC0 placement), only around the
 * tail copies (+4 nop, s5/s6 swap), the end after the last call (s7/fp back), a `frame`
 * local for object+0xC0 (3-6). Next: a form where the last call's a1 is not a copy of
 * a0 at sched1 while the group still ends before it.
 * Second pass, same day, no change: a pointer local for &position (set before or inside
 * the group), mixed object+0x10/origin arguments (904 bytes), casts, a group around the
 * tail copies or the last call.
 */
/* 4 November 2026: a genuine two-vector anchor aggregate was tested with
 * the existing qcopy/qcopy-barrier profile in the assigned production unit.
 * It remains 900/900 bytes, 0/28 USA placements, first mismatch +0x60:
 * grouping angles/position changes their stack slots as well as address
 * pseudos, so it does not improve the retained independent-vector source.
 * Keep the complete source below; no synthetic pointer-to-local copy used.
 * Other-release and linked checks were not run for this failed hypothesis.
 */
/* 31 October 2026: decomp-permuter (asm passes off) matches 28/28 with one change, the else
   branch's first copy written through the address of `state`:
       char **slot = &state; qcopy(&position, *slot);
   Retail keeps `state` in $s2 throughout, so this models no real memory traffic; it is an
   artefact, not used. Natural spellings measured 0/28: `state + 0`, ParticleVector casts and
   indexing, a `src` local for both copies, re-reading object + 0x68. The real source must
   reorder the same allocation; this branch is where to look. */
/* Retained near miss (M4, 26 October 2026); not linked.
 * Unit: src/game/00301F18-qcopy.c, profile -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * 900/900 bytes, 0/28 places: only the &position/&angles address pseudos take $s7/$fp the other way
 * round (8 words). Closed here: the parent-state test as an if/else-if chain (the `||` form folds into a
 * range check) and the found-parent arm first. Declaring angles before position gives retail's
 * registers but swaps the two stack slots (4 words). Queued for the permuter.
 */
#include "common.h"

typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern char ref_00305798_00[];

extern int func_002AD470(void *, void *, void *, void *, void *, void *);
extern s32 func_002AD0B0(u8 *);
extern void func_00282C88(ParticleWord *);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

/* Update the pickup's anchor, turn it, and compose the visible orientation. */
void func_00301F18(u8 *object, void *outPosition, void *outAngles)
{
    char *state=*(char **)(object+0x68);
    ParticleVector spinMatrix[3], anchorMatrix[3];
    ParticleVector rotation, offset, position, angles;
    char *parent;
    float step, tilt, radius, lift;
    int detach;
    u8 *origin;
    if (*(char **)(state+0x5c)) {
        func_002AD470(object,*(char **)(state+0x5c),state,state+0x10,&position,&angles);
    } else {
        qcopy(&position, state);
        qcopy(&angles, state+0x10);
    }
    origin = object+0x10;
    do {
    if (object[0x20]==3 && *(char **)(state+0x5c)) {
        parent=*(char **)(state+0x5c);
        detach=0;
        if (*(u8 *)(parent+0x20)==254) detach=1;
        else if (*(u8 *)(parent+0x20)==253) detach=1;
        else if (!func_00277258(object+0x10,0x22,object,0.25f)) detach=1;
        if (detach) {
            object[0x20]=1;
            func_00282C88((ParticleWord *)(state+0x30));
            *(float *)(state+0x3c)=1.0f;
            parent=(char *)func_002AD0B0((u8 *)*(char **)(state+0x5c));
            if (parent) {
                qcopy(state+0x20, parent+0x10);
                *(char **)(state+0x5c)=0;
            } else {
                func_00282C88((ParticleWord *)(state+0x20));
                *(char **)(state+0x5c)=0;
            }
        }
    }
    switch (*(short *)(object+0xaa)) {
    case 13: step=0.04f; tilt=-0.25f; radius=0.04875f; lift=0.325f; break;
    case 14: step=0.03f; tilt=-0.5f; radius=0.0245f; lift=0.35f; break;
    case 15: step=0.025f; tilt=-0.4f; radius=0.05625f; lift=0.375f; break;
    default: step=0.0175f; tilt=-0.35f; radius=0.135f; lift=0.3f; break;
    }
    if (*(u8 *)(state+0x55)&1) {
        *(float *)(state+0x50)=func_00283B98(*(float *)(state+0x50),step);
        *(float *)(state+0x58)=func_00283B98(*(float *)(state+0x58),-0.0125f);
    } else {
        *(float *)(state+0x50)=func_00283BE0(*(float *)(state+0x50),step);
        *(float *)(state+0x58)=func_00283BE0(*(float *)(state+0x58),-0.0125f);
    }
    qcopy(&rotation, state+0x50);
    rotation.f[1]=tilt;
    func_002833F0(spinMatrix,&rotation);
    func_002833F0(anchorMatrix,&angles);
    func_00283738(object+0xc0,anchorMatrix,spinMatrix);
    func_00282D30(origin,&anchorMatrix[2],radius);
    func_00282D30(&offset,object+0xc0,lift);
    func_00282CC0(origin,origin,&offset);
    } while (0);
    func_00282CC0(origin,origin,&position);
    if (outPosition) qcopy(outPosition, &position);
    if (outAngles) qcopy(outAngles, &angles);
}
