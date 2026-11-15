#include "include_asm.h"
#include "common.h"

extern void muckdweller_mark_nearby_objects(u8 *, void *, void *);
extern void enemy_update_wander_heading(void *, void *, void *);
extern void moby_follow_attached(u8 *, void *);
extern void muckdweller_clear_marked_objects(void *, void *);

/* func_L01_003DCDD8 around the other move step (func_L01_00318638, with the state's
   block at +0x1C0). */
void moby_move_keeping_transform_alt(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));

    if (state[0x3E4])
        muckdweller_mark_nearby_objects(object, matrix, extra);
    qcopy(position, object + 0x10);
    enemy_update_wander_heading(object, arg, state + 0x1C0);
    moby_follow_attached(object, position);
    if (state[0x3E4])
        muckdweller_clear_marked_objects(matrix, extra);
}
