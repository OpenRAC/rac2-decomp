#include "include_asm.h"
#include "names.h"

typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x4FC]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[0xD8]; } SelectionMaterial;
extern int snd_play_from_global_bank(int, int, void *);
extern unsigned char g_item_owned_flags[] __attribute__((section(".sdata")));
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_table[];
extern int g_selection_grid_cursor[];
extern int g_selected_item_material __attribute__((sda));
extern SelectionEntry g_menu_item_table_second[];

/* Handles the pad in the selection grid: moves the cursor and picks an owned item (USA v2.00 copy). */
void selection_grid_handle_input_us2(SelectionOwner *owner, int buttons)
{
    if (buttons & 0x1000) {
        int row;
        snd_play_from_global_bank(3, 0, 0);
        row = owner->row - 1;
        owner->row = row;
        if (row < 0) {
            owner->row = 0;
            owner->state = 1;
        }
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3, 0, 0);
        if (owner->row == 0) {
            if (owner->column == 0) {
                owner->column = 1;
                owner->row = 1;
            } else
                owner->row = 1;
        } else if (owner->row == 1) {
            owner->state = 3;
            owner->row = 0;
            owner->column--;
        }
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3, 0, 0);
        --owner->column;
        if (owner->row == 0)
            owner->column = owner->column < 0 ? 2 : owner->column;
        else
            owner->column = owner->column < 1 ? 2 : owner->column;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3, 0, 0);
        ++owner->column;
        if (owner->row == 0)
            owner->column = owner->column > 2 ? 0 : owner->column;
        else
            owner->column = owner->column > 2 ? 1 : owner->column;
    } else if (buttons & 0x40) {
        int id = g_menu_item_table_second[owner->column + owner->row * 3].v[3];
        if (id && g_item_owned_flags[id]) {
            snd_play_from_global_bank(4, 0, 0);
            g_selection_grid_cursor[0] = id;
            owner->selected = id;
        } else
            snd_play_from_global_bank(5, 0, 0);
    }
    {
        int id = g_menu_item_table_second[owner->column + owner->row * 3].v[3];
        owner->selected = id;
        if (id && g_item_owned_flags[id])
            g_selected_item_material = ((SelectionMaterial *)(g_weapon_table + g_item_slot_to_record[id] * 0xE0))->material;
    }
}
