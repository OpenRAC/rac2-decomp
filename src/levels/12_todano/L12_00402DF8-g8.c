#include "common.h"

extern void func_002AEE70(u8 *, u8 *, u8 *, float, float, float);
extern void func_0029F338(void *);
extern void func_L12_00402B48(void *);
extern float func_00282E80(void *, void *);
extern void func_002B0A18(int, int);
extern void func_00288308(int);
extern void func_L00_003294F0(void *, int);
extern void func_002AD860(int);
extern float D_L12_001B12B0 __attribute__((sda));
extern float D_L12_001B12B4 __attribute__((sda));
extern float D_L12_001B12B8 __attribute__((sda));
extern float D_L12_001B12BC __attribute__((sda));
extern float D_L12_001B12C0 __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern u8 D_L12_001B3C1C[] MACRO_ADDR;
extern u8 D_L12_001B3C20[] MACRO_ADDR;
extern u8 D_0019B4A8[];
extern u8 D_00189EA0[];
extern u8 *D_L12_001B2E9C MACRO_ADDR;

typedef struct {
    u8 pad[0x464];
    u8 flags[0];
} TodanoObjectFlags;

extern TodanoObjectFlags D_L12_0021EDF0;

/* Each object has a three-bit counter in one half of a packed byte. */
#define OBJECT_COUNTERS(o) \
    ((u8 *)D_0019B4A8)[((s16)*(u16 *)((o) + 0xB2) >> 1) + (D_001A79F0 << 10)]
#define INCREMENT_OBJECT_COUNTER(o) { \
    if (*(u16 *)((o) + 0xB2) & 1) { \
        if (((OBJECT_COUNTERS(o) >> 4) & 7) != 7) OBJECT_COUNTERS(o) += 16; \
    } else { \
        if ((OBJECT_COUNTERS(o) & 7) != 7) OBJECT_COUNTERS(o)++; \
    } \
}

typedef struct {
    u8 pad[0xF0];
    f32 rx, ry, rz;
} TodanoRotation;

/* Sets the object's rotation and bob from the level's tuning floats. An object whose packed
   counter is already set is removed; otherwise, once within 1.5 units of the target position,
   it plays its sound, bumps the counter and is removed. */
void func_L12_00402DF8(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 flagIndex;
    s32 counterBits;
    TodanoObjectFlags *flagTable;

    if (object[0x20]) return;
    ((TodanoRotation *)object)->rx = D_L12_001B12B8 * 0.0174532942f;
    ((TodanoRotation *)object)->ry = D_L12_001B12BC * 0.0174532942f;
    ((TodanoRotation *)object)->rz = D_L12_001B12C0 * 0.0174532942f;
    UpdateWrappedAngleOffset(object, D_L12_001B3C1C, D_L12_001B3C20, D_L12_001B12B0, D_L12_001B12B4 * 0.00029088825f, 0.0f);
    flagIndex = *(u16 *)(object + 0xB2);
    flagTable = &D_L12_0021EDF0;
    if (flagTable->flags[(s16)flagIndex]) goto kill;
    counterBits = (u8)D_0019B4A8[((s16)flagIndex >> 1) + (gCurrentMapIndex << 10)];
    if (flagIndex & 1) {
        if ((counterBits >> 4) & 7) goto kill;
    } else if (counterBits & 7) {
        goto kill;
    }
    goto update;

kill:
    MarkMobySpawned(object);
    return;

update:
    DrawSparkleTrailToHero(object);
    if (vec_distance_xy(object + 0x10, gHeroPosition) < 1.5f) {
        SetEntryValueByIndex(0x1246, 0x1F4);
        UnlockHelpEntry(0x10);
        SetObjectFlagBit(D_L12_001B2E9C + (*(s32 *)state << 8), 1);
        HandleRequestSlotState(0x10);
        INCREMENT_OBJECT_COUNTER(object);
        MarkMobySpawned(object);
    }
}
