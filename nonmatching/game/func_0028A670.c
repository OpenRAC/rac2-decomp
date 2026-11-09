/* 9 November 2026 (o132, HUD-panel recipe of L02_003FDDE8/L11_00443940): func_00300A00 declared (char *, float x, int colour, float y, ...) (bank-preserving): object byte-identical (2 words). With it, the active grid (draws 1/2/3 each one/active/act2(set before draw 1 or 2)/1, ~70 local cc1 scores) and `active = one` at every position from the switch to draw 3: best stays 2. Dump: draw-2 fix_truncsfsi2 scratch follows reload round robin from the draw-2 0x8710 reload (a2 -> f1 -> v0); retail needs a v0 reload between them (draw 1 gets one from the $LC0 address of `active = one`), and no placement gives both draws theirs. Body unchanged. */
/* 9 November 2026 (Codex): 147 new C variants under -O2 -G0 -ffunction-sections;
 * 64 helper active-type/predicate-promotion combinations and 83 bank-preserving call
 * interleavings beyond the baseline. All 84 interleaving layouts emit the same target
 * body; promotion variants tie or worsen it. Retained C unchanged: 1192/1192 bytes,
 * 2 words off (+0x3A8/+0x3B4, second 0x8710 reload v0 instead of a2).
 * check.py --diff and --version us2 --diff each report 0/28 places; PAL has no
 * catalogue identity. No linked build run or match claimed. See blocker 45. */
/* 9 November 2026 (o113, func_L06_00382608 lever, ~960 local cc1 scores): one = 1 as first loop statement, active/firstX moves, and 0x8710, 178/179, the three 0.5f, len > 0 / len - 1, case floats (0.0714285746f, 0.142857149f, 7.0f, 1.0f), 14/7 and 0x55F0C070 as set-once locals at every legal position: best stays 2 words. */
/* 9 November 2026 (o101): body below unchanged (1192/1192, 2 words: draw-2 0x8710 reload $v0, retail $a2). Idiom sweep, local cc1 scorer: label_y/label_y3/label_y4 (handle id or x) x active (active/one/1) on each draw: 1196-1204 bytes for draws 1/2, 14-23 for draw 3; hud_coord with the mode test first, before the rounding, the mode load hoisted, or the L02 three-test form, x active, singles (42) and draw 1 x draw 2 pairs (300, incl. `one != 0`): best 2 (the base), next 4. The sprintf format takes exactly the one %d argument it gets. */
/* 9 November 2026 (Sonnet round o73, dumps): 2 rows remain. Deciding rule: reload1 round robin. fix_truncsfsi2 insn 455 clobbers a1 then $f1, so last_spill_reg=$f1 and the draw-2 0x8710 reload (insn 760) wraps to v0. Retail a2 needs one more GPR reload after 455 ending on a1; a reload of `active` in the dead D_001B23A0 test (insn 458: v0 busy, v1 result, a0 id live -> a1) fits, but here `active` gets s1. Tried: active set before sprintf (9), at loop top (11), before the firstX test (11), u16 (2). */
/* 9 November 2026 (label_y2 sweep (owner ruling 2026-11-09, Sonnet s46): each of the 3 hud_coord calls as label_y2 (one handle test, half or scale form, handles id/text/first/second/color/x), singles, pairs and all three: base 2 words stays best, every variant 9-80 rows worse; no gain. */
/* 9 November 2026 (Sonnet round s42, lesson 52): scripted `do { real_op; } while (0)` groups around 1-3 consecutive statements at every position (120 singles + 86 pairs, pairs of the near-base ones) and every -frac2-* switch / -freduce-all-givs on the unit: nothing below the base 2 words (best only ties, most groups far worse); no switch changes it. */
/* 8 November 2026 (Sonnet round s17, lesson 48 sweep): scripted statement/declaration moves (1..4 positions per block, 312 singles + 2225 pairs of the near-base ones): nothing below the base 2 words (ties and 4+ only). */
/* 8 November 2026 (Sonnet round s15): re-measured 2 words. New: per-draw pointer local (`b2 = D_001A8CFC; f(b2 + 0x8710, ..)`, in one or both draws, declared at top or in a block), `off = 0x8710` local, `half = 0.5f` local (4 words, fp consts move): no change / worse. 1500 s permuter run (-j2, seeded from the 2-word C): no improvement. */
/* 8 November 2026 (Sonnet round): re-measured 2 words (draw 2 0x8710 reload v0, retail a2); a separate `unsigned char active2 = one` for draw 2 gives 3 more words (s0/s1 swap), a separate `id2` for draw 2 gives 8 more. Not rerun in the permuter (round 4 covered it). */
/* 8 November 2026 (0x8710 push): the v0/a2 choice is reload1's round robin (last_spill_reg). In the C below no GR reload
 * follows draw 1's fix (whose last reload is f1), so draw 2's 0x8710 reload wraps to v0. Passing `one` in draw 1 (spilled, so
 * the dead branch gets an a1 reload) gives a2 but then draw 2's fix scratch wraps to v0 (4 words); `one != 0` in draw 2 fixes
 * that but leaves `active` dead (B2 order lost, 7). Per-draw locals, literal or pointer forms of 0x8710: no change (2). */
