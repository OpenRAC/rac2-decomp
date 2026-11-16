#include "common.h"
typedef struct { u8 pad[6]; s16 index; u8 tail[2]; } InputEntry;
typedef struct { u8 pad[6]; s16 value; u8 tail[216]; } InputRecord;
extern InputEntry g_selection_menu_rows[];
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_item_slot_to_record[];
extern InputRecord g_weapon_table[];
extern int g_selection_menu_index[];
extern int g_selected_item_material __attribute__((sda));
extern int snd_play_from_global_bank(int, int, int);
/* Handles the pad on a menu with two choices, moves the cursor and lets the player pick one they own. */
void selection_menu_handle_two_entry_input(char *menu, int buttons) {
#define I(off) (*(int *)(menu+(off)))
    int index;
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3,0,0); I(0x48c)++; I(0x490)=1; I(0x498)=0;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3,0,0); I(0x48c)++; I(0x498)=1; I(0x490)=0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3,0,0); if (--I(0x48c)<0) I(0x48c)=1;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3,0,0); if (++I(0x48c)>=2) I(0x48c)=0;
    } else if (buttons & 0x40) {
        index=g_selection_menu_rows[I(0x48c)].index;
        if (index && g_item_owned_flags[index]) { snd_play_from_global_bank(4,0,0); g_selection_menu_index[0]=index; I(0x494)=index; }
        else snd_play_from_global_bank(5,0,0);
    }
    { int selected=g_selection_menu_rows[I(0x48c)].index;
    I(0x494)=selected;
    if (selected && g_item_owned_flags[selected]) g_selected_item_material=((InputRecord *)(g_item_slot_to_record[selected]*224 + (char *)g_weapon_table))->value; }
#undef I
}
