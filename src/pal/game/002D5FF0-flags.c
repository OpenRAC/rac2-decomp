#include "include_asm.h"
#include "names.h"

int menu_process_request_pal(short request, int param_2, int *param_3);

/* Processes the request stored in a menu entry with a throwaway result slot (PAL). */
void menu_start_action_pal(int request)
{
  int result[4];

  result[0] = 0;
  menu_process_request_pal(*(short *)(request + 2), *(int *)(request + 4), &result[0]);
  return;
}

typedef struct { char pad[4]; short mode; } Mode2D6E78;
typedef struct { char pad[0x29C]; int flags[5]; int selected; } Map2D6E78;
typedef struct { char pad[0xDB]; unsigned char active; char padDC[0x118 - 0xDC]; char *loaded; unsigned int limit; } State2D6E78;
extern Mode2D6E78 g_music_state;
extern Map2D6E78 g_map_overlay_state;
extern State2D6E78 g_pause_menu_state;
extern unsigned char g_map_selection_flag;
extern void load_request_disc_read_break(void);
extern void load_request_disc_read_break(void);

/* Cancels the pending map selection: toggles its flag, or stops the disc read when a level load was started (PAL). */
int menu_cancel_map_selection_pal(void)
{
    if (g_music_state.mode == 0) {
        Map2D6E78 *map = &g_map_overlay_state;
        int index = map->selected;
        if (index != -1) {
            g_map_selection_flag = 0;
            map->flags[index] ^= 0x1000;
            map->selected = -1;
        }
    }
    if (g_music_state.mode != 0) {
        State2D6E78 *state = &g_pause_menu_state;
        if (state->active != 0) {
            Map2D6E78 *map;
            load_request_disc_read_break();
            state->active = 0;
            map = &g_map_overlay_state;
            map->flags[map->selected] = -1;
            map->selected = -1;
        }
    }
    return 0;
}

extern int menu_update_entry_states(int *);
extern int menu_list_active_entries(unsigned int, unsigned int, unsigned int, int);
extern int g_selected_map_index;
typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 g_page_preview;
extern int g_level_page_entry_value[];

/* Refreshes the entry states of a level page and copies the selected map target values to the page preview (PAL). */
int menu_preview_entry_init_pal(int *menu)
{
    menu_update_entry_states(menu);
    *(int *)((char *)menu + 0xA0) = menu_list_active_entries(0x70000000, 0, 0x70000100, 1);
    {
        char *base = (char *)menu + 0x30;
        int index = g_selected_map_index;

        if (*(int *)(base + (index << 2)) != -1) {
            g_page_preview.f3C = -0x240;
            g_page_preview.f34 = *(int *)(0x70000000 + 4 * *(int *)(base + (index << 2)));
            *(int *)g_level_page_entry_value = *(int *)(0x70000100 + 4 * *(int *)(base + (index << 2)));
        }
    }
    *(int *)((char *)menu + 0xA4) = 0;
    return 0;
}

/* Menu page callback that does nothing and returns 0 (PAL). */
unsigned int menu_page_noop_first_pal(void)
{
    return 0;
}

/* Menu page callback that does nothing and returns 0 (PAL). */
unsigned int menu_page_noop_second_pal(void)
{
    return 0;
}

extern int g_menu_input_flags;
extern int menu_update_map_screen_pal(int);
extern int g_menu_input_flags;
extern int menu_update_map_screen_pal(int);

/* Passes the current pad buttons to the alternate page button handler (PAL). */
int menu_handle_buttons_alt_pal(void) {
    menu_update_map_screen_pal(g_menu_input_flags);
    return 0;
}
