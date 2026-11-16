#include "include_asm.h"

#include "common.h"
extern f32 func_00303270(f32, f32);
extern s32 path_check_entry_for_moby(char *, s32);
extern f32 vec_distance_xy(void *, void *);
extern char *g_path_point_tables[];

/* Tells whether this object is done or close enough to its goal point. */
s32 moby_is_near_goal_point_pal(char *moby_arg, s32 path_arg) {
    char *moby = moby_arg;
    s32 path_index = path_arg;
    char *state;
    s32 result;
    f32 distance;

    state = *(char **)(moby + 0x68);
    result = path_check_entry_for_moby(moby, path_index);
    if (result == 0) {
        if (path_index != -1) {
            distance = vec_distance_xy(moby + 0x10,
                               g_path_point_tables[path_index] + ((*(s16 *)(state + 0x1CA) << 4) + 0x10));
            if (!(*(f32 *)(state + 0x134) > distance)) {
            } else {
                result = 1;
            }
        }
    }
    return result;
}


