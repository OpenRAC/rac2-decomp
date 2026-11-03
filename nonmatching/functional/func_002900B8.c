/* functional: high. Same reads, writes, calls and arguments in the same order as retail, and the same result; the near miss's matching-only block-scoped locals are kept only where they help reading. func_00283D38 returns a packed RGBA word zero-extended to 64 bits (ppacb), so it is unsigned int, and func_0027DE50's colour is retail's 64-bit register (unsigned long, as the landed callers declare it). Float compare sense and operand order follow retail (c.le.s). */

#include "common.h"

typedef struct {
    int active;     /* +0x00 */
    char pad04[0x20];
    int unk24;      /* +0x24: -1 when free */
} Subtitle_002900B8;

typedef struct {
    char pad[0xB0];
    float opacity;  /* +0xB0 */
} Hud_002900B8;

extern char *D_001A8CFC;            /* lui 0x1B / lw -29444 */
extern Subtitle_002900B8 D_00254E78; /* lui 0x25 / 20088 */
extern Hud_002900B8 D_001B9040;     /* lui 0x1C / -28608 */
extern float D_001B23A4;            /* vertical screen scale */
extern int D_001A8D40;              /* $gp-0x62B0: the result */
extern int D_001A9000;              /* $gp-0x5FF0 */
extern int D_001A9004;              /* $gp-0x5FEC: bar mode */
extern float D_001A9008;            /* $gp-0x5FE8: bar fill, 0..1 */
extern int D_001A900C;              /* $gp-0x5FE4: bar colour 1 */
extern int D_001A9010;              /* $gp-0x5FE0: bar colour 2 */

extern void func_0027AB40(void);
extern float func_00283CE0(int);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_0027DE50(int, int, int, int, unsigned long);

/* HUD callback: unless D_001A8CFC is null or the D_00254E78 slot is busy, sets the HUD opacity to 0.62, draws the
   two sprites 166 and 167 at x 484 / y 206 in two pulsing colours, then a five-segment fill bar (D_001A9008 of 157
   pixels, from y 285 up to 128): mode 0 draws it with colour D_001A900C at x 477..489 and a second pass with colour
   D_001A9010 at 476..488 from the top; modes 1 and 2 draw only the first pass at 476..488. Restores the opacity
   and returns D_001A8D40. */
int func_002900B8(void)
{
    float saved, pulse, step, lower, upper, limit;
    unsigned int first, second;
    int top, i, mode;

    if (D_001A8CFC == 0 || D_00254E78.active != 0 || D_00254E78.unk24 != -1) {
        return D_001A8D40;
    }

    saved = D_001B9040.opacity;
    D_001B9040.opacity = 0.62f;
    func_0027AB40();
    pulse = func_00283CE0(D_001A9000) * 0.1f;
    first = func_00283D38(0x442D00, 0x60442D00, pulse);
    second = func_00283D38(0xF0C070, 0x55F0C070, pulse);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 166), first, 484.0f,
                  (float)(int)(D_001B23A4 * 206.0f + 0.5f), 1.0f, 1.0f, 0.0f);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 167), second, 484.0f,
                  (float)(int)(D_001B23A4 * 206.0f + 0.5f), 1.0f, 1.0f, 0.0f);

    mode = D_001A9004;
    if (mode == 0) {
        if (0.0f <= D_001A9008 && D_001A9008 <= 1.0f) {
            unsigned int color1, color2;

            color1 = func_00283D38(D_001A900C & 0xFFFFFF, D_001A900C, pulse);
            color2 = func_00283D38(D_001A9010 & 0xFFFFFF, D_001A9010, pulse);
            top = (int)((float)(285 - (int)((1.0f - D_001A9008) * 157.0f)) * D_001B23A4 + 0.5f);
            step = (float)(int)(D_001B23A4 * 128.0f + 0.5f) * 0.25f;
            lower = (float)(int)(D_001B23A4 * 285.0f + 0.5f);
            upper = lower - step + 1.0f;
            for (i = 0; i < 5; i++) {
                limit = (float)top;
                if (upper <= limit) {
                    upper = limit;
                }
                func_0027DE50((int)upper, (int)lower, 477, 489, color1);
                lower -= step;
                upper -= step;
                if (lower <= limit) {
                    break;
                }
            }
            upper = (float)(int)(D_001B23A4 * 128.0f + 0.5f);
            lower = upper + step - 1.0f;
            for (i = 0; i < 5; i++) {
                limit = (float)top;
                if (limit <= lower) {
                    lower = limit;
                }
                func_0027DE50((int)upper, (int)lower, 476, 488, color2);
                upper += step;
                lower += step;
                if (limit <= upper) {
                    break;
                }
            }
        }
    } else if (mode >= 0 && mode < 3) {
        unsigned int color;

        color = func_00283D38(D_001A900C & 0xFFFFFF, D_001A900C, pulse);
        top = (int)((float)(285 - (int)((1.0f - D_001A9008) * 157.0f)) * D_001B23A4 + 0.5f);
        step = (float)(int)(D_001B23A4 * 128.0f + 0.5f) * 0.25f;
        lower = (float)(int)(D_001B23A4 * 285.0f + 0.5f);
        upper = lower - step + 1.0f;
        for (i = 0; i < 5; i++) {
            limit = (float)top;
            if (upper <= limit) {
                upper = limit;
            }
            func_0027DE50((int)upper, (int)lower, 476, 488, color);
            lower -= step;
            upper -= step;
            if (lower <= limit) {
                break;
            }
        }
    }

    D_001B9040.opacity = saved;
    func_0027AB40();
    return D_001A8D40;
}
