#include "common.h"

extern int g_radial_slot_count;
extern float D_gp_F73C __attribute__((sda));
extern float D_gp_F740 __attribute__((sda));
extern int D_gp_F748 __attribute__((sda));
extern int D_gp_F744 __attribute__((sda));

extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void radial_menu_place_item(void *, int, int, int, int);

/* Puts eight radial menu items on a circle and lifts the selected one. */
void radial_menu_layout_items(void *obj, int x, int y, int z) {
    unsigned i;

    if (g_radial_slot_count != 0) {
        for (i = 0; i < 8; i++) {
            float a = (float)i * 2.0f * 3.1415927f / (float)g_radial_slot_count - 3.1415927f + 1.5707964f;
            int ox = (int)(math_fast_sin_or_cos_a(a) * (D_gp_F73C * 74.0f)) + 0x69;
            int px = x + ox;
            int oy = (int)(math_fast_sin_or_cos_b(a) * (D_gp_F740 * 74.0f)) + 0x64;
            int py = y + oy;
            if (i == D_gp_F748) {
                radial_menu_place_item(obj, i, px, py + D_gp_F744, z);
            } else {
                radial_menu_place_item(obj, i, px, py, z);
            }
        }
    }
}
