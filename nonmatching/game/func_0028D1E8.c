/* 8 November 2026, Sonnet round (o27): unchanged 3048/3056 bytes, aligned diff 7 words. RTL dumps:
 * b1/b2 set in draw 1's do/while(0) group stay separate through cse1 (the LOOP_END note ends its
 * block) but cse2 (after_loop ignores loop notes) merges them into the lookup's 0x8710 pseudo; long
 * (truncate is folded), unsigned short/int, sets before the lookup (b1 becomes canonical for all)
 * and inits at the declaration (local-alloc moves each single-use init to its use, calls-crossed 0,
 * so sched1 cannot lift it) all fail. Retail's $s1/$s2 sets cross ten calls, so at sched1 they were
 * in draw 1's block but cse2 must not have seen them equal; no plain-C form found. Draw 1 order:
 * tex lookup inside the group or as a direct argument (+12), colour local, non-inline call (+125)
 * all worse or equal. -frac2-* flags tried: no change; -fno-rerun-cse-after-loop breaks the clamps.
 */
/* 8 November 2026, Sonnet round (o17): 3048/3056 bytes, 0/28 places, aligned diff 7 words (was 24).
 * New: draw 1's constants and draw go in a do/while(0) group after its lookup (scale/half/one/zero,
 * the draw, then minus), so the loop note keeps 208.0/0.5 after the call as retail; the tail's two
 * func_00283D38 calls and two text draws go in one group after alpha, which keeps its 0.5 after the
 * first call in $f21. Left: retail's $s1/$s2 copies of 0x8710 (cse2 merges any equal constant in one
 * block; b1/b2 inits inside or outside groups, dead-test helper all fail) and draw 1's
 * `daddu a0,v0` / `lui a1` order. Statement-move sweep (single moves, 720 group orders, constant
 * placements) found nothing better; one capped permuter run seeded from this C: no honest gain.
 */
/* 8 November 2026, Sonnet round: 3048/3056 bytes, 0/28 places, aligned diff 24 words (was 37). New:
 * `sel = *(int *)(o+0x74)` read before the post-loop test gives retail's beqz with the lw in its slot;
 * 129.0f/208.0f written inside draw_background and plain 0x8710 literals for the two 134 draws
 * (b1/b2 dropped: cse merged them anyway); a separate `char *label` now scores the same as reusing
 * selectedAvailable, so no owner ruling is needed. Left: the 208.0/0.5 sets in draw 1 and the tail's
 * 0.5 are hoisted above the block's first call (they cross calls, so sched1 fills idle slots with
 * them; retail keeps them after the call), and retail's $s1/$s2 copies of 0x8710 for the 134 draws.
 * A do/while(0) right after draw 1's lookup stops the hoist (a loop note is a sched barrier) but
 * swaps the float registers (50 words); hud_coord dead tests make every constant per-draw.
 * One capped permuter run (seed: this C): best 1550 from 1940, only by a volatile local or by
 * hoisting a colour store out of the switch (changes behaviour); nothing honest to keep.
 */
/* 8 November 2026, round 2: 3060/3056 bytes (one word long), 0/28 places, aligned diff 37 words
 * (round 1: 56). The 0x8710 offset is now four sources, as retail: a literal for draws 1-10 (cse
 * gives $s0), and locals b1, b2, b3 initialised at their declaration for the two 134 draws and the
 * selected-slot draw. Initialised in the entry block they are separate pseudos; local-alloc moves
 * each single-use init to its use, so b3 becomes retail's exact lw/ori/addu. The label pointer reuses
 * selectedAvailable (retail keeps both in $s1), which fixes the $s0/$s1 swap. Still open: retail sets
 * b1/b2 in $s1/$s2 after the first call; here their inits move next to the draws ($a0, D in $v0).
 * Putting the two 134 draws in a do/while(0) group stops that move (loop depth), and b1/b2 then get
 * $s1/$s2, but set in the entry block (41 words). Inits written in the draws block are merged by cse.
 * Also open: 0.5/208.0 are set before the first call (retail: after), the post-loop beql (retail
 * beqz with lw 0x74 in the slot) and the tail 0.5 placement.
 */
