/* 6 November 2026 (round 12): byte-exact only with two forbidden forms, so still a near miss. One inline asm statement for the call, `__asm__ volatile("move $4,%0\n\tjalr %1" :: "r"(t), "r"(update) : "$2", "$4", "$31");`, gives the callback in v1 (the $2 clobber), the a0 move before the jalr and the empty slot, with no pin and no .set; the assembler's reorder mode supplies the nop. With `volatile unsigned short flags` as well (the beqz; nop) and `Node *head = func_002A08A0(); D_001B1B68 = head; for (t = head; ...)`, tools/check.py gives 28 of 28, and diagnostic `tools/build.py boot --strict` and `level 0 --strict` print OK with the function placed. PAL and v2.00 not checked (no dumps here). Without volatile: asm alone, with "memory", and with -frac2-sticky-volatile-refs all keep beql + the lhu steal. AGENTS.md forbids both forms in linked C, so this is evidence of how retail was built, not a match. Unblock: a maintainer decision on a reviewed shared helper for this call, and a real cause for the flags reload. */
/* 6 November 2026 (round 11, w-c5): not matched. Control-flow forms tested against the fixed retail flow: if/else arms that each call, both-arm callback loads, goto to a shared call, goto around the call, `?:` argument, switch on the flag, switch on `update != 0`, for(;;)/while + break, do/while(0) around call + 0x4 test, do/while with a condition after the call. All cross-jump or simplify back to `move a0; jal v1` (slot filled, callback v0); the switch on `update != 0` gives v1 but adds a compare. By construction no C form works: expand emits the a0 move adjacent to the call, and a label there survives only with a jump to it; retail has no branch to 0x2B66AC/0x2B66B0, no division (trap_if), no asm. Retail also leaves the beqz slot empty, so the daddu was unavailable to both slots there. -flive-range: no change. */
/* 6 November 2026 (round 10, w-c5): not matched. Retail tests v0 (flags & 0x40) in the bnel, not a long-lived value; the sibling-shape lead does not apply. Flags read once into a local (f = t->flags reused) and an early `update = 0` keep v0 and the filled slot. Our reorg (fill_simple_delay_slots backward scan, plus the RAC2 trap_if stop) can only leave the jalr empty at a label, jump, SEQUENCE, asm or trap_if between the a0 move and the call; an unused user label before the call is deleted by jump. v1 needs a non-call-crossing allocno born after func_002A05A8 that conflicts with the callback and prefers v0 (regs_someone_prefers); only t (call-crossing, pruned) exists. */
/* 6 November 2026 (round 9, w-cc): not matched, no flag. Source: a `void (*volatile vfunc)` member drops the bnel steal (retail steals the lw, so the retail load is not volatile); a `const` callback local is identical (v0, filled slot). Compiler rule: falsified by comparison, not built. Our cc1 output for matched func_L00_002D5940 has the identical pre-reorg shape (beql slot steals `lw $2,100`, label, `beq $2`, `move $4`, `jal $31,$2`) and retail fills that slot with v0, so any reorg rule that empties this jalr slot, or any allocation rule keyed on this shape that gives v1, changes a matched unit. */
/* 6 November 2026 (round 6, w-c5): not matched. Separate head local (`head = func_002A08A0(); ref = head; for (t = head; ...)`) gives retail's `sw $v0` global store; with `volatile unsigned short flags` and the plain join load the only diffs left are callback v0 (retail v1) and the filled jalr slot. Gas in reorder mode reproduces retail's `beqz; nop; daddu a0; jalr v1; nop` exactly, so retail cc1 left that jalr unfilled; reorg (fill_simple_delay_slots backward scan) only refuses the a0 move for a label/asm/SEQUENCE/trap_if between it or a volatile/length-2 insn, none reachable from C here. greg: callback pseudo conflicts only with t, a0, sp (no v0 conflict). If/else arms that each call the callback, and goto-to-shared-call forms, cross-jump back to the same code. */
/* 5 November 2026 (round 5, w-cc): not matched, no flag. v1 is reachable: `update = t->vfunc; if ((t->flags & 0x40) == 0) { func_002A05A8(t); update = t->vfunc; }` keeps the callback live over the v0 flag test, so global-alloc gives v1; but reorg then backfills the first lw into a plain bne (retail bnel, stolen from target) and still fills the jalr slot. Census of `move aN; jal; nop` in boot+L00: the matched-C sites checked (func_0027A1D0, func_L00_003F5870) are unfilled because a real cross-jump label sits between the arg move and the jal; no source form here gives such a label, and no principled reorg rule covers only these two sites. */
/* 5 November 2026 (w-c6): one-pass groups around the callback load, the call, load+call, the 0x40 test, the 0x4 test, the whole body and a grouped `self = t` arg (cse deletes it) all keep v0 and the filled jalr slot. greg shows the callback pseudo conflicts only with t (crosses calls, so its v0 preference is pruned); priority order is irrelevant: v1 needs a real hard conflict with v0 during lw..jalr. */
/* 5 November 2026 (w-c2): cc1 -dd shows our reorg fills the jalr slot from the backward a0 move; retail census has the same `lw; L: beqz; nop; jalr; daddu a0` shape filled 27 times elsewhere, so only this function and its sibling func_L00_0032CF60 (callback in v1, slot empty) differ. Unprototyped callback, direct member call, int return, -fno-schedule-insns(2)/-fexceptions/-fno-gcse/-fno-sched-interblock all keep v0 and the filled slot. Next: find what makes global-alloc avoid v0 (regs_someone_prefers from a lower-priority conflicting pseudo) - the same RTL cause likely blocks the slot. */
/* 5 November 2026 (wave 3): not matched. Only these two functions (all 28/27 places) have lw v1;beqz;nop;daddu a0;jalr v1;nop; the 27 FILLED lw v0,0x64(s2) sites are func_L00_002D5940 (C, plain `if (obj->update) obj->update(obj);`). Reorg (reorg.c fill_simple_delay_slots) can only refuse the a0 move if a stopper (label/asm/jump) sits between it and the call: an empty asm after a $4-pinned arg reproduces nop+daddu+jalr+nop exactly, and a $3 pin gives v1, but both are banned. int/ptr/double/long long/char/short returns, switch/goto/cross-jump forms, int-view test, local copy, inline helper with -mastra-sibcall/-mastra-cygnus-cfg, and -O1/-O3/-Os/-fno-* flags all keep v0 and the filled slot. */
/* 5 November 2026 (wave 2): `volatile unsigned short flags` stops the beql target steal, so the beqz+nop now match retail; still 144/148, 0/28: callback stays in v0 and cc1 fills the jalr slot with the a0 move (retail: v1, a0 move before jalr, nop slot). Tried -g, -frac2-hazard-labels, -frac2-keep-block-order, noreturn/variadic/long/float callback types, inline helper: no change. */
/* 5 November 2026: pointer-based baseline rechecked at 144/148, 0/28; retail hoists the callback `lw $v1,0x64` into the first bnel slot and leaves nops in both the beqz and jalr slots (a0 move sits between), which the baseline never reproduces. */
/* 4 November 2026 follow-up: nonmatching, not linked. The actual head-cache
 * store occurs once in the entry branch slot, using the getter's v0; the
 * loop backedge enters at the current-node state test. Do not add a cache
 * store per iteration. The void callback view agrees with current RAC1's
 * Moby update API. A real one-pass callback group, the same group with -g,
 * and a stored signed32 callback-address view all remain 144/148 bytes,
 * 0/28 USA: callback allocation and null-branch scheduling still differ.
 * Those probes are preserved privately; the pointer-based baseline below
 * retains its historical measurement. Corrected only its scope name here.
 */
