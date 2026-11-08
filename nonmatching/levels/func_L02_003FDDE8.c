/* 8 November 2026 (Sonnet round, s28): lesson 49 pass (c, x, fy, label, one, entry, half, sc, z each written as expressions): none beats 964/964, 8 aligned diff words (draw 3 only); C unchanged. */
/* 8 November 2026 (Sonnet round, s19, lesson 48 sweep): no gain, 964/964, 9 words, C below unchanged. Scripted every single-statement move within its basic-block run (26 compiling moves, all stay at 9) plus block moves of pulse/sc,z/c,x across draws (34-229 words); none changes draw 3. Not ported to L11 (nothing to port). */
/* 8 November 2026 (Sonnet round, s14): no gain, 964/964, 9 differing words (draw 3 only), C below unchanged. New: buttons through a separate local, if-then colour form, ternary colour in draw 3: no change. Permuter 1500 s -j2 seeded from this C: stuck at base 355, no candidate below it. */
/* 8 November 2026 (Sonnet round): best C below 964/964 bytes, draw 4 (0x4a) now fully matches (was 18 differing words, now draw 3 only, 8 words at 003FDFD0-003FDFEC): the loop draw's x goes in its own local `nv` (a second variable for a different value, no copy), which keeps x out of the draw-1/2 pseudo and issues the x conversion before the label copy. The same split for draw 3 loses draw 1's copy (944), as does any x/c/fy rename (partition of x over the four draws: best is this one), draw 3 statement order (6 orders), c3/f3 locals. Permuter 1500 s -j2: no gain (best 355 = this C). Same change ported to func_L11_00443940 with the same result. */
/* 8 November 2026 (compiler matrix, scratch only): retained C compiled with 10 EE cc1 builds at the same flags (-frac2-* dropped for non-local builds), our as: local 991111; decomp.me 2.9-ee-991111a, 991111-01, 991111b (= SN SDK 2.4's 991111); Sony 2.96-ee-001003-1; SN 2.95.2 v2.73a/v2.74, 2.95.3 v1.07/v1.14/v1.36 (no 990721 build available). No build gives retail's draws 3/4 order (+0x1E4, +0x318): every other build is longer (1028-1124 bytes) and neither ours nor retail in both clusters. Not a compiler-build difference. */
/* 8 November 2026 (round 14, USA v1.01, check.py only, ~55 runs): no gain; C below unchanged (964/964, 17 differing words by an opcode-level count). sched1 trace (-fsched-verbose-3): in draws 3/4 the copy `label = $v0` ties `one = 1` on priority and wins on register weight (copy kills $v0, so weight 0 vs +1), then on luid; x (floatsisf from memory, fmac unit) ranks lowest and waits behind the y chain on fmac. So the copy issues beside or before the buttons load, $v0 is free, and buttons/hi get $a0/$v1 (draw 3) or $v0 (draw 4). No gain: lesson 43 (plain y rounding plus one-pass `do { c = ...; } while (0);`) in draw 3 (956 bytes, copy folded into $a0) or draw 4 (34 words), also with gcse on (159); gcse on with the C below (60); do-while around c or x in draw 3 (952, draw-1 copy lost) or c in draw 4 (25/26); a separate x local for draw 3 at function or block scope (944, draw-1 copy lost); x through `pulse` (no change); late `label = text` copy with a new text local (no change: cse substitutes text); `one = 1` before the label call (19); a label_y variant with handle tests first (944) or rounding after the tests (956/944; would need an owner ruling anyway); four local declaration orders (no change). */
/* 8 November 2026 (round 13, USA v1.01, check.py only): best C below 964/964 bytes, 0/1 places, 18 differing words (was 20). label_y now in all four draws; in draws 3/4 `active` is a local `one` set to 1 right after each label call (per the owner ruling on a local holding 1, func_L01_002F1588). That removes the ghost $s6 of the literal 1 in the loop. Setting `one` once for the whole function, or once before `if (enabled)`, puts it in a saved register (928 bytes, 150+ words). Draw 3's rounded int is now right. Left: the label copy in draws 3/4 still issues before the x conversion. No gain (~12 runs): every order of one/c/x in draws 3 and 4 (18); x and label_y written as call arguments (904 bytes, 181 words; or 18). */
/* 8 November 2026 (round 12, USA v1.01, check.py only): best C below 964/964 bytes, 0/1 places, 20 differing words (was 28 with the round-14 C, same count). Pair check: L02_003FDDE8 and L11_00443940 are the same routine (opcode diff: L02 has one extra saved register and the i == 8 entry test). label_y (master L15_00431590-g8.c form, label as handle, literal 1) in draws 1/2 fixes them fully: the label copy now lands in $a2 as in retail. label_y inside the loop (0x4a draw) hoists its constant 1 into a ghost $s6 (928 bytes, loop.c movable), so draws 3/4 use hud_coord (L05_0037A5F8-g8.c form); scaled_coord there gives the same rows. Left: draws 3/4 only. sched1 order here is y, scale, half, hi, field, COPY, mul, alt, andi, mode, movz, x; retail's registers need x issued before the copy (copy after andi), so $v0 stays busy and field/int take $v1, hi $a0. No gain (~45 runs): c/x/y orders with both helpers (19-27), handle = c, label_y with handle tests first (parked form, 19), if/else and split colour forms (19-40), separate late label variable (916 bytes), `label = text` copy before the helper (19), c reused for the field (int right, field in $a1, 21 words). Flags: -O2 -G8 -ffunction-sections -fno-rerun-loop-opt -fno-gcse. */
/* 8 November 2026 (round 9, rank_for_schedule): base 964/964, 25 differing words (retained C, recorded flags). rank_for_schedule is identical in GCC 2.95/2.95.2/2.95.3 and EE 991111/991111b; SN 2.95.2 v2.73a makes the same tie choice where its output is comparable. Env probes (sched1/sched2/both): reg weight swapped/clamped/dropped/after class/positive-or-negative only, class dropped/reversed, dependent count reversed/dropped/data-only/clamped, LUID reversed, INSN_UID ties, no birthing boost: none improves any of the nine cluster targets; forced on, every variant changes 6-7124 of 8761 matched units. Hypothesis falsified. */
/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 964/964, 26 rows with the owner-allowed helper (label copy from v0 scheduled early in draws 3/4). */
/* 7 November 2026, round 14: the dead-test helper is allowed by owner ruling (master
 * precedent: src/game/002D2188-g8.c); it already loads the mode first, as
 * L02_003FF6E8-g8.c:43 does. The `#define TABLE` alias is gone (D_L02_001B1190 used by its
 * own name). Best C below: 964/964 bytes, 0/1 places, 26 real rows (four draws).
 * Draw 3/4 cause (sched1 dump, -dS): the label copy `r87 = $v0` is ready right after the
 * call and takes the first free ALU slot (t=8, beside the buttons load), so local-alloc
 * finds $v0 free and puts the rounded int in $v0, the high address in $v1, buttons in $a0.
 * Retail ($v1 for both, high in $a0) needs the copy to stay after the fix insn, which list
 * scheduling only does if the copy depends on it. No source with that dependency found.
 * Measured, no gain (~55 compiles): int-returning helper (L02_003FF6E8 form) for all draws
 * (70 rows) or draws 3/4 (28/72); draw 3/4 through an inline draw helper or the label call
 * as an argument (944 bytes, 190+); `half, one` variables in draws 3/4 (952-960); draw 3
 * statement permutations (28 best); sc/z order and placement (32-51); a late `label = t`
 * copy (944, test folds away); 18 flags incl. -fno-sched-interblock, -fno-sched-spec,
 * -frac2-* switches, -g (no change), -fno-regmove (968), -fno-rerun-cse-after-loop (37).
 */
