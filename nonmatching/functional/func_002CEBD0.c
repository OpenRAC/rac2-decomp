/* functional: high. Same reads, calls, arguments and stores as retail; the near miss's matching-only inline helpers are written out. Float sums keep retail's order ((k * D_001B23A4 + 0.5) + offset; base + 0.07). D_001B23A0 is read once per block as retail does. The model colour (0x80F0F0F0 from lui/ori) is a sign-extended 32-bit value in retail, so int carries it unchanged; the frame colour 0x55F0C070 is positive and goes as func_0028FC48's 64-bit unsigned long. Callees are declared as their C definitions declare them (func_00300AA8 takes its ints and floats in separate registers, so the retail register use is object/flags/transform in a0-a2 and x/y/frame in f12-f14). */

#include "common.h"

extern char *D_001A8CFC;      /* lui 0x1B / lw -29444 */
extern int D_001B23A0;        /* widescreen/aspect flag: 1 adds the offsets */
extern float D_001B23A4;      /* vertical screen scale */
extern float D_001B23A8;      /* horizontal vector base */
extern float D_001AB9E4;      /* $gp-0x360C: y offset of the two models */
extern float D_001AB9E8;      /* $gp-0x3608: y offset of the frame rectangles */
extern char D_00138180[];     /* lui 0x14 / addiu -32384; flags word at +0x1C0 */

extern char *func_00336D50(char *, int);
extern int func_002A9588(int, int, int, int, int);
extern void func_00283388(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00300AA8(char *object, float x, float y, int flags, float frame, float *transform); /* as nonmatching/functional/func_00300AA8.c defines it: ints a0/a1/a2, floats f12/f13/f14 */
extern void func_0028FC48(int, int, int, int, unsigned long, int); /* as src defines it: the colour is a 64-bit register */

/* Menu page draw: fetches item 74 of the table at D_001A8CFC + 0x8710 and a colour (func_002A9588), then draws that
   model twice (at x 58 / y 457 and x 44 / y 187, highlighted 0x80F0F0F0 when flag 0x1000 / 0x4000 of the menu state
   word D_00138180+0x1C0 is set, else the fetched colour), each with a two-row vector block scaled by the model's
   +12 scale, and four thin frame rectangles in colour 0x55F0C070. */
void func_002CEBD0(void)
{
    float v[16];
    char *model;
    int dim, color;
    float base, a, b, y;
    int y0, y1, wide;

    model = func_00336D50(D_001A8CFC + 0x8710, 74);
    dim = func_002A9588(0x60442D00, 0x55F0C070, 25, 0, 0);
    func_00283388(v);

    base = D_001B23A8;
    wide = D_001B23A0;
    a = base;
    ((int *)v)[0] = 0;
    if (wide == 1) {
        a = base + 0.07f;
    }
    v[2] = a;
    b = base;
    if (wide == 1) {
        b = base + 0.07f;
    }
    v[8] = b;
    ((int *)v)[10] = 0;
    func_00282D30(v, v, *(float *)(model + 12));
    func_00282D30(v + 8, v + 8, *(float *)(model + 12));
    color = (*(int *)(D_00138180 + 0x1C0) & 0x1000) ? (int)0x80F0F0F0 : dim;
    y = D_001B23A4 * 457.0f + 0.5f;
    if (D_001B23A0 == 1) {
        y = y + D_001AB9E4;
    }
    func_00300AA8(model, 58.0f, (float)(int)y, color, 0.0f, v);

    base = -D_001B23A8;
    wide = D_001B23A0;
    v[0] = 0.0f;
    a = base;
    if (wide == 1) {
        a = base + -0.07f;
    }
    v[2] = a;
    b = base;
    if (wide == 1) {
        b = base + -0.07f;
    }
    v[8] = b;
    v[10] = 0.0f;
    func_00282D30(v, v, *(float *)(model + 12));
    func_00282D30(v + 8, v + 8, *(float *)(model + 12));
    color = (*(int *)(D_00138180 + 0x1C0) & 0x4000) ? (int)0x80F0F0F0 : dim;
    y = D_001B23A4 * 187.0f + 0.5f;
    if (D_001B23A0 == 1) {
        y = y + D_001AB9E4;
    }
    func_00300AA8(model, 44.0f, (float)(int)y, color, 0.0f, v);

#define FRAME_Y(k) (D_001B23A0 == 1 ? (int)((D_001B23A4 * (k) + 0.5f) + D_001AB9E8) : (int)(D_001B23A4 * (k) + 0.5f))
    y0 = FRAME_Y(278.0f);
    y1 = FRAME_Y(369.0f);
    func_0028FC48(39, y0, 41, y1, 0x55F0C070UL, 0);
    y0 = FRAME_Y(278.0f);
    y1 = FRAME_Y(369.0f);
    func_0028FC48(63, y0, 65, y1, 0x55F0C070UL, 0);
    y0 = FRAME_Y(277.0f);
    y1 = FRAME_Y(279.0f);
    func_0028FC48(39, y0, 65, y1, 0x55F0C070UL, 0);
    y0 = FRAME_Y(368.0f);
    y1 = FRAME_Y(370.0f);
    func_0028FC48(39, y0, 65, y1, 0x55F0C070UL, 0);
#undef FRAME_Y
}
