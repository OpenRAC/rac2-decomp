/* 9 November 2026 (o126, L11/L02 idioms): 19 -> 13 masked positions (656/656, check.py us 0/1). New in the C below: a set-once `buf = buffer;` (owner: set-once constant locals) used only by the first sprintf fixes the i/buffer s3/s4 swap (sweep of 1-2 pointer locals x use sets x 6 orders, 120 variants; 13 is the floor). Left: buffer addiu after the key copy (sched2 c31: movstr prio 2 beats the addiu prio 1), the first sprintf rematerialises addiu a0,sp,0x10, and draw 2's ori/f15 (sched2 c25 picks ori beside f14; the LOOP_END before cvt is the barrier head). Interleaved func_00300A00(char *, float, int, ...) prototype: no change in either draw (prototype kept as src). Groups moved in draw 2 (23-37), colour as set-once local (19), label_y/label_y2 swaps (13-22), all 12 -frac2-* switches + -fno-sched-interblock: no change. */
/* 9 November 2026 (o86, dump-driven): 656/656, 21 -> 19 masked positions (65 rows). sched2: retail's i = 0 jal slot
 * and s7 = 1 after the call need no loop note between the draw-2 call and i = 0 and a LOOP_BEG before one = 1; a
 * LOOP_END before the for's entry test ends the cse1 block (cse.c:8596), the i<4 test survives gcse, PRE stops
 * hoisting buffer/walks (116 rows). Body: draw 2 ungrouped, `i = 0;` then `do { one = 1; } while (0);`, loop as
 * do { ...; i++; } while (i < 4) (no entry test). Left: (1) buffer addiu after the key copy: lui v0 is the barrier head
 * after the group's LOOP_END; one group around one = 1 AND the loop puts it right (one = 1 head) but doubles loop
 * refs: shift 9/32 beats x 6/19 (floor_log2) and i 13/114 < buffer 11/53 (25 positions). (2) i/buffer s3/s4:
 * global-alloc i 9/114 = .237 < buffer 7/52 = .269; retail needs i in (.269, keyptr 7/49 = .286): len <= 100 or 10 refs
 * at len <= 111. (3) draw-2 ori/f15 sched2 cycle order. 6 check.py runs. */
/* 9 November 2026, Codex follow-up: 45 new C variants compiled and checked in the
 * existing rac2-gnu container, game -O2 -G0 -ffunction-sections with
 * -Wa,--r5900-la-addend=sn; USA v1.01, one Endako placement. Baseline remains
 * 656/656 bytes, 21 differing instruction positions with relocation fields
 * masked; tools/check.py: "03_endako: instruction at +0xf0 differs", 0/1.
 * Tested five local-data shapes (plain, key-record wrapper, 2x2 key table,
 * buffer-record wrapper, const keys plus buffer wrapper) against eight loop
 * forms (signed <4, !=4, <=3, do/while, unsigned !=4, long !=4, explicit break,
 * increment by one), excluding the baseline: 39 variants. Record wrappers
 * and const keys tie; !=4/do/while/explicit-break forms give 25 positions;
 * long indices give 688 bytes, and the 2x2 table gives 680-732 bytes.
 * Six integer-parameter orders of an inline real formatting helper all give
 * 668 bytes. None improves the retained source. These are instruction-position
 * counts, not the historical aligned-diff row counts. The draw-2 argument
 * order, loop preheader and i/buffer register roles still need an independently
 * supported source/scheduling witness. No linked build; marker stays assembly.
 */
/* 9 November 2026, Codex lifetime controls: current compiler, -O2 -G0
 * -ffunction-sections -Wa,--r5900-la-addend=sn; 656/656 bytes, USA 0/1,
 * first difference +0xF0, 21 word-aligned differences masking only relocation
 * fields (includes s3/s4 uses). Earlier index initialization, index assignment
 * after draw 2 inside its outer group, and moving keys/buffer/index before the
 * headings give 664 bytes. Do-while traversal and const local keys emit the
 * baseline size and difference count. Retained body unchanged; no linked build.
 */
