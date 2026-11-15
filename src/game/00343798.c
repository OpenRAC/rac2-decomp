#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_F32_F7036EF03
#define RAC2_T_F32_F7036EF03
typedef float f32_F7036ef03;
#endif

extern f32_F7036ef03 D_L04_001AE4A8 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4B0 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4B8 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4C0 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4C8 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4AC;

extern f32_F7036ef03 D_L04_001AE4B4;

extern f32_F7036ef03 D_L04_001AE4BC;

extern f32_F7036ef03 D_L04_001AE4C4;

extern f32_F7036ef03 D_L04_001AE4CC;

extern void func_00335E38_2(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);

extern void func_L00_00438970(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2);

extern void func_00343638(void *a0);

extern void func_003435C8(void *a0);

extern int func_00342978(void *a0, int a1);

/* Moves every part of the item menu to its place, refreshes the labels and updates the list. */
void func_00343798(char *self, int buttons)
{
    f32_F7036ef03 *position;
    char *list = self + 664;

    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self, D_L04_001AE4A8 + position[0], D_L04_001AE4AC + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self + 76, D_L04_001AE4B0 + position[0], D_L04_001AE4B4 + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self + 152, D_L04_001AE4B8 + position[0], D_L04_001AE4BC + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self + 576, D_L04_001AE4C0 + position[0], D_L04_001AE4C4 + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    StoreTwoFloats(list, D_L04_001AE4C8 + position[0], D_L04_001AE4CC + position[1]);
    UpdateMenuTitleText(self);
    UpdateMenuEmptyLabel(self);
    *(int *)(self + 416) = UpdateListSelection(list, buttons);
}


extern void func_00336320(void *a0);
extern void func_00336A78(void *a0);
extern void func_00342BE8(void *a0);
extern int func_00342BC0(void *a0);
extern int func_00288FB8(int);
extern void func_00336A38(void *a0, int a1);
extern unsigned char D_00139568[];
extern char D_00239BA0[];

/* Draws the item menu: its frame, list, and the description of the selected item. */
void func_003438E8(char *self)
{
    int itemId;
    char *itemRecord;

    if (*(int *)(self + 0x290) != 0) {
        DrawScreenElementAtStoredPosition(self);
        DrawScreenElementAtStoredPosition(self + 0x4C);
        DrawScreenElementAtStoredPosition(self + 0x98);
        DrawAlignedTextLabel(self + 0x1B0);
        DrawMenuListEntries(self + 0x298);
        itemId = GetSelectedMenuListId(self + 0x298);
        itemRecord = gWeaponTable_00239BA0 + gItemSlotToRecord[itemId] * 224;
        SetWidgetField40(self + 0x1F8, GetLocalizedString(*(int *)(itemRecord + 8)));
        DrawAlignedTextLabel(self + 0x1F8);
        DrawAlignedTextLabel(self + 0x240);
    }
}
