/* 9 November 2026 (o101): 18 -> 17 rows (masked 17 -> 16, 1388/1388). Change: case 0 reads the scale into s first (`s = D_001B23A4[0]; s = (float)hud_coord(128.0f, s, half, one);`), so the 128 multiply reads $f2 and only the 285 rounding reads the $f3 copy, as retail. Case 1/2 has the same row (+0x464); the same form there (top on D_001B23A4[0], or s, with/without a do-group) gives 18-25 or 1396 bytes: a group around top fixes it but moves top to $s0 and the D_001A9008 load (as case 0's +0x218 row). `edge = lower - step; upper = edge + scale;` fixes +0x2C4 but scale (86) then dies at upper's birth, so it no longer conflicts with upper (141, $f21) and 1.0/0.0 swap $f21/$f22 (24). label_y3/label_y4 at the text sites (9 mixes x two call-2 arg forms): 17-37; hud_coord with the mode test last or before the rounding on each case rounding: same code or worse. */
/* 9 November 2026 (o85 dump round): 18 rows kept. Mechanism of text call 2 (dumps -ds -dG -dt -dg): gcse CPROP turns call 2's 1.0/0.0 args (insns 205/207/209, block after label_y#2's dead-test labels) into constants; cse2 then restores pseudo 86 (scale) because its block, started at a label_y#1 label, holds call 1's `f14 = p86` insns with REG_EQUAL 1.0. Retail's `mov.s $f14,$f22; mov.s $f15,$f14` fits reload_cse_simplify_set (const src cost 6 >= 2: lowest reg holding 1.0 -> f22 for f14, then f14 for f15; f21 for 0.0), which needs call 2's args still constant after cse2 AND no CODE_LABEL between f22's set and call 2 at reload; label_y#2's labels survive to .greg (flow deletes only the dead `scaled` sets). Probes: hard-reg f15=f14 from cse1 (literal call 2 with scale set late, or do-while(0) around the 0xA7 text call) is undone by cse2 (pseudo cost 1 < hard reg 2); 7-10 dead tests at call 2 (path limit 9) or an && dead test (2-use label) keep the consts but lose the f22 copy (lui/mtc1) and change size; hud_coord/(void *) handles at either site and plain roundings: no change. No match. */
/* 9 November 2026 (Sonnet s47, lessons 49/52): re-measured 18 rows. do-while(0) groups of 1-3 statements at every line (1500 variants) x every -frac2-* switch singly: no gain (only -fno-gcse differs, 1384 bytes). label_y/label_y2/label_y3 at the two text label sites, all 9 mixes: 18 best (20-70 others). Call-2 args as 1.0f/scale/copy/zero fold to the same code; single-statement moves in the main block: none better. No match. */
/* 9 November 2026 (label_y2 sweep (owner ruling 2026-11-09, Sonnet s46): either label_y call as label_y2 (half or scale form) 18 -> 26/62 rows, both 70; no gain. */
/* 9 November 2026 (Sonnet round 3, lesson 49 audit): 18 rows kept. Locals pulse/scale/zero/half/one/s/step are real; `edge` for one or both case-0 sites (26-27), `scale + (lower - step)` (26), `lower = upper + step - scale` (154) are worse. A `nv=285` or top temp, or splitting `pulse = f(); pulse *= 0.1f`, change nothing (18-21). 25-minute permuter (-j2) 185 -> 150 only via those no-op temps (no row change). No match. */
/* 8 November 2026 (Sonnet round 2, lesson 49): removing the `edge` local in both case-0 loops (`upper = lower - step + scale;`, `lower = upper + step - 1.0f;`) puts 1.0/0.0 in retail's $f22/$f21: 27 -> 18 differing rows. Body below is that C. Left: text call 2 (retail f15=f14), mov $f3 copy read by the 128 multiply (both cases), f0 temp in the case-0 init lines. No gain from: other call-2 argument spellings, dropping `y`/`half`/`step`, `s` locals, a `sc` copy of D_001B23A4 at any subset of the case-0 sites. */
/* 8 November 2026 (Sonnet round): re-measured 77 differing rows (-g8 unit, profile above). Moving the 1.0/0.0 set before/after label_y, a y local for call 2, literal 1.0f/0.0f in the case-0 compare and in edge+scale: no change or worse (b3 237). 25-minute permuter (-j2) best 375 -> 235 only via `D_001A9008 <= (long long)scale` (a changed compare, not honest); no honest gain. */
/* 8 November 2026, round 2: 1388/1388 bytes, about 20 instructions differ. GPRs and case 1/2 are now exact:
 * case 1/2 passes literal 1, and `one` keeps retail's $s2 because the case-0 `top` call sits in a one-pass
 * do/while(0) group (loop weighting lifts `one` from 14/302 above the case-0 colour, 3/60); top reads
 * D_001B23A4[0] directly. Left: 1.0/0.0 swapped in $f21/$f22 (1.0 has 9 refs/178 insns, 0.0 has 4/66, so 1.0 goes
 * first; retail needs a conflict or fewer 1.0 refs); text call 2 is mov $f14,$f22 / mov $f15,$f14 in retail;
 * the 128 multiply reads the copy $f3, not $f2 (no top/128 argument mix fixed it); case-0 second-loop temps
 * f0/f1/f2 swapped; the colour-2 copy and the D_001A9008 load swap at 0x2D0 (the group's loop note).
 * Tried with no gain: moving `one = 1` (sched hoists it anyway), swapping the zero/scale declarations,
 * grouping the other helpers or call statements (worse or 1396 bytes), dropping `edge` in case 0. */
