#include "include_asm.h"
#include "common.h"

extern void func_L01_003DC8B8(u8 *, void *, void *);
extern void func_L01_00318638(void *, void *, void *);
extern void func_L01_003DC9E0(u8 *, void *);
extern void func_L01_003DC9A8(void *, void *);

/* func_L01_003DCDD8 around the other move step (func_L01_00318638, with the state's
   block at +0x1C0). */
void func_L01_003DCD40(u8 *object, void *arg)
{
    u8 *state = *(u8 **)(object + 0x68);
    float matrix[16] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));

    if (state[0x3E4])
        MarkNearbyObjectsOfKind(object, matrix, extra);
    qcopy(position, object + 0x10);
    UpdateWanderHeading(object, arg, state + 0x1C0);
    FollowAttachedObject(object, position);
    if (state[0x3E4])
        ClearMarkedObjects(matrix, extra);
}
