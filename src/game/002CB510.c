#include "common.h"

typedef struct {
    int count;
    int id;
    int pad;
    int state[25];
} LevelSelect_210A40;

extern LevelSelect_210A40 g_pause_cinema_controller;
extern unsigned char g_map_visited_flags[] __attribute__((sda));
extern unsigned char g_mission_active_flag[] __attribute__((sda));
extern int g_menu_text_id_table[];
extern void data_set_small_value_and_refresh(int, int);
extern void menu_ring_list_step_backward(s32 *);
extern void menu_ring_list_step_forward(s32 *);
extern s32 menu_is_index_allowed(s32);

/* Refreshes which planets can be picked in the level select list and handles the buttons: open, close, or choose a planet. */
int RebuildLevelSelectAvailability(int flags)
{
    int result = -1;
    int i;

    for (i = 0; i <= g_pause_cinema_controller.count; i++) {
        if (menu_is_index_allowed(i))
            g_pause_cinema_controller.state[i] = g_map_visited_flags[i] != 0;
    }
    g_pause_cinema_controller.state[0] = 0;
    if (flags & 0x1000) {
        menu_ring_list_step_backward((s32 *)&g_pause_cinema_controller);
    } else if (flags & 0x4000) {
        menu_ring_list_step_forward((s32 *)&g_pause_cinema_controller);
    } else if (flags & 0x40) {
        result = g_pause_cinema_controller.id;
        if (g_menu_text_id_table[result * 2] == 0xB47 && g_mission_active_flag[0] == 0)
            data_set_small_value_and_refresh(0x19, 1);
        else
            data_set_small_value_and_refresh(result, 1);
    }
    return result;
}
