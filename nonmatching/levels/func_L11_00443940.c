/* 8 November 2026 (compiler matrix, scratch only): retained C compiled with 10 EE cc1 builds at the same flags (-frac2-* dropped for non-local builds), our as: local 991111; decomp.me 2.9-ee-991111a, 991111-01, 991111b (= SN SDK 2.4's 991111); Sony 2.96-ee-001003-1; SN 2.95.2 v2.73a/v2.74, 2.95.3 v1.07/v1.14/v1.36 (no 990721 build available). No build gives retail's draws 3/4 order (+0x1E0, +0x25C): every other build is longer (988-1092 bytes) and neither ours nor retail there. Not a compiler-build difference. */
/* 8 November 2026 (round 14): no gain, C below unchanged. Worked on the twin func_L02_003FDDE8 (same draws 3/4 problem); see its note for the sched1 trace (copy beats `one = 1` on register weight, x waits on fmac) and the ~55 forms measured there (lesson 43 plain rounding plus do-while colour, gcse on, separate x local, late text copy, label_y variants): none improved, so nothing was ported. */
/* 8 November 2026 (round 13, USA v1.01, check.py only): best C below 924/924 bytes, 0/1 places, 18 differing words (was 20). label_y now in all four draws; in draws 3/4 `active` is a local `one` set to 1 right after each label call (per the owner ruling on a local holding 1, func_L01_002F1588). That removes the ghost $s6 of the literal 1 in the loop. Setting `one` once for the whole function, or once before `if (enabled)`, puts it in a saved register (928 bytes, 150+ words). Draw 3's rounded int is now right. Left: the label copy in draws 3/4 still issues before the x conversion. No gain (~12 runs): every order of one/c/x in draws 3 and 4 (18); x and label_y written as call arguments (904 bytes, 181 words; or 18). */
/* 8 November 2026 (round 12, USA v1.01, check.py only): best C below 924/924 bytes, 0/1 places, 20 differing words (was 24 with the round-14 C, same count). Pair check: L02_003FDDE8 and L11_00443940 are the same routine (opcode diff: L02 has one extra saved register and the i == 8 entry test). label_y (master L15_00431590-g8.c form, label as handle, literal 1) in draws 1/2 fixes them fully: the label copy now lands in $a2 as in retail. label_y inside the loop (0x4a draw) hoists its constant 1 into a ghost $s6 (928 bytes, loop.c movable), so draws 3/4 use hud_coord (L05_0037A5F8-g8.c form); scaled_coord there gives the same rows. Left: draws 3/4 only. sched1 order here is y, scale, half, hi, field, COPY, mul, alt, andi, mode, movz, x; retail's registers need x issued before the copy (copy after andi), so $v0 stays busy and field/int take $v1, hi $a0. No gain (~45 runs): c/x/y orders with both helpers (19-27), handle = c, label_y with handle tests first (parked form, 19), if/else and split colour forms (19-40), separate late label variable (916 bytes), `label = text` copy before the helper (19), c reused for the field (int right, field in $a1, 21 words). Flags: -O2 -G8 -ffunction-sections -fno-rerun-loop-opt -fno-gcse. */
/* 8 November 2026 (round 9, rank_for_schedule): base 924/924, 21 differing words (retained C, recorded flags). rank_for_schedule is identical in GCC 2.95/2.95.2/2.95.3 and EE 991111/991111b; SN 2.95.2 v2.73a makes the same tie choice where its output is comparable. Env probes (sched1/sched2/both): reg weight swapped/clamped/dropped/after class/positive-or-negative only, class dropped/reversed, dependent count reversed/dropped/data-only/clamped, LUID reversed, INSN_UID ties, no birthing boost: none improves any of the nine cluster targets; forced on, every variant changes 6-7124 of 8761 matched units. Hypothesis falsified. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 924/924, 23 differences with the owner-allowed dead-test helper (label copy issued before the rounding fix in the 0x4b/0x4a draws, as in func_L02_003FDDE8). */
/* 7 November 2026, round 14, USA v1.01, check.py only (~75 runs): dead-test helper now
 * allowed by owner ruling. Best C below: 924/924 bytes, 0/1 places, 23 real rows (was 25).
 * Change: the helper returns (float)result after the test instead of converting first;
 * this fixes the first two draws' sched2 order (mtc1 f21 / lwc1 f14 before daddu a0).
 * Left: label v1 not a2 (4 rows in draws 1-2) and the 0x4b/0x4a draws: retail field v1
 * (hi a0), andi v1, rounded int v1; here hi v1/field a0 (local-alloc: hi life 2 beats
 * field life 5) and int v0. Retail needs v0 busy over the field and the int, i.e. sched1
 * putting the label copy after the fix in the late draws; here it issues at t=7-8.
 * Label gets a2 only when a pseudo in v1 is allocated first: colour after fy in 0x4a
 * (X,F,C: mode in v1, 26 rows) or field via c (27 rows); both break the late draws.
 * No gain: helper written exactly like the matched ones (904), int return (904), literal
 * 1/one/half swaps, all c/x/fy orders in both late draws (23-32 or 904), pad/if colour
 * forms, separate late labels (904/916), helper param orders, -fno-sched-interblock (no
 * effect), do-while(0) groups around fy/c/x/label/draw (37-200 or 904/928).
 */
