#include "common.h"
extern int g_screen_width[] MACRO_ADDR;
extern int g_tile_int_table[];
extern float IntToFloat(s32);
extern u64 GetEffectTextureDescriptor(s32);
extern int FloatToInt(float);
extern s32 math_random_int_below(s32);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, s64, u64);
/* Tiles an alpha-blended texture over the current viewport. */
void DrawTiledScreenOverlay_pal(void *actor) {
    char *state = *(char **)((char *)actor + 0x68);
    u64 texture;
    int color;
    int columns, rows, row, column, nextRow;
    int u, v, x, y;
    float tick, limit, phase, opacity;
    int base;
    float scale[2];
    float pos[2];

    scale[0] = IntToFloat(g_screen_width[2]);
    scale[1] = IntToFloat(g_screen_width[3]);
    texture = GetEffectTextureDescriptor(30);
    rows = g_screen_width[0] / 32 + 1;
    columns = g_screen_width[1] / 32 + 1;
    for (row = 0; row < rows; row++) {
        int *p = g_tile_int_table;
        for (column = 0; column < columns; column++) {
            pos[0] = (float)(row << 5);
            pos[1] = (float)(column << 5);
            phase = (float)*p;
            tick = IntToFloat(*(int *)(state + 0x140));
            limit = IntToFloat(75);
            opacity = (tick * 127.5f) / limit;
            color = (FloatToInt(opacity) << 24) + 0x00FF7F7F;
            u = math_random_int_below(32);
            v = math_random_int_below(32);
            x = FloatToInt(pos[0] - phase);
            y = FloatToInt(pos[1] - phase);
            DrawTexturedQuad(x, y, 32, 32, u, v, 32, 32, color, texture);
        }
    }
}
