/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_0028A670. Opus 5.5 (v1961). Unit profile of src/game/00288D88.c: -O2 -G0 -ffunction-sections.
 * Best: 1192/1192 bytes, 0/28 USA v1.01 places, 151 of 298 cdiff rows differ, first mismatch +0xC.
 * This C keeps count/first/second in a local struct, which gives the exact size but not retail's
 * registers. Linked build not run. Needs CounterRow and D_001B1928 from src/game/00288D88.c.
 *
 * Measured over 16 comparisons plus allocator dumps; "reads as" marks inference from retail:
 * - Scalars count, first, second are closer in mechanism: the prologue matches and retail's
 *   0x30/0x34/0x38 slots come out, at 1200 bytes. The 8 extra bytes are case 2's first stores:
 *   sched1 splits `first = K` into lui and ori on the spilled pseudo, and each part stores.
 * - Retail's reload registers fit the last_spill_reg round-robin over v0,v1,a0,a1,a2,f1:
 *   count=1 v0; the case-1 constant a0 (v1 holds state); K1 a1; K2 a2; `lui v0` for the format's
 *   %hi; 0x8710 a2 twice; --count a0. This reads as: the constant 1 and the format %hi are
 *   spilled, rematerialized pseudos hoisted by loop.c, which needs savings * life >= 4 here.
 *   Only 0x8710 hoists in this C; no probe reproduces the format %hi in v0.
 * - Each fix_truncsfsi2 takes a GPR scratch, then f1. From f1 the next reload should be v0, yet
 *   the second 0x8710 and --count skip v0 and v1. Two more hidden reloads per Y conversion, or
 *   v0/v1 busy there, would explain it; neither is identified.
 * - `(int)(v * D_001B23A4 + 0.5f)` is the display-scale idiom of 002D3390.c and 002CE5D0-g8.c.
 *   Probe helper, used three times: `if (mode == 1) return (int)(v * S + 0.5f) + adjust;
 *   return (int)(v * S + 0.5f);`.
 *   With mode = count (1296 bytes): `1` hoists (savings 4), a0, a1 and a2 appear as in retail, yy
 *   takes s1, the widened color s0, and `daddu s0,s3` lands in the strlen delay slot as in retail.
 *   The arms do not merge, apparently because their fix insns clobber different GPRs.
 *   With mode = x, a saved register (1236 bytes): the arms cross-jump away, but `addiu v1,zero,1`
 *   stays behind at each site, Y's float moves to f1, 0x8710 becomes v0 and row moves to s3.
 *   No such mode is evidenced here and retail has no load for one, so neither is the source.
 *   Next: find what makes `1` movable and then disappears before reload, for example a test
 *   folded by cse2 plus its jump pass.
 * - Without that helper the widened color is hoisted by sched1 across the draw calls, so it gets
 *   s1 and yy s0. Its source position, `int` versus `long long`, and an X-variable copy all tie.
 * - Testing Y first (`y = (int)...; if (mode == 1) y += adjust;`) becomes a cmove at jump1, with
 *   no hoisted 1 and no effect on the output.
 * - The first store of case 2 is still unexplained: retail stores each color once from a1/a2.
 *   Loop-scope color variables are const-propagated by gcse (4 props, back to double stores).
 *   Function-scope ones with struct stores split, lose REG_EQUIV and take stack slots
 *   (1216 bytes). Unused copies of the colors or of 1 do not make them hoist.
 * - -fno-schedule-insns gives single stores but 1172 bytes. It loses retail's arm-local
 *   `mov.s f12,f20` and `lw v1,0(s2)` before `sw v0,0x38(sp)`, which reads as retail running sched1.
 * - Int returns for func_00300A00 and func_0027F980 change nothing.
 * - Source clue: the fade starts in cases 1 and 3 are their end colors & 0xFFFFFF, as in
 *   002B7E28-g8.c. Retail's saved registers are y s4, secondY s5, x s6, firstY s7, secondX fp;
 *   scalars give y s4, secondX s5, secondY s6, x s7, firstY fp, so secondX must rank last.
 */
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

void func_0028A670(void)
{
    char text[16];
    CounterWidths widths;
    int firstX, secondX, firstY, x, secondY, y;
    unsigned int color;
    CounterRow *row;
    struct { int count; unsigned int first, second; } draw;
    float fade, scale, width;
    int len, yy;

    row = D_001B1928.rows;
    color = 0;
    y = 0;
    secondY = 0;
    x = 0;
    firstY = 0;
    secondX = 0;
    widths = *(CounterWidths *)D_001A8DE0;
    scale = 0.0f;
    draw.first = 0;
    draw.second = 0;
    draw.count = 1;
    do {
        firstX = 0;
        switch (row->state) {
        case 1:
            fade = (float)row->age * 0.0714285746f;
            draw.first = func_00283D38(0x00F0C070, 0x55F0C070, fade);
            draw.second = func_00283D38(0x00442D00, 0x60442D00, fade);
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
            draw.first = 0x55F0C070;
            draw.second = 0x60442D00;
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
            draw.first = func_00283D38(0x00F0C070, 0x55F0C070, fade);
            draw.second = func_00283D38(0x00442D00, 0x60442D00, fade);
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
            func_00115DA8(text, D_001A8E00, row->value);
            len = func_001157AC(text);
            if (len > 0) {
                width = widths.value[len - 1];
                func_00300A00((char *)func_00336D50(D_001A8CFC + 0x8710, 178), draw.first,
                    (float)firstX, (float)(int)((float)firstY * D_001B23A4 + 0.5f), scale, scale, width);
                func_00300A00((char *)func_00336D50(D_001A8CFC + 0x8710, 179), draw.second,
                    (float)secondX, (float)(int)((float)secondY * D_001B23A4 + 0.5f), scale, scale, width);
                {
                    long long style = (int)color;
                    yy = (int)((float)y * D_001B23A4 + 0.5f);
                    func_0027F980(x, yy, style, (unsigned char *)text, func_001157AC(text));
                }
            }
        }
        row++;
    } while (--draw.count >= 0);
}
