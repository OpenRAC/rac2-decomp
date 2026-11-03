/* Claude Opus 5.5 xhigh tier, USA v1.01, default game -O2 -G8 -ffunction-sections (a -g8.c unit).
 * Best check.py: 3012/3056 bytes, 0/28 places, 670 of 764 rows differ (the previous draft
 * recompiled here: 3028 bytes, 755 rows differ, needing f27). Not linked. All declarations below.
 *
 * Reproduced by this wording: an inline draw helper rematerializes 129.0f into f12 at all 13
 * draws, and floats set just after the clamps give retail's f20-f26 assignment and seven saves.
 * Setting them at the top of the function loses those registers (direct li.s at each draw).
 * Also reproduced: colors[2]=colors[1]=colors[0]=colors[3] store order, case 3 sharing case 0's
 * tail, and the tied lui/lh form (incomplete sda short arrays).
 *
 * Still differs:
 * 1. 0x8710: retail uses s0 for lookups 1-10, s1 for 11, s2 for 12, a fresh a0 for 13; this has
 *    one register. i/available/special allocation (s3/s2/s0 in retail) follows from it.
 * 2. Retail keeps 208.0/0.5 behind the first func_00336D50 call; here sched1 lifts them above it.
 * 3. final colour: retail branches (beql, lui/ori in the arms), this gives movn. if/else gives
 *    the same movn; a ternary stored straight into the chain moved allocation and was worse.
 *
 * Measured probes, NOT in this draft (each uses a construct the worker rules forbid):
 * - A skip-around test on a live register in the Y helper, in every lookup, whose body is dead:
 *     int r = (int)(v * S + 0.5f);
 *     if (mode != 0) { int dead = r + adj; dead = dead * adj; }
 *     return r;
 *   After cse1 (.loop dump) the lookups use pseudos 130 x10, 147, 164, 181: the setters of lookups
 *   1, 2, 3, 4. Those early setters cross calls, so sched1 lifts them, which is retail's extra-ori
 *   shape. The 10 looks like cse.c's jump path limit (from memory of GCC's source, not read here).
 *   cse2 then merges them all back into one register.
 * - The same probe with -fno-rerun-cse-after-loop gives s0 x10, s1, s2, a0 and the second ori in
 *   the func_00300A00 delay slot, exactly retail's pattern. That flag is not the answer: the clamps
 *   become bc1tl, and retail has bc1f/nop/b. So retail runs cse2, and something must flush its
 *   table between lookups 4 and 11, then vanish before sched1.
 * - do { } while (0), while (1) { break; } or a flag-cleared while after the first texture call
 *   gives retail's first-segment shape (lw, ori, addiu, jal, addu) as a sched barrier. A real
 *   test surviving sched1 at that point, gone by jump2, would do the same.
 * - if (mode != 0) return X + adj; return X; on a live register survives to jump2 in every lookup
 *   and keeps nothing shared; on a local set to 0 it splits the lookups 2/11. Neither fits.
 *
 * Next idea: a real helper test on one live value that keeps a boundary in lookup 1 through
 * sched1 while the later tests go away in cse1/cse2. Retail reads no D_001B23A0 here.
 */
#include "common.h"

typedef struct { int xy[8][2]; } RadialPositions;
typedef struct { int ids[8]; } RadialLabels;
typedef struct { int icon, frame; int rest[5]; } RadialItem;
extern RadialPositions D_001A8E30;
extern RadialLabels D_001A8E70;
extern short D_001B189C[] __attribute__((sda));
extern short D_001B189E[] __attribute__((sda));
extern short D_001B18A0[] __attribute__((sda));
extern short D_001B18A2[] __attribute__((sda));
extern short D_001B18A4[] __attribute__((sda));
extern int D_001B18D0;
extern RadialItem **D_001B18D4;
extern int D_001A8D48 __attribute__((sda));
extern char *D_001A8CFC;
extern float D_001B23A4;
extern float func_00283CE0(int);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern char *func_00336D50(char *,int);
extern void func_00300A00(char *,int,float,float,float,float,float);
extern int func_002A9588(int,int,int,int,int);
extern void func_0028FC48(int,int,int,int,unsigned long,int);
extern int func_0028E588(int,int);
extern int func_0028EA58(int,int,int,int,int,int *);
extern char *func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00283D38(int,int,float);
extern void func_0027FAA8(int,int,int,char *,int);

static __inline__ void draw_background(char *tex, int color, float x, float y, float sx, float sy, float rot)
{
    func_00300A00(tex, color, x, (float)(int)(D_001B23A4 * y + 0.5f), sx, sy, rot);
}

