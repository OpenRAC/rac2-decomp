/* 7 November 2026: released from the medium-tier reservation (#152) as a documented near miss after its final round. Final state: 644/644, 8 rows (count in v1 vs retail a1; li.s 0.5 before the first mul.s). */
/* 7 November 2026, FINAL state: best C below unchanged at 644/644 bytes, 0/28 USA, 8 real rows. A fresh C written from the retail assembly alone (natural if-block, spacing = (int)(5F0 * 23A4 + 0.5f), top = (int)((float)(D_001A7344 >> 1) - (float)spacing * ((float)count * 0.5f)), separate vtable address, colour local) gives 35 rows: cc1 interleaves the height load into the centring and hoists i = 0 into the first call delay slot; the operand-order, count/height/half local and -fno-sched-interblock forms compile identically, and -fno-schedule-insns gives 120. Exact remaining blocker: retail allocates count to a1 (cc1 gives v1, 3 rows) and schedules li.s 0.5 after the first mul.s (cc1 puts it before, 5 rows); retail needs v0 and v1 both busy across the count lifetime and a scheduling barrier no rule-compliant source form found in 12 rounds (about 1000 checks plus a 34k-variant sweep and decomp-permuter). No RAC1/RAC4 donor. Closed unless a donor or a new compiler-rule witness appears. */
/* 6 November 2026, Codex round-11 follow-up: 117 check.py runs including
 * baseline/final confirmation; retained C unchanged, 644/644 bytes, 0/28 USA,
 * eight real instruction rows (relocation immediates excluded, register bits checked).
 * New controls against round 11: screen width/height record with the reused spacing
 * lifetime ties at eight; refreshed count gives 11 rows; reusing count as the indirect
 * call target puts the initial count in a1 but moves spacing to v1 and changes the
 * indirect-call registers (11 rows total). Slot/row-offset lifetimes do not improve it.
 * Eighteen third-group placements and 50 dependency-checked, four-group FP layouts
 * (explicit scale, bias and half-count operations) give no gain. Scheduler dumps show
 * the first multiply and bias load co-issued, emitted bias first; the retained group
 * also orders half-count multiplication before rounding addition. No donor found in
 * current local RAC1/RAC4 by the distinctive colour constants. Keep the marker; need
 * an independently grounded lifetime/scheduling hypothesis for count and FP setup.
 */
/* 7 November 2026, decomp-permuter: best score 110 (base 135) moved the rounding into the previous group and left an empty do/while (8 -> 15 rows); no rule-compliant gain. Setup: /tmp/claude-1000/-home-lynder063-rac2-decomp/lead/work/perm. */
/* 6 November 2026 (round 11c, prototype audit): func_00335E10/func_00335E20 given their established pointer returns (float *, int *) without casts: same 14 rows. Other callees agree with src. */
/* 6 November 2026, round 11b: no gain. Product forms `half = 0.5f; half *= (float)n;`, `half = (float)n; half *= 0.5f;`, `0.5f * n`, `t *= 23A4`, `t += 0.5f`, separate 0.5f variables with up to two groups: li.s 0.5 never moves after the first mul.s. Inline (count, spacing) helpers put count in a0 or v1 (19-22 rows); count stays block-local and lands in v1 because the height holds v0. */
/* 6 November 2026, round 11: new best C below (644/644, 0/28 USA, 8 real rows, was 14), 22 check.py runs.
 * Changes: D_001A7344 MACRO_ADDR; sp reused for the vtable offset in the loop (sp = v->offset),
 * which makes it global, so the loop's v0/v1 conflicts give it retail's a0 and height gets v0;
 * a float t = 5F0 * 23A4 split, one group {t, n = count, half} and one group {sp = (int)(t + 0.5f)}
 * give retail's FPRs (23A4 f2, 0.5 f1, half f3) and load order. Left: count v1 (retail a1, 3 rows)
 * and li.s scheduled before the first mul.s (5 rows). Model: count is a block-local qty, and
 * fake lifetimes (local-alloc INSN_SCHEDULING) only block v0 (height) for it; retail needs v1
 * busy too. Making count global (enabled/flag reuse) still picks v1. A 34k-variant cc1 sweep of
 * statement order, t/cf splits and up to two groups gave nothing better.
 */
/* 6 November 2026, Codex follow-up: retained best C unchanged after 79 check.py
 * runs, including baseline/final confirmations: 644/644 bytes, 0/28 USA,
 * 14 real instruction rows (relocation fields excluded, register/opcode bits checked).
 * New controls: widened signed coordinate/index locals add instructions (652/680);
 * the existing width/height screen-record view gives 19-22 rows; reusing the enabled
 * value as count/spacing/start/index shrinks to 636 bytes; reusing count/spacing/height
 * as the later selection, special-row flag or vtable offset gives 16-22 rows.
 * A count-guarded do loop ties at 14; early count returns and one-pass groups spanning
 * centring plus drawing, or the enclosing enabled branch, do not improve it. Tested
 * those controls with plain/MACRO_ADDR height and the retained/half-first/ungrouped
 * centring forms. All candidate uses were checked for initialization; no forbidden
 * steering constructs used. Still need a source witness explaining height=v0 and
 * both v0/v1 unavailable when spacing is allocated, plus the FP setup scheduling.
 */