/* 6 November 2026, round 10b: no admissible donor. Every other copy of this routine (L02_003FDDE8; the 194-instruction copy in levels 02/03/04/09/12/17/20/30; L04_0040C880, L11_003FC4D8) is unmatched, and every matched sibling of the rounding helper (L11_004456A0, L02_003FF6E8, L00_004003F0, L00_003DDEC8, game 0032F3D0/002D2188/00326A10) uses the same dead display-mode test. Retail's daddu a2,v0 ... daddu a0,a2 needs a block boundary between the label call and the draw; without the dead test lesson-27 flags, -frac2-* switches and nested calls stay at 904-924 bytes. */
/* 6 November 2026 (Codex follow-up), USA v1.01, check.py only:
 * Retained round-7 C unchanged: 924/924 bytes, 0/1 places. The baseline has
 * 25 instruction-word differences when relocation immediate bits are excluded
 * (the older 43-row count uses a different normalization). No improvement.
 * The helper's dead display-mode test/assignment is not eligible under the
 * current prohibition on constructs used only to steer the compiler; retain
 * it here as historical evidence, not as an approved source method.
 * New experiment: remove that dead test, then group only real operations.
 * Plain removal gives 904 bytes. Tested all 10 contiguous groups over the
 * helper's half/add/round/float-conversion statements, 8 draw-setup group
 * ranges, and 48 combinations of those groups (67 new candidates total).
 * Bodies range from 904 to 928 bytes; none matches or improves the retained
 * baseline. Every group preserves statement order and initialized uses.
 * No donor found in current RAC1/RAC4 searches. Next useful input: an evidenced
 * rounding-helper source/control-flow shape that retains the label copies
 * without a dead test. Source marker and flags restored; no linked build run.
 */
/* 6 November 2026 (round 7), USA v1.01, check.py only: best C below unchanged
 * (924/924, 0/1, 43 rows). Global-alloc dump: label (pseudo set 4 times, 10
 * refs, life 47) is allocated before the dead mode/active pseudos, so it takes
 * any free low register; it gets a2 only when a local field value sits in v1
 * across its copy. Writing the 0x4a field through c
 * (`c = field; c = (c & 0x2000) ? D_L11_001B1648 : color;`) does that: label
 * a2 in all four draws (45 rows; the field then is a1, not v1). Retail's 0x4b
 * and 0x4a draws (rounded int in v1, field hi a0/field v1) imply sched1 put the
 * label copy after the fix there, before it in the first two draws. Tried
 * without gain (~280 runs): field via phase/i/one/entry/label, two-step and if
 * colour forms, literal 1 for active, separate labels per draw (combine merges
 * the copy, 62-189 rows), all 36 c/x/fy orders in both late draws, and
 * 180 hill-climb steps over helper and entry statements.
 */
/* 6 November 2026 (round 6), USA v1.01, check.py only: size fixed, 924/924 bytes,
 * 0/1 placements, 43 normalized rows differ (73 before the half fix), under -O2 -G8 -ffunction-sections
 * -fno-rerun-loop-opt -fno-gcse (-g makes no difference). Not a match.
 * Fix for the four label copies (lessons 16/18): the inline helper with a dead
 * display-mode test (as func_L11_004456A0) splits blocks, so combine keeps the
 * label copy; converting to float inside the helper keeps the result local in v0;
 * computing the colour before the rounding in the 0x4b/0x4a draws puts the field
 * hi part in a0; one shared label variable then conflicts with v0/v1/a0/a1 and
 * gets a2, as in retail. entry/half/one/sc/z variables with -fno-gcse give the
 * retail prologue (s1 = 0x8710, f22/f20/f21) and the pulse must use sc.
 * Loop hoist of the in-loop 0.5f (retail mtc1 into f2, a constant, not a
 * load): the inline param temp had life 3 (two block notes) and was moved;
 * copying the param into a local just before the add (`h = half; scaled =
 * scaled + h;`) makes the constant load adjacent (life 1, not desirable).
 * Param order, const param, product/sum arguments, `scaled += half` and a
 * block macro (the test then dies, 904 bytes) did not.
 * Remaining (43 rows, all register choice): the label now gets v1, not a2,
 * because it lost its v1 conflict. In the 0x4b draw local-alloc gives the
 * field hi part v1 and the field a0 (retail hi a0, field v1); in the 0x4a draw
 * sched1 puts the label copy before the field load (retail after), so the field
 * takes v0. The dead active/mode pseudos sit in a3/a2 there. Tried: colour as
 * ternary/if/negated forms, `one` in the enabled calls (196 rows), mode in the
 * condition, flag probes (-g, -fno-regmove, -frac2-hazard-labels, ...), and
 * 105 hill-climb steps over statement order: no gain.
 */