/* 9 November 2026 (Sonnet round s45, owner ruling 2026-11-09): label_y2 (label_y with ONE handle test, allowed) on the second title draw only: quick scorer 23 -> 21 rows (68 -> 66 unmasked words), no match. First call 30, both 28; the other one-test forms tie. Body below carries it. */
/* 8 November 2026 (Sonnet round s33, lesson 49): x/c/d are fake but inlining them in draw 2 (no group) gives the same 23 quick-scorer rows; a `zero` local for both draws 150; shift declared after label/split 23; one = 1 after the group 23; for (i = 0 ...) 23. No change from the retained C. */
/* 8 November 2026 (Sonnet round s23): fresh C from retail asm (plain round_y helper, early return, plain for, no groups) is 668 bytes / 153 rows (vs retained 23 on the quick scorer): the early-return form hoists the key copy above the draws and the 0.5f lands in $f22; plain calls lose the group barriers. A scripted lesson-48 sweep (every single statement moved 1..3 places inside same-indent runs, 58 variants) found no variant below the retained C (best tie). Retained C unchanged. */
/* 8 November 2026 (compiler matrix, scratch only): retained C compiled with 10 EE cc1 builds at the same flags (-frac2-* dropped for non-local builds), our as: local 991111; decomp.me 2.9-ee-991111a, 991111-01, 991111b (= SN SDK 2.4's 991111); Sony 2.96-ee-001003-1; SN 2.95.2 v2.73a/v2.74, 2.95.3 v1.07/v1.14/v1.36 (no 990721 build available). No build reproduces retail in any of the 5 clusters: SN builds give our exact 656-byte order in all; stock 991111 differs only in cluster 1 (not retail either); 2.96 is 652 bytes. Not a compiler-build difference. */
/* 8 November 2026, round 15 (master compiler, ~28 check.py runs): 656/656 bytes, 0/1 places; aligned
 * masked diff 16 -> 15 rows. Profile now -O2 -G0 -ffunction-sections -Wa,--r5900-la-addend=sn (own
 * unit): one SDATA declaration of D_L03_001B0160 gives retail's mixed forms (.x walk addiu s5,$gp; .y
 * walk lui/addiu s6 of D+4), so the second gp name is gone. `one = 1` set after the draw-2 call inside
 * its group and used for both loop compares puts the 1 in s7 (literal 1 with this profile: 16 rows).
 * Left: draw 2's lui a1 order, i = 0 in the jal slot, the key copy after i/1/buffer, i/buffer s3/s4 swap.
 * Analysis: retail's order fits a sched1-only barrier between the draw-2 call and the loop preheader
 * (a branch that jump2 removes before sched2): sched2 then lets i = 0 (lowest luid, no call dependence)
 * fill the stall before the jal and puts 1/buffer before the copy. The do-while group is a barrier in
 * both passes (loop notes); no group lets sched1 hoist the s6 init and 1 over the call (30 rows).
 * Measured, no better: no outer group (30); i = 0 at the end of either draw-2 group, with or without
 * `for (i = 0` (102-107: movables and .x/.y givs not reduced); dead tests on title after the call or
 * after i = 0 (30-34; title kept in s0); `one` as label_y's active in one or both draws (46/65);
 * do-while groups around the i == 1 if/else (97) or the label lookup (33: lifts keys walk, not i);
 * plain title rounding without label_y (44); -fno-schedule-insns (99).
 */
/* 7 November 2026, round 14: 656/656 bytes, 0/1 places; masked aligned diff 21 -> 15 rows.
 * (1) D_L03_001B0160 declared `extern struct MenuCoordinate D_L03_001B0160[] __attribute__((sda));`
 * (incomplete sda array, COMPILER-NOTES "tied absolute macro form"): the .y walk is now retail's
 * lui s6/addiu s6 pair and the key copy uses lui v0/addiu a2 with v1/a0, as retail. The y read is
 * plain D_L03_001B0160[i].y (no py pointer; same score) through screen_coord(mode, value, offset),
 * the sibling helper shape (L10_004239A0-g8.c). (2) Both title draws pass a literal 0.0f as z, no z
 * local: draw 1 is now exact. Left (15): draw 2's lui a1 issued before the f12 load; i = 0, the
 * constant 1 and the buffer address stay after the key copy (retail: i = 0 in the jal slot, s7 and
 * the buffer between lui v0 and addiu a2); i and the buffer swap s3/s4. The swap is global-alloc
 * priority: i 9 refs over ~108-114 live insns vs the buffer 7 refs over ~54 (needs i <= 102 or one
 * more in-loop ref of i). Measured, no better: L10-style plain calls with label_y as an argument
 * (20 with sda: draw 1 exact, draw 2 and the preheader cross the call); groups around the tail,
 * the loop or each draw (24-48); every x/c/d placement in draw 2 (15 floor); all orders of the
 * py/keys/buffer/i declarations and `int i = 0` (no change or 652 bytes); unsigned i, char buffer,
 * buffer pointer local, keys pointer walk, shift/label/x outside the loop, while loop, `+ i` for
 * `+ 1`, second i == 1 test (680/644 bytes); -fno-sched-interblock, -fmove-all-movables,
 * -frac2-hazard-labels (tie), -fno-gcse/-fno-rerun-loop-opt/-fno-strength-reduce (worse).
 */
