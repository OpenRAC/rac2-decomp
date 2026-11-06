/* 6 November 2026, lead: the only real difference is the order of two stack stores into clip: retail y0, x1, y1, x0; ours y0, y1, x1, x0. Direct stores to menuClipGP (864 B), loading screenWidthGP (or width-1) into a local before the if (7-12 rows), x1 written last, and struct initializers / compound literal (932-964 B) all fail. */
/* 6 November 2026: current game compiler, -O2 -G8 -ffunction-sections:
 * 900/900 bytes, 0/28 places in each release; only the +0x230/+0x234 stores
 * differ (sw $a0, 0x2C($sp) vs retail sw $v0, 0x24($sp)).
 * Detailed scheduler analysis shows:
 * - All 120 permutations of the 5 statements in `if (D_001B23C0 == 0)` tie at 2 or 5 diffs.
 *   Haifa sched1 schedules independent statements by critical-path priority:
 *   screenWidthGP load (257, latency 2) delays `screenWidth - 1` (259) to clock 3, so `clip.x1` (261)
 *   is not ready until clock 4. Meanwhile, 340 (264) issues at clock 2, so `clip.y1` (266, prio 4,
 *   weight -1) issues at clock 3 ahead of 261.
 * - In sched2, ready list at t=4 contains both 261 and 266; tie-breaker INSN_LUID preserves
 *   sched1 order.
 * - Grouping menuClipGP and D_001B23C0 into a unified struct MenuClipState increases flag priority
 *   from 3 to 4, but cannot beat 264's priority of 5 (cost to 277 struct copy).
 * - Hoisting width load outside the block moves the load before bnez and yields 6 diffs.
 * - Permuting all 24 colour word store orders ties at 2 diffs or degrades up to 10 diffs.
 * - Nonempty do-while(0) groups introduce a .p2align 3 nop before unaligned .L00342E4C (904 bytes).
 * Retained C is unchanged.
 */
/* 5 November 2026: retained reconstruction, not linked or counted.
 * Retain func_0028EA58 as void with its real colour pointer and unsigned alpha packing.
 * The last bounded checks remain 900/900 bytes, 0/28 USA places: only clip.x1 and clip.y1 stores swap.
 * Complete screen-size views, captured width, builtin/byte-view copies, complete-owner stores and equivalent zero-to-initialized flag transitions all tie.
 * Do not repeat store permutations or add volatile stack fields.
 * Earlier measurements below describe earlier sources or toolchains.
 */
#include "common.h"
/* 3 November 2026 (opus, v2198): still 2 words. Ranking sched1 by hand (priority, then INSN_REG_WEIGHT, class,
 * depcount, luid) shows retail needs sched1 order 264<261<269 and 256<266<249. With the width load (252, p7, latency 2)
 * in the block, y1's store (266, p4, weight 0) always takes t3, before li 1 (269, p3, weight +1). Only a width pseudo
 * set outside the block, with the load put back in front of 254 after sched1, gives retail's order. update_equiv_regs
 * only adds a MEM REG_EQUIV for a single-block pseudo, so reload can't do that for a global. Reopen with a source
 * shape that changes 266's weight or the flag store's priority. */
/* 1 November 2026 (closer a3): sched2 keeps sched1's order on ties, so retail's sched1 had x1's store before y1's: its
 * t3 memory slot stayed empty or y1's li came later, where here 266 goes in at t3. Aggregate initialisers are 32 bytes
 * longer; -fno-sched-interblock, -g, -frac2-hazard-labels and -fno-sched-spec tie. */
/* 1 November 2026: 2 words (sw 0x24 / sw 0x2C in the reset block). The colours through a char view
 * (MenuColourQuad stores are MEM_IN_STRUCT, so the D_001B23C0 load passed them): 19 to 2. Retail's sched1
 * issues the flag's constant at t3 ahead of clip.y1's store; all 120 orders of the block tie, also with the flag
 * as a field of the clip state at D_001B23B0 + 0x10 (priority 3 against 4). */