/* 8 November 2026 re-measure on the new master compiler; retained near miss, not linked.
 * USA v1.01 check.py (-O2 -G8 -ffunction-sections, as src/game/0028D1E8-g8.c): 3044/3056 bytes,
 * 0/28 places; aligned diff 56 words (was 179 for the 4 November draft). No RAC1/RAC4 twin found
 * (0033F030-radial-g8.c is the widget version of the same menu, not a code twin).
 * Fixed this round: D_001B189E..18A4 read as D_001B189C[1..4] of one sda block (offset reads have
 * length 2, so the switch-case loads and the 0x2F35 test stop filling delay slots, as retail);
 * colour stores written [0..3] so gcc emits retail's [3],[0],[1],[2]; available colour as if/else
 * of the four stores (cross-jumped, retail's beql form instead of movn); `special` merged into
 * `previous` (retail keeps both in $s0); a block-local k for the bracket index; the alpha product
 * in its own float; packed colours passed without the u32 zero-extension (retail has none).
 * Remaining: retail loads 0x8710 three times for the background draws ($s0 for draws 1-10, $s1
 * and $s2 set early for the two 134 draws) and again into $a0 in the selected-slot block; this C
 * keeps one pseudo, which also leaves `previous` in $s1 and selectedAvailable in $s0 (swapped).
 * A dead display-mode test in draws 10-12 reproduces the three cse breaks (the selected-slot load
 * becomes retail's exact lw/ori/addu) but its constants stay in $a0 and the frame grows (3112
 * bytes); do/while(0) groups, -fmove-all-movables, -g, -fno-gcse, -fno-expensive-optimizations,
 * -mno-split-addresses and -G0 do not split the constant. Also open: the post-loop test fills an
 * annulled slot from the target (retail: beqz with lw 0x74 from the fall-through) and the tail's
 * 0.5 is set before the first func_00283D38 call (retail: after).
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 3020/3056 bytes, 0/28 placements; first difference size mismatch.
 * Profile: -O2 -G8 -ffunction-sections.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* 2 November 2026: corrected physical interface, not a match.
 * Current 0027F980.c defines func_0027FAA8 with an int return and a complete
 * 64-bit style argument; the old draft declared void and a 32-bit style.
 * Packed 32-bit colors now explicitly widen through u32 into u64. The text
 * lookup keeps its actual integer stored-address return (00336A78.c), with
 * explicit pointer casts at the drawing calls.
 * Default G8 check.py: 3020/3056 bytes, 0/28 USA v1.01 placements. The old
 * 3012-byte draft had the narrower, false interface. Shared lookup bases,
 * FP constants and final color-branch lowering remain different. No further
 * equivalent source or flag sweep was run; no linked match is claimed.
 */
#include "common.h"

typedef struct { int xy[8][2]; } RadialPositions;
typedef struct { int ids[8]; } RadialLabels;
typedef struct { int icon, frame; int rest[5]; } RadialItem;
extern RadialPositions D_001A8E30;
extern RadialLabels D_001A8E70;
extern short D_001B189C[] __attribute__((sda));
extern int D_001B18D0;
extern RadialItem **D_001B18D4;
extern int D_001A8D48 __attribute__((sda));
extern char *D_001A8CFC;
extern float D_001B23A4;
extern float func_00283CE0(int);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00336D50(char *,int);
extern void func_00300A00(char *,int,float,float,float,float,float);
extern int func_002A9588(int,int,int,int,int);
extern void func_0028FC48(int,int,int,int,unsigned long,int);
extern int func_0028E588(int,int);
extern void func_0028EA58(int,int,int,int,int,int *);
extern int func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00283D38(int,int,float);
extern int func_0027FAA8(int,int,u64,char *,int);

static __inline__ void draw_background(char *tex, int color, float sx, float sy, float rot, float scale, float half)
{
    func_00300A00(tex, color, 129.0f, (float)(int)(D_001B23A4 * scale + half), sx, sy, rot);
}