/* 7 November 2026, label_y sweep: both title rows now use the accepted HUD label idiom,
 * row = (float)label_y(title, D_L03_001B0150, D_L03_001B3284, 0.5f, 1); (definition above the
 * function, mode D_L03_001B3280). Same -O2 -G0 profile, 656/656 bytes, 0/1 places; sweep-harness
 * masked aligned diff 28 -> 21 rows. The title draws are exact except z = 0.0f (mtc1 $zero,$f21),
 * issued one draw early; dropping the do-while groups gives more rows. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 656/656, 41 real differences (text-call argument scheduling and the key-copy/.y pointer setup). */
/* 7 November 2026, round 13: retained best C, USA v1.01 656/656 bytes, 0/1
 * places; -O2 -G0 -ffunction-sections. 41 differing instruction positions after
 * masking relocation fields (was 43). The .y walk now starts from its own
 * pointer, float *py = &D_L03_001B0160[0].y, declared before the key array:
 * the setup is lui/addiu of D_L03_001B0160+4 (no base+4 add) and the pseudo
 * order keeps i in s3 and the buffer in s4. Declared after the keys, or with
 * the assignment split from the declaration, i and the buffer swap (44).
 * Left: the .y high part is a separate local register (lui v1) scheduled
 * first, so the key copy uses a3/a0/a1 and the high/low pair is not the
 * retail lui s6/addiu s6 (retail needs it materialized at the copy point),
 * plus the text-call title move and zero placement (23). Measured, no better:
 * all 688 placements of title/row/x/c/d/zero before, inside or after the group
 * or as call arguments (best 43 on the old base, 41 on this one); one zero
 * variable at function, block or group level (43-49); a group around the .y
 * assignment (44); py at function or if-body start (72-88); `int i = 0` at
 * four places (41-46); inline draw helper (644 bytes). Analysis: the group end
 * is a scheduling barrier on the merged a0 = v0 copy, so title cannot rise as
 * in retail; plain calls drop the barrier and interleave the argument loads.
 */
/* Superseded 6 November 2026, round 10: retained best C, USA v1.01 656/656 bytes, 0/1
 * places; -O2 -G0 -ffunction-sections. 43 differing instruction positions after
 * masking relocation fields (was 49). Two inline helpers, as in matched
 * func_002CE5D0 (menu_screen_y): menu_round for the title row and
 * menu_screen_y(value, offset) with `if (flag == 1) return (int)(y + offset);`
 * for the loop. The loop body now matches, including the increments after
 * cvt.s.w and $f2 for the adjustment. Left: in both text calls the title move
 * (daddu a0,v0) and the int->float row conversion are placed differently and
 * zero is set too early (12 + 11 positions); the key copy uses a0/a1/a3 instead
 * of v1/a0/a2 and the .y pointer is base+4 instead of its own lui/addiu (20).
 * Measured, no better: calls written as arguments (lesson 28; 668 bytes
 * without the outer group, 54-60 with it); inline title-draw helper (73);
 * groups of title+row only (46), title outside the group (54); float-returning
 * round helper; int-offset helper (672 bytes); `int i = 0` before keys (48,
 * fixes i in the delay slot but swaps s3/s4); [][2] and pointer y views;
 * -fno-sched-interblock (tie), -fno-schedule-insns, -mno-split-addresses
 * (648 bytes); 40-step hill-climb over the group statement order (tie).
 */
