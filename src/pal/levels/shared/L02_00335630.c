#include "include_asm.h"
#include "names.h"

extern void FastVecSub(float *out, const float *a, const float *b);
extern int coll_update_controller(char *moby, char *target, void *arg2);

/* Updates the collision controller with the vector from the moby to the target. */
void moby_aim_at_target_offset_pal(char *moby, char *target) {
    int offset[4];

    FastVecSub((float *)offset, (const float *)target, (const float *)(moby + 0x10));
    coll_update_controller(moby, target, offset);
}

