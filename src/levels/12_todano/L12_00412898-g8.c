#include "common.h"

extern s32 func_002B38B8(void);
extern void func_002E59F8(s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void func_0029F338(void *);
extern void func_002A0488(void *, s32, s32, s32);
extern void func_L12_00412548(void *, void *);
extern s32 func_00283CF0(f32);
extern void func_00291450(s32);
extern void func_L00_00310838(void *, s32, s32);

extern char D_0019B4A8[];
extern u8 D_00188660[];
extern u8 D_001395DA[];

typedef struct {
    u8 pad[0x464];
    u8 flags[0];
} TodanoObjectFlags;

extern TodanoObjectFlags D_L12_0021EDF0;
extern s32 D_001A79F0 MACRO_ADDR;
extern u8 *D_L12_001B2E9C __attribute__((sda));
extern f32 D_L12_001B17C0 __attribute__((sda));
extern s32 D_L12_001B17E0 __attribute__((sda));
extern s32 D_L12_001B29C8 MACRO_ADDR;

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

/* Shows a looping effect until the object it is linked to has been used up, then fades itself
   out and removes itself. */
void func_L12_00412898(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    s32 delta;
    u16 index;
    s32 bits;
    TodanoObjectFlags *record;

    if (IsThirdPendingFlagSet()) goto kill;
    index = *(u16 *)(object + 0xB2);
    record = &D_L12_0021EDF0;
    if (record->flags[(s16)index]) goto kill;
    bits = (u8)D_0019B4A8[((s16)index >> 1) + (gCurrentMapIndex << 10)];
    if (index & 1) {
        if ((bits >> 4) & 7) goto kill;
    } else if (bits & 7) {
        goto kill;
    }
    goto dispatch;

kill: {
        s32 id;
        u8 *effect;

        D_001395DA[0] = 1;
        INCREMENT_OBJECT_COUNTER(object);
        id = *(s32 *)(state + 0x10);
        if (id != -1) {
            effect = gSoundState + id * 0x70;
            if (*(u8 **)(effect + 0x88) == object && effect[0x74])
                StopSoundVoice(id);
        }
        *(s32 *)(state + 0x10) = -1;
        MarkMobySpawned(object);
        return;
    }

dispatch:
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        object[0x23] = 20;
        *(u16 *)(object + 0x34) |= 0xA08;
        *(s16 *)(state + 0xE) = -1;
        *(f32 *)(state + 4) = 1.0f;
        set_moby_color(object, 0x80, 0x80, 0x80);
        break;
    case 1: {
        u8 *effect;
        u16 index;
        s32 bits;

        effect = gSoundState + *(s32 *)(state + 0x10) * 0x70;
        if (*(u8 **)(effect + 0x88) != object || !effect[0x74])
            *(s32 *)(state + 0x10) = PlayMobySound(0, 4, object);
        {
            s32 id = *(s32 *)state;
            u8 *linked;

            if (id != -1) {
                linked = D_L12_001B2E9C + (id << 8);
                if (!linked || linked[0x20] == 0xFE || linked[0x20] == 0xFD)
                    goto activate;
                index = *(u16 *)(linked + 0xB2);
                bits = (u8)D_0019B4A8[((s16)index >> 1) + (gCurrentMapIndex << 10)];
                if (index & 1) {
                    if ((bits >> 4) & 7) goto activate;
                    else goto update;
                } else if (!(bits & 7)) {
                    goto update;
                }
activate: {
                    *(f32 *)(state + 4) = 1.0f;
                    object[0x20] = 2;
                    INCREMENT_OBJECT_COUNTER(object);
                }
            }
        }
update:
        PushObjectsOutOfRectangle(object, state);
        break;
    }
    case 2:
        *(f32 *)(state + 4) -= D_L12_001B17C0;
        if (*(f32 *)(state + 4) < 0.0f)
            object[0x20] = 3;
        else
            object[0x23] = FloatToInt(*(f32 *)(state + 4) * 20.0f);
        break;
    case 3: {
        s32 id;
        u8 *effect;

        id = *(s32 *)(state + 0x10);
        if (id != -1) {
            effect = gSoundState + id * 0x70;
            if (*(u8 **)(effect + 0x88) == object && effect[0x74])
                StopSoundVoice(id);
        }
        *(s32 *)(state + 0x10) = -1;
        if (*(s16 *)(state + 0xE) != -1) {
            FreePointLight(*(s16 *)(state + 0xE));
            *(s16 *)(state + 0xE) = -1;
        }
        MarkMobySpawned(object);
        return;
    }
    }
    delta = 0xC0;
    *(s16 *)(state + 0xC) += 0xC0;
    if (*(s16 *)(state + 0xC) > 0x1000) {
        *(s16 *)(state + 0xC) -= 0x1000;
        delta = -0xF40;
    } else if (*(s16 *)(state + 0xC) < 0) {
        *(s16 *)(state + 0xC) += 0x1000;
        delta = 0x10C0;
    }
    if (!(D_L12_001B29C8 << D_L12_001B17E0))
        offset_moby_class_point_pairs(*(void **)(object + 0x24), delta, 0);
}
