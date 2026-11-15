#include "common.h"

extern void *func_0029EFD0(s32 class_id);
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

void *func_L08_003D3D80(SpawnedObjectPrefix *source)
{
    SpawnedObjectPrefix *object = CreateMoby(0x987);
    if (object != 0) {
        SpawnedObjectPrefix **payload = object->payload;
        object->unk30 = source->unk30;
        object->unk32 = source->unk32;
        object->unk31 = 1;
        object->unk7C = 0x7F;
        object->state = 0;
        *payload = source;
        object->position = source->position;
        func_002A0F48(object);
    }
    return object;
}
