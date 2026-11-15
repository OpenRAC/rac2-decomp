#include "common.h"
typedef int CtorVector __attribute__((mode(TI)));
/* Accessed base-object fields, not the complete allocation extent. */
typedef struct {
    u8 unknown00[0x10];
    CtorVector position;
    u8 mode;
    u8 unknown21[0xF];
    u8 intensity, enabled;
    u16 colour;
    u8 unknown34[4];
    u64 ownerIdentity;
    u8 unknown40[0xB0];
    float rotationX, rotationY, rotationZ;
} CtorObject;
extern void *func_0029EFD0(int);
extern float func_002A7878(float, float);
extern void func_002A0F48(void *);

/* Install the full position and owner identity before activating the new object. */
/* Creates a copy of the breakable object at the given position, using the colour and owner of the original. */
CtorObject *func_L01_003BC490(CtorObject *owner, const CtorVector *position)
{
    CtorObject *object = CreateMoby(0xA26 /* moby class 2598 */);
    if (object != 0) {
        object->intensity = owner->intensity;
        object->colour = owner->colour;
        object->enabled = 1;
        object->mode = 1;
        object->position = *position;
        object->rotationX = owner->rotationX;
        object->rotationY = owner->rotationY;
        object->rotationZ = RandomFloatRange(-3.1415927f, 3.1415927f);
        object->ownerIdentity = owner->ownerIdentity;
        func_002A0F48(object);
    }
    return object;
}
