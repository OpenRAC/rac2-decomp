/* 8 November 2026, Sonnet round (o7c): body below is 3556/3552 bytes (was 3564), 0/1, about 100
 * aligned words differ (relocations masked). Change: a `half = 0.5f;` local after
 * func_L00_0037B7B0 (precedent: func_L02_003FF6E8, func_L08_0041D808) used by every box chain and
 * label, except the else tail's 0x4E/0x4F labels, which keep a literal 0.5f (LBL5). This removes
 * the box-2 0.5f reload and keeps retail's reload after the data+0xD0 join (all-half: 3548 bytes).
 * Also measured:
 * - Block-scoped `s32 ofs = 0x8710;` per arm, with the else arm split into the
 *   `if (data+0xD0)` block and a block around the 0x4E/0x4F labels: every arm's 0x8710 register
 *   now matches retail ($s3, $s3, $s0, $s1, then $s0). 3568 bytes, about 65 words differ (best
 *   word count). Needs the same owner ruling as the shared `ofs` (precedent: `entry = 0x8710`
 *   in func_L08_0041D808). No ofs at all: 3576 bytes, 79 words.
 * - Ghost saves: retail saves $s4/$s6 and never uses them. A pseudo used only by a dead test
 *   and live across calls does this here: `one = 1` passed as label_y's `active` (or a mode
 *   local read once) leaves $s2 saved and unused, moves data to $s3, and still keeps p70/pF0.
 *   So retail likely had two such dead-test pseudos with lower priority than data; not found.
 * - No gain: plain &r70/&r90/&rF0 in any mix (170-190 words), scaled_coord + s/one locals as in
 *   func_L02_003FF6E8 (337), per-arm `one`, x read into a local before/after label_y,
 *   -fno-gcse (194). One 25-minute permuter run from this body: only no-op rewrites.
 */
/* 8 November 2026, round 2: body below is 3564/3552 bytes (was 3592), 0/1, 105 masked words
 * (the count is higher because of register renames; the shape is closer). Where the round-1 40
 * bytes went: 4 words were the 0x8710 rematerialization at each arm's first label, 6 were box
 * address copies and extra 3s.
 * - Plain y rounding (no helper) per box, as in func_L02_003FE250: no gain here (91 -> 102-148);
 *   this function's copy-across-call comes from gcse PRE inserting each box address after its
 *   call, not from cprop.
 * - Box address locals: p70 set before box 2's chains, p90/pF0 set right before their calls
 *   (scan of 3^6 placements): box 1 now builds $a0 directly; 91 -> 83 at 3584 bytes.
 * - `ofs = 0x8710;` at the start of each arm, used by every label: retail's `ori $s3,0x8710`
 *   at label 1 and all labels share it (-4 words, 3564 bytes). This is borderline (a local
 *   holding a constant only to set allocation); it needs an owner ruling before any landing.
 * - Left (12 bytes): p70/pF0 keep $s5/$fp (retail rematerializes them and saves ghosts
 *   $s4/$s6, which looks like reload evicting them), p90 is in $s3 instead of retail's copy to
 *   $s5, there is an extra 0.5f reload in box 2, and the 3/0x8710 registers are renamed.
 */
/* 8 November 2026, HUD-recipe pass (re-measured on master's compiler): profile now plain
 * -O2 -G8 -ffunction-sections (one config/cflags.txt line, -g8 unit). check.py: 3592/3552 bytes,
 * 0/1. Aligned diff with relocations masked: 91 of 888 words (the 7 November label_y body at
 * this profile: 214; at -fno-schedule-insns: 222). Body below.
 * Measured:
 * - hud_coord (dead-test helper, owner ruling) on the box coordinates plus one-pass groups
 *   (`do { y = t; } while (0)`) give retail's chain order (x, y, h, then the arguments) and
 *   retail's constant-3 grouping: one pseudo for boxes 1-4, a fresh li for box 5, one for box 6
 *   and the mode test (set at box 3). The mix per coordinate came from a hill-climb over
 *   {plain, t-copy, group, hud_coord, grouped hud_coord}; uniform forms score 99-200.
 * - Rect *p90/pB0 locals for the two boxes the three timed arms reuse: 99 -> 91.
 * - Left (all allocation, 10 extra words): (1) gcse inserts each box address after the box's
 *   call and cse2 turns that into a copy of the argument pseudo, so the argument pseudo crosses
 *   the call and takes $s0 (`addiu $s0,$sp,0x50; daddu $a0,$s0`); retail builds $a0 directly
 *   and keeps only &r90/&rB0 (copies to $s5/$s7, rest rematerialized). (2) The 0x8710 sprite
 *   base: cse1 groups each arm's labels under the first label's pseudo (as retail), but cse2's
 *   10-branch windows make the second label's pseudo canonical, so label 1 rematerializes into
 *   $a0 and the group lives in $s3/$s4 from label 2 (retail: `ori $s3` at label 1). Label_y
 *   variants with 1-2 tests fix (2) but break the label scheduling. (3) Callee-saved roles
 *   shift with these ($s1/$s3 for the 3s, ghosts $s4/$s6 not reproduced).
 * - No effect / worse: switch for the outer dispatch (+20), -fno-schedule-insns, -fno-gcse,
 *   -fno-rerun-cse-after-loop, -fno-cse-skip-blocks/-follow-jumps, -fno-expensive-optimizations,
 *   -fno-sched-interblock, -fmove-all-movables, `one = 1` label active, separate x local.
 */
