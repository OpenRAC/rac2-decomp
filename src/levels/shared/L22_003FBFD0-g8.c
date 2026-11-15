#include "include_asm.h"
#include "names.h"
/* func_L22_003FBFD0: the level's copy of func_00313600 - the eight entries turned around the
   axis table by the small-data angle, then scaled. -G8 unit for the $gp reads. */
extern char D_L22_002558A0[];
extern char D_L22_00255820[];
extern float D_L22_001B0C60 __attribute__((sda));
extern float D_L22_001B0C5C __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

void part_rotate_anchor_table(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        char *entry = D_L22_00255820 + i * 16;
        math_apply_axis_rotation_to_quat(entry, entry, D_L22_002558A0 + i * 16, D_L22_001B0C60);
        vec_scale_to_length(entry, entry, D_L22_001B0C5C);
    }
}
