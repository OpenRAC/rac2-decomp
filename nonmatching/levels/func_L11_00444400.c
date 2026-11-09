/* 9 November 2026 (round o104): body below is new: 4632/4684 bytes, 0/1, profile now -O2 -G8 -ffunction-sections (sched1 ON; with -fno-schedule-insns the same body is 4648, 779 aligned). Masked-word LCS (relocs masked): 874 of 1171 retail words aligned (old body: 325 on the same scorer). Changes, from twin func_L02_003FE8B8 and owner-allowed HUD idioms: hud_coord (dead mode/result tests, owner ruling) for every box x/y/h and label_y (ls as handle) for every label y, `half = 0.5f;` after func_L00_0037B7B0, a block-scoped `s32 ofs = 0x8710;` per arm (7 blocks, as retail's 7 `ori ...,0x8710` sets). Result: box chains, the 0.5/-1/0 registers ($f20/$f21/$f22) and the arm-5 TITLE/sprintf rows are retail's. Measured (dumps): an int-arg scaled_coord on label y converts f32->int->f32 (+432 B); a single `mode == active` test leaves no jump at sched2 (no boundary), `result != 0 && ...` gives the boundary but LABEL_NUSES 2 ends cse's path (3/0x8710 fresh per box/label). `one` local as active and h inside the call: no change. Left: &r50 PRE copy kept in $fp/$s0 (retail rematerializes `addiu $a0,$sp,0x50`), constant 3 in $s4 plus a fresh $v0 in box 1 (retail $s1 boxes 1-4, fresh in 5/6), format-hi copy `daddu $fp,$s0` in arm 5, and arm-5/8 cross-jump starting one call later (13 words short). */
/* 5 November 2026, two-agent pass:
 * - Boundary: with func_L02_003FE768's one-pass conversion groups (allowed by COMPILER-NOTES'
 *   source methods; that function now matches) on the box x/y/h and the label y, every call's
 *   argument setup follows its chains as in retail: 4692/4684 bytes, 458 instructions aligned.
 * - Left, all register allocation: 0.5 in $f22 (the label -1/0 constants are block-local and
 *   local-alloc takes $f20/$f21 first; retail's are global, so a block boundary existed there
 *   during allocation); rect-address reaching registers keep $fp/$s6/$s7 where retail's reload
 *   evicts them (reload here never needs more than $v0/$v1); the constant 3 follows cse's
 *   10-block path length. The only construct found that fixes 0.5 and the save set is the
 *   twin's dead `if (mode == 1) y = 1.0f;` arm (580 aligned), which blocker 26 rules out.
 */
/* 5 November 2026, third pass (retained body unchanged, 4640/4684 bytes). Measured:
 * - This compiler's pass order after reload is flow2 -> sched2 -> jump2 (cross-jumping, jumps to
 *   the next insn) -> dbr. Retail's boundary before each call's argument setup is therefore a
 *   basic-block boundary that exists at sched2 and is gone by jump2 or dbr, without leaving a test.
 * - `if (D_L11_001B3E00 == 1)` around the box call with identical arms (D_L11_001B3E00 being the
 *   word before the scale, as the mode word D_L02_001B3E00 is in level 2) does give the boundary:
 *   all three chains finish before the argument loads. But the arms are not merged, so the
 *   function grows to 5144 bytes.
 * - An inline `hud_scaled(float v)` returning (int)(v * D_L11_001B3E04 + 0.5f) gives retail's
 *   chain shape (lwc1/cvt.s.w, value $f0, scale $f1); with the twin's dead `if (mode == 1)` arm
 *   it also gives retail's full save set ($s3, $s4, $s6, $s7 saved), as func_L02_003FF6E8's note
 *   explains, but no boundary (the test goes at flow2).
 * - Negative: sched1 on (4644 bytes), no sched2 (retail does schedule: data and 0.5 move),
 *   volatile layout globals (lw/mtc1 loads).
 */
/* 5 November 2026: retained body unchanged (4640/4684 bytes). New negative: the boxes as a
 * `static __inline__` helper taking the rounded coordinates as arguments (so they are
 * evaluated before the inlined call) do not make retail's boundary; sched2 then interleaves
 * all three chains. In haifa-sched a LOOP_BEG/END note in mid-block is a full barrier that
 * does not end the block, which is why the rejected do-while (0) diagnostic worked; a natural
 * construct with that effect is still not identified.
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 4640/4684 bytes, 0/1 placements; first difference size mismatch.
 * Profile: -O2 -G8 -ffunction-sections -fno-schedule-insns.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* Current retained result, 1 November 2026: 4640/4684 bytes. Current compiler and an additional -fno-force-
 * mem control retain this result; the scheduling boundary after the rounding chains is unresolved. No empty
 * wrapper, invented test or barrier is retained.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G8 -ffunction-sections -fno-schedule-insns.
 * Earlier measurements below remain historical where superseded by this note.
 */