/* 6 November 2026, round 10: retained best C, USA v1.01 656/656 bytes, 0/1
 * places; -O2 -G0 -ffunction-sections. 43 differing instruction positions after
 * masking relocation fields (was 49). Two inline helpers, as in matched
 * func_002CE5D0 (menu_screen_y): menu_round for the title row and
 * menu_screen_y(value, offset) with `if (flag == 1) return (int)(y + offset);`
 * for the loop. The loop body now matches, including the increments after
 * cvt.s.w and $f2 for the adjustment. Left: in both text calls the title move
 * (daddu a0,v0) and the int->float row conversion are placed differently and
 * zero is set too early (12 + 11 positions); the key copy uses a0/a1/a3 instead
 * of v1/a0/a2 and the .y pointer is base+4 instead of its own lui/addiu (20).
 * Measured, no better: calls written as arguments (lesson 28; 668 bytes
 * without the outer group, 54-60 with it); inline title-draw helper (73);
 * groups of title+row only (46), title outside the group (54); float-returning
 * round helper; int-offset helper (672 bytes); `int i = 0` before keys (48,
 * fixes i in the delay slot but swaps s3/s4); [][2] and pointer y views;
 * -fno-sched-interblock (tie), -fno-schedule-insns, -mno-split-addresses
 * (648 bytes); 40-step hill-climb over the group statement order (tie).
 */
/* Superseded 6 November 2026, Codex follow-up: retained best C, USA v1.01 656/656 bytes,
 * 0/1 places; -O2 -G0 -ffunction-sections. check.py: "03_endako: instruction at
 * +0x58 differs". There are 49 differing instruction positions after masking
 * only relocation fields, versus 60 for the previous retained C (the earlier
 * 92/102 line counts included unresolved relocation display differences).
 * Grouping the real title lookup and argument reads restores half in $f20 and
 * zero in $f21. An outer group around the second draw prevents part of the
 * loop preheader from crossing that draw. Remaining: zero is materialized too
 * early, title/coordinate argument moves and loads interleave differently,
 * key-array initialization and coordinate-pointer setup differ, and loop
 * increments occur between mfc1 and mtc1 rather than after cvt.s.w.
 * New measured controls: all 21 integer/FP-bank interleavings preserve the
 * physical call contract but tie or worsen; explicit rounded-int/float locals,
 * groups around lookup/conversion/argument-read intervals and nested groups
 * bottom out at this form. Adjacent independent x/c/d/zero assignment swaps
 * tie. Moving the actual loop increment between rounding/helper/draw steps
 * ties; grouping that increment adds four bytes. An explicit four-key memcpy
 * ties; initializing i before it gives 53 differences. A direct y-array view
 * fixes the base+4 expression but worsens scheduling by one position.
 * With this source, -frac2-sticky-volatile-refs, -fno-regmove and -g tie;
 * -fno-schedule-insns, -fno-schedule-insns2, -fno-gcse,
 * -fno-rerun-cse-after-loop and -fno-rerun-loop-opt worsen size or instructions.
 * No donor found by key/color constants in local RAC1/RAC4 sources. Next useful
 * evidence is the original text-argument conversion/call grouping or a compiler
 * scheduling witness; do not repeat the tied order/flag probes. No linked build.
 */
/* Superseded 6 November 2026, round 2: default -G0 profile, 656/656 bytes, 0/1 USA,
 * 92 diff lines (the previous form gave 102). Plain call arguments with literal 0.5f/0.0f
 * put half in $f20 before the first call as retail does; a group around the second text
 * call keeps the loop set-up (i, the constant 1, the coordinate pointers) after that call;
 * an unconditional (float)shift fixes the loop registers (i s3, shift s1, keys s2, buffer s4).
 * Left: half/zero swapped ($f21/$f20) once the group is in; in both text calls retail does
 * the whole row conversion before loading any other argument, here sched interleaves them;
 * retail's .y pointer is %hi/%lo(D_001B0164) where this forms base+4; loop increments sit
 * between mfc1 and mtc1. Measured, none closer: group around both calls or the first only
 * (668 bytes, extra $f22), group around the loop's row block (660), a `half` variable,
 * -ffast-math, -fno-schedule-insns, -fno-schedule-insns2 (652).
 */
