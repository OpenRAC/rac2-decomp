#include "common.h"
typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x48c]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[216]; } MaterialRecord;
typedef struct { char pad[0x44]; int selected; } EquipmentState;

extern void snd_play_from_global_bank(int, int, int);
extern unsigned char g_item_owned_flags[] __attribute__((section(".sdata")));
extern unsigned char g_item_slot_to_record[];
extern MaterialRecord g_weapon_table[];
extern int g_selected_item_material __attribute__((sda));
extern SelectionEntry D_001AA898[];
extern EquipmentState g_pause_menu_state;

#define MATERIAL(id) ((MaterialRecord *)(D_00139568[id]*224 + (char *)D_00239BA0))->material

/* Handles the pad for the column selection screen and lets the player pick an item they own. */
void HandleColumnSelectionInput(SelectionOwner *owner, int buttons)
{
    int id, column;

    if (buttons & 0x1000) {
        int next;

        snd_play_from_global_bank(3, 0, 0);
        column = owner->column;
        next = column - 1;
        owner->row = 0;
        owner->state = 3;
        if (next < 0)
            next = 0;
        owner->column = next;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        owner->row = 0;
        owner->state = 0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        column = owner->column;
        column--;
        owner->column = column;
        if (column < 0)
            owner->column = 2;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        column = owner->column;
        column++;
        owner->column = column;
        if (column >= 3)
            owner->column = 0;
    } else if (buttons & 0x40) {
        id = D_001AA898[owner->column].v[3];
        if (id != 0 && g_item_owned_flags[id] != 0) {
            snd_play_from_global_bank(4, 0, 0);
            g_selected_item_material = MATERIAL(owner->selected);
            if (g_pause_menu_state.selected == id)
                g_pause_menu_state.selected = 0;
            else
                g_pause_menu_state.selected = id;
        } else {
            snd_play_from_global_bank(5, 0, 0);
        }
    }
    {
        int selected = D_001AA898[owner->column].v[3];
        owner->selected = selected;
        if (selected != 0 && g_item_owned_flags[selected] != 0)
            g_selected_item_material = MATERIAL(selected);
    }
}
