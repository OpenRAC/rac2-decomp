#include "common.h"

extern int D_001B18D0;
extern float D_gp_F73C __attribute__((sda));
extern float D_gp_F740 __attribute__((sda));
extern int D_gp_F748 __attribute__((sda));
extern int D_gp_F744 __attribute__((sda));

extern float func_00283180(float);
extern float func_00283198(float);
extern void func_0034E220(void *, int, int, int, int);

/* Puts eight radial menu items on a circle and lifts the selected one. */
void func_0034E2E0(void *obj, int x, int y, int z) {
    unsigned i;

    if (gRadialSlotCount != 0) {
        for (i = 0; i < 8; i++) {
            float a = (float)i * 2.0f * 3.1415927f / (float)gRadialSlotCount - 3.1415927f + 1.5707964f;
            int ox = (int)(FastSinOrCosA(a) * (D_gp_F73C * 74.0f)) + 0x69;
            int px = x + ox;
            int oy = (int)(FastSinOrCosB(a) * (D_gp_F740 * 74.0f)) + 0x64;
            int py = y + oy;
            if (i == D_gp_F748) {
                PlaceRadialMenuItem(obj, i, px, py + D_gp_F744, z);
            } else {
                PlaceRadialMenuItem(obj, i, px, py, z);
            }
        }
    }
}
