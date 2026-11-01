/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* func_L23_0041B188 (748 bytes, 1 place: 23:0041B188) -- NEAR MISS, not integrated.
 * opus-1 (Claude Opus 5.5), task v1374, 2026-10-29.
 * Profile: -O2 -G8 -ffunction-sections (a <file>-g8.c unit of its own; L23_0041B188-g8.c gets the
 * profile from its name, no cflags line).  Uses qcopy from common.h.
 * Best check.py: 748/748 bytes, 0/1 places; exactly two words differ (+0x1BC, +0x1C4), in the
 * kind-2 mask read of the `step >= *list` path: retail `addu $v0,$v0,$v1 ; ld $a1,8($v0)`
 * (table base first), here `addu $v1,$v1,$v0 ; ld $a1,8($v1)` (scaled slot first).
 * What closed the rest (register allocation, the +0x8 save order and every branch):
 * - each branch has its own block-local `ids` (state + 0x230).  gcse's LCM inserts the join's
 *   `state + 0x230` at the end of each branch block; in the step < 0 block that is after the
 *   4190C8 call, so cse2's copy from a shared `slots` made that pseudo cross a call (flow's count
 *   for a multi-block pseudo is never lowered by sched1) and it took $s0, displacing state.  A
 *   block-local pseudo gets its count recomputed by sched1 once the copy moves above the call,
 *   so it lands in $t0/$v1 as in retail, and state/p3A0/flip/obj/obj+0x10/side/slots/table-hi
 *   fall into $s0..$s6 exactly;
 * - `*(int *)(ids + (idx << 2))` (char arithmetic, the idiom of func_L23_0041D0A0) gives retail's
 *   `addu slots, idx4` order; `ids[idx]` expands as MULT and is put first;
 * - the kind-2 mask through a local `masks` keeps the +8 as the ld displacement (with the symbol
 *   it folds into %lo(D+8)).
 * Remaining: cse's fold_rtx puts an operand with a known constant value second, so (plus masks x)
 * becomes (plus x masks) whatever the spelling, and local-alloc then ties the sum to x.  Retail's
 * order needs the table address in a register cse does not know as constant there (cf.
 * func_L23_00418FD0, where the base is reused after a call).  Tried: struct-array field, u64
 * index [1], masks set before the slot test (hoists the lui, worse).
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B14E4 __attribute__((sda));
extern float D_L23_001B14E8 __attribute__((sda));
extern float D_L23_001B1680 __attribute__((sda));
extern float D_L23_001B14DC __attribute__((sda));
extern float D_L23_001B1410 __attribute__((sda));
extern TI128 D_L23_001B38D0;
extern char D_L23_002595C8[];
extern int *D_L23_001FF300[];

extern void func_L23_00418650(char *, float);
extern float func_00282C48(float);
extern float func_00282E48(char *, char *);
extern void func_L23_004190C8(char *, u64, int, int);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);

void func_L23_0041B188(char *obj) {
    char *state = *(char **)(obj + 0x68);
    char *slots;
    int *list;
    TI128 vec;
    float x, mid, dev;
    int side, flip, step, slot;

    func_L23_00418650(state + 0x3A0, *(float *)(state + 0x588));
    mid = D_L23_001B14E4;
    x = *(float *)(state + 0x5B8);
    if (mid + D_L23_001B14E8 <= x || x <= mid - D_L23_001B14E8) {
        flip = 0;
        if (mid - D_L23_001B14E8 < x) {
            side = 3;
            dev = func_00282C48(x - mid);
            if (*(u32 *)(state + 0x5F0) >= 2) {
                flip = 1;
                *(short *)(state + 0x392) = -*(short *)(state + 0x392);
            }
            *(int *)(state + 0x5F0) = 1;
        } else {
            side = 2;
            dev = func_00282C48(x - mid);
            if (*(int *)(state + 0x5F0) != 0 && *(int *)(state + 0x5F0) != 2) {
                flip = 1;
                *(short *)(state + 0x392) = -*(short *)(state + 0x392);
            }
            *(int *)(state + 0x5F0) = 2;
        }
        if (flip != 0 || func_00282E48(obj + 0x10, state + 0x3A0) < D_L23_001B1680) {
            step = *(short *)(state + 0x396) + *(short *)(state + 0x392);
            if (step < 0) {
                char *ids = state + 0x230;

                func_L23_004190C8(obj, *(u64 *)(D_L23_002595C8 + (*(int *)(ids + (*(short *)(state + 0x394) << 2)) << 4)), side, 1);
            } else {
                char *ids = state + 0x230;

                slot = *(int *)(ids + (*(short *)(state + 0x394) << 2));
                list = D_L23_001FF300[slot];
                if (step >= *list) {
                    char *masks = D_L23_002595C8;

                    func_L23_004190C8(obj, *(u64 *)(masks + (slot << 4) + 8), side, 1);
                } else
                    *(short *)(state + 0x396) = step;
            }
            slots = state + 0x230;
            qcopy((state + 0x3A0) ,((char *)D_L23_001FF300[*(int *)(slots + (*(short *)(state + 0x394) << 2))] + *(short *)(state + 0x396) * 16 + 0x10));
            func_L23_00418650(state + 0x3A0, *(float *)(state + 0x588));
        }
        func_00282CF0((char *)&vec, state + 0x3A0, obj + 0x10);
        dev = dev * 0.0625f;
        if (D_L23_001B14DC < dev)
            dev = D_L23_001B14DC;
        else if (dev < D_L23_001B14DC * 0.05f)
            dev = D_L23_001B14DC * 0.05f;
        func_00282F20((char *)&vec, (char *)&vec, dev);
        qcopy(&D_L23_001B38D0,&vec);
        func_00282CC0(obj + 0x10, obj + 0x10, (char *)&vec);
        func_L23_00418650(obj + 0x10, *(float *)(state + 0x588));
    }
    D_L23_001B1410 = 1.0f;
}
