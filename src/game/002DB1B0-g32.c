#include "names.h"
/* func_002DB1B0 in its own unit: its fade value and toggle flag are written through $gp, so the
   file is compiled at -G32 (config/cflags.txt). D_001B1F10 is read absolute and written through
   $gp, so it has a plain name and an sda name (as D_001A7478 in 002D01D0-g32.c). */
typedef struct { int f0; unsigned char *toggle; int pad8[2]; int flags; } ListEntry;
typedef struct { char pad0[0x34]; ListEntry *list; int cursor; int timer; } ListMenu;

extern char g_pause_menu_state[];
extern int g_pad_state[];
extern float g_screen_fade __attribute__((sda));
extern unsigned char D_001B1F10_sda __attribute__((sda));
extern unsigned char D_001B1F10;
extern void snd_play_menu_sound_if_enabled(int, int);
extern void request_begin_slot(int, int, int, int, int);
extern void FadeToBlack(int);

/* Handles input for a list menu: moves the cursor, toggles the chosen entry, or starts a short fade for special entries. */
int menu_toggle_list_update(ListMenu *object)
{
    char *root = g_pause_menu_state;
    int active = *(ListMenu **)(*(char **)(root + 0x14) + 0xE8) == object;
    int flags;
    int old;

    if (object->timer != 0) {
        int t = --object->timer;
        g_screen_fade = (float)(t < 5 ? t : 4) * 0.25f;
        return 0;
    }
    if (!active)
        return 0;
    {
        int *state = g_pad_state;
        if (!(state[0x1C4 / 4] & 0x900))
            goto proceed;
        if (*(int *)(root + 0x134) == 0)
            return 1;
    }
proceed:
    {
        int *state = g_pad_state;
        flags = state[0x1C4 / 4];
    }
    if (flags & 0x10) {
        char *root = g_pause_menu_state;
        int value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                status = -1;
                goto finish;
            default:
                break;
            }
        }
        status = 0;
finish:
        return status;
    }
    old = object->cursor;
    if (flags & 0x1000) {
        if (old != 0)
            object->cursor = old - 1;
    }
    if (g_pad_state[0x1C4 / 4] & 0x4000) {
        int cur = object->cursor;
        if (object->list[cur + 1].f0 != 0)
            object->cursor = cur + 1;
    }
    if (g_pad_state[0x1C4 / 4] & 0x40) {
        snd_play_menu_sound_if_enabled(0, 0x11);

        if (object->list[object->cursor].flags & 1) {
            if (D_001B1F10_sda) {
                char *root = g_pause_menu_state;
                request_begin_slot(4, 1, 3, *(int *)(root + 0x14), 0);
            } else {
                FadeToBlack(4);
                object->timer = 0x10;
                D_001B1F10_sda = !D_001B1F10;
            }
        } else if (object->list[object->cursor].toggle) {
            *object->list[object->cursor].toggle = !*object->list[object->cursor].toggle;
        }
    }
    if (object->cursor != old)
        snd_play_menu_sound_if_enabled(1, 0x11);
    return 0;
}
