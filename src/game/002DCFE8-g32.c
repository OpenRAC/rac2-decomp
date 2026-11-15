#include "names.h"
/* func_002DCFE8 in its own unit: retail reads its small scalars absolute and through $gp, so
   the file is compiled at -G32 (config/cflags.txt). */
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0x118]; int fallback; int busy; int delay; char p140[0x24]; int ready; } MenuRoot;
typedef struct { char reserved[0x1B4]; int alt; char p1b8[0xC]; int flags; } PadState;
typedef struct { int status; char p04[0x18]; } SaveSlot;
typedef struct { char p00[8]; int mode; char p0c[4]; int f10; char p14[4]; short slot; char p1a[0x16]; SaveSlot slots[4]; char p0a0[0xA8]; int f148; char p14c[0x10]; int f15c; char p160[4]; int f164; int f168; int f16c; char p170[0xC]; int f17c; } SaveState;
typedef struct { char p00[0x30]; int flags; char p34[0xC]; int cursor; } SaveMenu;

extern MenuRoot g_pause_menu_state;
extern PadState g_pad_state;
extern SaveState g_memcard_state;
extern char *D_001A8CFC;
extern int D_001B1A3C;
extern int g_save_menu_flags;
extern int g_save_menu_screen;
extern int D_001A8C88;
extern int D_001A7B98;
extern int g_current_map_index;
extern unsigned char D_001A7BE8;
extern int D_001A7C08;
extern short D_00152C28[];
extern int D_001C4FB0[];
extern char D_001F2A40[];
extern char D_00260DB8[];
extern char D_0025DB68[];
extern void popup_set_row(char *, int);
extern void snd_set_default_group_volumes(void);
extern int snd_pump_music_and_disc_read(int);
extern void snd_send_cmd11_one_value(int);
extern void load_data_and_setup_callback(void);
extern int menu_send_request(int, char *);
extern void save_build_packet(char *);
extern void menu_init_block_fields(void);
extern int request_begin_slot(int, int, int, int, int);
extern int menu_get_counter(void);
extern int menu_get_mode(void);
extern int snd_play_from_global_bank(int, unsigned int, void *);

/* Handles the load-game slot menu: moves the cursor over the four slots and starts loading the chosen one. */
int load_slot_menu_update(SaveMenu *menu)
{
    int oldCursor = menu->cursor;
    int buttons;

    if (D_001A8CFC != 0)
        popup_set_row(D_001A8CFC + 0x3CAA8, oldCursor);
    if (g_pause_menu_state.busy != 0) {
        if (g_memcard_state.f15c >= 3)
            return 0;
        if (g_memcard_state.f164 >= 0)
            return 0;
        if (g_pause_menu_state.ready < 11)
            return 0;
        g_pause_menu_state.busy = 0;
        if (g_memcard_state.f16c != 0 || g_memcard_state.f10 != 0 || D_001B1A3C != 0) {
            g_memcard_state.f17c = 0;
            g_save_menu_flags |= 0x100;
            if (request_begin_slot(4, 1, 1, (int)g_pause_menu_state.owner, 0) == 0)
                return 0;
        } else {
            g_memcard_state.f17c = 1;
            snd_set_default_group_volumes();
            snd_pump_music_and_disc_read(1);
            snd_send_cmd11_one_value(D_001A7B98 == 0);
            if (g_current_map_index <= 0 && D_001A7BE8 == 0)
                load_data_and_setup_callback();
            else
                request_begin_slot(6, 2, 5, g_current_map_index, 0);
            D_00152C28[0] = 0;
            return 0;
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
        menu_send_request(5, D_001A8C88 ? D_00260DB8 : D_0025DB68);
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
    menu->cursor = D_001A7C08;
    if ((buttons & 0x1000) && D_001A7C08 != 0)
        menu->cursor = D_001A7C08 - 1;
    if ((buttons & 0x4000) && menu->cursor < 3)
        menu->cursor = menu->cursor + 1;
    D_001A7C08 = menu->cursor;
    if (buttons & 0x40) {
        SaveState *save = &g_memcard_state;
        if (save->mode == 2 && save->slots[D_001A7C08].status >= 0) {
            snd_play_from_global_bank(4, 0, 0);
            save->f148 = 0;
            save->slot = menu->cursor;
            save_build_packet(D_001F2A40);
            menu_init_block_fields();
            if (save->f164 < 0) {
                save->f168 = 0;
                save->f164 = 13;
            }
            g_pause_menu_state.busy = 1;
            g_pause_menu_state.delay = 0x2DFD;
            D_001C4FB0[0] = 0;
            D_001B1A3C = 0;
        } else
            snd_play_from_global_bank(5, 0, 0);
    }
    if (menu->cursor != oldCursor)
        snd_play_from_global_bank(3, 0, 0);
    return 0;
}
