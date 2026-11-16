#include "common.h"
typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x4fc]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[216]; } MaterialRecord;
typedef struct { char pad[0x44]; int selected; } EquipmentState;

extern int snd_play_from_global_bank(int, int, int);
extern unsigned char g_item_owned_flags[] __attribute__((section(".sdata")));
extern unsigned char g_item_slot_to_record[];
extern MaterialRecord g_weapon_table[];
extern int g_selected_item_material __attribute__((sda));
extern SelectionEntry g_item_grid_second_mode_rows[];
extern EquipmentState g_pause_menu_state;

#define MATERIAL(id) ((MaterialRecord *)(D_00139568[id]*224 + (char *)D_00239BA0))->material

/* Handles pad input on the three-column selection menu: moves the cursor, plays a sound and toggles the chosen item. (PAL) */
void HandleColumnSelectionInput_pal(SelectionOwner *menu, int buttons)
{
    int id, column;

    if (buttons & 0x1000) {
        int next_column;

        snd_play_from_global_bank(3, 0, 0);
        column = menu->column;
        next_column = column - 1;
        menu->row = 0;
        menu->state = 3;
        if (next_column < 0)
            next_column = 0;
        menu->column = next_column;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        menu->row = 0;
        menu->state = 0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        column = menu->column;
        column--;
        menu->column = column;
        if (column < 0)
            menu->column = 2;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        column = menu->column;
        column++;
        menu->column = column;
        if (column >= 3)
            menu->column = 0;
    } else if (buttons & 0x40) {
        id = g_item_grid_second_mode_rows[menu->column].v[3];
        if (id != 0 && g_item_owned_flags[id] != 0) {
            snd_play_from_global_bank(4, 0, 0);
            g_selected_item_material = MATERIAL(menu->selected);
            if (g_pause_menu_state.selected == id)
                g_pause_menu_state.selected = 0;
            else
                g_pause_menu_state.selected = id;
        } else {
            snd_play_from_global_bank(5, 0, 0);
        }
    }
    {
        int selected = g_item_grid_second_mode_rows[menu->column].v[3];
        menu->selected = selected;
        if (selected != 0 && g_item_owned_flags[selected] != 0)
            g_selected_item_material = MATERIAL(selected);
    }
}
