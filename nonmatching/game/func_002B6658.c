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
