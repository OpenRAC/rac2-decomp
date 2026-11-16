#include "common.h"

extern char g_path_zone_table[];

extern f32 mat_fast_helper_a(f32 a, f32 b);
extern int moby_step_controller(char *a, char *b, f32 c);

/* Aim pass over the slot the 0x110 record names: measure the two position differences,
   turn them into an angle, hand the slot to the shared pass, and step the 0x224 cursor
   when the pass reports one of the 0x8F bits. */
/* Turns the enemy toward its next route point and moves on to the following point once it gets there. Returns 1 at the end of the route. */
s32 AimAtPathCursorAndAdvance(char *obj)
{
    char *moby = obj;
    char *vars = *(char **)(moby + 0x68);
    char *tbl = g_path_zone_table;
    s32 path = *(s32 *)(tbl + *(s32 *)(vars + 0x110) * 4);
    s32 point_offset = *(s32 *)(vars + 0x224) << 4;
    char *source = (char *)point_offset;
    char *point;
    int copy[4] __attribute__((aligned(16)));
    f32 dx;
    f32 dy;
    f32 angle;
    s32 cursor;

    source += path;
    source += 0x10;
    qcopy_nc(copy, source);
    point = (char *)path + point_offset;
    dx = *(f32 *)(point + 0x10) - *(f32 *)(moby + 0x10);
    dy = *(f32 *)(point + 0x14) - *(f32 *)(moby + 0x14);
    angle = mat_fast_helper_a(dx, dy);
    if ((moby_step_controller(moby, (char *)path + ((*(s32 *)(vars + 0x224) << 4) + 0x10), angle) & 0x8F) != 0) {
        cursor = *(s32 *)(vars + 0x224);
        if (cursor == *(s32 *)(vars + 0x220))
            return 1;
        *(s32 *)(vars + 0x224) = cursor + 1;
    }
    return 0;
}
