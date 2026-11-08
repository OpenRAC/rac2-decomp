/* 8 November 2026 (nominalsan, Opus 5.5): retained C below compiles to 1212 bytes (retail 1216), 0/27 USA,
 * with the default -O2 -G0 -ffunction-sections (-fmove-all-movables is no longer needed). Aligned against retail
 * with relocations, call targets and branch offsets masked, 303 of retail's 304 instructions agree; the one
 * missing is the backward bne's delay slot: retail steals `lui v0,%hi(wanted base)` from the loop top, this C
 * fills it with the colour `addu` (so everything after 0x376D48 sits 4 bytes early).
 * What moved it, each measured:
 * (1) `wanted` computed at its use, after the key test: its madd then has a same-block user (the load), haifa
 *     gives it priority 7 (imul 4 + load 2 + branch 1) and moves it up into the key block ahead of the key's
 *     addu (priority 5), so reload puts W and 28 in v0 and the v0 anti-dependence keeps retail's order in sched2;
 * (2) the colour read as `tbl + (off + 4)`: cse1 always puts a known constant second, so every `tbl + off`
 *     form comes out (off, tbl); this one is rebuilt later as retail's (tbl, off), and it also stops cse from
 *     reusing the key address, so the table's high part alone is hoisted and its low part stays in the loop;
 * (3) the row table read as `D_L00_0022F7C0 + 0x140 + idx*28` (rows inside the same menu block as `wanted`):
 *     the separate D_L00_0022F900 hoisted a one-insn high-part pseudo that local-alloc gave v0 before y's load;
 * (4) `j = 0` before the phony do/while(0) and `wanted` declared before `j`: global-alloc priority is
 *     floor_log2(refs)*refs/live_length; with j=0 one loop level up j and wanted tie at 1.5 (j 3*11/22, wanted
 *     2*6/8) and the tie goes to the lower pseudo, so wanted takes a2 and j a3 as retail (j=0 inside: j 1.64).
 * Remaining: with `top:` before the do, reorg's mostly_true_jump sees a label outside the loop and predicts the
 * bne not taken. Retail's prediction needs a NOTE_INSN_LOOP_BEG directly before `top`, but a do/while that
 * starts with its label is a real loop to loop.c (A4: 0/27, ~1040 bytes). As a probe only, `j=0; do { do { }
 * while(0); top: ... } while(0);` matches 27/27 in USA v1.01, PAL and v2.00 (tools/check.py): the inner loop
 * note stops loop.c's phony scan and precedes the label. Empty loops are excluded (docs/COMPILER-NOTES.md), so
 * it is not a match; `while(0){}` and `for(;0;){}` behave the same. Nonempty alternatives measured, no match:
 * the label and key load in their own group with the goto outside it (an invalid loop for loop.c), with or
 * without a group around the wanted computation (1116 bytes; the row loop's allocation changes too).
 * Later the same day, no match: why each condition holds. reorg (mostly_true_jump) returns -1 for a branch to a
 * label LABEL_OUTSIDE_LOOP_P (set by loop.c's mark_loop_jump when the jump's loop does not contain the label);
 * otherwise a NOTE_INSN_LOOP_BEG directly before the label gives 2 and an NE test 1. Ref counts are recomputed
 * per insn by note position just before local-alloc (recompute_reg_usage), so `j = 0` must precede the loop
 * note itself. loop.c skips a loop that is phony (first insn or label after LOOP_BEG is not a CODE_LABEL; a
 * nested LOOP_BEG stops that scan) or invalid (a jump into it from outside). Shapes with retail's control flow
 * and the backward goto outside the group (`j=0; do { top: ...; if(!key) goto done; j++; wanted=...; } while(0);
 * if(*wanted!=key) goto top; color=...; done:`, an invalid loop): 1136-1148 bytes; the colour block after the
 * loop end gets its own table address, which the row loop hoists (its high part then takes v0 before y), and a
 * madd whose use is past the loop end goes through LO (madd $zero; mflo). A per-iteration `tb` table pointer for
 * the colour, or the wanted load inside the group: 1132-1148. The label and branch at one level with smaller
 * groups (key load, wanted, both): 1080-1140. `__builtin_expect` on the bne: no effect (1212, as without).
 * Siblings (8 November): rac1-decomp's render_vendor_item_icon_strip_pass (src/game/ui/vendor.c, b4a462a)
 * has this function's scroll +-4 and `* 0x10202` pulse but no table search; rac1's lookups (Hud_GetIconIndex,
 * assign_moby_class_data) are `while (t[i].key != END && t[i].key != id) i++;`, and that idiom or a for/break
 * form here gives 1012-1044 bytes (loop.c hoists and reduces the search). RAC2's func_L00_00376600 (the menu
 * draw just before, matched with -g) confirms the rows at D_L00_0022F7C0+0x140 but has no search; -g changes
 * nothing here. No other RAC2 C uses D_L00_0028E9F0 or a goto key search.
 * Why the nonempty forms conflict: loop.c's scan_loop leaves a set in the loop when it follows a label and its
 * register is used in another block, which is what keeps the table's low part in the search (shared with the
 * colour block); cse1 stops at NOTE_INSN_LOOP_END, so that sharing needs the key load and the colour read in
 * one group; reorg needs the bne in a loop that contains `top`; retail's allocation (tbl > wanted > j) needs
 * `j = 0` one level shallower than the rest (at one depth: depth 3 gives tbl > j > wanted, 2 and 4 worse); and
 * a group that starts with its label is a real loop unless entered from outside, which puts the bne outside
 * it. With a `tb` pointer set in the group for the colour (18 key/colour/pointer spellings, all 1132 bytes),
 * cse2 instead reuses the key address for the colour.
 * Next: an original construct that leaves a loop note right before `top` with no real insn, e.g. a real
 * inner loop that is optimised away or a debug macro of the original, and the evidence that it was there.
 */
