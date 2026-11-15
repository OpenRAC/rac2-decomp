#include "common.h"

extern void *CreateMoby(s32 class_id);
extern void func_002A0F48(void *object);

/* Partial object view; only the constructor's measured fields are described. */
typedef int ObjVec __attribute__((mode(TI)));

typedef struct SpawnedObjectPrefix {
    u8 reserved00[0x10];
    ObjVec position;
    u8 state;
    u8 reserved21[15];
    u8 unk30, unk31;
    u16 unk32;
    u8 reserved34[0x34];
    struct SpawnedObjectPrefix **payload;
    u8 reserved6C[0x10];
    u16 unk7C;
} SpawnedObjectPrefix;

/* Creates a new object of class 2439 at the parent's position and links it back to the parent. */
void *puff_spawn_linked_child(SpawnedObjectPrefix *parent)
{
    SpawnedObjectPrefix *child = CreateMoby(0x987 /* moby class 2439 */);
    if (child != 0) {
        SpawnedObjectPrefix **childVars = child->payload;
        child->unk30 = parent->unk30;
        child->unk32 = parent->unk32;
        child->unk31 = 1;
        child->unk7C = 0x7F;
        child->state = 0;
        *childVars = parent;
        child->position = parent->position;
        func_002A0F48(child);
    }
    return child;
}
