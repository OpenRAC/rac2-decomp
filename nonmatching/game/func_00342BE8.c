/* 8 November 2026 (Sonnet round): re-measured 900/900, 2 words; permuter 25 min -j2 from the retained C: no candidate beat base 20. Nothing new beyond the listed store-order attempts. */
/* 8 November 2026 (compiler matrix, scratch only): retained C compiled with 10 EE cc1 builds at the same flags (-frac2-* dropped for non-local builds), our as: local 991111; decomp.me 2.9-ee-991111a, 991111-01, 991111b (= SN SDK 2.4's 991111); Sony 2.96-ee-001003-1; SN 2.95.2 v2.73a/v2.74, 2.95.3 v1.07/v1.14/v1.36 (no 990721 build available). No build gives retail's sw v0/sw a0 order at +0x230: every SN build keeps our order; stock 991111/2.96 change frame and spill code (920-924 bytes) and move li 1 between the stores. Not a compiler-build difference. */
/* 8 November 2026 (decomp-permuter round, 35 min, -j4, randomisation, seeded from the retained C, -O2 -G8): base score 20 (2 words); no candidate tied or beat it. */
/* 8 November 2026, region donors (v101/m8h): no matched function in us/pal/us2 stores a 16-byte stack rect in retail's +8,+4,+C,+0 order before an ldl/sdl copy (only 002DBC10's +C,+0,+4,+8); window +0x230 matches only func_002D3D88+0x170 over 3 generic insns. Nothing to transcribe. */
/* 8 November 2026 (round 12, local cc1): still 2 words. One local shared by 63 and 340 gives retail's store order y0,x1,y1,x0,flag (li 340 waits on the y0 store by anti-dependence), but 63/340 then share a0 and li 63 takes the delay slot (about 8 rows). 63 and 1 in one local (retail's v1 reuse): all 60 orders tie or worse. Flag as a field of a {clip, flag} state: its store gets only an output dependence on the copy, which mips ADJUST_COST makes cost 0, so li 1 stays one priority below li 340. Width local inside the block with y1 in a group, pointer pair (&clip.x1)[0]/[2], const width: no better. */
/* 8 November 2026 (re-measure, master compiler with default set-side sticky volatile and the mtc1 hazard-nop fix): retained C still 900/900, 0/28, 2 words (+0x230/+0x234 x1/y1 store swap); it must sit in a -G8 unit (src/game/003427B0-selection-g8.c; the -G0 parent gives 924 bytes). sched1 block: t1 load+li63, t2 y0+li340, t3 y1+sub, t4 x1+li1, t5 x0, t6 flag, t7 movstr; retail needs x1 before y1 in sched1. Width read into its own local before the if: x1 is stored first but the sub moves ahead of y0 and the width takes v1 (7 rows); reusing `first` for it reallocates s0/s1. No donor in rac1/rac4. -Wa,--r5900-la-addend=sn does not touch this block. */
/* 8 November 2026 (REG_EQUIV round): local-alloc/regclass/reload1 equivalence code equals upstream 2.95.2 (update_equiv_regs, no_equiv, the REG_EQUIV REG_LIVE_LENGTH *= 2); SN 2.95.2 v2.73a gives the same REG_EQUIV notes, register stats and dispositions as ours here. Env probes (EE 991111 note test, MEM equiv for multi-block pseudos, no *= 2, replace in one block, move init in loops) give 2/2/8/2/2 words (multi-block MEM equiv does not move the width load). Sweep changes 197/602/3181/182/0 matched units. */
/* 8 November 2026 (round 9, rank_for_schedule): base 900/900, 2 differing words (retained C, recorded flags). rank_for_schedule is identical in GCC 2.95/2.95.2/2.95.3 and EE 991111/991111b; SN 2.95.2 v2.73a makes the same tie choice where its output is comparable. Env probes (sched1/sched2/both): reg weight swapped/clamped/dropped/after class/positive-or-negative only, class dropped/reversed, dependent count reversed/dropped/data-only/clamped, LUID reversed, INSN_UID ties, no birthing boost: none improves any of the nine cluster targets; forced on, every variant changes 6-7124 of 8761 matched units. Hypothesis falsified. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 900/900, 2 rows with the retained C (clip stores y0,y1,x1,x0 vs retail y0,x1,y1,x0); 4 rows with func_003427C0's real prototype. No EE GCC build reproduces retail's order. */
/* 6 November 2026, decomp-permuter (40 min, 3 threads, --stack-diffs, retail-byte scorer): no candidate beat the base score 20 (2 rows); best rule-compliant result is the retained C. Setup: /tmp/claude-1000/-home-lynder063-rac2-decomp/lead/work/perm. */
/* 6 November 2026 (round 11c, prototype audit): the note's func_003427C0(char *, float, float, float, float, int) is a false prototype; the real one is (void *unused, int limit, float, float, float, float) at src/game/003427B0-fade.c:8. With the real prototype and call order (object, D_001AE1D4, low, y, high, D_001AE1D0) the first call loads a1 before f15: 4 real rows (best stays 2, but only with the false order). A scale temporary for D_001AE1D0 also gives 4. Other callees agree with src. */
/* 6 November 2026, round 11b: still 2 words (y1/x1 store swap). sched1 trace: li 340 (p5) always takes t2 ALU (li 1 only p3), so y1 store is ready at t3 and beats x0 by weight; x1 store cannot be ready before t4. Tied or worse: rotated store orders (x1,y1,x0,y0 = 2 words), 85 sampled orders with 63/340 in own variables (best 2 words, many 6-16), one temp reused for width and 340 (x1 before y1 but width/340 share a register: 9 words), group inside the block (aligns .L00342E4C, 86 rows), -fno-schedule-insns (130+ rows). */
/* 6 November 2026, Antigravity worker: 900/900 bytes, 0/28 places, exactly 2 real instructions swapped at +0x230/+0x234 (sw $a0, 0x2C($sp) vs retail sw $v0, 0x24($sp)). In-depth Haifa scheduler trace confirms: load latency of 2 cycles on screenWidthGP prevents width - 1 from executing before clock 3 ALU, so clip.x1 store is unready until clock 4 MEM. At clock 2 ALU, li 340 (prio 5 to movstrsi) beats li 1 (prio 3 to standalone store D_001B23C0), making clip.y1 store ready at clock 3 MEM where it issues. In sched2, ready list at clock 4 has both clip.x1 and clip.y1 stores tied on priority/dependencies/class; tie-breaker INSN_LUID(tmp) - INSN_LUID(tmp2) stably preserves sched1 order. Tested: temporary variable reuse (first/second/texture/index), pointer/array indexing, arithmetic dependencies, comma chains, and 25 scheduling/optimization flags (-fno-sched-interblock, -fno-schedule-insns2, -fno-expensive-optimizations, etc.); all tie at [40, 44, 36, 32] or regress. */
/* 6 November 2026, Codex follow-up: best C unchanged, 900/900 bytes,
 * 0/28 places in USA v1.01, PAL and USA v2.00 after check.py --diff rechecks.
 * Byte-addressed clip-field writes, paired-axis/nested-axis rectangle layouts,
 * switch/goto guards and second/texture scalar reuse still tie at two words.
 * An inline rectangle-return constructor gives 940 bytes for all 24 argument
 * orders. Groups spanning colour writes/initialization give 904 bytes; grouping
 * only the clipping call gives 900 bytes but eight real instruction differences.
 * -malign-loops=2 removes the required nop at +0xB4: control and all 21 contiguous
 * initialization groups are 896 bytes, so it cannot fix the group's extra nop.
 * Reusing first for nonzero bounds changes 37-42 real instructions. No source
 * improved the +0x230/+0x234 store swap; no linked build was run.
 */
/* 6 November 2026, round 9: still 2 words. sched1 dumps: the x0 store (p4, weight 0) is ready at t1, so retail's order needs a fifth weight -1 store in the t3 memory slot (the flag store, which only reaches p3). Tied: all 120 orders with the flag as a field of a 20-byte state at D_001B23B0 (also with the copy before the flag store), flag `++`/`+= 1`, `y1 = y0 + 277`, inner-scope clip, inline field/copy helpers (use a $s address register), volatile width (no new deps), and -frac2-qcopy(-barrier), -g, -fno-expensive-optimizations, -fstrict-aliasing, -fno-gcse, -fno-sched-interblock. */
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