int func_0028D1E8(unsigned char *o)
{
    int total = D_001B18A4[0] + D_001B18A0[0] + D_001B18A2[0];
    RadialPositions positions = D_001A8E30;
    int colors[4], colors2[4];
    float open, text, angle;
    float one, zero, minus;
    int i, selectedAvailable, x, y, frame, special, available, color, previous;
    char *label;
    unsigned char *fade = o + 0x70;
    open = func_00283CE0(o[0x70]) / func_00283CE0(8);
    if (open > 1.0f) open = 1.0f;
    else if (open < 0.0f) open = 0.0f;
    text = func_00283CE0(fade[1]) / func_00283CE0(8);
    if (text > 1.0f) text = 1.0f;
    else if (text < 0.0f) text = 0.0f;
    one = 1.0f;
    zero = 0.0f;
    minus = -1.0f;
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 8), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 9), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 10), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 11), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 12), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 13), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 14), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 15), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 7), 0x60442D00, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 7), 0x60442D00, 129.0f, 208.0f, minus, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 134), 0x55F0C070, 129.0f, 208.0f, one, one, zero);
    draw_background(func_00336D50(D_001A8CFC + 0x8710, 134), 0x55F0C070, 129.0f, 208.0f, minus, one, zero);
    if (*(int *)(o+0x74) >= 0) {
        colors[0] = func_002A9588(0x80442D00,0x80FFDE8D,25,0,0);
        previous = *(int *)(o+0x74)-1;
        if (previous < 0) previous = 7;
        draw_background(func_00336D50(D_001A8CFC + 0x8710, 16), colors[0], 129.0f, 208.0f, one, one, (float)previous);
        i = *(int *)(o+0x74);
        func_0028FC48(positions.xy[i][0],(int)((float)positions.xy[i][1]*D_001B23A4+0.5f),
            positions.xy[i][0]+33,(int)((float)(positions.xy[i][1]+7)*D_001B23A4+0.5f),colors[0],0);
    }
    selectedAvailable = 0;
    for (i=0;i<D_001B18D0;i++) {
        angle = func_00283B98((float)i * 2.0f * 3.1415927f / (float)D_001B18D0 - 3.1415927f,1.5707964f);
        x = (int)(func_00283180(angle)*80.0f)+114;
        y = (int)(func_00283198(angle)*75.0f)+192;
        if (!D_001B18D4[D_001A8D48][i].icon) continue;
        frame = D_001B18D4[D_001A8D48][i].frame;
        special = 0;
        if (frame == 6 && !D_001B189E[0]) frame = 7;
        available = 0;
        switch (frame) {
        case 2:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x6000FF00;
                available=1; special=1;
            }
            break;
        case 3:
            if (D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x6029A1FF;
                special=1; available=1;
            }
            break;
        case 0:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x600000FF;
                special=1; available=1;
            }
            break;
        case 1:
            if (D_001B189C[0] && total < D_001B189C[0]) {
                if (i == *(int *)(o+0x74)) selectedAvailable=1;
                colors[2]=colors[1]=colors[0]=colors[3]=0x60FF0000;
                special=1; available=1;
            }
            break;
        case 6: case 7:
            if (D_001B18A0[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 4:
            if (D_001B18A2[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 8:
            if (D_001B18A4[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        case 9:
            if (D_001B189C[0]) { if (i == *(int *)(o+0x74)) selectedAvailable=1; available=1; }
            break;
        }
        if (special) func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,10),x+2,y+2,28,26,colors);
        color = available ? 0x80FFDE8D : 0x40808080;
        colors2[2]=colors2[1]=colors2[0]=colors2[3]=color;
        func_0028EA58(func_0028E588(D_001B18D4[D_001A8D48][i].icon,frame),x,y,30,28,colors2);
    }
    if (selectedAvailable && *(int *)(o+0x74)>=0 && *(int *)(o+0x74)<8) {
        RadialLabels labels=D_001A8E70;
        int id=labels.ids[*(int *)(o+0x74)];
        if (id==0x2F34 && D_001B189E[0]) id=0x2F35;
        label=func_00288FB8(id);
        if (label && func_001157AC(label)) {
            text *= open;
            color=func_00283D38(0x00E0C0A0,0x80E0C0A0,text);
            previous=func_00283D38(0,0x80000000,text);
            func_0027FAA8(128,(int)(D_001B23A4*200.0f+0.5f),previous,label,-1);
            func_0027FAA8(129,(int)(D_001B23A4*201.0f+0.5f),color,label,-1);
        }
    }
    return *(int *)(o+0x58);
}
