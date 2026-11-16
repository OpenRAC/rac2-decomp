#include "include_asm.h"
#include "names.h"

extern void FastVecSub(float *out, const float *a, const float *b);
extern int coll_update_controller(char *arg0, char *arg1, void *arg2);

void moby_aim_at_target_offset_pal(char *arg0, char *arg1) {
    int tmp[4];

    FastVecSub((float *)tmp, (const float *)arg1, (const float *)(arg0 + 0x10));
    coll_update_controller(arg0, arg1, tmp);
}