/* 8 November 2026 (round twelve, m8i): 10 -> 2 words, same 1192 bytes. Draw 2 `one != 0` (4 positions) confirmed;
 * then a permuter-found `unsigned char active = one;` set just before the draw-1 id call and passed as
 * `active` to hud_coord (float value) in draws 1 and 2 fixes draw 1 (addiu a1,0xB2 order, early daddu a0,v0,
 * mfc1 v1; fix scratch now a1 as retail). Left: draw 2 0x8710 reload in v0 (retail a2): reload round robin;
 * `active` is spilled and its reload (v0) sits between. Tried without gain: active placement (before width,
 * after the id call), int/u16 type, `one != 0` assignment, active in draw 3 (11), hud_coord2 in draw 1 (8),
 * draw-2 `(unsigned char)one`/`active != 0` (7), draw-3 `one != 0` (6). C below is the 2-word version. */
/* 8 November 2026, permuter round 4 (35 min -j3, base 130): draw 2 fixed (10 -> 4 positions: draw-1 `daddu a0,v0` early and fix scratch v0, retail v1) by `(unsigned char)one` as draw 2's active, or plainly by a second hud_coord with an `unsigned char` (or unsigned short) active used for draw 2 only (`one != 0` also works). Not landed: a param-type-only helper variant needs an owner ruling, and draw 1 stays (u8/u16 active in hud_coord2, casts, literal 1, `one = 1` per draw: 5-6 words; 12 more permuter minutes from that base found nothing). C below unchanged. */
/* 8 November 2026 (source round, v101 wasJ): 11 -> 10 words, same 1192 bytes. Draw 1 now uses
 * hud_coord2 (int value, mode read first: L08_0041D808-g8.c scaled_coord precedent); this fixes
 * draw 1's `addiu a1,0xB2` order. Left: draw 1 fix output is v0 (mfc1 v0) and `daddu a0,v0` early;
 * draw 2 `daddu a0,v0` early. Mechanism (greg dump): mode is now a global pseudo and its load is
 * hoisted by sched1 above the id copy (r100=$2, lowest rank: priority 1), so mode conflicts with v0
 * and takes v1; result (priority 3, allocated first) takes v0. Retail needs result v1 and v0 busy at
 * the fix (scratch a1). result only avoids v0 when a block-local pseudo holds v0 in its life (the
 * block-28 mode load of hud_coord), and then nothing holds v0 at the fix. Tried without gain:
 * plain rounding (+do/while(0) forms: 23-55), mode read after scaled/result, hud_coord2 in draw 2
 * (20), mode-first / mode-only / float tests (not deleted, 1200-1228 bytes), extra mode refs (not
 * deleted), handle test of id before/after (10, copy still after the mode load), do/while(0) around
 * the id call or the mode load (1196 bytes), nested text call, r = hud_coord2 temp (16).
 */
/* 8 November 2026 (source round, v101 wasI): rewrite from 151 to ~11 differing words, same 1192 bytes,
 * prologue, cases, saved registers and reload registers now as retail. What did it:
 * - `for (i = 0; i < 2; i++)` with scalar first/second (loop reversal gives retail's count at 0x30).
 * - hud_coord dead-test helper (002D2188-g8.c / 00326A10-g8.c idiom, owner-allowed) for the three
 *   Y roundings, `value * scale` order: puts the arg moves after the rounding as retail.
 * - `one = 1` at the loop top, passed as `active`: loop.c matches it with the case-1 compare
 *   constant and hoists both, so the compare's 1 is a reload in a0 as retail.
 * - `secondX = 0` first among the zero inits: secondX ranks last in global-alloc (fp), as retail.
 * - `D_001B1928.rows[i].value` as the sprintf argument: its address insns sit between the format's
 *   %hi and its use, so the %hi life reaches 4 and loop.c hoists it; the spilled %hi is
 *   rematerialized in v0, which moves the 0x8710 reloads to a2 as retail.
 * Left (sched2 ties): first draw `addiu a1,0xB2` vs `addu a0`/`lwc1 f20` order, and in both draws
 * `daddu a0,v0` before `mtc1 x` instead of after its cvt. Cause: our fix_truncsfsi2 GPR scratch is
 * v0 (round robin after the a2 reload; v0 free); retail's must be a1, which needs v0 busy at the
 * fix. -fno-gcse gives a1 there but loses the %hi hoist. Literal 1 as `active` keeps the formal
 * copy (fixes the second draw, 9 words with first two literal and third `one`), but its copy is
 * set before the id copy so it takes a1, not v0. Tried without gain: label_y, the L05 hud_coord,
 * mode-first test (not deleted), handle test, `one = 1` per draw, inline text helper, `half` local,
 * nested text call, active-first parameter order.
 */
