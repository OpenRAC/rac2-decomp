#include "names.h"
/* func_L00_003B5210 (180 bytes, 27 levels): for each of the four slots with a count,
   rebuilds its effect record from the slot's level scaled by the global factor. The two
   short tables are read through the absolute macro (MACRO_ADDR); the count-up index
   becomes the retail count-down loop. */
#include "common.h"
extern short D_L00_001B28B0[] MACRO_ADDR;
extern short D_L00_001B28B8[] MACRO_ADDR;
extern float D_L00_001B28D8;
extern char D_L00_0023D9E0[];
extern float D_L00_001AFA00 __attribute__((sda));
extern float D_L00_001AFA04 __attribute__((sda));
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void gfx_l00_draw_ribbon_with_halo_2(void *, int, int, int, float, float, float);
void jitter_trail_draw(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (D_L00_001B28B0[i] != 0) {
            int v = FloatToInt(IntToFloat(D_L00_001B28B8[i]) * D_L00_001B28D8);
            gfx_l00_draw_ribbon_with_halo_2(D_L00_0023D9E0 + i * 0x50, v, v, 5, D_L00_001AFA00, D_L00_001AFA04, 0.2f);
        }
    }
}
