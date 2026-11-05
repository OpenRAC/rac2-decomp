/* 5 November 2026 (w-c4): dumps show sched2 (not loop.c or sched1) lifts the hoisted %hi(D_001A7578) above the volatile sd: with both schedulers off cc1 gives retail's sd, b, lui $s0 order; RAC1's store order (sentinel before callback fn) is byte-neutral; a NOT_SDA non-volatile long splits through a GPR; -mno-split-addresses keeps the macro sd but loses the hoisted lui (la in the loop). RAC1's compiled 989snd shows the same sd; move; b; lui shape because its lui reuses a register a preceding store reads (anti-dependence); here nothing orders it. Moving the callback-data store earlier in the source (d,a,c,m / a,d,c,m / a,c,d,m) puts the lui after the sd, but the sentinel sw then sinks into the b delay slot; no order gives both. The load/store anti-dependence lever (func_0033A520) does not apply: the lui has no memory operand. */
/* 5 November 2026 (w-c4): in the -g8 sibling with `unsigned int D_001A7180` (cast at the call) only the hoisted lui $s0 differs: sched2 issues it at t=3 with the sentinel sw (alu slot free), before the volatile sd. A `msg = D_001A7578` local after the sd puts addiu $s0 (full address) in the b slot, 236 bytes, addressing wrong. In the sdk unit the frame is 0x50 and no $gp. */
/* sol-low v0268: rechecked with the pinned v2 toolchain, 0/1 boot places.
 * -fno-schedule-insns is byte-neutral. Giving the message a complete extent
 * removes s0 and changes the loop; retain the closest 236/236-byte form below.
 */
/* sol-high, b0264: USA v1.01 boot, game -O2 -G8 -ffunction-sections.
 * 236/236 bytes, 0/1 places. The entry correction to 0x001325E8 is
 * already in the current catalogue. This replaces the stale 228-byte draft.
 * The callback-data scalar is volatile, as in current RAC1 989snd, which
 * keeps its absolute doubleword store out of the branch delay slot.
 * Remaining: the message-address LUI is hoisted before that store instead
 * of occupying the branch delay slot. The rest of the body agrees.
 * Volatile sentinel, -fno-sched-spec, and sharing the matched BankLoadAsync
 * unit do not close this scheduling difference. SDK changes frame/GP/calls.
 * Reopen with a qualified address-lifetime/scheduling remedy.
 * All required declarations are below. Compile in a -g8.c sibling.
 */
#include "common.h"
extern int D_001A74C8 __attribute__((sda));
extern int D_001A7488 __attribute__((sda));
extern int D_001A74F8 __attribute__((sda));
extern int D_001A74D0 __attribute__((sda));
extern int D_001A71C0 MACRO_ADDR;
extern unsigned int D_001A7180 MACRO_ADDR;
extern volatile long D_001A74D8 MACRO_ADDR;
extern int D_001A7140 MACRO_ADDR;
extern char D_001A76F8[], D_001A7578[];
extern void func_00115D48(const void *, ...);
extern void func_00132028(void);
extern void func_0011AEA0(int);
extern int func_0011D810(const void *);
extern int func_0011D620(const void *, int, int, int *, int, unsigned int *, int, int, int);
extern int D_001A71C4 MACRO_ADDR;
extern char D_001A7600[], D_001A7630[];
extern int func_00133580(int);
void func_001325E0(int a, int c, long d) {
    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 != 0) return;
        func_00115D48(D_001A76F8);
        return;
    }
    D_001A71C0 = a;
    D_001A74D0 = c;
    D_001A7180 = -1u;
    D_001A74D8 = d;
    while (func_0011D810(&D_001A7140)) {
        if (D_001A74F8 == 0) func_00115D48(D_001A7578);
        func_00132028();
        func_0011AEA0(0);
    }
    D_001A74C8 = 1;
    func_0011D620(&D_001A7140, 0x57, 1, &D_001A71C0, 4, &D_001A7180, 4, 0, 0);
}