/* func_L11_00444400 (L11 only, 4,684 B): draws the level's six HUD text boxes (layout table scaled by
 * D_L11_001B3E04 and rounded), then per mode (data + 0x1F0 == 5, 9, 8, 12, else) the titles, the time
 * or count through sprintf (func_00115DA8), and the boss bar (func_L02_003FE768).
 * Claude Opus 5.5 (xhigh), task v1931, 31 October 2026. FAILED near miss, USA v1.01 level 11:
 * 4640/4684 bytes, 0 of 1 places. Frame 0x180 and the save set ($s0-$s7, $fp, $ra, $f20-$f23) agree.
 * In a word LCS that ignores relocated immediates: 424 rows identical, 866 by opcode. The earlier
 * draft gave 4652 bytes, 515 and 846 (interleaved chains); sol-high gave 4688 bytes, 315 and 879.
 * Profile: -O2 -G8 -ffunction-sections -fno-schedule-insns in a dedicated unit
 * src/levels/11_joba/L11_00444400-g8.c (one config/cflags.txt line). Split addresses stay on; `sda` on
 * the incomplete arrays gives the tied `lui $a3; lw $a3` and `lui $at; lwc1` forms; SDATA gives the
 * $gp-relative table addresses. All declarations are below. No linked build; the marker is restored.
 *
 * Established, each measured:
 * - The shared `t` (twin func_L02_003FE8B8's wording) gives retail's box chains exactly: value $f0,
 *   scale $f1, scratch $f2 ($f1 on the third).
 * - Retail has a scheduling boundary inside every box call and every func_00300A00 label call, between
 *   the coordinate chain and the rest of the argument setup. No independent insn fills the chains'
 *   load/fmac latency gaps. Only values assigned before it sit ahead of it: the label string copied to
 *   $a0, the rounded y converted into $f13, and `data` in box 1. Here sched2 fills the gaps.
 *   Diagnostic only (forbidden): `do { call } while (0)` around the box and label calls gives retail's
 *   box call setup word for word and raises the opcode LCS to 973, but it gives 4692 bytes, not exact.
 * - Diagnostic only (identical arms, not allowed): `if (x != 0) h = ...; else h = ...;` before each
 *   box call also makes the boundary. But its join ends cse's path in every box, so 0.5 and 3 are
 *   rematerialized per box (0.5 in $f2). Retail keeps one 0.5 in $f20 from box 1 through the first part
 *   of every mode arm, reloading it only after the n >= 100 join (mode 12) and the boss switch
 *   (default arm). So at cse time the boundary is not an if/else join.
 * - Constant 3: retail has $s1 for boxes 1-4 and a fresh `addiu $v0,$zero,3` in boxes 5 and 6. Here
 *   cse folds every literal 3 (also into a `style` local) into one register, so something ends cse's
 *   knowledge of 3 before box 5 and again before box 6 while 0.5 survives. Not explained; cse's
 *   1000-insn flush and PATHLENGTH 10 do not fit the counts.
 * - Retail saves $s4, $s6 and $s7 and never uses them. It rematerializes &r50, &r70, &rF0 and &rD0 at
 *   every use and copies &r90/&rB0 out of $a0 into $s5/$fp (reload eviction plus gcse's reaching
 *   register, as in the twin). Here the rectangle addresses keep saved registers.
 * - 0.5 lands in $f22 here: -1.0f and 0.0f take $f20/$f21 first (retail: 0.5 $f20, -1/+1 $f21,
 *   0 $f22, which suggests those label constants are global pseudos in retail).
 * - An f32 label y changes nothing: combine sinks the conversion into the argument copy.
 * Next: find the construct that gives a basic-block boundary at each call's argument setup without
 * ending cse's path, or get a ruling on the non-empty do-while(0) row in MATCHING-BLOCKERS.
 * The TITLE/LABEL/SUM/DRAW/BOX macros stand for repeated blocks; expand them once it matches.
 */
#include "common.h"

typedef struct {
    u16 w[12];
} Rect;

typedef struct {
    u8 pad[0xB0];
    f32 text_scale;
} HudRenderState;

