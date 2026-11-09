/* 9 November 2026 (Opus round o103): 1216/1216, 0/27, 13 differing words, one register rotation. Nonempty form of the
 * probe: `do { do { j=0; } while(0); top: ... } while(0);` (j=0 moved into the inner group) gives retail's size, the
 * loop note and the bne slot; only the search registers rotate: j a1/tbl a2/wanted a3 vs retail a3/a1/a2. Deciding
 * value (regalloc.py): j's depth-weighted refs go 11 -> 13, priority 39/22 = 1.77 beats tbl 27/16 = 1.69 and wanted
 * 3/2 = 1.5; retail needs j <= 1.5 (refs <= 11 at live 22, or live >= 27). Declaration order: no change (not a tie).
 * Worse: wanted computed in the inner group (97-100), `color = 0xf0f0b0` as the group body (1224 bytes),
 * `do { j=0; } while(0); top:` with no outer group (1220). */
/* 8 November 2026 (nominalsan, Opus 5.5): compiles to 1212 bytes (retail 1216), 0/27 USA, default flags.
 * Aligned with relocations masked, 303 of retail's 304 instructions agree: retail fills the backward bne's
 * delay slot with `lui v0,%hi(wanted base)` from the loop top, this C with the colour `addu`.
 * What moved it: `wanted` computed at its use (haifa then moves the madd ahead of the key's addu); the colour
 * read as `tbl + (off + 4)` (cse1 puts a known constant second; this form keeps retail's (tbl, off) and the
 * table's low part in the loop); the rows as `D_L00_0022F7C0 + 0x140` (no hoisted high part taking v0 before
 * y); `j = 0` before the do/while(0) and `wanted` declared first (global-alloc ties j and wanted at 1.5, the
 * lower pseudo wins, giving retail's a2/a3).
 * Remaining: `top` is outside the loop notes, so reorg (mostly_true_jump) predicts the bne not taken. A loop
 * note directly before `top` fixes it: as a probe only, `j=0; do { do { } while(0); top: ... } while(0);`
 * matches 27/27 in USA, PAL and v2.00 (tools/check.py), but empty loops are excluded (docs/COMPILER-NOTES.md).
 * Why nonempty forms fail: the table's low part stays in the loop only if its register is shared with the
 * colour block (scan_loop), which needs both in one group because cse1 stops at a loop end; reorg needs the
 * bne in a loop containing `top`; the allocation needs `j = 0` one level shallower than the rest; and a group
 * starting with its label is a real loop unless entered from outside. Measured, no match: jump-into-loop
 * shapes with retail's control flow (1132-1148 bytes), smaller groups (1080-1140), rac1's
 * `while (t[i].key != END && t[i].key != id) i++;` idiom and for/break forms (1012-1044), -g,
 * __builtin_expect. Siblings: rac1's render_vendor_item_icon_strip_pass shares the scroll and pulse code;
 * RAC2's func_L00_00376600 shares the row loop and rows at +0x140; neither has the search.
 * Next: the original construct that leaves a loop note before `top`, with evidence (e.g. a debug macro).
 */
/* 7 November 2026 (nominalsan, Opus 5.5): 1220 bytes with -fmove-all-movables, 11 instructions differing.
 * Kept from it: the `fade()` helper (y+2 in s0 copied to s6) and the search in a do/while(0), which flow counts
 * as a loop (idx s2, colour s3, as retail) and loop.c skips as phony. Measured then, no gain: real for/while
 * searches, a single-flag sweep (-frac2-*, -fno-sched-*, -fno-strength-reduce, -G8, -g), and three
 * decomp-permuter runs on the earlier C (about 1.1 million candidates; only the colors[] store order kept).
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
