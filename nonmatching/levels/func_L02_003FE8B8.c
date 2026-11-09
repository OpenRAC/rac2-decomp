/* 9 November 2026 (round o44): body below is now the plain-address form at 3568/3552, 29 masked aligned differences (was 3560/33; p3 form 31). Found: the &r70/&rF0 extra copies come from sched1, not gcse. PRE inserts the arm copy at the end of the box block, cse2 turns it into a copy of the box-2 arg pseudo, and a do { } while (0) LOOP_BEG/END note between that call and the block end is a sched barrier, so the copy stays after the next call and the arg pseudo crosses calls in $s0/$fp. Fix: box-3 x as a plain hud_coord statement (block break right after the box-2 call) and box-6 x without its do-while -> box 2 and box 5 now `addiu $a0,$sp,0x70/0xF0` as retail; hill-climb of the other coordinates -> 29 (box-4 h and box-6 h grouped as do { t = ...; h = t; }, box-5 x plain t-form). Left: rB0 and rD0 now take the same late-copy pattern (box 4: $s0 then $s7 after the call, retail copies $s7 before it; box 6: $s1/$fp), the label colour-before-x order, else-arm $v1 vs $v0. Measured, no gain: no-loop-barrier hill-climbs (best 55-68), box-5 x/y forms for rB0 (33-96), a `three` local at box 3 (30, fake local). One 1500 s permuter run from this body: best 27/3568 only through a held `f32 *new_var = &D_L02_001B1410;` (a fake pointer to a global, rejected); earlier bests were a statement before `case 0x9F8:` (never executed). */
/* 9 November 2026 (round o36): body below unchanged (3560/3552, 33). Found: the p70/pF0 locals can never be rematerialized like retail's &r70/&rF0 (a user variable set from &r gets no REG_EQUIV; when it loses its register it goes to a stack slot, +16 frame), so retail used plain &r70/&rF0 (gcse reaching regs, as r50/rD0). Also, gcse kills frame-address expressions at every call (FRAME_POINTER_REGNUM $1 is call-used), so PRE puts r70's reaching copy after box 3's call. Plain-address form: base with p70/pF0 removed, `one = 1;` moved to just before the box-2 call, actives TITLE 0x4C literal 1, LABEL 0x4D one, both 0x51 one, 0x4E/0x4F literal 1 -> 31 diffs at 3568. This reproduces retail's two ghost saves $s4/$s6 and the rematerialized &r70 in arms 3/5. Left in that form: the box-2 arg pseudo crosses two calls in $s0 before the late PRE copy, rF0's reaching reg shares $fp with the 0x1428 base, and the second 3 is set at box 5. Measured, no gain: a fake second `1` local (cse merges it with one), 512 active mixes, move sweeps, box-form hill-climb (8 forms x 18 coords + `one` placement), plain &r90 (44-46/3568+). One 1500 s permuter run from the plain form: best 29/3560 only through `new_var = one;` placed before `case 0x9F8:` (never executed, an uninitialised read); the honest placements score 31/3568. */
/* 9 November 2026 (round o31): body below is 3560/3552 bytes on the cc1 harness, 33 masked aligned differences (was 43). Changes: an `s32 one = 1;` local (owner ruling: existing local holding 1 as label_y active) passed as active to the four -1.0f labels (TITLE 0x4C/0x4D and 0x4E/0x4F), literal 1 elsewhere -> 35 (the TITLE first label now takes $v1: the literal 1 pseudo sat in $v1 across the label_y result; all 512 one/1 mixes scored); LABEL 0x4D x read into a local (`f32 xx = xv;`) -> 41/-2; box-5 y as grouped hud_coord (box hill-climb rerun) -> 33. Measured, no gain: label forms with colour/x/y locals per site (7 forms x 2 actives coordinate descent), lesson-48 single moves (512, none better), `one` placement (no effect), plain &r70/&rF0/&r90 (49-111); &r70 instead of p70 only in the 0x03 arm tail -> 32 (left out: arms 3/5 are identical code). One 1500 s permuter run from this body: only the same &r70 swaps. Callee prototypes checked against src (lesson 47): consistent. Left: TITLE/LABEL labels load the colour before x (lwc1 $f12 vs mov.s $f14 order), else-arm label results $v1 vs retail $v0, the second constant-3 pseudo set at box 5 (retail box 3, $s3), and the p70/p90/pF0 copies (8 bytes). */
/* 8 November 2026 (Sonnet round o25, lesson 49): body below is 3560/3552 bytes (check.py), 0/1, 43 masked aligned differences (this body was 79 at 3556 on the same harness). Changes: label_y written inside the func_00300A00 call (as matched L15_00431590) -> 68 (fixes the int-x labels and the second label of each group: xv load before the colour); block-scoped `s32 ofs = 0x8710;` per arm, the else arm split into the data+0xD0 block and a block around 0x4E/0x4F -> 49 (every arm's 0x8710 register now retail's; borderline local, same precedent as `entry = 0x8710` in func_L08_0041D808); SUM init `obj` before `i` -> 45; box-form hill-climb (6 forms x 18 coordinates + 3 pointer modes): rD0 h grouped -> 44; box 5 h written as hud_coord(...) inside the func_002802E0 call (lesson 49, from the permuter) -> 43; a hill-climb adding in-call forms for every coordinate finds nothing further. Lesson 49 audit: retail never holds &r70/&rF0 (plain &r70/&rF0/&r90: 49-85, PRE copies them to $s regs; retail evicts them and saves ghost $s4/$s6). Left: first label of each group (constant li.s in the block) loads the colour before xv in sched1 and takes $a1 for the label_y result (retail $v1); else-arm labels $v1 vs $v0; box 5/6 constant 3 grouping; box address copies. One 1500 s permuter run from the 44 body: the box-5 in-call h above; its later bests are dishonest (volatile return type, 0x4F held in a variable). */
/* 8 November 2026 (Sonnet round, lesson 48 sweep): scripted moves of every statement by 1..6 (548 singles + 109 pairs) and top-level items (548): best legal is 150 vs base 151 aligned differences (h/pF0 one-step moves, noise), size stays 3556/3552; DRAWBUF with strlen before the colour load 3540 bytes/174, a colour local in DRAW no change. Callee prototypes checked against src: consistent. */
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