/* 8 November 2026, dead-test helper sweep: now 1388/1388 bytes, same six saved GPRs and six FPRs, case order right.
 * Profile: own -g8 unit, -O2 -G8 -fno-expensive-optimizations -ffunction-sections -frac2-keep-block-order.
 * What closed the gap: hud_coord (label_y with the rounded result as handle, owner ruling 8 November 2026) on
 * every case rounding (top, 128, 285); `one`, a local holding 1, as `active` everywhere (gives retail's ghost
 * $s2 in the text phase); `s = D_001B23A4[0]` for top and the 128 result written back into s (gives retail's
 * mov.s $f3,$f2 copy for the 285 rounding); an `edge` local for lower-step and upper+step (retail's $f0 temp);
 * (float)top written out in case 0 instead of a `limit` variable (fixes the case-0 loop registers).
 * Left (~25 instructions): text call 2 is mov $f14,$f22 / mov $f15,$f14 in retail (cse picked the pseudo here);
 * 1.0/0.0 sit in $f21/$f22 swapped; the 128 multiply reads the copy $f3 instead of $f2 (both cases); f0/f1/f2
 * temps in the case-0 second loop. Case 1/2 is exact with literal 1 for `active` there, but then `one` loses
 * $s2 to 0x8710 (priority 14/302 vs case-0 colour), so this draft keeps `one` in case 1/2.
 * -fno-gcse breaks size (1376). Mode-test-last helper order and the && helper made it worse. */
/* 7 November 2026, label_y sweep: both 206.0f label ys go through label_y (handle: the sprite; the second sprite now in `text`), the bars unchanged. Same profile (-O2 -G8 -fno-expensive-optimizations): still 1364/1388 bytes, but masked aligned-diff rows 392 -> 336 (m1d h.py count; not a check.py figure). The size gap and case layout remain. */
/* Closer C3, 1 November 2026: the profile below is wrong. Retail has sched1 on: -O2 -G8 -fno-expensive-optimizations
 * -ffunction-sections. 206.0f, 0x8710, 0.5f are call-crossing pseudos and float up over the calls as in retail; literal args go
 * straight to hard regs; with that the first 0x128 bytes agree but for the save count. Left: one more saved GPR
 * and 1.0/0.0 stop just after the y conversion: a pseudo that crosses no call cannot pass the last call (sched_analyze),
 * yet retail keeps them in f22/f21 for case 0, so what holds them there is not found.
 */
