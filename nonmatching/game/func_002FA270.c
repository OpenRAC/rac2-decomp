/* 8 November 2026 (round 12, twin port from func_002F9C80): base unchanged (1552/1552, same 16 rows). Twin spellings: ternary clamps, alpha0-first shifts/stores, plain icon pointer lookup, count field, kind temp: identical code. Twin screen_y macro (D*y, +(B90?4:0)) in all calls: +0x30, 24 rows; only in draw_icon: 17; D*size for h: 21-32. Helper param orders, size local, x/D8 operand orders, color/or temps, index order, loop bound: same or worse. Flags (each alone): keep-block-order, gcse-unsplit-edges, keep-block-zero-copy, mult-add-no-flatten, frame-pointer-liveness, no-extra-increment-givs, qcopy, zero-ti-por, keep-float-pun-source, no-null-pointer-checks: all identical. The D0/scale tie and C4 order do not move from source. */
/* 8 November 2026 (round 9, rank_for_schedule): base 1552/1552, 20 differing words (retained C, recorded flags). rank_for_schedule is identical in GCC 2.95/2.95.2/2.95.3 and EE 991111/991111b; SN 2.95.2 v2.73a makes the same tie choice where its output is comparable. Env probes (sched1/sched2/both): reg weight swapped/clamped/dropped/after class/positive-or-negative only, class dropped/reversed, dependent count reversed/dropped/data-only/clamped, LUID reversed, INSN_UID ties, no birthing boost: none improves any of the nine cluster targets; forced on, every variant changes 6-7124 of 8761 matched units. Hypothesis falsified. */
/* 7 November 2026: retained near miss, not linked. USA v1.01 check.py: 1552/1552 bytes,
 * 0/28 places; 16 real rows left (was 21), all in the block before the first func_0028EA58.
 * Fixed this round:
 *   - First D_00239BA0 lookup as (IconInfo *)((char *)D_00239BA0 + idx * 224): addu v0,v0,s2.
 *   - alpha1 <<= 24; alpha0 <<= 24; before the color stores: sll s1,s1,24 in place, or t2,s1,s5.
 *   - x = y + (D_001AD3C4 + b) as a temp for the first call: retail's (y+(C4+2))+D8 grouping and
 *     every register now match (t1 for D_001A7B90, v1 for the mfc1).
 *   - draw_icon(tex, x, y, size, colors) helper (w == h at all three calls): same code, kept.
 * Remaining (sched2 order only): retail loads D_001AD3D0 before the scale D_001B2280, clamps
 *   before the D_001AD3C4 load, and loads D_001A7B90 before C4+2. -fsched-verbose-5 shows
 *   prio(D0) == prio(scale) == 56 (scale wins on dependents 6 vs 4) and C4 50 vs movz 49. The C4
 *   chain is lifted by insn 698 (fix_truncsfsi2 for h), whose hidden SI scratch clobber is $4:
 *   it gets an output dep on the D8 load and an anti dep on x+D8. That scratch comes from
 *   reload's round-robin (last_spill_reg) and is not visible in the asm.
 * Tried without effect (all 16): statement order of clamps/shifts/stores/x (all legal orders
 *   sampled), temps for sy/h, helper body order and parameter order, scalar scale, x forms,
 *   separate colors stores, flags -frac2-hazard-labels/-fno-sched-interblock/-fsched-spec-load/
 *   -frac2-sticky-volatile-refs. Worse: clamp swap (19), -fno-gcse (30), scale*value (25/34),
 *   -fno-schedule-insns(2) (size), dead-test hud_h helper (1576 bytes), x reused (1544 bytes).
 * Next idea: earlier code shape that changes reload's scratch rotation for insn 698.
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 1552/1552 bytes, 0/28 placements; first difference 0x2b4.
 * Profile: -O2 -G8 -ffunction-sections.
 * The text lookup keeps its signed32 stored-address return with a use-site pointer cast.
 * func_0028EA58 returns void in its matched definition; that correction fixes the two color-store
 * ordering rows at +0x4A8/+0x4B4. The earlier table/alpha/coordinate residual remains.
 * Earlier measurements below are historical where superseded by this note.
 */
/* opus xhigh, task v2072: retained C attempt, USA v1.01.
 * Profile: -O2 -G8 -ffunction-sections (unit src/game/002F9BC0-ammo-g8.c).
 * Best: 1552 bytes, the same as retail; 0 of 28 places; about 21 real
 * (non-relocation) instruction differences.
 * Fixed since v1165:
 *   - "int left = 233" plus a variable border "b" (4, then 2) keeps 233 in s0.
 *     With a literal 4/2, fold() split_tree turns 233-(A0+4) into 229-A0.
 *   - y+(D_001AD3C4+b) gives retail's x in s6, icon in s7, overlay in fp, with
 *     no spill.
 *   - Icon height is the global D_001AD3D0.
 * Remaining differences:
 *   - 0x2FA524: addu v0,s2,v0 vs retail v0,v0,s2 (first D_00239BA0[] lookup).
 *   - Block before the first func_0028EA58: retail clamps alpha1, then alpha0,
 *     and only then loads C4/D8. Retail stores colors at 0xC, 0x4, then 0x8,
 *     0x0. The first call's x is (y+(C4+2))+D8 in retail. Here Cygnus
 *     reduce_expression_tree_depth flattens it to (y+D8)+(C4+2).
 *   - A temp, comma or inline row_x(pos,margin) helper gives retail's grouping
 *     but worse scheduling (24 diffs). Swapping the clamps or the colors
 *     a=b=v nesting also made it worse (24-27).
 * Next idea: the original UI helper or macro shape for the row x and alpha.
 * All required declarations follow; switch IDs are from retail's jump table.
 */
