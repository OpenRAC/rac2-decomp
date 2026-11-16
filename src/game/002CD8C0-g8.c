#include "include_asm.h"
#include "names.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;

typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;

extern char *g_resident_data_base;

extern volatile unsigned char g_extras_unlocked_flag;

extern int ref_L00_002D1CB0_01;

extern int ref_L00_002D1CB0_02;

extern int ref_L00_002D1CB0_03 __attribute__((sda));

extern int ref_L00_002D1CB0_04;

extern int ref_L00_002D1CB0_05 __attribute__((sda));

extern int ref_L00_002D1CB0_06;

extern int ref_L00_002D1CB0_07 __attribute__((sda));

extern int ref_L00_002D1CB0_08 __attribute__((sda));

extern int g_menu_input_flags[];

extern int g_scroll_list_repeat_timer __attribute__((sda));

extern SelectionCallback g_pause_menu_state;

extern int g_scroll_list_index_copy[];

extern int snd_play_from_global_bank(int, unsigned int, void *);

extern CallbackMenuState g_pad_state;

extern int func_0029C560(int);

extern int func_0029C4F0(int);

extern char *tab_menu_get_selected_entry(void *);

extern void menu_start_action(int);

/* Turns on a few menu setting flags when the panel exists and the matching options are set. */
int menu_apply_setting_flags(void)
{
    if (g_resident_data_base != 0) {
        if (g_extras_unlocked_flag != 0) {
            *(volatile int *)&ref_L00_002D1CB0_01 = 1;
            *(volatile int *)&ref_L00_002D1CB0_02 = 1;
        }
        if (ref_L00_002D1CB0_03 != 0)
            *(volatile int *)&ref_L00_002D1CB0_04 = 1;
        if (ref_L00_002D1CB0_05 != 0)
            *(volatile int *)&ref_L00_002D1CB0_06 = 1;
        if (ref_L00_002D1CB0_07 != 0)
            ref_L00_002D1CB0_08 = 1;
    }
    return 0;
}

/* Handles input for a scrolling list of seven entries: up and down move the choice with a click sound, confirm and back leave. */
int menu_handle_scroll_list_input(void)
{
    int flags = g_menu_input_flags[0];
    int result = 0;
    if (flags & 0x10) {
        int value;
        int status;
        g_scroll_list_repeat_timer = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
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
    if (flags & 0x900) {
        g_scroll_list_repeat_timer = 0;
        result = 1;
    } else if (flags & 0x8000) {
        if (--g_scroll_list_repeat_timer >= 0)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (g_scroll_list_repeat_timer < 0)
            g_scroll_list_repeat_timer = 0;
    } else if (flags & 0x2000) {
        if (++g_scroll_list_repeat_timer < 7)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (g_scroll_list_repeat_timer >= 7)
            g_scroll_list_repeat_timer = 6;
    }
    g_scroll_list_index_copy[0] = g_scroll_list_repeat_timer;
    return result;
}

/* Handles menu input: confirm or back leave, otherwise it passes the buttons on and sends the chosen entry's key and value to the menu. */
int menu_handle_input_send_selection(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &g_pad_state;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
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
    if (flags & 0x900) {
        result = 1;
    } else {
        func_0029C4F0(flags);
        if ((state->flags & 0x40) && g_resident_data_base != 0) {
            char *data = tab_menu_get_selected_entry(g_resident_data_base + 0x3BE08);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            menu_start_action((int)&message);
        }
    }
    return result;
}

/* Like the menu input above, but plays a refusal sound when the chosen entry has no value. */
int menu_handle_input_send_selection_or_refuse(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &g_pad_state;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
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
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C560(flags);
        if ((state->flags & 0x40) && g_resident_data_base != 0) {
            char *data = tab_menu_get_selected_entry(g_resident_data_base + 0x3BE08);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            if (message.value == 0)
                snd_play_from_global_bank(5, 0, 0);
            menu_start_action((int)&message);
        }
    }
    return result;
}

extern int g_eight_entry_cursor __attribute__((sda));
extern unsigned char g_special_item_collected_flags[8] __attribute__((sda));
extern int g_arena_state_flag __attribute__((sda));
extern short g_sequence_active_flag[];
extern void data_set_small_value_and_refresh(int, int);

typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
extern FlagTarget *g_eight_entry_flag_targets[];
extern MenuFields g_eight_entry_menu_fields;
extern int D_0026CD20[];

/* Handles input for an eight entry menu: moves the choice, plays sounds, and starts the screen for the chosen entry if it is available. */
int menu_handle_eight_entry_input(void)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old = g_eight_entry_cursor;
    int result = 0;

    if (flags & 0x10) {
        int value;
        int status;
        g_eight_entry_cursor = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
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
    if (flags & 0x900) {
        g_eight_entry_cursor = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--g_eight_entry_cursor < 0)
                g_eight_entry_cursor = 7;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++g_eight_entry_cursor >= 8)
                g_eight_entry_cursor = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            if (g_special_item_collected_flags[g_eight_entry_cursor] != 0) {
                snd_play_from_global_bank(4, 0, 0);
                if ((unsigned)g_eight_entry_cursor < 8)
                    goto *D_0026CD20[g_eight_entry_cursor];
                goto cont;
c0:            g_arena_state_flag = 2; data_set_small_value_and_refresh(2, 1); goto cont;
c1:            g_arena_state_flag = 3; data_set_small_value_and_refresh(4, 1); goto cont;
c2:            g_arena_state_flag = 3; data_set_small_value_and_refresh(11, 1); goto cont;
c3:            g_arena_state_flag = 2; data_set_small_value_and_refresh(11, 1); goto cont;
c4:            g_arena_state_flag = 1; data_set_small_value_and_refresh(26, 1); goto cont;
c5:            g_arena_state_flag = 1; data_set_small_value_and_refresh(22, 1); goto cont;
c6:            g_arena_state_flag = 1; data_set_small_value_and_refresh(23, 1); goto cont;
c7:            data_set_small_value_and_refresh(21, 1); goto cont;
            } else {
                snd_play_from_global_bank(5, 0, 0);
            }
        }
cont:
        {
            MenuFields *menu = &g_eight_entry_menu_fields;
            menu->f58 = g_eight_entry_cursor;
            if (g_special_item_collected_flags[g_eight_entry_cursor] != 0) {
                if (old == g_eight_entry_cursor) {
                    if (g_sequence_active_flag[0] == 0) {
                        if (menu->f50 == old && menu->f44 == 2) {
                            g_eight_entry_flag_targets[0]->flags &= -5;
                        } else if (menu->f54 == old && menu->f44 == 4) {
                            g_eight_entry_flag_targets[0]->flags &= -5;
                        }
                    }
                }
            } else {
                g_eight_entry_flag_targets[0]->flags |= 4;
            }
        }
    }
    return result;
}
