#include "names.h"
/* func_PAL_002DE110, the PAL copy of func_002DD400 (src/game/002DD400-g32.c, where its notes are):
   the same C, where the flag D_001B1A3C goes through func_PAL_00299518 and func_PAL_00299520, the
   field at D_001A8CFC moves to 0x3CF50 and the delay is 0xC0D. Compiled at -G32 like v1.01's unit
   (config/cflags.txt). */
typedef struct { char p00[0x14]; char *owner; int value; char p1c[0xC4]; char *screen; int fe4; char pe8[0x4C]; int fallback; int busy; int delay; char p140[0x24]; int ready; } MenuRoot;
typedef struct { char reserved[0x1B4]; int alt; char p1b8[0xC]; int flags; } PadState;
typedef struct { unsigned char b[8]; } Stamp;
typedef struct { int status; int balance; int level; int ticks; Stamp stamp; int tail; } SaveSlot;
typedef struct { char p00[8]; int mode; char p0c[4]; int f10; char p14[4]; short slot; char p1a[0x16]; SaveSlot slots[4]; char p0a0[0xA8]; int f148; char p14c[0x10]; int f15c; char p160[4]; int f164; int f168; int f16c; char p170[0xC]; int f17c; } SaveState;
typedef struct { char p00[0x30]; int flags; char p34[0xC]; int cursor; int f44; int f48; int stage; } SaveMenu;
typedef struct { char p00[0x12C]; int f12c; } SaveScreen;

extern MenuRoot g_pause_menu_state;
extern PadState g_pad_state;
extern SaveState g_memcard_state;
extern SaveScreen D_00261108;
extern SaveScreen D_002613B8;
extern int D_0025E9E0[];
extern char *D_001A8CFC;
extern int g_save_menu_flags;
extern int g_save_menu_screen;
extern int D_001A8C88;
extern int D_001A8C8C;
extern int g_current_map_index;
extern int g_player_bolts;
extern int D_001A7BC0;
extern unsigned char D_001A7A0A;
extern Stamp D_001A7360;
extern int D_001A7C08;
extern char D_00261238[];
extern char D_00260EE8[];
extern char D_0025DA38[];
extern void func_PAL_0033B6B8(char *, int);
extern void func_PAL_002DF760(int);
extern void func_PAL_002DF6D0(int, int);
extern void load_data_and_setup_callback(void);
extern void save_load_game_data_reset_menu(void);
extern int func_PAL_002D6710(int, char *);
extern int request_begin_slot(int, int, int, int, int);
extern int menu_get_counter(void);
extern int menu_get_mode(void);
extern void func_PAL_002DFF60(int, int);
extern int func_PAL_00299518(void);
extern int func_PAL_00299520(void);

