#include "names.h"


extern int g_hero_locked_flag __attribute__((sda));

extern int D_L00_001A8FF4_1 __attribute__((sda));

extern char D_00189E20_11[];

extern void vec_copy_helper_a(char *a);

extern void vec_compute_flat_direction_from_point(char *a, char *b, int c);

extern void func_00282CF0_5(char *a, char *b, char *c);

extern void func_00282F20_4(char *a, char *b, float f12);

extern void func_00282D30_8(char *a, char *b, float f12);

/* three-way branch on two 32-bit engine flags: one arm calls a helper, one arm calls a three-argument helper, and the third reads a float from a bound table to pick a +1/-1 scale and issues two helper calls; a final call runs only when the third argument is zero. */
/* Works out a flat direction vector from a position, depending on the current view mode.
   The direction is flipped unless the flag is set. */
void cam_compute_view_direction(char *origin, char *outDir, int flag)
{
    char *table;
    float sign;

    if (g_hero_locked_flag == 0) {
        vec_copy_helper_a(outDir);
    } else if (D_L00_001A8FF4_1 != 0) {
        vec_compute_flat_direction_from_point(origin, outDir, 1);
    } else {
        table = D_00189E20_11;
        sign = 1.0f;
        if (0.0f < *(float *)(table + 188))
            sign = -1.0f;
        func_00282CF0_5(outDir, table + 176, origin);
        func_00282F20_4(outDir, outDir, sign);
    }
    if (flag == 0)
        func_00282D30_8(outDir, outDir, -1.0f);
}