/* 6 November 2026, round 10: best C below unchanged (14 real rows), about 105 check.py runs.
 * MACRO_ADDR on D_001A7344 gives retail's height v0 (lw v0 macro, no %hi pseudo), but then
 * sp takes v1 and count a0 (16-26 over 54 group/order variants, h and spf locals included).
 * Half first with spf in the group gives retail's FPRs and spf order, GPRs still off (14+).
 * No change from: static inline round/centring helpers (11-25), sda array D_001AE5F0 (27),
 * scalar/plain D_001B23A4, operand order swaps, x / 2.0f, -fno-sched-interblock (same),
 * -fno-schedule-insns (81), -fno-schedule-insns2 (40). Retail needs v0 and v1 busy across sp.
 */
/* 6 November 2026, Codex worker: best C below retained unchanged after 137 check.py
 * runs (including baseline and final confirmation): 644/644 bytes, 0/28 USA,
 * 14 real instruction rows. No improvement from new lifetime pipelines: reusing a
 * scale/product/bias float as half-count or converted spacing, with one-pass groups
 * around their real operations (88 candidates); reusing the loop index/count for
 * spacing or height (24); scalar declarations for the height/tuning globals and
 * explicit conversion/height groups (16); explicit refreshed loop bounds (2);
 * five initial integer/float lifetime variants. No donor found by distinctive
 * colour constants in current local RAC1/RAC4 sources. Allocator dumps confirm
 * count=a1 and spacing=a0 already; split height address=v0, load/shift=v1.
 * Still needed: retail's tuning=f2, bias=f1, height=v0, and spacing conversion
 * before the height load. Keep the marker; reopen on a source/control-flow
 * witness for these lifetimes rather than further equivalent reorderings.
 */
/* 6 November 2026, round 9: new best C below (644/644, 0/28 USA, 14 real rows, was 19).
 * The 18-row source of the next note read n before setting it (the hill-climb moved n = menu->count
 * below its use); that order is not valid C and is dropped. Changes: a for loop on
 * menu->count (no n), the group holds only sp and half, and D_001A7344 is a plain extern
 * (split %hi). Count a1, sp a0 and (float)count f3 now match retail. Left: 23A4 f1 / 0.5 f2
 * (retail f2/f1), height v1 (retail v0, same as %hi), and the (float)sp convert scheduled
 * after the height load. Half first in the group gives retail's FPRs but loads the count
 * first (19). No change from: declaration order (30-run hill-climb), early h = D_001A7344 >> 1
 * (14-28), MACRO_ADDR with this shape (19), group start before any of the five calls (16),
 * nested groups (19-25), float temp reuse (14-19), single flags incl. -frac2-* (14+).
 */
/* 6 November 2026, lead: 24-run hill-climb over the four group statements gives 18 real rows (from 19); source below is that order. Reusing sp or n for start (19, 118), the loop bound as n (68) and a block-local h = D_001A7344 >> 1 (18) do not help. */
/* 6 November 2026, round 2: new best C below (644/644, 0/28 USA, 19 words, was 25).
 * One group holding sp, n, half = (float)n * 0.5f and spf = (float)sp puts its loop-end
 * note between the (float)sp conversion and the D_001A7344 load: the whole centring block
 * now has retail's instruction order. Only registers differ: count a0/v0/v1 for retail's
 * a1/a0/v0 (count/sp/height), and 23A4 f1, 0.5 f2, half f1 for retail's f2/f1/f3.
 * Swapping the group to n, half, sp, spf gives retail's FPRs but loads the count first.
 * A plain `extern int D_001A7344[];` (split %hi pseudo) gives 18 words: height v0 but %hi
 * in v1 and sp still v0. -dg dump: sp is a local-alloc quantity, and v0/v1 are free during
 * its life, so retail needs a GPR quantity live across the fix that this form lacks.
 * No change from: n before sp, half = 0.5f * n, 0.5f + product, h = D_001A7344 >> 1 in or
 * before the group (22-25 words).
 */
/* 6 November 2026: retained source below unchanged (644/644, 0/28 USA, 25 words).
 * Retail loads D_001AE5F0 ($gp), D_001B23A4 and the count, then D_001A7344 last; this
 * source loads D_001B23A4 first and D_001A7344 before the count. No change from: count
 * read before sp, a `half` or `scale` local, menu->count in place of n, swapped product
 * operands; a one-pass group around sp or start gives 23-26 words.
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 644/644 bytes, 0/28 placements; first difference 0x98.
 * Profile: -O2 -G8 -ffunction-sections.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* 3 November 2026: retained near miss, not linked.
 * Profile: -O2 -G8 -ffunction-sections.
 * Current size: 644/644 bytes; US 0/28, US2 absent, PAL absent.
 * Complete 72-byte text typing preserves the true 64-bit style. Reusing the descriptor address
 * shortened the body to 628 bytes; preserving its separately formed address retains the 27-word
 * centering/setup residual.
 * Reopen on a real additional lifetime or source/control-flow witness for the centering block;
 * owner typing and widget-address capture did not resolve it.
 * Earlier measurements below are historical where this note supersedes them.
 */
