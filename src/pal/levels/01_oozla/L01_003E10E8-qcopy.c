#include "include_asm.h"

#include "common.h"
extern void muckdweller_mark_nearby_objects(u8 *, void *, void *);
extern void enemy_update_wander_heading_pal(void *, void *, void *);
extern void moby_follow_attached_pal(u8 *, void *);
extern void muckdweller_clear_marked_objects(void *, void *);

/* func_L01_003DCDD8 around the other move step (func_PAL_L01_0031A4D0, with the state's
   block at +0x1C0). */
void moby_move_keeping_transform_alt_pal(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));

    if (state[0x3E4])
        muckdweller_mark_nearby_objects(object, matrix, extra);
    qcopy(position, object + 0x10);
    enemy_update_wander_heading_pal(object, arg, state + 0x1C0);
    moby_follow_attached_pal(object, position);
    if (state[0x3E4])
        muckdweller_clear_marked_objects(matrix, extra);
}

extern s32 moby_l01_turn_toward_target_pal(u8 *, void *);

/* Runs the shared move step (func_PAL_L01_00323068) with the object's position saved before
   it; when the state's flag at +0x3E4 is set, the transform is saved before and restored
   after. */
s32 moby_move_keeping_transform_pal(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    s32 r;

    if (state[0x3E4])
        muckdweller_mark_nearby_objects(object, matrix, extra);
    qcopy(position, object + 0x10);
    r = moby_l01_turn_toward_target_pal(object, arg);
    moby_follow_attached_pal(object, position);
    if (state[0x3E4])
        muckdweller_clear_marked_objects(matrix, extra);
    return r;
}
