#include "include_asm.h"
#include "common.h"

extern void func_L01_003DC8B8(u8 *, void *, void *);
extern s32 func_L01_00321178(u8 *, void *);
extern void func_L01_003DC9E0(u8 *, void *);
extern void func_L01_003DC9A8(void *, void *);

/* Runs the shared move step (func_L01_00321178) with the object's position saved before
   it; when the state's flag at +0x3E4 is set, the transform is saved before and restored
   after. */
s32 func_L01_003DCDD8(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    s32 r;

    if (state[0x3E4])
        MarkNearbyObjectsOfKind(object, matrix, extra);
    qcopy(position, object + 0x10);
    r = TurnMobyTowardTarget(object, arg);
    FollowAttachedObject(object, position);
    if (state[0x3E4])
        ClearMarkedObjects(matrix, extra);
    return r;
}
