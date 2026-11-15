#include "common.h"

/* The viewport is one array, so its reads stay two-word macros out of delay slots. The phase pointer is set outside the inner loop: loop hoists it, it gets no register, and reload builds the address beside the load. */
extern int D_001A7340[] MACRO_ADDR;
extern int D_L00_001AF5A8[];
extern float func_00283CE0(s32);
extern u64 func_0027C878(s32);
extern int func_00283CF0(float);
extern s32 func_002A77E0(s32);
extern void func_0027E018(int, int, int, int, int, int, int, int, s64, u64);
/* Tiles an alpha-blended texture over the current viewport. */
void func_L00_003A09F8(void *actor) {
    char *state = *(char **)((char *)actor + 0x68);
    u64 texture;
    int color;
    int columns, rows, row, column, nextRow;
    int u, v, x, y;
    float tick, limit, phase, opacity;
    int base;
    float scale[2];
    float pos[2];

    scale[0] = IntToFloat(gScreenWidth[2]);
    scale[1] = IntToFloat(gScreenWidth[3]);
    texture = GetEffectTextureDescriptor(30);
    rows = gScreenWidth[0] / 32 + 1;
    columns = gScreenWidth[1] / 32 + 1;
    for (row = 0; row < rows; row++) {
        int *p = D_L00_001AF5A8;
        for (column = 0; column < columns; column++) {
            pos[0] = (float)(row << 5);
            pos[1] = (float)(column << 5);
            phase = (float)*p;
            tick = IntToFloat(*(int *)(state + 0x140));
            limit = IntToFloat(90);
            opacity = (tick * 127.5f) / limit;
            color = (FloatToInt(opacity) << 24) + 0x00FF7F7F;
            u = RandomIntBelow(32);
            v = RandomIntBelow(32);
            x = FloatToInt(pos[0] - phase);
            y = FloatToInt(pos[1] - phase);
            DrawTexturedQuad(x, y, 32, 32, u, v, 32, 32, color, texture);
        }
    }
}