/* func_002900B8: retained plain-C near miss (opus-1, Claude Opus 5.5, task v1928, 31 October 2026).
 *
 * Unit: a dedicated *-g8.c file compiled with
 *   -O2 -G8 -fno-expensive-optimizations -ffunction-sections -frac2-keep-block-order -fno-schedule-insns
 * Best check.py: 1380/1388 bytes, 0 of 28 US v1.01 places match. PAL and US2 not checked.
 * Same size as the previous 1380-byte draft, but much closer in sequence: 188 of 347 retail
 * instructions line up in order (difflib LCS, relocations ignored) against 142 for that draft.
 *
 * Evidence used (retail):
 * - 484.0f is loaded fresh with li.s for both text calls while 1.0f/0.0f/206/0.5 are shared:
 *   constant call arguments go straight to the hard argument register, as with
 *   -fno-expensive-optimizations (calls.c copies them into pseudos only when
 *   preserve_subexpressions_p(), i.e. flag_expensive_optimizations). Most matched HUD text
 *   callers of func_00300A00 (002D1228-g8.c, 002CDD88-g8.c, 002D1E70-rc2.c) use that flag.
 * - Case 0 and case 1/2 use different pseudos for their bar variables (lower is $f20 in case 0
 *   and $f22 in case 1/2, limit the reverse; colours $s3/$s4 vs $s2), and the text colours
 *   ($s0/$s1) differ from the bar colours: hence block-scoped locals per case.
 * - Case-0 arithmetic is in source order (top, then 128, then 285), as with sched1 off.
 *
 * Still differs: five saved GPRs and seven FPRs (retail six and six), so $s and $f numbers are
 * shifted almost everywhere; retail keeps %hi(D_001B9040) in $s5 and 0x8710 in $s3.
 * Unexplained retail details, for the next attempt:
 * - Text call 2 is `mov.s $f14,$f22; mov.s $f15,$f14; mov.s $f16,$f21`, call 1
 *   `mov.s $f14,$f22; mov.s $f15,$f22; mov.s $f16,$f21`. cse prefers a pseudo (cost 1) to a
 *   hard reg (cost 2), so f15=f14 means no pseudo was known to hold 1.0 when cse saw call 2;
 *   f14=f22/f16=f21 then come from reload_cse_regs (constant replaced by a hard reg holding it),
 *   which forgets everything at a CODE_LABEL. Yet case 0 uses $f22/$f21 for 1.0/0.0 too.
 * - The 1.0/0.0 loads, call 2's argument loads and each loop's `i = 0` are not hoisted by
 *   sched2 in retail (ours are), which looks like extra basic-block boundaries (for example a
 *   test that cross-jumping removes at jump2) that this wording does not have. A placeholder
 *   test (`scaled_screen_size(first, ...)`, v1926 draft) is not allowed.
 * - Retail copies the scale (mov.s $f3,$f2) before the 285 product; int temporaries use $a1/$a0
 *   in places (mfc1 $a1 for lower, mfc1 $a0 in the second loop).
 * Declarations: the -G8 sibling already declares func_002900B8 as int (callback interface).
 */
#include "common.h"

extern int D_001A9000 __attribute__((sda));
extern int D_001A9004 __attribute__((sda));
extern float D_001A9008 __attribute__((sda));
extern int D_001A900C __attribute__((sda));
extern int D_001A9010 __attribute__((sda));

typedef struct {
    int active;
    int timer;
    char pad08[0x18];
    int entryIndex;
    int unk24;
} Subtitle_002900B8;

typedef struct {
    char pad[0xB0];
    float opacity;
} Hud_002900B8;

extern char *D_001A8CFC[] __attribute__((sda));
extern Subtitle_002900B8 D_00254E78;
extern Hud_002900B8 D_001B9040;
extern float D_001B23A4[] __attribute__((sda));
extern int D_001A8D40 __attribute__((sda));
extern void func_0027AB40(void);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_0027DE50(int, int, int, int, unsigned long);