/* 6 November 2026, USA v1.01, check.py only: 964/964 compiled bytes (exact size),
 * 0/1 places match. 20 non-reloc instruction differences remain across 4 draws
 * under `-O2 -G8 -ffunction-sections -fno-rerun-loop-opt -fno-gcse`.
 * 6 November 2026 (round 10): the retained C below is NOT admissible: scaled_coord's
 * `if (result != 0 && mode == active) scaled = 1.0f;` is a dead test (blocker 26), and
 * `#define TABLE` is a second name for D_L02_001B1190 (new AGENTS.md rule). Compliant form
 * (no dead test, no TABLE alias, no field copy; draw 3 body in a one-pass do/while(0) group)
 * measures 952/964 bytes, 68 real rows. Cause: combine folds `label = v0; a0 = label` into
 * `a0 = v0` within one block, so label never lives in $a2 (retail `daddu $a2,$v0` ... `daddu
 * $a0,$a2` in all four draws). Tried without effect: call written as the draw argument,
 * inline draw_text helper taking label, do/while(0) groups around the label call, if/else vs
 * ternary colour, 110-step statement-order hill-climb. Only a block split between the label
 * call and the draw call keeps the copy; no real source construct for it is known.
 *
 * 6 November 2026 (round 11, 9 runs): no admissible block-boundary shape found. Lesson-35 and
 * UYA (func_003DBEC8/func_003A5DF0/func_003AE8A8) forms in scaled_coord, all dead tests and so
 * NOT admissible (COMPILER-NOTES "false tests", blocker 26): `scaled = mode == active ? z0 : z1`
 * with local zeros 976 bytes; identical arms `if (result) coord = (float)result; else ...` 980,
 * same on the mode global 1016; identical zero-variable arms on result merge early (952);
 * `if (result != 0) scaled = 1.0f;` without the mode load 964/964 but more rows than the mode
 * form. `goto` to the next statement (with or without a test) 952: the jump goes before combine.
 * Retail has no extra load or branch here, so the boundary needs a test that survives combine
 * and vanishes later; with gcc 2.95 that happens only when both outcomes compute the same value,
 * i.e. a test dead under C semantics. Next: evidence of the original helper, not more spellings.
 *
 * Prologue and epilogue are byte-for-byte identical to retail (frame 0x60, saving
 * $s0..$s6 and $f20..$f22). All callee-saved registers match retail assignments:
 * $s0 (object), $s1 (0x8710 / 0xE0), $s2 (state / &D_L02_00264A70), $s3 (enabled / &D_00139568),
 * $s4 (color), $s5 (&D_001395B8), $s6 (&D_00138180), $f20 (1.0f), $f21 (0.0f), $f22 (0.5f).
 *
 * Progress from previous 944-byte draft:
 * 1. The inline helper `scaled_coord` with the dead display-mode test
 *    (`if (result != 0 && mode == active) scaled = 1.0f;` with `int mode = D_L02_001B3E00;`
 *    and `int one = 1;`) splits basic blocks after the y conversion without surviving to
 *    assembly (flow2 deletes the dead test), preventing CSE from hoisting 0.5f, 1.0f, 0.0f
 *    and 0x8710 into callee-saved registers across draws 3 and 4. This brought the compiled
 *    size from 944 to exactly 964 bytes.
 * 2. In retail, `label` is allocated in `global-alloc` across all four draws to $a2, and
 *    moved to $a0 before each draw call (`daddu $a0, $a2, $zero`). In naive C, `label`
 *    takes $v1. Writing the draw 4 field through c (`field = D_00138180.buttons; c = field;
 *    c = (c & 0x2000) ? D_L02_001B128C : color;`) keeps $v1 busy across the label definition,
 *    forcing `global-alloc` to assign $a2 to `label` in all four draws.
 *
 * Tried (~340 runs + 300 hill-climb iterations):
 * - Permutations of independent statements in calls 1, 2, 3, 4.
 * - Alternative expression and condition forms for buttons and color (if/else, ternary,
 *   two-step assignment, direct pointer casts `*(int *)(D_00138180 + 0x1A0)`).
 * - Separate global declaration `extern int D_00138320 __attribute__((nosda));`.
 * - Local-alloc dump analysis: in draw 3, `local-alloc` creates qty 146 for the high address
 *   and qty 148 for the loaded buttons value. QTY_CMP_PRI gives qty 146 higher priority
 *   because its live range is only 1 insn (`qty_death - qty_birth = 1` in the denominator),
 *   allocating it first to $v1, leaving $a0 for buttons. In retail, high address is $a0
 *   and buttons is $v1 (`lui $a0, 0x14; lw $v1, -0x7CE0($a0)`).
 * - Compiler flags tested: -fno-schedule-insns (944), -fno-schedule-insns2 (940),
 *   -fno-inline (924), -fno-expensive-optimizations (27 diffs), -fforce-mem (20 diffs),
 *   -fforce-addr (972), -fno-delayed-branch (1060), -fcaller-saves (20 diffs).
 *
 * Residual (20 non-reloc diffs):
 * - Draw 1 (003FDE94/003FDE98): 1-instruction swap of `daddu $a0, $a2, $zero` and `mtc1 $zero, $f21`.
 * - Draw 2 (003FDF00): 1-instruction swap of `daddu $a0, $a2, $zero` and `lwc1 $f14, 0x2270($gp)`.
 * - Draw 3 (003FDFD4-003FDFFC): address high in $v1 and buttons in $a0 (retail: address in $a0,
 *   buttons in $v1), and `scaled_coord` int conversion uses $v0 instead of $v1.
 * - Draw 4 (003FE0F8-003FE12C): buttons loaded into $a1 due to `c = field`, whereas retail
 *   loads into $v1 (`lw $v1, 0x1A0($s6)`).
 *
 * What would unblock it:
 * A source construct for draw 3 and draw 4 that loads buttons into $v1 while keeping $v0 live
 * (delaying `daddu $a2, $v0, $zero` past the button load as in retail lines 129 and 202) and
 * maintaining the $a2 assignment for `label`.
 */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int buttons;
} HelpInput;
typedef struct {
    u8 pad[4];
    u8 available;
    u8 rest[0xdb];
} HelpEntry;