extern s32 D_L11_001A904C[] __attribute__((sda));
extern f32 D_L11_001B3E04;
extern u8 D_L11_001BEDC0[];
extern char D_L11_001B17E8[];
extern char D_L11_001B17F0[];
extern char D_L11_001B17F8[];
extern char D_L11_001B1800[];
extern s32 D_L11_001B14B8[] SDATA(D_L11_001B14B8);
extern s32 D_L11_001B14D0[] SDATA(D_L11_001B14D0);
extern s32 D_L11_001B14D8[] SDATA(D_L11_001B14D8);
extern s16 *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
extern s32 D_L11_001B1718 __attribute__((sda));

extern s32 D_L11_001B1798 __attribute__((sda));
extern s32 D_L11_001B179C __attribute__((sda));
extern s32 D_L11_001B17A0 __attribute__((sda));
extern s32 D_L11_001B17A4[] __attribute__((sda));
extern s32 D_L11_001B17A8[] __attribute__((sda));
extern s32 D_L11_001B17AC[] __attribute__((sda));
extern s32 D_L11_001B1780 __attribute__((sda));
extern s32 D_L11_001B1784 __attribute__((sda));
extern s32 D_L11_001B1788 __attribute__((sda));
extern s32 D_L11_001B178C[] __attribute__((sda));
extern s32 D_L11_001B1790[] __attribute__((sda));
extern s32 D_L11_001B1794[] __attribute__((sda));
extern s32 D_L11_001B1738 __attribute__((sda));
extern s32 D_L11_001B173C __attribute__((sda));
extern s32 D_L11_001B1740 __attribute__((sda));
extern s32 D_L11_001B1744[] __attribute__((sda));
extern s32 D_L11_001B1748[] __attribute__((sda));
extern s32 D_L11_001B174C[] __attribute__((sda));
extern s32 D_L11_001B171C __attribute__((sda));
extern s32 D_L11_001B1720 __attribute__((sda));
extern s32 D_L11_001B1728 __attribute__((sda));
extern s32 D_L11_001B172C[] __attribute__((sda));
extern s32 D_L11_001B1730[] __attribute__((sda));
extern s32 D_L11_001B1734[] __attribute__((sda));
extern s32 D_L11_001B1768 __attribute__((sda));
extern s32 D_L11_001B176C __attribute__((sda));
extern s32 D_L11_001B1770 __attribute__((sda));
extern s32 D_L11_001B1774[] __attribute__((sda));
extern s32 D_L11_001B1778[] __attribute__((sda));
extern s32 D_L11_001B177C[] __attribute__((sda));
extern s32 D_L11_001B1750 __attribute__((sda));
extern s32 D_L11_001B1754 __attribute__((sda));
extern s32 D_L11_001B1758 __attribute__((sda));
extern s32 D_L11_001B175C[] __attribute__((sda));
extern s32 D_L11_001B1760[] __attribute__((sda));
extern s32 D_L11_001B1764[] __attribute__((sda));

extern s32 D_L11_001B17B0 __attribute__((sda));
extern s32 D_L11_001B17B4 __attribute__((sda));
extern s32 D_L11_001B17B8 __attribute__((sda));
extern s32 D_L11_001B17BC __attribute__((sda));
extern s32 D_L11_001B17C0 __attribute__((sda));
extern f32 D_L11_001B17C4 __attribute__((sda));
extern f32 D_L11_001B17C8 __attribute__((sda));
extern f32 D_L11_001B17CC __attribute__((sda));
extern f32 D_L11_001B17D0 __attribute__((sda));
extern f32 D_L11_001B17D4 __attribute__((sda));
extern f32 D_L11_001B17D8 __attribute__((sda));
extern f32 D_L11_001B17DC __attribute__((sda));
extern s32 D_L11_001B17E0 __attribute__((sda));
extern s32 D_L11_001B17E4 __attribute__((sda));

