#include "include_asm.h"
#include "names.h"
/* func_L22_003FBFD0: the level's copy of func_00313600 - the eight entries turned around the
   axis table by the small-data angle, then scaled. -G8 unit for the $gp reads. */
extern char g_effect_anchor_axes[];
extern char g_effect_anchor_table[];
extern float g_anchor_table_rotation __attribute__((sda));
extern float g_anchor_table_length __attribute__((sda));
extern void vec_scale_to_length(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

void part_rotate_anchor_table(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        char *entry = g_effect_anchor_table + i * 16;
        math_apply_axis_rotation_to_quat(entry, entry, g_effect_anchor_axes + i * 16, g_anchor_table_rotation);
        vec_scale_to_length(entry, entry, g_anchor_table_length);
    }
}