/* 7 November 2026, label_y sweep: LBL's sprite y is label_y(ls, (f32)(yv), D_L02_001B3E04, 0.5f, 1), mode D_L02_001B3E00 (accepted HUD label idiom, definition above the function). Same profile (-fno-schedule-insns): 3568/3552 bytes (was 3560), sweep-harness masked aligned diff 509 -> 341; plain -O2 -G8 -ffunction-sections gives 310. Still far: size off by 16. */
/* Claude Opus 5.5 (xhigh), task v1870, 31 October 2026.
 * Near miss, USA v1.01 level 02: 3560/3552 bytes, 0 of 1 places match; frame 0x180 and the
 * save set agree. 572 of retail's 888 words lie in a common subsequence that ignores relocated
 * immediates (earlier draft v1584, recompiled at its own profile here: 3596 bytes, 429 words).
 * PAL and USA v2.00 have no catalogue row for this name.
 * Profile: -O2 -G8 -ffunction-sections -fno-schedule-insns, in a dedicated -g8 unit (one
 * config/cflags.txt line). Declarations are below. No linked build; the marker is restored.
 *
 * Established, each measured:
 * - Split addresses stay ON. Retail splits `lui $s0` from `addiu $s0,$s0,lo` across a jal, so
 *   -mno-split-addresses (earlier drafts) is wrong. The tied `lui $a3; lw $a3,lo($a3)` and
 *   `lui $at; lwc1` forms come from `sda` on the incomplete arrays (COMPILER-NOTES).
 * - A shared `t` (`t = (f32)X * S + 0.5f; x = t;`) gives retail's chains exactly: value $f0,
 *   scale $f1, scratch $f2 ($f1 on the third), each `fix` in place. Reassigning t stops combine
 *   moving the fix down into the argument copy; direct expressions interleave the chains.
 * - A switch gives retail's boss dispatch word for word without -frac2-keep-block-order.
 * - Passing buf directly (not through `str`) gives the rematerialized `addiu $a0,$sp,0x10`.
 *
 * Still different:
 * 1. Retail saves $s4 and $s6 and never uses them, and rematerializes &r50 and &r70 at every
 *    use. That is what a pseudo allocated by global-alloc and then evicted by reload looks like
 *    (see nonmatching/levels/func_L02_003FF6E8.c and the open "register saved and never used"
 *    row in MATCHING-BLOCKERS). Here those pseudos keep $s6/$s5. This blocks an exact match
 *    and looks compiler-side, not a source shape.
 * 2. Retail keeps every argument set-up after the coordinate chain (rectangles and labels);
 *    sched2 here fills the chains' latency gaps with them. Only the copy of the call result to
 *    $a0 and `data` move early in retail. A do-while (0) around the calls (not allowed, measured
 *    as a diagnostic only) does stop the filling and gives the else tail's $f20/$f21/$f22, but
 *    the whole function is then 3568 bytes and 577 words: it is not an exact-bytes form.
 *    A real test per chain is ruled out: 0.5f stays in one register from the first rectangle
 *    through the mode arms, retail reloads it only after the `data+0xD0` join, and cse paths
 *    hold about ten branches.
 * 3. 0.5f is $f20 through the mode arms in retail; here -1.0f and 0.0f are local-allocated
 *    first, so it lands in $f22. $s2 (data) and the callee-saved roles differ with it.
 * 4. Retail copies addresses out of the argument register (`addiu $a0,$sp,0x90; daddu $s5,$a0`,
 *    likewise rB0, and `lui $s0; daddu $fp,$s0` for the %hi of D_L02_001B1428), which is gcse's
 *    reaching-register shape; not reproduced. The constant 3 is $s1 for rectangles 1-4, $v0 for
 *    5 and $s3 for 6 and the mode test; here it is one register.
 * Whole-file -fno-sched-interblock and -fno-rerun-loop-opt change nothing;
 * -fno-schedule-insns2 is worse (3564 bytes, 506 words).
 */