/* 6 November 2026, USA v1.01, check.py only: retained original best C,
 * 904/924 bytes, 0/1 placements, frame 0x60, under -O2 -G8
 * -ffunction-sections -fno-rerun-loop-opt. No new match.
 * New trials: real one-pass groups around draws, rounding and the initial
 * draw pair; inline rounding helper; and scratch reuse for label/rounded y.
 * These stay 904 bytes. Six additional physical-ABI-preserving interleavings
 * (within-bank argument order/count/width unchanged) also tie at 904.
 * A 64-bit label local reaches 924 bytes through dsll32/dsra32 sign-extension
 * pairs, NOT retail's two daddu copies; narrowing it explicitly before the
 * pointer cast does not remove them. That size-only route is rejected.
 * Retain the original 32-bit address contract and the original remaining
 * blockers: four label copies, saved GPR/FP allocation and draw scheduling.
 * No suitable donor found in RAC1/RAC4 searches. Historical note follows.
 */
/* Retained manual C reconstruction; not linked and not matching.
 * Profile: -O2 -G8 -ffunction-sections
 * Local tools/check.py measurements: us: 908 compiled bytes, 0/1 placements, exit 1; us2: 908 compiled bytes, 0/1 placements, exit 1; pal: 908 compiled bytes, 0/1 placements, exit 1.
 * Retail extent: 924 bytes. No exact-C credit and no full build performed.
 * Residual: 908 versus 924 bytes (-16), 0x60 frame. GP coordinate/color objects are explicit; FP argument order/saved registers and selection loop scheduling differ. Joba has one special entry.
 * Reopen: Reopen with a qualified selection-table layout and measured pulse/label allocation hypothesis.
 * Arrays with unknown total extent remain incomplete. Pointer-offset views do
 * not establish the full sizes or ownership of game records.
 *
 * 2026-11-03 (USA v1.01, 11:00443940, check.py only; about 35 compiles):
 * - Callees verified against retail jal targets (func_00336D50 = 11:0048DFD0,
 *   func_00300A00 = 11:00394D98, func_L00_0037B7B0 = 11:00390018,
 *   func_00283D38 = 11:00301748, func_00288D58 = 11:00306870,
 *   func_002FC560 = 11:0038FD70, func_L11_0043E108). No semantic error found.
 * - Body below now uses the sibling func_L11_00443498 shapes: MenuRecord for
 *   D_L11_00279BA0 (retail adds base then reads +4) and an SDATA incomplete
 *   table for D_L11_001B14F8, emitted as one `la` that gas turns into retail's
 *   `addiu $v1,$gp,0x2508`. Default profile: 912 bytes.
 * - Loop: retail recomputes the table address every iteration (la/sll/addu,
 *   lw a1, jal, lw a0,8(a1)) and does not hoist 8, 0xE0 or 0x8710. loop.c
 *   pass 1 (69 insns) keeps the la (savings 1, threshold already lowered by
 *   the moved lui/addiu pairs), so no giv. -frerun-loop-opt's pass 2 (59 insns)
 *   hoists the la (initial threshold 60 or 61; each move lowers it by 3) and
 *   then strength-reduces TABLE[i]. Adding `-fno-rerun-loop-opt` to the unit
 *   (profile already used by 7 files) reproduces retail's whole loop shape and
 *   registers s1..s5 exactly: 904 bytes. Source alternatives tried without
 *   effect on the pass-2 count: if-based colour, combined condition, inline
 *   rounding helper; a while loop with three `i++` stops the reduction
 *   (biv_count 2) but hoists the la and does not cross-jump; an inline
 *   availability helper moves the draw out of the loop.
 * - Remaining -20 bytes with that profile: (1) each of the four
 *   func_00300A00 calls in retail keeps the label in a separate pseudo
 *   (`daddu a2,v0` after the text call, `daddu a0,a2` in front of/in the
 *   draw call's delay slot); here combine merges label into a0
 *   (`(set a0 v0)`) and sched1 lifts it. Not changed by a nested call,
 *   an FP-first prototype order, -fno-regmove, -fno-gcse,
 *   -fno-expensive-optimizations, -fno-cse-skip-blocks, -f(no-)force-mem,
 *   -fno-caller-saves; -fno-schedule-insns keeps the late copy but loses
 *   all retail scheduling. (2) retail's loop head carries one alignment nop
 *   (0x443BA4); expected to follow once the four copies restore the layout.
 *   (3) Entry allocation: retail object s0, 0x8710 s1 (later colour),
 *   state s2, 0.5f f22, 1.0f f20, 0.0f f21 loaded late; here object s1,
 *   0x8710 s0, 0.5f f21, 1.0f f22 loaded early.
 * - Next: find why combine keeps the label copy (something setting v0 or a
 *   block boundary between the text call and the draw call's argument
 *   moves), then recheck entry allocation.
 */