/* 8 November 2026 (REG_EQUIV round): local-alloc/regclass/reload1 equivalence code equals upstream 2.95.2 (update_equiv_regs, no_equiv, the REG_EQUIV REG_LIVE_LENGTH *= 2); SN 2.95.2 v2.73a gives the same REG_EQUIV notes, register stats and dispositions as ours here. Env probes (EE 991111 note test, MEM equiv for multi-block pseudos, no *= 2, replace in one block, move init in loops) leave 138 masked words; SN body equals ours. All-units sweep changes 197/602/3181/182/0 matched units. */
/* func_0028A670. Best C below (8 November 2026). Unit profile of src/game/00288D88.c: -O2 -G0
 * -ffunction-sections. Needs CounterRow and D_001B1928 from src/game/00288D88.c. */
#include "common.h"

typedef struct { float value[7]; } CounterWidths;
extern float D_001A8DE0[];
extern char D_001A8E00[];
extern unsigned char *D_001A8CFC __attribute__((sda));
extern float D_001B23A4 __attribute__((sda));
extern int func_00283D38(int, int, float);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_0027F980(int, int, unsigned long long, unsigned char *, int);

/* The display mode word beside the HUD scale. */
extern int D_001B23A0 __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel; the display-mode test
   has no effect on the result (as func_00326A10). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && D_001B23A0 == active)
        scaled = 1.0f;
    return result;
}

void func_0028A670(void)
{
    char text[16];
    unsigned char active;
    CounterWidths widths;
    int firstX, y, secondY, x, firstY, secondX;
    unsigned int color;
    CounterRow *row;
    int i;
    unsigned int first, second;
    float fade, scale, width;
    int len;
    int one, id;

    secondX = 0;
    color = 0;
    y = 0;
    secondY = 0;
    x = 0;
    firstY = 0;
    widths = *(CounterWidths *)D_001A8DE0;
    scale = 0.0f;
    first = 0;
    second = 0;
    for (i = 0; i < 2; i++) {
        row = &D_001B1928.rows[i];
        firstX = 0;
        one = 1;
        switch (row->state) {
        case 1:
            fade = (float)row->age * 0.0714285746f;
            first = func_00283D38(0x00F0C070, 0x55F0C070, fade);
            second = func_00283D38(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = func_00283D38(0x001010F0, 0x801010F0, fade);
            else
                color = func_00283D38(0x0029A1FF, 0x6029A1FF, fade);
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 2:
            if (row->timer < 14)
                fade = (float)row->timer * 0.0714285746f;
            else
                fade = 1.0f;
            first = 0x55F0C070;
            second = 0x60442D00;
            if (row->value < 0)
                color = func_00283D38(0x001010F0, 0x801010F0, fade);
            else
                color = func_00283D38(0x8000FFFF, 0x6029A1FF, fade);
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 3:
            if (row->timer < 7)
                fade = 1.0f;
            else
                fade = 1.0f - ((float)row->timer - 7.0f) * 0.142857149f;
            first = func_00283D38(0x00F0C070, 0x55F0C070, fade);
            second = func_00283D38(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = func_00283D38(0x001010F0, 0x801010F0, fade);
            else
                color = func_00283D38(0x0029A1FF, 0x6029A1FF, fade);
            x = 442;
            scale = 1.0f;
            y = 36;
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            break;
        }
        if (firstX) {
            func_00115DA8(text, D_001A8E00, D_001B1928.rows[i].value);
            len = func_001157AC(text);
            if (len > 0) {
                width = widths.value[len - 1];
                active = one;
                id = func_00336D50(D_001A8CFC + 0x8710, 178);
                func_00300A00((char *)id, first,
                    (float)firstX, (float)hud_coord((float)firstY, D_001B23A4, 0.5f, active), scale, scale, width);
                id = func_00336D50(D_001A8CFC + 0x8710, 179);
                func_00300A00((char *)id, second,
                    (float)secondX, (float)hud_coord((float)secondY, D_001B23A4, 0.5f, active), scale, scale, width);
                func_0027F980(x, hud_coord((float)y, D_001B23A4, 0.5f, one), (int)color, (unsigned char *)text, func_001157AC(text));
            }
        }
    }
}
