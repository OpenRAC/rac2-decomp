#include "common.h"

/* func_US2_00339B00, the USA v2.00 copy of func_00338AD8: the same bordered panel, where the
   text offset comes from a table indexed by the panel's mode (0x1C4), and the text is drawn
   with the float wrapper at the scale func_US2_003396E8 gives that mode.
   Retail builds the table's base through $gp and the address of its y field through lui/addiu,
   so the one table has two names: the SDATA view for x, the absolute name for y. */
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
extern void func_US2_0027FFF0(float, float, u64, u8 *, int, float);
extern float func_US2_003396E8(void *, int);

void func_US2_00339B00(char *object)
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
            func_US2_0027FFF0((float)(textX + ref_00338AD8_02_gp[mode].x),
                              (float)(textY + ref_00338AD8_02[mode].y + i * 16),
                              **(unsigned int **)(object + 12), ((u8 **)(object + 0x1d8))[i], -1,
                              func_US2_003396E8(object, mode));
        }
    }
}
