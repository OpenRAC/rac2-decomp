#include "names.h"
/* func_US2_002DD888, the USA v2.00 copy of func_002DCB58, at -G32 like v1.01's unit. The same C, where the
   word D_001B1A3C becomes the accessors func_US2_00299960/68 (one extra saved register), the back test also
   needs D_001A8C8C clear, the field offset is 0x3CEA0 and the delay 0x2C92. */
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
extern SaveScreen D_0025E870;
extern int D_0025E9E0[];
extern char *D_001A8CFC;
extern int D_001A8C8C;
extern int g_save_menu_flags;
extern int g_save_menu_screen;
extern int D_001A8C88;
extern int g_current_map_index;
extern int g_player_bolts;
extern int D_001A7BC0;
extern unsigned char D_001A7A0A;
extern Stamp D_001A7360;
extern int D_001A7C08;
extern char D_00260EE8[];
extern char D_0025DA38[];
extern void func_US2_0033A7D8(char *, int);
extern int func_US2_00299960(void);
extern int func_US2_00299968(void);
extern void save_start_to_slot(int, int);
extern void menu_set_confirm_pending(void);
extern int menu_send_request(int, char *);
extern int request_begin_slot(int, int, int, int, int);
extern int menu_get_counter(void);
extern int menu_get_mode(void);
extern int snd_play_from_global_bank(int, unsigned int, void *);

int func_US2_002DD888(SaveMenu *menu)
{
    int old;
    int buttons;

    if (*(SaveMenu **)(g_pause_menu_state.owner + 0xE8) != menu)
        return 0;
    if (D_001A8CFC != 0)
        func_US2_0033A7D8(D_001A8CFC + 0x3CEA0, menu->cursor);
    if (menu->stage == 0 && g_pause_menu_state.screen == (char *)&D_0025E870 && D_0025E870.f12c != 0)
        menu->stage = 1;
    if (menu->stage == 1) {
        save_start_to_slot(menu->f48, menu->cursor);
        g_pause_menu_state.busy = 1;
        func_US2_00299968();
        g_pause_menu_state.delay = 0x2C92;
    }
    menu->stage = 2;
    old = menu->cursor;
    if (g_pause_menu_state.busy != 0) {
        if (g_memcard_state.f15c >= 3)
            return 0;
        if (g_memcard_state.f164 >= 0)
            return 0;
        if (g_pause_menu_state.ready < 11)
            return 0;
        g_pause_menu_state.busy = 0;
        if (g_memcard_state.f16c != 0 || g_memcard_state.f10 != 0 || func_US2_00299960() != 0) {
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
            g_memcard_state.slots[g_memcard_state.slot].ticks = D_001A7BC0;
            {
                Stamp *stamp = &g_memcard_state.slots[g_memcard_state.slot].stamp;
                *stamp = D_001A7360;
            }
            g_memcard_state.slots[g_memcard_state.slot].level = D_001A7A0A;
        }
    }
    if ((g_pad_state.flags & 0x900) && g_pause_menu_state.fallback == 0 && D_001A8C8C == 0)
        return 1;
    if (g_pad_state.flags & 0x10) {
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
        menu_send_request(4, D_001A8C88 ? D_00260EE8 : D_0025DA38);
    else if (g_save_menu_screen != 16 && g_save_menu_screen != 1) {
        if (menu_get_counter() == 0 && menu_get_mode() == 1)
            request_begin_slot(4, 1, 1, (int)g_pause_menu_state.owner, 0);
        else {
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
    if (buttons & 0x40) {
        SaveState *save = &g_memcard_state;
        if (save->mode == 2) {
            snd_play_from_global_bank(4, 0, 0);
            if (save->slots[menu->cursor].status != -1) {
                g_pause_menu_state.fe4 = 0;
                g_pause_menu_state.value = (int)&D_0025E870;
                D_0025E9E0[0] = menu->cursor;
            } else
                menu->stage = 1;
        }
    }
    if (menu->cursor != old)
        snd_play_from_global_bank(3, 0, 0);
    return 0;
}