extern void func_0027AB40(void);
extern void func_00280190(Rect *, u64, char *, s32);
extern void func_00280200(Rect *, u64, char *, s32);
extern void func_00280270(Rect *, u64, char *, s32);
extern void func_002802E0(Rect *, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 func_00283CE0(s32);
extern int func_00288FB8(s32);
extern void func_002FC560(u32, u64);
extern void func_L00_0037B7B0(void);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern void func_L02_003FE768(f32);
extern int func_00336D50(s32, s32);
extern s32 func_001157AC(char *);
extern s32 func_00115DA8(char *, char *, ...);

extern s32 D_L11_001B3E00;
#define LBL(id, c, xv, yv, a1, a2, a3) { char *ls = (char *)func_00336D50(D_L11_001A904C[0] + ofs, id); func_00300A00(ls, c, xv, (f32)label_y(ls, (yv), D_L11_001B3E04, half, 1), a1, a2, a3); }
#define TITLE() \
        LBL(0x4C, D_L11_001B17E4, D_L11_001B17D0, D_L11_001B17D4, -1.0f, D_L11_001B17C4, 0.0f); \
        LBL(0x4D, D_L11_001B17E0, D_L11_001B17D0, D_L11_001B17D4, -1.0f, D_L11_001B17C4, 0.0f)
#define LABEL() \
        LBL(0x4C, D_L11_001B17E4, D_L11_001B17C8, D_L11_001B17CC, D_L11_001B17C4, 1.0f, 0.0f); \
        LBL(0x4D, D_L11_001B17E0, D_L11_001B17C8, D_L11_001B17CC, D_L11_001B17C4, 1.0f, 0.0f)
#define LABEL50() \
        LBL(0x50, D_L11_001B17E0, D_L11_001B17BC, D_L11_001B17C0, D_L11_001B17C4, 1.0f, 0.0f)
#define SUM() \
            sum = 0; \
            for (i = 7, obj = data + 0x100; i >= 0; i--, obj += 4) { \
                sum += *(s32 *)obj; \
            }
#define DRAW(fn, r, s) \
            str = (s); \
            fn((r), D_L11_001B1718, str, func_001157AC(str))
#define DRAWBUF(fn, r) \
            { s32 c = D_L11_001B1718; s32 n = func_001157AC(buf); fn((r), c, buf, n); }
#define sprintf_n func_00115DA8
#define BOX(r, X, Y, C, D, E, H) \
    x = hud_coord((f32)X, D_L11_001B3E04, half); \
    y = hud_coord((f32)Y[0], D_L11_001B3E04, half); \
    h = hud_coord((f32)H, D_L11_001B3E04, half); \
    func_002802E0(r, x, y, C[0], D[0], E, h, 0, 3)

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L11_001B3E00;
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

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L11_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L11_00444400(u8 *moby)
{
    char buf[0x40];
    Rect r50;
    Rect r70;
    Rect r90;
    Rect rB0;
    Rect rD0;
    Rect rF0;
    u8 *data;
    u8 *obj;
    u8 *pv;
    f32 save;
    s32 sum;
    s32 i;
    s32 n;
    s32 tm;
    s32 x, y, h;
    char *str;
    f32 half;

    if (D_L11_001A904C[0] == 0) {
        return;
    }
    func_L00_0037B7B0();
    half = 0.5f;
    data = *(u8 **)(moby + 0x68);
    BOX(&r50, D_L11_001B17A0, D_L11_001B17A4, D_L11_001B17A8, D_L11_001B17AC, D_L11_001B1798, D_L11_001B179C);
    BOX(&r70, D_L11_001B1788, D_L11_001B178C, D_L11_001B1790, D_L11_001B1794, D_L11_001B1780, D_L11_001B1784);
    BOX(&r90, D_L11_001B1740, D_L11_001B1744, D_L11_001B1748, D_L11_001B174C, D_L11_001B1738, D_L11_001B173C);
    BOX(&rB0, D_L11_001B1728, D_L11_001B172C, D_L11_001B1730, D_L11_001B1734, D_L11_001B171C, D_L11_001B1720);
    BOX(&rF0, D_L11_001B1770, D_L11_001B1774, D_L11_001B1778, D_L11_001B177C, D_L11_001B1768, D_L11_001B176C);
    BOX(&rD0, D_L11_001B1758, D_L11_001B175C, D_L11_001B1760, D_L11_001B1764, D_L11_001B1750, D_L11_001B1754);
    save = ((HudRenderState *)D_L11_001BEDC0)->text_scale;
    ((HudRenderState *)D_L11_001BEDC0)->text_scale = 0.62f;
    func_0027AB40();
    if (*(s16 *)(data + 0x1F0) == 5) {
        s32 ofs = 0x8710;
        TITLE();
        sprintf_n(buf, D_L11_001B17E8, 0x5A - *(s32 *)(data + 0x188) / 60);
        DRAWBUF(func_00280270, &r90);
        DRAW(func_00280190, &rB0, ((char *)func_00288FB8(0x2F63)));
        LABEL();
        SUM();
        sprintf_n(buf, D_L11_001B17E8, D_L11_001B14B8[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
        DRAWBUF(func_00280270, &r50);
        DRAW(func_00280190, &r70, ((char *)func_00288FB8(0x2F61)));
    } else if (*(s16 *)(data + 0x1F0) == 9) {
        s32 ofs = 0x8710;
        TITLE();
        tm = *(s32 *)(data + 0x188);
        sprintf_n(buf, D_L11_001B17F0, 2 - tm / 3600, 0x3B - tm / 60 % 60);
        DRAWBUF(func_00280200, &r90);
        DRAW(func_00280190, &rB0, ((char *)func_00288FB8(0x2F63)));
        LABEL();
        LABEL50();
        pv = *(u8 **)(*(u8 **)(data + 0x180) + 0x68);
        func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
        func_00300A00(((char *)func_00336D50(D_L11_001A904C[0] + ofs, 0xE3)), D_L11_001B17B0, D_L11_001B17B4, D_L11_001B17B8, D_L11_001B17C4, 1.0f, 1.0f);
    } else if (*(s16 *)(data + 0x1F0) == 8) {
        s32 ofs = 0x8710;
        TITLE();
        sprintf_n(buf, D_L11_001B17E8, 0x3C - *(s32 *)(data + 0x188) / 60);
        DRAWBUF(func_00280270, &r90);
        DRAW(func_00280190, &rB0, ((char *)func_00288FB8(0x2F63)));
        LABEL();
        SUM();
        sprintf_n(buf, D_L11_001B17E8, D_L11_001B14D0[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
        DRAWBUF(func_00280270, &r50);
        DRAW(func_00280190, &r70, ((char *)func_00288FB8(0x2F61)));
    } else if (*(s16 *)(data + 0x1F0) == 0xC) {
        s32 ofs = 0x8710;
        TITLE();
        n = 100 - *(s32 *)(data + 0x188) / 60;
        sprintf_n(buf, D_L11_001B17E8, n);
        if (n >= 100) {
            DRAWBUF(func_00280190, &r90);
        } else {
            DRAWBUF(func_00280270, &r90);
        }
        DRAW(func_00280190, &rB0, ((char *)func_00288FB8(0x2F63)));
        if (moby[0xBC] != 0) {
            s32 ofs = 0x8710;
            LABEL();
            SUM();
            if (moby[0xBC] < 2) {
                sprintf_n(buf, D_L11_001B17E8, D_L11_001B14D8[*(s16 *)(data + 0x1F2)] + sum - *(s32 *)(data + 0x140));
                DRAWBUF(func_00280270, &r50);
            } else {
                sprintf_n(buf, D_L11_001B17E8, 100);
                DRAWBUF(func_00280190, &r50);
            }
            DRAW(func_00280190, &r70, ((char *)func_00288FB8(0x2F61)));
        }
    } else {
        if (*(u8 **)(data + 0x180) != 0) {
            s32 ofs = 0x8710;
            LABEL();
            LABEL50();
            obj = *(u8 **)(data + 0x180);
            switch (*(s16 *)(obj + 0xAA)) {
            case 0xB3A:
                pv = *(u8 **)(obj + 0x68);
                func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                func_00300A00(((char *)func_00336D50(D_L11_001A904C[0] + ofs, 0xE3)), D_L11_001B17B0, D_L11_001B17B4, D_L11_001B17B8, D_L11_001B17C4, 1.0f, 2.0f);
                break;
            case 0xD4A:
                pv = *(u8 **)(obj + 0x68);
                if (*(f32 *)(pv + 0x20) > 0.0f) {
                    func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                }
                func_00300A00(((char *)func_00336D50(D_L11_001A904C[0] + ofs, 0xE3)), D_L11_001B17B0, D_L11_001B17B4, D_L11_001B17B8, D_L11_001B17C4, 1.0f, 1.0f);
                break;
            }
        }
        {
            s32 ofs = 0x8710;
            LBL(0x4E, D_L11_001B17E4, D_L11_001B17D8, D_L11_001B17DC, -1.0f, D_L11_001B17C4, 0.0f);
            LBL(0x4F, D_L11_001B17E0, D_L11_001B17D8, D_L11_001B17DC, -1.0f, D_L11_001B17C4, 0.0f);
        }
        if (*(s16 *)(data + 0x1F0) == 0xA) {
            sprintf_n(buf, D_L11_001B17F8, *(s16 *)(data + 0x1F2) + 1);
        } else {
            sprintf_n(buf, D_L11_001B1800, *(s16 *)(data + 0x1F2) + 1, *D_L11_001B14F8[*(s16 *)(data + 0x1F0)]);
        }
        DRAWBUF(func_00280270, &rF0);
        DRAW(func_00280190, &rD0, ((char *)func_00288FB8(0x2F60)));
    }
    func_002FC560(0x47, 0x5360B);
    func_002FC560(0x47, 0x5360B);
    ((HudRenderState *)D_L11_001BEDC0)->text_scale = save;
    func_0027AB40();
}
