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

void HandleColumnSelectionInput_us2(SelectionOwner *o, int buttons)
{
    int id, column;

    if (buttons & 0x1000) {
        int next;

        snd_play_from_global_bank(3, 0, 0);
        column = o->column;
        next = column - 1;
        o->row = 0;
        o->state = 3;
        if (next < 0)
            next = 0;
        o->column = next;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        o->row = 0;
        o->state = 0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        column = o->column;
        column--;
        o->column = column;
        if (column < 0)
            o->column = 2;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        column = o->column;
        column++;
        o->column = column;
        if (column >= 3)
            o->column = 0;
    } else if (buttons & 0x40) {
        id = g_item_grid_second_mode_rows[o->column].v[3];
        if (id != 0 && g_item_owned_flags[id] != 0) {
            snd_play_from_global_bank(4, 0, 0);
            g_selected_item_material = MATERIAL(o->selected);
            if (g_pause_menu_state.selected == id)
                g_pause_menu_state.selected = 0;
            else
                g_pause_menu_state.selected = id;
        } else {
            snd_play_from_global_bank(5, 0, 0);
        }
    }
    {
        int selected = g_item_grid_second_mode_rows[o->column].v[3];
        o->selected = selected;
        if (selected != 0 && g_item_owned_flags[selected] != 0)
            g_selected_item_material = MATERIAL(selected);
    }
}
