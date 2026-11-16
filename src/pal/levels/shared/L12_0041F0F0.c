#include "include_asm.h"



#include "common.h"
extern char g_path_zone_table[];
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern int moby_step_controller_pal(char *a, char *b, f32 c);

/* Aim pass over the slot the 0x110 record names: measure the two position differences,
   turn them into an angle, hand the slot to the shared pass, and step the 0x224 cursor
   when the pass reports one of the 0x8F bits. */
s32 AimAtPathCursorAndAdvance_pal(char *moby_arg)
{
    char *moby = moby_arg;
    char *vars = *(char **)(moby + 0x68);
    char *zone_table = g_path_zone_table;
    s32 zone = *(s32 *)(zone_table + *(s32 *)(vars + 0x110) * 4);
    s32 point_offset = *(s32 *)(vars + 0x224) << 4;
    char *src = (char *)point_offset;
    char *point;
    int copy[4] __attribute__((aligned(16)));
    f32 delta_x;
    f32 delta_y;
    f32 angle;
    s32 point_index;

    src += zone;
    src += 0x10;
    qcopy_nc(copy, src);
    point = (char *)zone + point_offset;
    delta_x = *(f32 *)(point + 0x10) - *(f32 *)(moby + 0x10);
    delta_y = *(f32 *)(point + 0x14) - *(f32 *)(moby + 0x14);
    angle = mat_fast_helper_a(delta_x, delta_y);
    if ((moby_step_controller_pal(moby, (char *)zone + ((*(s32 *)(vars + 0x224) << 4) + 0x10), angle) & 0x8F) != 0) {
        point_index = *(s32 *)(vars + 0x224);
        if (point_index == *(s32 *)(vars + 0x220))
            return 1;
        *(s32 *)(vars + 0x224) = point_index + 1;
    }
    return 0;
}

