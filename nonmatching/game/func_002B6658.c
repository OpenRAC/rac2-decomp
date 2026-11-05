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