#include "common.h"

typedef struct {
    u16 w[12];
} Rect;

extern s32 D_L02_001A904C[] __attribute__((sda));
extern f32 D_L02_001B3E04;
typedef struct {
    u8 pad[0xB0];
    f32 text_scale;
} HudRenderState;
extern u8 D_L02_001BEA00[];
extern char D_L02_001B1428[];
extern char D_L02_001B1430[];
extern s16 *D_L02_001B1190[] SDATA(D_L02_001B1190);
extern s32 D_L02_001B1358 __attribute__((sda));

extern s32 D_L02_001B13D8 __attribute__((sda));
extern s32 D_L02_001B13DC __attribute__((sda));
extern s32 D_L02_001B13E0 __attribute__((sda));
extern s32 D_L02_001B13E4[] __attribute__((sda));
extern s32 D_L02_001B13E8[] __attribute__((sda));
extern s32 D_L02_001B13EC[] __attribute__((sda));
extern s32 D_L02_001B13C0 __attribute__((sda));
extern s32 D_L02_001B13C4 __attribute__((sda));
extern s32 D_L02_001B13C8 __attribute__((sda));
extern s32 D_L02_001B13CC[] __attribute__((sda));
extern s32 D_L02_001B13D0[] __attribute__((sda));
extern s32 D_L02_001B13D4[] __attribute__((sda));
extern s32 D_L02_001B1378 __attribute__((sda));
extern s32 D_L02_001B137C __attribute__((sda));
extern s32 D_L02_001B1380 __attribute__((sda));
extern s32 D_L02_001B1384[] __attribute__((sda));
extern s32 D_L02_001B1388[] __attribute__((sda));
extern s32 D_L02_001B138C[] __attribute__((sda));
extern s32 D_L02_001B135C __attribute__((sda));
extern s32 D_L02_001B1360 __attribute__((sda));
extern s32 D_L02_001B1368 __attribute__((sda));
extern s32 D_L02_001B136C[] __attribute__((sda));
extern s32 D_L02_001B1370[] __attribute__((sda));
extern s32 D_L02_001B1374[] __attribute__((sda));
extern s32 D_L02_001B13A8 __attribute__((sda));
extern s32 D_L02_001B13AC __attribute__((sda));
extern s32 D_L02_001B13B0 __attribute__((sda));
extern s32 D_L02_001B13B4[] __attribute__((sda));
extern s32 D_L02_001B13B8[] __attribute__((sda));
extern s32 D_L02_001B13BC[] __attribute__((sda));
extern s32 D_L02_001B1390 __attribute__((sda));
extern s32 D_L02_001B1394 __attribute__((sda));
extern s32 D_L02_001B1398 __attribute__((sda));
extern s32 D_L02_001B139C[] __attribute__((sda));
extern s32 D_L02_001B13A0[] __attribute__((sda));
extern s32 D_L02_001B13A4[] __attribute__((sda));

extern s32 D_L02_001B13F0 __attribute__((sda));
extern s32 D_L02_001B13F4 __attribute__((sda));
extern s32 D_L02_001B13F8 __attribute__((sda));
extern s32 D_L02_001B13FC __attribute__((sda));
extern s32 D_L02_001B1400 __attribute__((sda));
extern f32 D_L02_001B1404 __attribute__((sda));
extern f32 D_L02_001B1408 __attribute__((sda));
extern f32 D_L02_001B140C __attribute__((sda));
extern f32 D_L02_001B1410 __attribute__((sda));
extern f32 D_L02_001B1414 __attribute__((sda));
extern f32 D_L02_001B1418 __attribute__((sda));
extern f32 D_L02_001B141C __attribute__((sda));
extern s32 D_L02_001B1420 __attribute__((sda));
extern s32 D_L02_001B1424 __attribute__((sda));

