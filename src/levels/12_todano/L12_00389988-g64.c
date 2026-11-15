#include "common.h"
typedef unsigned int Q12 __attribute__((mode(TI)));
typedef struct { float x, y; } UV12;
extern int D_L12_001AEF48 __attribute__((sda));
extern int D_L12_001AEE34 __attribute__((sda)), D_L12_001AEE38 __attribute__((sda));
typedef short Face12[4][3];
extern short D_L12_001AEE80[12] __attribute__((sda));
extern Face12 D_L12_001AEE82[] __attribute__((sda));
extern Q12 D_L12_001AEE40[4] __attribute__((sda));
extern UV12 D_L12_001AEE98[4] __attribute__((sda));
extern UV12 D_L12_001AEE9C[] __attribute__((sda));
extern void func_00281DE8(void *, int, int, int);
extern void func_00280B90(void *, int, int);

void func_L12_00389988(char *obj) {
    struct {
        Q12 vertices[4];
        int colors[4];
        UV12 uv[4];
        char pad[0x20];
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    int i, j;
    /* Keep the first pass's table bases live across packet initialization. */
    Q12 *vertices = D_L12_001AEE40;
    UV12 *texX = D_L12_001AEE98;
    UV12 *texY = D_L12_001AEE9C;
    func_00281DE8(&frame, D_L12_001AEF48, 2, 128);
    frame.colors[0] = frame.colors[1] = frame.colors[2] = frame.colors[3] = D_L12_001AEE34;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 4; j++) {
            int vertex = D_L12_001AEE80[i * 12 + j * 3];
            int uv = D_L12_001AEE82[i][j][0];
            qcopy(&frame.vertices[j], &vertices[vertex]);
            frame.uv[j].x = texX[uv].x + *(float *)(ctx + 0x10);
            frame.uv[j].y = texY[uv].x;
        }
        draw_world_quad(&frame, 0, 0);
    }
    func_00281DE8(&frame, D_L12_001AEF48 + 1, 0, 128);
    frame.colors[0] = frame.colors[1] = frame.colors[2] = frame.colors[3] = D_L12_001AEE38;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 4; j++) {
            int vertex = D_L12_001AEE80[i * 12 + j * 3];
            int uv = D_L12_001AEE82[i][j][0];
            qcopy(&frame.vertices[j], &D_L12_001AEE40[vertex]);
            frame.uv[j].x = D_L12_001AEE98[uv].x + *(float *)(ctx + 0x10);
            frame.uv[j].y = D_L12_001AEE9C[uv].x;
        }
        draw_world_quad(&frame, 0, 0);
    }
}