int func_PAL_002DE110(SaveMenu *menu)
{
    int old;
    int buttons;

    if (*(SaveMenu **)(g_pause_menu_state.owner + 0xE8) != menu)
        return 0;
    old = menu->cursor;
    if (D_001A8CFC != 0)
        func_PAL_0033B6B8(D_001A8CFC + 0x3CF50, old);
    if (menu->stage == 0 && g_pause_menu_state.screen == (char *)&D_00261108 && ((SaveScreen *)g_pause_menu_state.screen)->f12c != 0)
        menu->stage = 1;
    if (menu->stage == 0 && g_pause_menu_state.screen == (char *)&D_002613B8 && ((SaveScreen *)g_pause_menu_state.screen)->f12c != 0)
        menu->stage = 1;
    if (menu->stage == 1) {
        if (menu->flags & 0x2000)
            func_PAL_002DF760(menu->cursor);
        else
            func_PAL_002DF6D0(menu->f48, menu->cursor);
        g_memcard_state.f17c = 1;
        g_pause_menu_state.busy = 1;
        func_PAL_00299520();
        g_pause_menu_state.ready = 0;
        g_pause_menu_state.delay = 0xC0D;
    }
    menu->stage = 2;
    if (g_pause_menu_state.busy != 0) {
        SaveState *save = &g_memcard_state;
        if (save->f15c >= 3)
            return 0;
        if (save->f164 >= 0)
            return 0;
        if (g_pause_menu_state.ready < 11)
            return 0;
        g_pause_menu_state.busy = 0;
        if (save->f16c != 0 || save->f10 != 0 || func_PAL_00299518() != 0) {
            if (D_001A8C8C != 0) {
                g_save_menu_flags |= 0x80;
                request_begin_slot(4, 1, 5, (int)g_pause_menu_state.owner, 0);
                g_memcard_state.f17c = 0;
                return 0;
            }
            g_memcard_state.f17c = 0;
            g_save_menu_flags |= 0x80;
            request_begin_slot(4, 1, 1, (int)g_pause_menu_state.owner, 0);
            return 0;
        }
        save->f17c = 1;
        g_memcard_state.slots[g_memcard_state.slot].balance = g_player_bolts;
        g_memcard_state.slots[g_memcard_state.slot].status = g_current_map_index;
        g_memcard_state.slots[g_memcard_state.slot].ticks = D_001A7BC0;
        {
            Stamp *stamp = &g_memcard_state.slots[g_memcard_state.slot].stamp;
            *stamp = D_001A7360;
        }
        g_memcard_state.slots[g_memcard_state.slot].level = D_001A7A0A;
        load_data_and_setup_callback();
        save->f17c = 1;
        D_001A8C88 = 0;
        return 0;
    }
    if ((g_pad_state.flags & 0x900) && g_pause_menu_state.fallback == 0 && D_001A8C8C == 0)
        return 1;
    if ((g_pad_state.flags & 0x10) && D_001A8C8C == 0) {
        int value = *(int *)(g_pause_menu_state.owner + 0xE0);
        int status;
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (g_save_menu_screen == 9)
    {
        char *screen;
        if (D_001A8C8C != 0)
            screen = D_00261238;
        else if (D_001A8C88 != 0)
            screen = D_00260EE8;
        else
            screen = D_0025DA38;
        func_PAL_002D6710(4, screen);
    }
    else if (g_save_menu_screen != 16 && g_save_menu_screen != 1) {
        if (menu_get_counter() == 0 && menu_get_mode() == 1)
            request_begin_slot(4, 1, 1, (int)g_pause_menu_state.owner, 0);
        else if (D_001A8C8C == 0) {
            int value = *(int *)(g_pause_menu_state.owner + 0xE0);
            int status;
            if (value != 0)
                g_pause_menu_state.value = value;
            else if (g_pause_menu_state.fallback == 0) {
                status = -1;
                goto done;
            }
            status = 0;
done:
            return status;
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
    if ((buttons & 0x20) && g_memcard_state.mode == 2) {
        if (menu->flags & 0x2000) {
            g_memcard_state.f17c = 0;
            func_PAL_002DF760(-1);
            load_data_and_setup_callback();
            return 0;
        }
        save_load_game_data_reset_menu();
        {
            int mode = g_save_menu_flags & ~2;
            mode &= ~4;
            g_save_menu_flags = mode | 0x20;
        }
        load_data_and_setup_callback();
        return 0;
    }
    if (buttons & 0x40) {
        if (g_memcard_state.slots[menu->cursor].status != -1) {
            g_pause_menu_state.value = (menu->flags & 0x2000) ? (int)&D_002613B8 : (int)&D_00261108;
            g_pause_menu_state.fe4 = (menu->flags & 0x2000) ? 2 : 1;
            D_0025E9E0[0] = menu->cursor;
        } else {
            if (menu->flags & 0x2000) {
                menu->stage = 1;
                return 0;
            }
            menu->stage = 1;
            return 0;
        }
    }
    if (menu->cursor != old)
        func_PAL_002DFF60(1, 0x11);
    return 0;
}
