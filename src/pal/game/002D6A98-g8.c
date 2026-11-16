#include "include_asm.h"
#include "common.h"

/* func_PAL_002D6A98, the PAL copy of func_002D5EC0: the same C, where the highlight clamp is scaled to 50 Hz. */

/* An entry of a text list: its label, the action it runs, the action's value and the
 * timer of its highlight fade. */
typedef struct {
    short text;
    short action;
    int value;
    short text2;
    unsigned short fade_timer;
} ListEntry;

typedef struct ListMenu {
    char pad00[0x30];
    int flags;
    ListEntry *entries;
    int up;
    int down;
    int selected;
} ListMenu;

/* A menu page: the page the back button opens, the menu taking input and the menu
 * that takes it next. */
typedef struct {
    char pad00[0xE0];
    int back;
    char padE4[4];
    ListMenu *focus;
    char padEC[0x128 - 0xEC];
    int pending_focus;
} MenuPage;

/* The menu system: its current page, the page to open next and the flag that keeps the
 * menu from closing. */
typedef struct {
    char pad00[0x14];
    MenuPage *current;
    int next;
    char pad1C[0x134 - 0x1C];
    int close_locked;
} MenuSystem;

typedef struct {
    char pad000[0x1B4];
    int raw_pressed;
    char pad1B8[0xC];
    int pressed;
} PadState;

extern MenuSystem g_pause_menu_state;
extern PadState g_pad_state;
extern int g_label_default_color __attribute__((sda));
extern int g_current_map_index;
extern int g_save_menu_flags;
extern int *g_map_select_list;
extern void map_set_current_and_refresh(int);
extern void FadeToBlack(int);
extern void menu_set_pause_scale_inverse(float);
extern int menu_process_selected_row_request_pal(ListMenu *, int, int *);
extern int snd_play_from_global_bank(int, unsigned int, void *);

/* The timers are compared signed and stepped as unsigned halfwords; returning the new
 * value keeps each clamp a branch rather than a conditional move. */
static inline unsigned short incrementTimer(unsigned short timer)
{
    if ((short)timer < 32000)
        return timer + 1;
    return 32000;
}

static inline unsigned short decrementTimer(unsigned short timer)
{
    if ((short)timer > 0)
        return timer - 1;
    return 0;
}

/* Text list input: highlight fades, then close, back, the entry's action and up/down. */
int UpdateMenuListActions_pal(ListMenu *menu)
{
    int focused = g_pause_menu_state.current->focus == menu;
    int i;
    int count;
    int previous;
    int pressed;
    int buttons;

    for (i = 0; menu->entries[i].text != 0; i++) {
        /* The entry address is formed as offset + base, the order the code needs. */
        ListEntry *entry;

        if (focused && menu->selected == i) {
            entry = (ListEntry *)(i * sizeof(ListEntry) + (int)menu->entries);
            entry->fade_timer = incrementTimer(entry->fade_timer);
        } else {
            if ((short)menu->entries[i].fade_timer > ((s32)g_label_default_color * 5 + 2) / 6)
                menu->entries[i].fade_timer = ((s32)g_label_default_color * 5 + 2) / 6;
            entry = (ListEntry *)(i * sizeof(ListEntry) + (int)menu->entries);
            entry->fade_timer = decrementTimer(entry->fade_timer);
        }
    }
    if (!focused)
        return 0;

    pressed = g_pad_state.pressed;
    if (pressed & 0x900) {
        if (menu->flags & 0x20)
            map_set_current_and_refresh(g_current_map_index);
        return -1;
    }
    if (pressed & 0x10) {
        int back;
        int result;

        if (menu->flags & 0x20)
            map_set_current_and_refresh(g_current_map_index);
        back = g_pause_menu_state.current->back;
        /* The shared exit keeps the 0/-1 choice a branch rather than a conditional move. */
        if (back != 0) {
            g_pause_menu_state.next = back;
        } else if (g_pause_menu_state.close_locked == 0) {
            result = -1;
            goto finish;
        }
        result = 0;
finish:
        return result;
    }
    if ((pressed & 0x40) && ((g_save_menu_flags ^ 1) & 1)) {
        int result;

        if (menu->flags & 0x20) {
            FadeToBlack(4);
            menu_set_pause_scale_inverse(4.0f);
        }
        result = 0;
        if (menu_process_selected_row_request_pal(menu, menu->entries[menu->selected].action, &result) != 0)
            return result;
    }

    count = 0;
    while (menu->entries[count].text != 0)
        count++;
    previous = menu->selected;
    if (menu->flags & 1)
        buttons = g_pad_state.raw_pressed;
    else
        buttons = g_pad_state.pressed;
    if ((buttons & 0x1000) || ((menu->flags & 0x100) && (buttons & 4))) {
        if (menu->selected != 0)
            menu->selected--;
        else if (menu->flags & 0x1000)
            menu->selected = count - 1;
        else
            g_pause_menu_state.current->pending_focus = menu->up;
    }
    if ((buttons & 0x4000) || ((menu->flags & 0x100) && (buttons & 8))) {
        int selected = menu->selected;

        if (menu->entries[selected + 1].text != 0 && menu->entries[selected + 1].action != 0)
            menu->selected = selected + 1;
        else if (menu->flags & 0x1000)
            menu->selected = 0;
        else
            g_pause_menu_state.current->pending_focus = menu->down;
    }
    if (menu->selected != previous || g_pause_menu_state.current->pending_focus != 0) {
        snd_play_from_global_bank(3, 0, 0);
        if (menu->flags & 0x20)
            map_set_current_and_refresh(g_map_select_list[menu->selected]);
    }
    return 0;
}
