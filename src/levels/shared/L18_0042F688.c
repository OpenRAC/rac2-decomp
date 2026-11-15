#include "include_asm.h"
#include "common.h"

extern char *D_L18_001FE480[];
extern f32 func_00282E48(void *, void *);

/* Path walker (the func_L14_00423CD0 body without the wrap): copies the current point, steps
   the index once the object is within the radius, and says whether the index is still on the
   path. */
s32 func_L18_0042F688(char *self, char *point, s32 route, s16 *index, s32 reverse, f32 radius) {
    char *path = D_L18_001FE480[route];
    qcopy(point, path + 16 + (*index << 4));
    if (reverse) {
        if (fast_vec_dist(self + 16, point) < radius) --*index;
        if (*index < 0)
            return 0;
    } else {
        if (fast_vec_dist(self + 16, point) < radius) ++*index;
        if (*index >= *(s32 *)path)
            return 0;
    }
    return 1;
}