extern void func_0027AB40(void);
extern void func_00280190(Rect *, u64, char *, s32);
extern void func_00280270(Rect *, u64, char *, s32);
extern void func_002802E0(Rect *, s32, s32, s32, s32, s32, s32, s32, s32);
extern f32 func_00283CE0(s32);
extern char *func_00288FB8(s32);
extern void func_002FC560(u32, u64);
extern void func_L00_0037B7B0(void);
extern void func_00300A00(char *, s32, f32, f32, f32, f32, f32);
extern void func_L02_003FE768(f32);
extern char *func_00336D50(s32, s32);
extern s32 func_001157AC(char *);
extern s32 func_00115DA8(char *, char *, ...);

#define Scale(v) ((s32)((f32)(v) * D_L02_001B3E04 + 0.5f))


#define LBL(id, c, xv, yv, a1, a2, a3) { \
        char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); \
        s32 ly = label_y(ls, (f32)(yv), D_L02_001B3E04, half, 1); \
        func_00300A00(ls, c, xv, ly, a1, a2, a3); }
#define LBL5(id, c, xv, yv, a1, a2, a3) { \
        char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); \
        s32 ly = label_y(ls, (f32)(yv), D_L02_001B3E04, 0.5f, 1); \
        func_00300A00(ls, c, xv, ly, a1, a2, a3); }
#define TITLE() \
        LBL(0x4C, D_L02_001B1424, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f); \
        LBL(0x4D, D_L02_001B1420, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f)
#define LABEL() \
        LBL(0x4C, D_L02_001B1424, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f); \
        LBL(0x4D, D_L02_001B1420, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f)
#define LABEL50() \
        LBL(0x50, D_L02_001B1420, D_L02_001B13FC, D_L02_001B1400, D_L02_001B1404, 1.0f, 0.0f)
#define SUM() \
            sum = 0; \
            for (i = 5, obj = data + 0x90; i >= 0; i--, obj += 4) { \
                sum += *(s32 *)obj; \
            }
#define DRAW(fn, r, s) \
            str = (s); \
            fn((r), D_L02_001B1358, str, func_001157AC(str))
#define DRAWBUF(fn, r) \
            { s32 c = D_L02_001B1358; s32 n = func_001157AC(buf); fn((r), c, buf, n); }
#define sprintf_n func_00115DA8

extern int D_L02_001B3E00;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
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
    int mode = D_L02_001B3E00;
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