/* Retained bounded near miss, 2026-10-28: default profile656/656 bytes.
 * Five forms: named half constant removes duplicated FPR and restores0xf0
 * frame; explicit row/zero/adjustment lifetimes and -fno-regmove tie the
 * remaining scheduling. -fno-schedule-insns and -fno-gcse reach652 bytes and
 * are not retained. First difference+0x4c is swapped persistenthalf/zero FPRs,
 * followed by independent argument setup hoisted across coordinate conversion.
 * Reopen with a measured genuine constant lifetime/scheduling witness.
 * Getter keeps its actual integer stored-address return; text drawing takes
 * an explicit pointer cast. Printer returnsint and is variadic. Font renderer
 * style is64-bit unsignedlong, and both ending wrappers returnint.
 * The actual local formatting capacity is128 bytes; its initialized text is
 * terminated by the verified sprintf-style helper before font consumption.
 * Four key words16 bytes and four coordinate pairs32 bytes are complete.
 */
#include "common.h"

struct MenuCoordinate { float x, y; };
extern unsigned char *D_L03_001A904C __attribute__((sda));
extern float D_L03_001B014C SDATA(D_L03_001B014C);
extern float D_L03_001B0150 SDATA(D_L03_001B0150);
extern float D_L03_001B0154 SDATA(D_L03_001B0154);
extern float D_L03_001B0158 SDATA(D_L03_001B0158);
extern struct MenuCoordinate D_L03_001B0160[] SDATA(D_L03_001B0160);
extern int D_L03_001B0140 SDATA(D_L03_001B0140);
extern int D_L03_001B3280 __attribute__((sda));
extern float D_L03_001B3284 __attribute__((sda));
extern char D_L03_001B0190[], D_L03_001B0198[];
extern unsigned char D_001A7A7C[] __attribute__((sda));
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);
extern int func_00283CF0(float);
extern int func_0027FB40(int, int, unsigned long, unsigned char *, int);
extern int func_L00_00443DF8(char *);
extern int func_L00_00443E18(char *);

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L03_001B3280;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L03_001B3280;
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}

static __inline__ int screen_coord(int mode, float value, float offset, int one)
{
    float scaled = value * D_L03_001B3284 + 0.5f;

    if (mode == one)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_L03_003C7018(void)
{
    if (D_L03_001A904C) {
        int one;
        int i;

        {
            char *title;
            float row, x, c, d;

            do {
                title = (char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc6);
                row = (float)label_y(title, D_L03_001B0150, D_L03_001B3284, 0.5f, 1);
                x = D_L03_001B014C;
                c = D_L03_001B0154;
                d = D_L03_001B0158;
            } while (0);
            func_00300A00(title, 0x60442d00, x, row, c, d, 0.0f);
        }
        {
            char *title;
            float row, x, c, d;

            do {
                title = (char *)func_00336D50(D_L03_001A904C + 0x8710, 0xc7);
                row = (float)label_y2(title, D_L03_001B0150, D_L03_001B3284, 0.5f, 1);
                x = D_L03_001B014C;
                c = D_L03_001B0154;
                d = D_L03_001B0158;
            } while (0);
            func_00300A00(title, 0x55f0c070, x, row, c, d, 0.0f);
        }
        i = 0;
        do {
            one = 1;
        } while (0);
        {
            int keys[4] = {11599,12116,12769,12770};
            unsigned char buffer[128];
            unsigned char *buf;
            buf = buffer;
            do {
                int shift = 5;
                int x;
                unsigned char *label = func_00288FB8(keys[i]);
                if (i == one) {
                    func_00115DA8((char *)buf, D_L03_001B0190, label, D_L03_001B0140 + 1);
                    shift = -4;
                } else {
                    func_00115DA8((char *)buffer, D_L03_001B0198, label);
                }
                x = func_00283CF0(D_L03_001B0160[i].x);
                func_0027FB40(x, func_00283CF0((float)screen_coord(D_L03_001B3280, D_L03_001B0160[i].y, (float)shift, one)), 0x80808080UL, buffer, 0x80);
                i++;
            } while (i < 4);
        }
        if (D_001A7A7C[0]) {
            func_L00_00443DF8((char *)D_L03_001A904C + 0x36f28);
            func_L00_00443E18((char *)D_L03_001A904C + 0x36f28);
        }
    }
    return 1;
}

