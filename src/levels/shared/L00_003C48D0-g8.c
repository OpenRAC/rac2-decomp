#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void DrawTwoLayerPolylineRibbon(void *, int, int, int, unsigned int, unsigned int, float, float, float);
extern short g_tesla_ribbon_ids[5] MACRO_ADDR;
extern short g_electric_ribbon_alphas[5] MACRO_ADDR;
extern short g_electric_ribbon_lengths[5] MACRO_ADDR;
extern float g_electric_ribbon_alpha_scale[] MACRO_ADDR;
extern Vector g_tesla_barrier_points[5][10];
extern Vector D_L00_00240080_1[5][10];
extern float g_electric_ribbon_scale __attribute__((sda));
extern unsigned int g_electric_ribbon_color __attribute__((sda));
extern unsigned int g_tesla_arc_param __attribute__((sda));

/* Moves five electric ribbons to follow their owner and fades them out over time, then draws them. */
void electric_ribbons_update(unsigned char *object) {
    Vector origin;
    Vector differences[10];
    int i, j, k, alphaValue;
    Vector (*row)[10];
    Vector (*table)[10] = g_tesla_barrier_points;
    float numerator, denominator;
    unsigned int colour;
    qcopy(&origin, *(unsigned char **)(object + 0x68) + 0x30);
    for (i = 0; i < 5; ++i) {
        if (g_tesla_ribbon_ids[i]) {
            for (j = 1; j < 10; ++j)
                FastVecSub(&differences[j], &g_tesla_barrier_points[i][j], &D_L00_00240080_1[i][j - 1]);
            qcopy(&g_tesla_barrier_points[i][0], &origin);
            g_tesla_barrier_points[i][0].f[3] = 0.04f;
            for (j = 1; j < 10; ++j) {
                FastVecAdd(&g_tesla_barrier_points[i][j], &D_L00_00240080_1[i][j - 1], &differences[j]);
                row = table;
                row += i;
                (*row)[j].f[3] = 0.04f;
            }
            if (g_tesla_ribbon_ids[i] > 0) {
                numerator = IntToFloat(g_tesla_ribbon_ids[i]);
                denominator = IntToFloat(g_electric_ribbon_lengths[i]);
                g_electric_ribbon_alphas[i] = FloatToInt(g_electric_ribbon_scale * (numerator / denominator));
            } else g_electric_ribbon_alphas[i] = 0;
        }
    }
    for (k = 0; k < 5; ++k) {
        if (g_tesla_ribbon_ids[k]) {
            alphaValue = FloatToInt(IntToFloat(g_electric_ribbon_alphas[k]) * g_electric_ribbon_alpha_scale[0]);
            colour = g_electric_ribbon_color;
            if (*(short *)(object + 0xAA) == MOBY_CLASS_TESLA_BARRIER) colour = g_tesla_arc_param;
            DrawTwoLayerPolylineRibbon(g_tesla_barrier_points[k], 23, 14, 10,
                             ((unsigned int)alphaValue << 24) | 0x7F7F7F,
                             ((unsigned int)alphaValue << 24) | colour, 0.0f, 4.0f, 0.0f);
        }
    }
}
