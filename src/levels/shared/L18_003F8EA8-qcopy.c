#include "common.h"
extern char *g_path_l18_table[];
extern f32 vec_distance_squared_xy(char *, char *);

/* Advances or reverses a waypoint index when the object reaches the current point. */
s32 path_advance_waypoint_index(char *self, char *point, s32 route, s16 *index, s32 reverse, f32 radius) {
    char *path = g_path_l18_table[route];
    qcopy(point, path + 16 + (*index << 4));
    if (reverse) {
        if (vec_distance_squared_xy(self + 16, point) < radius * radius) --*index;
        if (*index < 0) {
            *index = *(u16 *)path - 1;
            return 0;
        }
    } else {
        if (vec_distance_squared_xy(self + 16, point) < radius * radius) ++*index;
        if (*index >= *(s32 *)path) {
            *index = 0;
            return 0;
        }
    }
    return 1;
}
