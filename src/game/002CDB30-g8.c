#include "common.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;

/* 0x18-byte rows; the halfword at +0xA is shown for the selected row. */
typedef struct {
    char reserved00[0xA];
    short value;
    char reserved0c[0xC];
} TableRow;

typedef struct {
    char reserved00[0x58];
    int value;
} MenuCounter;

typedef struct {
    char reserved00[0x34];
    int value;
    int reserved38;
    int motion;
} MenuSelection;

extern int g_menu_input_flags NOT_SDA;
extern CallbackState g_pause_menu_state;
extern int g_item_list_cursor __attribute__((sda));
extern int g_item_list_prev_row __attribute__((sda));
extern int g_item_list_next_row __attribute__((sda));
/* Two halfword counts per row (see func_002A6AE0). */
extern unsigned short g_kill_event_counts[][2];
extern TableRow g_item_menu_table[];
extern MenuCounter g_menu_counter_2;
extern MenuSelection g_menu_selection;
extern int snd_play_from_global_bank(int, unsigned int, void *);

/* Handles the left and right buttons on the item list menu and picks the nearest rows that have items. */
int menu_handle_item_list_input(void)
{
    int flags = g_menu_input_flags;
    int previous_row = g_item_list_cursor;
    int result = 0;

    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900) {
        result = 1;
    } else if (flags & 0x8000) {
        if (previous_row != g_item_list_prev_row)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        g_item_list_cursor = g_item_list_prev_row;
        if (g_item_list_cursor <= 0)
            g_item_list_cursor = 1;
    } else if (flags & 0x2000) {
        if (previous_row != g_item_list_next_row)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        g_item_list_cursor = g_item_list_next_row;
        if (g_item_list_cursor >= 64)
            g_item_list_cursor = 63;
    }

    /* The nearest rows below and above the current one with a nonzero count;
       row 1 and the current row when there is none. */
    g_item_list_next_row = g_item_list_cursor + 1;
    g_item_list_prev_row = g_item_list_cursor - 1;
    for (;;) {
        if (g_kill_event_counts[g_item_list_prev_row][0] != 0 || g_kill_event_counts[g_item_list_prev_row][1] != 0)
            break;
        if (--g_item_list_prev_row <= 0) {
            g_item_list_prev_row = 1;
            break;
        }
    }
    {
        int current_row = g_item_list_cursor;
        for (;;) {
            if (g_kill_event_counts[g_item_list_next_row][0] != 0 || g_kill_event_counts[g_item_list_next_row][1] != 0)
                break;
            if (++g_item_list_next_row >= 64) {
                g_item_list_next_row = current_row;
                break;
            }
        }
    }

    if (g_kill_event_counts[g_item_list_cursor][0] == 0 && g_kill_event_counts[g_item_list_cursor][1] == 0) {
        g_menu_counter_2.value = 63;
        g_menu_selection.value = 0;
    } else {
        g_menu_counter_2.value = g_item_list_cursor - 1;
        g_menu_selection.value = g_item_menu_table[g_item_list_cursor].value;
    }
    if (g_item_list_cursor != previous_row)
        g_menu_selection.motion = -576;
    return result;
}
