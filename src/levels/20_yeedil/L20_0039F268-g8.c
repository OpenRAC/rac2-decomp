#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void DrawTwoLayerPolylineRibbon(void *, int, int, int, unsigned int, unsigned int, float, float, float);
extern short g_orb_arm_numerators[10] MACRO_ADDR;
extern short g_orb_arm_alphas[10] MACRO_ADDR;
extern short g_orb_arm_denominators[10] MACRO_ADDR;
extern float g_orb_alpha_scale[] MACRO_ADDR;
extern Vector g_electric_orb_arm_points[10][10];
extern Vector D_L20_00235580_1[10][10];
extern float g_electric_arm_alpha __attribute__((sda));
extern unsigned int g_electric_arm_color __attribute__((sda));
extern unsigned int g_tesla_barrier_arm_color __attribute__((sda));

/* Draws the ten fading arms of the electric orb, each one following behind the orb. */
void electric_orb_draw_arms(unsigned char *object) {
    Vector offset;
    Vector origin;
    Vector differences[10];
    unsigned char *state = *(unsigned char **)(object + 0x68);
    int i, j, k, alphaValue;
    Vector (*row)[10];
    Vector (*table)[10] = g_electric_orb_arm_points;
    float numerator, denominator;
    unsigned int colour;
    offset.q = 0;
    offset.f[2] = 0.75f;
    FastVecAdd(&origin, object + 0x10, &offset);
    for (i = 0; i < 10; ++i) {
        if (g_orb_arm_numerators[i]) {
            for (j = 1; j < 10; ++j)
                FastVecSub(&differences[j], &g_electric_orb_arm_points[i][j], &D_L20_00235580_1[i][j - 1]);
            qcopy(&g_electric_orb_arm_points[i][0], &origin);
            g_electric_orb_arm_points[i][0].f[3] = 0.04f;
            for (j = 1; j < 10; ++j) {
                FastVecAdd(&g_electric_orb_arm_points[i][j], &D_L20_00235580_1[i][j - 1], &differences[j]);
                /* Two steps: the loop pass cannot look through a register set twice, so the w
                 * pointer starts from (row + 0x1C) as a whole. */
                row = table;
                row += i;
                (*row)[j].f[3] = 0.04f;
            }
            if (g_orb_arm_numerators[i] > 0) {
                numerator = IntToFloat(g_orb_arm_numerators[i]);
                denominator = IntToFloat(g_orb_arm_denominators[i]);
                g_orb_arm_alphas[i] = FloatToInt(g_electric_arm_alpha * *(float *)(state + 0x14) * (numerator / denominator));
            } else g_orb_arm_alphas[i] = 0;
        }
    }
    for (k = 0; k < 10; ++k) {
        if (g_orb_arm_numerators[k]) {
            alphaValue = FloatToInt(IntToFloat(g_orb_arm_alphas[k]) * g_orb_alpha_scale[0]);
            colour = g_electric_arm_color;
            if (*(short *)(object + 0xAA) == MOBY_CLASS_TESLA_BARRIER) colour = g_tesla_barrier_arm_color;
            DrawTwoLayerPolylineRibbon(g_electric_orb_arm_points[k], 23, 14, 10,
                             ((unsigned int)alphaValue << 24) | 0x7F7F7F,
                             ((unsigned int)alphaValue << 24) | colour, 0.0f, 4.0f, 0.0f);
        }
    }
}
