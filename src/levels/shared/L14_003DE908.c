#include "include_asm.h"
#include "common.h"

/* Quadword copies, the spelling that reaches lq/sq. */
typedef int TI128 __attribute__((mode(TI)));

extern int func_L00_00324120(char *object);

extern int func_002761F8(void *a, void *b, int mode, void *self, int flag);

extern char D_00189EA0[];

extern int D_L14_001BF958;

extern char *D_L14_001FE1C0[];
extern f32 func_00282E80(char *, char *);


/* func_L14_003F0E68 is built with -G8: see L14_003DE908-g8.c. */

/* Follows a path: when the object is close to the current point it moves to the next (or previous) point, and returns 0 when the path ends. */
s32 func_L14_00423CD0(char *self, char *point, s32 route, s16 *index, s32 reverse, f32 radius) {
    char *path = D_L14_001FE1C0[route];
    qcopy(point, path + 16 + (*index << 4));
    if (reverse) {
        if (vec_distance_xy(self + 16, point) < radius) --*index;
        if (*index < 0) {
            *index = *(u16 *)path - 1;
            return 0;
        }
    } else {
        if (vec_distance_xy(self + 16, point) < radius) ++*index;
        if (*index >= *(s32 *)path) {
            *index = 0;
            return 0;
        }
    }
    return 1;
}