/* 7 November 2026 (nominalsan, Opus 5.5): retained C below compiles to 1220/1216 bytes, 0/27 USA, with
 * -O2 -G0 -ffunction-sections -fmove-all-movables. Aligned against retail with relocation fields, $gp offsets
 * and call targets masked: 11 differing instructions, 1180/1216 bytes agree (the 1 November C: 38 and 1084).
 * What moved it, each measured on its own:
 * (1) the fade is a static inline helper, `fade(y+2)` and `fade(y+40)`, with y+2 written out at the two calls:
 *     its parameter gives retail's y+2 in s0 copied to s6, and the size becomes 1216;
 * (2) the row table without sda: next-i in fp and next-y on the stack, as retail;
 * (3) the colour search inside `do { j=0; top: ... } while(0)` (macro-shaped): flow counts the block as a loop
 *     (idx's use in the search weighs one more, so idx is allocated before colour and takes s2, colour s3, as
 *     retail), and loop.c skips it as phony (no label first), so the search keeps its integer index and its madd;
 * (4) the table address read once before the search (`tbl`): sched1 then issues the wanted madd first, and
 *     the search's registers become retail's for wanted (a2) and the key.
 * Remaining: retail has the table address as lui t0 before the search and addiu a1,t0 in each iteration;
 * here it is one lui/addiu pair before the loop (a3) plus a load-delay nop, and j is a1 where retail has a3;
 * y's load before the loop is v1, retail v0 (local-alloc gives v0 to the hoisted high part of the row table,
 * whose insns reload then drops). Same C with the colour table also without sda but no `tbl` (the address
 * split as retail, 1216 bytes): 18 differing instructions, 1156 bytes; there sched1 issues the madd last and
 * wanted takes v0. Why: haifa priority() counts only same-block dependents, so the madd (its one user, the
 * load of *wanted, is in the next block) has priority 0 and loses to j++ (no dependents, priority 1), while the
 * split address adds the lo_sum to the key chain; retail's order needs the madd ahead of j++ with the lo_sum in
 * the loop. A do/while(0) around the search head puts a loop note (a scheduling barrier) before the key branch
 * and does issue the madd early, but its result then goes to LO (madd $zero; mflo) or, with the rest in a
 * second do/while(0), gcse no longer hoists the table's lui and reorg annuls the branch (1224 bytes, 34).
 * Also no gain: j++ before the key test, the search statements in any order (cc1 gives one schedule),
 * -fno-sched-interblock/-fno-sched-spec on these shapes, y initialised in the for header after i.
 * Measured, no gain: the search as a real for/while loop (loop.c hoists the madd and
 * strength-reduces the colour pointer; 1224 bytes, 16), a separate label colour variable (1228), temporaries
 * for the call arguments, j++ placements, statement orders in the search, a single-flag sweep on these shapes
 * (the -frac2-* switches, -fno-sched-*, -fno-strength-reduce, -G8, -g, ...), and three decomp-permuter runs
 * on the earlier C (OpenRAC tools/permuter, rac2/ntsc, --no-asm-passes): 184,370 candidates found the second
 * colors[] site's b-first store order kept here; 181,369 and 771,671 (2 hours) found only an out-of-line
 * `inline` helper that changed the permuter's scoring, not the code, and a hoisted `ty = y + 2` that is not
 * this function.
 */