/* opus-1 (v1334): -O2 -G8 -ffunction-sections (a *-g8.c unit); 644/644 bytes, 0/28 places.
 * The whole loop body, the prologue/epilogue and the frame match retail. Two source facts
 * recovered that: the coordinate stores go through a struct view of the rectangle returned
 * by func_00335E10 (MEM_IN_STRUCT stores do not conflict with the scalar sda tuning loads, so
 * those loads schedule above the first store as retail does), and the highlight colour is
 * computed into a local before the func_00335E20 call.
 * Still different: the 28 instructions of the centring computation between the fifth
 * func_00336320 call and the count test (+0x8C..+0xF8). Retail allocates count=a1,
 * spacing=a0, height=v0, 5F0=f0, 23A4=f2, 0.5=f1, (float)count=f3; cc1 gives count=v1,
 * spacing=v0 (and f0/f3/f4 for the floats), so sched2 orders the block differently.
 * A local-alloc model of this block shows retail's GPR assignment needs one more GPR
 * quantity live across the spacing conversion than this dataflow has. Tried without
 * success: statement order/separate variables, float variable reuse, 0.5 hoisted to a
 * variable (takes f20), split-address D_001A7344 (count moves to a0), -g,
 * -fno-sched-interblock, -fno-sched-spec, -ffast-math, -fno-schedule-insns (breaks the
 * loop), a for loop nested in the count test (count becomes global, spacing v1, but a
 * second blez stays). Next: find what natural source adds a GPR value in that block.
 * Declarations below are standalone; the D_ addresses are the boot's (gp 0x001AEFF0).
 */
#include "common.h"

extern int func_002A9588(int, int, int, int, int);
extern void func_00336320(char *);
extern int func_00335E10(char *);
extern int func_00335E20(char *);
extern float D_001AE5F0 __attribute__((sda));
extern float D_001B23A4[] MACRO_ADDR;
extern int D_001A7344[] MACRO_ADDR;
extern float D_001AE5D0 __attribute__((sda));
extern float D_001AE5D4[] MACRO_ADDR;
extern float D_001AE5D8 __attribute__((sda));
extern float D_001AE5E0 __attribute__((sda));
extern float D_001AE5E4[] MACRO_ADDR;
extern float D_001AE5E8 __attribute__((sda));

typedef struct { float x, y, w, h; } ListRect;
typedef struct {
    char pad[0x434];
    ListRect *origin;
    int unknown438;
    int selected;
    int enabled;
    int count;
    int showSpecial;
} ListMenu;
typedef struct { short pad[4]; short offset; short pad2; void (*call)(char *); } ListVtable;
typedef struct {
    ListRect *position;
    ListRect *scale;
    void *parameter08;
    unsigned int *colors;
    float *visibility;
    char lifetime[0x1C];
    ListVtable *table;
    void *metrics;
    unsigned long style;
    char *text;
    int alignment;
} ListSlot;

void func_00348EC0(char *o)
{
    int color = func_002A9588(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int start, i, sp, h, n;
    float half, spf, t;
    ListMenu *menu = (ListMenu *)o;

    if (menu->enabled) {
        func_00336320(o);
        func_00336320(o + 0x130);
        func_00336320(o + 0x4C);
        func_00336320(o + 0x98);
        func_00336320(o + 0xE4);
        do {
            t = D_001AE5F0 * D_001B23A4[0];
            n = menu->count;
            half = (float)n * 0.5f;
        } while (0);
        do {
            sp = (int)(t + 0.5f);
        } while (0);
        spf = (float)sp;
        h = D_001A7344[0] >> 1;
        start = (int)((float)h - spf * half);
        for (i = 0; i < menu->count; i++) {
            ListRect *p;
            char *slot;
            ListVtable *v;
            int c;

            if (i == 7 && !menu->showSpecial)
                continue;
            p = (ListRect *)((float *)func_00335E10(o + 0x17C));
            p->x = D_001AE5D0 + menu->origin->x;
            p->y = (D_001AE5D4[0] + (float)i * D_001AE5D8) + (float)start;
            c = i == menu->selected ? color : 0x55F0C070;
            *((int *)func_00335E20(o + 0x1C8)) = c;
            func_00336320(o + 0x17C);
            p = (ListRect *)((float *)func_00335E10(o + 0x1C8));
            p->x = D_001AE5D0 + menu->origin->x;
            p->y = (D_001AE5D4[0] + (float)i * D_001AE5D8) + (float)start;
            func_00336320(o + 0x1C8);
            slot = (char *)&((ListSlot *)(o + 0x218))[i];
            p = (ListRect *)((float *)func_00335E10(slot));
            p->x = D_001AE5E0 + menu->origin->x;
            p->y = (D_001AE5E4[0] + (float)i * D_001AE5E8) + (float)start;
            v = *(ListVtable **)(o + i * 72 + 0x248);
            sp = v->offset;
            v->call(slot + sp);
        }
    }
}