extern int D_001B23A0;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
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

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

int func_002900B8(void)
{
    float saved;
    float pulse;
    float scale;
    float zero;
    float y;
    char *text;
    int first;
    int second;
    int one;
    float half;

    if (D_001A8CFC[0] != 0 && D_00254E78.active == 0 && D_00254E78.unk24 == -1) {
        one = 1;
        half = 0.5f;
        saved = D_001B9040.opacity;
        D_001B9040.opacity = 0.62f;
        func_0027AB40();
        pulse = func_00283CE0(D_001A9000) * 0.1f;
        first = func_00283D38(0x442D00, 0x60442D00, pulse);
        second = func_00283D38(0xF0C070, 0x55F0C070, pulse);
        text = func_00336D50(D_001A8CFC[0] + 0x8710, 0xA6);
        y = (float)label_y(text, 206.0f, D_001B23A4[0], half, one);
        scale = 1.0f;
        zero = 0.0f;
        func_00300A00(text, first, 484.0f, y, scale, scale, zero);
        text = func_00336D50(D_001A8CFC[0] + 0x8710, 0xA7);
        func_00300A00(text, second, 484.0f, (float)label_y(text, 206.0f, D_001B23A4[0], half, one), 1.0f, 1.0f, 0.0f);
        switch (D_001A9004) {
        case 0:
            if (zero <= D_001A9008 && D_001A9008 <= scale) {
                int color1;
                int color2;
                int top;
                int i;
                float step;
                float lower;
                float upper;
                float edge;
                float s;

                color1 = func_00283D38(D_001A900C & 0xFFFFFF, D_001A900C, pulse);
                color2 = func_00283D38(D_001A9010 & 0xFFFFFF, D_001A9010, pulse);
                do {
                    top = hud_coord((float)(285 - (int)((scale - D_001A9008) * 157.0f)), D_001B23A4[0], half, one);
                } while (0);
                s = D_001B23A4[0];
                s = (float)hud_coord(128.0f, s, half, one);
                step = s * 0.25f;
                lower = (float)hud_coord(285.0f, D_001B23A4[0], half, one);
                upper = lower - step + scale;
                for (i = 0; i < 5; i++) {
                                        if (upper <= (float)top)
                        upper = (float)top;
                    func_0027DE50((int)upper, (int)lower, 477, 489, color1);
                    lower -= step;
                    upper -= step;
                    if (lower <= (float)top)
                        break;
                }
                upper = (float)hud_coord(128.0f, D_001B23A4[0], 0.5f, one);
                lower = upper + step - 1.0f;
                for (i = 0; i < 5; i++) {
                                        if ((float)top <= lower)
                        lower = (float)top;
                    func_0027DE50((int)upper, (int)lower, 476, 488, color2);
                    upper += step;
                    lower += step;
                    if ((float)top <= upper)
                        break;
                }
            }
            break;
        case 1:
        case 2: {
            int color;
            int top;
            int i;
            float step;
            float lower;
            float upper;
            float limit;
            float s;
            float edge;

            color = func_00283D38(D_001A900C & 0xFFFFFF, D_001A900C, pulse);
            s = D_001B23A4[0];
            top = hud_coord((float)(285 - (int)((1.0f - D_001A9008) * 157.0f)), s, 0.5f, 1);
            s = (float)hud_coord(128.0f, D_001B23A4[0], 0.5f, 1);
            step = s * 0.25f;
            lower = (float)hud_coord(285.0f, D_001B23A4[0], 0.5f, 1);
            edge = lower - step;
            upper = edge + 1.0f;
            for (i = 0; i < 5; i++) {
                limit = (float)top;
                if (upper <= limit)
                    upper = limit;
                func_0027DE50((int)upper, (int)lower, 476, 488, color);
                lower -= step;
                upper -= step;
                if (lower <= limit)
                    break;
            }
        }
        }
        D_001B9040.opacity = saved;
        func_0027AB40();
    }
    return D_001A8D40;
}
