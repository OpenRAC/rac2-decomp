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
