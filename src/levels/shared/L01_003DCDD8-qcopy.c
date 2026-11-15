#include "include_asm.h"
#include "common.h"

extern void muckdweller_mark_nearby_objects(u8 *, void *, void *);
extern s32 moby_l01_turn_toward_target(u8 *, void *);
extern void moby_follow_attached(u8 *, void *);
extern void muckdweller_clear_marked_objects(void *, void *);

/* Runs the shared move step (func_L01_00321178) with the object's position saved before
   it; when the state's flag at +0x3E4 is set, the transform is saved before and restored
   after. */
s32 moby_move_keeping_transform(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    s32 r;

    if (state[0x3E4])
        muckdweller_mark_nearby_objects(object, matrix, extra);
    qcopy(position, object + 0x10);
    r = moby_l01_turn_toward_target(object, arg);
    moby_follow_attached(object, position);
    if (state[0x3E4])
        muckdweller_clear_marked_objects(matrix, extra);
    return r;
}