#define LBL0(id, c, xv, yv, a1, a2, a3, H, A) { char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); func_00300A00(ls, c, xv, (f32)label_y(ls, (f32)(yv), D_L02_001B3E04, H, A), a1, a2, a3); }
#define LBLB(id, c, xv, yv, a1, a2, a3, H, A) { char *ls = func_00336D50(D_L02_001A904C[0] + ofs, id); f32 xx = xv; func_00300A00(ls, c, xx, (f32)label_y(ls, (f32)(yv), D_L02_001B3E04, H, A), a1, a2, a3); }
#define TITLE() \
        LBL0(0x4C, D_L02_001B1424, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f, half, 1); \
        LBL0(0x4D, D_L02_001B1420, D_L02_001B1410, D_L02_001B1414, -1.0f, D_L02_001B1404, 0.0f, half, one)
#define LABEL() \
        LBL0(0x4C, D_L02_001B1424, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f, half, 1); \
        LBLB(0x4D, D_L02_001B1420, D_L02_001B1408, D_L02_001B140C, D_L02_001B1404, 1.0f, 0.0f, half, one)
#define LABEL50() \
        LBL0(0x50, D_L02_001B1420, D_L02_001B13FC, D_L02_001B1400, D_L02_001B1404, 1.0f, 0.0f, half, 1)
