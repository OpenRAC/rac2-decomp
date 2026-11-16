#include "include_asm.h"

#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern int coll_update_controller_pal(char *, char *, void *);

int coll_check_move_to_point_pal(char *object, void *point)
{
    char *target = object + 0x10;
    float diff[4];

    FastVecSub(diff, point, target);
    return coll_update_controller_pal(object, target, diff);
}