int func_0028D1E8(unsigned char *o)
{
    int total = D_001B189C[4] + D_001B189C[2] + D_001B189C[3];
    RadialPositions positions = D_001A8E30;
    int colors[4], colors2[4];
    float open, text, angle;
    float one, zero, minus, scale, half;
    char *tex;
    int b3 = 0x8710;
    int sel;
    char *label;
    int i, selectedAvailable, x, y, frame, available, color, previous;
    unsigned char *fade = o + 0x70;
    open = func_00283CE0(o[0x70]) / func_00283CE0(8);
    if (open > 1.0f) open = 1.0f;
    else if (open < 0.0f) open = 0.0f;
    text = func_00283CE0(fade[1]) / func_00283CE0(8);
    if (text > 1.0f) text = 1.0f;
    else if (text < 0.0f) text = 0.0f;
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 8);
    do {
        scale = 208.0f;
        half = 0.5f;
        one = 1.0f;
        zero = 0.0f;
        draw_background(tex, 0x60442D00, one, one, zero, scale, half);
        minus = -1.0f;
    } while (0);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 9);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 10);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 11);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 12);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 13);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 14);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 15);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 7);
    draw_background(tex, 0x60442D00, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 7);
    draw_background(tex, 0x60442D00, minus, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 134);
    draw_background(tex, 0x55F0C070, one, one, zero, scale, half);
    tex = (char *)func_00336D50(D_001A8CFC + 0x8710, 134);
    draw_background(tex, 0x55F0C070, minus, one, zero, scale, half);
    if (*(int *)(o+0x74) >= 0) {
        colors[0] = func_002A9588(0x80442D00,0x80FFDE8D,25,0,0);
        previous = *(int *)(o+0x74)-1;
        if (previous < 0) previous = 7;
        draw_background((char *)func_00336D50(D_001A8CFC + b3, 16), colors[0], one, one, (float)previous, scale, half);
        {
            int k = *(int *)(o+0x74);
            func_0028FC48(positions.xy[k][0],(int)((float)positions.xy[k][1]*D_001B23A4+0.5f),
                positions.xy[k][0]+33,(int)((float)(positions.xy[k][1]+7)*D_001B23A4+0.5f),colors[0],0);
        }
    }
    selectedAvailable = 0;
    for (i=0;i<D_001B18D0;i++) {
        angle = func_00283B98((float)i * 2.0f * 3.1415927f / (float)D_001B18D0 - 3.1415927f,1.5707964f);
        x = (int)(func_00283180(angle)*80.0f)+114;
        y = (int)(func_00283198(angle)*75.0f)+192;
        if (!D_001B18D4[D_001A8D48][i].icon) continue;
        frame = D_001B18D4[D_001A8D48][i].frame;
        previous = 0;
        if (frame == 6 && !D_001B189C[1]) frame = 7;
        available = 0;
        switch (frame) {
        case 2:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x6000FF00;
                available=1; previous=1;
            }
            break;
        case 3:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x6029A1FF;
                previous=1; available=1;
            }
            break;
        case 0:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x600000FF;
                previous=1; available=1;
            }
            break;
        case 1:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[3]=colors[2]=colors[1]=colors[0]=0x60FF0000;
                previous=1; available=1;
            }
            break;
        case 6: case 7:
            if (D_001B189C[2]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 4:
            if (D_001B189C[3]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 8:
            if (D_001B189C[4]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 9:
            if (D_001B189C[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        }
        if (previous) func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,10),x+2,y+2,28,26,colors);
        if (available) {
            colors2[3]=colors2[2]=colors2[1]=colors2[0]=0x80FFDE8D;
        } else {
            colors2[3]=colors2[2]=colors2[1]=colors2[0]=0x40808080;
        }
        func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,frame),x,y,30,28,colors2);
    }
    sel = *(int *)(o+0x74);
    if (selectedAvailable && sel>=0 && sel<8) {
        RadialLabels labels=D_001A8E70;
        int id=labels.ids[sel];
        if (id==0x2F34 && D_001B189C[1]) id=0x2F35;
        label=(char *)func_00288FB8(id);
        if (label && func_001157AC(label)) {
            float alpha = text * open;
            do {
                color=func_00283D38(0x00E0C0A0,0x80E0C0A0,alpha);
                previous=func_00283D38(0,0x80000000,alpha);
                func_0027FAA8(128,(int)(D_001B23A4*200.0f+0.5f),previous,label,-1);
                func_0027FAA8(129,(int)(D_001B23A4*201.0f+0.5f),color,label,-1);
            } while (0);
        }
    }
    return *(int *)(o+0x58);
}
