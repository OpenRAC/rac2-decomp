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
#include "include_asm.h"

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

    if (D_001A8CFC[0] != 0 && D_00254E78.active == 0 && D_00254E78.unk24 == -1) {
        saved = D_001B9040.opacity;
        D_001B9040.opacity = 0.62f;
        func_0027AB40();
        pulse = func_00283CE0(D_001A9000) * 0.1f;
        first = func_00283D38(0x442D00, 0x60442D00, pulse);
        second = func_00283D38(0xF0C070, 0x55F0C070, pulse);
        text = func_00336D50(D_001A8CFC[0] + 0x8710, 0xA6);
        y = (float)(int)(D_001B23A4[0] * 206.0f + 0.5f);
        scale = 1.0f;
        zero = 0.0f;
        func_00300A00(text, first, 484.0f, y, scale, scale, zero);
        func_00300A00(func_00336D50(D_001A8CFC[0] + 0x8710, 0xA7), second, 484.0f,
                      (float)(int)(D_001B23A4[0] * 206.0f + 0.5f), 1.0f, 1.0f, 0.0f);
        switch (D_001A9004) {
        case 0:
            if (0.0f <= D_001A9008 && D_001A9008 <= 1.0f) {
                int color1;
                int color2;
                int top;
                int i;
                float step;
                float lower;
                float upper;
                float limit;

                color1 = func_00283D38(D_001A900C & 0xFFFFFF, D_001A900C, pulse);
                color2 = func_00283D38(D_001A9010 & 0xFFFFFF, D_001A9010, pulse);
                top = (int)((float)(285 - (int)((1.0f - D_001A9008) * 157.0f)) * D_001B23A4[0] + 0.5f);
                step = (float)(int)(D_001B23A4[0] * 128.0f + 0.5f) * 0.25f;
                lower = (float)(int)(D_001B23A4[0] * 285.0f + 0.5f);
                upper = lower - step + 1.0f;
                for (i = 0; i < 5; i++) {
                    limit = (float)top;
                    if (upper <= limit)
                        upper = limit;
                    func_0027DE50((int)upper, (int)lower, 477, 489, color1);
                    lower -= step;
                    upper -= step;
                    if (lower <= limit)
                        break;
                }
                upper = (float)(int)(D_001B23A4[0] * 128.0f + 0.5f);
                lower = upper + step - 1.0f;
                for (i = 0; i < 5; i++) {
                    limit = (float)top;
                    if (limit <= lower)
                        lower = limit;
                    func_0027DE50((int)upper, (int)lower, 476, 488, color2);
                    upper += step;
                    lower += step;
                    if (limit <= upper)
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

            color = func_00283D38(D_001A900C & 0xFFFFFF, D_001A900C, pulse);
            top = (int)((float)(285 - (int)((1.0f - D_001A9008) * 157.0f)) * D_001B23A4[0] + 0.5f);
            step = (float)(int)(D_001B23A4[0] * 128.0f + 0.5f) * 0.25f;
            lower = (float)(int)(D_001B23A4[0] * 285.0f + 0.5f);
            upper = lower - step + 1.0f;
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
