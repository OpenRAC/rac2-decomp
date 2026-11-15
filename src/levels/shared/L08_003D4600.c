#include "common.h"
typedef int SpawnVector __attribute__((mode(TI)));
typedef struct SpawnObject SpawnObject;
typedef struct { u8 unknown00[0x24]; float scale; } BlueprintPrefix;
typedef struct { SpawnObject *owner; } AttachedState;
/* Partial object view; all gaps and offsets are measured accesses, not a
 * complete allocation-size claim. */
struct SpawnObject {
    u8 unknown00[0x10];
    SpawnVector position;
    u8 mode;
    u8 unknown21[3];
    BlueprintPrefix *blueprint;
    u8 unknown28[4];
    float scale;
    u8 intensity;
    u8 enabled;
    u16 colour;
    u16 flags;
    u8 unknown36[0x32];
    AttachedState *state;
    u8 unknown6C[0x84];
    SpawnVector orientation;
};
extern SpawnObject *func_0029EFD0(s32);
extern void func_002A0F48(void *);

/* Inherits colour and orientation, while installing a separate position. */
/* Creates a new effect object owned by another object, at a given position. */
SpawnObject *func_L08_003D4600(SpawnObject *owner, SpawnVector *position)
{
    SpawnObject *object = CreateMoby(0x9A1 /* moby class 2465 */);
    if (object != 0) {
        SpawnVector *destination = &object->position;
        object->intensity = owner->intensity;
        object->colour = owner->colour;
        object->enabled = 1;
        object->mode = 0;
        object->state->owner = owner;
        qcopy(destination, position);
        qcopy(&object->orientation, &owner->orientation);
        func_002A0F48(object);
    }
    return object;
}
