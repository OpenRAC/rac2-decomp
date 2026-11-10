#include "include_asm.h"
#include "common.h"

/* func_PAL_0033A9B0, the PAL copy of func_00338AD8: the same panel, where the text lines are drawn
   in every mode (USA only in mode 1), at the offsets of the panel's mode, with the scaled text call
   and the scale of func_PAL_0033A598.
   Bordered text panel: background box, six border pieces, then the text lines.
   The border offsets are per-program records (ref_ names); 0x1D0 is a float field.
   Retail reaches the offset table's x column through $gp and its y column as an absolute address,
   so the table has two names, as in other mixed GP/absolute accesses (docs/build/compiler-notes.md). */
typedef struct { float x, y; } BorderOffset_00338AD8;
typedef struct { int x, y; } TextOffset_00338AD8;
extern BorderOffset_00338AD8 ref_00338AD8_00;
extern BorderOffset_00338AD8 ref_00338AD8_01;
extern TextOffset_00338AD8 ref_00338AD8_02[] __attribute__((sda));
extern TextOffset_00338AD8 ref_00338AD8_02_gp[] SDATA(ref_00338AD8_02);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00336320(void *);
extern float func_PAL_0033A598(void *, int);
extern void func_PAL_0027FE88(float, float, long, signed char *, int, float);

void func_PAL_0033A9B0(char *object)
{
    unsigned int colors[4];
    BorderOffset_00338AD8 corner;
    BorderOffset_00338AD8 edge;
    float x, y;
    int i = 0, textX, textY;
    char *top = object + 0x10;
    char *side = object + 0x5c;
    colors[0] = **(unsigned int **)(object + 8);
    colors[1] = colors[0];
    colors[2] = colors[0];
    colors[3] = colors[0];
    func_0027EAE8((int)((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)),
                 (int)((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)),
                 (int)((*(float **)object)[0] + (float)*(int *)(object + 0x1a8)),
                 (int)((*(float **)object)[1] + (float)*(int *)(object + 0x1ac)), 0xfffff0, colors);
    corner = ref_00338AD8_00;
    edge = ref_00338AD8_01;
    func_00335E38(top, ((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - corner.x,
                      ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - corner.y, 0.0f, 0.0f);
    func_00335F88(top, -1.0f, 1.0f, 0.0f, 0.0f);
    func_00336320(top);
    func_00335E38(top, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + corner.x + 1.0f,
                      ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - corner.y, 0.0f, 0.0f);
    func_00335F88(top, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00336320(top);
    func_00335E38(side, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + edge.x,
                       ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y, 0.0f, 0.0f);
    func_00335F88(side, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00336320(side);
    func_00335E38(side, ((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - edge.x + 1.0f,
                       ((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y, 0.0f, 0.0f);
    func_00335F88(side, -1.0f, 1.0f, 0.0f, 0.0f);
    func_00336320(side);
    func_00335E38(side, (*(float **)object)[0] + (float)*(int *)(object + 0x1a8) + edge.x,
                       (((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y) + *(float *)(object + 0x1d0), 0.0f, 0.0f);
    func_00335F88(side, 1.0f, -1.0f, 0.0f, 0.0f);
    func_00336320(side);
    func_00335E38(side, (((*(float **)object)[0] - (float)*(int *)(object + 0x1a8)) - edge.x) + 1.0f,
                       (((*(float **)object)[1] - (float)*(int *)(object + 0x1ac)) - edge.y) + *(float *)(object + 0x1d0), 0.0f, 0.0f);
    func_00335F88(side, -1.0f, -1.0f, 0.0f, 0.0f);
    func_00336320(side);
    x = (*(float **)object)[0];
    y = (*(float **)object)[1];
    textX = (int)((x - (float)*(int *)(object + 0x1a8)) + (float)*(int *)(object + 0x1bc));
    textY = (int)(y - (float)*(int *)(object + 0x1ac));
    if (*(int *)(object + 0x1d8)) {
        for (; i < *(int *)(object + 0x1b0); i++) {
            int mode = *(int *)(object + 0x1c4);
            func_PAL_0027FE88((float)(textX + ref_00338AD8_02_gp[mode].x),
                              (float)(textY + ref_00338AD8_02[mode].y + i * 16),
                              **(unsigned int **)(object + 12), ((signed char **)(object + 0x1d8))[i], -1,
                              func_PAL_0033A598(object, mode));
        }
    }
}
