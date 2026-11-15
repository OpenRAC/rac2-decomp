#include "common.h"
extern char *D_L18_001FE480[];
extern f32 func_L02_002F21C0(char *, char *);

/* Advances or reverses a waypoint index when the object reaches the current point. */
s32 func_L18_003F8EA8(char *self, char *point, s32 route, s16 *index, s32 reverse, f32 radius) {
    char *path = D_L18_001FE480[route];
    qcopy(point, path + 16 + (*index << 4));
    if (reverse) {
        if (DistanceSquaredXY(self + 16, point) < radius * radius) --*index;
        if (*index < 0) {
            *index = *(u16 *)path - 1;
            return 0;
        }
    } else {
        if (DistanceSquaredXY(self + 16, point) < radius * radius) ++*index;
        if (*index >= *(s32 *)path) {
            *index = 0;
            return 0;
        }
    }
    return 1;
}
