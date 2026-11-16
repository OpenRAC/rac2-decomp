#include "include_asm.h"

#include "common.h"
extern void cam_compute_view_direction(char *moby, void *a1, int a2);
extern void FastVecScale(void *moby, void *a1, float f12);
extern void lightning_arcs_update_owned_pal(char *moby);
extern char ref_L00_004117B8_00[];

/* func_L00_004115E8 is defined in L00_004096B0-g8.c. */

/* Walks the thirty records of the level's block and, for every record whose +0x18 pointer is
   set, folds it into a sixteen-byte buffer: the record's own transform, then the scale of its
   +0x0C word, then its first three words added to the buffer. The block's address differs
   from level to level, so it takes a per-level name. */
/* Updates the positions of the 30 tracked targets, then redraws the lightning arcs of this object. */
void tracked_target_offsets_update_pal(char *moby)
{
    char *slot = ref_L00_004117B8_00;
    char *owner = moby;
    char *target;
    float offset[4];
    int i;

    for (i = 0x1D; i >= 0; i--) {
        if (*(char **)(slot + 0x18) != 0) {
            target = *(char **)(slot + 0x18);
            cam_compute_view_direction(target + 0x10, offset, 1);
            target = *(char **)(slot + 0x18);
            FastVecScale(offset, offset, *(float *)(target + 0xC) * 0.0008300250046886504f);
            target = *(char **)(slot + 0x18);
            offset[0] += *(float *)(target + 0) * 0.0009764999849721789f;
            offset[1] += *(float *)(target + 4) * 0.0009764999849721789f;
            offset[2] += *(float *)(target + 8) * 0.0009764999849721789f;
        }
        slot = slot + 0x30;
    }
    lightning_arcs_update_owned_pal(owner);
}

