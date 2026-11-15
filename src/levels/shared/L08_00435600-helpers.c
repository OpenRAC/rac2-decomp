#include "common.h"
typedef int SpawnVector __attribute__((mode(TI)));
typedef struct SpawnObject SpawnObject;
typedef struct { u8 unknown00[0x24]; float scale; } BlueprintPrefix;
typedef struct { SpawnVector position; u8 *owner; int timer; } AttachedState;
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
extern SpawnObject *CreateMoby(s32);
extern void func_002A0F48(void *);

extern float D_L08_001B1F94 __attribute__((sda));
/* Creates the effect object for the owner and starts it at the given position. */
/* Installs the same aligned input vector in the owner and its attached state. */
SpawnObject *part_spawn_attached_effect(u8 *owner, SpawnVector *position)
{
    SpawnObject *object = CreateMoby(0x998 /* moby class 2456 */);
    if (object != 0) {
        AttachedState *state;
        object->enabled = 1;
        object->intensity = 255;
        object->colour = 255;
        object->mode = 0;
        object->scale = object->blueprint->scale * D_L08_001B1F94;
        state = object->state;
        state->owner = owner;
        qcopy(&state->position, position);
        qcopy(&object->position, position);
        state->timer = 0;
        func_002A0F48(object);
    }
    return object;
}
