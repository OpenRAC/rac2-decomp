#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner {
    unsigned char prefix_00[0x120]; void *slots_120[10]; int count_148; int active_14c;
} Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner;
extern void func_L00_002AF7D0(void);
extern void func_L00_002B1F90(void);
extern void func_L00_00322EC8(Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L18_002D0850(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(void *);
extern s32 func_L18_002E0070(s32, s32);
extern void func_L00_002D2168(s32, s32, float);
extern u8 D_00189E20[];
/* Puts the hero under control of another object (for example a vehicle) and saves the hero position. */
void func_L18_002CFD68(s32 mode, s32 index, u8 *object)
{
    u8 *base = gHeroState;
    u8 *current;
    cancel_hero_item_animation();
    base[0x22B6] = 1;
    UpdateHeroSlotCallbacks();
    *(u8 **)(base + 0x2290) = *(u8 **)(base + 0xC18);
    ReleaseSlotList((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)(base + 0x18E0));
    ReleaseSlotList((Rac2Native_5b4b17178a13f443_SmallSlotReset128Owner *)(base + 0x1A30));
    *(s32 *)(*(u8 **)(base + 0x2290) + 0x9C) = -1;
    if (mode != 4 || base[0x22B4] != 4) SetHeroObjectsFlagBit();
    ClearTrackedSlots();
    ResetAllAttachmentRecords();
    gHeroState[0x22B4] = mode;
    *(u8 **)(gHeroState + 0xC14) = object;
    *(u8 **)(gHeroState + 0x2290) = object;
    UpdateHeroSpeedTargets_L18();
    *(float *)(gHeroState + 0x250) = *(float *)(gHeroState + 0x258);
    *(float *)(gHeroState + 0x254) = *(float *)(gHeroState + 0x25C);
    current = *(u8 **)(gHeroState + 0x2290);
    *(u16 *)(current + 0x34) |= 6;
    *(float *)(gHeroState + 0xC20) = 1.0f;
    *(float *)(gHeroState + 0xC24) = 1.0f;
    ClearHeroQueuedAnimation();
    func_002A677C(*(u8 **)(gHeroState + 0x2290));
    *(s16 *)(gHeroState + 0x24F2) = index;
    if (mode == 4) {
        *(VectorBits *)(gHeroState + 0x80) = *(VectorBits *)(object + 0x10);
        *(VectorBits *)(gHeroState + 0x90) = *(VectorBits *)(object + 0xF0);
        *(s16 *)(gHeroState + 0x24D4) = *(u16 *)(gHeroState + 0x24CC);
        *(s32 *)(gHeroState + 0x24CC) = 3;
    }
    SetHeroAction_L18(index, 2);
    if (mode == 4) set_hero_animation(15, 0, 5.0f);
}

extern u8 D_00189E20[];
extern u8 D_L18_001B4E00[], D_L18_001B5400[];
extern s32 D_L18_001A8F00[] __attribute__((sda));
extern s32 func_002AB1F0(u8 *);
extern void func_0029B758(s32, s32);
extern void func_L00_002B2BD0(void);
extern void func_L00_002A53B8(void);
extern void func_0028BDB0(u8 *);
extern void func_0028BE00(u8 *);
extern void func_0028C6D0(u8 *);
extern s32 func_0028B3D0(s32, s32, void (*)(u8 *), void (*)(u8 *), void (*)(u8 *), s32, s32);
extern s32 func_L00_002F6B90(u32);
extern void func_L00_002A6708(void);
extern void func_L00_002D24B8(void);
extern s32 func_L00_002A4DB0(char *, s32, s32, s32);
extern void func_L00_002D9D98(void);
/* Gives control back to the hero and restores the saved position and camera state. */
void func_L18_002CFF48(s32 keep)
{
    u8 *base = gHeroState;
    u8 *object;
    float *record;
    s32 value;
    s32 mode;
    u8 *attached;
    u8 *restored;
    u8 *current;
    if (base[0x22B4] == 4) {
        record = (float *)GetMobyPrivateValue0(*(u8 **)(base + 0x2290));
        if (record) *record = (float)*(s32 *)(base + 0x24CC);
        object = *(u8 **)(base + 0xC18);
        qcopy((base + 0x80), (object + 0x10));
        qcopy((base + 0x90), (object + 0xF0));
        *(s32 *)(base + 0x24CC) = *(s16 *)(base + 0x24D4);
        if (!keep) StoreLevelObjectValuePair(0, 0);
        ResetHeroSpeedsAndVectors();
        *(s16 *)(base + 0x34E) = 1;
        *(s32 *)(base + 0x3A4) &= ~1;
        *(s32 *)(base + 0x3A4) &= ~2;
        *(s32 *)(base + 0x3A0) = 0;
        base[0x22B5] = 0;
    }
    ResetAllAttachmentRecords();
    gHeroState[0x22B4] = 0;
    SetHudSlotContents(35, 0, InitMenuPanelLayout, UpdateRadialWeaponSelect, DrawWeaponWheel, 0, 0);
    RunSlotCallback(3);
    attached = *(u8 **)(gHeroState + 0xC14);
    if (attached) *(u16 *)(attached + 0x34) &= ~6;
    *(u8 **)(gHeroState + 0xC14) = 0;
    ClearTrackedSlots();
    restored = *(u8 **)(gHeroState + 0xC18);
    *(u8 **)(gHeroState + 0x2290) = restored;
    qcopy((restored + 0x10), (gHeroState + 0x80));
    *(s32 *)(restored + 0x9C) = 0;
    *(float *)(gHeroState + 0xC24) = 1.0f;
    ClearHeroQueuedAnimation();
    current = *(u8 **)(gHeroState + 0x2290);
    if (current[0x42] != 255) {
        value = CopyAnimationEntryData((char *)current, current[0x42], current[0x40], (s32)D_L18_001B4E00);
        *(s32 *)(*(u8 **)(gHeroState + 0x2290) + 0x58) = value;
    }
    current = *(u8 **)(gHeroState + 0x2290);
    value = CopyAnimationEntryData((char *)current, current[0x43], current[0x41], (s32)D_L18_001B5400);
    *(s32 *)(*(u8 **)(gHeroState + 0x2290) + 0x5C) = value;
    if (*(s32 *)(gHeroState + 0x2294) != 0x61) goto reset;
    switch (D_L18_001A8F00[0]) {
    case 2:
    case 6:
        goto done;
    }
reset:
    SetHeroAction_L18(0, 1);
done:
    if (gHeroState[0x22B4] == 4) ResetDefaultCamera();
}