#define SUM() \
            sum = 0; \
            for (obj = data + 0x90, i = 5; i >= 0; i--, obj += 4) { \
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
    Rect *p50;
    Rect *p90;
    Rect *pB0;
    Rect *pD0;
    u8 *data;
    u8 *obj;
    u8 *pv;
    f32 save;
    s32 sum;
    s32 i;
    s32 n;
    f32 t;
    f32 half;
    s32 one;
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
    x = hud_coord((f32)D_L02_001B13C8, D_L02_001B3E04, half);
    t = (f32)D_L02_001B13CC[0] * D_L02_001B3E04 + half; y = t;
    do { h = hud_coord((f32)D_L02_001B13C4, D_L02_001B3E04, half); } while (0);
    one = 1;
    func_002802E0(&r70, x, y, D_L02_001B13D0[0], D_L02_001B13D4[0], D_L02_001B13C0, h, 0, 3);
    x = hud_coord((f32)D_L02_001B1380, D_L02_001B3E04, half);
    do { t = (f32)D_L02_001B1384[0] * D_L02_001B3E04 + half; y = t; } while (0);
    t = (f32)D_L02_001B137C * D_L02_001B3E04 + half; do { h = t; } while (0);
    p90 = &r90;
    func_002802E0(p90, x, y, D_L02_001B1388[0], D_L02_001B138C[0], D_L02_001B1378, h, 0, 3);
    t = (f32)D_L02_001B1368 * D_L02_001B3E04 + half; x = t;
    do { t = (f32)D_L02_001B136C[0] * D_L02_001B3E04 + half; y = t; } while (0);
    do { t = (f32)D_L02_001B1360 * D_L02_001B3E04 + half; h = t; } while (0);
    func_002802E0(&rB0, x, y, D_L02_001B1370[0], D_L02_001B1374[0], D_L02_001B135C, h, 0, 3);
    t = (f32)D_L02_001B13B0 * D_L02_001B3E04 + half; x = t;
    do { y = hud_coord((f32)D_L02_001B13B4[0], D_L02_001B3E04, half); } while (0);
    func_002802E0(&rF0, x, y, D_L02_001B13B8[0], D_L02_001B13BC[0], D_L02_001B13A8, hud_coord((f32)D_L02_001B13AC, D_L02_001B3E04, half), 0, 3);
    x = hud_coord((f32)D_L02_001B1398, D_L02_001B3E04, half);
    do { t = (f32)D_L02_001B139C[0] * D_L02_001B3E04 + half; y = t; } while (0);
    do { t = (f32)D_L02_001B1394 * D_L02_001B3E04 + half; h = t; } while (0);
    func_002802E0(&rD0, x, y, D_L02_001B13A0[0], D_L02_001B13A4[0], D_L02_001B1390, h, 0, 3);
    save = ((HudRenderState *)D_L02_001BEA00)->text_scale;
    ((HudRenderState *)D_L02_001BEA00)->text_scale = 0.62f;
    func_0027AB40();
    if (*(s16 *)(data + 0x120) == 3) {
        s32 ofs = 0x8710;
        TITLE();
        sprintf_n(buf, D_L02_001B1428, 0x1E - *(s32 *)(data + 0xD4) / 60);
        DRAWBUF(func_00280270, p90);
        DRAW(func_00280190, &rB0, func_00288FB8(0x2F63));
        LABEL();
        SUM();
        func_00115DA8(buf, D_L02_001B1428, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(func_00280270, &r50);
        DRAW(func_00280190, &r70, func_00288FB8(0x2F61));
    } else if (*(s16 *)(data + 0x120) == 5) {
        s32 ofs = 0x8710;
        TITLE();
        sprintf_n(buf, D_L02_001B1428, 0x3C - *(s32 *)(data + 0xD4) / 60);
        DRAWBUF(func_00280270, p90);
        DRAW(func_00280190, &rB0, func_00288FB8(0x2F63));
        LABEL();
        SUM();
        func_00115DA8(buf, D_L02_001B1428, 15 * *(s16 *)(data + 0x122) + sum - *(s32 *)(data + 0x60));
        DRAWBUF(func_00280270, &r50);
        DRAW(func_00280190, &r70, func_00288FB8(0x2F61));
    } else if (*(s16 *)(data + 0x120) == 0xC) {
        s32 ofs = 0x8710;
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
        if (*(u8 **)(data + 0xD0) != 0) {
            s32 ofs = 0x8710;
            LABEL();
            LABEL50();
            obj = *(u8 **)(data + 0xD0);
            switch (*(s16 *)(obj + 0xAA)) {
            case 0x9F8:
                pv = *(u8 **)(obj + 0x68);
                func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                LBL0(0x51, D_L02_001B13F0, D_L02_001B13F4, D_L02_001B13F8, D_L02_001B1404, 1.0f, 2.0f, half, one);
                break;
            case 0xA44:
                pv = *(u8 **)(obj + 0x68);
                func_L02_003FE768(*(f32 *)(pv + 0x20) / func_00283CE0(*(s16 *)(pv + 0x24)));
                LBL0(0x51, D_L02_001B13F0, D_L02_001B13F4, D_L02_001B13F8, D_L02_001B1404, 1.0f, 1.0f, half, one);
                break;
            }
        }
        {
        s32 ofs = 0x8710;
        LBL0(0x4E, D_L02_001B1424, D_L02_001B1418, D_L02_001B141C, -1.0f, D_L02_001B1404, 0.0f, 0.5f, 1);
        LBL0(0x4F, D_L02_001B1420, D_L02_001B1418, D_L02_001B141C, -1.0f, D_L02_001B1404, 0.0f, 0.5f, 1);
        }
        func_00115DA8(buf, D_L02_001B1430, *(s16 *)(data + 0x122) + 1, *D_L02_001B1190[*(s16 *)(data + 0x120)]);
        DRAWBUF(func_00280270, &rF0);
        DRAW(func_00280190, &rD0, func_00288FB8(0x2F60));
    }
    func_002FC560(0x47, 0x5360B);
    ((HudRenderState *)D_L02_001BEA00)->text_scale = save;
    func_0027AB40();
}
