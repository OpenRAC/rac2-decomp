#include "common.h"
typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x48c]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[216]; } MaterialRecord;
typedef struct { char pad[0x44]; int selected; } EquipmentState;

extern void func_002E5E58(int, int, int);
extern unsigned char D_001A7AF8[] __attribute__((section(".sdata")));
extern unsigned char D_00139568[];
extern MaterialRecord D_00239BA0[];
extern int D_001ADB10 __attribute__((sda));
extern SelectionEntry D_001AA898[];
extern EquipmentState D_001F2840;

#define MATERIAL(id) ((MaterialRecord *)(D_00139568[id]*224 + (char *)D_00239BA0))->material

/* Handles the pad for the column selection screen and lets the player pick an item they own. */
void func_00345D58(SelectionOwner *owner, int buttons)
{
    int id, column;

    if (buttons & 0x1000) {
        int next;

        PlaySoundFromGlobalBank(3, 0, 0);
        column = owner->column;
        next = column - 1;
        owner->row = 0;
        owner->state = 3;
        if (next < 0)
            next = 0;
        owner->column = next;
    } else if (buttons & 0x4000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        owner->row = 0;
        owner->state = 0;
    } else if (buttons & 0x8000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        column = owner->column;
        column--;
        owner->column = column;
        if (column < 0)
            owner->column = 2;
    } else if (buttons & 0x2000) {
        PlaySoundFromGlobalBank(3, 0, 0);
        column = owner->column;
        column++;
        owner->column = column;
        if (column >= 3)
            owner->column = 0;
    } else if (buttons & 0x40) {
        id = D_001AA898[owner->column].v[3];
        if (id != 0 && gItemOwnedFlags[id] != 0) {
            PlaySoundFromGlobalBank(4, 0, 0);
            gSelectedItemMaterial = MATERIAL(owner->selected);
            if (gPauseMenuState.selected == id)
                gPauseMenuState.selected = 0;
            else
                gPauseMenuState.selected = id;
        } else {
            PlaySoundFromGlobalBank(5, 0, 0);
        }
    }
    {
        int selected = D_001AA898[owner->column].v[3];
        owner->selected = selected;
        if (selected != 0 && gItemOwnedFlags[selected] != 0)
            gSelectedItemMaterial = MATERIAL(selected);
    }
}
