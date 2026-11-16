#include "names.h"
/* func_002DCB58 in its own unit, a sibling of func_002DCFE8: retail reads its small scalars
   absolute and through $gp, so the file is compiled at -G32 (config/cflags.txt). The word at
   D_0025E9E0 gets its own %hi, not one derived from D_0025E870's, so it is its own global. */
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0xC4]; char *screen; int fe4; char pe8[0x4C]; int fallback; int busy; int delay; char p140[0x24]; int ready; } MenuRoot;
typedef struct { char reserved[0x1B4]; int alt; char p1b8[0xC]; int flags; } PadState;
typedef struct { unsigned char b[8]; } Stamp;
typedef struct { int status; int balance; int level; int ticks; Stamp stamp; int tail; } SaveSlot;
typedef struct { char p00[8]; int mode; char p0c[4]; int f10; char p14[4]; short slot; char p1a[0x16]; SaveSlot slots[4]; char p0a0[0xA8]; int f148; char p14c[0x10]; int f15c; char p160[4]; int f164; int f168; int f16c; char p170[0xC]; int f17c; } SaveState;
typedef struct { char p00[0x30]; int flags; char p34[0xC]; int cursor; int f44; int f48; int stage; } SaveMenu;
typedef struct { char p00[0x12C]; int f12c; char p130[0x40]; int f170; } SaveScreen;

extern MenuRoot g_pause_menu_state;
extern PadState g_pad_state;
extern SaveState g_memcard_state;
extern SaveScreen g_save_screen;
extern int g_save_menu_cursor[];
extern char *g_resident_data_base;
extern int g_map_state_flag;
extern int g_save_menu_flags;
extern int g_save_menu_screen;
extern int g_menu_panel_active;
extern int g_current_map_index;
extern int g_player_bolts;
extern int g_frame_counter_2;
extern unsigned char g_extras_unlocked_flag;
extern Stamp g_cd_clock_buffer;
extern int g_save_slot_cursor;
extern char g_save_slot_screen_alt[];
extern char g_save_slot_screen[];
extern void popup_set_row(char *, int);
extern void save_start_to_slot(int, int);
extern void menu_set_confirm_pending(void);
extern int menu_send_request(int, char *);
extern int request_begin_slot(int, int, int, int, int);
extern int menu_get_counter(void);
extern int menu_get_mode(void);
extern int snd_play_from_global_bank(int, unsigned int, void *);

/* Handles the save-game slot menu: moves the cursor over the four slots, asks before overwriting a used slot, and updates the slot summary after a save finishes. */
int save_slot_menu_update(SaveMenu *menu)
{
    int oldCursor;
    int buttons;

    if (*(SaveMenu **)(g_pause_menu_state.owner + 0xE8) != menu)
        return 0;
    if (g_resident_data_base != 0)
        popup_set_row(g_resident_data_base + 0x3CAA8, menu->cursor);
    if (menu->stage == 0 && g_pause_menu_state.screen == (char *)&g_save_screen && g_save_screen.f12c != 0)
        menu->stage = 1;
    if (menu->stage == 1) {
        save_start_to_slot(menu->f48, menu->cursor);
        g_pause_menu_state.busy = 1;
        g_pause_menu_state.delay = 0x2DFC;
        g_map_state_flag = 0;
    }
    menu->stage = 2;
    oldCursor = menu->cursor;
    if (g_pause_menu_state.busy != 0) {
        if (g_memcard_state.f15c >= 3)
            return 0;
        if (g_memcard_state.f164 >= 0)
            return 0;
        if (g_pause_menu_state.ready < 11)
            return 0;
        g_pause_menu_state.busy = 0;
        if (g_memcard_state.f16c != 0 || g_memcard_state.f10 != 0 || g_map_state_flag != 0) {
            g_save_menu_flags |= 0x80;
            if (g_memcard_state.f17c != 0) {
                g_memcard_state.f17c = 0;
                menu_set_confirm_pending();
            }
            if (request_begin_slot(4, 1, 1, (int)g_pause_menu_state.owner, 0) == 0)
                return 0;
        } else {
            g_memcard_state.f17c = 1;
            g_memcard_state.slots[g_memcard_state.slot].balance = g_player_bolts;
            g_memcard_state.slots[g_memcard_state.slot].status = g_current_map_index;
            g_memcard_state.slots[g_memcard_state.slot].ticks = g_frame_counter_2;
            {
                Stamp *stamp = &g_memcard_state.slots[g_memcard_state.slot].stamp;
                *stamp = g_cd_clock_buffer;
            }
            g_memcard_state.slots[g_memcard_state.slot].level = g_extras_unlocked_flag;
        }
    }
    if ((g_pad_state.flags & 0x900) && g_pause_menu_state.fallback == 0)
        return 1;
    if (g_pad_state.flags & 0x10) {
        int parentScreen = *(int *)(g_pause_menu_state.owner + 0xE0);
        int result;
        if (parentScreen != 0)
            g_pause_menu_state.value = parentScreen;
        else if (g_pause_menu_state.fallback == 0) {
            result = -1;
            goto finish;
        }
        result = 0;
finish:
        return result;
    }
    if (g_save_menu_screen == 9)
        menu_send_request(4, g_menu_panel_active ? g_save_slot_screen_alt : g_save_slot_screen);
    else if (g_save_menu_screen != 16 && g_save_menu_screen != 1) {
        if (menu_get_counter() == 0 && menu_get_mode() == 1)
            request_begin_slot(4, 1, 1, (int)g_pause_menu_state.owner, 0);
        else {
            int parentScreen = *(int *)(g_pause_menu_state.owner + 0xE0);
            int result;
            if (parentScreen != 0)
                g_pause_menu_state.value = parentScreen;
            else if (g_pause_menu_state.fallback == 0) {
                result = -1;
                goto done;
            }
            result = 0;
done:
            return result;
        }
    }
    if (g_memcard_state.f15c >= 3)
        return 0;
    if (g_memcard_state.f164 >= 0)
        return 0;
    if (g_pause_menu_state.ready < 11)
        return 0;
    if (g_memcard_state.mode != 2)
        return 0;
    if (menu->flags & 1)
        buttons = g_pad_state.alt;
    else
        buttons = g_pad_state.flags;
    menu->cursor = g_save_slot_cursor;
    if ((buttons & 0x1000) && g_save_slot_cursor != 0)
        menu->cursor = g_save_slot_cursor - 1;
    if ((buttons & 0x4000) && menu->cursor < 3)
        menu->cursor = menu->cursor + 1;
    g_save_slot_cursor = menu->cursor;
    if (buttons & 0x40) {
        SaveState *save = &g_memcard_state;
        if (save->mode == 2) {
            snd_play_from_global_bank(4, 0, 0);
            if (save->slots[menu->cursor].status != -1) {
                g_pause_menu_state.fe4 = 0;
                g_pause_menu_state.value = (int)&g_save_screen;
                g_save_menu_cursor[0] = menu->cursor;
            } else
                menu->stage = 1;
        }
    }
    if (menu->cursor != oldCursor)
        snd_play_from_global_bank(3, 0, 0);
    return 0;
}