/* GPT-6.1 Sol (high), pinned game compiler, -O2 -G8 -ffunction-sections.
 * Best check: 900/900 bytes, frame 0xB0, 0/28 placements in USA v1.01,
 * PAL and USA v2.00. Nineteen instruction differences (relocation operands
 * excluded diagnostically); the first is at +0x1C8. These are the colour-word
 * loads/updates/stores, the initialization-flag load and branch slot, and
 * the order of the clip.x1/clip.y1 stores. No linked build was run.
 * A fully typed MenuList recovers the invariant ids base and saved registers.
 * The explicit SDATA views preserve the complete 16-byte clip rectangle
 * while reproducing its GP copy destination and ordinary absolute field reads.
 * The width view expresses the GP initialization read and absolute reset read.
 * The alpha helper's integer/FP interleaving preserves each EE register bank
 * and fixes only its first call's load order. Retained source uses that EE ABI.
 * Preloaded colours, scalar result temporaries, named fields, a union view,
 * and an inline scalar alpha helper tie; bitfield alpha emits byte stores.
 * Disabling sched1 regresses. Reopen with a measured colour storage/access
 * model that explains the remaining schedule; do not add volatile stack fields.
 * All required types and declarations follow.
 */
#include "common.h"
typedef struct { float x, y; } MenuListPosition;
typedef struct { unsigned int values[4]; } MenuColourQuad;
typedef struct { int x0, x1, y0, y1; } MenuClipRectangle;
extern void func_00343068(MenuListPosition **);
extern int func_003427C0(char *, float, float, float, float, int);
extern unsigned char D_00139568[], D_00239BA0[];
extern MenuColourQuad D_001AE1D8, D_001AE1E8;
extern float D_001AE1D0 __attribute__((sda));
extern int D_001AE1D4 __attribute__((sda));
extern int D_001B23C0 __attribute__((sda));
extern MenuClipRectangle D_001B23B0 MACRO_ADDR;
extern MenuClipRectangle menuClipGP SDATA(D_001B23B0);
extern int D_001A7340 MACRO_ADDR, D_001A7344 MACRO_ADDR;
extern int screenWidthGP SDATA(D_001A7340);
extern void func_002FC620(int, int, int, int);
extern int func_0028E588(int, int);
extern void func_0028EA58(int, int, int, int, int, int *);


typedef struct {
    MenuListPosition *position;
    float iconSize, unused08, rowHeight;
    int count, selected, state, backward, firstVisible, lastVisible;
    int ids[25];
    void *allocation;
    int scrollOffset, frames;
} MenuList;

void func_00342BE8(MenuList *object)
{
    float high, low, current;
    int index, first, second, texture;
    MenuColourQuad normal, alternate;
    char *colours;
    MenuClipRectangle clip;
    unsigned char *entry;
    func_00343068(&object->position);
    low = object->position->y + object->rowHeight * -4.0f;
    high = object->position->y + object->iconSize * 0.5f;
    for (index = object->firstVisible;
            index <= object->lastVisible && object->count; index++) {
        normal = D_001AE1D8;
        alternate = D_001AE1E8;
        entry = D_00239BA0 + D_00139568[object->ids[object->selected + index]] * 224;
        colours = (char *)&normal;
        if (*(int *)entry && entry[4]) colours = (char *)&alternate;
        current = (float)index;
        first = func_003427C0((char *)object, low,
                object->position->y + object->rowHeight * current + (float)object->scrollOffset,
                high, D_001AE1D0, D_001AE1D4);
        second = func_003427C0((char *)object, low,
                object->position->y + object->rowHeight * current + object->iconSize + (float)object->scrollOffset,
                high, D_001AE1D0, D_001AE1D4);
        *(unsigned int *)(colours + 0) = (*(unsigned int *)(colours + 0) & 0xFFFFFF) | ((unsigned int)first << 24);
        *(unsigned int *)(colours + 4) = (*(unsigned int *)(colours + 4) & 0xFFFFFF) | ((unsigned int)first << 24);
        *(unsigned int *)(colours + 8) = (*(unsigned int *)(colours + 8) & 0xFFFFFF) | ((unsigned int)second << 24);
        *(unsigned int *)(colours + 12) = (*(unsigned int *)(colours + 12) & 0xFFFFFF) | ((unsigned int)second << 24);
        if (D_001B23C0 == 0) {
            clip.x0 = 0;
            clip.x1 = screenWidthGP - 1;
            clip.y0 = 63;
            clip.y1 = 340;
            D_001B23C0 = 1;
            menuClipGP = clip;
        }
        func_002FC620(D_001B23B0.x0, D_001B23B0.x1, D_001B23B0.y0, D_001B23B0.y1);
        entry = D_00239BA0 + D_00139568[object->ids[object->selected + index]] * 224;
        texture = func_0028E588(*(unsigned short *)(entry + 0x3C), 0);
        func_0028EA58(texture, (int)object->position->x,
                (int)(object->position->y + object->rowHeight * current + (float)object->scrollOffset),
                (int)object->iconSize, (int)object->iconSize, (int *)colours);
        func_002FC620(0, D_001A7340 - 1, 0, D_001A7344 - 1);
    }
}