/* 2 November 2026, remaining-function review: nonmatching; no linked credit.
 * Profile: -O2 -G8 -ffunction-sections.
 * US check: 144/148 bytes, 0/28 placements.
 * Fresh retail disproves the retained C flow: every flag/callback/delete test applies to current node and next is read at loop tail. Corrected body restores bltzl and both bnel delay-slot advances;144/148,0/28. Global-init/callback-local and for-loop forms tie. Remaining global-store source v0/s0, callback address v1/v0 and plain-vs-likely callback test/missing nop. Do not invent nonvoid callback return to occupy v0.
 */
#include "common.h"

typedef struct Node Node;

struct Node {
    unsigned char pad0[0x20];
    signed char flag20;
    unsigned char pad21[7];
    Node *next;
    unsigned char pad2c[8];
    unsigned short flags;
    unsigned char pad36[0x2E];
    void (*vfunc)(Node *);
};

extern Node *func_002A08A0(void);
extern void func_002A05A8(Node *);
extern void func_002A0F48(Node *);
extern Node *ref_002B6658_00 __attribute__((sda));

void func_002B6658(void)
{
    Node *t;
    void (*update)(Node *);
    ref_002B6658_00 = func_002A08A0();
    t = ref_002B6658_00;
    for (; t != 0; t = t->next) {
        if (t->flag20 >= 0) {
            if ((t->flags & 0x40) == 0)
                func_002A05A8(t);
            update = t->vfunc;
            if (update != 0)
                update(t);
            if ((t->flags & 4) == 0)
                func_002A0F48(t);
        }
    }
}
