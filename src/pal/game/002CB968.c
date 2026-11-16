#include "include_asm.h"


#include "common.h"
extern char g_pause_menu_state[];
extern short g_sequence_active_flag;
extern int g_selected_map_index;
extern int g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
extern int request_end_slot(int, int);
extern int request_begin_slot(int, int, int, int, void *);
extern s16 snd_pump_music_and_disc_read_pal(int);
extern void LoadClassIntoFreeCacheSlot(int);
typedef struct {
    char pad00[0x1C];
    int mode;
    char pad20[0x04];
    volatile int count;
    char pad28[0x08];
    int field30;
    char pad34[0x0C];
    int field40;
    char pad44[0xB0];
    int fieldF4;
} GameState_1F2840;

/* Counts down the pause fade timer and, when it ends, asks for the load or save slot that matches the mode, preloading the chosen weapon class (PAL). */
void menu_handle_pause_fade_timer_pal(void)
{
    int fade_timer = ((GameState_1F2840 *)g_pause_menu_state)->count;

    if (fade_timer != 0)
        ((GameState_1F2840 *)g_pause_menu_state)->count = fade_timer - 1;
    if (((GameState_1F2840 *)g_pause_menu_state)->count != 0)
        return;
    if (g_sequence_active_flag != 0)
        return;
    if (((GameState_1F2840 *)g_pause_menu_state)->mode == 2) {
        request_end_slot(0, g_selected_map_index);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 3) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 4) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 6) {
        request_begin_slot(1, 1, 0, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0);
    } else if (((GameState_1F2840 *)g_pause_menu_state)->mode == 5) {
        request_begin_slot(2, 1, ((GameState_1F2840 *)g_pause_menu_state)->fieldF4, 0, 0);
    } else {
        request_end_slot(0, 0);
    }
    if (((GameState_1F2840 *)g_pause_menu_state)->field40 != 0 &&
        ((GameState_1F2840 *)g_pause_menu_state)->field30 != ((GameState_1F2840 *)g_pause_menu_state)->field40) {
        int id;
        int *rec;
        snd_pump_music_and_disc_read_pal(1);
        id = ((GameState_1F2840 *)g_pause_menu_state)->field40;
        rec = (int *)((char *)g_weapon_table + g_item_slot_to_record[id] * 0xE0);
        LoadClassIntoFreeCacheSlot(rec[5]);
        snd_pump_music_and_disc_read_pal(1);
    }
    snd_pump_music_and_disc_read_pal(1);
}


