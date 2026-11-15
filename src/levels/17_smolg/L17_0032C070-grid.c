#include "common.h"

/* The screen rectangle is one array: an element read with an offset is two instructions and
   never fills a slot. The scroll word's pointer is set outside the inner loop: loop hoists it, it
   gets no register, and reload builds the address beside the load. */

extern int D_001A7340[] MACRO_ADDR;
extern int D_L17_001AF52C[];
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned long func_0027C878(int);
extern int func_002A77E0(int);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Draws a grid of small square tiles over the whole screen. Each tile fades according to the
   object's timer and shows a random part of the texture. */
void func_L17_003A4740(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float screenSize[2];
    unsigned long packet;
    int columns, rows, i, j;
    float cellPos[2];
    float scroll, alphaNum, alphaDen;
    int color;
    int texU, texV;

    screenSize[0] = IntToFloat(gScreenWidth[2]);
    screenSize[1] = IntToFloat(gScreenWidth[3]);
    packet = GetEffectTextureDescriptor(0x1E);
    columns = gScreenWidth[0] / 32 + 1;
    rows = gScreenWidth[1] / 32 + 1;

    for (i = 0; i < columns; i++) {
        int *scrollPtr = D_L17_001AF52C;
        for (j = 0; j < rows; j++) {
            cellPos[0] = (float)(i * 32);
            cellPos[1] = (float)(j * 32);
            scroll = (float)*scrollPtr;
            alphaNum = IntToFloat(*(int *)(vars + 0x140));
            alphaDen = IntToFloat(0x5A);
            color = (FloatToInt(alphaNum * 127.5f / alphaDen) << 24) + 0xFF7F7F;
            texU = RandomIntBelow(0x20);
            texV = RandomIntBelow(0x20);
            DrawTexturedQuad(FloatToInt(cellPos[0] - scroll), FloatToInt(cellPos[1] - scroll), 0x20, 0x20, texU, texV, 0x20, 0x20, color, packet);
        }
    }
}