void func_L02_003FE8B8(u8 *moby)
{
    char buf[0x40];
    Rect r50;
    Rect r70;
    Rect r90;
    Rect rB0;
    Rect rD0;
    Rect rF0;
    Rect *p70;
    Rect *p90;
    Rect *pF0;
    u8 *data;
    u8 *obj;
    u8 *pv;
    f32 save;
    s32 sum;
    s32 i;
    s32 ofs;
    s32 n;
    f32 t;
    f32 half;
    s32 x, y, h;
    char *str;

    if (D_L02_001A904C[0] == 0) {
        return;
    }
    func_L00_0037B7B0();
    half = 0.5f;
    data = *(u8 **)(moby + 0x68);
    x = hud_coord((f32)D_L02_001B13E0, D_L02_001B3E04, half);
    y = hud_coord((f32)D_L02_001B13E4[0], D_L02_001B3E04, half);
    h = hud_coord((f32)D_L02_001B13DC, D_L02_001B3E04, half);
    func_002802E0(&r50, x, y, D_L02_001B13E8[0], D_L02_001B13EC[0], D_L02_001B13D8, h, 0, 3);
    p70 = &r70;
    x = hud_coord((f32)D_L02_001B13C8, D_L02_001B3E04, half);
    t = (f32)D_L02_001B13CC[0] * D_L02_001B3E04 + half; y = t;
    do { h = hud_coord((f32)D_L02_001B13C4, D_L02_001B3E04, half); } while (0);
    func_002802E0(p70, x, y, D_L02_001B13D0[0], D_L02_001B13D4[0], D_L02_001B13C0, h, 0, 3);
    t = (f32)D_L02_001B1380 * D_L02_001B3E04 + half; x = t;
    do { t = (f32)D_L02_001B1384[0] * D_L02_001B3E04 + half; y = t; } while (0);
    t = (f32)D_L02_001B137C * D_L02_001B3E04 + half; do { h = t; } while (0);
    p90 = &r90;
    func_002802E0(p90, x, y, D_L02_001B1388[0], D_L02_001B138C[0], D_L02_001B1378, h, 0, 3);
    t = (f32)D_L02_001B1368 * D_L02_001B3E04 + half; x = t;
    do { t = (f32)D_L02_001B136C[0] * D_L02_001B3E04 + half; y = t; } while (0);
    do { h = hud_coord((f32)D_L02_001B1360, D_L02_001B3E04, half); } while (0);
    func_002802E0(&rB0, x, y, D_L02_001B1370[0], D_L02_001B1374[0], D_L02_001B135C, h, 0, 3);
    x = hud_coord((f32)D_L02_001B13B0, D_L02_001B3E04, half);
    do { t = (f32)D_L02_001B13B4[0] * D_L02_001B3E04 + half; y = t; } while (0);
    h = hud_coord((f32)D_L02_001B13AC, D_L02_001B3E04, half);
    pF0 = &rF0;
    func_002802E0(pF0, x, y, D_L02_001B13B8[0], D_L02_001B13BC[0], D_L02_001B13A8, h, 0, 3);
    do { x = hud_coord((f32)D_L02_001B1398, D_L02_001B3E04, half); } while (0);
    do { t = (f32)D_L02_001B139C[0] * D_L02_001B3E04 + half; y = t; } while (0);
    h = hud_coord((f32)D_L02_001B1394, D_L02_001B3E04, half);
    func_002802E0(&rD0, x, y, D_L02_001B13A0[0], D_L02_001B13A4[0], D_L02_001B1390, h, 0, 3);
    save = ((HudRenderState *)D_L02_001BEA00)->text_scale;
    ((HudRenderState *)D_L02_001BEA00)->text_scale = 0.62f;
    func_0027AB40();
    if (*(s16 *)(data + 0x120) == 3) {
        ofs = 0x8710;
        TITLE();
        sprintf_n(buf, D_L02_001B1428, 0x1E - *(s32 *)(data + 0xD4) / 60);
        DRAWBUF(func_00280270, p90);
        DRAW(func_00280190, &rB0, func_00288FB8(0x2F63));
        LABEL();
        SUM();
        func_00115DA8(buf, D_L02_001B1428, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(func_00280270, &r50);
        DRAW(func_00280190, p70, func_00288FB8(0x2F61));
    } else if (*(s16 *)(data + 0x120) == 5) {
        ofs = 0x8710;
        TITLE();
        sprintf_n(buf, D_L02_001B1428, 0x3C - *(s32 *)(data + 0xD4) / 60);
        DRAWBUF(func_00280270, p90);
        DRAW(func_00280190, &rB0, func_00288FB8(0x2F63));
        LABEL();
        SUM();
        func_00115DA8(buf, D_L02_001B1428, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(func_00280270, &r50);
        DRAW(func_00280190, p70, func_00288FB8(0x2F61));
    } else if (*(s16 *)(data + 0x120) == 0xC) {
        ofs = 0x8710;
        TITLE();
        n = 120 - *(s32 *)(data + 0xD4) / 60;
        func_00115DA8(buf, D_L02_001B1428, n);
        if (n >= 100) {
            DRAWBUF(func_00280190, p90);
        } else {
            DRAWBUF(func_00280270, p90);
        }
        DRAW(func_00280190, &rB0, func_00288FB8(0x2F63));
    } else {
        ofs = 0x8710;
        if (*(u8 **)(data + 0xD0) != 0) {
            LABEL();
            LABEL50();
            obj = *(u8 **)(data + 0xD0);
            switch (*(s16 *)(obj + 0xAA)) {
            case 0x9F8:
                pv = *(u8 **)(obj + 0x68);
                func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                LBL(0x51, D_L02_001B13F0, D_L02_001B13F4, D_L02_001B13F8, D_L02_001B1404, 1.0f, 2.0f);
                break;
            case 0xA44:
                pv = *(u8 **)(obj + 0x68);
                func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                LBL(0x51, D_L02_001B13F0, D_L02_001B13F4, D_L02_001B13F8, D_L02_001B1404, 1.0f, 1.0f);
                break;
            }
        }
        LBL5(0x4E, D_L02_001B1424, D_L02_001B1418, D_L02_001B141C, -1.0f, D_L02_001B1404, 0.0f);
        LBL5(0x4F, D_L02_001B1420, D_L02_001B1418, D_L02_001B141C, -1.0f, D_L02_001B1404, 0.0f);
        func_00115DA8(buf, D_L02_001B1430, *(s16 *)(data + 0x122) + 1, *D_L02_001B1190[*(s16 *)(data + 0x120)]);
        DRAWBUF(func_00280270, pF0);
        DRAW(func_00280190, &rD0, func_00288FB8(0x2F60));
    }
    func_002FC560(0x47, 0x5360B);
    ((HudRenderState *)D_L02_001BEA00)->text_scale = save;
    func_0027AB40();
}
