#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void DrawTwoLayerPolylineRibbon(void *, int, int, int, unsigned int, unsigned int, float, float, float);
extern short D_L20_001B38B0[10] MACRO_ADDR;
extern short D_L20_001B38C8[10] MACRO_ADDR;
extern short D_L20_001B38E0[10] MACRO_ADDR;
extern float D_L20_001B3904[] MACRO_ADDR;
extern Vector D_L20_00235580[10][10];
extern Vector D_L20_00235580_1[10][10];
extern float D_L20_001AED84 __attribute__((sda));
extern unsigned int D_L20_001AED18 __attribute__((sda));
extern unsigned int D_L20_001AED1C __attribute__((sda));

/* Draws the ten fading arms of the electric orb, each one following behind the orb. */
void electric_orb_draw_arms(unsigned char *object) {
    Vector offset;
    Vector origin;
    Vector differences[10];
    unsigned char *state = *(unsigned char **)(object + 0x68);
    int i, j, k, alphaValue;
    Vector (*row)[10];
    Vector (*table)[10] = D_L20_00235580;
    float numerator, denominator;
    unsigned int colour;
    offset.q = 0;
    offset.f[2] = 0.75f;
    FastVecAdd(&origin, object + 0x10, &offset);
    for (i = 0; i < 10; ++i) {
        if (D_L20_001B38B0[i]) {
            for (j = 1; j < 10; ++j)
                FastVecSub(&differences[j], &D_L20_00235580[i][j], &D_L20_00235580_1[i][j - 1]);
            qcopy(&D_L20_00235580[i][0], &origin);
            D_L20_00235580[i][0].f[3] = 0.04f;
            for (j = 1; j < 10; ++j) {
                FastVecAdd(&D_L20_00235580[i][j], &D_L20_00235580_1[i][j - 1], &differences[j]);
                /* Two steps: the loop pass cannot look through a register set twice, so the w
                 * pointer starts from (row + 0x1C) as a whole. */
                row = table;
                row += i;
                (*row)[j].f[3] = 0.04f;
            }
            if (D_L20_001B38B0[i] > 0) {
                numerator = IntToFloat(D_L20_001B38B0[i]);
                denominator = IntToFloat(D_L20_001B38E0[i]);
                D_L20_001B38C8[i] = FloatToInt(D_L20_001AED84 * *(float *)(state + 0x14) * (numerator / denominator));
            } else D_L20_001B38C8[i] = 0;
        }
    }
    for (k = 0; k < 10; ++k) {
        if (D_L20_001B38B0[k]) {
            alphaValue = FloatToInt(IntToFloat(D_L20_001B38C8[k]) * D_L20_001B3904[0]);
            colour = D_L20_001AED18;
            if (*(short *)(object + 0xAA) == MOBY_CLASS_TESLA_BARRIER) colour = D_L20_001AED1C;
            DrawTwoLayerPolylineRibbon(D_L20_00235580[k], 23, 14, 10,
                             ((unsigned int)alphaValue << 24) | 0x7F7F7F,
                             ((unsigned int)alphaValue << 24) | colour, 0.0f, 4.0f, 0.0f);
        }
    }
}