/* Draws the contextual selection help and locates the next available entry. */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int field1a0;
} InputView;
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xdb];
} MenuRecord;
extern u8 *D_L11_001A904C;
extern float D_L11_001B3E04;
extern int D_L11_001B30C8;
extern unsigned char D_00138180[];
extern unsigned char D_00139568[], D_001395B8[];
extern unsigned char D_L11_00279BA0[];
/* The class pointer table is addressed through gp. */
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
extern void func_L00_0037B7B0(void);
extern int func_00336D50(u8 *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern int func_L11_0043E108(unsigned int);
extern int func_00288D58(void);
extern void func_002FC560(unsigned int, unsigned long long);
extern float D_L11_001B161C __attribute__((sda));
extern int D_L11_001B1620 __attribute__((sda));
extern int D_L11_001B1624 __attribute__((sda));
extern int D_L11_001B1628 __attribute__((sda));
extern int D_L11_001B162C __attribute__((sda));
extern int D_L11_001B1630 __attribute__((sda));
extern int D_L11_001B1634 __attribute__((sda));
extern unsigned int D_L11_001B1638 __attribute__((sda));
extern unsigned int D_L11_001B163C __attribute__((sda));
extern unsigned int D_L11_001B1644 __attribute__((sda));
extern unsigned int D_L11_001B1648 __attribute__((sda));

extern int D_L11_001B3E00;

/* label_y: dead-test HUD helper allowed by owner ruling (7 November 2026; precedent
   src/levels/15_gorn/L15_00431590-g8.c); `one` as active per the func_L01_002F1588 ruling. */
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

void func_L11_00443940(u8 *object, int enabled)
{
    u8 *state;
    int label, phase, i, one, entry;
    unsigned int color, c;
    float x, fy, pulse, half, sc, z;
    if (D_L11_001A904C == 0) return;
    func_L00_0037B7B0();
    entry = 0x8710;
    state = *(u8 **)(object + 0x68);
    half = 0.5f;

    label = func_00336D50(D_L11_001A904C + entry, 0x49);
    x = (float)D_L11_001B1620;
    fy = (float)label_y((void *)label, (float)D_L11_001B1624, D_L11_001B3E04, half, 1);
    sc = 1.0f;
    z = 0.0f;
    func_00300A00((char *)label, D_L11_001B163C, x, fy, D_L11_001B161C, sc, z);
    label = func_00336D50(D_L11_001A904C + entry, 0x48);
    x = (float)D_L11_001B1620;
    fy = (float)label_y((void *)label, (float)D_L11_001B1624, D_L11_001B3E04, half, 1);
    func_00300A00((char *)label, D_L11_001B1638, x, fy, D_L11_001B161C, sc, z);
    phase = D_L11_001B30C8 % 50;
    if (phase >= 25) pulse = sc - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = func_00283D38(D_L11_001B1638, D_L11_001B163C, pulse);
    if (enabled) {
        if (*(short *)(state + 0x1e8) != 0) {
            label = func_00336D50(D_L11_001A904C + 0x8710, 0x4b);
            one = 1;
            c = (((InputView *)D_00138180)->field1a0 & 0x8000) ? D_L11_001B1644 : color;
            x = (float)D_L11_001B1628;
            fy = (float)label_y((void *)label, (float)D_L11_001B162C, D_L11_001B3E04, 0.5f, one);
            func_00300A00((char *)label, c, x, fy, D_L11_001B161C, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x1e8) + 1; i < 13; i++) {
            if (!D_001395B8[func_L11_0043E108(D_L11_001B14F8[i][2])]) continue;
            if (i >= 11 && !func_00288D58()) continue;
            if (i == 8) {
                MenuRecord *choice = (MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0);
                if (!choice->enabled) continue;
            }
            label = func_00336D50(D_L11_001A904C + 0x8710, 0x4a);
            one = 1;
            c = (((InputView *)D_00138180)->field1a0 & 0x2000) ? D_L11_001B1648 : color;
            x = (float)D_L11_001B1630;
            fy = (float)label_y((void *)label, (float)D_L11_001B1634, D_L11_001B3E04, 0.5f, one);
            func_00300A00((char *)label, c, x, fy, D_L11_001B161C, 1.0f, 0.0f);
            break;
        }
    }
    func_002FC560(0x47, 0x5360b);
}
