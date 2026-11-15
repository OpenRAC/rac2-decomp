#include "include_asm.h"
#include "names.h"

/* func_002B50E0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt). Its two returns
   keep the final status load in the block of the calls: with one shared return the block would
   end in the calls, add_branch_dependences would tie the argument moves of func_002B5828 and
   $a3 would be set last. func_002B52A0 is passed the two scratch slots retail really sets. */

extern int D_001B1688 __attribute__((sda));
extern char *func_002B5D28(void *);
extern void func_002B5CD8(void *, void *);
extern void func_002B5BC0(void *, void *, float);
extern void func_00282C88(void *);
extern void func_002B52A0(void *, void *, void *, void *, void *, float);
extern void func_002B5678(void *, void *, void *, void *);
extern void func_002B5828(void *, void *, void *, void *);
extern void func_002B5EF8(void *, void *, float);
extern void func_002B62A0(void);

typedef int PoseVector128 __attribute__((mode(TI)));

/* Runs one movement step for an object that has a movement controller: finds the ground, moves it toward the target, resolves collisions and returns the controller status. */
int func_002B50E0(void *self, void *target, float amount)
{
    char *data = GetMovementController(self);
    PoseVector128 work[3];

    if (data == 0)
        return 8;
    if (gGameTime == *(int *)(data + 0xBC))
        return *(int *)(data + 0x94);
    *(int *)(data + 0x98) = *(int *)(data + 0x94);
    *(int *)(data + 0x94) = 0;
    if (!(*(int *)(data + 0x38) & 0x100))
        CheckGroundObjectTouch(self, data);
    {
        PoseVector128 *src = (PoseVector128 *)((char *)self + 0x10);
        work[0] = *src;
    }
    if (gGameTime - *(int *)(data + 0xBC) >= 2 || *(int *)(data + 0xBC) == 0) {
        FindGroundBelowObject(self, data, 0.0f);
        *(unsigned char *)(data + 0xEA) = 0xFF;
        *(int *)(data + 0x9C) &= ~2;
        *(float *)(data + 0xB4) = 0.0f;
        *(int *)(data + 0x80) = 0;
        ClearVector128(data + 0xA0);
    }
    *(int *)(data + 0xBC) = gGameTime;
    UpdateControllerVelocity(self, data, target, &work[1], &work[2], amount);
    ApplyVelocityAndResolveCollisions(self, data, &work[0], &work[2]);
    UpdateGroundContactState_002B5828(self, data, target, &work[0]);
    UpdateFootTiltAngles(self, data, amount);
    AccumulateTimerTicks();
    return *(int *)(data + 0x94);
}
