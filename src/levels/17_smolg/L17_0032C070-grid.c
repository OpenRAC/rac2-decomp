#include "common.h"

/* The screen rectangle is one array: an element read with an offset is two instructions and
   never fills a slot. The scroll word's pointer is set outside the inner loop: loop hoists it, it
   gets no register, and reload builds the address beside the load. */

extern int g_screen_width[] MACRO_ADDR;
extern int D_L17_001AF52C[];
extern float IntToFloat(int);
extern int FloatToInt(float);
extern unsigned long GetEffectTextureDescriptor(int);
extern int math_random_int_below(int);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Draws a grid of small square tiles over the whole screen. Each tile fades according to the
   object's timer and shows a random part of the texture. */
void gfx_draw_fading_tile_grid(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float screenSize[2];
    unsigned long packet;
    int columns, rows, i, j;
    float cellPos[2];
    float scroll, alphaNum, alphaDen;
    int color;
    int texU, texV;

    screenSize[0] = IntToFloat(g_screen_width[2]);
    screenSize[1] = IntToFloat(g_screen_width[3]);
    packet = GetEffectTextureDescriptor(0x1E);
    columns = g_screen_width[0] / 32 + 1;
    rows = g_screen_width[1] / 32 + 1;

    for (i = 0; i < columns; i++) {
        int *scrollPtr = D_L17_001AF52C;
        for (j = 0; j < rows; j++) {
            cellPos[0] = (float)(i * 32);
            cellPos[1] = (float)(j * 32);
            scroll = (float)*scrollPtr;
            alphaNum = IntToFloat(*(int *)(vars + 0x140));
            alphaDen = IntToFloat(0x5A);
            color = (FloatToInt(alphaNum * 127.5f / alphaDen) << 24) + 0xFF7F7F;
            texU = math_random_int_below(0x20);
            texV = math_random_int_below(0x20);
            DrawTexturedQuad(FloatToInt(cellPos[0] - scroll), FloatToInt(cellPos[1] - scroll), 0x20, 0x20, texU, texV, 0x20, 0x20, color, packet);
        }
    }
}
