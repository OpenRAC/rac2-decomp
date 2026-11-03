/* functional: high. The near-miss draft (1004/1004 bytes, allocation/scheduling off) with common.h's qcopy asm helper written as plain quadword copies, func_00280B90 declared as the port's host routine defines it (host/render.c: gaddr, int, int; the packet and matrix passed as 32-bit game addresses), and the blend pair's unaligned ldl/sdl copy written as two float copies. Level 02's callees mapped through functions.tsv; data by retail's $gp/lui addresses (0x1B0D60 shader table, 0x1B0D68/0x1B0D6C UV columns, 0x1B0DA8..0x1B0DB4 colours, 0x1B368C matrix table). */
/* func_L02_003EB258 (Maktar Nebula, level 02 only): draws a two-layer banded surface. Two quad packets
 * (shaders 0x1B0D60[0..1]); blend weights 0.5 + 0.5*sin-ish(func_00283198) of state+0x14 and of
 * state+0x14 + pi; the band count from the length of the actor's matrix (0x1B368C + state[8]*0x80) row 1;
 * per corner the UVs (layer 1's U scrolled by state+0x18), colours blended between the table colours by the
 * weights (faded by state+0x1C when it is below 1), and the corner x = +-1, y = -1 or -1 + step; then the
 * packets are drawn count times through the matrix, moving every corner's y up by step = 2/count.
 * From the near-miss draft nonmatching/levels/func_L02_003EB258.c. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct {
    float vertex[4][4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long state[4];
} SurfacePacket __attribute__((aligned(16)));

extern int D_L02_001B0D60[2] __attribute__((sda));
extern float D_L02_001B0D68[][2] __attribute__((sda));
extern float D_L02_001B0D6C[][2] __attribute__((sda));
extern unsigned int D_L02_001B0DA8 __attribute__((sda));
extern unsigned int D_L02_001B0DAC;
extern unsigned int D_L02_001B0DB0;
extern unsigned int D_L02_001B0DB4;
extern char *D_L02_001B368C;
extern void func_00281DE8(void *, int, int, int);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern void func_00283658(void *, void *);
extern void func_00280B90(unsigned int, int, int); /* as the port's host routine (host/render.c) defines it */

void func_L02_003EB258(char *actor)
{
    SurfacePacket packet[2];
    float calculated[2];
    float blend[2];
    float normal[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    char *state = *(char **)(actor + 0x68);
    int i, j, layer, slice, count;
    float step;

    for (layer = 0; layer < 2; layer++)
        func_00281DE8(&packet[layer], D_L02_001B0D60[layer], 0, 0x80);
    calculated[0] = func_00283198(*(float *)(state + 0x14)) * 0.5f + 0.5f;
    calculated[1] = func_00283198(func_00283B98(*(float *)(state + 0x14), 3.1415927f)) * 0.5f + 0.5f;
    blend[0] = calculated[0];
    blend[1] = calculated[1];
    count = func_00283CF0(func_00282DF0(D_L02_001B368C + *(int *)(state + 8) * 0x80 + 0x10));
    *(Quad *)normal = 0;
    normal[3] = 1.0f;
    step = 2.0f / (float)count;
    for (i = 0; i < 4; i++) {
        packet[0].uv[i][0] = D_L02_001B0D68[i][0];
        packet[0].uv[i][1] = D_L02_001B0D6C[i][0];
        packet[1].uv[i][0] = D_L02_001B0D68[i + 4][0] + *(float *)(state + 0x18);
        packet[1].uv[i][1] = D_L02_001B0D6C[i + 4][0];
        packet[0].color[i] = func_00283D38(D_L02_001B0DA8, D_L02_001B0DAC, blend[0]);
        packet[1].color[i] = func_00283D38(D_L02_001B0DB0, D_L02_001B0DB4, blend[1]);
        if (*(float *)(state + 0x1C) < 1.0f) {
            packet[0].color[i] = func_00283D38(packet[0].color[i] & 0x00FFFFFF, packet[0].color[i],
                                               *(float *)(state + 0x1C));
            packet[1].color[i] = func_00283D38(packet[1].color[i] & 0x00FFFFFF, packet[1].color[i],
                                               *(float *)(state + 0x1C));
        }
        *(Quad *)packet[0].vertex[i] = *(Quad *)normal;
        if (i < 2)
            packet[0].vertex[i][0] = 1.0f;
        else
            packet[0].vertex[i][0] = -1.0f;
        if (i & 1)
            packet[0].vertex[i][1] = -1.0f;
        else
            packet[0].vertex[i][1] = step + -1.0f;
        *(Quad *)packet[1].vertex[i] = *(Quad *)normal;
        if (i < 2)
            packet[1].vertex[i][0] = 1.0f;
        else
            packet[1].vertex[i][0] = -1.0f;
        if (i & 1)
            packet[1].vertex[i][1] = -1.0f;
        else
            packet[1].vertex[i][1] = step + -1.0f;
    }
    func_00283658(matrix, D_L02_001B368C + *(int *)(state + 8) * 0x80);
    *(Quad *)(matrix + 12) = *(Quad *)(D_L02_001B368C + *(int *)(state + 8) * 0x80 + 0x30);
    for (slice = 0; slice < count; slice++) {
        func_00280B90((unsigned int)&packet[0], (int)matrix, 0);
        func_00280B90((unsigned int)&packet[1], (int)matrix, 0);
        for (j = 0; j < 4; j++) {
            packet[0].vertex[j][1] += step;
            packet[1].vertex[j][1] += step;
        }
    }
}
