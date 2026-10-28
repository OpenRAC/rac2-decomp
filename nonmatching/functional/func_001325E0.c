/* functional: high. Same reads, writes and calls in the same order as retail; only instruction scheduling (store order at the loop entry) and register use differ. */
/* from src/core/00131780-g8.c: the catalogue row is eight bytes too long.
 *
 * func_001325E0's row (0x001325E0, 244 bytes) opens with
 *
 *     addiu $sp,$sp,0x20 ; nop
 *
 * that belongs to no function: a linker remnant of the 989snd unit, the kind
 * rac1-decomp splits off as core_text/func_0012E1B8, right before its
 * cmd-0x57 wrapper func_0012E1C8 (rac1-decomp src/core/989snd.c), which is
 * the function this row is. The remnant is dead-stripped code, not part of
 * the function, and no C emits a stack-pointer increase at function entry, so
 * the row as it stands cannot be matched from C. A tools/levels.py split (the
 * row starts at 0x001325E8, 236 bytes) unblocks it.
 *
 * The C below is the function itself: 228 bytes against retail's 236. What
 * agrees is the whole shape - the 0x20 frame, the $s0 and $ra saves, the
 * branch out of the "pending" path, the four stores into D_001A71C0,
 * D_001A74D0, D_001A7180 and D_001A74D8, the -1 sentinel materialised as
 * `lui 0xFFFF` + `ori 0xFFFF`, the wait loop (the busy flag loaded into the
 * back edge's delay slot, the pump and the message under it, then
 * func_0011D810), the ninth argument of func_0011D620 on the stack at
 * 0x0($sp), and the epilogue. What is left is two instructions of scheduling:
 * retail keeps the four stores (and three `lui $at`) before the branch into
 * the loop, this cc1 sinks the last store into the branch's delay slot and
 * reuses $at, and the two stores after the loop come out in the other order.
 *
 * Unit: the -g8 sibling (the game compiler at -O2 -G8 -ffunction-sections);
 * the small globals need __attribute__((sda)) to come out $gp-relative.
 * GP is 0x001AEFF0: -0x7B28 is D_001A74C8, -0x7B68 is D_001A7488, -0x7AF8
 * is D_001A74F8 and -0x7B20 is D_001A74D0.
 *
 * Verified: compiled with the unit's own flags and compared with retail at
 * 0x001325E8: 228 of 236 bytes, the first difference at +0x1c (the $gp
 * offsets, which the linker fills in).
 */

extern int D_001A74C8 __attribute__((sda));   /* gp - 0x7B28 */
extern int D_001A7488 __attribute__((sda));   /* gp - 0x7B68 */
extern int D_001A74F8 __attribute__((sda));   /* gp - 0x7AF8 */
extern int D_001A74D0;
extern int D_001A71C0;
extern unsigned int D_001A7180;
extern long long D_001A74D8;
extern int D_001A7140;
extern char D_001A76F8[];
extern char D_001A7578[];

extern void func_00115D48(char *);
extern void func_00132028(void);
extern void func_0011AEA0(int);
extern int func_0011D810(int);
extern void func_0011D620(int, int, int, int, int, int, int, int, int);

void func_001325E0(int arg0, int arg1, long long arg2) {
    D_001A7488 = 0;
    if (D_001A74C8 != 0) {
        if (D_001A74F8 != 0) {
            return;
        }
        func_00115D48(D_001A76F8);
        return;
    } else {
        D_001A71C0 = arg0;
        D_001A74D0 = arg1;
        D_001A7180 = 0xFFFFFFFFu;
        D_001A74D8 = arg2;
        while (func_0011D810((int)&D_001A7140) != 0) {
            if (D_001A74F8 == 0) {
                func_00115D48(D_001A7578);
            }
            func_00132028();
            func_0011AEA0(0);
        }
        D_001A74C8 = 1;
        func_0011D620((int)&D_001A7140, 0x57, 1, (int)&D_001A71C0, 4, (int)&D_001A7180, 4, 0, 0);
    }
}