#include "common.h"
typedef struct { int id, kind, spare[3], locked; } ItemRow;
typedef struct { int frame, id, spare[2]; } AmmoRow;
typedef struct {
    int state, tick;
    char pad08[0x64];
    int scroll;
    char pad70[0x10];
    int selected;
    char pad84[0xbc];
    union { ItemRow item[64]; AmmoRow ammo[96]; } rows;
} ListState;
typedef struct { char pad00[4]; unsigned char color; char pad05[0x37]; unsigned short icon; char pad3e[0xa2]; } IconInfo;
extern ListState D_0021F240;
extern unsigned char D_00139568[];
extern IconInfo D_00239BA0[];
extern float D_001B2280[] MACRO_ADDR;
extern int D_001A7B90 MACRO_ADDR;
extern int D_001A7340 MACRO_ADDR, D_001A7344 MACRO_ADDR;
extern void func_002FC620(int,int,int,int);
extern int func_00282C30(int);
extern void func_00285548(int,int,int,int,int,int,unsigned int);
extern int func_0028E588(int,int);
extern unsigned int func_00336EF8(int);
extern void func_0028EA58(int,int,int,int,int,unsigned int *);
extern int func_00288FB8(int);
extern int func_0027F288(char *,int,float);
extern void func_002F97A0(float,float,unsigned long,float,char *,int);
static __inline__ int screen_y(int y) { int result = (int)((float)y * D_001B2280[0] + 0.5f); if (D_001A7B90) result += 4; return result; }
extern int D_001AD39C MACRO_ADDR;
extern int D_001AD394 MACRO_ADDR;
extern int D_001AD3A4 MACRO_ADDR;
extern int D_001AD3AC MACRO_ADDR;
extern int D_001AD3A8 MACRO_ADDR;
extern int D_001AD3CC MACRO_ADDR;
extern int D_001AD398 __attribute__((sda));
extern int D_001AD390 __attribute__((sda));
extern int D_001AD3A0 __attribute__((sda));
extern int D_001AD3B0 __attribute__((sda));
extern int D_001AD3C0 __attribute__((sda));
extern int D_001AD3C4 __attribute__((sda));
extern int D_001AD3C8 __attribute__((sda));
extern int D_001AD3D0 __attribute__((sda));
extern int D_001AD3D8 __attribute__((sda));
extern int D_001AD3BC __attribute__((sda));
static __inline__ void draw_icon(int tex, int x, int y, int size, unsigned int *colors)
{
    func_0028EA58(tex, x, screen_y(y), size, (int)((float)size * D_001B2280[0] + 0.5f), colors);
}

void func_002FA270(void)
{
    int pulse, x;
    int left, b;
    int i, index, y, icon, overlay, kind, special, alpha0, alpha1;
    unsigned int color, colors[4];
    char *text;
    double distance;
    func_002FC620(D_001AD390,D_001AD394,(int)((float)D_001AD398 * D_001B2280[0]+0.5f),screen_y(D_001AD39C));
    if (D_0021F240.scroll < 0) D_0021F240.scroll += 4;
    else if (D_0021F240.scroll > 0) D_0021F240.scroll -= 4;
    i = -5;
    left = 233;
    b = 4;
    pulse = ((func_00282C30(((D_0021F240.tick*4)&63)-32)+64)*0x10202)|0x80000000;
    func_00285548(left-(D_001AD3A0+b),screen_y(325-D_001AD3A4),D_001AD3A8+285,screen_y(D_001AD3AC+381),D_001A7340,D_001A7344,
        pulse);
    b = 2;
    func_00285548(left-(D_001AD3A0+b),screen_y(327-D_001AD3A4),D_001AD3A8+283,screen_y(D_001AD3AC+379),D_001A7340,D_001A7344,0x80442d00);
    y = D_0021F240.scroll - 47;
    do {
        index = i + D_0021F240.selected;
        if (index >= 0 && index < *(int *)((char *)&D_0021F240+0x740)) {
            icon = func_0028E588(((IconInfo *)((char *)D_00239BA0 + D_00139568[D_0021F240.rows.ammo[index].id] * 224))->icon,0);
            overlay = func_0028E588(0xeaa3,D_0021F240.rows.ammo[index].frame);
            special = 0;
            kind = D_00239BA0[D_00139568[D_0021F240.rows.ammo[index].id]].color;
            switch (D_0021F240.rows.ammo[index].id) {
            case 12: case 14: case 17: case 18: case 53: special = 1; break;
            }
            color = func_00336EF8(special && kind == 1 ? 2 : kind) & 0xffffff;
            distance = (double)(256.0f - (float)(y+2));
            if (distance < 0.0) distance = -distance;
            alpha0 = 128 - (int)(distance * 0.75);
            distance = (double)(256.0f - (float)(y+40));
            if (distance < 0.0) distance = -distance;
            alpha1 = 128 - (int)(distance * 0.75);
            if (alpha0 < 0) alpha0 = 0;
            if (alpha1 < 0) alpha1 = 0;
            alpha1 <<= 24;
            alpha0 <<= 24;
            colors[3] = colors[1] = alpha1|color;
            colors[2] = colors[0] = alpha0|color;
            x = y+(D_001AD3C4+b);
            draw_icon(icon,x+D_001AD3D8,D_001AD3C0+D_001AD3CC,D_001AD3D0,colors);
            draw_icon(overlay,y+(D_001AD3C4+b),D_001AD3C0-D_001AD3C8,D_001AD3C8,colors);
            icon = func_0028E588(0xeaa3,3);
            draw_icon(icon,y+(D_001AD3C4+b),(D_001AD3C0-D_001AD3C8)+D_001AD3BC,D_001AD3C8,colors);
        }
        i++;
        y += 56;
    } while (i < 7);
}