extern u8 *D_L02_001A904C;
extern float D_L02_001B3E04;
extern int D_L02_001B30C8;
extern HelpInput D_00138180;
extern u8 D_00139568[], D_001395B8[];
extern HelpEntry D_L02_00264A70[];
extern u8 *D_L02_001B1190[] SDATA(D_L02_001B1190);

extern void func_L00_0037B7B0(void);
extern int func_00336D50(u8 *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern int func_L02_003F9B70(int);
extern int func_00288D58(void);
extern void func_002FC560(unsigned int, unsigned long long);

extern float D_L02_001B1260 __attribute__((sda));
extern int D_L02_001B1264 __attribute__((sda));
extern int D_L02_001B1268 __attribute__((sda));
extern int D_L02_001B126C __attribute__((sda));
extern int D_L02_001B1270 __attribute__((sda));
extern int D_L02_001B1274 __attribute__((sda));
extern int D_L02_001B1278 __attribute__((sda));
extern unsigned int D_L02_001B127C __attribute__((sda));
extern unsigned int D_L02_001B1280 __attribute__((sda));
extern unsigned int D_L02_001B1288 __attribute__((sda));
extern unsigned int D_L02_001B128C __attribute__((sda));

extern int D_L02_001B3E00;

/* label_y: dead-test HUD helper allowed by owner ruling (7 November 2026; precedent
   src/levels/15_gorn/L15_00431590-g8.c); `one` as active per the func_L01_002F1588 ruling. */
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

void func_L02_003FDDE8(u8 *object, int enabled)
{
    u8 *state;
    char *label;
    int phase, i, one, entry;
    unsigned int color, c;
    float nv, x, fy, pulse, half, sc, z;
    HelpEntry *r;

    if (D_L02_001A904C == 0) return;
    func_L00_0037B7B0();
    entry = 0x8710;
    state = *(u8 **)(object + 0x68);
    half = 0.5f;
    label = (char *)func_00336D50(D_L02_001A904C + entry, 0x49);
    x = (float)D_L02_001B1264;
    fy = (float)label_y(label, (float)D_L02_001B1268, D_L02_001B3E04, half, 1);
    sc = 1.0f;
    z = 0.0f;
    func_00300A00(label, D_L02_001B1280, x, fy, D_L02_001B1260, sc, z);
    label = (char *)func_00336D50(D_L02_001A904C + entry, 0x48);
    x = (float)D_L02_001B1264;
    fy = (float)label_y(label, (float)D_L02_001B1268, D_L02_001B3E04, half, 1);
    func_00300A00(label, D_L02_001B127C, x, fy, D_L02_001B1260, sc, z);
    phase = D_L02_001B30C8 % 50;
    if (phase >= 25) pulse = sc - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = func_00283D38(D_L02_001B127C, D_L02_001B1280, pulse);
    if (enabled) {
        if (*(short *)(state + 0x118) != 0) {
            label = (char *)func_00336D50(D_L02_001A904C + 0x8710, 0x4b);
            one = 1;
            x = (float)D_L02_001B126C;
            if (D_00138180.buttons & 0x8000) c = D_L02_001B1288; else c = color;
            fy = (float)label_y(label, (float)D_L02_001B1270, D_L02_001B3E04, 0.5f, one);
            func_00300A00(label, c, x, fy, D_L02_001B1260, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x118) + 1; i < 14; i++) {
            if (D_001395B8[func_L02_003F9B70(*(int *)(D_L02_001B1190[i] + 8))] == 0) continue;
            if (i >= 12 && !func_00288D58()) continue;
            if (i == 7) {
                r = &D_L02_00264A70[D_00139568[0x1e]];
                if (r->available == 0) continue;
            }
            if (i == 8) {
                r = &D_L02_00264A70[D_00139568[0x2a]];
                if (r->available == 0) continue;
            }
            label = (char *)func_00336D50(D_L02_001A904C + 0x8710, 0x4a);
            one = 1;
            c = (D_00138180.buttons & 0x2000) ? D_L02_001B128C : color;
            nv = (float)D_L02_001B1274;
            fy = (float)label_y(label, (float)D_L02_001B1278, D_L02_001B3E04, 0.5f, one);
            func_00300A00(label, c, nv, fy, D_L02_001B1260, 1.0f, 0.0f);
            break;
        }
    }
    func_002FC560(0x47, 0x5360b);
}