/* Closer C, 1 November 2026: -O2 -G0 -ffunction-sections -fmove-all-movables, 1212/1216, 43 rows. Retail's search keeps
 * its integer index, so it is a goto loop: loop.c reduces every do/while or for form. Left: retail recomputes the
 * entry address for the colour (addu v0,a1,a0; lw 4(v0)), idx/colour take s2/s3 the other way, i+1/y+56 swapped.
 * Closer C4: cse reuses the key address whichever way the sum is written; table base a1 and j a3 follow from that row.
 */
#include "common.h"
/* sol-high; USA v1.01, -O2 -G0 -ffunction-sections.
 * Best check: 1212/1216 bytes, 0 of 27 places match; no linked match.
 * Postincrement search removes the duplicated first table test, but strength
 * reduction turns it into a pointer walk. The compiler shares idx*28 across
 * row accesses (mult/addu instead of retail's two madd formations), swaps the
 * next-index/next-row saved and stack values, and schedules color stores
 * differently. A useful next experiment must retain the integer table index
 * and independent row-address formation without adding memory effects.
 * Required declarations are included below. Incomplete SDA arrays preserve
 * the measured absolute rematerialization in this G0 unit.
 */
extern float D_L00_001B25E0[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern int D_001A7340[] __attribute__((sda));
extern int D_001A7344[] __attribute__((sda));
typedef struct { int words[0x744/4]; } Menu705;
extern Menu705 D_L00_0022F7C0[];
typedef struct { int key; unsigned int color; } MenuColor;
extern MenuColor D_L00_0028E9F0[];
extern void func_002FC620(int, int, int, int);
extern int func_00282C30(int);
extern void func_00285548(int,int,int,int,int,int,unsigned int);
extern char *func_0028E588(int,int);
extern int func_0028EA58(char *,int,int,int,int,unsigned int *);
#define MW(o) (D_L00_0022F7C0[0].words[(o)/4])
#define MY(y) ((int)(D_L00_001B25E0[0]*(y)+0.5f)+(D_001A7B90[0]?4:0))
static __inline__ int fade(int v)
{
    double d=256.0f-(float)v;
    if(d<0.0) d=0.0-d;
    return 128-(int)(d*0.75);
}
void func_L00_003769C0(void)
{
    int y;
    int bottom, top;
    unsigned int pulse;
    unsigned int color;
    unsigned int colors[4];

    bottom=MY(382.0f);
    top=(int)(D_L00_001B25E0[0]*320.0f+0.5f);
    func_002FC620(58,456,top,bottom);
    if (MW(0x6c)<0) MW(0x6c)+=4;
    else if(MW(0x6c)>0) MW(0x6c)-=4;
    color=0xf0f0b0;
    pulse=(func_00282C30(((MW(4)<<2)&63)-32)+64)*0x10202;
    func_00285548(229,MY(325.0f),285,MY(381.0f),D_001A7340[0],D_001A7344[0],0x80000000|pulse);
    func_00285548(231,MY(327.0f),283,MY(379.0f),D_001A7340[0],D_001A7344[0],0x80442d00);
    y=MW(0x6c)-47;
    { int i;
    for(i=-5;i<7;i++,y+=56) {
        int idx, a,b;
        double d;
        char *text, *row;
        idx=i+MW(0x80);
        if(idx<0 || idx>=MW(0x740)) continue;
        row=(char *)D_L00_0022F7C0+0x140+idx*28;
        text=func_0028E588(0xea97,*(int *)row);
        a=fade(y+2);
        b=fade(y+40);
        if(a<0) a=0;
        if(b<0) b=0;
        a<<=24; b<<=24;
        if(*(int *)row==0) {
            char *label;
            int key;
            int off;
            int *wanted;    /* declared before j: equal allocation priorities go to the lower pseudo */
            int j;

            j=0;
        top:
            do {
                off=j*8;
                key=*(int *)((char *)D_L00_0028E9F0+off);
                if(key) {
                    j++;
                    wanted=(int *)((char *)D_L00_0022F7C0+0x158+idx*28);
                    if(*wanted!=key) goto top;
                    color=*(unsigned int *)((char *)D_L00_0028E9F0+(off+4));
                }
            } while(0);
            label=func_0028E588(0xea97,1);
            colors[2]=colors[0]=a|color;
            colors[3]=colors[1]=b|color;
            func_0028EA58(label,y+2,MY(332.0f),40,(int)(D_L00_001B25E0[0]*40.0f+0.5f),colors);
            color=0xf0f0b0;
        }
        colors[3]=colors[1]=b|color;
        colors[2]=colors[0]=a|color;
        func_0028EA58(text,y+2,MY(332.0f),40,(int)(D_L00_001B25E0[0]*40.0f+0.5f),colors);
    }
    }
}
#undef MW
#undef MY
