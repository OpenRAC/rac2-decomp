#include "common.h"
extern int D_001A7340[] MACRO_ADDR;
extern int D_L00_001AF5A8[];
extern float func_00283CE0(s32);
extern u64 func_0027C878(s32);
extern int func_00283CF0(float);
extern s32 func_002A77E0(s32);
extern void func_0027E018(int, int, int, int, int, int, int, int, s64, u64);
/* Tiles an alpha-blended texture over the current viewport. */
void func_PAL_L00_003A3FC8(void *actor) {
    char *state = *(char **)((char *)actor + 0x68);
    u64 texture;
    int color;
    int columns, rows, row, column, nextRow;
    int u, v, x, y;
    float tick, limit, phase, opacity;
    int base;
    float scale[2];
    float pos[2];

    scale[0] = func_00283CE0(D_001A7340[2]);
    scale[1] = func_00283CE0(D_001A7340[3]);
    texture = func_0027C878(30);
    rows = D_001A7340[0] / 32 + 1;
    columns = D_001A7340[1] / 32 + 1;
    for (row = 0; row < rows; row++) {
        int *p = D_L00_001AF5A8;
        for (column = 0; column < columns; column++) {
            pos[0] = (float)(row << 5);
            pos[1] = (float)(column << 5);
            phase = (float)*p;
            tick = func_00283CE0(*(int *)(state + 0x140));
            limit = func_00283CE0(75);
            opacity = (tick * 127.5f) / limit;
            color = (func_00283CF0(opacity) << 24) + 0x00FF7F7F;
            u = func_002A77E0(32);
            v = func_002A77E0(32);
            x = func_00283CF0(pos[0] - phase);
            y = func_00283CF0(pos[1] - phase);
            func_0027E018(x, y, 32, 32, u, v, 32, 32, color, texture);
        }
    }
}
