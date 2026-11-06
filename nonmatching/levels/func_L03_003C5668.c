/* 6 November 2026, Codex follow-up: current-toolchain reproduction of the
 * retained source in src/levels/shared/L03_002AB5C8.c is 644/644 bytes, 0/2 USA
 * places. The old claim of only one displaced instruction is incomplete for
 * this source/profile: 12 positions at +0x4 through +0x30 differ in prologue
 * ordering, and 10 later positions exchange the +0x1c/+0x20 spill slots.
 * Default -O2 -G0 -ffunction-sections. A separate unit reproduces the same
 * differences. Grouping the first real distance call gives 652 bytes; grouping
 * the output copy/height update gives 640. An output alias scoped to the tail,
 * a concrete 16-byte output-struct view, and a separate height local tie.
 * An entry output alias consistently used by the tail still costs a second
 * spill and eight bytes (652), as in the earlier note. The best C is unchanged.
 * Reopen on the incoming output pointer's spill dependency and loop spill order.
 * No alternate-release checks or linked builds were run in this follow-up.
 */
/* 6 November 2026: one check, no change. A `float *` return of a1 (the caller in
 * L03_003C3220-g8.c declares `float *`; retail leaves a1 in v0) compiles the same:
 * `sw a1,0x10(sp)` still sits at +0x20 instead of +0x4. 644/644 bytes, 0/2.
 */
/* Opus-1 (v1496), 29 October 2026: GNU game -O2 -G0 -ffunction-sections.
 * US, US2 and PAL: 644/644 bytes, 0/2 places each ("instruction at +0x4 differs").
 * One instruction is out of place: retail schedules the a1 spill `sw $a1,0x10($sp)`
 * at +0x4, ahead of every register save; here it follows `addiu $s0,$s6,0x10` (+0x20).
 * Everything else matches, including the tail: with qcopy_nc for the a1 copy the
 * call argument reuses the copy's $a3 reload (`daddu $a0,$a3`), as in retail; with
 * the "memory" clobber of qcopy it is reloaded from 0x10($sp) instead.
 * Measured cause of the residue (cc1 -fsched-verbose-5): in sched2 the spill store
 * (insn 6) ties the five saves that have five dependents (priority 14) and loses on
 * INSN_LUID; retail needs one more dependent for it. Stale pre-reload LOG_LINKS survive
 * into sched2: an entry alias `float *out = a1;` gives it that dependent (the store goes
 * to +0x4) but costs a second slot and store (652 bytes). const parameters, -g and
 * -fno-schedule-insns do not fix it. Reopen with a source shape that gives the a1
 * parameter copy a block-0 dependent without extra code.
 * Declarations below are the ones L03_002AB5C8.c already has.
 */
#include "common.h"

extern unsigned char *D_L03_001B2A1C __attribute__((sda));

extern int D_L03_001B2A38[] __attribute__((sda));

extern unsigned short *D_L03_001FB5A0[];

extern int func_L03_00419BD8(unsigned int, void *, void *);

extern float func_00282E80(void *, void *);

extern int func_00277258(void *, int, void *, float);

extern float func_002A89A8(void *, int, float);

extern float func_00282E48(void *, void *);

typedef struct {
    unsigned char pad0[0x200];
    int ids[8];
    unsigned int ref220;
    unsigned char pad1[0x354 - 0x224];
    unsigned char *target;
} L03SeekState;

void func_L03_003C5668(unsigned char *a0, float *a1, float *a2) {
    L03SeekState *o = *(L03SeekState **)(a0 + 0x68);
    unsigned short **tbl = D_L03_001FB5A0;
    unsigned char *cand;
    unsigned char *best = 0;
    unsigned char *e;
    unsigned short *q;
    float bestd;
    float d;
    float vec[4] __attribute__((aligned(16)));
    int r;
    int i;

    bestd = func_00282E48(a0 + 0x10, o->target + 0x10);
    cand = o->target;
    if (func_L03_00419BD8(o->ref220, a0 + 0x10, cand + 0x10))
        best = o->target;
    for (i = 0; i < 8; i++) {
        for (q = tbl[o->ids[i]];
             (o->ids[i] & 0xFF) != 0xFF && o->ids[i] <= D_L03_001B2A38[0] && q != 0 &&
             ((short)q[-1] >= 0 || q == tbl[o->ids[i]]);
             q++) {
            e = D_L03_001B2A1C + ((*q & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(short *)(e + 0xAA) == 0x972) {
                d = func_00282E80(a0 + 0x10, e + 0x10);
                if (d < bestd) {
                    qcopy(vec, e + 0x10);
                    vec[2] += 1.0f;
                    if (func_00277258(vec, 0, a0, 0.5f) == 0) {
                        cand = e;
                        r = func_L03_00419BD8(o->ref220, a0 + 0x10, e + 0x10);
                        bestd = d;
                        if (r)
                            best = cand;
                    }
                }
            }
        }
    }
    if (best)
        cand = best;
    qcopy(a2, cand + 0xF0);
    qcopy_nc(a1, cand + 0x10);
    a1[2] = func_002A89A8(a1, 0, 0.5f);
}

